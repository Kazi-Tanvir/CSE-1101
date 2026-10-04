#include<iup.h>
#include<stdio.h>

static int msgfunc(Ihandle *self){
    (void)self;
    IupMessage("Hi","Hello from callback!");
    return IUP_DEFAULT;
}

int main(int argc , char **argv){
    IupOpen(&argc, &argv);
    
    Ihandle *lbl = IupLabel("Hello, Iup!");
    Ihandle *btn = IupButton("Say Hi !",NULL);
    Ihandle *hbox = IupHbox(lbl,IupFill(),btn,NULL);
    Ihandle *dlg = IupDialog(hbox);

    IupSetCallback(btn,"ACTION",msgfunc);

    IupSetAttribute(dlg, "RASTERSIZE", "400x200");
    IupSetAttribute(dlg, "TITLE", "My First Window");
    IupShowXY(dlg,IUP_CENTER,IUP_CENTER);

    IupMainLoop();
    IupClose();

    return 0;
}