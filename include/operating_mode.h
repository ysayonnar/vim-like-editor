#ifndef OPERATING_MODES_H
#define OPERATING_MODES_H

#include "editor.h"

class OperatingMode {
  private:
    Editor &editor;

  public:
    OperatingMode(Editor &editor) : editor(editor) {};
    ~OperatingMode() = default;

    virtual void exit() const = 0;
    virtual void handle_input() const = 0; // NOTE: здесь возвращать КОМАНДУ
    virtual void execute_command() const = 0;
};

// в классе каждой команды будет мой самописный шаблон вектора, где будyт хранится команды

#endif
