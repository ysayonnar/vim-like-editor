#ifndef OPERATING_MODE_H
#define OPERATING_MODE_H

#include "editor.h"

class OperatingMode {
  protected:
    Editor &editor;

  public:
    OperatingMode(Editor &editor) : editor(editor) {};
    ~OperatingMode() = default;

    virtual void exit() const = 0;
    virtual void handle_input() const = 0; // FIXME: здесь возвращать КОМАНДУ
    virtual void execute_command() const = 0;
};

// TODO: в классе каждой команды будет мой самописный шаблон вектора, где будyт хранится команды

#endif
