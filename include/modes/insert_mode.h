#ifndef INSERT_MODE_H
#define INSERT_MODE_H

#include "../commands/change_mode.h"
#include "../commands/command.h"
#include "../string.h"
#include "operating_mode.h"
#include <memory>
#include <vector>

class InsertMode : public OperatingMode {
  private:
    String name = "INSERT";
    std::vector<std::unique_ptr<Command>> commands;

  public:
    InsertMode(Editor &editor) : OperatingMode(editor, false) {};
    ~InsertMode() = default;
    void exit() const override;
    void handle_input(String str) const override;
};

#endif