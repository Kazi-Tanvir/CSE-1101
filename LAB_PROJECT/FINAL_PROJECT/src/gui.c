#include "gui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iupdraw.h>

static Image *current_image = NULL;
static Image *prev_image = NULL;
static Ihandle *canvas = NULL;
static Ihandle *status_bar = NULL;
static Ihandle *current_iup_img = NULL;
static const char *IMG_HANDLE_NAME = "GUI_ACTIVE_IMAGE";
static char loaded_filename[260] = "Untitled";

static void save_undo(void) {
    if (!current_image) return;
    if (prev_image) {
        free_image(prev_image);
        prev_image = NULL;
    }
    prev_image = clone_image(current_image);
}

static void undo(void) {
    if (!prev_image) return;
    if (current_image) {
        free_image(current_image);
    }
    current_image = prev_image;
    prev_image = NULL;
}

static void update_status(const char *action_msg) {
    if (!status_bar) return;
    if (current_image) {
        char buf[512];
        if (action_msg && strlen(action_msg) > 0) {
            snprintf(buf, sizeof(buf), " [%s]  File: %s | Dimensions: %d x %d px | 24-bit RGB",
                     action_msg, loaded_filename, current_image->width, current_image->height);
        } else {
            snprintf(buf, sizeof(buf), " File: %s | Dimensions: %d x %d px | 24-bit RGB",
                     loaded_filename, current_image->width, current_image->height);
        }
        IupSetStrAttribute(status_bar, "TITLE", buf);
    } else {
        IupSetStrAttribute(status_bar, "TITLE", " Ready. Please open a 24-bit BMP image.");
    }
}

static void update_display(const char *action_msg) {
    if (current_iup_img) {
        IupSetHandle((char*)IMG_HANDLE_NAME, NULL);
        IupDestroy(current_iup_img);
        current_iup_img = NULL;
    }

    if (current_image && current_image->data) {
        int width = current_image->width;
        int height = current_image->height;
        unsigned char *rgb = (unsigned char*)malloc(width * height * 3);
        if (rgb) {
            for (int i = 0; i < (width * height); i++) {
                rgb[i * 3 + 0] = current_image->data[i].r;
                rgb[i * 3 + 1] = current_image->data[i].g;
                rgb[i * 3 + 2] = current_image->data[i].b;
            }
            current_iup_img = IupImageRGB(width, height, rgb);
            free(rgb);

            if (current_iup_img) {
                IupSetHandle((char*)IMG_HANDLE_NAME, current_iup_img);
            }
        }
    }

    update_status(action_msg);

    if (canvas) {
        IupUpdate(canvas);
    }
}

static int canvas_action(Ihandle *ih, float posx, float posy) {
    (void)posx; (void)posy;
    IupDrawBegin(ih);

    int cw = 0, ch = 0;
    IupDrawGetSize(ih, &cw, &ch);

    IupSetAttribute(ih, "DRAWCOLOR", "30 33 39");
    IupSetAttribute(ih, "DRAWSTYLE", "FILL");
    IupDrawRectangle(ih, 0, 0, cw, ch);

    if (current_image && current_iup_img) {
        int iw = current_image->width;
        int ih_h = current_image->height;

        double scale = 1.0;
        int margin = 20;
        int avail_w = cw - margin * 2;
        int avail_h = ch - margin * 2;
        if (avail_w > 0 && avail_h > 0) {
            if (iw > avail_w || ih_h > avail_h) {
                double sx = (double)avail_w / (double)iw;
                double sy = (double)avail_h / (double)ih_h;
                scale = (sx < sy) ? sx : sy;
            }
        }

        int draw_w = (int)(iw * scale);
        int draw_h = (int)(ih_h * scale);
        if (draw_w < 1) draw_w = 1;
        if (draw_h < 1) draw_h = 1;

        int x = (cw - draw_w) / 2;
        int y = (ch - draw_h) / 2;
        if (x < 10) x = 10;
        if (y < 10) y = 10;

        IupSetAttribute(ih, "DRAWCOLOR", "18 20 24");
        IupSetAttribute(ih, "DRAWSTYLE", "STROKE");
        IupDrawRectangle(ih, x - 1, y - 1, x + draw_w, y + draw_h);

        IupDrawImage(ih, IMG_HANDLE_NAME, x, y, draw_w, draw_h);
    } else {
        const char *title = "CSE 1101 \xe2\x80\x94 Image Manipulation Software";
        const char *sub = "No image loaded. Click File > Open (Ctrl+O) or toolbar 'Open' to load a BMP image.";

        int tw = 0, th = 0;
        IupDrawGetTextSize(ih, title, 0, &tw, &th);
        int tx = (cw - tw) / 2;
        int ty = (ch / 2) - 20;
        if (tx < 10) tx = 10;
        if (ty < 10) ty = 10;

        IupSetAttribute(ih, "DRAWCOLOR", "225 228 234");
        IupDrawText(ih, title, 0, tx, ty, tw, th);

        int stw = 0, sth = 0;
        IupDrawGetTextSize(ih, sub, 0, &stw, &sth);
        int stx = (cw - stw) / 2;
        int sty = ty + th + 12;
        if (stx < 10) stx = 10;

        IupSetAttribute(ih, "DRAWCOLOR", "140 145 160");
        IupDrawText(ih, sub, 0, stx, sty, stw, sth);
    }

    IupDrawEnd(ih);
    return IUP_DEFAULT;
}

