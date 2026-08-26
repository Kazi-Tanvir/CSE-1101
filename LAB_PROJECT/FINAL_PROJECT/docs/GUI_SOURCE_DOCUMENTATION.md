# `gui.c` — Detailed Source Code Documentation

This document provides a **line-by-line breakdown** of `src/programs/gui.c`, the file responsible for the entire graphical user interface of the Image Manipulation Software.

---

## Table of Contents

1. [File Overview](#file-overview)
2. [Includes & Dependencies](#includes--dependencies)
3. [Global State Variables](#global-state-variables)
4. [Undo System](#undo-system)
5. [Status Bar Updates](#status-bar-updates)
6. [Display Pipeline — How Images Appear on Screen](#display-pipeline--how-images-appear-on-screen)
7. [Canvas Redraw — The Heart of Rendering](#canvas-redraw--the-heart-of-rendering)
8. [File Callbacks (Open / Save)](#file-callbacks-open--save)
9. [Filter Callbacks (Grayscale, Invert, Flip, etc.)](#filter-callbacks)
10. [Crop & Brightness Callbacks (User Input Dialogs)](#crop--brightness-callbacks)
11. [Exit & Cleanup](#exit--cleanup)
12. [Building the GUI — `build_main_gui()`](#building-the-gui--build_main_gui)
13. [Complete Call Flow Diagram](#complete-call-flow-diagram)

---

## File Overview

| Property        | Value                           |
|-----------------|---------------------------------|
| **File**        | `src/programs/gui.c`           |
| **Header**      | `src/header/gui.h`             |
| **Role**        | Builds the IUP window, handles all user interactions, renders images on a canvas |
| **Exported Functions** | `build_main_gui()`, `cleanup_images()` |
| **All other functions** | `static` (private to this file) |

The file follows this architecture:

```
gui.c
├── Global State (image pointers, canvas handle, status bar)
├── Undo System (save_undo, undo)
├── Display Pipeline (update_status, update_display)
├── Canvas Renderer (canvas_action — called by IUP on every repaint)
├── File Callbacks (open, save)
├── Filter Callbacks (grayscale, invert, flip, blur, sharpen, rotate, crop, brightness)
├── Exit & Cleanup
└── GUI Builder (build_main_gui — assembles the entire window)
```

---

## Includes & Dependencies

```c
#include "gui.h"        // Our header — pulls in image.h, filter.h, and <iup.h>
#include <stdio.h>      // snprintf()
#include <stdlib.h>     // malloc(), free()
#include <string.h>     // strlen(), strncpy(), strrchr()
#include <iupdraw.h>    // IupDrawBegin, IupDrawImage, IupDrawEnd, etc.
```

**Why `<iupdraw.h>`?**
The standard `<iup.h>` provides widgets (buttons, labels, dialogs). But to **draw pixels directly onto a canvas** (images, rectangles, text), you need `<iupdraw.h>`. This is the IUP Canvas Draw API.

---

## Global State Variables

```c
static Image *current_image  = NULL;   // The image currently being edited
static Image *prev_image     = NULL;   // The previous state (for undo)
static Ihandle *canvas       = NULL;   // The IUP canvas widget
static Ihandle *status_bar   = NULL;   // The bottom status label
static Ihandle *current_iup_img = NULL; // IUP's internal image handle
static const char *IMG_HANDLE_NAME = "GUI_ACTIVE_IMAGE"; // Named handle for drawing
static char loaded_filename[260] = "Untitled";           // Current filename
```

### Why `static`?

In C, `static` at file scope means **"private to this file"**. No other `.c` file can access these variables. This is important for encapsulation — `main.c` only sees `build_main_gui()` and `cleanup_images()`.

### Why Two Image Types?

We maintain **two separate representations** of the image:

| Variable | Type | Purpose |
|----------|------|---------|
| `current_image` | `Image*` (our struct) | Stores pixel data as an array of `{r, g, b}` structs. Used by all filters. |
| `current_iup_img` | `Ihandle*` (IUP image) | An IUP image object created from pixel data. Required by `IupDrawImage()` to render on the canvas. |

Every time a filter modifies `current_image`, we must **rebuild** `current_iup_img` from the new pixel data.

---

## Undo System

```c
static void save_undo(void) {
    if (!current_image) return;
    if (prev_image) {
        free_image(prev_image);
        prev_image = NULL;
    }
    prev_image = clone_image(current_image);
}
```

**How it works:**
1. Before applying any filter, call `save_undo()`.
2. This clones the **entire** current image into `prev_image`.
3. If there was already an old undo state, it gets freed first (we only support 1 undo level).

```c
static void undo(void) {
    if (!prev_image) return;
    if (current_image) {
        free_image(current_image);
    }
    current_image = prev_image;
    prev_image = NULL;
}
```

**Undo** simply:
1. Frees the current (modified) image.
2. Points `current_image` to the saved `prev_image`.
3. Sets `prev_image = NULL` (nothing left to undo).

> **Limitation:** Only 1 level of undo. A multi-level undo would require a linked list or array of snapshots.

---

## Status Bar Updates

```c
static void update_status(const char *action_msg) {
    if (!status_bar) return;
    if (current_image) {
        char buf[512];
        if (action_msg && strlen(action_msg) > 0) {
            snprintf(buf, sizeof(buf),
                " [%s]  File: %s | Dimensions: %d x %d px | 24-bit RGB",
                action_msg, loaded_filename,
                current_image->width, current_image->height);
        } else {
            snprintf(buf, sizeof(buf),
                " File: %s | Dimensions: %d x %d px | 24-bit RGB",
                loaded_filename,
                current_image->width, current_image->height);
        }
        IupSetStrAttribute(status_bar, "TITLE", buf);
    } else {
        IupSetStrAttribute(status_bar, "TITLE",
            " Ready. Please open a 24-bit BMP image.");
    }
}
```

**Key Detail:** We use `IupSetStrAttribute()` (not `IupSetAttribute()`!) because `buf` is a local variable on the stack. `IupSetStrAttribute()` makes IUP **copy** the string internally, so it survives after `buf` goes out of scope.

---

## Display Pipeline — How Images Appear on Screen

This is the most important function to understand. Every time the image changes, we call:

```c
static void update_display(const char *action_msg) { ... }
```

### Step-by-step breakdown:

### Step 1: Destroy the old IUP image

```c
if (current_iup_img) {
    IupSetHandle((char*)IMG_HANDLE_NAME, NULL);  // Unregister the name
    IupDestroy(current_iup_img);                 // Free IUP's internal memory
    current_iup_img = NULL;
}
```

IUP images are **separate objects** in memory. If we don't destroy the old one before creating a new one, we leak memory every time a filter is applied.

### Step 2: Convert our pixel data → IUP image

```c
if (current_image && current_image->data) {
    int width = current_image->width;
    int height = current_image->height;

    // Allocate a flat RGB buffer (R,G,B,R,G,B,...)
    unsigned char *rgb = (unsigned char*)malloc(width * height * 3);

    // Copy our Pixel structs → flat RGB array
    for (int i = 0; i < (width * height); i++) {
        rgb[i * 3 + 0] = current_image->data[i].r;
        rgb[i * 3 + 1] = current_image->data[i].g;
        rgb[i * 3 + 2] = current_image->data[i].b;
    }

    // Create IUP image from the flat buffer
    current_iup_img = IupImageRGB(width, height, rgb);
    free(rgb);   // IUP makes its own copy

    // Register with a global name so IupDrawImage() can find it
    if (current_iup_img) {
        IupSetHandle((char*)IMG_HANDLE_NAME, current_iup_img);
    }
}
```

**Why the conversion?**
- Our `Image` struct stores pixels as `Pixel` structs: `{r, g, b}`.
- `IupImageRGB()` expects a flat byte array: `R₁G₁B₁R₂G₂B₂...`.
- They are the same data, just different memory layouts. The loop does the conversion.

**Why `IupSetHandle()`?**
- `IupDrawImage()` takes an image **by name** (a string), not by pointer.
- `IupSetHandle("GUI_ACTIVE_IMAGE", img)` registers the image with that name.
- Later, `IupDrawImage(ih, "GUI_ACTIVE_IMAGE", ...)` finds it by name.

### Step 3: Update status bar & trigger canvas repaint

```c
update_status(action_msg);

if (canvas) {
    IupUpdate(canvas);  // Tells IUP: "redraw the canvas on next event cycle"
}
```

`IupUpdate()` doesn't redraw immediately — it marks the canvas as "dirty". IUP will call `canvas_action()` during the next event processing cycle.

---

## Canvas Redraw — The Heart of Rendering

```c
static int canvas_action(Ihandle *ih, float posx, float posy) { ... }
```

This function is **called by IUP** every time the canvas needs to be redrawn:
- When the window is first shown
- When the window is resized
- When `IupUpdate(canvas)` is called
- When the window is uncovered after being behind another window

### Rendering steps:

### 1. Begin drawing & get canvas size

```c
IupDrawBegin(ih);
int cw = 0, ch = 0;
IupDrawGetSize(ih, &cw, &ch);   // Canvas width & height in pixels
```

### 2. Clear background (dark gray)

```c
IupSetAttribute(ih, "DRAWCOLOR", "30 33 39");   // RGB color
IupSetAttribute(ih, "DRAWSTYLE", "FILL");        // Filled rectangle
IupDrawRectangle(ih, 0, 0, cw, ch);              // Entire canvas
```

### 3a. If image exists — draw it centered with auto-scaling

```c
// Calculate scale factor to fit image within canvas (with margins)
double scale = 1.0;
int margin = 20;
int avail_w = cw - margin * 2;
int avail_h = ch - margin * 2;

if (iw > avail_w || ih_h > avail_h) {
    double sx = (double)avail_w / (double)iw;
    double sy = (double)avail_h / (double)ih_h;
    scale = (sx < sy) ? sx : sy;   // Use the smaller scale to preserve aspect ratio
}

// Calculate centered position
int x = (cw - draw_w) / 2;
int y = (ch - draw_h) / 2;

// Draw a subtle border around the image
IupSetAttribute(ih, "DRAWCOLOR", "18 20 24");
IupSetAttribute(ih, "DRAWSTYLE", "STROKE");
IupDrawRectangle(ih, x - 1, y - 1, x + draw_w, y + draw_h);

// Draw the actual image
IupDrawImage(ih, IMG_HANDLE_NAME, x, y, draw_w, draw_h);
```

**Auto-scaling logic:**
- If the image is 4000×3000 but the canvas is only 800×600, we compute `scale = min(780/4000, 580/3000)` to make it fit while preserving aspect ratio.
- If the image is smaller than the canvas, `scale` stays at 1.0 (no scaling).

### 3b. If no image — draw placeholder text

```c
IupSetAttribute(ih, "DRAWCOLOR", "225 228 234");   // Light text
IupDrawText(ih, title, 0, tx, ty, tw, th);

IupSetAttribute(ih, "DRAWCOLOR", "140 145 160");   // Gray subtext
IupDrawText(ih, sub, 0, stx, sty, stw, sth);
```

### 4. Finish drawing

```c
IupDrawEnd(ih);
return IUP_DEFAULT;
```

**Important:** All drawing MUST happen between `IupDrawBegin()` and `IupDrawEnd()`. Drawing outside this pair is undefined behavior.

---

## File Callbacks (Open / Save)

### Open

```c
static int callback_file_open(Ihandle *self) { ... }
```

1. Creates an `IupFileDlg()` with `DIALOGTYPE = "OPEN"` and a BMP filter.
2. Shows it with `IupPopup()` (modal — blocks until user picks a file).
3. Checks `STATUS != -1` (user didn't cancel).
4. Gets the chosen path from `IupGetAttribute(file_dlg, "VALUE")`.
5. Calls `load_bmp(filename)` to read the BMP file.
6. Extracts just the filename (not the full path) using `strrchr()` to find the last `\` or `/`.
7. Calls `update_display("Image Opened")`.
8. Destroys the dialog with `IupDestroy(file_dlg)`.

### Save

```c
static int callback_file_save(Ihandle *self) { ... }
```

Same flow but with `DIALOGTYPE = "SAVE"` and calls `save_bmp()`.

---

## Filter Callbacks

All filter callbacks follow the same pattern:

```c
static int callback_FILTER(Ihandle *self) {
    (void)self;                             // Suppress "unused parameter" warning
    if (!current_image) {                   // Guard: no image loaded
        IupMessage("Error", "No image loaded.");
        return IUP_DEFAULT;
    }
    save_undo();                            // Save current state for undo
    APPLY_FILTER(current_image);            // Apply the filter
    update_display("Filter Name");          // Rebuild IUP image + refresh canvas
    return IUP_DEFAULT;
}
```

### In-place filters (modify `current_image` directly)

| Callback | Filter Function | What It Does |
|----------|----------------|--------------|
| `callback_grayscale` | `grayscale(img)` | Converts each pixel to its luminance value |
| `callback_inversion` | `inversion(img)` | Inverts each channel: `255 - value` |
| `callback_horizontalFlip` | `horizontalFlip(img)` | Mirrors left ↔ right |
| `callback_verticalFlip` | `verticalFlip(img)` | Mirrors top ↔ bottom |

### New-image filters (return a new `Image*`, old one is freed)

| Callback | Filter Function | What It Does |
|----------|----------------|--------------|
| `callback_blur` | `blur(img)` | 3×3 box blur (average neighboring pixels) |
| `callback_sharpen` | `sharpen(img)` | 3×3 sharpen kernel |
| `callback_rotate90` | `rotate90(img)` | 90° clockwise rotation (width↔height swap) |

**Pattern for new-image filters:**
```c
Image *new_img = blur(current_image);
if (new_img) {
    free_image(current_image);         // Free old data
    current_image = new_img;           // Point to new data
    update_display("Blur Filter");
}
```

---

## Crop & Brightness Callbacks

These callbacks use `IupGetParam()` to show an input dialog.

### Crop

```c
static int callback_crop(Ihandle *self) { ... }
```

**Problem we solved:** `IupGetParam()` format syntax is **NOT** `printf()`. Each `%i` in the format string expects **exactly one `int*`** in the argument list. The format string label can contain `[min,max]` range hints.

We build the format dynamically:
```c
char fmt[256];
snprintf(fmt, sizeof(fmt),
    "X1 (Left) [0,%d]: %%i\n"      // %%i → literal %i for IUP
    "Y1 (Top) [0,%d]: %%i\n"
    "X2 (Right) [0,%d]: %%i\n"
    "Y2 (Bottom) [0,%d]: %%i\n",
    max_x, max_y, max_x, max_y);

IupGetParam("Crop Image Coordinates", NULL, NULL,
            fmt,
            &x1, &y1, &x2, &y2, NULL);
```

### Brightness

```c
int level = 0;
IupGetParam("Adjust Brightness", NULL, NULL,
            "Brightness level (-255 to 255): %i\n",
            &level, NULL);
```

Simpler — just one integer input.

---

## Exit & Cleanup

```c
static int callback_exit(Ihandle *self) {
    (void)self;
    return IUP_CLOSE;   // Tells IupMainLoop() to stop
}
```

```c
void cleanup_images(void) {
    // 1. Unregister and destroy the IUP image handle
    if (current_iup_img) {
        IupSetHandle((char*)IMG_HANDLE_NAME, NULL);
        IupDestroy(current_iup_img);
        current_iup_img = NULL;
    }
    // 2. Free our pixel data
    if (current_image) { free_image(current_image); current_image = NULL; }
    if (prev_image)    { free_image(prev_image);    prev_image = NULL; }
}
```

`cleanup_images()` is called from `main.c` **after** `IupMainLoop()` returns but **before** `IupClose()`.

---

## Building the GUI — `build_main_gui()`

This is the single function that assembles the entire window. Here's the hierarchy it creates:

```
IupDialog (main window)
├── MENU → IupMenu (menu bar)
│   ├── IupSubmenu("File") → IupMenu
│   │   ├── IupItem("Open")     → callback_file_open
│   │   ├── IupItem("Save As")  → callback_file_save
│   │   ├── IupSeparator()
│   │   └── IupItem("Exit")     → callback_exit
│   ├── IupSubmenu("Edit") → IupMenu
│   │   └── IupItem("Undo")     → callback_undo
│   └── IupSubmenu("Image") → IupMenu
│       ├── IupItem("Grayscale")      → callback_grayscale
│       ├── IupItem("Brightness...")   → callback_brightness
│       ├── IupItem("Invert Colors")  → callback_inversion
│       ├── IupSeparator()
│       ├── IupItem("Horizontal Flip") → callback_horizontalFlip
│       ├── IupItem("Vertical Flip")   → callback_verticalFlip
│       ├── IupItem("Rotate 90° CW")  → callback_rotate90
│       ├── IupSeparator()
│       ├── IupItem("Crop...")         → callback_crop
│       ├── IupItem("Blur (Smooth)")   → callback_blur
│       └── IupItem("Sharpen")         → callback_sharpen
│
└── IupVbox (vertical layout)
    ├── IupHbox (toolbar — horizontal row of buttons)
    │   ├── [Open] [Save] [Undo]
    │   ├── IupFill()  ← pushes remaining buttons to the right
    │   └── [Gray] [Bright] [Invert] [H-Flip] [V-Flip] [Rotate] [Crop] [Blur] [Sharp]
    ├── IupCanvas (drawing area — EXPAND=YES, fills all available space)
    └── IupLabel (status bar — EXPAND=HORIZONTAL)
```

### Key attributes set on the dialog:

| Attribute | Value | Meaning |
|-----------|-------|---------|
| `TITLE` | `"CSE 1101 — Image Manipulation Software"` | Window title bar text |
| `RASTERSIZE` | `"900x700"` | Initial window size in pixels |
| `SHRINK` | `"NO"` | Window cannot be shrunk smaller than its content |
| `MENU` | `menu_bar` (handle) | Attaches the menu bar to the dialog |

---

## Complete Call Flow Diagram

```
User clicks "Open" button or File > Open menu
    │
    ▼
callback_file_open()
    │
    ├── IupFileDlg() → IupPopup() → user picks a file
    ├── load_bmp(filename)          → reads BMP → creates Image*
    ├── current_image = new_img
    │
    ▼
update_display("Image Opened")
    │
    ├── Destroy old current_iup_img
    ├── Convert current_image pixels → flat RGB array
    ├── IupImageRGB(w, h, rgb)      → create new IUP image
    ├── IupSetHandle("GUI_ACTIVE_IMAGE", iup_img)
    ├── update_status(msg)          → updates status bar text
    │
    ▼
IupUpdate(canvas)                   → marks canvas as dirty
    │
    ▼
[IUP event loop calls canvas_action()]
    │
    ├── IupDrawBegin()
    ├── Clear background (dark rect)
    ├── Calculate scale & center position
    ├── IupDrawImage("GUI_ACTIVE_IMAGE", x, y, w, h)
    ├── IupDrawEnd()
    │
    ▼
Image appears on screen! ✓
```

```
User clicks "Grayscale" (or any filter)
    │
    ▼
callback_grayscale()
    │
    ├── save_undo()                 → clone_image() into prev_image
    ├── grayscale(current_image)    → modifies pixels in-place
    │
    ▼
update_display("Grayscale Filter")
    │
    └── (same pipeline as above — rebuild IUP image, repaint canvas)
```

```
User clicks "Undo"
    │
    ▼
callback_undo()
    │
    ├── undo()                      → swap current_image ← prev_image
    │
    ▼
update_display("Undo Action")
    │
    └── (same pipeline)
```
