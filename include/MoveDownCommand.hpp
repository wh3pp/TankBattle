#ifndef MOVE_DOWN_COMMAND_HPP
#define MOVE_DOWN_COMMAND_HPP

#include "../include/Command.hpp"

class MoveDownCommand : public Command {
public:
  void execute(Tank &tank) override;
};

#endif
