#ifndef INSERT_MODE_H
#define INSERT_MODE_H

#include "../string.h"
#include "operating_mode.h"

class InsertMode : public OperatingMode {
  private:
    String name = "INSERT";
    // FIXME: сделать свой контейнер вектора, где будут хранится команды

  public:
    InsertMode(Editor &editor) : OperatingMode(editor) {};
    ~InsertMode() = default;
    void exit() const override;
    void handle_input(String str) const override; // FIXME: здесь возвращать КОМАНДУ
};

#endif