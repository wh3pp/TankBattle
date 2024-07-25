#include "../include/MoveUpCommand.hpp"
#include "../include/Tank.hpp"

void MoveUpCommand::execute(Tank &tank) {
  tank.setRunning(true);
  tank.setSpeed(-(std::abs(tank.getSpeed())));
}
