#include<iup.h>
#include<stdio.h>

static int buttonClick(Ihandle *self){
    (void)self;
    printf("Button clicked!\n");
    return IUP_DEFAULT;
}

int main(int argc, char **argv){
    IupOpen(&argc, &argv);
    
    Ihandle *btn = IupButton("Click Me", NULL);
    IupSetCallback(btn, "ACTION", buttonClick);

    Ihandle *dlg = IupDialog(btn);
    IupSetAttribute(dlg, "TITLE", "My First IUP App");
    IupSetAttribute(dlg, "SIZE", "400x200");

    IupShowXY(dlg, IUP_CENTER, IUP_CENTER);
    IupMainLoop();

    IupDestroy(dlg);
    IupClose();
    return 0;
}