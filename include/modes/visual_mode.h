#ifndef VISUAL_MODE_H
#define VISUAL_MODE_H

#include "../string.h"
#include "operating_mode.h"

class VisualMode : public OperatingMode {
  private:
    String name = "VISUAL";
    // FIXME: сделать свой контейнер вектора, где будут хранится команды

  public:
    // FIXME: конструкторы и деструкторы
    void exit() const override;
    void handle_input() const override; // FIXME: здесь возвращать КОМАНДУ
    void execute_command() const override;
};

#endif