#include "../include/HealthBar.hpp"

HealthBar::HealthBar(float maxHealth, sf::Vector2f position, sf::Vector2f size)
    : maxHealth(maxHealth), currentHealth(maxHealth) {
  healthBarBackground.setSize(size);
  healthBarBackground.setPosition(position);
  healthBarBackground.setFillColor(sf::Color(150, 150, 150));

  healthBar.setSize(size);
  healthBar.setPosition(position);
  healthBar.setFillColor(sf::Color(0, 255, 0));
}

void HealthBar::updateHealth(float health) {
  currentHealth = std::max(0.0f, std::min(health, maxHealth));
  float healthRatio = currentHealth / maxHealth;
  healthBar.setSize(sf::Vector2f(healthBarBackground.getSize().x * healthRatio,
                                 healthBarBackground.getSize().y));
}

void HealthBar::draw(sf::RenderWindow &window) {
  window.draw(healthBarBackground);
  window.draw(healthBar);
}

float HealthBar::getCurrentHealth() const { return currentHealth; }
