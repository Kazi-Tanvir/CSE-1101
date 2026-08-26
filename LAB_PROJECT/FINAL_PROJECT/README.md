# 🖼️ CSE 1101: Image Manipulation Software — Complete Development Guide

> A Windows 64-bit, step-by-step guide to building the **Image Manipulation Software** using **C** and the **IUP 3.32 GUI Toolkit**.
> Covers everything from initial IUP setup through final viva preparation.

---

## 📑 Table of Contents

### Part A — Environment Setup ✅ (Completed)
1. [⚙️ Environment & IUP 3.32 Win64 Overview](#️-environment--iup-332-win64-overview)
2. [📁 Workspace & Folder Layout](#-workspace--folder-layout)
3. [🧪 Step-by-Step IUP Verification Test](#-step-by-step-iup-verification-test)
4. [🛠️ Windows 64-bit Linker Flags & UCRT Compatibility Fix](#️-windows-64-bit-linker-flags--ucrt-compatibility-fix)
5. [🚀 Building and Running (PowerShell, Batch, VS Code)](#-building-and-running-powershell-batch-vs-code)

### Part B — Project Implementation Guide 🔨 (Start Here)
6. [🏗️ Project Architecture & Theory](#️-project-architecture--theory)
   - [6.1 — 24-bit BMP File Format (Deep Dive)](#61--24-bit-bmp-file-format-deep-dive)
   - [6.2 — Pixel & Image Structs (Data Model)](#62--pixel--image-structs-data-model)
   - [6.3 — Displaying Images in IUP](#63--displaying-images-in-iup)
7. [📐 Phase 1 — Core Data Layer (`image.h` / `image.c`)](#-phase-1--core-data-layer-imageh--imagec)
   - [Step 1.1 — Define the Header Guards & Includes](#step-11--define-the-header-guards--includes-imageh)
   - [Step 1.2 — Define the Pixel Struct](#step-12--define-the-pixel-struct)
   - [Step 1.3 — Define the Image Struct](#step-13--define-the-image-struct)
   - [Step 1.4 — Declare Function Prototypes](#step-14--declare-function-prototypes)
   - [Step 1.5 — Implement `create_image()`](#step-15--implement-create_image)
   - [Step 1.6 — Implement `free_image()`](#step-16--implement-free_image)
   - [Step 1.7 — Implement `clone_image()`](#step-17--implement-clone_image)
   - [Step 1.8 — Implement `load_bmp()`](#step-18--implement-load_bmp)
   - [Step 1.9 — Implement `save_bmp()`](#step-19--implement-save_bmp)
   - [Step 1.10 — Compile & Test Phase 1](#step-110--compile--test-phase-1)
8. [🎨 Phase 2 — Image Processing Filters (`filter.h` / `filter.c`)](#-phase-2--image-processing-filters-filterh--filterc)
   - [Step 2.1 — Header & Helper: `clamp()`](#step-21--header--helper-clamp)
   - [Step 2.2 — Grayscale](#step-22--grayscale)
   - [Step 2.3 — Brightness Adjustment](#step-23--brightness-adjustment)
   - [Step 2.4 — Image Inversion (Negative)](#step-24--image-inversion-negative)
   - [Step 2.5 — Horizontal Flip](#step-25--horizontal-flip)
   - [Step 2.6 — Vertical Flip](#step-26--vertical-flip)
   - [Step 2.7 — Rotate 90° Clockwise](#step-27--rotate-90-clockwise)
   - [Step 2.8 — Crop](#step-28--crop)
   - [Step 2.9 — 3×3 Box Blur](#step-29--33-box-blur)
   - [Step 2.10 — Undo Feature](#step-210--undo-feature)
   - [Step 2.11 — ⭐ Bonus: Image Sharpening (+5 Marks)](#step-211---bonus-image-sharpening-5-marks)
   - [Step 2.12 — Compile & Test Phase 2](#step-212--compile--test-phase-2)
9. [🖥️ Phase 3 — GUI Layer (`gui.h` / `gui.c`)](#️-phase-3--gui-layer-guih--guic)
   - [Step 3.1 — GUI Header (`gui.h`)](#step-31--gui-header-guih)
   - [Step 3.2 — GUI Global State](#step-32--gui-global-state)
   - [Step 3.3 — Image Display Helper](#step-33--image-display-helper)
   - [Step 3.4 — File Callbacks (Open, Save)](#step-34--file-callbacks-open-save)
   - [Step 3.5 — Filter Callbacks](#step-35--filter-callbacks)
   - [Step 3.6 — Undo Callback](#step-36--undo-callback)
   - [Step 3.7 — Crop Callback (with IUP Input Dialog)](#step-37--crop-callback-with-iup-input-dialog)
   - [Step 3.8 — Brightness Callback (with IUP Input Dialog)](#step-38--brightness-callback-with-iup-input-dialog)
   - [Step 3.9 — Build the Main GUI Layout](#step-39--build-the-main-gui-layout)
10. [🔗 Phase 4 — Wire Everything in `main.c`](#-phase-4--wire-everything-in-mainc)
11. [🔨 Phase 5 — Final Build & Validation](#-phase-5--final-build--validation)
    - [Step 5.1 — Update `build.bat`](#step-51--update-buildbat)
    - [Step 5.2 — Full Compile & Smoke Test Checklist](#step-52--full-compile--smoke-test-checklist)

### Part C — Reference & Exam Prep
12. [📂 Final Modular Source Organization](#-final-modular-source-organization)
13. [📊 Marking Rubric Breakdown (100 + 5 Bonus)](#-marking-rubric-breakdown-100--5-bonus)
14. [🎤 Viva & Demonstration — What You Must Know](#-viva--demonstration--what-you-must-know)
15. [🐛 Common Pitfalls & Debugging Tips](#-common-pitfalls--debugging-tips)

---

<br>

# Part A — Environment Setup ✅

> **You have already completed everything in Part A.**
> These sections are preserved here as reference. Skip to [Part B](#️-project-architecture--theory) to start coding.

---

## ⚙️ Environment & IUP 3.32 Win64 Overview

- **Operating System:** Windows (64-bit)
- **Compiler:** MinGW-w64 GCC (64-bit)
- **IUP Version:** `iup-3.32_Win64_mingw6_lib`
- **Location of IUP Archive:** `archive/iup-3.32_Win64_mingw6_lib`

---

## 📁 Workspace & Folder Layout

Your project directory is structured as follows:

```text
FINAL_PROJECT/
├── include/                     <-- IUP Header files (.h from iup-3.32)
│   ├── iup.h
│   ├── iupcbs.h
│   ├── iupdef.h
│   ├── iupkey.h
│   └── ...
├── lib/                         <-- Windows 64-bit static libraries (.a from iup-3.32)
│   ├── libiup.a
│   ├── libiupimglib.a
│   └── ...
├── src/                         <-- Your C source and header files
│   ├── main.c                  <-- Window creation, IUP initialization, event loop
│   ├── gui.h                   <-- GUI declarations (menus, canvas/label, buttons)
│   ├── gui.c                   <-- GUI implementations and IUP callbacks
│   ├── image.h                 <-- Pixel & Image structs, BMP load/save declarations
│   ├── image.c                 <-- 24-bit BMP parser, memory allocation, free, clone
│   ├── filter.h                <-- Filter and manipulation function prototypes
│   ├── filter.c                <-- Grayscale, Brightness, Invert, Flip, Rotate, Crop, Blur, Sharpen
│   └── ucrt_compat.c           <-- MinGW UCRT compatibility shim for IUP
├── archive/                     <-- Original downloaded packages
│   └── iup-3.32_Win64_mingw6_lib/
├── docs/                        <-- IUP learning examples
│   ├── 01_hello.c
│   └── 02_HW_with_full_btn.c
├── build_test.bat               <-- One-click batch script to compile & run test_iup.c
├── build.bat                    <-- One-click batch script to compile the full Image Editor
├── test_iup.exe                 <-- Verified working test executable
└── README.md
```

> [!NOTE]
> **Source Files vs Folders**:
> Make sure `filter.h`, `image.h`, and `gui.h` in `src/` are **C header files** (e.g. `src/filter.h`, `src/filter.c`), not folders!

---

## 🧪 Step-by-Step IUP Verification Test

We have created and verified a working test file [test_iup.c](file:///d:/02_CODE/05_CSE_1101/LAB_PROJECT/FINAL_PROJECT/test_iup.c) for your Windows 64-bit environment.

### 1. The Verification Code (`test_iup.c`)

```c
#include <stdio.h>
#include <stdlib.h>
#include <iup.h>

/* MinGW UCRT compatibility fix for IUP on Windows 64-bit */
#if defined(_UCRT) || defined(__UCRT__)
int *__imp___argc;
char ***__imp___argv;
__attribute__((constructor)) static void _fix_ucrt_iup(void) {
    __imp___argc = __p___argc();
    __imp___argv = __p___argv();
}
#endif

int btn_click_cb(Ihandle *self) {
    (void)self;
    IupMessage("Success!", "IUP 3.32 (Win64) has been successfully configured and linked!");
    return IUP_DEFAULT;
}

int btn_exit_cb(Ihandle *self) {
    (void)self;
    return IUP_CLOSE;
}

int main(int argc, char **argv) {
    // 1. Initialize IUP
    IupOpen(&argc, &argv);

    // 2. Create UI Elements
    Ihandle *label = IupLabel("CSE 1101: Image Manipulation Software (IUP 3.32 Win64 Test)");
    Ihandle *btn_test = IupButton("Test IUP Dialog", NULL);
    Ihandle *btn_quit = IupButton("Quit", NULL);

    // 3. Attach Callbacks
    IupSetCallback(btn_test, "ACTION", (Icallback)btn_click_cb);
    IupSetCallback(btn_quit, "ACTION", (Icallback)btn_exit_cb);

    // 4. Arrange in a Layout Box
    Ihandle *btn_box = IupHbox(btn_test, btn_quit, NULL);
    IupSetAttribute(btn_box, "GAP", "15");
    IupSetAttribute(btn_box, "ALIGNMENT", "ACENTER");

    Ihandle *vbox = IupVbox(label, btn_box, NULL);
    IupSetAttribute(vbox, "MARGIN", "25x25");
    IupSetAttribute(vbox, "GAP", "15");
    IupSetAttribute(vbox, "ALIGNMENT", "ACENTER");

    // 5. Create Dialog Window
    Ihandle *dlg = IupDialog(vbox);
    IupSetAttribute(dlg, "TITLE", "IUP Test Window");
    IupSetAttribute(dlg, "SIZE", "280x90");

    // 6. Display and run Event Loop
    IupShowXY(dlg, IUP_CENTER, IUP_CENTER);
    IupMainLoop();

    // 7. Cleanup
    IupClose();
    return 0;
}
```

---

## 🛠️ Windows 64-bit Linker Flags & UCRT Compatibility Fix

### 1. Linker Flags for IUP 3.32 on Windows:
To compile on Windows with MinGW-w64, the linker requires:
```text
-I./include -L./lib -liup -lgdi32 -lcomdlg32 -lcomctl32 -luuid -loleaut32 -lole32 -luxtheme
```

| Flag | Purpose |
|---|---|
| `-I./include` | Tells GCC where to find `iup.h` |
| `-L./lib` | Tells GCC where to find `libiup.a` |
| `-liup` | Links the IUP Core GUI library (`libiup.a`) |
| `-lgdi32` | Windows Graphics Device Interface (GDI) |
| `-lcomdlg32` | Windows Common Dialogs (File Open/Save Dialogs) |
| `-lcomctl32` | Windows Common Controls |
| `-luuid` | Windows COM UUID definitions (e.g. `IID_IDropTarget`) |
| `-loleaut32` | OLE Automation 32-bit runtime |
| `-lole32` | Windows OLE32 / COM subsystem |
| `-luxtheme` | Windows Visual Styles & Theming |

### 2. MinGW-w64 UCRT Compatibility Fix (Crucial)
Modern MinGW-w64 compilers (GCC 12+) on Windows use the **Universal C Runtime (UCRT)**. IUP's precompiled `libiup.a` references legacy MSVCRT variables `__argc` and `__argv`. We solved this by creating a dedicated [ucrt_compat.c](file:///d:/02_CODE/05_CSE_1101/LAB_PROJECT/FINAL_PROJECT/src/ucrt_compat.c) file:

```c
/* ucrt_compat.c */
extern int    __argc;
extern char **__argv;

int    *__imp___argc = &__argc;
char ***__imp___argv = (char ***)&__argv;
```

> [!IMPORTANT]
> This file **must always be compiled** alongside your project. It is already included in `build.bat`.

---

## 🚀 Building and Running (PowerShell, Batch, VS Code)

### Method 1: Using the Batch Script (Easiest)
Simply double-click or run [build_test.bat](file:///d:/02_CODE/05_CSE_1101/LAB_PROJECT/FINAL_PROJECT/build_test.bat):
```powershell
.\build_test.bat
```

### Method 2: Direct PowerShell / Command Prompt
```powershell
gcc test_iup.c -o test_iup.exe -I./include -L./lib -liup -lgdi32 -lcomdlg32 -lcomctl32 -luuid -loleaut32 -lole32 -luxtheme
.\test_iup.exe
```

### Method 3: VS Code `tasks.json`
To build with `Ctrl + Shift + B` in VS Code, create `.vscode/tasks.json`:
```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "type": "shell",
            "label": "Build Image Editor (Win64)",
            "command": "gcc",
            "args": [
                "-g",
                "${workspaceFolder}/src/main.c",
                "${workspaceFolder}/src/gui.c",
                "${workspaceFolder}/src/image.c",
                "${workspaceFolder}/src/filter.c",
                "${workspaceFolder}/src/ucrt_compat.c",
                "-I${workspaceFolder}/include",
                "-L${workspaceFolder}/lib",
                "-liup",
                "-lgdi32",
                "-lcomdlg32",
                "-lcomctl32",
                "-luuid",
                "-loleaut32",
                "-lole32",
                "-luxtheme",
                "-o",
                "${workspaceFolder}/ImageEditor.exe"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "problemMatcher": ["$gcc"]
        }
    ]
}
```

---

<br>

# Part B — Project Implementation Guide 🔨

> **Start here.** This is the phase-by-phase guide to build the complete Image Manipulation Software.
> Each phase builds on the previous one. Complete them in order.

---

## 🏗️ Project Architecture & Theory

Before writing code, you need to understand three foundational concepts:
1. How BMP files store pixel data on disk
2. How to represent pixels and images in C memory
3. How IUP displays images on screen

---

### 6.1 — 24-bit BMP File Format (Deep Dive)

A 24-bit uncompressed BMP file has three sections:

```text
┌─────────────────────────────────────────┐
│  BMP File Header (14 bytes)             │  ← Identifies the file as BMP
├─────────────────────────────────────────┤
│  BMP Info Header (40 bytes)             │  ← Image dimensions, bit depth
├─────────────────────────────────────────┤
│  Pixel Data (variable size)             │  ← Raw BGR pixel values + padding
└─────────────────────────────────────────┘
```

#### A. File Header (14 bytes total)

```c
#pragma pack(push, 1)   // ← Prevents compiler padding! Critical for BMP parsing
typedef struct {
    unsigned short bfType;      // Must be 0x4D42 ('BM') — identifies BMP format
    unsigned int   bfSize;      // Total file size in bytes
    unsigned short bfReserved1; // Always 0
    unsigned short bfReserved2; // Always 0
    unsigned int   bfOffBits;   // Byte offset from start of file to pixel data (typically 54)
} BMPFileHeader;
```

#### B. Info Header (40 bytes total)

```c
typedef struct {
    unsigned int   biSize;          // Size of this header = 40
    int            biWidth;         // Image width in pixels
    int            biHeight;        // Image height (positive = bottom-up, negative = top-down)
    unsigned short biPlanes;        // Must be 1
    unsigned short biBitCount;      // Bits per pixel = 24 for our format
    unsigned int   biCompression;   // 0 = BI_RGB (uncompressed)
    unsigned int   biSizeImage;     // Size of raw pixel data (with padding)
    int            biXPelsPerMeter; // 0 (unused)
    int            biYPelsPerMeter; // 0 (unused)
    unsigned int   biClrUsed;       // 0 (unused)
    unsigned int   biClrImportant;  // 0 (unused)
} BMPInfoHeader;
#pragma pack(pop)
```

> [!WARNING]
> **`#pragma pack(push, 1)` is mandatory.** Without it, the compiler may insert padding bytes between struct fields, causing `fread()` to read the wrong byte offsets, corrupting your headers.

#### C. BMP Scanline Padding — The Critical Formula

Each horizontal row in a BMP file **must be a multiple of 4 bytes** wide:

$$\text{padding} = (4 - (\text{width} \times 3) \bmod 4) \bmod 4$$

**Worked example:** If `width = 10`:
- Row bytes = $10 \times 3 = 30$ bytes
- $30 \bmod 4 = 2$
- Padding = $(4 - 2) \bmod 4 = 2$ extra zero-bytes appended to each row

#### D. Two Crucial BMP Quirks

| Quirk | What it means for your code |
|---|---|
| **BGR byte order** | BMP stores pixels as Blue→Green→Red, not RGB. You must swap B↔R when loading/saving. |
| **Bottom-up storage** | The *last* row of the image is stored *first* in the file. Row 0 in the file = bottom row on screen. |

---

### 6.2 — Pixel & Image Structs (Data Model)

Your in-memory representation uses two structs:

```text
Pixel:                              Image:
┌───────┬───────┬───────┐          ┌──────────┐
│  r    │  g    │  b    │          │  width   │
│ (0-255)│(0-255)│(0-255)│          │  height  │
└───────┴───────┴───────┘          │  *data ──┼──→ [Pixel][Pixel][Pixel]...
                                   └──────────┘     (width × height Pixels)
```

> **1D Array Pixel Indexing:**
> A pixel at column `x` and row `y` is accessed as:
> ```c
> img->data[y * img->width + x]
> ```
> This is used **everywhere** — in every filter, in loading, in saving, in display.

---

### 6.3 — Displaying Images in IUP

IUP provides `IupImageRGB(width, height, rgb_buffer)` to create an image handle from a flat `unsigned char` array of `[R, G, B, R, G, B, ...]` values.

**The workflow:**
```text
Image struct (Pixel array)
    │
    ▼
Convert to flat unsigned char[width * height * 3]
    │
    ▼
IupImageRGB() creates an Ihandle* image
    │
    ▼
IupSetAttributeHandle(label, "IMAGE", iup_img) displays it
    │
    ▼
IupRefresh(label) redraws the screen
```

> [!NOTE]
> `IupImageRGB()` makes an **internal copy** of your buffer, so you can safely `free()` the flat array after calling it.

---

<br>

## 📐 Phase 1 — Core Data Layer (`image.h` / `image.c`)

> **Goal:** Create the Pixel/Image structs, BMP read/write, and memory management.
> These are pure C with no IUP dependency — you can test them independently.

---

### Step 1.1 — Define the Header Guards & Includes (`image.h`)

Open `src/image.h` and start with:

```c
/* src/image.h — Pixel & Image data structures, BMP I/O declarations */
#ifndef IMAGE_H
#define IMAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
```

**Why header guards?** They prevent the file from being included twice in the same compilation unit, which would cause "redefinition" errors.

---

### Step 1.2 — Define the Pixel Struct

Add inside `image.h`:

```c
/* A single pixel with Red, Green, Blue channels (0-255 each) */
typedef struct {
    unsigned char r;  // Red channel
    unsigned char g;  // Green channel
    unsigned char b;  // Blue channel
} Pixel;
```

**Why `unsigned char`?** Each color channel is 0–255, which is exactly the range of an `unsigned char` (1 byte).

---

### Step 1.3 — Define the Image Struct

Add inside `image.h`:

```c
/* A complete image: dimensions + dynamically allocated pixel array */
typedef struct {
    int width;    // Image width in pixels
    int height;   // Image height in pixels
    Pixel *data;  // 1D array of (width * height) Pixels, allocated with malloc
} Image;
```

**Why a 1D array instead of `Pixel**` (2D)?**
- Single `malloc()` call = one contiguous memory block
- Better CPU cache performance (pixels are adjacent in memory)
- Simpler deallocation: just one `free(img->data)`
- Access formula: `img->data[y * img->width + x]`

---

### Step 1.4 — Declare Function Prototypes

Add at the bottom of `image.h` before `#endif`:

```c
/* ── Memory Management ─────────────────────────────────── */

/* Allocate a new blank image of the given dimensions.
   Returns NULL on failure. Pixel data is zero-initialized. */
Image* create_image(int width, int height);

/* Free all memory associated with an image. Safe to call with NULL. */
void free_image(Image *img);

/* Create an independent deep copy of src.
   Returns NULL on failure. */
Image* clone_image(const Image *src);

/* ── 24-bit BMP File I/O ──────────────────────────────── */

/* Load a 24-bit uncompressed BMP file into a new Image.
   Returns NULL if the file can't be opened or is not valid 24-bit BMP. */
Image* load_bmp(const char *filename);

/* Save an Image as a 24-bit uncompressed BMP file.
   Returns 1 on success, 0 on failure. */
int save_bmp(const char *filename, const Image *img);

#endif /* IMAGE_H */
```

---

### Step 1.5 — Implement `create_image()`

Open `src/image.c` and start writing the implementations:

```c
/* src/image.c — Image memory management and 24-bit BMP I/O */
#include "image.h"

/* ── BMP Header Structs (packed to match file layout exactly) ── */
#pragma pack(push, 1)
typedef struct {
    unsigned short bfType;
    unsigned int   bfSize;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned int   bfOffBits;
} BMPFileHeader;

typedef struct {
    unsigned int   biSize;
    int            biWidth;
    int            biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned int   biCompression;
    unsigned int   biSizeImage;
    int            biXPelsPerMeter;
    int            biYPelsPerMeter;
    unsigned int   biClrUsed;
    unsigned int   biClrImportant;
} BMPInfoHeader;
#pragma pack(pop)

/* ────────────────────────────────────────────────────────── */
/*                    MEMORY MANAGEMENT                       */
/* ────────────────────────────────────────────────────────── */

Image* create_image(int width, int height) {
    if (width <= 0 || height <= 0) return NULL;

    Image *img = (Image *)malloc(sizeof(Image));
    if (!img) return NULL;

    img->width  = width;
    img->height = height;

    /* calloc zero-initializes the pixel data (all pixels start as black) */
    img->data = (Pixel *)calloc(width * height, sizeof(Pixel));
    if (!img->data) {
        free(img);
        return NULL;
    }

    return img;
}
```

**Key decisions explained:**
- `calloc` instead of `malloc` ensures pixels are initialized to black (all zeros), preventing garbage data display
- We validate width/height > 0 to prevent invalid allocations
- We check each allocation and return `NULL` on failure (defensive programming)

---

### Step 1.6 — Implement `free_image()`

Add below `create_image()`:

```c
void free_image(Image *img) {
    if (!img) return;       // Safe to call with NULL
    if (img->data) {
        free(img->data);    // Free the pixel array first
        img->data = NULL;   // Prevent dangling pointer
    }
    free(img);              // Then free the Image struct itself
}
```

> [!TIP]
> **Always set freed pointers to `NULL`**. This prevents use-after-free bugs and makes double-free safe (since `free(NULL)` is a no-op).

---

### Step 1.7 — Implement `clone_image()`

Add below `free_image()`:

```c
Image* clone_image(const Image *src) {
    if (!src || !src->data) return NULL;

    Image *copy = create_image(src->width, src->height);
    if (!copy) return NULL;

    /* Copy all pixel data in one shot (contiguous memory advantage!) */
    memcpy(copy->data, src->data, src->width * src->height * sizeof(Pixel));
    return copy;
}
```

**Why do we need `clone_image()`?**
- The **Undo** feature needs to save a complete snapshot of the image *before* applying a filter
- Filters like **Rotate** and **Crop** create new images — we need to be able to copy originals
- A shallow copy (`copy = *src`) would share the same `data` pointer, causing double-free bugs

---

### Step 1.8 — Implement `load_bmp()`

This is the most complex function. Add below `clone_image()`:

```c
/* ────────────────────────────────────────────────────────── */
/*                     BMP FILE I/O                           */
/* ────────────────────────────────────────────────────────── */

Image* load_bmp(const char *filename) {
    /* ── Step A: Open the file in binary mode ── */
    FILE *fp = fopen(filename, "rb");   // "rb" = read binary (crucial on Windows!)
    if (!fp) {
        fprintf(stderr, "Error: Cannot open file '%s'\n", filename);
        return NULL;
    }

    /* ── Step B: Read and validate the File Header ── */
    BMPFileHeader fh;
    if (fread(&fh, sizeof(BMPFileHeader), 1, fp) != 1) {
        fprintf(stderr, "Error: Cannot read BMP file header\n");
        fclose(fp);
        return NULL;
    }

    /* Check the magic number: first 2 bytes must be 'B' 'M' (0x4D42) */
    if (fh.bfType != 0x4D42) {
        fprintf(stderr, "Error: Not a valid BMP file (magic number mismatch)\n");
        fclose(fp);
        return NULL;
    }

    /* ── Step C: Read and validate the Info Header ── */
    BMPInfoHeader ih;
    if (fread(&ih, sizeof(BMPInfoHeader), 1, fp) != 1) {
        fprintf(stderr, "Error: Cannot read BMP info header\n");
        fclose(fp);
        return NULL;
    }

    /* We only support 24-bit uncompressed BMP */
    if (ih.biBitCount != 24 || ih.biCompression != 0) {
        fprintf(stderr, "Error: Only 24-bit uncompressed BMP is supported\n");
        fclose(fp);
        return NULL;
    }

    /* ── Step D: Determine image dimensions ── */
    int width  = ih.biWidth;
    int height = ih.biHeight;

    /* Handle both bottom-up (positive height) and top-down (negative height) */
    int is_top_down = 0;
    if (height < 0) {
        height = -height;
        is_top_down = 1;
    }

    /* ── Step E: Create the image in memory ── */
    Image *img = create_image(width, height);
    if (!img) {
        fprintf(stderr, "Error: Memory allocation failed for %dx%d image\n", width, height);
        fclose(fp);
        return NULL;
    }

    /* ── Step F: Calculate padding and read pixel data ── */
    int padding = (4 - (width * 3) % 4) % 4;

    /* Seek to the start of pixel data (skipping any extra header bytes) */
    fseek(fp, fh.bfOffBits, SEEK_SET);

    /* Read row by row */
    for (int y = 0; y < height; y++) {
        /* Determine which row in our Image to write to:
           - Bottom-up BMP (normal): file row 0 = image row (height-1)
           - Top-down BMP:           file row 0 = image row 0 */
        int target_row = is_top_down ? y : (height - 1 - y);

        for (int x = 0; x < width; x++) {
            unsigned char bgr[3];
            if (fread(bgr, 1, 3, fp) != 3) {
                fprintf(stderr, "Error: Unexpected end of pixel data at row %d, col %d\n", y, x);
                free_image(img);
                fclose(fp);
                return NULL;
            }

            /* BMP stores BGR, we store RGB — swap Blue and Red */
            int idx = target_row * width + x;
            img->data[idx].b = bgr[0];   // Blue  → .b
            img->data[idx].g = bgr[1];   // Green → .g
            img->data[idx].r = bgr[2];   // Red   → .r
        }

        /* Skip the padding bytes at the end of each row */
        if (padding > 0) {
            fseek(fp, padding, SEEK_CUR);
        }
    }

    fclose(fp);
    return img;
}
```

> [!IMPORTANT]
> **Critical line:** `FILE *fp = fopen(filename, "rb");` — The `"b"` (binary mode) is **essential on Windows**. Without it, Windows may translate `\r\n` sequences in the binary pixel data, silently corrupting your image.

**Step-by-step explanation of what this function does:**

| Step | What happens | Why |
|------|-------------|-----|
| A | Open file in binary mode | Windows text mode corrupts binary data |
| B | Read 14-byte File Header | Get file size and pixel data offset |
| B✓ | Check `bfType == 0x4D42` | Reject non-BMP files gracefully |
| C | Read 40-byte Info Header | Get width, height, bit depth |
| C✓ | Check `biBitCount == 24` | Reject 8-bit, 32-bit, compressed BMPs |
| D | Handle negative height | Support both bottom-up and top-down BMPs |
| E | `create_image(w, h)` | Allocate pixel array in memory |
| F | Read rows with BGR→RGB swap | Translate from disk format to our struct |
| F✓ | Skip padding bytes per row | BMP rows must be 4-byte aligned |

---

### Step 1.9 — Implement `save_bmp()`

Add below `load_bmp()`:

```c
int save_bmp(const char *filename, const Image *img) {
    if (!img || !img->data || !filename) return 0;

    FILE *fp = fopen(filename, "wb");   // "wb" = write binary
    if (!fp) {
        fprintf(stderr, "Error: Cannot create file '%s'\n", filename);
        return 0;
    }

    int width  = img->width;
    int height = img->height;
    int padding = (4 - (width * 3) % 4) % 4;
    int row_size = width * 3 + padding;
    int data_size = row_size * height;

    /* ── Build the File Header ── */
    BMPFileHeader fh;
    fh.bfType      = 0x4D42;                              // 'BM'
    fh.bfSize       = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + data_size;
    fh.bfReserved1 = 0;
    fh.bfReserved2 = 0;
    fh.bfOffBits   = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);  // = 54

    /* ── Build the Info Header ── */
    BMPInfoHeader ih;
    memset(&ih, 0, sizeof(BMPInfoHeader));  // Zero everything first
    ih.biSize        = sizeof(BMPInfoHeader);  // = 40
    ih.biWidth       = width;
    ih.biHeight      = height;                 // Positive = bottom-up (standard)
    ih.biPlanes      = 1;
    ih.biBitCount    = 24;
    ih.biCompression = 0;                      // BI_RGB (uncompressed)
    ih.biSizeImage   = data_size;

    /* ── Write headers ── */
    fwrite(&fh, sizeof(BMPFileHeader), 1, fp);
    fwrite(&ih, sizeof(BMPInfoHeader), 1, fp);

    /* ── Write pixel data (bottom-up, BGR format) ── */
    unsigned char pad_bytes[3] = {0, 0, 0};   // Up to 3 bytes of padding

    for (int y = height - 1; y >= 0; y--) {   // Bottom row first!
        for (int x = 0; x < width; x++) {
            int idx = y * width + x;
            unsigned char bgr[3];
            bgr[0] = img->data[idx].b;        // RGB → BGR for BMP
            bgr[1] = img->data[idx].g;
            bgr[2] = img->data[idx].r;
            fwrite(bgr, 1, 3, fp);
        }
        /* Write padding bytes */
        if (padding > 0) {
            fwrite(pad_bytes, 1, padding, fp);
        }
    }

    fclose(fp);
    return 1;   // Success
}
```

**Key save logic mirrors load logic:**
- We write the **bottom row first** (standard bottom-up BMP)
- We swap **RGB → BGR** (reverse of what we did in `load_bmp`)
- We append **padding bytes** at the end of each row

---

### Step 1.10 — Compile & Test Phase 1

At this point you can verify that your BMP loading/saving works without any GUI. Create a temporary test:

```c
/* Quick test — add to main.c temporarily, or create a test_image.c */
#include "image.h"
#include <stdio.h>

int main(void) {
    Image *img = load_bmp("test.bmp");          // Use any 24-bit BMP file
    if (!img) {
        printf("FAIL: Could not load test.bmp\n");
        return 1;
    }
    printf("OK: Loaded %dx%d image\n", img->width, img->height);

    /* Test clone */
    Image *copy = clone_image(img);
    printf("OK: Cloned image (%dx%d)\n", copy->width, copy->height);

    /* Test save */
    if (save_bmp("output.bmp", img)) {
        printf("OK: Saved output.bmp\n");
    }

    /* Cleanup */
    free_image(copy);
    free_image(img);
    printf("OK: All memory freed\n");
    return 0;
}
```

Compile with:
```powershell
gcc src/image.c test_main.c -o test_image.exe -Wall -Wextra
.\test_image.exe
```

**✅ Milestone:** If `output.bmp` looks identical to `test.bmp` when opened in any image viewer, Phase 1 is complete.

---

<br>

## 🎨 Phase 2 — Image Processing Filters (`filter.h` / `filter.c`)

> **Goal:** Implement all 9 required image manipulation algorithms + 1 bonus.
> These functions operate on `Image` structs and have **no IUP dependency**.

---

### Step 2.1 — Header & Helper: `clamp()`

Create `src/filter.h`:

```c
/* src/filter.h — Image manipulation filter declarations */
#ifndef FILTER_H
#define FILTER_H

#include "image.h"

/* ── In-place operations (modify the image directly) ──────── */
void apply_grayscale(Image *img);
void apply_brightness(Image *img, int delta);
void apply_inversion(Image *img);
void apply_horizontal_flip(Image *img);
void apply_vertical_flip(Image *img);

/* ── Operations that return a NEW image (caller must free) ── */
Image* apply_rotate_90_cw(const Image *src);
Image* apply_crop(const Image *src, int x1, int y1, int x2, int y2);
Image* apply_blur(const Image *src);
Image* apply_sharpen(const Image *src);    /* Bonus (+5 marks) */

#endif /* FILTER_H */
```

> [!IMPORTANT]
> **Two categories of filters:**
> - **In-place filters** (grayscale, brightness, invert, flip): modify `img->data` directly, no new allocation needed
> - **New-image filters** (rotate, crop, blur, sharpen): return a **new** `Image*` because the output dimensions or logic require a separate buffer. **The caller is responsible for freeing the returned image.**

Now start `src/filter.c`:

```c
/* src/filter.c — Image manipulation filter implementations */
#include "filter.h"

/* Clamp a value to the valid 0–255 range */
static inline unsigned char clamp(int val) {
    if (val < 0)   return 0;
    if (val > 255) return 255;
    return (unsigned char)val;
}
```

**Why `static inline`?**
- `static` limits the function's visibility to this file only (no linker conflicts)
- `inline` hints to the compiler to insert the code directly at call sites, avoiding function-call overhead — important since this is called millions of times (once per channel per pixel)

---

### Step 2.2 — Grayscale

**Formula (ITU-R BT.601 standard):**
$$\text{gray} = 0.299R + 0.587G + 0.114B$$

This formula weights green highest because human eyes are most sensitive to green light.

```c
void apply_grayscale(Image *img) {
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

**How it works:** Setting all three channels (R, G, B) to the same computed luminance value produces a shade of gray.

---

### Step 2.3 — Brightness Adjustment

```c
void apply_brightness(Image *img, int delta) {
    if (!img || !img->data) return;

    int total = img->width * img->height;
    for (int i = 0; i < total; i++) {
        img->data[i].r = clamp(img->data[i].r + delta);
        img->data[i].g = clamp(img->data[i].g + delta);
        img->data[i].b = clamp(img->data[i].b + delta);
    }
}
```

**How it works:**
- `delta > 0` → brighter (adds to each channel, clamped at 255)
- `delta < 0` → darker (subtracts from each channel, clamped at 0)
- `clamp()` prevents overflow (e.g., 250 + 30 → 255, not 280 or wrapping to 24)

---

### Step 2.4 — Image Inversion (Negative)

**Formula:** $R' = 255 - R$, $G' = 255 - G$, $B' = 255 - B$

```c
void apply_inversion(Image *img) {
    if (!img || !img->data) return;

    int total = img->width * img->height;
    for (int i = 0; i < total; i++) {
        img->data[i].r = 255 - img->data[i].r;
        img->data[i].g = 255 - img->data[i].g;
        img->data[i].b = 255 - img->data[i].b;
    }
}
```

**How it works:** Each channel is "flipped" around the midpoint (127.5). White (255) becomes black (0), red becomes cyan, etc. Applying inversion twice restores the original image.

---

### Step 2.5 — Horizontal Flip

Mirrors the image left-to-right:

```c
void apply_horizontal_flip(Image *img) {
    if (!img || !img->data) return;

    for (int y = 0; y < img->height; y++) {
        for (int x = 0; x < img->width / 2; x++) {
            /* Swap pixel at (x, y) with pixel at (width-1-x, y) */
            int left_idx  = y * img->width + x;
            int right_idx = y * img->width + (img->width - 1 - x);

            Pixel temp = img->data[left_idx];
            img->data[left_idx]  = img->data[right_idx];
            img->data[right_idx] = temp;
        }
    }
}
```

**Algorithm:** For each row, swap the leftmost pixel with the rightmost, then the second-leftmost with the second-rightmost, etc. We only iterate to `width / 2` to avoid swapping back.

---

### Step 2.6 — Vertical Flip

Mirrors the image top-to-bottom:

```c
void apply_vertical_flip(Image *img) {
    if (!img || !img->data) return;

    for (int y = 0; y < img->height / 2; y++) {
        for (int x = 0; x < img->width; x++) {
            /* Swap pixel at (x, y) with pixel at (x, height-1-y) */
            int top_idx    = y * img->width + x;
            int bottom_idx = (img->height - 1 - y) * img->width + x;

            Pixel temp = img->data[top_idx];
            img->data[top_idx]    = img->data[bottom_idx];
            img->data[bottom_idx] = temp;
        }
    }
}
```

---

### Step 2.7 — Rotate 90° Clockwise

**This returns a NEW image** because width and height are swapped:

```text
Original (4×3):         Rotated 90° CW (3×4):
A B C D                 I E A
E F G H        →        J F B
I J K L                 K G C
                         L H D
```

```c
Image* apply_rotate_90_cw(const Image *src) {
    if (!src || !src->data) return NULL;

    /* Width and height swap in a 90° rotation */
    Image *dst = create_image(src->height, src->width);
    if (!dst) return NULL;

    for (int y = 0; y < src->height; y++) {
        for (int x = 0; x < src->width; x++) {
            int src_idx = y * src->width + x;

            /* Mapping formula: src(x,y) → dst(height-1-y, x) */
            int dst_x = src->height - 1 - y;
            int dst_y = x;
            int dst_idx = dst_y * dst->width + dst_x;

            dst->data[dst_idx] = src->data[src_idx];
        }
    }
    return dst;
}
```

> [!WARNING]
> **After rotation, you must replace the current image with the returned one and free the old one.** The old image has different dimensions and cannot be reused.

---

### Step 2.8 — Crop

Extracts a rectangular sub-region `(x1, y1)` to `(x2, y2)`:

```c
Image* apply_crop(const Image *src, int x1, int y1, int x2, int y2) {
    if (!src || !src->data) return NULL;

    /* Clamp coordinates to valid range */
    if (x1 < 0) x1 = 0;
    if (y1 < 0) y1 = 0;
    if (x2 >= src->width)  x2 = src->width  - 1;
    if (y2 >= src->height) y2 = src->height - 1;
    if (x1 > x2 || y1 > y2) return NULL;

    int new_w = x2 - x1 + 1;
    int new_h = y2 - y1 + 1;
    Image *dst = create_image(new_w, new_h);
    if (!dst) return NULL;

    for (int y = 0; y < new_h; y++) {
        for (int x = 0; x < new_w; x++) {
            /* Map destination (x, y) back to source (x1+x, y1+y) */
            dst->data[y * new_w + x] = src->data[(y1 + y) * src->width + (x1 + x)];
        }
    }
    return dst;
}
```

---

### Step 2.9 — 3×3 Box Blur

For each pixel, average the RGB values of itself and its 8 neighbors:

```text
Neighborhood:
┌───┬───┬───┐
│NW │ N │NE │    Each neighbor contributes equally.
├───┼───┼───┤    Edge pixels use fewer neighbors
│ W │ C │ E │    (adaptive averaging).
├───┼───┼───┤
│SW │ S │SE │
└───┴───┴───┘
```

```c
Image* apply_blur(const Image *src) {
    if (!src || !src->data) return NULL;

    Image *dst = create_image(src->width, src->height);
    if (!dst) return NULL;

    for (int y = 0; y < src->height; y++) {
        for (int x = 0; x < src->width; x++) {
            int sum_r = 0, sum_g = 0, sum_b = 0, count = 0;

            /* Iterate over the 3×3 neighborhood */
            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    int nx = x + dx;
                    int ny = y + dy;

                    /* Only include pixels within image bounds */
                    if (nx >= 0 && nx < src->width && ny >= 0 && ny < src->height) {
                        int idx = ny * src->width + nx;
                        sum_r += src->data[idx].r;
                        sum_g += src->data[idx].g;
                        sum_b += src->data[idx].b;
                        count++;
                    }
                }
            }

            int dst_idx = y * src->width + x;
            dst->data[dst_idx].r = (unsigned char)(sum_r / count);
            dst->data[dst_idx].g = (unsigned char)(sum_g / count);
            dst->data[dst_idx].b = (unsigned char)(sum_b / count);
        }
    }
    return dst;
}
```

> [!NOTE]
> **Why a separate output image?** If we wrote blurred values back to the source, later pixels would read already-blurred neighbors instead of originals, producing incorrect results. This is why we read from `src` and write to `dst`.

---

### Step 2.10 — Undo Feature

The undo feature saves a **single-level snapshot** of the image before each operation:

```c
/* Note: These are typically called from GUI callbacks, not standalone.
   They manage two Image pointers: the current image and the undo backup.
   Include these in filter.c or in gui.c — wherever you manage the state. */

void save_undo(Image **current, Image **undo) {
    if (*undo) free_image(*undo);    // Discard old undo snapshot
    *undo = clone_image(*current);   // Save current state
}

void apply_undo(Image **current, Image **undo) {
    if (!(*undo)) {
        /* No undo available — you can show an IUP message here */
        return;
    }
    if (*current) free_image(*current);   // Free current image
    *current = *undo;                     // Restore from undo
    *undo = NULL;                         // Undo slot is now empty
}
```

**How the undo pattern works in callbacks:**
```text
User clicks "Grayscale" button
    │
    ▼
save_undo(&current_image, &undo_image)   ← saves current state
    │
    ▼
apply_grayscale(current_image)            ← modifies current
    │
    ▼
update_display()                          ← refresh screen

User clicks "Undo"
    │
    ▼
apply_undo(&current_image, &undo_image)  ← restores saved state
    │
    ▼
update_display()                          ← refresh screen
```

---

### Step 2.11 — ⭐ Bonus: Image Sharpening (+5 Marks)

**Sharpening kernel (Laplacian):**

$$\begin{bmatrix} 0 & -1 & 0 \\ -1 & 5 & -1 \\ 0 & -1 & 0 \end{bmatrix}$$

The center weight (5) amplifies the current pixel, while the negative neighbors subtract surrounding blur, enhancing edges.

```c
Image* apply_sharpen(const Image *src) {
    if (!src || !src->data) return NULL;

    Image *dst = create_image(src->width, src->height);
    if (!dst) return NULL;

    int kernel[3][3] = {
        { 0, -1,  0},
        {-1,  5, -1},
        { 0, -1,  0}
    };

    for (int y = 0; y < src->height; y++) {
        for (int x = 0; x < src->width; x++) {
            /* Boundary pixels: copy unchanged (they don't have full 3×3 neighbors) */
            if (x == 0 || x == src->width - 1 || y == 0 || y == src->height - 1) {
                dst->data[y * src->width + x] = src->data[y * src->width + x];
                continue;
            }

            /* Apply convolution for interior pixels */
            int acc_r = 0, acc_g = 0, acc_b = 0;
            for (int ky = -1; ky <= 1; ky++) {
                for (int kx = -1; kx <= 1; kx++) {
                    int weight = kernel[ky + 1][kx + 1];
                    int idx = (y + ky) * src->width + (x + kx);
                    acc_r += src->data[idx].r * weight;
                    acc_g += src->data[idx].g * weight;
                    acc_b += src->data[idx].b * weight;
                }
            }

            int dst_idx = y * src->width + x;
            dst->data[dst_idx].r = clamp(acc_r);
            dst->data[dst_idx].g = clamp(acc_g);
            dst->data[dst_idx].b = clamp(acc_b);
        }
    }
    return dst;
}
```

---

### Step 2.12 — Compile & Test Phase 2

You can test the filters without IUP by loading a BMP, applying a filter, and saving the result:

```c
/* test_filters.c (temporary test) */
#include "image.h"
#include "filter.h"
#include <stdio.h>

int main(void) {
    Image *img = load_bmp("test.bmp");
    if (!img) return 1;

    /* Test grayscale */
    Image *backup = clone_image(img);
    apply_grayscale(img);
    save_bmp("test_grayscale.bmp", img);
    printf("Saved test_grayscale.bmp\n");

    /* Test inversion on original */
    apply_inversion(backup);
    save_bmp("test_inverted.bmp", backup);
    printf("Saved test_inverted.bmp\n");

    /* Test rotation */
    Image *rotated = apply_rotate_90_cw(backup);
    save_bmp("test_rotated.bmp", rotated);
    printf("Saved test_rotated.bmp\n");

    free_image(img);
    free_image(backup);
    free_image(rotated);
    return 0;
}
```

Compile:
```powershell
gcc src/image.c src/filter.c test_filters.c -o test_filters.exe -Wall -Wextra
.\test_filters.exe
```

**✅ Milestone:** Open each output BMP in an image viewer and visually verify the filter was applied correctly.

---

<br>

## 🖥️ Phase 3 — GUI Layer (`gui.h` / `gui.c`)

> **Goal:** Build the IUP graphical interface with menus, buttons, image display, and connect everything to the filters.

---

### Step 3.1 — GUI Header (`gui.h`)

```c
/* src/gui.h — GUI layout builder and callback declarations */
#ifndef GUI_H
#define GUI_H

#include <iup.h>
#include "image.h"
#include "filter.h"

/* Build the complete GUI and return the main dialog handle.
   The returned Ihandle* should be shown with IupShowXY() in main.c */
Ihandle* build_main_gui(void);

/* Clean up global image state (call before IupClose) */
void cleanup_images(void);

#endif /* GUI_H */
```

---

### Step 3.2 — GUI Global State

Open `src/gui.c` and define the global state:

```c
/* src/gui.c — GUI implementation: layout, callbacks, image display */
#include "gui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ── Global State ─────────────────────────────────────── */
/* These are the two core pointers the entire application revolves around */
static Image *g_current_image = NULL;    // The image currently being displayed/edited
static Image *g_undo_image    = NULL;    // One-level undo backup

/* Handle to the IUP label that displays the image */
static Ihandle *g_img_label = NULL;
```

**Why global (static)?**
- IUP callbacks have a fixed signature `int cb(Ihandle *self)` — you can't pass extra parameters
- `static` limits scope to this file only, preventing name collisions with other files
- This is the standard pattern for IUP applications

---

### Step 3.3 — Image Display Helper

This function converts our `Image` struct into an IUP-displayable image:

```c
/* ── Display Helper ───────────────────────────────────── */
static void update_display(void) {
    if (!g_current_image || !g_current_image->data || !g_img_label) return;

    int w = g_current_image->width;
    int h = g_current_image->height;
    int total = w * h;

    /* Allocate a flat RGB buffer for IUP */
    unsigned char *rgb = (unsigned char *)malloc(total * 3);
    if (!rgb) return;

    for (int i = 0; i < total; i++) {
        rgb[i * 3 + 0] = g_current_image->data[i].r;
        rgb[i * 3 + 1] = g_current_image->data[i].g;
        rgb[i * 3 + 2] = g_current_image->data[i].b;
    }

    /* Create new IUP image */
    Ihandle *new_iup_img = IupImageRGB(w, h, rgb);
    free(rgb);  /* IUP copies the data internally */

    /* Destroy the old image handle to prevent memory leaks */
    Ihandle *old_iup_img = (Ihandle *)IupGetAttributeHandle(g_img_label, "IMAGE");
    if (old_iup_img) {
        IupDestroy(old_iup_img);
    }

    /* Attach new image to the label and refresh */
    IupSetAttributeHandle(g_img_label, "IMAGE", new_iup_img);
    IupSetAttribute(g_img_label, "TITLE", "");  /* Clear placeholder text */
    IupRefresh(g_img_label);
}
```

---

### Step 3.4 — File Callbacks (Open, Save)

```c
/* ── File Callbacks ───────────────────────────────────── */

static int cb_file_open(Ihandle *self) {
    (void)self;

    /* Show a native file-open dialog filtered to BMP files */
    Ihandle *filedlg = IupFileDlg();
    IupSetAttribute(filedlg, "DIALOGTYPE", "OPEN");
    IupSetAttribute(filedlg, "TITLE", "Open BMP Image");
    IupSetAttribute(filedlg, "EXTFILTER", "BMP Files|*.bmp|All Files|*.*|");
    IupPopup(filedlg, IUP_CENTER, IUP_CENTER);

    if (IupGetInt(filedlg, "STATUS") != -1) {  /* -1 = user cancelled */
        const char *filename = IupGetAttribute(filedlg, "VALUE");

        /* Free any existing images */
        if (g_current_image) { free_image(g_current_image); g_current_image = NULL; }
        if (g_undo_image)    { free_image(g_undo_image);    g_undo_image = NULL; }

        g_current_image = load_bmp(filename);
        if (g_current_image) {
            update_display();
        } else {
            IupMessage("Error", "Failed to load BMP file.\nMake sure it is a 24-bit uncompressed BMP.");
        }
    }

    IupDestroy(filedlg);
    return IUP_DEFAULT;
}

static int cb_file_save(Ihandle *self) {
    (void)self;

    if (!g_current_image) {
        IupMessage("Error", "No image loaded to save!");
        return IUP_DEFAULT;
    }

    Ihandle *filedlg = IupFileDlg();
    IupSetAttribute(filedlg, "DIALOGTYPE", "SAVE");
    IupSetAttribute(filedlg, "TITLE", "Save BMP Image");
    IupSetAttribute(filedlg, "EXTFILTER", "BMP Files|*.bmp|All Files|*.*|");
    IupSetAttribute(filedlg, "EXTDEFAULT", "bmp");
    IupPopup(filedlg, IUP_CENTER, IUP_CENTER);

    if (IupGetInt(filedlg, "STATUS") != -1) {
        const char *filename = IupGetAttribute(filedlg, "VALUE");
        if (!save_bmp(filename, g_current_image)) {
            IupMessage("Error", "Failed to save BMP file!");
        } else {
            IupMessage("Success", "Image saved successfully!");
        }
    }

    IupDestroy(filedlg);
    return IUP_DEFAULT;
}
```

> [!NOTE]
> **`IupFileDlg()`** creates a native Windows file dialog (Open/Save). You must call `IupPopup()` to show it, read `STATUS` to check if the user selected a file or cancelled, then `IupDestroy()` to free it.

---

### Step 3.5 — Filter Callbacks

Each filter button gets a callback. They all follow the same pattern:
1. Check if an image is loaded
2. Save undo
3. Apply the filter
4. Update the display

```c
/* ── Filter Callbacks (In-place operations) ───────────── */

/* Helper macro to reduce boilerplate for simple in-place filters */
#define FILTER_CALLBACK_INPLACE(cb_name, filter_func)             \
    static int cb_name(Ihandle *self) {                           \
        (void)self;                                               \
        if (!g_current_image) {                                   \
            IupMessage("Error", "No image loaded!");              \
            return IUP_DEFAULT;                                   \
        }                                                         \
        save_undo(&g_current_image, &g_undo_image);               \
        filter_func(g_current_image);                             \
        update_display();                                         \
        return IUP_DEFAULT;                                       \
    }

FILTER_CALLBACK_INPLACE(cb_grayscale,       apply_grayscale)
FILTER_CALLBACK_INPLACE(cb_inversion,       apply_inversion)
FILTER_CALLBACK_INPLACE(cb_horizontal_flip, apply_horizontal_flip)
FILTER_CALLBACK_INPLACE(cb_vertical_flip,   apply_vertical_flip)

/* ── Filter Callbacks (New-image operations) ──────────── */

/* Helper macro for filters that return a new image */
#define FILTER_CALLBACK_NEW_IMAGE(cb_name, filter_func)           \
    static int cb_name(Ihandle *self) {                           \
        (void)self;                                               \
        if (!g_current_image) {                                   \
            IupMessage("Error", "No image loaded!");              \
            return IUP_DEFAULT;                                   \
        }                                                         \
        save_undo(&g_current_image, &g_undo_image);               \
        Image *result = filter_func(g_current_image);             \
        if (result) {                                             \
            free_image(g_current_image);                          \
            g_current_image = result;                             \
            update_display();                                     \
        }                                                         \
        return IUP_DEFAULT;                                       \
    }

FILTER_CALLBACK_NEW_IMAGE(cb_blur,    apply_blur)
FILTER_CALLBACK_NEW_IMAGE(cb_sharpen, apply_sharpen)
FILTER_CALLBACK_NEW_IMAGE(cb_rotate,  apply_rotate_90_cw)
```

> [!TIP]
> **If you prefer not to use macros**, you can write each callback as a separate function. The macros above just eliminate the copy-paste pattern. Here's what the expanded `cb_grayscale` looks like:
> ```c
> static int cb_grayscale(Ihandle *self) {
>     (void)self;
>     if (!g_current_image) {
>         IupMessage("Error", "No image loaded!");
>         return IUP_DEFAULT;
>     }
>     save_undo(&g_current_image, &g_undo_image);
>     apply_grayscale(g_current_image);
>     update_display();
>     return IUP_DEFAULT;
> }
> ```

---

### Step 3.6 — Undo Callback

```c
static int cb_undo(Ihandle *self) {
    (void)self;
    if (!g_undo_image) {
        IupMessage("Undo", "Nothing to undo!");
        return IUP_DEFAULT;
    }
    apply_undo(&g_current_image, &g_undo_image);
    update_display();
    return IUP_DEFAULT;
}
```

---

### Step 3.7 — Crop Callback (with IUP Input Dialog)

Crop requires user input (the rectangle coordinates). Use `IupGetParam()` to show an input dialog:

```c
static int cb_crop(Ihandle *self) {
    (void)self;
    if (!g_current_image) {
        IupMessage("Error", "No image loaded!");
        return IUP_DEFAULT;
    }

    int x1 = 0, y1 = 0;
    int x2 = g_current_image->width  - 1;
    int y2 = g_current_image->height - 1;

    /* IupGetParam shows a dialog with labeled integer input fields */
    if (!IupGetParam("Crop Image", NULL, NULL,
                     "X1 (left): %i\n"
                     "Y1 (top): %i\n"
                     "X2 (right): %i\n"
                     "Y2 (bottom): %i\n",
                     &x1, &y1, &x2, &y2, NULL)) {
        return IUP_DEFAULT;   /* User cancelled */
    }

    save_undo(&g_current_image, &g_undo_image);
    Image *cropped = apply_crop(g_current_image, x1, y1, x2, y2);
    if (cropped) {
        free_image(g_current_image);
        g_current_image = cropped;
        update_display();
    } else {
        IupMessage("Error", "Invalid crop region!");
    }
    return IUP_DEFAULT;
}
```

---

### Step 3.8 — Brightness Callback (with IUP Input Dialog)

```c
static int cb_brightness(Ihandle *self) {
    (void)self;
    if (!g_current_image) {
        IupMessage("Error", "No image loaded!");
        return IUP_DEFAULT;
    }

    int delta = 0;

    if (!IupGetParam("Brightness", NULL, NULL,
                     "Adjustment (-255 to 255): %i\n",
                     &delta, NULL)) {
        return IUP_DEFAULT;   /* User cancelled */
    }

    /* Validate range */
    if (delta < -255 || delta > 255) {
        IupMessage("Error", "Brightness value must be between -255 and 255!");
        return IUP_DEFAULT;
    }

    save_undo(&g_current_image, &g_undo_image);
    apply_brightness(g_current_image, delta);
    update_display();
    return IUP_DEFAULT;
}
```

---

### Step 3.9 — Build the Main GUI Layout

This is the function that assembles all the IUP elements:

```c
/* ── Exit Callback ────────────────────────────────────── */
static int cb_exit(Ihandle *self) {
    (void)self;
    return IUP_CLOSE;
}

/* ── Cleanup ──────────────────────────────────────────── */
void cleanup_images(void) {
    if (g_current_image) { free_image(g_current_image); g_current_image = NULL; }
    if (g_undo_image)    { free_image(g_undo_image);    g_undo_image = NULL; }
}

/* ── Main GUI Builder ─────────────────────────────────── */
Ihandle* build_main_gui(void) {
    /* ── 1. Create the image display area ── */
    g_img_label = IupLabel("No image loaded. Click File > Open to load a BMP image.");
    IupSetAttribute(g_img_label, "EXPAND", "YES");
    IupSetAttribute(g_img_label, "ALIGNMENT", "ACENTER:ACENTER");

    /* ── 2. Create the Menu Bar ── */
    /* File menu */
    Ihandle *item_open = IupItem("Open\tCtrl+O", NULL);
    Ihandle *item_save = IupItem("Save As\tCtrl+S", NULL);
    Ihandle *item_exit = IupItem("Exit", NULL);
    IupSetCallback(item_open, "ACTION", (Icallback)cb_file_open);
    IupSetCallback(item_save, "ACTION", (Icallback)cb_file_save);
    IupSetCallback(item_exit, "ACTION", (Icallback)cb_exit);

    Ihandle *file_menu = IupMenu(
        item_open,
        item_save,
        IupSeparator(),
        item_exit,
        NULL
    );

    /* Edit menu */
    Ihandle *item_undo = IupItem("Undo\tCtrl+Z", NULL);
    IupSetCallback(item_undo, "ACTION", (Icallback)cb_undo);

    Ihandle *edit_menu = IupMenu(
        item_undo,
        NULL
    );

    /* Filters menu */
    Ihandle *item_gray   = IupItem("Grayscale", NULL);
    Ihandle *item_bright = IupItem("Brightness...", NULL);
    Ihandle *item_invert = IupItem("Invert (Negative)", NULL);
    Ihandle *item_hflip  = IupItem("Horizontal Flip", NULL);
    Ihandle *item_vflip  = IupItem("Vertical Flip", NULL);
    Ihandle *item_rotate = IupItem("Rotate 90° CW", NULL);
    Ihandle *item_crop   = IupItem("Crop...", NULL);
    Ihandle *item_blur   = IupItem("Blur (3x3)", NULL);
    Ihandle *item_sharp  = IupItem("Sharpen (Bonus)", NULL);

    IupSetCallback(item_gray,   "ACTION", (Icallback)cb_grayscale);
    IupSetCallback(item_bright, "ACTION", (Icallback)cb_brightness);
    IupSetCallback(item_invert, "ACTION", (Icallback)cb_inversion);
    IupSetCallback(item_hflip,  "ACTION", (Icallback)cb_horizontal_flip);
    IupSetCallback(item_vflip,  "ACTION", (Icallback)cb_vertical_flip);
    IupSetCallback(item_rotate, "ACTION", (Icallback)cb_rotate);
    IupSetCallback(item_crop,   "ACTION", (Icallback)cb_crop);
    IupSetCallback(item_blur,   "ACTION", (Icallback)cb_blur);
    IupSetCallback(item_sharp,  "ACTION", (Icallback)cb_sharpen);

    Ihandle *filters_menu = IupMenu(
        item_gray,
        item_bright,
        item_invert,
        IupSeparator(),
        item_hflip,
        item_vflip,
        item_rotate,
        IupSeparator(),
        item_crop,
        item_blur,
        item_sharp,
        NULL
    );

    /* Assemble the menu bar */
    Ihandle *menu_bar = IupMenu(
        IupSubmenu("File", file_menu),
        IupSubmenu("Edit", edit_menu),
        IupSubmenu("Filters", filters_menu),
        NULL
    );

    /* ── 3. Create Toolbar Buttons (optional but nice) ── */
    Ihandle *btn_open   = IupButton("Open",   NULL);
    Ihandle *btn_save   = IupButton("Save",   NULL);
    Ihandle *btn_undo   = IupButton("Undo",   NULL);
    Ihandle *btn_gray   = IupButton("Gray",   NULL);
    Ihandle *btn_bright = IupButton("Bright", NULL);
    Ihandle *btn_invert = IupButton("Invert", NULL);
    Ihandle *btn_hflip  = IupButton("H-Flip", NULL);
    Ihandle *btn_vflip  = IupButton("V-Flip", NULL);
    Ihandle *btn_rotate = IupButton("Rotate", NULL);
    Ihandle *btn_crop   = IupButton("Crop",   NULL);
    Ihandle *btn_blur   = IupButton("Blur",   NULL);
    Ihandle *btn_sharp  = IupButton("Sharp",  NULL);

    IupSetCallback(btn_open,   "ACTION", (Icallback)cb_file_open);
    IupSetCallback(btn_save,   "ACTION", (Icallback)cb_file_save);
    IupSetCallback(btn_undo,   "ACTION", (Icallback)cb_undo);
    IupSetCallback(btn_gray,   "ACTION", (Icallback)cb_grayscale);
    IupSetCallback(btn_bright, "ACTION", (Icallback)cb_brightness);
    IupSetCallback(btn_invert, "ACTION", (Icallback)cb_inversion);
    IupSetCallback(btn_hflip,  "ACTION", (Icallback)cb_horizontal_flip);
    IupSetCallback(btn_vflip,  "ACTION", (Icallback)cb_vertical_flip);
    IupSetCallback(btn_rotate, "ACTION", (Icallback)cb_rotate);
    IupSetCallback(btn_crop,   "ACTION", (Icallback)cb_crop);
    IupSetCallback(btn_blur,   "ACTION", (Icallback)cb_blur);
    IupSetCallback(btn_sharp,  "ACTION", (Icallback)cb_sharpen);

    Ihandle *toolbar = IupHbox(
        btn_open, btn_save, btn_undo,
        IupFill(),   /* Spacer */
        btn_gray, btn_bright, btn_invert,
        btn_hflip, btn_vflip, btn_rotate,
        btn_crop, btn_blur, btn_sharp,
        NULL
    );
    IupSetAttribute(toolbar, "GAP", "5");
    IupSetAttribute(toolbar, "MARGIN", "5x2");

    /* ── 4. Assemble the Main Layout ── */
    Ihandle *vbox = IupVbox(
        toolbar,
        g_img_label,
        NULL
    );

    /* ── 5. Create the Main Dialog ── */
    Ihandle *dlg = IupDialog(vbox);
    IupSetAttribute(dlg, "TITLE", "CSE 1101 — Image Manipulation Software");
    IupSetAttribute(dlg, "SIZE", "HALFxHALF");       /* Start at half screen size */
    IupSetAttributeHandle(dlg, "MENU", menu_bar);     /* Attach menu bar */

    return dlg;
}
```

**Layout structure:**
```text
┌──────────────────────────────────────────────────────┐
│  Menu Bar: [File ▾] [Edit ▾] [Filters ▾]            │
├──────────────────────────────────────────────────────┤
│  Toolbar: [Open][Save][Undo]    [Gray][Bright]...   │
├──────────────────────────────────────────────────────┤
│                                                      │
│                  Image Display Area                  │
│              (IupLabel with IMAGE)                   │
│                                                      │
└──────────────────────────────────────────────────────┘
```

---

<br>

## 🔗 Phase 4 — Wire Everything in `main.c`

Replace your current `main.c` with the final version:

```c
/* src/main.c — Application entry point */
#include <stdlib.h>
#include <iup.h>
#include "gui.h"

int main(int argc, char **argv) {
    /* 1. Initialize IUP */
    IupOpen(&argc, &argv);

    /* 2. Build the GUI */
    Ihandle *dlg = build_main_gui();

    /* 3. Show the window centered on screen */
    IupShowXY(dlg, IUP_CENTER, IUP_CENTER);

    /* 4. Run the event loop (blocks until user closes the window) */
    IupMainLoop();

    /* 5. Cleanup */
    cleanup_images();
    IupClose();
    return EXIT_SUCCESS;
}
```

> [!NOTE]
> `main.c` is intentionally tiny. All complexity lives in `gui.c` (layout and callbacks), `image.c` (data), and `filter.c` (algorithms). This is the **modular design** the rubric rewards.

---

<br>

## 🔨 Phase 5 — Final Build & Validation

### Step 5.1 — Update `build.bat`

Your [build.bat](file:///d:/02_CODE/05_CSE_1101/LAB_PROJECT/FINAL_PROJECT/build.bat) needs to compile **all source files**:

```batch
@echo off
setlocal

echo ====================================================
echo   Building Image Manipulation Software (Win64)
echo ====================================================
taskkill /F /IM ImageEditor.exe >nul 2>nul

gcc src\main.c src\gui.c src\image.c src\filter.c src\ucrt_compat.c ^
    -o ImageEditor.exe ^
    -I./include -L./lib ^
    -liup -lgdi32 -lcomdlg32 -lcomctl32 -luuid -loleaut32 -lole32 -luxtheme ^
    -Wall -Wextra

if %ERRORLEVEL% EQU 0 (
    echo.
    echo [SUCCESS] ImageEditor.exe built successfully!
    echo Launching ImageEditor.exe...
    .\ImageEditor.exe
) else (
    echo.
    echo [ERROR] Build failed! Please review compiler errors above.
)

pause
```

### Step 5.2 — Full Compile & Smoke Test Checklist

Run `.\build.bat` and verify each feature:

| # | Test | Expected Result | ✅ |
|---|------|----------------|---|
| 1 | File → Open → select a `.bmp` | Image appears in the window | ☐ |
| 2 | File → Open → select a `.jpg` | Error message: "Only 24-bit uncompressed BMP" | ☐ |
| 3 | Filters → Grayscale | Image turns grayscale | ☐ |
| 4 | Edit → Undo | Image reverts to color | ☐ |
| 5 | Filters → Brightness → enter `50` | Image becomes brighter | ☐ |
| 6 | Filters → Brightness → enter `-50` | Image becomes darker | ☐ |
| 7 | Filters → Invert | Colors invert (negative effect) | ☐ |
| 8 | Filters → Horizontal Flip | Image mirrors left-right | ☐ |
| 9 | Filters → Vertical Flip | Image mirrors top-bottom | ☐ |
| 10 | Filters → Rotate 90° CW | Image rotates clockwise, window updates | ☐ |
| 11 | Filters → Crop → enter coordinates | Image is cropped to sub-region | ☐ |
| 12 | Filters → Blur | Image becomes blurred | ☐ |
| 13 | Filters → Sharpen | Edges become sharper | ☐ |
| 14 | File → Save As → enter filename | `.bmp` file is created, opens correctly | ☐ |
| 15 | Try filters with no image loaded | Error message appears (no crash) | ☐ |
| 16 | Undo with nothing to undo | "Nothing to undo" message (no crash) | ☐ |
| 17 | Close the window | Application exits cleanly | ☐ |

---

<br>

# Part C — Reference & Exam Prep

---

## 📂 Final Modular Source Organization

```text
src/
├── main.c          Entry point: IupOpen → build_main_gui → IupMainLoop → cleanup → IupClose
├── gui.h           Declares: build_main_gui(), cleanup_images()
├── gui.c           Implements: layout, menus, toolbar, all callbacks, display helper
├── image.h         Declares: Pixel, Image, create/free/clone_image, load/save_bmp
├── image.c         Implements: BMP headers, memory management, BMP read/write
├── filter.h        Declares: all filter function prototypes
├── filter.c        Implements: grayscale, brightness, invert, flip, rotate, crop, blur, sharpen
└── ucrt_compat.c   MinGW UCRT → MSVCRT symbol compatibility shim
```

**Dependency graph:**
```text
main.c ──→ gui.h ──→ image.h ←── filter.h
              │         ↑              │
              ▼         │              ▼
           gui.c    image.c       filter.c
              │
              └──→ filter.h (for calling filter functions in callbacks)
```

---

## 📊 Marking Rubric Breakdown (100 + 5 Bonus)

| Category | Marks | What the examiner evaluates |
|---|---|---|
| **GUI & IUP** | **10** | Window, menus, buttons, organized layout, usable interface |
| **Image I/O** | **10** | Load 24-bit BMP, display it, save modified image correctly |
| **Image Manipulation** | **30** | Grayscale, Brightness, Invert, H-Flip, V-Flip, Rotate 90°, Crop, Blur, Undo |
| **Modular Design** | **10** | Separate `.h`/`.c` files, functions instead of monolithic `main()`, proper `#include` |
| **Memory & Errors** | **10** | `malloc`/`free` correctness, no leaks, handles invalid input gracefully |
| **Viva & Demo** | **30** | Explain your code, trace algorithm execution, answer pointer/struct questions |
| **⭐ Sharpen Bonus** | **+5** | Convolution kernel implementation (not a library call) |

---

## 🎤 Viva & Demonstration — What You Must Know

### Questions About Data Structures

| Question | Key Answer |
|---|---|
| **Why use a 1D array `Pixel *data` instead of `Pixel **data`?** | Single `malloc()` = contiguous memory, better cache performance, simpler `free()`. Access via `data[y * width + x]`. |
| **Why `unsigned char` for RGB channels?** | Range 0–255 perfectly fits 1 byte. `char` might be signed (-128 to 127) on some compilers. |
| **Why `#pragma pack(push, 1)` on BMP headers?** | Prevents compiler from inserting padding between struct fields. BMP headers must be read as exact byte sequences. |

### Questions About BMP Format

| Question | Key Answer |
|---|---|
| **Why does BMP need row padding?** | CPU/GPU hardware reads memory in 32-bit (4-byte) aligned chunks. Aligned rows enable faster DMA transfers. |
| **Why is BMP stored bottom-up?** | Historical: early CRT monitors drew bottom-to-top. BMPs with `biHeight > 0` follow this convention. |
| **Why does BMP use BGR instead of RGB?** | Windows GDI internally uses BGR (COLORREF is `0x00BBGGRR`). BMP matches the native Windows format. |

### Questions About IUP

| Question | Key Answer |
|---|---|
| **What is an `Ihandle*`?** | An opaque pointer to any IUP GUI element (dialog, button, label, menu). You interact with it only via IUP API functions. |
| **What does `IupSetCallback()` do?** | Associates a C function with a GUI event (e.g., button click). When the event fires, IUP calls your function. |
| **Why call `IupRefresh()` after updating an image?** | IUP doesn't automatically redraw. `IupRefresh()` recalculates the layout and repaints the element. |

### Questions About Filters

| Question | Key Answer |
|---|---|
| **Why does blur need a separate output image?** | If you write blurred values back to the source, later pixels read already-blurred neighbors → incorrect result. |
| **How does the sharpen kernel enhance edges?** | Center weight (5) amplifies the pixel; negative neighbors (-1) subtract surrounding average, emphasizing differences. |
| **What happens at image boundaries during convolution?** | Edge pixels don't have a full 3×3 neighborhood. Options: copy unchanged, clamp to edge, or adjust count. |

### Questions About Memory Management

| Question | Key Answer |
|---|---|
| **Where does memory allocation happen?** | `create_image()` allocates. `clone_image()` allocates via `create_image()`. `load_bmp()` allocates via `create_image()`. |
| **Where does deallocation happen?** | `free_image()` frees. Called in: `cleanup_images()`, filter callbacks (when replacing current image), `apply_undo()`. |
| **How do you avoid memory leaks?** | Every `create_image`/`clone_image`/`load_bmp` has a matching `free_image`. IUP images are freed via `IupDestroy()` in `update_display()`. |

---

## 🐛 Common Pitfalls & Debugging Tips

### Compilation Errors

| Error Message | Cause | Fix |
|---|---|---|
| `undefined reference to __imp___argc` | UCRT/MSVCRT mismatch | Ensure `ucrt_compat.c` is compiled in `build.bat` |
| `undefined reference to IupOpen` | Missing `-liup` linker flag | Check that `-liup` comes **after** your source files in the gcc command |
| `multiple definition of ...` | Function defined in a `.h` file | Move function bodies to `.c` files; `.h` files should only have `declarations` |
| `implicit declaration of function` | Missing `#include` | Add the appropriate `#include "image.h"` or `#include "filter.h"` |

### Runtime Crashes

| Symptom | Likely Cause | Fix |
|---|---|---|
| Crash when loading a BMP | Forgetting `"rb"` (binary mode) in `fopen` | Use `fopen(filename, "rb")` — always binary on Windows |
| Image looks scrambled/shifted | Scanline padding not handled | Apply the padding formula: `(4 - (width * 3) % 4) % 4` |
| Colors look wrong (red↔blue swap) | Not converting BGR ↔ RGB | Swap channels during both `load_bmp()` and `save_bmp()` |
| Crash after rotation/crop | Not replacing the old image pointer | After `rotate`/`crop`, `free_image(old)` then assign the new image |
| Crash on undo | Double-freeing the undo image | Set `*undo = NULL` after restoring (as shown in `apply_undo()`) |

### Memory Leak Detection

If you want to check for memory leaks, add a simple counter:
```c
/* Add to image.c (debugging only) */
static int alloc_count = 0;

Image* create_image(...) {
    /* ... existing code ... */
    alloc_count++;
    printf("[DEBUG] Image allocated (total: %d)\n", alloc_count);
    return img;
}

void free_image(Image *img) {
    if (!img) return;
    alloc_count--;
    printf("[DEBUG] Image freed (remaining: %d)\n", alloc_count);
    /* ... existing code ... */
}
```

At exit, `alloc_count` should be **0**. If it's not, you have a leak.

---

> **End of Guide.** Follow Phases 1 → 5 in order, and you'll have a complete, working Image Manipulation Software. Good luck! 🚀
