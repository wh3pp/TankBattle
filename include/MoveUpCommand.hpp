#ifndef MOVE_UP_COMMAND_HPP
#define MOVE_UP_COMMAND_HPP

#include "../include/Command.hpp"

class MoveUpCommand : public Command {
public:
  void execute(Tank &tank) override;
};

#endif
