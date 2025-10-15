#ifndef COMMAND_H
#define COMMAND_H

#include "../string.h"
#include "editor.h"

class Command {
  private:
    Editor &editor;
    String key_bind;

  public:
    virtual void execute() const = 0;
    virtual void undo() const = 0;
    virtual String get_name() const = 0;
};

#endif