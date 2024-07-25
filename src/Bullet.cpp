#include "../include/Bullet.hpp"

Bullet::Bullet(sf::Texture &texture, const sf::Vector2f &initialPosition,
               float initialVelocity, sf::Vector2f direction)
    : speed(initialVelocity), active(true), direction(direction) {
  sprite.setTexture(texture);
  sprite.setPosition(initialPosition);
}

void Bullet::setRotation(float rotation) { sprite.setRotation(rotation); }
void Bullet::update(sf::Time dt, const std::vector<Wall> &walls) {
  if (!active)
    return;
  sprite.move(direction * speed * dt.asSeconds());
  handleCollision(walls);
}

void Bullet::draw(sf::RenderWindow &window) {
  if (active) {
    window.draw(sprite);
  }
}
sf::FloatRect Bullet::getBounds() const { return sprite.getGlobalBounds(); }
