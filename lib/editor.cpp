#include "../include/editor.h"
#include "../include/external/colors.h"
#include "../include/external/conio.h"
#include <sys/ioctl.h>

void Editor::run() {
    clear_screen();
    String input("");

    while (true) {
        render();

        char c = getch();
        input += c;

        operating_mode->handle_input(input);

        // TODO: проверять найдена ли команда
        input = "";
    }
}

void Editor::render() {
    std::cout << CURSOR_HOME;
    std::cout << "\r" << buf << std::endl;
    print_toolbar();
}

void Editor::clear_screen() {
    std::cout << CLEAR_SCREEN;
}

void Editor::print_toolbar() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    std::cout << "\033[" << w.ws_row << ";1H";

    if (NormalMode *mode = dynamic_cast<NormalMode *>(operating_mode)) {
        std::cout << COLOR_BG_BRIGHT_BLUE << COLOR_BLACK << " NORMAL " << COLOR_RESET;
    }
    if (VisualMode *mode = dynamic_cast<VisualMode *>(operating_mode)) {
        std::cout << COLOR_BG_BRIGHT_MAGENTA << COLOR_BLACK << " VISUAL " << COLOR_RESET;
    }
    if (InsertMode *mode = dynamic_cast<InsertMode *>(operating_mode)) {
        std::cout << COLOR_BG_BRIGHT_GREEN << COLOR_BLACK << " INSERT " << COLOR_RESET;
    }
    if (CommandMode *mode = dynamic_cast<CommandMode *>(operating_mode)) {
        std::cout << COLOR_BG_BRIGHT_CYAN << COLOR_BLACK << " COMMAND " << COLOR_RESET;
    }

    // TODO:  выводить номер строки и тп
}