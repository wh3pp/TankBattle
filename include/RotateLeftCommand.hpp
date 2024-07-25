#ifndef ROTATE_LEFT_COMMAND_HPP
#define ROTATE_LEFT_COMMAND_HPP

#include "../include/Command.hpp"

class RotateLeftCommand : public Command {
public:
  void execute(Tank &tank) override;
};

#endif
