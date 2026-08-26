# IUP Toolkit — Learn by Example (from gui.c)

This guide teaches you IUP by explaining **every IUP function used in our Image Editor**, with standalone examples you can copy, compile, and run. By the end, you will understand how IUP works well enough to build your own GUI applications.

---

## Table of Contents

1. [What is IUP?](#1-what-is-iup)
2. [The IUP Lifecycle](#2-the-iup-lifecycle)
3. [Core Concepts](#3-core-concepts)
4. [Element Creation Functions](#4-element-creation-functions)
   - [IupDialog](#41-iupdialog)
   - [IupCanvas](#42-iupcanvas)
   - [IupLabel](#43-iuplabel)
   - [IupButton](#44-iupbutton)
   - [IupMenu, IupSubmenu, IupItem, IupSeparator](#45-menus)
   - [IupHbox, IupVbox](#46-layout-containers)
   - [IupFill](#47-iupfill)
   - [IupFileDlg](#48-iupfiledlg)
5. [Attribute Functions](#5-attribute-functions)
   - [IupSetAttribute vs IupSetStrAttribute](#51-iupsetattribute-vs-iupsetstrattribute)
   - [IupGetAttribute, IupGetInt](#52-iupgetattribute-iupgetint)
   - [IupSetAttributeHandle, IupGetAttributeHandle](#53-iupsetattributehandle)
6. [Callback Functions](#6-callback-functions)
   - [IupSetCallback](#61-iupsetcallback)
   - [Return Values (IUP_DEFAULT, IUP_CLOSE)](#62-return-values)
7. [Named Handles](#7-named-handles)
   - [IupSetHandle, IupGetHandle](#71-iupsethandle)
8. [Image Functions](#8-image-functions)
   - [IupImageRGB](#81-iupimagergb)
9. [Canvas Draw API (iupdraw.h)](#9-canvas-draw-api)
   - [IupDrawBegin / IupDrawEnd](#91-iupdrawbegin--iupdrawend)
   - [IupDrawGetSize](#92-iupdrawgetsize)
   - [IupDrawRectangle](#93-iupdrawrectangle)
   - [IupDrawImage](#94-iupdrawimage)
   - [IupDrawText](#95-iupdrawtext)
   - [IupDrawGetTextSize](#96-iupdrawgettextsize)
10. [Dialog Functions](#10-dialog-functions)
    - [IupPopup, IupShowXY](#101-iuppopup-iupshowxy)
    - [IupMessage](#102-iupmessage)
    - [IupGetParam](#103-iupgetparam)
11. [Lifecycle Functions](#11-lifecycle-functions)
    - [IupUpdate, IupRefresh](#111-iupupdate-iuprefresh)
    - [IupDestroy](#112-iupdestroy)
12. [Common Attributes Reference Table](#12-common-attributes-reference-table)
13. [Minimal Complete Examples](#13-minimal-complete-examples)

---

## 1. What is IUP?

**IUP** (Portable User Interface) is a C library for building cross-platform GUIs. It maps to **native** controls on each OS:
- **Windows**: Win32 API (buttons are real Win32 buttons)
- **Linux**: GTK
- **macOS**: Cocoa

**Key philosophy**: You describe your UI as a **tree of elements**, set **attributes** (strings like `"TITLE"`, `"EXPAND"`) on them, and register **callbacks** (function pointers) for events.

### Headers you need

```c
#include <iup.h>       // Core: dialogs, buttons, labels, menus, etc.
#include <iupdraw.h>   // Canvas drawing: rectangles, images, text
```

### Linking

```
-liup -lgdi32 -lcomdlg32 -lcomctl32 -luuid -loleaut32 -lole32 -luxtheme
```

---

## 2. The IUP Lifecycle

Every IUP program follows this exact pattern:

```c
#include <iup.h>

int main(int argc, char **argv) {
    // 1. Initialize IUP (must be first)
    IupOpen(&argc, &argv);

    // 2. Create your UI elements
    Ihandle *btn = IupButton("Click Me", NULL);
    Ihandle *dlg = IupDialog(btn);

    // 3. Show the main dialog
    IupShowXY(dlg, IUP_CENTER, IUP_CENTER);

    // 4. Run the event loop (BLOCKS here until window is closed)
    IupMainLoop();

    // 5. Cleanup
    IupClose();
    return 0;
}
```

### What `IupMainLoop()` does

```
IupMainLoop()
    │
    ├── Wait for user input (mouse click, key press, resize, etc.)
    ├── Find the corresponding callback function
    ├── Call the callback
    ├── If callback returns IUP_CLOSE → exit the loop
    └── Otherwise → go back to waiting
```

**This is the core of every GUI app.** The program "lives" inside `IupMainLoop()`.

---

## 3. Core Concepts

### 3.1 `Ihandle*` — The Universal Type

Every IUP element (button, label, dialog, canvas, menu item, image) is represented as `Ihandle*`. You never see the internals — you interact with it through functions:

```c
Ihandle *btn = IupButton("OK", NULL);    // Create a button
IupSetAttribute(btn, "TIP", "Click!");   // Set a tooltip
IupSetCallback(btn, "ACTION", my_cb);    // Set click handler
```

### 3.2 Attributes — How You Configure Everything

IUP uses **string-based attributes** instead of setter functions. Every element has dozens of attributes you can set/get:

```c
IupSetAttribute(element, "ATTRIBUTE_NAME", "value");
char *val = IupGetAttribute(element, "ATTRIBUTE_NAME");
```

Common attributes:

| Attribute | Applies To | Values | Meaning |
|-----------|-----------|--------|---------|
| `TITLE` | Dialog, Label, Button, Item | Any string | The text shown |
| `EXPAND` | Any | `YES`, `NO`, `HORIZONTAL`, `VERTICAL` | Whether element grows to fill space |
| `TIP` | Any | Any string | Tooltip on hover |
| `RASTERSIZE` | Dialog | `"WxH"` e.g. `"900x700"` | Size in pixels |
| `GAP` | Hbox, Vbox | Number string | Spacing between children |
| `MARGIN` | Hbox, Vbox | `"WxH"` | Padding around children |
| `PADDING` | Label, Button | `"WxH"` | Internal padding |

### 3.3 Callbacks — How You Handle Events

```c
// Your callback function
int my_button_clicked(Ihandle *self) {
    IupMessage("Hello", "Button was clicked!");
    return IUP_DEFAULT;
}

// Register it
IupSetCallback(btn, "ACTION", (Icallback)my_button_clicked);
```

The **`(Icallback)` cast** is needed because IUP defines callbacks as `int (*)(Ihandle*)`, but some callbacks have different signatures (like canvas ACTION which receives `float posx, float posy`).

---

## 4. Element Creation Functions

### 4.1 `IupDialog`

```c
Ihandle* IupDialog(Ihandle *child);
```

Creates the **main application window**. Takes exactly **one child** element (usually a layout container like `IupVbox`).

```c
// Used in gui.c:
Ihandle *dialog = IupDialog(vbox);
IupSetAttribute(dialog, "TITLE", "CSE 1101 — Image Manipulation Software");
IupSetAttribute(dialog, "RASTERSIZE", "900x700");
IupSetAttributeHandle(dialog, "MENU", menu_bar);
```

**Key attributes:**

| Attribute | Example | Meaning |
|-----------|---------|---------|
| `TITLE` | `"My App"` | Window title bar text |
| `RASTERSIZE` | `"900x700"` | Initial size in pixels |
| `SIZE` | `"HALFxHALF"` | Size relative to screen |
| `SHRINK` | `"NO"` | Prevent shrinking below content size |
| `MENU` | (handle) | Attach a menu bar |

---

### 4.2 `IupCanvas`

```c
Ihandle* IupCanvas(const char *action_name);
```

Creates a **blank drawing surface**. You draw on it using the `iupdraw.h` functions inside the `ACTION` callback.

```c
// Used in gui.c:
canvas = IupCanvas(NULL);
IupSetAttribute(canvas, "EXPAND", "YES");
IupSetCallback(canvas, "ACTION", (Icallback)(void*)canvas_action);
```

**Why not IupLabel for images?**

On Windows, `IupLabel` creates a Win32 Static Control. When initialized with text, it gets the `SS_LEFT` style and **silently ignores image assignments**. `IupCanvas` gives you full control over rendering.

**ACTION callback signature for Canvas:**
```c
int canvas_action(Ihandle *ih, float posx, float posy);
```

- `posx`, `posy` — scroll bar positions (unused in our app)
- Called whenever the canvas needs to be redrawn (resize, uncover, `IupUpdate()`)

---

### 4.3 `IupLabel`

```c
Ihandle* IupLabel(const char *title);
```

Creates a static text label. We use it for the status bar:

```c
// Used in gui.c:
status_bar = IupLabel(" Ready. Please open a 24-bit BMP image.");
IupSetAttribute(status_bar, "EXPAND", "HORIZONTAL");
IupSetAttribute(status_bar, "PADDING", "6x4");
```

---

### 4.4 `IupButton`

```c
Ihandle* IupButton(const char *title, const char *action_name);
```

Creates a clickable button. `action_name` is legacy — always pass `NULL` and use `IupSetCallback` instead.

```c
// Used in gui.c:
Ihandle *btn_open = IupButton("Open", NULL);
IupSetAttribute(btn_open, "TIP", "Open a BMP image file (Ctrl+O)");
IupSetCallback(btn_open, "ACTION", (Icallback)callback_file_open);
```

---

### 4.5 Menus

Menus are built from four element types:

```c
Ihandle* IupMenu(Ihandle *child, ...);      // Container for menu items
Ihandle* IupSubmenu(const char *title, Ihandle *menu);  // Dropdown entry
Ihandle* IupItem(const char *title, const char *action); // Clickable item
Ihandle* IupSeparator(void);                 // Horizontal line divider
```

**Building a menu bar (from gui.c):**

```c
// Individual items with keyboard shortcuts
Ihandle *item_open = IupItem("Open\tCtrl+O", NULL);
Ihandle *item_save = IupItem("Save As...\tCtrl+S", NULL);
Ihandle *item_exit = IupItem("Exit\tAlt+F4", NULL);

// Group items into a menu
Ihandle *menu_file = IupMenu(
    item_open,
    item_save,
    IupSeparator(),    // Adds a horizontal divider line
    item_exit,
    NULL               // Must end with NULL!
);

// Create the menu bar with submenus
Ihandle *menu_bar = IupMenu(
    IupSubmenu("File", menu_file),
    IupSubmenu("Edit", menu_edit),
    IupSubmenu("Image", menu_filters),
    NULL
);

// Attach menu bar to the dialog
IupSetAttributeHandle(dialog, "MENU", menu_bar);
```

**Shortcut syntax:** The `\t` in `"Open\tCtrl+O"` displays the shortcut text on the right side of the menu item. Note: IUP does NOT automatically bind keyboard shortcuts — this is just display text. You would need `K_ANY` or `K_cO` callbacks for actual keyboard binding.

---

### 4.6 Layout Containers

```c
Ihandle* IupHbox(Ihandle *child, ...);   // Horizontal: children left → right
Ihandle* IupVbox(Ihandle *child, ...);   // Vertical: children top → bottom
```

These are **invisible containers** that control how children are arranged.

```c
// Used in gui.c — vertical layout:
Ihandle *vbox = IupVbox(
    toolbar,        // Top: toolbar buttons
    canvas,         // Middle: drawing canvas (EXPAND=YES → takes all space)
    status_bar,     // Bottom: status label
    NULL
);
```

**Important attributes:**

```c
IupSetAttribute(toolbar, "GAP", "6");       // 6 pixels between each child
IupSetAttribute(toolbar, "MARGIN", "6x4");  // 6px horizontal, 4px vertical padding
```

**Visual representation:**

```
┌─────────── IupVbox ──────────────┐
│ ┌────── IupHbox (toolbar) ─────┐ │
│ │ [Open] [Save] [Undo] ... ... │ │  ← GAP=6 between buttons
│ └──────────────────────────────┘ │
│ ┌────── IupCanvas ─────────────┐ │
│ │                              │ │  ← EXPAND=YES (fills all space)
│ │        (image here)          │ │
│ │                              │ │
│ └──────────────────────────────┘ │
│ ┌────── IupLabel (status) ─────┐ │
│ │  File: lena.bmp | 512x512    │ │  ← EXPAND=HORIZONTAL
│ └──────────────────────────────┘ │
└──────────────────────────────────┘
```

---

### 4.7 `IupFill`

```c
Ihandle* IupFill(void);
```

An **invisible spring** that pushes elements apart. In an `IupHbox`, it expands horizontally to consume all remaining space.

```c
// Used in gui.c toolbar:
Ihandle *toolbar = IupHbox(
    btn_open, btn_save, btn_undo,
    IupFill(),         // ← This spring pushes filter buttons to the right
    btn_gray, btn_bright, btn_invert, /* ... */
    NULL
);
```

**Result:**
```
[Open] [Save] [Undo]          [Gray] [Bright] [Invert] [H-Flip] ...
^--- left-aligned ---^  (gap)  ^------- right-aligned --------^
                      ↑
                   IupFill()
```

---

### 4.8 `IupFileDlg`

```c
Ihandle* IupFileDlg(void);
```

Creates a native **file open/save dialog** (the standard Windows file picker).

```c
// Used in gui.c:
Ihandle *file_dlg = IupFileDlg();
IupSetAttribute(file_dlg, "DIALOGTYPE", "OPEN");          // or "SAVE"
IupSetAttribute(file_dlg, "TITLE", "Open BMP Image");
IupSetAttribute(file_dlg, "EXTFILTER",
    "BMP Images (*.bmp)|*.bmp|All Files (*.*)|*.*|");

IupPopup(file_dlg, IUP_CENTER, IUP_CENTER);               // Show dialog (modal)

if (IupGetInt(file_dlg, "STATUS") != -1) {                 // -1 = cancelled
    const char *filename = IupGetAttribute(file_dlg, "VALUE");
    // ... use filename ...
}

IupDestroy(file_dlg);   // Always destroy after use
```

**STATUS values:**
| Value | Meaning |
|-------|---------|
| `0`   | File exists (Open) or new file (Save) |
| `1`   | New file selected |
| `-1`  | User cancelled the dialog |

**EXTFILTER format:**
```
"Description|*.ext|Description2|*.ext2|"
```
Each pair is: `display text | glob pattern`, separated by `|`. Must end with `|`.

---

## 5. Attribute Functions

### 5.1 `IupSetAttribute` vs `IupSetStrAttribute`

```c
void IupSetAttribute(Ihandle *ih, const char *name, const char *value);
void IupSetStrAttribute(Ihandle *ih, const char *name, const char *value);
```

**Critical difference:**
- `IupSetAttribute()` stores the **pointer** you pass. The string must remain valid (use with string literals or globally allocated strings).
- `IupSetStrAttribute()` makes an **internal copy** of the string. Safe to use with local variables.

```c
// SAFE — string literal lives forever:
IupSetAttribute(label, "TITLE", "Hello World");

// DANGEROUS — buf is on the stack, pointer becomes dangling:
char buf[100];
snprintf(buf, 100, "Size: %d x %d", w, h);
IupSetAttribute(label, "TITLE", buf);    // ❌ BUG! buf gets freed when function returns

// SAFE — IUP copies the string:
IupSetStrAttribute(label, "TITLE", buf); // ✅ Correct!
```

**Rule of thumb:** If the value comes from a variable, use `IupSetStrAttribute`. If it's a literal string (`"..."`) or a constant, `IupSetAttribute` is fine.

---

### 5.2 `IupGetAttribute`, `IupGetInt`

```c
char* IupGetAttribute(Ihandle *ih, const char *name);  // Returns string
int   IupGetInt(Ihandle *ih, const char *name);         // Returns int
```

```c
// Used in gui.c:
const char *filename = IupGetAttribute(file_dlg, "VALUE");  // File path
int status = IupGetInt(file_dlg, "STATUS");                  // -1, 0, or 1
```

---

### 5.3 `IupSetAttributeHandle`

```c
void     IupSetAttributeHandle(Ihandle *ih, const char *name, Ihandle *ih_named);
Ihandle* IupGetAttributeHandle(Ihandle *ih, const char *name);
```

Used when an attribute needs to reference **another IUP element** (not a string). The most common use is attaching a menu to a dialog:

```c
// Used in gui.c:
IupSetAttributeHandle(dialog, "MENU", menu_bar);
```

This tells IUP: "The MENU attribute of this dialog is the menu_bar element." Internally, IUP creates a temporary name for `menu_bar` and sets the attribute to that name.

---

## 6. Callback Functions

### 6.1 `IupSetCallback`

```c
Icallback IupSetCallback(Ihandle *ih, const char *name, Icallback func);
```

Registers a function to be called when an event occurs.

```c
// Used in gui.c:
IupSetCallback(btn_open, "ACTION", (Icallback)callback_file_open);
```

**Common callback names:**

| Name | Triggered When | Signature |
|------|---------------|-----------|
| `"ACTION"` (button) | Button is clicked | `int cb(Ihandle *self)` |
| `"ACTION"` (menu item) | Menu item is clicked | `int cb(Ihandle *self)` |
| `"ACTION"` (canvas) | Canvas needs to be redrawn | `int cb(Ihandle *ih, float posx, float posy)` |

### 6.2 Return Values

Every callback must return an `int`:

| Return Value | Meaning |
|-------------|---------|
| `IUP_DEFAULT` | Normal — continue processing events |
| `IUP_CLOSE` | Close the application (exit `IupMainLoop()`) |
| `IUP_IGNORE` | Cancel the operation |

```c
static int callback_exit(Ihandle *self) {
    (void)self;
    return IUP_CLOSE;     // This tells IupMainLoop() to stop
}

static int callback_grayscale(Ihandle *self) {
    (void)self;
    // ... do work ...
    return IUP_DEFAULT;   // Keep the app running
}
```

---

## 7. Named Handles

### 7.1 `IupSetHandle` / `IupGetHandle`

```c
Ihandle* IupSetHandle(const char *name, Ihandle *ih);
Ihandle* IupGetHandle(const char *name);
```

IUP maintains a **global name → handle dictionary**. You can register any element with a string name, then retrieve it later by that name.

**Why we need this:** `IupDrawImage()` takes an image **by name**, not by pointer:

```c
// Used in gui.c:

// Register: "GUI_ACTIVE_IMAGE" → current_iup_img
IupSetHandle("GUI_ACTIVE_IMAGE", current_iup_img);

// Later, in canvas_action():
IupDrawImage(ih, "GUI_ACTIVE_IMAGE", x, y, w, h);  // Finds image by name

// Unregister (before destroying):
IupSetHandle("GUI_ACTIVE_IMAGE", NULL);
IupDestroy(current_iup_img);
```

**Important:** Always unregister (`IupSetHandle(name, NULL)`) before calling `IupDestroy()`. Otherwise IUP's name table holds a dangling pointer.

---

## 8. Image Functions

### 8.1 `IupImageRGB`

```c
Ihandle* IupImageRGB(int width, int height, const unsigned char *pixels);
```

Creates an IUP image from a flat RGB byte array. The array must be `width × height × 3` bytes, in row-major order: `R₁G₁B₁R₂G₂B₂...`

**IUP copies the pixel data**, so you can `free()` the array after calling this function.

```c
// Used in gui.c:
unsigned char *rgb = malloc(width * height * 3);

for (int i = 0; i < width * height; i++) {
    rgb[i * 3 + 0] = current_image->data[i].r;   // Red
    rgb[i * 3 + 1] = current_image->data[i].g;   // Green
    rgb[i * 3 + 2] = current_image->data[i].b;   // Blue
}

current_iup_img = IupImageRGB(width, height, rgb);
free(rgb);   // Safe — IUP made its own copy
```

**Pixel order:** Row 0 is the **top** of the image. This matches screen coordinates (y=0 is the top).

**Related functions:**
- `IupImage(w, h, pixels)` — 1 byte per pixel (indexed color, needs palette)
- `IupImageRGB(w, h, pixels)` — 3 bytes per pixel (24-bit color)
- `IupImageRGBA(w, h, pixels)` — 4 bytes per pixel (32-bit with alpha transparency)

---

## 9. Canvas Draw API

All these functions are declared in `<iupdraw.h>` and must be called **inside the canvas ACTION callback**, between `IupDrawBegin()` and `IupDrawEnd()`.

### 9.1 `IupDrawBegin` / `IupDrawEnd`

```c
void IupDrawBegin(Ihandle *ih);
void IupDrawEnd(Ihandle *ih);
```

**Bracket all drawing operations.** No drawing outside these calls.

```c
static int canvas_action(Ihandle *ih, float posx, float posy) {
    IupDrawBegin(ih);

    // ... all drawing code here ...

    IupDrawEnd(ih);
    return IUP_DEFAULT;
}
```

Think of it like opening and closing a file: `Begin` = open for writing, `End` = flush and close.

---

### 9.2 `IupDrawGetSize`

```c
void IupDrawGetSize(Ihandle *ih, int *w, int *h);
```

Gets the current canvas size in pixels. **Essential** because the canvas changes size when the user resizes the window.

```c
int cw = 0, ch = 0;
IupDrawGetSize(ih, &cw, &ch);
// cw = canvas width, ch = canvas height
```

---

### 9.3 `IupDrawRectangle`

```c
void IupDrawRectangle(Ihandle *ih, int x1, int y1, int x2, int y2);
```

Draws a rectangle. The color and style are controlled by attributes:

```c
// Filled dark background
IupSetAttribute(ih, "DRAWCOLOR", "30 33 39");   // RGB as space-separated string
IupSetAttribute(ih, "DRAWSTYLE", "FILL");        // "FILL" or "STROKE"
IupDrawRectangle(ih, 0, 0, cw, ch);

// Outline border around the image
IupSetAttribute(ih, "DRAWCOLOR", "18 20 24");
IupSetAttribute(ih, "DRAWSTYLE", "STROKE");      // Only draws the border
IupDrawRectangle(ih, x - 1, y - 1, x + w, y + h);
```

**DRAWCOLOR format:** `"R G B"` — three integers 0-255, separated by spaces.

**DRAWSTYLE values:**
| Value | Meaning |
|-------|---------|
| `"FILL"` | Solid filled shape |
| `"STROKE"` | Outline only |

---

### 9.4 `IupDrawImage`

```c
void IupDrawImage(Ihandle *ih, const char *name, int x, int y, int w, int h);
```

Draws a previously registered image onto the canvas.

```c
// Used in gui.c:
IupDrawImage(ih, "GUI_ACTIVE_IMAGE", x, y, draw_w, draw_h);
```

- `name` — The string name registered with `IupSetHandle()`
- `x, y` — Top-left corner position on the canvas
- `w, h` — Drawing size (IUP will scale the image if different from original size)

**Scaling:** If `draw_w` and `draw_h` differ from the original image dimensions, IUP scales automatically. In gui.c, we compute the scale factor ourselves to maintain aspect ratio.

---

### 9.5 `IupDrawText`

```c
void IupDrawText(Ihandle *ih, const char *text, int len, int x, int y, int w, int h);
```

Draws text on the canvas. Color is controlled by `DRAWCOLOR`.

```c
// Used in gui.c (empty-state placeholder):
IupSetAttribute(ih, "DRAWCOLOR", "225 228 234");
IupDrawText(ih, "CSE 1101 — Image Manipulation Software", 0, tx, ty, tw, th);
```

- `len` — Length of text to draw (pass `0` to use `strlen()` automatically)
- `x, y` — Top-left corner
- `w, h` — Bounding box (usually obtained from `IupDrawGetTextSize`)

---

### 9.6 `IupDrawGetTextSize`

```c
void IupDrawGetTextSize(Ihandle *ih, const char *text, int len, int *w, int *h);
```

Measures how many pixels a string would occupy when drawn. Essential for **centering text**.

```c
// Used in gui.c:
int tw = 0, th = 0;
IupDrawGetTextSize(ih, title, 0, &tw, &th);
int tx = (canvas_width - tw) / 2;   // Center horizontally
int ty = (canvas_height - th) / 2;  // Center vertically
```

---

## 10. Dialog Functions

### 10.1 `IupPopup` / `IupShowXY`

```c
int IupPopup(Ihandle *ih, int x, int y);   // Modal (blocks until closed)
int IupShowXY(Ihandle *ih, int x, int y);  // Non-modal (returns immediately)
```

**Modal vs Non-Modal:**
- `IupPopup()` — Used for file dialogs, message boxes. The function **blocks** until the user closes the popup.
- `IupShowXY()` — Used for the main window. Returns immediately; the event loop handles the rest.

```c
// Used in gui.c:
IupShowXY(dialog, IUP_CENTER, IUP_CENTER);   // Main window (from main.c)
IupPopup(file_dlg, IUP_CENTER, IUP_CENTER);  // File dialog (blocks)
```

**Position constants:**
| Constant | Meaning |
|----------|---------|
| `IUP_CENTER` | Center on screen |
| `IUP_LEFT` | Left edge |
| `IUP_RIGHT` | Right edge |
| `IUP_CURRENT` | Keep current position |

---

### 10.2 `IupMessage`

```c
void IupMessage(const char *title, const char *message);
```

Shows a **modal message box** with an OK button. Blocks until user clicks OK.

```c
// Used in gui.c:
IupMessage("Error", "No image loaded.");
IupMessage("Success", "Image saved successfully!");
IupMessage("Error", "Failed to load BMP image.\nPlease make sure it is 24-bit.");
```

---

### 10.3 `IupGetParam`

```c
int IupGetParam(const char *title, Iparamcb action, void *user_data,
                const char *format, ...);
```

Shows a **parameter input dialog** — a form with labeled input fields. Returns `1` if user clicked OK, `0` if cancelled.

**Format string syntax** (NOT the same as printf!):

```
"Label text: %i\n"     → Integer input field
"Label text: %r\n"     → Real (float) input field
"Label text: %s\n"     → String input field
"Label text: %b\n"     → Boolean (checkbox)
```

Each `%i` corresponds to **one `int*`** in the variadic argument list. The argument list must end with `NULL`.

**Simple example (brightness):**
```c
int level = 0;
if (!IupGetParam("Adjust Brightness", NULL, NULL,
                 "Brightness (-255 to 255): %i\n",
                 &level, NULL)) {
    return IUP_DEFAULT;   // User cancelled
}
// level now contains the user's input
```

**Multiple fields (crop):**
```c
int x1 = 0, y1 = 0, x2 = 100, y2 = 100;

// Build format string dynamically to show range hints
char fmt[256];
snprintf(fmt, sizeof(fmt),
    "X1 (Left) [0,%d]: %%i\n"       // %%i becomes %i after snprintf
    "Y1 (Top) [0,%d]: %%i\n"
    "X2 (Right) [0,%d]: %%i\n"
    "Y2 (Bottom) [0,%d]: %%i\n",
    max_x, max_y, max_x, max_y);

if (!IupGetParam("Crop", NULL, NULL, fmt,
                 &x1, &y1, &x2, &y2, NULL)) {
    return IUP_DEFAULT;
}
```

> **⚠️ Common Trap:** Do NOT put extra `%i` or `%d` in the format string for display purposes. Every `%i` creates an input field and expects a pointer. Extra ones will cause a **segmentation fault** by reading stack garbage as pointers.

---

## 11. Lifecycle Functions

### 11.1 `IupUpdate` / `IupRefresh`

```c
void IupUpdate(Ihandle *ih);    // Mark element for redraw (next event cycle)
void IupRefresh(Ihandle *ih);   // Recalculate layout and redraw immediately
```

```c
// Used in gui.c:
IupUpdate(canvas);   // "Hey IUP, call canvas_action() on next event cycle"
```

**When to use which:**
- `IupUpdate()` — When content changed (new image, new drawing). Triggers `ACTION` callback.
- `IupRefresh()` — When size/layout changed (element added/removed). Recalculates layout tree.

---

### 11.2 `IupDestroy`

```c
void IupDestroy(Ihandle *ih);
```

Frees an IUP element and all its children. Used for:
- File dialogs after use: `IupDestroy(file_dlg);`
- Old IUP images when creating new ones: `IupDestroy(current_iup_img);`

**Important:** Destroying a dialog also destroys all elements inside it. When `IupClose()` is called, it destroys everything. But images registered with `IupSetHandle()` should be explicitly unregistered first.

---

## 12. Common Attributes Reference Table

| Attribute | Elements | Values | Description |
|-----------|----------|--------|-------------|
| `TITLE` | Dialog, Label, Button, Item | String | Display text |
| `EXPAND` | Any | `YES` / `NO` / `HORIZONTAL` / `VERTICAL` | Growth behavior |
| `TIP` | Any | String | Tooltip on hover |
| `RASTERSIZE` | Dialog | `"WxH"` | Pixel size |
| `SIZE` | Dialog | `"HALFxHALF"` | Screen-relative size |
| `SHRINK` | Dialog | `YES` / `NO` | Allow shrinking below content |
| `GAP` | Hbox, Vbox | Number | Child spacing (pixels) |
| `MARGIN` | Hbox, Vbox | `"WxH"` | Container padding |
| `PADDING` | Label, Button | `"WxH"` | Internal padding |
| `DIALOGTYPE` | FileDlg | `"OPEN"` / `"SAVE"` / `"DIR"` | Dialog mode |
| `EXTFILTER` | FileDlg | `"Desc\|*.ext\|"` | File type filter |
| `STATUS` | FileDlg | `-1` / `0` / `1` | Result after popup |
| `VALUE` | FileDlg, Text | String | Selected file / text content |
| `FILE` | FileDlg | String | Pre-filled filename |
| `DRAWCOLOR` | Canvas | `"R G B"` | Drawing color (0-255 each) |
| `DRAWSTYLE` | Canvas | `"FILL"` / `"STROKE"` | Fill mode |
| `CANVASBOX` | Canvas | `YES` / `NO` | Allow child elements |
| `IMAGE` | Label, Button | Name/Handle | Image to display |
| `MENU` | Dialog | Handle | Menu bar reference |

---

## 13. Minimal Complete Examples

### Example 1: Hello World with a Button

```c
#include <iup.h>

int btn_click(Ihandle *self) {
    (void)self;
    IupMessage("Hello", "You clicked the button!");
    return IUP_DEFAULT;
}

int main(int argc, char **argv) {
    IupOpen(&argc, &argv);

    Ihandle *btn = IupButton("Click Me", NULL);
    IupSetCallback(btn, "ACTION", (Icallback)btn_click);

    Ihandle *dlg = IupDialog(btn);
    IupSetAttribute(dlg, "TITLE", "Hello IUP");
    IupSetAttribute(dlg, "RASTERSIZE", "300x200");

    IupShowXY(dlg, IUP_CENTER, IUP_CENTER);
    IupMainLoop();
    IupClose();
    return 0;
}
```

### Example 2: Canvas Drawing

```c
#include <iup.h>
#include <iupdraw.h>

int my_canvas_action(Ihandle *ih, float posx, float posy) {
    (void)posx; (void)posy;
    IupDrawBegin(ih);

    int w, h;
    IupDrawGetSize(ih, &w, &h);

    // Blue background
    IupSetAttribute(ih, "DRAWCOLOR", "30 60 120");
    IupSetAttribute(ih, "DRAWSTYLE", "FILL");
    IupDrawRectangle(ih, 0, 0, w, h);

    // White text centered
    const char *msg = "Hello Canvas!";
    int tw, th;
    IupDrawGetTextSize(ih, msg, 0, &tw, &th);
    IupSetAttribute(ih, "DRAWCOLOR", "255 255 255");
    IupDrawText(ih, msg, 0, (w-tw)/2, (h-th)/2, tw, th);

    IupDrawEnd(ih);
    return IUP_DEFAULT;
}

int main(int argc, char **argv) {
    IupOpen(&argc, &argv);

    Ihandle *canvas = IupCanvas(NULL);
    IupSetAttribute(canvas, "EXPAND", "YES");
    IupSetCallback(canvas, "ACTION", (Icallback)(void*)my_canvas_action);

    Ihandle *dlg = IupDialog(canvas);
    IupSetAttribute(dlg, "TITLE", "Canvas Demo");
    IupSetAttribute(dlg, "RASTERSIZE", "400x300");

    IupShowXY(dlg, IUP_CENTER, IUP_CENTER);
    IupMainLoop();
    IupClose();
    return 0;
}
```

### Example 3: Menu Bar + File Dialog

```c
#include <iup.h>
#include <stdio.h>

int cb_open(Ihandle *self) {
    (void)self;
    Ihandle *fdlg = IupFileDlg();
    IupSetAttribute(fdlg, "DIALOGTYPE", "OPEN");
    IupSetAttribute(fdlg, "TITLE", "Pick a File");
    IupSetAttribute(fdlg, "EXTFILTER", "All Files|*.*|");
    IupPopup(fdlg, IUP_CENTER, IUP_CENTER);

    if (IupGetInt(fdlg, "STATUS") != -1) {
        printf("Selected: %s\n", IupGetAttribute(fdlg, "VALUE"));
    }
    IupDestroy(fdlg);
    return IUP_DEFAULT;
}

int cb_exit(Ihandle *self) {
    (void)self;
    return IUP_CLOSE;
}

int main(int argc, char **argv) {
    IupOpen(&argc, &argv);

    Ihandle *item_open = IupItem("Open\tCtrl+O", NULL);
    Ihandle *item_exit = IupItem("Exit", NULL);
    IupSetCallback(item_open, "ACTION", (Icallback)cb_open);
    IupSetCallback(item_exit, "ACTION", (Icallback)cb_exit);

    Ihandle *menu = IupMenu(
        IupSubmenu("File", IupMenu(item_open, IupSeparator(), item_exit, NULL)),
        NULL
    );

    Ihandle *lbl = IupLabel("Check the File menu!");
    IupSetAttribute(lbl, "EXPAND", "YES");
    IupSetAttribute(lbl, "ALIGNMENT", "ACENTER:ACENTER");

    Ihandle *dlg = IupDialog(lbl);
    IupSetAttribute(dlg, "TITLE", "Menu Demo");
    IupSetAttribute(dlg, "RASTERSIZE", "400x200");
    IupSetAttributeHandle(dlg, "MENU", menu);

    IupShowXY(dlg, IUP_CENTER, IUP_CENTER);
    IupMainLoop();
    IupClose();
    return 0;
}
```

### Example 4: IupGetParam Input Dialog

```c
#include <iup.h>
#include <stdio.h>

int main(int argc, char **argv) {
    IupOpen(&argc, &argv);

    int age = 20;
    int score = 85;

    if (IupGetParam("Student Info", NULL, NULL,
                    "Age (years): %i\n"
                    "Score (0-100): %i\n",
                    &age, &score, NULL)) {
        char msg[128];
        sprintf(msg, "Age: %d\nScore: %d", age, score);
        IupMessage("Result", msg);
    } else {
        IupMessage("Info", "Cancelled!");
    }

    IupClose();
    return 0;
}
```

---

## Further Reading

- **Official IUP Documentation:** https://www.tecgraf.puc-rio.br/iup/
- **IUP Tutorial:** https://www.tecgraf.puc-rio.br/iup/en/tutorial/tutorial.html
- **Canvas Draw Guide:** https://www.tecgraf.puc-rio.br/iup/en/func/iupdraw.html
- **Attributes Guide:** https://www.tecgraf.puc-rio.br/iup/en/attrib_guide.html
