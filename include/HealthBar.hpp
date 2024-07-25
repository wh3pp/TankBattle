#ifndef HEALTH_BAR_HPP
#define HEALTH_BAR_HPP

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

class HealthBar {
private:
  sf::RectangleShape healthBarBackground;
  sf::RectangleShape healthBar;
  float maxHealth;
  float currentHealth;

public:
  HealthBar(float maxHealth, sf::Vector2f position, sf::Vector2f size);
  void updateHealth(float health);
  void draw(sf::RenderWindow &window);
  float getCurrentHealth() const;
};
#endif
