
#ifndef BULLET_HPP
#define BULLET_HPP

#include "Wall.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

class Bullet {
protected:
  sf::Sprite sprite;
  float speed;
  sf::Vector2f direction;
  bool active;

public:
  Bullet(sf::Texture &texture, const sf::Vector2f &initialPosition,
         float initialVelocity, sf::Vector2f direction);
  virtual void update(sf::Time dt, const std::vector<Wall> &walls);
  void draw(sf::RenderWindow &window);
  sf::FloatRect getBounds() const;
  virtual void handleCollision(const std::vector<Wall> &walls) = 0;
  bool isActive() const { return active; }
  void deactivate() { active = false; }
  void setRotation(float rotation);
};

#endif
