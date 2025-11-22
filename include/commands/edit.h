#ifndef EDIT_H
#define EDIT_H

#include "command.h"

class CutSymbol : public Command {
  public:
    CutSymbol(Editor &editor, String key_bind_pattern, bool is_cancelable) : Command(editor, key_bind_pattern, is_cancelable) {};
    ~CutSymbol() = default;

    void execute(String combination) const override;
    void undo() const override {};
};

class CutLine : public Command {
  public:
    CutLine(Editor &editor, String key_bind_pattern, bool is_cancelable) : Command(editor, key_bind_pattern, is_cancelable) {};
    ~CutLine() = default;

    void execute(String combination) const override;
    void undo() const override {};
};

class NewLineAfterAndInsert : public Command {
  public:
    NewLineAfterAndInsert(Editor &editor, String key_bind_pattern, bool is_cancelable) : Command(editor, key_bind_pattern, is_cancelable) {};
    ~NewLineAfterAndInsert() = default;

    void execute(String combination) const override;
    void undo() const override {};
};

class NewLineBeforeAndInsert : public Command {
  public:
    NewLineBeforeAndInsert(Editor &editor, String key_bind_pattern, bool is_cancelable) : Command(editor, key_bind_pattern, is_cancelable) {};
    ~NewLineBeforeAndInsert() = default;

    void execute(String combination) const override;
    void undo() const override {};
};

class SaveQuit : public Command {
  public:
    SaveQuit(Editor &editor, String key_bind_pattern, bool is_cancelable) : Command(editor, key_bind_pattern, is_cancelable) {};
    ~SaveQuit() = default;

    void execute(String combination) const override;
    void undo() const override {};
};

#endif