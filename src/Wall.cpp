#include "../include/Wall.hpp"

void Wall::setPosition(const sf::Vector2f &position) {
  this->position = position;
  rect.setPosition(position);
}

void Wall::setSize(const sf::Vector2f &size) {
  this->size = size;
  rect.setSize(size);
}

void Wall::setTexture(sf::Texture &texture) {
  rect.setTexture(&texture);
  if (getSize().x > getSize().y) {
    rect.setTextureRect(
        sf::IntRect(0, 0, texture.getSize().y, texture.getSize().x));
  } else {
    rect.setTextureRect(
        sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
  }
}

sf::Vector2f Wall::getPosition() const { return position; }

sf::Vector2f Wall::getSize() const { return size; }

void Wall::draw(sf::RenderWindow &window) { window.draw(rect); }

sf::FloatRect Wall::getBounds() const { return rect.getGlobalBounds(); }
