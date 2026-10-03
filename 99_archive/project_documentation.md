# 📄 Image Manipulation Software — Technical Documentation

**Language:** C (C99)
**GUI Toolkit:** IUP 3.32
**Image Format:** 24-bit uncompressed BMP
**Platform:** Windows 64-bit (MinGW-w64 / GCC)
**Version:** 1.0

---

## Table of Contents

1. [Architecture Overview](#1-architecture-overview)
2. [Directory Structure](#2-directory-structure)
3. [Data Structures](#3-data-structures)
4. [API Reference — image.c](#4-api-reference--imagec)
5. [API Reference — filter.c](#5-api-reference--filterc)
6. [API Reference — gui.c](#6-api-reference--guic)
7. [BMP File Format Specification](#7-bmp-file-format-specification)
8. [Build System](#8-build-system)
9. [IUP Widget Hierarchy](#9-iup-widget-hierarchy)
10. [Data Flow Diagrams](#10-data-flow-diagrams)
11. [Design Decisions](#11-design-decisions)
12. [Known Limitations](#12-known-limitations)
13. [Dependencies](#13-dependencies)

---

## 1. Architecture Overview

The application is a single-window desktop image editor organized into three distinct layers:

```
┌────────────────────────────────────────────────────────────┐
│                     Presentation Layer                      │
│                         gui.c / gui.h                       │
│   IUP widgets, callbacks, canvas rendering, undo state      │
├────────────────────────────────────────────────────────────┤
│                    Image Processing Layer                    │
│                       filter.c / filter.h                   │
│   Grayscale, brightness, flip, rotate, crop, blur, sharpen  │
├────────────────────────────────────────────────────────────┤
│                    Image Memory Layer                        │
│                       image.c / image.h                     │
│   Pixel/Image structs, BMP I/O, alloc/free/clone            │
└────────────────────────────────────────────────────────────┘
                            ▲
                       main.c (entry point)
                  IupOpen → build GUI → IupMainLoop → IupClose
```

**Dependency graph:**
```
main.c  ──► gui.h ──► image.h
                  └── filter.h ──► image.h
```
`main.c` only knows about `gui.h`. `gui.h` knows about both `image.h` and `filter.h`. `filter.h` knows about `image.h`. No circular dependencies.

---

## 2. Directory Structure

```
FINAL_PROJECT/
├── ImageEditor.exe          Pre-compiled 64-bit Windows executable
├── build.bat                Batch build script (GCC + link + launch)
├── README.md                User-facing readme
│
├── include/                 IUP 3.32 header files (iup.h, iupkey.h, iupdraw.h, etc.)
├── lib/                     IUP 3.32 static libraries (libiup.a, etc.) for Win64
├── pics/                    Sample test images (lena.bmp + filtered variants)
├── screenshots/             Application screenshots (01_ui_overview.png ... 12_sharpen.png)
│
└── src/
    ├── main.c               Application entry point
    │
    ├── header/              Header files (declarations only)
    │   ├── image.h          Pixel, Image structs + image function prototypes
    │   ├── filter.h         Filter function prototypes
    │   └── gui.h            GUI function prototypes
    │
    └── programs/            Implementation files (definitions)
        ├── image.c          BMP I/O + image memory management
        ├── filter.c         Image manipulation algorithms
        ├── gui.c            IUP GUI construction + event callbacks
        └── ucrt_compat.c    UCRT compatibility shim
```

---

## 3. Data Structures

### 3.1 `Pixel` — Single Image Pixel

**Defined in:** `src/header/image.h`

```c
typedef struct {
    unsigned char r;  // Red   component [0, 255]
    unsigned char g;  // Green component [0, 255]
    unsigned char b;  // Blue  component [0, 255]
} Pixel;
```

**Size:** 3 bytes (no padding — `unsigned char` has alignment 1)

| Field | Type | Range | Description |
|-------|------|-------|-------------|
| `r` | `unsigned char` | 0–255 | Red color channel |
| `g` | `unsigned char` | 0–255 | Green color channel |
| `b` | `unsigned char` | 0–255 | Blue color channel |

---

### 3.2 `Image` — Image Container

**Defined in:** `src/header/image.h`

```c
typedef struct {
    int    width;    // Image width in pixels
    int    height;   // Image height in pixels
    Pixel *data;     // Heap-allocated 1D array of width×height Pixels
} Image;
```

**Memory layout:**
```
Image struct (on heap)
├── width  : int
├── height : int
└── data   ──► [ Pixel(0,0) | Pixel(1,0) | ... | Pixel(w-1,0) | Pixel(0,1) | ... ]
                ◄─────────── row 0 ────────────► ◄──── row 1 ────► ...
```

**Pixel access formula:** `data[y * width + x]` for pixel at column `x`, row `y`.

**Ownership:** The `data` pointer is always heap-allocated by `create_image()`. The caller is responsible for calling `free_image()` when done.

---

### 3.3 `BMPFileHeader` — BMP File Header

**Defined in:** `src/programs/image.c` (private, not exposed in headers)

```c
#pragma pack(push, 1)
typedef struct {
    unsigned short bfType;       // Offset 0,  Size 2: Magic "BM" = 0x4D42
    unsigned int   bfSize;       // Offset 2,  Size 4: Total file size in bytes
    unsigned short bfReserved1;  // Offset 6,  Size 2: Reserved, must be 0
    unsigned short bfReserved2;  // Offset 8,  Size 2: Reserved, must be 0
    unsigned int   bfOffBits;    // Offset 10, Size 4: Byte offset to pixel data
} BMPFileHeader;                 // Total: 14 bytes
#pragma pack(pop)
```

---

### 3.4 `BMPInfoHeader` — BMP Info Header (DIB Header)

**Defined in:** `src/programs/image.c` (private)

```c
#pragma pack(push, 1)
typedef struct {
    unsigned int   biSize;          // Offset 14, Size 4: Size of this header (40)
    int            biWidth;         // Offset 18, Size 4: Image width in pixels
    int            biHeight;        // Offset 22, Size 4: Image height (neg = top-down)
    unsigned short biPlanes;        // Offset 26, Size 2: Color planes (must be 1)
    unsigned short biBitCount;      // Offset 28, Size 2: Bits per pixel (24)
    unsigned int   biCompression;   // Offset 30, Size 4: Compression (0 = none)
    unsigned int   biSizeImage;     // Offset 34, Size 4: Pixel data size in bytes
    int            biXPelsPerMeter; // Offset 38, Size 4: Horizontal DPI (ignored)
    int            biYPelsPerMeter; // Offset 42, Size 4: Vertical DPI (ignored)
    unsigned int   biClrUsed;       // Offset 46, Size 4: Colors used (0 = max)
    unsigned int   biClrImportant;  // Offset 50, Size 4: Important colors (0 = all)
} BMPInfoHeader;                    // Total: 40 bytes
#pragma pack(pop)
```

---

## 4. API Reference — `image.c`

### `create_image()`

```c
Image *create_image(int width, int height);
```

**Description:** Allocates and initializes a new `Image` struct with a zero-filled pixel buffer.

**Parameters:**
| Param | Type | Description |
|-------|------|-------------|
| `width` | `int` | Width in pixels. Must be > 0. |
| `height` | `int` | Height in pixels. Must be > 0. |

**Returns:** Pointer to newly allocated `Image`, or `NULL` on failure (invalid dimensions or allocation failure).

**Memory:** Caller owns the returned pointer. Must call `free_image()` when done.

**Behavior:**
- Uses `malloc` for the `Image` struct
- Uses `calloc` for the pixel array (all pixels initialized to black = 0,0,0)
- If pixel allocation fails, frees the `Image` struct before returning `NULL`

---

### `free_image()`

```c
void free_image(Image *img);
```

**Description:** Frees all memory associated with an `Image`, including its pixel data buffer.

**Parameters:**
| Param | Type | Description |
|-------|------|-------------|
| `img` | `Image*` | Image to free. Safe to pass `NULL`. |

**Memory:** After this call, `img` is a dangling pointer. Caller should set it to `NULL`.

**Behavior:**
- If `img` is `NULL`, does nothing (safe)
- Frees `img->data` first, sets it to `NULL`
- Then frees `img`

---

### `clone_image()`

```c
Image *clone_image(const Image *img);
```

**Description:** Creates a deep copy of an `Image` — a fully independent duplicate with its own pixel buffer.

**Parameters:**
| Param | Type | Description |
|-------|------|-------------|
| `img` | `const Image*` | Source image to copy. Must not be `NULL`. |

**Returns:** Pointer to new `Image` (deep copy), or `NULL` on failure.

**Memory:** Caller owns the returned pointer. Must call `free_image()` when done.

**Implementation:** Uses `create_image()` then `memcpy()` for the pixel data.

---

### `load_bmp()`

```c
Image *load_bmp(const char *filename);
```

**Description:** Loads a 24-bit uncompressed BMP file from disk into an `Image` struct.

**Parameters:**
| Param | Type | Description |
|-------|------|-------------|
| `filename` | `const char*` | Absolute or relative path to the BMP file. |

**Returns:** Pointer to loaded `Image`, or `NULL` on any failure.

**Failure cases:**
- File not found / cannot open
- File header magic number ≠ `0x4D42` (not a BMP)
- `biBitCount` ≠ 24 (not 24-bit color)
- `biCompression` ≠ 0 (compressed BMP — not supported)
- Memory allocation failure

**Behavior:**
- Opens file in binary mode (`"rb"`)
- Reads and validates `BMPFileHeader` and `BMPInfoHeader`
- Handles both bottom-up (`biHeight > 0`, standard) and top-down (`biHeight < 0`) row orders
- Calculates and skips row padding bytes: `padding = (4 - (width * 3) % 4) % 4`
- Converts BGR (BMP format) to RGB (`Pixel.r`, `.g`, `.b`)
- Seeks to pixel data using `bfOffBits` (handles extra header data gracefully)
- Closes file before returning

---

### `save_bmp()`

```c
int save_bmp(const char *filename, const Image *img);
```

**Description:** Saves an `Image` to a 24-bit uncompressed BMP file on disk.

**Parameters:**
| Param | Type | Description |
|-------|------|-------------|
| `filename` | `const char*` | Output file path. Will be created/overwritten. |
| `img` | `const Image*` | Image to save. Must not be `NULL`. |

**Returns:** `1` on success, `0` on failure.

**Failure cases:**
- `img`, `img->data`, or `filename` is `NULL`
- File cannot be created/opened for writing

**Behavior:**
- Writes standard 54-byte BMP header (14 + 40 bytes)
- Writes pixel data in bottom-up row order (standard BMP)
- Converts RGB to BGR for each pixel
- Writes zero-padding bytes after each row

---

## 5. API Reference — `filter.c`

### Helper: `clamp()` (private)

```c
static inline unsigned char clamp(int val);
```

**Description:** Constrains an integer value to the range [0, 255] for safe storage in `unsigned char`.

**Visibility:** Static — only accessible within `filter.c`.

---

### `grayscale()`

```c
void grayscale(Image *img);
```

**Description:** Converts the image to grayscale in-place using the ITU-R BT.601 luminance formula.

**Formula:** `gray = 0.299 × R + 0.587 × G + 0.114 × B`

All three channels (R, G, B) are set to the computed `gray` value.

**Complexity:** O(width × height) — single pass over all pixels.

---

### `brightness()`

```c
void brightness(Image *img, int brightness);
```

**Description:** Adjusts the brightness of all pixels in-place by adding an offset to each channel.

**Parameters:**
| Param | Type | Description |
|-------|------|-------------|
| `brightness` | `int` | Offset to add. Positive = brighter, negative = darker. Typical range: [-255, 255]. |

**Behavior:** Each channel is clamped to [0, 255] after addition.

**Complexity:** O(width × height).

---

### `inversion()`

```c
void inversion(Image *img);
```

**Description:** Inverts all pixel colors in-place (negative effect).

**Formula:** `channel = 255 - channel` for each R, G, B.

**Complexity:** O(width × height).

---

### `horizontalFlip()`

```c
void horizontalFlip(Image *img);
```

**Description:** Mirrors the image horizontally (left↔right) in-place.

**Algorithm:** For each row `y`, swap pixel at column `x` with pixel at column `(width-1-x)`, iterating `x` from 0 to `width/2 - 1`.

**Complexity:** O(width × height / 2).

---

### `verticalFlip()`

```c
void verticalFlip(Image *img);
```

**Description:** Flips the image vertically (top↔bottom) in-place.

**Algorithm:** Swap pixel at row `y` with pixel at row `(height-1-y)` for all columns, iterating `y` from 0 to `height/2 - 1`.

**Complexity:** O(width × height / 2).

---

### `rotate90()`

```c
Image *rotate90(const Image *img);
```

**Description:** Creates a new image that is the original rotated 90° clockwise.

**Returns:** New `Image*` with swapped dimensions (`height_new = width_orig`, `width_new = height_orig`), or `NULL` on failure.

**Coordinate mapping (90° CW):**
- Source `(x, y)` → Destination `(height-1-y, x)` (using new image's coordinate system)
- Destination index: `x * img->height + (img->height - 1 - y)`

**Memory:** Caller owns the returned pointer. Must call `free_image()` when done.

**Complexity:** O(width × height).

---

### `crop()`

```c
Image *crop(const Image *img, int x1, int y1, int x2, int y2);
```

**Description:** Extracts a rectangular sub-region from the image into a new image.

**Parameters:**
| Param | Type | Description |
|-------|------|-------------|
| `x1, y1` | `int` | Top-left corner of crop region (inclusive) |
| `x2, y2` | `int` | Bottom-right corner of crop region (inclusive) |

**Returns:** New `Image*` of size `(x2-x1+1) × (y2-y1+1)`, or `NULL` on failure.

**Behavior:**
- Coordinates are clamped to image bounds before processing
- Returns `NULL` if `x1 > x2` or `y1 > y2` after clamping

**Memory:** Caller owns the returned pointer. Must call `free_image()` when done.

**Complexity:** O(crop_width × crop_height).

---

### `blur()`

```c
Image *blur(const Image *img);
```

**Description:** Applies a 3×3 box blur to the image, creating a new smoothed image.

**Algorithm:** For each pixel, compute the arithmetic mean of all valid neighbors in its 3×3 window (handles border pixels by counting only in-bounds neighbors).

**Returns:** New `Image*` (same dimensions), or `NULL` on failure.

**Memory:** Caller owns the returned pointer. Must call `free_image()` when done.

**Complexity:** O(width × height × 9) worst case = O(width × height).

---

### `sharpen()`

```c
Image *sharpen(const Image *img);
```

**Description:** Applies a 3×3 Laplacian sharpening kernel to the image.

**Kernel:**
```
[  0  -1   0 ]
[ -1   5  -1 ]
[  0  -1   0 ]
```

**Returns:** New `Image*` (same dimensions), or `NULL` on failure.

**Behavior:** Border pixels (first/last row and column) are copied unchanged.

**Memory:** Caller owns the returned pointer. Must call `free_image()` when done.

**Complexity:** O(width × height × 9) = O(width × height).

---

## 6. API Reference — `gui.c`

### `build_main_gui()` (public)

```c
Ihandle* build_main_gui(void);
```

**Description:** Constructs and returns the complete application dialog with all widgets, callbacks, and keyboard shortcuts configured.

**Returns:** `Ihandle*` pointing to the top-level `IupDialog`.

**Side effects:** Sets the global `canvas` and `status_bar` handles.

**Widget hierarchy built:**
```
IupDialog
└── IupVbox
    ├── IupHbox (toolbar)
    │   ├── btn_open, btn_save, btn_undo
    │   ├── IupFill()
    │   └── btn_gray, btn_bright, btn_invert, btn_hflip, btn_vflip,
    │       btn_rotate, btn_crop, btn_blur, btn_sharp
    ├── IupCanvas (canvas — fills remaining space)
    └── IupLabel  (status_bar)
```

---

### `cleanup_images()` (public)

```c
void cleanup_images(void);
```

**Description:** Frees all heap-allocated image resources held by the GUI module. Must be called before `IupClose()`.

**Frees:**
- `current_iup_img` (IUP image handle — via `IupDestroy`)
- `current_image` (via `free_image`)
- `prev_image` (via `free_image`)

---

### Private GUI Functions

| Function | Description |
|----------|-------------|
| `save_undo()` | Clones `current_image` into `prev_image` for undo |
| `undo()` | Restores `prev_image` as `current_image` |
| `update_status(msg)` | Updates status bar label with image info and action message |
| `update_display(msg)` | Rebuilds IUP image handle from `current_image`, triggers canvas redraw |
| `canvas_action(ih, ...)` | Canvas ACTION callback — draws background, scales/centers image, or placeholder text |
| `callback_file_open(self)` | Opens file dialog, loads BMP, replaces `current_image` |
| `callback_file_save(self)` | Opens save dialog, writes `current_image` to BMP |
| `callback_grayscale(self)` | save_undo → grayscale → update_display |
| `callback_inversion(self)` | save_undo → inversion → update_display |
| `callback_horizontalFlip(self)` | save_undo → horizontalFlip → update_display |
| `callback_verticalFlip(self)` | save_undo → verticalFlip → update_display |
| `callback_blur(self)` | save_undo → blur (new img) → free old → update_display |
| `callback_sharpen(self)` | save_undo → sharpen (new img) → free old → update_display |
| `callback_rotate90(self)` | save_undo → rotate90 (new img) → free old → update_display |
| `callback_crop(self)` | Prompts for coords → save_undo → crop (new img) → free old → update_display |
| `callback_brightness(self)` | Prompts for level → save_undo → brightness → update_display |
| `callback_undo(self)` | undo() → update_display |

---

## 7. BMP File Format Specification

### File Layout

```
Byte Offset  Size   Field
──────────────────────────────────────────────
0            2      bfType        = 0x4D42 ("BM")
2            4      bfSize        = file size in bytes
6            2      bfReserved1   = 0
8            2      bfReserved2   = 0
10           4      bfOffBits     = 54 (for standard 24-bit BMP)
──────────────────────────────────────────────
14           4      biSize        = 40
18           4      biWidth       = image width
22           4      biHeight      = image height (positive = bottom-up)
26           2      biPlanes      = 1
28           2      biBitCount    = 24
30           4      biCompression = 0 (BI_RGB, no compression)
34           4      biSizeImage   = row_size × height
38           4      biXPelsPerMeter (ignored)
42           4      biYPelsPerMeter (ignored)
46           4      biClrUsed     = 0
50           4      biClrImportant= 0
──────────────────────────────────────────────
54           ...    Pixel data (bottom-up, BGR, with row padding)
```

### Pixel Data

- Pixel order: **BGR** (Blue byte first, then Green, then Red)
- Row order: **Bottom-up** — row 0 in file = bottom row of image
- Row size in file: `width × 3 + padding` bytes
- Padding formula: `padding = (4 - (width × 3) % 4) % 4`
- Padding bytes are zeros

### Supported Subset

This application only supports:
- `biBitCount == 24` (24-bit true color, no color table)
- `biCompression == 0` (BI_RGB, uncompressed)
- Standard BITMAPINFOHEADER (40-byte info header)

---

## 8. Build System

### `build.bat`

```bat
gcc src\main.c src\programs\gui.c src\programs\image.c \
    src\programs\filter.c src\programs\ucrt_compat.c \
    -o ImageEditor.exe \
    -I./src/header -I./include -L./lib \
    -liup -lgdi32 -lcomdlg32 -lcomctl32 -luuid -loleaut32 -lole32 -luxtheme \
    -Wall -Wextra
```

### Compiler Flags

| Flag | Purpose |
|------|---------|
| `-I./src/header` | Add project header directory to include search path |
| `-I./include` | Add IUP header directory to include search path |
| `-L./lib` | Add IUP library directory to library search path |
| `-liup` | Link against `lib/libiup.a` |
| `-lgdi32` | Windows Graphics Device Interface |
| `-lcomdlg32` | Windows Common Dialogs (file open/save) |
| `-lcomctl32` | Windows Common Controls (buttons, etc.) |
| `-luuid` | COM interface IDs |
| `-loleaut32` | OLE Automation |
| `-lole32` | Object Linking and Embedding |
| `-luxtheme` | Windows visual theme support |
| `-Wall -Wextra` | Enable all compiler warnings |

### `ucrt_compat.c` — Purpose

The IUP static libraries in `lib/` were compiled against an older Windows C runtime (MSVCRT) which exposes `__argc` and `__argv` as importable symbols `__imp___argc` and `__imp___argv`. Modern GCC on Windows uses the Universal CRT (UCRT), which exposes these as plain `__argc` / `__argv`. The linker fails to find `__imp___argc` unless this shim is provided.

```c
extern int    __argc;
extern char **__argv;

int    *__imp___argc = &__argc;
char ***__imp___argv = (char ***)&__argv;
```

This creates the expected linker symbols by pointing them to the UCRT's standard `__argc`/`__argv`.

---

## 9. IUP Widget Hierarchy

```
IupDialog  ["TITLE"="Image Manipulation Software", "RASTERSIZE"="900x700"]
│   callbacks: K_cO → callback_file_open
│              K_cS → callback_file_save
│              K_cZ → callback_undo
│
└── IupVbox
    │
    ├── IupHbox  ["GAP"="6", "MARGIN"="6x4"]  (toolbar)
    │   ├── IupButton "Open"    ["TIP"=...] → callback_file_open
    │   ├── IupButton "Save"    ["TIP"=...] → callback_file_save
    │   ├── IupButton "Undo"    ["TIP"=...] → callback_undo
    │   ├── IupFill()
    │   ├── IupButton "Gray"    ["TIP"=...] → callback_grayscale
    │   ├── IupButton "Bright"  ["TIP"=...] → callback_brightness
    │   ├── IupButton "Invert"  ["TIP"=...] → callback_inversion
    │   ├── IupButton "H-Flip"  ["TIP"=...] → callback_horizontalFlip
    │   ├── IupButton "V-Flip"  ["TIP"=...] → callback_verticalFlip
    │   ├── IupButton "Rotate"  ["TIP"=...] → callback_rotate90
    │   ├── IupButton "Crop"    ["TIP"=...] → callback_crop
    │   ├── IupButton "Blur"    ["TIP"=...] → callback_blur
    │   └── IupButton "Sharp"   ["TIP"=...] → callback_sharpen
    │
    ├── IupCanvas  ["EXPAND"="YES", "CANVASBOX"="YES"]
    │       ACTION callback → canvas_action()
    │
    └── IupLabel  (status_bar)  ["EXPAND"="HORIZONTAL", "PADDING"="6x4"]
```

---

## 10. Data Flow Diagrams

### Loading an Image

```
User clicks "Open"
    │
    ▼
callback_file_open()
    │
    ├── IupFileDlg() ──► user picks file ──► filename
    │
    ├── load_bmp(filename)
    │       ├── fopen(filename, "rb")
    │       ├── fread BMPFileHeader → validate 0x4D42
    │       ├── fread BMPInfoHeader → validate 24-bit, uncompressed
    │       ├── create_image(width, height) → malloc Image + calloc data[]
    │       ├── loop: fread 3 bytes (BGR) per pixel, store as RGB in data[]
    │       │         fseek padding bytes
    │       └── fclose → return Image*
    │
    ├── free_image(old current_image)
    ├── current_image = new Image*
    │
    └── update_display("Image Opened")
            ├── IupDestroy(old current_iup_img)
            ├── malloc flat rgb[] buffer
            ├── copy Image.data[] → rgb[] (struct-of-RGB to flat array)
            ├── IupImageRGB(w, h, rgb) → current_iup_img
            ├── free(rgb)
            ├── IupSetHandle(IMG_HANDLE_NAME, current_iup_img)
            ├── update_status("Image Opened")
            │       └── IupSetStrAttribute(status_bar, "TITLE", buf)
            └── IupUpdate(canvas) ──► canvas_action() fires
                    ├── IupDrawBegin
                    ├── draw dark background rect
                    ├── compute scale + center position
                    ├── IupDrawImage(IMG_HANDLE_NAME, x, y, draw_w, draw_h)
                    └── IupDrawEnd
```

### Applying a Filter (e.g., Blur)

```
User clicks "Blur"
    │
    ▼
callback_blur()
    │
    ├── save_undo()
    │       ├── free_image(prev_image)  [discard old undo state]
    │       └── prev_image = clone_image(current_image)
    │               └── create_image + memcpy
    │
    ├── blur(current_image)
    │       ├── create_image(w, h)
    │       ├── for each pixel: average 3×3 neighborhood
    │       └── return new Image*
    │
    ├── free_image(current_image)  [old image no longer needed]
    ├── current_image = new Image*
    │
    └── update_display("Blur Filter")
            └── (same as Load flow above)
```

### Undo

```
User presses Ctrl+Z
    │
    ▼
callback_undo() → undo()
    │
    ├── free_image(current_image)  [discard modified image]
    ├── current_image = prev_image [restore saved state]
    └── prev_image = NULL          [undo slot now empty]
    │
    └── update_display("Undo Action")
```

---

## 11. Design Decisions

### Why BMP format?

BMP is the simplest binary image format — no compression, no color tables (for 24-bit), no complex decoding required. The entire decoder fits in ~50 lines of C. It is ideal for a learning project focused on teaching image processing concepts rather than file format complexity.

**Trade-off:** BMP files are large (no compression). `lena.bmp` at 512×512×3 bytes = 786,486 bytes (~768 KB). A JPEG would be ~50 KB.

### Why a 1D array for pixel data?

2D arrays in C (`Pixel data[H][W]`) cannot be dynamically sized at runtime. A 1D array (`Pixel *data`) can be allocated with `malloc`/`calloc` for any dimensions at runtime. The 2D indexing formula `y * width + x` is simple and fast.

### Why only 1 level of undo?

Simplicity. A multi-level undo would require a stack of cloned images. Each clone of `lena.bmp` is 786,486 bytes. 10 undo steps = ~7.5 MB. For a learning project, 1-level undo demonstrates the concept without the complexity (or memory overhead) of a full undo stack.

### Why static global variables in `gui.c`?

Multiple unrelated callback functions (grayscale, blur, save, etc.) need to share state (`current_image`, `canvas`, `status_bar`). Passing these through IUP's userdata mechanism would add complexity. Static globals in `gui.c` are private to that module (can't be accessed from other files) and straightforward to reason about for a project this size.

### Why `IupSetStrAttribute` instead of `IupSetAttribute` for the status bar?

`IupSetAttribute` stores only the **pointer** — it does not copy the string content. If the string is in a local `char buf[]`, the pointer becomes dangling when the function returns. `IupSetStrAttribute` copies the string content into IUP's own storage, making it safe.

### Why `IupFill()` in the toolbar?

Creates visual grouping: file/undo operations on the left, image filters on the right. Without `IupFill()`, all buttons would be packed to the left edge.

### Why separate `update_status()` and `update_display()`?

`update_display()` does expensive work (allocating a buffer, creating an IUP image, triggering a canvas redraw). `update_status()` only updates a text label. After `save_bmp()`, we only need to update the status text (not redraw the image), so they are separate.

---

## 12. Known Limitations

| Limitation | Impact | Possible Fix |
|-----------|--------|-------------|
| Only 24-bit uncompressed BMP | Cannot open JPEG, PNG, 8-bit BMP, 32-bit BMP | Integrate a library like `stb_image` |
| 1-level undo only | Cannot undo multiple steps | Implement an undo stack |
| No zoom/pan | Large images are scaled down, cannot zoom in | Add scroll canvas with zoom factor |
| No menu bar | File > Open / Image > Filter menus are absent | Add `IupMenu` / `IupMenuBar` |
| Fixed window size (no shrink) | `SHRINK=NO` prevents making the window smaller than 900×700 | Allow resizing |
| Border pixels not processed in sharpen | Border pixels are copied unchanged | Implement proper boundary extension (padding, clamp, or wrap) |
| No progress indicator for large images | UI freezes while processing very large BMPs | Move filter to background thread |
| No "Save" vs "Save As" distinction | Always opens a save dialog | Implement in-place save using `loaded_filename` |

---

## 13. Dependencies

| Dependency | Version | Purpose |
|-----------|---------|---------|
| **GCC / MinGW-w64** | Any modern | C compiler for Windows |
| **IUP** | 3.32 | GUI toolkit (static library) |
| **Windows GDI32** | OS | Window drawing, graphics |
| **Windows comdlg32** | OS | Native file open/save dialogs |
| **Windows comctl32** | OS | Native button/control styles |
| **Windows UUID/OLE32/OLEAut32** | OS | COM infrastructure (required by IUP) |
| **Windows UxTheme** | OS | Visual theme/styling |

### IUP Library Files Used

| Library | Purpose |
|---------|---------|
| `libiup.a` | Core IUP GUI framework |
| `libiupim.a` | IUP image utilities (IupImageRGB) |
| `libiupimglib.a` | IUP built-in image set |

> **Note:** `include/` and `lib/` directories contain the complete IUP 3.32 distribution for Windows 64-bit. No separate IUP installation is required.
