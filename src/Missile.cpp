#include "../include/Missile.hpp"

Missile::Missile(sf::Texture &texture, const sf::Vector2f &initialPosition,
                 float initialVelocity, sf::Vector2f direction)
    : Bullet(texture, initialPosition, initialVelocity, direction) {}

void Missile::handleCollision(const std::vector<Wall> &walls) {
  for (const Wall &wall : walls) {
    if (wall.getBounds().intersects(getBounds())) {
      if (bounces > 0) {
        if (wall.getBounds().width > wall.getBounds().height) {
          direction.y *= -1.f;
        } else {
          direction.x *= -1.f;
        }
        bounces--;
        return;
      } else {
        deactivate();
        return;
      }
    }
  }
}
