#ifndef SHOOT_2_COMMAND_HPP
#define SHOOT_2_COMMAND_HPP

#include "../include/Command.hpp"

class Shoot2Command : public Command {
public:
  void execute(Tank &tank) override;
};

#endif
