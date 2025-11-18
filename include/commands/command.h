#ifndef COMMAND_H
#define COMMAND_H

#include "../string.h"

class Editor;

class Command {
  protected:
    Editor &editor;

  public:
    String key_bind_pattern;
    bool is_cancelable;

    Command(Editor &editor, String key_bind_pattern, bool is_cancelable) : editor(editor), key_bind_pattern(key_bind_pattern), is_cancelable(is_cancelable) {};
    virtual ~Command() = default;

    virtual void execute(String combination) const = 0;
    virtual void undo() const = 0;
};

#endif
