#ifndef MISSILE_HPP
#define MISSILE_HPP

#include "Bullet.hpp"

class Missile : public Bullet {
  int bounces = 4;

public:
  Missile(sf::Texture &texture, const sf::Vector2f &initialPosition,
          float initialVelocity, sf::Vector2f direction);
  void handleCollision(const std::vector<Wall> &walls) override;
};

#endif
