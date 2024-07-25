#include "../include/RotateRightCommand.hpp"
#include "../include/Tank.hpp"

void RotateRightCommand::execute(Tank &tank) {
  tank.setRotationBool(false, true);
}
