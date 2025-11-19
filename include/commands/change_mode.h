#ifndef CHANGE_MODE_H
#define CHANGE_MODE_H

#include "command.h"

class ChangeToNormalMode : public Command {
  public:
    ChangeToNormalMode(Editor &editor, String key_bind_pattern, bool is_cancelable) : Command(editor, key_bind_pattern, is_cancelable) {};
    ~ChangeToNormalMode() = default;

    void execute(String combination) const override;
    void undo() const override {};
};

class ChangeToInsertMode : public Command {
  public:
    ChangeToInsertMode(Editor &editor, String key_bind_pattern, bool is_cancelable) : Command(editor, key_bind_pattern, is_cancelable) {};
    ~ChangeToInsertMode() = default;

    void execute(String combination) const override;
    void undo() const override {};
};

class ChangeToVisualMode : public Command {
  public:
    ChangeToVisualMode(Editor &editor, String key_bind_pattern, bool is_cancelable) : Command(editor, key_bind_pattern, is_cancelable) {};
    ~ChangeToVisualMode() = default;

    void execute(String combination) const override;
    void undo() const override {};
};

#endif