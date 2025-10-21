#ifndef UNKNOWN_COMMAND_H
#define UNKNOWN_COMMAND_H

#include <exception>

class UnknownCommand : public std::exception {
    const char *msg;

  public:
    UnknownCommand(const char *message) : msg(message) {}
    const char *what() const noexcept override { return msg; }
};

#endif