#include "../include/modes/normal_mode.h"
#include "../include/editor.h"
#include "../include/exceptions/exit_command.h"
#include "../include/exceptions/unknown_command.h"
#include "../include/string.h"
#include <cctype>
#include <iostream>

bool compare_commands(String command, String pattern) {
    int idx = 0;

    while (idx < command.get_length() && std::isdigit(command[idx])) {
        idx++;
    }

    if (idx + pattern.get_length() != command.get_length())
        return false;

    for (int i = 0; i < pattern.get_length(); i++) {
        if (command[idx + i] != pattern[i]) {
            return false;
        }
    }

    return true;
}

void NormalMode::exit() const {
    // TODO: placeholder implementation
    std::cout << "Exiting NORMAL mode" << std::endl;
}

void NormalMode::handle_input(String str) const {
    char last_symbol = str[str.get_length() - 1];
    if (last_symbol < 32) {
        editor.command_input = "";
        return;
    } else if (std::isdigit(last_symbol)) {
        throw UnknownCommand("bad pattern");
    }

    bool is_executed = false;
    for (int i = 0; i < commands.size(); i++) {
        if (compare_commands(str, commands[i]->key_bind_pattern)) {
            commands[i]->execute(str);
            is_executed = true;
            break;
        }
    }

    if (!is_executed) {
        // editor.command_input = "";
        throw UnknownCommand("bad command pattern");
    }
}