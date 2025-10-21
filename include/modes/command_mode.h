#ifndef COMMAND_MODE_H
#define COMMAND_MODE_H

#include "../string.h"
#include "operating_mode.h"

class CommandMode : public OperatingMode {
  private:
    String name = "Command";
    // FIXME: сделать свой контейнер вектора, где будут хранится команды

  public:
    CommandMode(Editor &editor) : OperatingMode(editor, true) {};
    ~CommandMode() = default;
    void exit() const override;
    void handle_input(String str) const override; // FIXME: здесь возвращать КОМАНДУ
};

#endif