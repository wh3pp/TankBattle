#ifndef WALL_HPP
#define WALL_HPP

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

class Wall {
private:
  sf::RectangleShape rect;
  sf::Vector2f position, size;

public:
  Wall() = default;
  void draw(sf::RenderWindow &window);
  void setPosition(const sf::Vector2f &position);
  void setSize(const sf::Vector2f &size);
  void setTexture(sf::Texture &texture);
  sf::Vector2f getPosition() const;
  sf::Vector2f getSize() const;
  sf::FloatRect getBounds() const;
};
#endif
