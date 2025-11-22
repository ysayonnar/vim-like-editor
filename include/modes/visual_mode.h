#ifndef VISUAL_MODE_H
#define VISUAL_MODE_H

#include "../commands/change_mode.h"
#include "../commands/command.h"
#include "../string.h"
#include "operating_mode.h"
#include <memory>
#include <vector>

class VisualMode : public OperatingMode {
  private:
    String name = "VISUAL";
    std::vector<std::unique_ptr<Command>> commands;
    bool line_mode = false;

  public:
    VisualMode(Editor &editor, bool line_mode = false);
    ~VisualMode() = default;
    void exit() const override;
    void handle_input(String str) const override;
};

#endif