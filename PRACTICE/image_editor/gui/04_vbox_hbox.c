#include <iup.h>
#include<stdio.h>

static int ok_action(Ihandle *self) {
    printf("OK clicked!\n");
    return IUP_DEFAULT;
}

static int cancel_action(Ihandle *self) {
    printf("Cancel clicked!\n");
    return IUP_DEFAULT;
}

int main(int argc, char **argv) {
    IupOpen(&argc , &argv);

    Ihandle *label = IupLabel("Enter name : ");
    Ihandle *text_box = IupText(NULL);

    IupSetAttribute(text_box , "EXPAND" , "HORIZONTAL");

    Ihandle *button_ok = IupButton("OK", NULL);
    Ihandle *button_cancel = IupButton("Cancel", NULL);

    IupSetCallback(button_ok, "ACTION", ok_action);
    IupSetCallback(button_cancel, "ACTION", cancel_action);

    Ihandle *button_row = IupHbox(
        IupFill(),
        button_ok,
        button_cancel,
        NULL
    );
    IupSetAttribute(button_row, "GAP",  "10");

    Ihandle *main_layout = IupVbox(
        label,
        text_box,
        button_row,
        NULL
    );

    IupSetAttribute(main_layout , "GAP", "10");
    IupSetAttribute(main_layout, "MARGIN","15x15");

    Ihandle *dlg = IupDialog(main_layout);

    IupSetAttribute(dlg, "TITLE", "Box Layout Example");
    IupSetAttribute(dlg, "RASTERSIZE", "320x180");

    IupShowXY(dlg, IUP_CENTER, IUP_CENTER);
    IupMainLoop();
    IupClose();

    return 0;
}