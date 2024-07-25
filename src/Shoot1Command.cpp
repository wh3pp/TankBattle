#include "../include/Shoot1Command.hpp"
#include "../include/Tank.hpp"

void Shoot1Command::execute(Tank &tank) {
  tank.fireBullet("machinegun", tank.getMachinegunTexture());
}
