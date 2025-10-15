#ifndef NORMAL_MODE_H
#define NORMAL_MODE_H

#include "../string.h"
#include "operating_mode.h"

class NormalMode : public OperatingMode {
  private:
    String name = "NORMAL";
    // FIXME: сделать свой контейнер вектора, где будут хранится команды

  public:
    // FIXME: конструкторы и деструкторы
    void exit() const override;
    void handle_input() const override; // FIXME: здесь возвращать КОМАНДУ
    void execute_command() const override;
};

#endif