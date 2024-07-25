#ifndef TANK_HPP
#define TANK_HPP

#include "Bullet.hpp"
#include "Command.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <memory>

class Tank {
private:
  sf::Sprite sprite;
  sf::Vector2f direction;
  bool running, rotateL, rotateR;
  float speed, previousRotation;
  sf::Keyboard::Key up, down, left, right, shoot1, shoot2;
  sf::Vector2f previousPosition;
  std::vector<std::unique_ptr<Bullet>> bullets;
  sf::Texture missileTexture, machinegunTexture;
  float missileCooldown;
  float machinegunCooldown;
  const float missileCooldownTime = 2.0f;
  const float machinegunCooldownTime = 0.4f;

public:
  Tank(sf::Texture &texture, sf::Texture &missileTex,
       sf::Texture &machinegunTex);
  void setSpeed(float speed);
  void setPosition(sf::Vector2f position);
  void setRotation(float rotation);
  void setRunning(bool running);
  void setRotationBool(bool rotateL, bool rotateR);
  float getSpeed();
  sf::Vector2f getPosition() const;
  sf::Vector2f getDirection() const;
  sf::Texture &getMissileTexture();
  sf::Texture &getMachinegunTexture();
  void setKeymaps(sf::Keyboard::Key up, sf::Keyboard::Key down,
                  sf::Keyboard::Key left, sf::Keyboard::Key right,
                  sf::Keyboard::Key shoot1, sf::Keyboard::Key shoot2);
  void update(sf::Time &dt, const std::vector<Wall> &walls,
              const std::vector<std::unique_ptr<Tank>> &tanks);
  void handleInput(sf::Event &event);
  void draw(sf::RenderWindow &window);
  sf::FloatRect getBounds() const;
  bool checkCollision(const std::vector<Wall> &walls,
                      const std::vector<std::unique_ptr<Tank>> &tanks);
  void fireBullet(const std::string &type, sf::Texture &bulletTexture);
  const std::vector<std::unique_ptr<Bullet>> &getBullets() const;
};

#endif