static int callback_file_open(Ihandle *self){
    (void)self;

    Ihandle *file_dlg = IupFileDlg();
    IupSetAttribute(file_dlg, "DIALOGTYPE", "OPEN");
    IupSetAttribute(file_dlg, "TITLE", "Open BMP Image");
    IupSetAttribute(file_dlg, "EXTFILTER", "BMP Images (*.bmp)|*.bmp|All Files (*.*)|*.*|");
    IupPopup(file_dlg, IUP_CENTER, IUP_CENTER);

    if (IupGetInt(file_dlg, "STATUS") != -1) {
        const char *filename = IupGetAttribute(file_dlg, "VALUE");
        if (filename && strlen(filename) > 0) {
            Image *new_img = load_bmp(filename);
            if (new_img) {
                if (current_image) free_image(current_image);
                if (prev_image) { free_image(prev_image); prev_image = NULL; }
                current_image = new_img;

                const char *base = strrchr(filename, '\\');
                if (!base) base = strrchr(filename, '/');
                if (base) base++; else base = filename;
                strncpy(loaded_filename, base, sizeof(loaded_filename) - 1);
                loaded_filename[sizeof(loaded_filename) - 1] = '\0';

                update_display("Image Opened");
            } else {
                IupMessage("Error", "Failed to load BMP image.\nPlease make sure it is an uncompressed 24-bit BMP file.");
            }
        }
    }

    IupDestroy(file_dlg);
    return IUP_DEFAULT;
}

static int callback_file_save(Ihandle *self){
    (void)self;

    if (!current_image) {
        IupMessage("Error", "No image loaded to save.");
        return IUP_DEFAULT;
    }

    Ihandle *file_dlg = IupFileDlg();
    IupSetAttribute(file_dlg, "DIALOGTYPE", "SAVE");
    IupSetAttribute(file_dlg, "TITLE", "Save Image As BMP");
    IupSetAttribute(file_dlg, "EXTFILTER", "BMP Images (*.bmp)|*.bmp|All Files (*.*)|*.*|");
    IupSetAttribute(file_dlg, "FILE", loaded_filename);
    IupPopup(file_dlg, IUP_CENTER, IUP_CENTER);

    if (IupGetInt(file_dlg, "STATUS") != -1) {
        const char *filename = IupGetAttribute(file_dlg, "VALUE");
        if (filename && strlen(filename) > 0) {
            if (save_bmp(filename, current_image)) {
                const char *base = strrchr(filename, '\\');
                if (!base) base = strrchr(filename, '/');
                if (base) base++; else base = filename;
                strncpy(loaded_filename, base, sizeof(loaded_filename) - 1);
                loaded_filename[sizeof(loaded_filename) - 1] = '\0';

                update_status("Image Saved");
                IupMessage("Success", "Image saved successfully!");
            } else {
                IupMessage("Error", "Failed to save image file.");
            }
        }
    }

    IupDestroy(file_dlg);
    return IUP_DEFAULT;
}

