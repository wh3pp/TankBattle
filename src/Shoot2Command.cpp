#include "../include/Shoot2Command.hpp"
#include "../include/Tank.hpp"

void Shoot2Command::execute(Tank &tank) {
  tank.fireBullet("missile", tank.getMissileTexture());
}
