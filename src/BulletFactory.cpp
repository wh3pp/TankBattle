#include "../include/BulletFactory.hpp"
#include "../include/MachineGun.hpp"
#include "../include/Missile.hpp"

std::unique_ptr<Bullet>
BulletFactory::createBullet(const std::string &type, sf::Texture &texture,
                            const sf::Vector2f &position, float velocity,
                            sf::Vector2f direction) {
  if (type == "missile") {
    return std::make_unique<Missile>(texture, position, velocity, direction);
  } else if (type == "machinegun") {
    return std::make_unique<MachineGun>(texture, position, velocity, direction);
  }
  return nullptr;
}
