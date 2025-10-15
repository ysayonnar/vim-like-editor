#ifndef COMMAND_MODE_H
#define COMMAND_MODE_H

#include "../string.h"
#include "operating_mode.h"

class CommandMode : public OperatingMode {
  private:
    String name = "Command";
    // FIXME: сделать свой контейнер вектора, где будут хранится команды

  public:
    void exit() const override;
    void handle_input() const override; // FIXME: здесь возвращать КОМАНДУ
    void execute_command() const override;
};

#endif