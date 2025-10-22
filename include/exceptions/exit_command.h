#ifndef EXIT_COMMAND_H
#define EXIT_COMMAND_H

#include <exception>

class ExitCommand : public std::exception {
    const char *msg;

  public:
    ExitCommand(const char *message) : msg(message) {}
    const char *what() const noexcept override { return msg; }
};

#endif