#ifndef SHOOT_1_COMMAND_HPP
#define SHOOT_1_COMMAND_HPP

#include "../include/Command.hpp"

class Shoot1Command : public Command {
public:
  void execute(Tank &tank) override;
};

#endif
