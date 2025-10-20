#ifndef NORMAL_MODE_H
#define NORMAL_MODE_H

#include "../string.h"
#include "operating_mode.h"

class NormalMode : public OperatingMode {
  private:
    String name = "NORMAL";
    // FIXME: сделать свой контейнер вектора, где будут хранится команды

  public:
    NormalMode(Editor &editor) : OperatingMode(editor) {};
    ~NormalMode() = default;
    void exit() const override;
    void handle_input(String str) const override; // FIXME: здесь возвращать КОМАНДУ
};

#endif