static int callback_grayscale(Ihandle *self){
    (void)self;
    if (!current_image) { IupMessage("Error", "No image loaded."); return IUP_DEFAULT; }
    save_undo();
    grayscale(current_image);
    update_display("Grayscale Filter");
    return IUP_DEFAULT;
}

static int callback_inversion(Ihandle *self){
    (void)self;
    if (!current_image) { IupMessage("Error", "No image loaded."); return IUP_DEFAULT; }
    save_undo();
    inversion(current_image);
    update_display("Invert Colors");
    return IUP_DEFAULT;
}

static int callback_horizontalFlip(Ihandle *self){
    (void)self;
    if (!current_image) { IupMessage("Error", "No image loaded."); return IUP_DEFAULT; }
    save_undo();
    horizontalFlip(current_image);
    update_display("Horizontal Flip");
    return IUP_DEFAULT;
}

static int callback_verticalFlip(Ihandle *self){
    (void)self;
    if (!current_image) { IupMessage("Error", "No image loaded."); return IUP_DEFAULT; }
    save_undo();
    verticalFlip(current_image);
    update_display("Vertical Flip");
    return IUP_DEFAULT;
}

static int callback_blur(Ihandle *self){
    (void)self;
    if (!current_image) { IupMessage("Error", "No image loaded."); return IUP_DEFAULT; }
    save_undo();
    Image *new_img = blur(current_image);
    if (new_img) {
        free_image(current_image);
        current_image = new_img;
        update_display("Blur Filter");
    }
    return IUP_DEFAULT;
}

static int callback_sharpen(Ihandle *self){
    (void)self;
    if (!current_image) { IupMessage("Error", "No image loaded."); return IUP_DEFAULT; }
    save_undo();
    Image *new_img = sharpen(current_image);
    if (new_img) {
        free_image(current_image);
        current_image = new_img;
        update_display("Sharpen Filter");
    }
    return IUP_DEFAULT;
}

static int callback_rotate90(Ihandle *self){
    (void)self;
    if (!current_image) { IupMessage("Error", "No image loaded."); return IUP_DEFAULT; }
    save_undo();
    Image *new_img = rotate90(current_image);
    if (new_img) {
        free_image(current_image);
        current_image = new_img;
        update_display("Rotate 90\xc2\xb0 CW");
    }
    return IUP_DEFAULT;
}

static int callback_undo(Ihandle *self){
    (void)self;
    if (!prev_image) {
        IupMessage("Info", "Nothing to undo.");
        return IUP_DEFAULT;
    }
    undo();
    update_display("Undo Action");
    return IUP_DEFAULT;
}

static int callback_crop(Ihandle *self){
    (void)self;
    if (!current_image) {
        IupMessage("Error", "No image loaded.");
        return IUP_DEFAULT;
    }

    int max_x = current_image->width - 1;
    int max_y = current_image->height - 1;
    int x1 = 0, y1 = 0;
    int x2 = max_x;
    int y2 = max_y;

    char fmt[256];
    snprintf(fmt, sizeof(fmt),
             "X1 (Left) [0,%d]: %%i\n"
             "Y1 (Top) [0,%d]: %%i\n"
             "X2 (Right) [0,%d]: %%i\n"
             "Y2 (Bottom) [0,%d]: %%i\n",
             max_x, max_y, max_x, max_y);

    if (!IupGetParam("Crop Image Coordinates", NULL, NULL,
                     fmt,
                     &x1, &y1, &x2, &y2, NULL)) {
        return IUP_DEFAULT;
    }

    if (x1 < 0 || y1 < 0 || x2 > max_x || y2 > max_y || x1 > x2 || y1 > y2) {
        IupMessage("Error", "Invalid crop coordinates. Please ensure X1 <= X2 and Y1 <= Y2 within image bounds.");
        return IUP_DEFAULT;
    }

    save_undo();
    Image *cropped = crop(current_image, x1, y1, x2, y2);
    if (cropped) {
        free_image(current_image);
        current_image = cropped;
        update_display("Crop Image");
    } else {
        IupMessage("Error", "Crop operation failed.");
    }
    return IUP_DEFAULT;
}

