#ifndef BULLET_FACTORY_HPP
#define BULLET_FACTORY_HPP

#include "Bullet.hpp"
#include <memory>

class BulletFactory {
public:
  static std::unique_ptr<Bullet> createBullet(const std::string &type,
                                              sf::Texture &texture,
                                              const sf::Vector2f &position,
                                              float velocity,
                                              sf::Vector2f direction);
};

#endif
