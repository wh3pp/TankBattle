#ifndef MACHINEGUN_HPP
#define MACHINEGUN_HPP

#include "Bullet.hpp"

class MachineGun : public Bullet {
public:
  MachineGun(sf::Texture &texture, const sf::Vector2f &initialPosition,
             float initialVelocity, sf::Vector2f direction);
  void handleCollision(const std::vector<Wall> &walls) override;
};

#endif
