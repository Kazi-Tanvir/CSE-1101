#include <stdlib.h>
#include <iup.h>
#include "gui.h"

int main(int argc, char **argv) {
    IupOpen(&argc, &argv);

    Ihandle *dlg = build_main_gui();

    IupShowXY(dlg, IUP_CENTER, IUP_CENTER);

    IupMainLoop();

    cleanup_images();
    IupClose();
    return EXIT_SUCCESS;
}