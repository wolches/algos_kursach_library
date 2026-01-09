#include <regex>

#include "app/ui/library_ui.h"
#include <windows.h>
#include <io.h>
#include <fcntl.h>

#include "app/ui/io.h"

int main() {
    system("chcp 65001 > nul");
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    setbuf(stdout, 0);
    SetConsoleOutputCP(CP_UTF8);
    library_ui ui;
    int status = ui.run();
    return status;
}