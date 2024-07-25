#include "../include/MoveDownCommand.hpp"
#include "../include/Tank.hpp"

void MoveDownCommand::execute(Tank &tank) {
  tank.setRunning(true);
  tank.setSpeed((std::abs(tank.getSpeed())));
}
