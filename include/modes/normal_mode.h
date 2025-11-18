#ifndef NORMAL_MODE_H
#define NORMAL_MODE_H

#include "../commands/basic_movement.h"
#include "../commands/command.h"
#include "../string.h"
#include "operating_mode.h"
#include <memory>
#include <vector>

class NormalMode : public OperatingMode {
  public:
    String name = "NORMAL";
    std::vector<std::unique_ptr<Command>> commands;

    NormalMode(Editor &editor) : OperatingMode(editor, true) {
        commands.push_back(std::make_unique<MoveLeft>(editor, "h", false));
        commands.push_back(std::make_unique<MoveRight>(editor, "l", false));
        commands.push_back(std::make_unique<MoveDown>(editor, "j", false));
        commands.push_back(std::make_unique<MoveUp>(editor, "k", false));
        commands.push_back(std::make_unique<MoveNextWord>(editor, "w", false));
        commands.push_back(std::make_unique<MovePrevWord>(editor, "b", false));
        commands.push_back(std::make_unique<MoveEndBuf>(editor, "G", false));
        commands.push_back(std::make_unique<MoveBeginBuf>(editor, "gg", false));
        commands.push_back(std::make_unique<MoveEndLine>(editor, "$", false));
        commands.push_back(std::make_unique<MoveBeginLine>(editor, "-", false));
    };
    ~NormalMode() = default;
    void exit() const override;
    void handle_input(String str) const override;
};

#endif