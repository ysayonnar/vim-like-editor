#ifndef BASIC_MOVEMENT_H
#define BASIC_MOVEMENT_H

#include "command.h"

class MoveLeft : public Command {
  public:
    MoveLeft(Editor &editor, String key_bind_pattern, bool is_cancelable) : Command(editor, key_bind_pattern, is_cancelable) {};
    ~MoveLeft() = default;

    void execute(String combination) const override;
    void undo() const override {};
};

class MoveRight : public Command {
  public:
    MoveRight(Editor &editor, String key_bind_pattern, bool is_cancelable) : Command(editor, key_bind_pattern, is_cancelable) {};
    ~MoveRight() = default;

    void execute(String combination) const override;
    void undo() const override {};
};

class MoveUp : public Command {
  public:
    MoveUp(Editor &editor, String key_bind_pattern, bool is_cancelable) : Command(editor, key_bind_pattern, is_cancelable) {};
    ~MoveUp() = default;

    void execute(String combination) const override;
    void undo() const override {};
};

class MoveDown : public Command {
  public:
    MoveDown(Editor &editor, String key_bind_pattern, bool is_cancelable) : Command(editor, key_bind_pattern, is_cancelable) {};
    ~MoveDown() = default;

    void execute(String combination) const override;
    void undo() const override {};
};
class MoveNextWord : public Command {
  public:
    MoveNextWord(Editor &editor, String key_bind_pattern, bool is_cancelable) : Command(editor, key_bind_pattern, is_cancelable) {};
    ~MoveNextWord() = default;

    void execute(String combination) const override;
    void undo() const override {};
};

class MovePrevWord : public Command {
  public:
    MovePrevWord(Editor &editor, String key_bind_pattern, bool is_cancelable) : Command(editor, key_bind_pattern, is_cancelable) {};
    ~MovePrevWord() = default;

    void execute(String combination) const override;
    void undo() const override {};
};

class MoveBeginBuf : public Command {
  public:
    MoveBeginBuf(Editor &editor, String key_bind_pattern, bool is_cancelable) : Command(editor, key_bind_pattern, is_cancelable) {};
    ~MoveBeginBuf() = default;

    void execute(String combination) const override;
    void undo() const override {};
};

class MoveEndBuf : public Command {
  public:
    MoveEndBuf(Editor &editor, String key_bind_pattern, bool is_cancelable) : Command(editor, key_bind_pattern, is_cancelable) {};
    ~MoveEndBuf() = default;

    void execute(String combination) const override;
    void undo() const override {};
};

class MoveBeginLine : public Command {
  public:
    MoveBeginLine(Editor &editor, String key_bind_pattern, bool is_cancelable) : Command(editor, key_bind_pattern, is_cancelable) {};
    ~MoveBeginLine() = default;

    void execute(String combination) const override;
    void undo() const override {};
};

class MoveEndLine : public Command {
  public:
    MoveEndLine(Editor &editor, String key_bind_pattern, bool is_cancelable) : Command(editor, key_bind_pattern, is_cancelable) {};
    ~MoveEndLine() = default;

    void execute(String combination) const override;
    void undo() const override {};
};

int extract_num(String str);

#endif