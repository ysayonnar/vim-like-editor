#include "../include/editor.h"
#include "../include/exceptions/exit_command.h"
#include "../include/exceptions/unknown_command.h"
#include "../include/external/colors.h"
#include "../include/external/conio.h"
#include <iomanip>
#include <stdexcept>
#include <sys/ioctl.h>

void Editor::run() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    if (w.ws_col < 60 || w.ws_row < 5) {
        throw std::out_of_range("terminal size is too small");
    }

    bool isExit = false;
    while (!isExit) {
        render();

        while (true) {
            char c = getch();
            command_input += c;
            print_toolbar();

            try {
                operating_mode->handle_input(command_input);
            } catch (const UnknownCommand &err) {
                continue;
            } catch (const ExitCommand &err) {
                isExit = true;
            }

            break;
        }

        command_input = "";
    }
}

void Editor::render() {
    clear_screen();
    std::cout << buf << std::endl;
    print_toolbar();
}

void Editor::clear_screen() {
    std::cout << "\033[2J\033[H";
}

void Editor::print_toolbar() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    std::cout << "\033[" << w.ws_row << ";1H";
    std::cout << CLEAR_LINE;

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

    if (command_input.get_length() > 10) {
        std::cout << " command prompt: " << std::setw(10) << command_input(0, 10);
    } else {
        std::cout << " command prompt: " << std::setw(10) << command_input;
    }
    std::cout << " " << filename;

    // TODO:  выводить номер строки и тп
}