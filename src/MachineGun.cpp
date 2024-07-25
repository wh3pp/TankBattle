#include "../include/MachineGun.hpp"

MachineGun::MachineGun(sf::Texture &texture,
                       const sf::Vector2f &initialPosition,
                       float initialVelocity, sf::Vector2f direction)
    : Bullet(texture, initialPosition, initialVelocity, direction) {}

void MachineGun::handleCollision(const std::vector<Wall> &walls) {
  for (const Wall &wall : walls) {
    if (wall.getBounds().intersects(getBounds())) {
      deactivate();
      return;
    }
  }
}
