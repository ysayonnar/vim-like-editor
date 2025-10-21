#ifndef OPERATING_MODE_H
#define OPERATING_MODE_H

#include "../string.h"

class Editor;

class OperatingMode {
  public:
    Editor &editor;
    bool is_input_printable = false;

    OperatingMode(Editor &editor, bool is_input_printable) : editor(editor), is_input_printable(is_input_printable) {};
    virtual ~OperatingMode() = default;

    virtual void exit() const = 0;
    virtual void handle_input(String str) const = 0; // FIXME: здесь возвращать КОМАНДУ
};

// TODO: в классе каждой команды будет мой самописный шаблон вектора, где будyт хранится команды

#endif
