#include <iup.h>
#include<stdio.h>

int main(int argc, char **argv) {
    IupOpen(&argc, &argv);

    Ihandle *label = IupLabel("Hello, World!");
    // Ihandle *hbox = IupHbox(label, NULL);

    Ihandle *dlg = IupDialog(label);
    IupSetAttribute(dlg, "TITLE", "My First IUP App");
    IupSetAttribute(dlg, "SIZE", "400x200");

    IupShowXY(dlg, IUP_CENTER, IUP_CENTER); 
    IupMainLoop();

    IupDestroy(dlg);
    IupClose();
    return 0;
}
