#ifndef COMMAND_H
#define COMMAND_H

#include "../string.h"
#include "editor.h"

class Command {
  private:
    Editor &editor;
    String key_bind_pattern;
    bool is_cancelable;

  public:
    Command(Editor &editor, String key_bind_pattern, bool is_cancelable) : editor(editor), key_bind_pattern(key_bind_pattern), is_cancelable(is_cancelable) {};
    ~Command() = default;

    virtual void execute(String combination) const = 0;
    virtual void undo() const = 0;
    virtual String get_name() const = 0;
};

#endif