static int callback_brightness(Ihandle *self){
    (void)self;
    if (!current_image) {
        IupMessage("Error", "No image loaded.");
        return IUP_DEFAULT;
    }

    int level = 0;
    if (!IupGetParam("Adjust Brightness", NULL, NULL,
                    "Brightness level (-255 to 255): %i\n",
                    &level, NULL)) {
        return IUP_DEFAULT;
    }

    if (level < -255 || level > 255) {
        IupMessage("Error", "Invalid brightness value. Must be between -255 and 255.");
        return IUP_DEFAULT;
    }

    save_undo();
    brightness(current_image, level);
    update_display("Brightness Adjusted");
    return IUP_DEFAULT;
}

static int callback_exit(Ihandle *self){
    (void)self;
    return IUP_CLOSE;
}

void cleanup_images(void){
    if (current_iup_img) {
        IupSetHandle((char*)IMG_HANDLE_NAME, NULL);
        IupDestroy(current_iup_img);
        current_iup_img = NULL;
    }
    if (current_image) {
        free_image(current_image);
        current_image = NULL;
    }
    if (prev_image) {
        free_image(prev_image);
        prev_image = NULL;
    }
}

Ihandle* build_main_gui(void){
    canvas = IupCanvas(NULL);
    IupSetAttribute(canvas, "EXPAND", "YES");
    IupSetAttribute(canvas, "CANVASBOX", "YES");
    IupSetCallback(canvas, "ACTION", (Icallback)(void*)canvas_action);

    status_bar = IupLabel(" Ready. Please open a 24-bit BMP image.");
    IupSetAttribute(status_bar, "EXPAND", "HORIZONTAL");
    IupSetAttribute(status_bar, "PADDING", "6x4");

    Ihandle *item_open = IupItem("Open\tCtrl+O", NULL);
    Ihandle *item_save = IupItem("Save As...\tCtrl+S", NULL);
    Ihandle *item_exit = IupItem("Exit\tAlt+F4", NULL);

    IupSetCallback(item_open, "ACTION", (Icallback)callback_file_open);
    IupSetCallback(item_save, "ACTION", (Icallback)callback_file_save);
    IupSetCallback(item_exit, "ACTION", (Icallback)callback_exit);

    Ihandle *menu_file = IupMenu(
        item_open,
        item_save,
        IupSeparator(),
        item_exit,
        NULL
    );

    Ihandle *item_undo = IupItem("Undo\tCtrl+Z", NULL);
    IupSetCallback(item_undo, "ACTION", (Icallback)callback_undo);

    Ihandle *menu_edit = IupMenu(
        item_undo,
        NULL
    );

    Ihandle *item_grayscale      = IupItem("Grayscale", NULL);
    Ihandle *item_brightness     = IupItem("Brightness...", NULL);
    Ihandle *item_inversion      = IupItem("Invert Colors", NULL);
    Ihandle *item_horizontalFlip = IupItem("Horizontal Flip", NULL);
    Ihandle *item_verticalFlip   = IupItem("Vertical Flip", NULL);
    Ihandle *item_rotate90       = IupItem("Rotate 90\xc2\xb0 CW", NULL);
    Ihandle *item_crop           = IupItem("Crop...", NULL);
    Ihandle *item_blur           = IupItem("Blur (Smooth)", NULL);
    Ihandle *item_sharpen        = IupItem("Sharpen", NULL);

    IupSetCallback(item_grayscale,      "ACTION", (Icallback)callback_grayscale);
    IupSetCallback(item_brightness,     "ACTION", (Icallback)callback_brightness);
    IupSetCallback(item_inversion,      "ACTION", (Icallback)callback_inversion);
    IupSetCallback(item_horizontalFlip, "ACTION", (Icallback)callback_horizontalFlip);
    IupSetCallback(item_verticalFlip,   "ACTION", (Icallback)callback_verticalFlip);
    IupSetCallback(item_rotate90,       "ACTION", (Icallback)callback_rotate90);
    IupSetCallback(item_crop,           "ACTION", (Icallback)callback_crop);
    IupSetCallback(item_blur,           "ACTION", (Icallback)callback_blur);
    IupSetCallback(item_sharpen,        "ACTION", (Icallback)callback_sharpen);

    Ihandle *menu_filters = IupMenu(
        item_grayscale,
        item_brightness,
        item_inversion,
        IupSeparator(),
        item_horizontalFlip,
        item_verticalFlip,
        item_rotate90,
        IupSeparator(),
        item_crop,
        item_blur,
        item_sharpen,
        NULL
    );

    Ihandle *menu_bar = IupMenu(
        IupSubmenu("File", menu_file),
        IupSubmenu("Edit", menu_edit),
        IupSubmenu("Image", menu_filters),
        NULL
    );

    /* ── Toolbar buttons ── */
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

    IupSetAttribute(btn_open,   "TIP", "Open a BMP image file (Ctrl+O)");
    IupSetAttribute(btn_save,   "TIP", "Save current image as BMP (Ctrl+S)");
    IupSetAttribute(btn_undo,   "TIP", "Undo last filter/operation (Ctrl+Z)");
    IupSetAttribute(btn_gray,   "TIP", "Convert to Grayscale");
    IupSetAttribute(btn_bright, "TIP", "Adjust Brightness");
    IupSetAttribute(btn_invert, "TIP", "Invert Colors");
    IupSetAttribute(btn_hflip,  "TIP", "Flip Horizontally");
    IupSetAttribute(btn_vflip,  "TIP", "Flip Vertically");
    IupSetAttribute(btn_rotate, "TIP", "Rotate 90 Degrees Clockwise");
    IupSetAttribute(btn_crop,   "TIP", "Crop Image");
    IupSetAttribute(btn_blur,   "TIP", "Apply 3x3 Box Blur");
    IupSetAttribute(btn_sharp,  "TIP", "Apply Sharpen Filter");

    IupSetCallback(btn_open,   "ACTION", (Icallback)callback_file_open);
    IupSetCallback(btn_save,   "ACTION", (Icallback)callback_file_save);
    IupSetCallback(btn_undo,   "ACTION", (Icallback)callback_undo);
    IupSetCallback(btn_gray,   "ACTION", (Icallback)callback_grayscale);
    IupSetCallback(btn_bright, "ACTION", (Icallback)callback_brightness);
    IupSetCallback(btn_invert, "ACTION", (Icallback)callback_inversion);
    IupSetCallback(btn_hflip,  "ACTION", (Icallback)callback_horizontalFlip);
    IupSetCallback(btn_vflip,  "ACTION", (Icallback)callback_verticalFlip);
    IupSetCallback(btn_rotate, "ACTION", (Icallback)callback_rotate90);
    IupSetCallback(btn_crop,   "ACTION", (Icallback)callback_crop);
    IupSetCallback(btn_blur,   "ACTION", (Icallback)callback_blur);
    IupSetCallback(btn_sharp,  "ACTION", (Icallback)callback_sharpen);

    Ihandle *toolbar = IupHbox(
        btn_open,
        btn_save,
        btn_undo,
        IupFill(),
        btn_gray,
        btn_bright,
        btn_invert,
        btn_hflip,
        btn_vflip,
        btn_rotate,
        btn_crop,
        btn_blur,
        btn_sharp,
        NULL
    );

    IupSetAttribute(toolbar, "GAP", "6");
    IupSetAttribute(toolbar, "MARGIN", "6x4");

    Ihandle *vbox = IupVbox(
        toolbar,
        canvas,
        status_bar,
        NULL
    );

    Ihandle *dialog = IupDialog(vbox);
    IupSetAttribute(dialog, "TITLE", "CSE 1101 \xe2\x80\x94 Image Manipulation Software");
    IupSetAttribute(dialog, "RASTERSIZE", "900x700");
    IupSetAttribute(dialog, "SHRINK", "NO");
    IupSetAttributeHandle(dialog, "MENU", menu_bar);

    return dialog;
}