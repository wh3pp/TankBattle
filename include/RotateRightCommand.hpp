#ifndef ROTATE_RIGHT_COMMAND_HPP
#define ROTATE_RIGHT_COMMAND_HPP

#include "../include/Command.hpp"

class RotateRightCommand : public Command {
public:
  void execute(Tank &tank) override;
};

#endif
