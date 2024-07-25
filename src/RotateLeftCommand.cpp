#include "../include/RotateLeftCommand.hpp"
#include "../include/Tank.hpp"

void RotateLeftCommand::execute(Tank &tank) {
  tank.setRotationBool(true, false);
}
