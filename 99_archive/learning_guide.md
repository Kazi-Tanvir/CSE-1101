# 📚 Image Editor — Complete Learning Guide
### IUP + C | CSE 1101 Lab Project

> This guide will teach you everything you need to **fully understand and rebuild** your Image Manipulation Software from scratch. Follow the phases in order — each one builds on the previous.

---

## Table of Contents

- [Project Overview](#-project-overview)
- [How the Project Works (Big Picture)](#-how-the-project-works-big-picture)
- [Phase 1 — IUP & GUI Setup](#phase-1--iup--gui-setup)
- [Phase 2 — Image Backend](#phase-2--image-backend-load-save-memory)
- [Phase 3 — Image Editing Filters](#phase-3--image-editing-filters)
- [Viva Quick Reference](#-viva-quick-reference)
- [Learning Suggestions](#-learning-suggestions)

---

## 🌐 Project Overview

You built a **desktop image editing application** using:
- **C** — the programming language
- **IUP 3.32** — a cross-platform GUI (Graphical User Interface) toolkit

The software can:
- Load and save 24-bit BMP images
- Apply 8 image filters (grayscale, brightness, invert, flip, rotate, crop, blur, sharpen)
- Undo the last operation
- Display images on a dark-themed canvas

---

## 🗺️ How the Project Works (Big Picture)

Before diving into code, understand the **flow of data** through your application:

```
User clicks "Open"
        │
        ▼
  IUP File Dialog  ──► user selects a .bmp file
        │
        ▼
  load_bmp(filename)   ◄─── image.c
        │  reads binary file → fills Image struct
        ▼
  current_image (global)
        │
        ▼
  update_display()     ◄─── gui.c
        │  converts Image → IupImageRGB → draws on canvas
        ▼
  Canvas shows image on screen


User clicks "Gray" button
        │
        ▼
  callback_grayscale() ◄─── gui.c
        │  1. save_undo()    → clones current_image into prev_image
        │  2. grayscale()    → modifies current_image pixels in-place
        │  3. update_display() → re-renders canvas
        ▼
  Canvas shows grayscale image
```

**File responsibility map:**

| File | Responsibility |
|------|---------------|
| `main.c` | Start IUP, build window, run event loop, clean up |
| `gui.h` | Declare `build_main_gui()` and `cleanup_images()` |
| `gui.c` | Build the entire UI, handle all user events |
| `image.h` | Declare `Pixel`, `Image`, and all image functions |
| `image.c` | BMP loading, saving, memory allocation/deallocation |
| `filter.h` | Declare all filter function signatures |
| `filter.c` | Implement every image manipulation algorithm |
| `ucrt_compat.c` | Fix a linker compatibility issue (explained later) |

---

---

# Phase 1 — IUP & GUI Setup

> **Goal:** Understand how to build a native GUI application in C using IUP.

---

## 1.1 What is IUP?

**IUP** (Portable User Interface) is a GUI library created by **PUC-Rio** (Brazil). It lets you create native Windows, Linux, and macOS windows using C code.

**Why IUP?**
- Works great with C (no C++ required)
- Creates real native OS windows (not fake drawings)
- Lightweight — just link a library, include a header
- Simple, consistent API

**Core Idea:** Everything in IUP is an `Ihandle*` (a pointer to a widget handle). Buttons, labels, dialogs, canvases — they're all handles. You create them, configure them with attributes, connect callbacks to them, and arrange them in containers.

---

## 1.2 IUP Lifecycle (the must-know sequence)

```c
// main.c
int main(int argc, char **argv) {
    IupOpen(&argc, &argv);        // 1. Initialize IUP (must be first)

    Ihandle *dlg = build_main_gui(); // 2. Build your UI

    IupShowXY(dlg, IUP_CENTER, IUP_CENTER); // 3. Show window centered on screen

    IupMainLoop();                // 4. Start event loop (blocks here until window closes)

    cleanup_images();             // 5. Free your C memory (Image* pointers)
    IupClose();                   // 6. Shut down IUP (must be last)
    return EXIT_SUCCESS;
}
```

**The 4-step lifecycle:**
1. `IupOpen()` — initializes IUP's internal state. Always first.
2. Build UI — create widgets, connect callbacks, arrange in containers.
3. `IupShowXY()` — makes the dialog visible on screen.
4. `IupMainLoop()` — the event loop. IUP sits here, waiting for mouse clicks, key presses, etc. and fires your callbacks. This function only returns when the user closes the window.
5. `IupClose()` — frees IUP's internal state. Always last.

> **Viva tip:** Think of `IupMainLoop()` like a `while(true)` loop that says "wait for user input, call the right callback, repeat." This is called **event-driven programming**.

---

## 1.3 Core IUP Concepts

### Handles — `Ihandle*`

Every widget is an `Ihandle*`. You never touch what's inside — IUP manages it.

```c
Ihandle *btn  = IupButton("Click Me", NULL);
Ihandle *lbl  = IupLabel("Hello World");
Ihandle *dlg  = IupDialog(some_container);
```

### Attributes — `IupSetAttribute` / `IupGetAttribute`

Attributes are key-value string pairs that configure widgets:

```c
IupSetAttribute(btn, "TITLE", "New Label");  // Change button text
IupSetAttribute(dlg, "RASTERSIZE", "800x600"); // Set window size
IupSetAttribute(canvas, "EXPAND", "YES");    // Stretch to fill space
```

For non-string values, use helpers:
```c
int val = IupGetInt(dlg, "STATUS");     // get attribute as int
IupSetStrAttribute(lbl, "TITLE", buf);  // set from a char* variable (not a literal)
```

### Containers — arranging widgets

IUP uses box containers to arrange widgets:

```c
// Horizontal box — children side by side left→right
Ihandle *hbox = IupHbox(btn1, btn2, btn3, NULL); // NULL terminates the list

// Vertical box — children stacked top→bottom
Ihandle *vbox = IupVbox(toolbar, canvas, status_bar, NULL);

// IupFill() — a flexible spacer (pushes things to edges)
Ihandle *hbox = IupHbox(btn_open, btn_save, IupFill(), btn_filter1, NULL);
//                      LEFT side                        RIGHT side
```

### Callbacks — responding to events

A **callback** is a C function that IUP calls when an event happens (button click, key press, etc.).

```c
// 1. Define the callback function (must match expected signature)
static int my_button_click(Ihandle *self) {
    (void)self;  // suppress "unused parameter" warning
    IupMessage("Info", "Button was clicked!");
    return IUP_DEFAULT;  // tell IUP to continue processing normally
}

// 2. Register it
IupSetCallback(btn, "ACTION", (Icallback)my_button_click);
```

**Important:** Most callbacks return `IUP_DEFAULT` (= 0). This tells IUP "I handled it, continue normally." Never return garbage values.

---

## 1.4 Code Walkthrough — `gui.h`

```c
#ifndef GUI_H      // Include guard — prevents the header from being included twice
#define GUI_H

#include "image.h"    // gui.c needs Image* and image functions
#include "filter.h"   // gui.c needs filter functions (called from callbacks)
#include <iup.h>      // gui.c needs IUP types like Ihandle*

Ihandle* build_main_gui(void);  // Declares the function that builds the whole window
void cleanup_images(void);      // Declares the cleanup function called at exit

#endif
```

**Include guards (`#ifndef / #define / #endif`):**
Every header file should have one. Without it, if two files both include `gui.h`, the compiler would see the declarations twice and error out. The guard makes the second inclusion a no-op.

---

## 1.5 Code Walkthrough — `gui.c` (Global State)

```c
static Image *current_image = NULL;   // The image currently being displayed/edited
static Image *prev_image    = NULL;   // The image saved for undo (one level)
static Ihandle *canvas      = NULL;   // The drawing canvas widget
static Ihandle *status_bar  = NULL;   // The bottom status label widget
static Ihandle *current_iup_img = NULL; // IUP's internal representation of the image
static const char *IMG_HANDLE_NAME = "GUI_ACTIVE_IMAGE"; // A name key for IUP's image handle registry
static char loaded_filename[260] = "Untitled"; // Current file's name (for status bar)
```

**Why `static`?** The `static` keyword on a global variable means it is **private to this file** (gui.c). Other files cannot access these variables directly. This is good practice — it hides implementation details.

**Why global variables here?** In a GUI application, many different callbacks (grayscale, save, blur, etc.) all need to access the same `current_image`. Globals are a simple solution. A more advanced design would use a "context struct" passed around, but globals are fine for a project this size.

---

## 1.6 Code Walkthrough — Undo System

```c
static void save_undo(void) {
    if (!current_image) return;       // nothing to save
    if (prev_image) {
        free_image(prev_image);       // discard the old undo state
        prev_image = NULL;
    }
    prev_image = clone_image(current_image); // deep-copy current → prev
}

static void undo(void) {
    if (!prev_image) return;          // nothing to undo
    if (current_image) {
        free_image(current_image);    // discard current (about to be replaced)
    }
    current_image = prev_image;       // restore
    prev_image = NULL;                // mark undo slot as empty
}
```

**How it works:** Before every filter operation, `save_undo()` is called. It clones `current_image` into `prev_image`. When the user hits Ctrl+Z, `undo()` swaps them back.

**Limitation:** Only 1 level of undo. To support multiple levels, you'd need a stack of cloned images.

---

## 1.7 Code Walkthrough — `update_status()`

```c
static void update_status(const char *action_msg) {
    if (!status_bar) return;
    if (current_image) {
        char buf[512];
        // snprintf safely builds the string into buf (prevents buffer overflow)
        snprintf(buf, sizeof(buf), " [%s]  File: %s | Dimensions: %d x %d px | 24-bit RGB",
                 action_msg, loaded_filename, current_image->width, current_image->height);
        IupSetStrAttribute(status_bar, "TITLE", buf); // Update label text
    } else {
        IupSetStrAttribute(status_bar, "TITLE", " Ready. Please open a 24-bit BMP image.");
    }
}
```

**Why `IupSetStrAttribute` instead of `IupSetAttribute`?**
`IupSetAttribute(w, "TITLE", buf)` only works with **string literals** (constant strings). When your string is in a variable (`buf`), you MUST use `IupSetStrAttribute`, which copies the string content. Using `IupSetAttribute` with a local variable would result in a dangling pointer bug (the variable's memory is freed after the function returns).

---

## 1.8 Code Walkthrough — `update_display()`

This is the most important function in gui.c. It converts your `Image*` (C struct with pixel data) into something IUP can draw on screen.

```c
static void update_display(const char *action_msg) {
    // Step 1: Destroy old IUP image handle (if any)
    if (current_iup_img) {
        IupSetHandle((char*)IMG_HANDLE_NAME, NULL); // unregister from IUP's name table
        IupDestroy(current_iup_img);                // free IUP's internal memory
        current_iup_img = NULL;
    }

    if (current_image && current_image->data) {
        int width  = current_image->width;
        int height = current_image->height;

        // Step 2: Create a temporary flat RGB byte array (IUP's required format)
        //         IUP wants: [R0,G0,B0, R1,G1,B1, ...] — packed, no padding
        unsigned char *rgb = (unsigned char*)malloc(width * height * 3);
        if (rgb) {
            for (int i = 0; i < (width * height); i++) {
                rgb[i * 3 + 0] = current_image->data[i].r;
                rgb[i * 3 + 1] = current_image->data[i].g;
                rgb[i * 3 + 2] = current_image->data[i].b;
            }
            // Step 3: Create an IUP image from the flat buffer
            current_iup_img = IupImageRGB(width, height, rgb);
            free(rgb); // IupImageRGB copies the data internally, so free this

            if (current_iup_img) {
                // Step 4: Register the image with a name (so canvas_action can find it by name)
                IupSetHandle((char*)IMG_HANDLE_NAME, current_iup_img);
            }
        }
    }

    update_status(action_msg); // Update the status bar text

    if (canvas) {
        IupUpdate(canvas); // Tell IUP to redraw the canvas (triggers canvas_action callback)
    }
}
```

**Key insight:** IUP images are separate from your `Image*`. Your `Image*` is raw C memory with `Pixel` structs. `IupImageRGB` creates IUP's own internal format. After calling `IupImageRGB`, your `rgb` buffer is no longer needed and is freed immediately.

---

## 1.9 Code Walkthrough — `canvas_action()` (Drawing)

This callback fires every time IUP needs to redraw the canvas (on window resize, after `IupUpdate`, etc.).

```c
static int canvas_action(Ihandle *ih, float posx, float posy) {
    (void)posx; (void)posy; // these are scroll positions, unused

    IupDrawBegin(ih);  // start drawing session

    // --- Draw background ---
    int cw = 0, ch = 0;
    IupDrawGetSize(ih, &cw, &ch); // get current canvas size in pixels
    IupSetAttribute(ih, "DRAWCOLOR", "30 33 39"); // dark background color (RGB)
    IupSetAttribute(ih, "DRAWSTYLE", "FILL");
    IupDrawRectangle(ih, 0, 0, cw, ch); // fill entire canvas

    if (current_image && current_iup_img) {
        int iw   = current_image->width;
        int ih_h = current_image->height;

        // --- Calculate scale to fit image in canvas with margins ---
        double scale = 1.0;
        int margin = 20;
        int avail_w = cw - margin * 2;
        int avail_h = ch - margin * 2;
        if (avail_w > 0 && avail_h > 0) {
            if (iw > avail_w || ih_h > avail_h) {
                double sx = (double)avail_w / (double)iw;
                double sy = (double)avail_h / (double)ih_h;
                scale = (sx < sy) ? sx : sy; // use the smaller scale to fit both dimensions
            }
        }

        // --- Calculate drawn size and centered position ---
        int draw_w = (int)(iw * scale);
        int draw_h = (int)(ih_h * scale);
        int x = (cw - draw_w) / 2; // center horizontally
        int y = (ch - draw_h) / 2; // center vertically

        // Draw thin border around image
        IupSetAttribute(ih, "DRAWCOLOR", "18 20 24");
        IupSetAttribute(ih, "DRAWSTYLE", "STROKE");
        IupDrawRectangle(ih, x-1, y-1, x+draw_w, y+draw_h);

        // Draw the image (scaled to draw_w x draw_h, starting at x, y)
        IupDrawImage(ih, IMG_HANDLE_NAME, x, y, draw_w, draw_h);

    } else {
        // No image loaded — draw placeholder text
        IupSetAttribute(ih, "DRAWCOLOR", "225 228 234");
        IupDrawText(ih, "Image Manipulation Software", 0, tx, ty, tw, th);
        // ... (sub-text drawing omitted for brevity)
    }

    IupDrawEnd(ih); // end drawing session, flush to screen
    return IUP_DEFAULT;
}
```

**Important drawing functions:**

| Function | Purpose |
|----------|---------|
| `IupDrawBegin(ih)` | Start a drawing session |
| `IupDrawGetSize(ih, &w, &h)` | Get canvas pixel dimensions |
| `IupDrawRectangle(ih, x1,y1,x2,y2)` | Draw a filled or outlined rectangle |
| `IupDrawImage(ih, name, x, y, w, h)` | Draw a registered image (scaled) |
| `IupDrawText(ih, text, len, x, y, w, h)` | Draw text |
| `IupDrawGetTextSize(ih, text, len, &w, &h)` | Measure text size before drawing |
| `IupDrawEnd(ih)` | Finish the session, display everything |

---

## 1.10 Code Walkthrough — File Open Callback

```c
static int callback_file_open(Ihandle *self) {
    (void)self;  // self is the widget that triggered this — unused

    // Step 1: Create a native file dialog
    Ihandle *file_dlg = IupFileDlg();
    IupSetAttribute(file_dlg, "DIALOGTYPE", "OPEN");    // Open dialog (not Save)
    IupSetAttribute(file_dlg, "TITLE", "Open BMP Image");
    IupSetAttribute(file_dlg, "EXTFILTER", "BMP Images (*.bmp)|*.bmp|All Files (*.*)|*.*|");
    IupPopup(file_dlg, IUP_CENTER, IUP_CENTER); // Show it centered, blocking

    // Step 2: Check if user picked a file (STATUS == -1 means cancelled)
    if (IupGetInt(file_dlg, "STATUS") != -1) {
        const char *filename = IupGetAttribute(file_dlg, "VALUE"); // full path
        if (filename && strlen(filename) > 0) {
            Image *new_img = load_bmp(filename);  // try to load
            if (new_img) {
                // Success: free old images, set new one
                if (current_image) free_image(current_image);
                if (prev_image)   { free_image(prev_image); prev_image = NULL; }
                current_image = new_img;

                // Extract just the filename (not full path) for status bar
                const char *base = strrchr(filename, '\\'); // find last backslash
                if (!base) base = strrchr(filename, '/');   // or forward slash
                if (base) base++; else base = filename;     // skip the slash
                strncpy(loaded_filename, base, sizeof(loaded_filename) - 1);
                loaded_filename[sizeof(loaded_filename) - 1] = '\0'; // null-terminate

                update_display("Image Opened");
            } else {
                IupMessage("Error", "Failed to load BMP image.\n...");
            }
        }
    }

    IupDestroy(file_dlg); // Always destroy dialogs after use
    return IUP_DEFAULT;
}
```

**Why `IupDestroy(file_dlg)` at the end?** File dialogs allocate memory when created with `IupFileDlg()`. You must destroy them manually after use to avoid memory leaks.

**`strrchr(string, char)`** — Finds the *last* occurrence of a character in a string. Used here to extract just the filename from a full path like `C:\Users\me\pics\lena.bmp` → `lena.bmp`.

---

## 1.11 Code Walkthrough — A Typical Filter Callback

All filter callbacks follow the same pattern. Let's look at grayscale:

```c
static int callback_grayscale(Ihandle *self) {
    (void)self;
    if (!current_image) { IupMessage("Error", "No image loaded."); return IUP_DEFAULT; }
    save_undo();                   // 1. Clone current → prev (for undo)
    grayscale(current_image);      // 2. Apply filter in-place
    update_display("Grayscale Filter"); // 3. Re-render canvas + status bar
    return IUP_DEFAULT;
}
```

**The pipeline:**
```
save_undo() → apply_filter() → update_display()
```

Filters that **return a new Image\*** (blur, sharpen, rotate, crop) are slightly different:

```c
static int callback_blur(Ihandle *self) {
    (void)self;
    if (!current_image) { IupMessage("Error", "No image loaded."); return IUP_DEFAULT; }
    save_undo();
    Image *new_img = blur(current_image);   // creates a NEW image
    if (new_img) {
        free_image(current_image);          // discard old one
        current_image = new_img;            // replace with new
        update_display("Blur Filter");
    }
    return IUP_DEFAULT;
}
```

---

## 1.12 Code Walkthrough — `build_main_gui()`

```c
Ihandle* build_main_gui(void) {
    // ── Canvas ──
    canvas = IupCanvas(NULL);
    IupSetAttribute(canvas, "EXPAND", "YES");     // stretch to fill available space
    IupSetAttribute(canvas, "CANVASBOX", "YES");  // enable IupDraw* functions
    IupSetCallback(canvas, "ACTION", (Icallback)(void*)canvas_action); // drawing callback

    // ── Status Bar ──
    status_bar = IupLabel(" Ready...");
    IupSetAttribute(status_bar, "EXPAND", "HORIZONTAL"); // stretch horizontally

    // ── Toolbar Buttons ──
    Ihandle *btn_open = IupButton("Open", NULL);
    // ... (create all buttons)

    // Set tooltips
    IupSetAttribute(btn_open, "TIP", "Open a BMP image file (Ctrl+O)");
    // ...

    // Connect callbacks
    IupSetCallback(btn_open, "ACTION", (Icallback)callback_file_open);
    // ...

    // ── Layout ──
    //   toolbar: [Open][Save][Undo]<spacer>[Gray][Bright]...[Sharp]
    Ihandle *toolbar = IupHbox(
        btn_open, btn_save, btn_undo,
        IupFill(),   // flexible spacer — pushes filter buttons to the right
        btn_gray, btn_bright, ..., btn_sharp,
        NULL
    );
    IupSetAttribute(toolbar, "GAP", "6");      // 6px gap between buttons
    IupSetAttribute(toolbar, "MARGIN", "6x4"); // 6px horizontal, 4px vertical margin

    //   vbox: [toolbar] / [canvas] / [status_bar]
    Ihandle *vbox = IupVbox(toolbar, canvas, status_bar, NULL);

    // ── Dialog (the window) ──
    Ihandle *dialog = IupDialog(vbox);
    IupSetAttribute(dialog, "TITLE", "Image Manipulation Software");
    IupSetAttribute(dialog, "RASTERSIZE", "900x700"); // initial window size

    // ── Keyboard Shortcuts (on the dialog level) ──
    IupSetCallback(dialog, "K_cO", (Icallback)callback_file_open); // Ctrl+O
    IupSetCallback(dialog, "K_cS", (Icallback)callback_file_save); // Ctrl+S
    IupSetCallback(dialog, "K_cZ", (Icallback)callback_undo);      // Ctrl+Z

    return dialog;
}
```

**IUP attribute key names for keyboard shortcuts:**
- `K_cO` = Ctrl+O (c = control, O = letter)
- `K_cS` = Ctrl+S
- `K_cZ` = Ctrl+Z
- `K_F1` = F1 key
These are defined in `iupkey.h`.

---

## 1.13 Code Walkthrough — `cleanup_images()`

```c
void cleanup_images(void) {
    if (current_iup_img) {
        IupSetHandle((char*)IMG_HANDLE_NAME, NULL); // unregister from IUP name table
        IupDestroy(current_iup_img);                // free IUP image memory
        current_iup_img = NULL;
    }
    if (current_image) { free_image(current_image); current_image = NULL; }
    if (prev_image)    { free_image(prev_image);    prev_image    = NULL; }
}
```

Called from `main.c` just before `IupClose()`. Frees all allocated image memory to avoid leaks. The `NULL` assignments after freeing are defensive — they prevent double-free bugs.

---

## 1.14 Code Walkthrough — `ucrt_compat.c`

```c
extern int    __argc;
extern char **__argv;

int    *__imp___argc = &__argc;
char ***__imp___argv = (char ***)&__argv;
```

**What is this?**

When you link against IUP's pre-compiled static library (`libiup.a`), it was compiled expecting certain C runtime symbols. On modern Windows with the Universal CRT (UCRT), these symbols are named differently. IUP's old library looks for `__imp___argc` and `__imp___argv` (import-table style), but UCRT exposes them as `__argc` and `__argv`.

This tiny file creates the `__imp___argc` and `__imp___argv` symbols that the linker needs, pointing them to the standard `__argc` and `__argv` provided by UCRT.

**Short answer for viva:** It's a compatibility shim. The IUP library was compiled against an older C runtime, and this file bridges the naming difference between the old runtime and the modern Windows Universal CRT.

---

## 1.15 Code Walkthrough — `build.bat`

```bat
gcc src\main.c src\programs\gui.c src\programs\image.c src\programs\filter.c src\programs\ucrt_compat.c ^
    -o ImageEditor.exe ^
    -I./src/header -I./include -L./lib ^
    -liup -lgdi32 -lcomdlg32 -lcomctl32 -luuid -loleaut32 -lole32 -luxtheme ^
    -Wall -Wextra
```

| Flag | Meaning |
|------|---------|
| `src\main.c ...` | Source files to compile |
| `-o ImageEditor.exe` | Output executable name |
| `-I./src/header` | Look for your custom headers here |
| `-I./include` | Look for IUP headers (`iup.h`) here |
| `-L./lib` | Look for library files here |
| `-liup` | Link against `lib/libiup.a` |
| `-lgdi32 -lcomdlg32 ...` | Windows system libraries IUP depends on |
| `-Wall -Wextra` | Enable all warnings (good practice) |

**Windows system libraries needed by IUP:**
- `gdi32` — Windows graphics device interface (drawing)
- `comdlg32` — Common dialogs (the file open/save dialog)
- `comctl32` — Common controls (buttons, etc.)
- `uuid`, `ole32`, `oleaut32` — COM/OLE (Windows automation)
- `uxtheme` — Windows visual themes/styles

---

## ✏️ Phase 1 Practice Exercises

### Exercise 1: Minimal IUP Window
Write a complete C program that:
1. Opens a 400×200 IUP window titled "My First Window"
2. Has a `IupLabel` saying "Hello, IUP!"
3. Has a button "Say Hi" that calls `IupMessage("Hi", "Hello from callback!")`

<details>
<summary>Hint</summary>

```c
#include <iup.h>
static int btn_click(Ihandle *self) {
    (void)self;
    IupMessage("Hi", "Hello from callback!");
    return IUP_DEFAULT;
}
int main(int argc, char **argv) {
    IupOpen(&argc, &argv);
    Ihandle *lbl = IupLabel("Hello, IUP!");
    Ihandle *btn = IupButton("Say Hi", NULL);
    IupSetCallback(btn, "ACTION", (Icallback)btn_click);
    Ihandle *vbox = IupVbox(lbl, btn, NULL);
    Ihandle *dlg = IupDialog(vbox);
    IupSetAttribute(dlg, "TITLE", "My First Window");
    IupSetAttribute(dlg, "RASTERSIZE", "400x200");
    IupShowXY(dlg, IUP_CENTER, IUP_CENTER);
    IupMainLoop();
    IupClose();
    return 0;
}
```
</details>

### Exercise 2: Canvas Drawing
Extend Exercise 1: Replace the label with an `IupCanvas`. In the canvas `ACTION` callback, draw:
- A filled red rectangle covering the left half
- A filled blue rectangle covering the right half

### Exercise 3: File Dialog
Add a button "Open File" that opens `IupFileDlg()`. When the user picks a file, update the window title to show the selected filename. If cancelled, do nothing.

---

## 🎙️ Phase 1 Viva Q&A

**Q: What is IUP?**
> IUP (Portable User Interface) is a cross-platform GUI toolkit from PUC-Rio that lets you build native desktop windows using C. It wraps OS-level controls (Win32 on Windows).

**Q: What does `IupMainLoop()` do?**
> It enters the event loop — a loop that waits for user events (clicks, key presses, window resize), calls the appropriate registered callback functions, and repeats. It only returns when the user closes the main window.

**Q: What is a callback function?**
> A function that you write and register with IUP. IUP calls it automatically when a specific event occurs (e.g., button click). You don't call it directly.

**Q: What is event-driven programming?**
> A programming model where the flow of the program is determined by user events (mouse clicks, key presses) rather than sequential execution. The program waits for events and reacts to them via callbacks.

**Q: What is `Ihandle*`?**
> An opaque pointer to an IUP widget (button, label, dialog, canvas, etc.). You use IUP functions to create, configure, and destroy handles — you never access the internal data directly.

**Q: What does `IupSetCallback` do? What are the parameters?**
> It registers a callback function for a widget's event. Parameters: (1) the widget handle, (2) the event name as a string (e.g., `"ACTION"`), (3) the callback function cast to `Icallback`.

**Q: Why does your project need `ucrt_compat.c`?**
> The pre-compiled IUP static library was built against an older Windows C runtime, which exposes `__argc`/`__argv` with import-table names. Modern Windows UCRT uses different names, so this file provides compatibility symbols to bridge the gap.

**Q: What is `IupFill()` and when do you use it?**
> A flexible spacer widget. In an `IupHbox` or `IupVbox`, it expands to fill available space. Used to push widgets to opposite sides (e.g., file buttons on left, filter buttons on right).

**Q: What keyboard shortcut names does IUP use?**
> They follow the pattern `K_cX` where `c` = Ctrl and `X` = the letter. So Ctrl+O = `"K_cO"`. These come from `iupkey.h`.

---

---

# Phase 2 — Image Backend: Load, Save, Memory

> **Goal:** Understand the BMP file format and how images are managed in memory.

---

## 2.1 The Pixel and Image Structs

```c
// image.h

typedef struct {
    unsigned char r;  // Red   channel — value 0 to 255
    unsigned char g;  // Green channel — value 0 to 255
    unsigned char b;  // Blue  channel — value 0 to 255
} Pixel;
```

**Why `unsigned char`?** A `char` is 1 byte. `unsigned char` = 0 to 255. This is the perfect range for a color channel. `signed char` would be -128 to 127, which doesn't match the 0–255 color range.

```c
typedef struct {
    int    width;    // image width in pixels
    int    height;   // image height in pixels
    Pixel *data;     // pointer to a flat 1D array of Pixel structs
} Image;
```

**How is a 2D image stored in 1D memory?**

An image is conceptually a 2D grid, but memory is 1D. We lay rows out sequentially:

```
Row 0: [P(0,0)][P(1,0)][P(2,0)]...
Row 1: [P(0,1)][P(1,2)][P(2,1)]...
...
```

To access pixel at column `x`, row `y`:
```c
int idx = y * width + x;
Pixel p = img->data[idx];
```

This formula is **the most important formula in the entire project.** Every filter uses it.

---

## 2.2 The BMP File Format

BMP is a simple, uncompressed binary image format. This project only handles **24-bit uncompressed BMP**.

**File structure:**

```
[File Header — 14 bytes]
[Info Header — 40 bytes]
[Pixel Data — rows of BGR triples, bottom-up, with padding]
```

### BMPFileHeader (14 bytes)

```c
#pragma pack(push, 1)  // <-- CRITICAL: pack structs tightly, no padding bytes
typedef struct {
    unsigned short bfType;       // 2 bytes — must be 0x4D42 = "BM" (magic number)
    unsigned int   bfSize;       // 4 bytes — total file size in bytes
    unsigned short bfReserved1;  // 2 bytes — always 0
    unsigned short bfReserved2;  // 2 bytes — always 0
    unsigned int   bfOffBits;    // 4 bytes — offset from start of file to pixel data
} BMPFileHeader;                 // Total: 14 bytes
#pragma pack(pop)
```

**Why `#pragma pack(push, 1)`?**
By default, the C compiler adds **padding bytes** between struct fields to align them efficiently in memory. For example, it might pad a `short` to 4 bytes. This is great for performance, but terrible for reading binary files — the file doesn't have those extra bytes. `#pragma pack(1)` tells the compiler: no padding, lay fields out exactly as written. This way, `sizeof(BMPFileHeader)` = exactly 14 bytes, matching the real file.

**The magic number `0x4D42`:**
In ASCII, `0x42` = 'B', `0x4D` = 'M'. So checking `bfType == 0x4D42` verifies the file starts with "BM" — confirming it's a BMP file. This is called a **magic number** or **file signature**.

### BMPInfoHeader (40 bytes)

```c
typedef struct {
    unsigned int   biSize;          // 4 — size of this header (40)
    int            biWidth;         // 4 — image width in pixels
    int            biHeight;        // 4 — image height (positive = bottom-up, negative = top-down)
    unsigned short biPlanes;        // 2 — always 1
    unsigned short biBitCount;      // 2 — bits per pixel (we only support 24)
    unsigned int   biCompression;   // 4 — 0 = uncompressed (BI_RGB)
    unsigned int   biSizeImage;     // 4 — size of pixel data in bytes
    int            biXPelsPerMeter; // 4 — horizontal resolution (ignored)
    int            biYPelsPerMeter; // 4 — vertical resolution (ignored)
    unsigned int   biClrUsed;       // 4 — number of colors in palette (0 = all)
    unsigned int   biClrImportant;  // 4 — important colors (0 = all)
} BMPInfoHeader;                    // Total: 40 bytes
```

### Pixel Data Layout

Each pixel is stored as **3 bytes in BGR order** (not RGB!). This is a quirk of the BMP format.

Rows go from **bottom to top** (when `biHeight > 0`). So row 0 in the file is the bottom of the image.

Each row is padded to a **multiple of 4 bytes**:
```
row_size_in_file = width * 3 (bytes for pixels)
padding = (4 - (width * 3) % 4) % 4  (extra bytes to reach next multiple of 4)
```

Example for width = 5:
- Pixel data per row = 5 × 3 = 15 bytes
- 15 % 4 = 3, so padding = (4 - 3) % 4 = 1 byte
- Total row size in file = 16 bytes

---

## 2.3 Code Walkthrough — `create_image()`

```c
Image *create_image(int width, int height) {
    if (width <= 0 || height <= 0) return NULL; // reject invalid sizes

    Image *img = (Image*)malloc(sizeof(Image)); // allocate the Image struct
    if (!img) return NULL;                      // allocation failed

    img->width  = width;
    img->height = height;

    // calloc allocates AND zero-initializes
    // calloc(count, size) — allocates count * size bytes, all set to 0
    img->data = (Pixel*)calloc(width * height, sizeof(Pixel));

    if (!img->data) {  // pixel buffer allocation failed
        free(img);     // must free img before returning NULL!
        return NULL;
    }
    return img;
}
```

**`malloc` vs `calloc`:**
- `malloc(n)` — allocates `n` bytes, contents are garbage (uninitialized)
- `calloc(count, size)` — allocates `count * size` bytes, all bytes set to `0`

Why `calloc` for pixel data? So all pixels start as black (R=0, G=0, B=0). Better than random garbage colors if the image is only partially written.

**Two-step allocation:** The `Image` struct and the `Pixel` array are separate allocations. You must free both to avoid leaks.

---

## 2.4 Code Walkthrough — `free_image()`

```c
void free_image(Image *img) {
    if (!img) return;         // if NULL, do nothing (defensive)
    if (img->data) {
        free(img->data);      // free the pixel buffer first
        img->data = NULL;     // prevent dangling pointer
    }
    free(img);                // then free the Image struct itself
    // Note: we don't set img = NULL here because img is a local copy of the pointer
    //       The caller is responsible for setting their pointer to NULL
}
```

**Why free `data` before `img`?** If you free `img` first, you lose the pointer to `img->data` and create a memory leak. Always free nested allocations inside-out.

**Why set `img->data = NULL` after freeing?** If some code accidentally calls `free_image()` again on the same pointer, it won't try to double-free `data` (because `data == NULL`, so the `if (img->data)` check skips it). This is defensive coding.

---

## 2.5 Code Walkthrough — `clone_image()`

```c
Image *clone_image(const Image *img) {
    if (!img || !img->data) return NULL;

    Image *copy = create_image(img->width, img->height); // allocate new image
    if (!copy) return NULL;

    // Copy ALL pixel data from img to copy
    memcpy(copy->data, img->data, img->width * img->height * sizeof(Pixel));
    return copy;
}
```

**`memcpy(dest, src, bytes)`** — copies `bytes` bytes from `src` to `dest`. This is a **deep copy** — it copies the actual pixel data, not just a pointer. After cloning, modifying `copy->data` does NOT affect `img->data`.

**Why clone and not just copy the pointer?** If you did `copy->data = img->data`, both structs would point to the same pixel array. Modifying one would change the other, and double-freeing would crash. A deep copy is a truly independent duplicate.

---

## 2.6 Code Walkthrough — `load_bmp()`

```c
Image *load_bmp(const char *filename) {
    FILE *file = fopen(filename, "rb"); // "rb" = read binary
    if (!file) return NULL;

    // Read and validate file header
    BMPFileHeader header;
    fread(&header, sizeof(BMPFileHeader), 1, file);
    if (header.bfType != 0x4D42) { // check "BM" magic number
        fclose(file);
        return NULL;  // not a BMP file
    }

    // Read and validate info header
    BMPInfoHeader info_header;
    fread(&info_header, sizeof(BMPInfoHeader), 1, file);
    if (info_header.biBitCount != 24 || info_header.biCompression != 0) {
        fclose(file);
        return NULL;  // we only support 24-bit uncompressed
    }

    int width  = info_header.biWidth;
    int height = info_header.biHeight;

    // Handle top-down images (negative height means top-down row order)
    int is_top_down = 0;
    if (height < 0) {
        height = -height;   // make positive
        is_top_down = 1;    // remember we need to flip reading order
    }

    Image *img = create_image(width, height);
    if (!img) { fclose(file); return NULL; }

    int padding = (4 - (width * 3) % 4) % 4; // bytes of padding per row

    fseek(file, header.bfOffBits, SEEK_SET); // jump to pixel data (skip any extra header data)

    for (int y = 0; y < height; y++) {
        // For bottom-up (normal): row 0 in file = bottom row of image
        // so we read row 0 into data[height-1], row 1 into data[height-2], etc.
        int target_row = is_top_down ? y : (height - 1 - y);

        for (int x = 0; x < width; x++) {
            unsigned char bgr[3];
            fread(bgr, 1, 3, file);          // read 3 bytes: Blue, Green, Red

            int idx = target_row * width + x;
            img->data[idx].b = bgr[0];       // BMP stores B first
            img->data[idx].g = bgr[1];
            img->data[idx].r = bgr[2];       // R is last in BMP
        }

        if (padding > 0) {
            fseek(file, padding, SEEK_CUR);  // skip padding bytes
        }
    }

    fclose(file);
    return img;
}
```

---

## 2.7 Code Walkthrough — `save_bmp()`

```c
int save_bmp(const char *filename, const Image *img) {
    if (!img || !img->data || !filename) return 0;

    FILE *file = fopen(filename, "wb"); // "wb" = write binary
    if (!file) return 0;

    int width   = img->width;
    int height  = img->height;
    int padding = (4 - (width * 3) % 4) % 4;
    int row_size  = width * 3 + padding;
    int data_size = row_size * height;

    // Build file header
    BMPFileHeader header;
    header.bfType      = 0x4D42;  // "BM"
    header.bfSize      = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + data_size;
    header.bfReserved1 = 0;
    header.bfReserved2 = 0;
    header.bfOffBits   = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader); // 54

    // Build info header
    BMPInfoHeader info_header;
    memset(&info_header, 0, sizeof(BMPInfoHeader)); // zero all fields first
    info_header.biSize      = sizeof(BMPInfoHeader); // 40
    info_header.biWidth     = width;
    info_header.biHeight    = height; // positive = bottom-up (standard)
    info_header.biPlanes    = 1;
    info_header.biBitCount  = 24;
    info_header.biCompression = 0;   // BI_RGB = no compression
    info_header.biSizeImage = data_size;

    fwrite(&header,      sizeof(BMPFileHeader), 1, file);
    fwrite(&info_header, sizeof(BMPInfoHeader), 1, file);

    unsigned char pad_bytes[3] = {0, 0, 0}; // padding is always zeros

    // Write pixel data bottom-up (row height-1 first, then height-2, ... then 0)
    for (int y = height - 1; y >= 0; y--) {
        for (int x = 0; x < width; x++) {
            int idx = y * width + x;
            unsigned char bgr[3];
            bgr[0] = img->data[idx].b; // write B first
            bgr[1] = img->data[idx].g;
            bgr[2] = img->data[idx].r; // write R last
            fwrite(bgr, 1, 3, file);
        }
        if (padding > 0) {
            fwrite(pad_bytes, 1, padding, file);
        }
    }

    fclose(file);
    return 1; // success
}
```

---

## ✏️ Phase 2 Practice Exercises

### Exercise 1: Create a Solid Color BMP
Write a program (no GUI needed — just `main()`) that:
1. Creates a 200×200 Image
2. Sets every pixel to red (R=255, G=0, B=0)
3. Saves it as `red.bmp`
4. Verify by opening the file in an image viewer

### Exercise 2: Load and Inspect
Write a program that:
1. Loads `lena.bmp`
2. Prints its width, height
3. Prints the RGB values of pixel at (100, 100)

### Exercise 3: Gradient Image
Create a 256×1 BMP where each pixel goes from pure red (left) to pure blue (right).
- Pixel at x: R = 255 - x, G = 0, B = x

### Exercise 4: Swap R and B Channels
Write a function that loops through an image and swaps the R and B channel of every pixel. What does a normal photo look like after this? (Answer: it looks like a "blue cast" version — you'll see warm colors look cold.)

---

## 🎙️ Phase 2 Viva Q&A

**Q: What is the BMP file format? Describe its structure.**
> BMP (Bitmap) is a simple uncompressed image format. It has a 14-byte File Header (magic number "BM", file size, data offset), a 40-byte Info Header (width, height, bit depth, compression), followed by raw pixel data. Pixels are stored in BGR order (not RGB), rows go bottom-up, and each row is padded to a multiple of 4 bytes.

**Q: Why does BMP store pixels in BGR order?**
> It's a historical quirk of the Windows GDI (Graphics Device Interface). When BMP was designed, Windows' internal color representation was BGR, so BMP follows that convention.

**Q: What is `#pragma pack(push, 1)` and why is it needed?**
> By default, the compiler adds padding bytes between struct fields for memory alignment, making the struct larger than the actual fields. For binary file I/O, we need the struct to exactly match the file's byte layout with no extra bytes. `#pragma pack(1)` disables padding, making the struct size exactly equal to the sum of its field sizes.

**Q: What is the BMP row padding formula? Why does BMP have padding?**
> `padding = (4 - (width * 3) % 4) % 4`. BMP requires each row of pixel data to be a multiple of 4 bytes. If `width * 3` isn't divisible by 4, zero bytes are added at the end of each row. This is a performance optimization from Windows' original design — memory aligned to 4-byte boundaries is faster to access.

**Q: What is `malloc` vs `calloc`?**
> `malloc(n)` allocates n bytes with uninitialized (garbage) contents. `calloc(count, size)` allocates count×size bytes and zero-initializes all of them. `calloc` is used for pixel data so all pixels start as black (0,0,0).

**Q: Why is `Image->data` a 1D array? How do you access a 2D pixel?**
> Memory is inherently 1D. A 2D image is stored row-by-row in a single contiguous array. To access pixel at column x, row y: `index = y * width + x`.

**Q: What is a deep copy vs shallow copy? Which does `clone_image()` do?**
> A shallow copy just copies the pointer — both copies point to the same data. A deep copy duplicates the actual data — independent copies. `clone_image()` does a deep copy using `memcpy`, so modifying the clone doesn't affect the original.

**Q: What is `fopen("file", "rb")` and why "rb"?**
> Opens a file for reading in binary mode. The `b` flag is important on Windows — without it, reading `\r\n` (Windows line endings) would translate to `\n`, corrupting binary data. Binary mode reads bytes exactly as-is.

**Q: What does `fseek(file, offset, SEEK_SET)` do?**
> Moves the file position to `offset` bytes from the beginning of the file (SEEK_SET). Used in `load_bmp` to jump directly to the pixel data at `bfOffBits` offset.

---

---

# Phase 3 — Image Editing Filters

> **Goal:** Understand the algorithms behind every image manipulation function.

---

## 3.1 Two Types of Filters

| Type | Returns | Examples | Why? |
|------|---------|---------|------|
| **In-place** | `void` | grayscale, brightness, inversion, horizontalFlip, verticalFlip | Modify pixels directly — no need for a new image |
| **New image** | `Image*` | rotate90, crop, blur, sharpen | Need to read from the original while writing to the new image — can't modify in-place |

**Why can't blur be in-place?** When blurring pixel (x, y), you read its neighbors. If you've already modified the neighbors (because they were processed first), your blurred result uses incorrect values. You need the original, unmodified image as your source.

---

## 3.2 The `clamp()` Helper

```c
static inline unsigned char clamp(int val) {
    if (val < 0)   return 0;
    if (val > 255) return 255;
    return (unsigned char)val;
}
```

`static inline` — this function is only visible within filter.c, and the compiler inserts it directly at call sites (like a macro, but type-safe). Used everywhere to keep pixel values in the valid 0–255 range.

**Why is clamping necessary?** Operations like brightness add a value to each channel. If a pixel has R=230 and you add +50, result = 280 — which doesn't fit in a `unsigned char`. Clamping keeps it at 255. Without clamping, the value wraps around (overflow), causing strange color artifacts.

---

## 3.3 `grayscale()`

```c
void grayscale(Image *img) {
    if (!img || !img->data) return;

    int total = img->width * img->height;
    for (int i = 0; i < total; i++) {
        unsigned char gray = (unsigned char)(
            0.299 * img->data[i].r +
            0.587 * img->data[i].g +
            0.114 * img->data[i].b
        );
        img->data[i].r = gray;
        img->data[i].g = gray;
        img->data[i].b = gray;
    }
}
```

**The luminance formula:** `Gray = 0.299R + 0.587G + 0.114B`

These weights are not equal because the human eye is more sensitive to green (~59%) than red (~30%) and blue (~11%). Using these weights produces a grayscale image that looks natural to us. Using equal weights (0.333 each) produces a technically correct but visually "off" grayscale.

**Why set R, G, B all to the same `gray` value?** A grayscale pixel has equal R, G, and B. The value represents luminance (brightness). Setting all three channels equal creates a neutral gray.

---

## 3.4 `brightness()`

```c
void brightness(Image *img, int brightness) {
    if (!img || !img->data) return;

    int total = img->width * img->height;
    for (int i = 0; i < total; i++) {
        img->data[i].r = clamp(img->data[i].r + brightness);
        img->data[i].g = clamp(img->data[i].g + brightness);
        img->data[i].b = clamp(img->data[i].b + brightness);
    }
}
```

**How it works:** Add the `brightness` value to each channel. Positive values brighten (approach 255). Negative values darken (approach 0). `clamp()` prevents overflow/underflow.

Simple, but effective. No math beyond addition.

---

## 3.5 `inversion()`

```c
void inversion(Image *img) {
    if (!img || !img->data) return;

    int total = img->width * img->height;
    for (int i = 0; i < total; i++) {
        img->data[i].r = 255 - img->data[i].r;
        img->data[i].g = 255 - img->data[i].g;
        img->data[i].b = 255 - img->data[i].b;
    }
}
```

**How it works:** Subtract each channel from 255. This finds the complementary color:
- White (255,255,255) → Black (0,0,0)
- Red (255,0,0) → Cyan (0,255,255)
- Yellow (255,255,0) → Blue (0,0,255)

This is also called the "negative" effect — like a photographic negative.

---

## 3.6 `horizontalFlip()` — Mirror Left↔Right

```c
void horizontalFlip(Image *img) {
    if (!img || !img->data) return;

    for (int y = 0; y < img->height; y++) {
        for (int x = 0; x < img->width / 2; x++) {
            int left  = y * img->width + x;
            int right = y * img->width + (img->width - 1 - x);

            Pixel temp        = img->data[left];   // standard swap
            img->data[left]   = img->data[right];
            img->data[right]  = temp;
        }
    }
}
```

**How it works:** For each row `y`, swap pixel at column `x` with pixel at column `(width-1-x)`. Only iterate through the first half of the row (`x < width/2`) to avoid swapping back to the original.

```
Before: [A][B][C][D][E]
         0  1  2  3  4
Swap x=0 ↔ x=4:  [E][B][C][D][A]
Swap x=1 ↔ x=3:  [E][D][C][B][A]
x=2 is the center — stop here (width/2 = 2)
After:  [E][D][C][B][A]  ✓ mirrored
```

---

## 3.7 `verticalFlip()` — Flip Upside Down

```c
void verticalFlip(Image *img) {
    if (!img || !img->data) return;

    for (int y = 0; y < img->height / 2; y++) {
        for (int x = 0; x < img->width; x++) {
            int top    = y * img->width + x;
            int bottom = (img->height - 1 - y) * img->width + x;

            Pixel temp         = img->data[top];
            img->data[top]     = img->data[bottom];
            img->data[bottom]  = temp;
        }
    }
}
```

**How it works:** Same logic as horizontal flip, but swap rows instead of columns. Swap row `y` with row `(height-1-y)`. Only process the first half of rows (`y < height/2`).

---

## 3.8 `rotate90()` — 90° Clockwise Rotation

```c
Image *rotate90(const Image *img) {
    if (!img || !img->data) return NULL;

    // New image has SWAPPED dimensions: original (W×H) → rotated (H×W)
    Image *rotated = create_image(img->height, img->width);
    if (!rotated) return NULL;

    for (int y = 0; y < img->height; y++) {
        for (int x = 0; x < img->width; x++) {
            int srcIdx = y * img->width + x;
            // Rotation formula for 90° CW:
            //   new_x = (height - 1 - y)
            //   new_y = x
            int dstIdx = x * img->height + (img->height - 1 - y);
            //             ↑ new_y      ↑ new_x
            // (using new width = img->height in the formula: new_y * new_width + new_x)

            rotated->data[dstIdx] = img->data[srcIdx];
        }
    }
    return rotated;
}
```

**The rotation formula (90° CW):**

For a pixel at `(x, y)` in the original image:
- In the rotated image: `new_x = (height - 1 - y)`, `new_y = x`

Think of it geometrically:
- Top-left (0, 0) → goes to top-right: (height-1, 0) ✓
- Top-right (width-1, 0) → goes to bottom-right: (height-1, width-1) ✓

The **destination index** uses the new image's dimensions:
```
new_width  = original height
new_height = original width
dst_idx = new_y * new_width + new_x
        = x    * img->height + (img->height - 1 - y)
```

**Why must this return a new image?** Because the dimensions change (W×H → H×W). You can't resize an array in-place.

---

## 3.9 `crop()`

```c
Image *crop(const Image *img, int x1, int y1, int x2, int y2) {
    if (!img || !img->data) return NULL;

    // Clamp coordinates to image boundaries
    if (x1 < 0)          x1 = 0;
    if (y1 < 0)          y1 = 0;
    if (x2 >= img->width)  x2 = img->width - 1;
    if (y2 >= img->height) y2 = img->height - 1;

    if (x1 > x2 || y1 > y2) return NULL; // invalid region

    // New image size = crop region size
    Image *cropped = create_image(x2 - x1 + 1, y2 - y1 + 1); // +1 because inclusive
    if (!cropped) return NULL;

    for (int y = y1; y <= y2; y++) {
        for (int x = x1; x <= x2; x++) {
            int imgIndex     = y * img->width + x;           // source index
            int croppedIndex = (y - y1) * cropped->width + (x - x1); // dest index (offset by y1, x1)
            cropped->data[croppedIndex] = img->data[imgIndex];
        }
    }
    return cropped;
}
```

**How it works:** Copy a rectangular sub-region `(x1,y1) to (x2,y2)` from the source image into a new smaller image. The destination index subtracts the top-left corner offset `(x1, y1)` so the crop starts at `(0,0)` in the new image.

---

## 3.10 `blur()` — 3×3 Box Blur

```c
Image *blur(const Image *img) {
    if (!img || !img->data) return NULL;

    Image *blured = create_image(img->width, img->height);
    if (!blured) return NULL;

    for (int y = 0; y < img->height; y++) {
        for (int x = 0; x < img->width; x++) {
            int r_sum = 0, g_sum = 0, b_sum = 0;
            int count = 0;

            // Sample the 3×3 neighborhood centered at (x, y)
            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    int nx = x + dx;
                    int ny = y + dy;

                    // Only include neighbors that are within the image
                    if (nx >= 0 && nx < img->width && ny >= 0 && ny < img->height) {
                        int idx = ny * img->width + nx;
                        r_sum += img->data[idx].r;
                        g_sum += img->data[idx].g;
                        b_sum += img->data[idx].b;
                        count++;
                    }
                }
            }

            int idx = y * img->width + x;
            blured->data[idx].r = clamp(r_sum / count);
            blured->data[idx].g = clamp(g_sum / count);
            blured->data[idx].b = clamp(b_sum / count);
        }
    }
    return blured;
}
```

**How it works:** For every pixel, average the colors of its 3×3 neighborhood (up to 9 pixels). This smooths out abrupt color changes, creating a blurred effect.

**Boundary handling:** Edge pixels have fewer neighbors. Instead of using out-of-bounds pixels (which would crash or give garbage), the code only includes in-bounds neighbors. The `count` variable tracks how many valid neighbors were found, so the average is still correct (for corner pixels with only 4 valid neighbors, count=4).

**Why use a new image?** If we blurred in-place, pixel (1,0) would be modified before pixel (2,0) reads it as a neighbor. The blur would use already-blurred values instead of original values, creating an incorrect result.

---

## 3.11 `sharpen()` — Convolution with Sharpening Kernel

```c
Image *sharpen(const Image *img) {
    if (!img || !img->data) return NULL;

    Image *sharpened = create_image(img->width, img->height);
    if (!sharpened) return NULL;

    // The sharpening kernel
    int kernel[3][3] = {
        { 0, -1,  0},
        {-1,  5, -1},
        { 0, -1,  0}
    };

    for (int y = 0; y < img->height; y++) {
        for (int x = 0; x < img->width; x++) {
            // Skip border pixels — copy them unchanged
            if (y == 0 || y == img->height-1 || x == 0 || x == img->width-1) {
                int idx = y * img->width + x;
                sharpened->data[idx] = img->data[idx];
                continue;
            }

            int r_sum = 0, g_sum = 0, b_sum = 0;

            // Apply the kernel to the 3×3 neighborhood
            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    int nx = x + dx;
                    int ny = y + dy;
                    int idx = ny * img->width + nx;
                    int k   = kernel[dy+1][dx+1]; // kernel index: dy+1 and dx+1 shift -1..1 to 0..2

                    r_sum += img->data[idx].r * k;
                    g_sum += img->data[idx].g * k;
                    b_sum += img->data[idx].b * k;
                }
            }

            int idx = y * img->width + x;
            sharpened->data[idx].r = clamp(r_sum);
            sharpened->data[idx].g = clamp(g_sum);
            sharpened->data[idx].b = clamp(b_sum);
        }
    }
    return sharpened;
}
```

**What is a convolution kernel?**

A **kernel** (also called a filter matrix) is a small 2D grid of numbers (weights). To process a pixel, you multiply each kernel weight by the corresponding neighbor pixel's value and sum everything up:

```
Kernel:          Neighborhood at (x,y):
[ 0  -1   0]    [P(x-1,y-1)  P(x,y-1)  P(x+1,y-1)]
[-1   5  -1]  × [P(x-1,y)    P(x,y)    P(x+1,y)  ]
[ 0  -1   0]    [P(x-1,y+1)  P(x,y+1)  P(x+1,y+1)]

Result = (0 × top_left) + (-1 × top) + (0 × top_right) +
         (-1 × left) + (5 × center) + (-1 × right) +
         (0 × bottom_left) + (-1 × bottom) + (0 × bottom_right)
       = 5 × center - top - bottom - left - right
```

**Intuition:** The center pixel is amplified (×5), and its neighbors are subtracted (×-1). This increases contrast between adjacent pixels → enhances edges → sharpening effect.

**Kernel sum = 5 + 4×(-1) + 4×0 = 5 - 4 = 1** — uniform areas stay the same brightness.

**Why copy border pixels unchanged?** The kernel needs a 3×3 neighborhood, but border pixels don't have one full neighborhood. Rather than handle partial kernels (like blur does), this simpler approach just copies edge pixels as-is.

**Why this returns a new Image\*:** Same reason as blur — can't modify source pixels while reading neighbors.

---

## ✏️ Phase 3 Practice Exercises

### Exercise 1: Sepia Tone Filter
Implement a sepia tone filter (gives an old photograph look):
```
newR = clamp(0.393*R + 0.769*G + 0.189*B)
newG = clamp(0.349*R + 0.686*G + 0.168*B)
newB = clamp(0.272*R + 0.534*G + 0.131*B)
```
Note: Use the original R, G, B values (not the already-modified ones) to compute all three.

### Exercise 2: 180° Rotation
Implement a `rotate180()` function **without writing new code** — just call two existing functions. Which two? Hint: Think geometrically.

<details>
<summary>Answer</summary>
Call `horizontalFlip()` then `verticalFlip()` (or vice versa). A horizontal flip + vertical flip = 180° rotation.
</details>

### Exercise 3: Edge Detection
Implement edge detection using this kernel:
```
int kernel[3][3] = {{-1,-1,-1},{-1,8,-1},{-1,-1,-1}};
```
This highlights edges. Apply the result and clamp. What does the output look like on lena.bmp?

### Exercise 4: Threshold / Binary Filter
Implement a binary (black & white) filter:
1. First convert to grayscale
2. Then set each pixel to white (255,255,255) if its gray value > 128, else black (0,0,0)

---

## 🎙️ Phase 3 Viva Q&A

**Q: What is the difference between in-place and new-image filters?**
> In-place filters modify the image directly (void return). New-image filters create a fresh image and return a pointer (Image* return). New images are needed when reading neighbors (blur, sharpen — to avoid using already-modified values) or when the image dimensions change (rotate, crop).

**Q: What is the grayscale luminance formula? Why aren't the weights equal?**
> `Gray = 0.299R + 0.587G + 0.114B`. The human eye is most sensitive to green, then red, then blue. Equal weights would produce an inaccurate brightness perception. These weights match human visual sensitivity.

**Q: What is clamping and why is it necessary?**
> Keeping a value within a valid range (0–255 for pixels). Without clamping, arithmetic like adding brightness could overflow `unsigned char` (wrapping 256→0), causing incorrect colors. Clamping ensures results stay valid.

**Q: What is a convolution kernel?**
> A small matrix of weights applied to a pixel and its neighbors. For each pixel, multiply each neighbor by the corresponding kernel weight and sum the products. Different kernels produce different effects: averaging weights = blur; amplifying center, subtracting neighbors = sharpen; detecting differences = edge detection.

**Q: Explain the blur algorithm.**
> For each pixel, compute the average color of its 3×3 neighborhood. For border pixels with fewer than 9 neighbors, only average the valid neighbors (tracked by `count`). Store the result in a new image.

**Q: Explain the sharpen algorithm.**
> Apply the kernel `{{0,-1,0},{-1,5,-1},{0,-1,0}}` to each pixel's 3×3 neighborhood. This multiplies the center pixel by 5 and subtracts each of the 4 direct neighbors, amplifying color differences between adjacent pixels and enhancing edges.

**Q: Why does `rotate90` create a new image instead of modifying in-place?**
> Because the image dimensions change from W×H to H×W. You cannot resize a dynamically allocated array in-place. A new image with swapped dimensions must be created.

**Q: Explain the rotation coordinate formula.**
> For 90° CW rotation: a pixel at (x, y) in the original maps to position (height-1-y, x) in the rotated image. The destination index in the new array is: `new_y * new_width + new_x = x * original_height + (original_height - 1 - y)`.

**Q: What happens at the boundary pixels in the sharpen filter?**
> Border pixels (first/last row and column) don't have a full 3×3 neighborhood, so they can't be properly convolved. In this implementation, they are copied unchanged from the original image.

**Q: What is the 2D-to-1D pixel index formula?**
> `index = y * width + x`. This converts a 2D (x, y) coordinate into a 1D array index, where rows are laid out sequentially in memory.

---

---

# 🎙️ Viva Quick Reference

## Key Terms

| Term | Definition |
|------|-----------|
| **IUP** | Cross-platform GUI toolkit for C from PUC-Rio |
| **Ihandle*** | Opaque pointer to any IUP widget |
| **Callback** | Function called by IUP when an event occurs |
| **Event loop** | Loop in `IupMainLoop()` that waits for and dispatches user events |
| **BMP** | Bitmap image format — simple uncompressed binary image |
| **Magic number** | `0x4D42` ("BM") — identifies a file as BMP |
| **BGR** | Blue-Green-Red byte order used in BMP (reversed from RGB) |
| **Row padding** | Zero bytes added to each BMP row to make its size a multiple of 4 |
| **Pixel** | One color point: R, G, B each 0–255 |
| **malloc** | Allocate uninitialized memory on the heap |
| **calloc** | Allocate zero-initialized memory on the heap |
| **free** | Release heap-allocated memory |
| **deep copy** | Duplicate data itself (not just the pointer) |
| **clamp** | Restrict a value to a range (0–255 for pixels) |
| **convolution** | Applying a kernel matrix to an image neighborhood |
| **in-place** | Modifying the original data directly |
| **Luminance** | Perceived brightness, weighted `0.299R + 0.587G + 0.114B` |

## Key Formulas

| Formula | Used in |
|---------|--------|
| `idx = y * width + x` | Accessing any pixel in all functions |
| `padding = (4 - (width * 3) % 4) % 4` | BMP load/save row padding |
| `gray = 0.299R + 0.587G + 0.114B` | grayscale() |
| `255 - channel` | inversion() |
| `clamp(channel + brightness)` | brightness() |
| Swap left `x` ↔ right `(width-1-x)` | horizontalFlip() |
| Swap top `y` ↔ bottom `(height-1-y)` | verticalFlip() |
| `new_x = (h-1-y), new_y = x` | rotate90() |
| `dst = (y-y1)*crop_w + (x-x1)` | crop() |
| Average 3×3 neighborhood | blur() |
| Kernel `{{0,-1,0},{-1,5,-1},{0,-1,0}}` | sharpen() |

---

# 💡 Learning Suggestions

1. **Build incrementally.** Start with "window opens" → add canvas → add file open → add one filter. Don't write all 1000 lines at once.

2. **Test filters without GUI first.** Write a `main()` that does `load_bmp → apply_filter → save_bmp`. Run it and open the output in Windows Photos to verify. Way faster than debugging through IUP.

3. **Draw the memory layout on paper.** Sketch a 4×3 image. Write out the pixel indices (0 to 11). Trace through `horizontalFlip` manually with pen and paper. This will make every formula crystal-clear.

4. **Inspect a BMP with a hex editor.** Download HxD (free). Open `lena.bmp`. The first two bytes will be `42 4D` (BM). Match bytes 0-13 to `BMPFileHeader` fields. This makes the binary format completely concrete.

5. **Modify before creating.** Before writing your own grayscale, try changing the weights. What does equal-weight grayscale look like? What if you only use green? Experimenting builds intuition.

6. **Understand the callback flow.** Trace a button click all the way: button clicked → IUP fires callback → `save_undo()` → `grayscale()` → `update_display()` → `IupUpdate()` → `canvas_action()` fires → `IupDrawImage()`. Following data through a system is a fundamental skill.

7. **For viva: know WHY, not just WHAT.** "It converts to gray" is weak. "It uses luminance weights because the human eye is more sensitive to green — without them the result looks visually wrong" is strong.
