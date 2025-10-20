#ifndef VISUAL_MODE_H
#define VISUAL_MODE_H

#include "../string.h"
#include "operating_mode.h"

class VisualMode : public OperatingMode {
  private:
    String name = "VISUAL";
    // FIXME: сделать свой контейнер вектора, где будут хранится команды

  public:
    VisualMode(Editor &editor) : OperatingMode(editor) {};
    ~VisualMode() = default;
    void exit() const override;
    void handle_input(String str) const override; // FIXME: здесь возвращать КОМАНДУ
};

#endif