#include "../include/Tank.hpp"
#include "../include/BulletFactory.hpp"
#include "../include/MoveDownCommand.hpp"
#include "../include/MoveUpCommand.hpp"
#include "../include/RotateLeftCommand.hpp"
#include "../include/RotateRightCommand.hpp"
#include "../include/Shoot1Command.hpp"
#include "../include/Shoot2Command.hpp"

#include <SFML/Window/Event.hpp>
#include <cmath>
#include <memory>

Tank::Tank(sf::Texture &texture, sf::Texture &missileTex,
           sf::Texture &machinegunTex)
    : missileTexture(missileTex), machinegunTexture(machinegunTex) {
  sprite.setTexture(texture);
  running = false;
  rotateL = false;
  rotateR = false;
  previousPosition = sprite.getPosition();
  previousRotation = sprite.getRotation();
}

void Tank::setSpeed(float speed) { this->speed = speed; }

void Tank::setRotation(float rotation) { sprite.setRotation(rotation); }

void Tank::setPosition(sf::Vector2f position) { sprite.setPosition(position); }
void Tank::setRunning(bool running) { this->running = running; }
void Tank::setRotationBool(bool rotateL, bool rotateR) {
  this->rotateL = rotateL;
  this->rotateR = rotateR;
}
float Tank::getSpeed() { return speed; }
sf::Texture &Tank::getMissileTexture() { return missileTexture; }
sf::Texture &Tank::getMachinegunTexture() { return machinegunTexture; }
void Tank::setKeymaps(sf::Keyboard::Key up, sf::Keyboard::Key down,
                      sf::Keyboard::Key left, sf::Keyboard::Key right,
                      sf::Keyboard::Key shoot1, sf::Keyboard::Key shoot2) {
  this->up = up;
  this->down = down;
  this->left = left;
  this->right = right;
  this->shoot1 = shoot1;
  this->shoot2 = shoot2;
}

void Tank::update(sf::Time &dt, const std::vector<Wall> &walls,
                  const std::vector<std::unique_ptr<Tank>> &tanks) {
  previousPosition = sprite.getPosition();
  previousRotation = sprite.getRotation();
  float angle = sprite.getRotation();
  float radians = angle * (3.14159f / 180.f);
  direction.x = cos(radians);
  direction.y = sin(radians);
  if (running) {
    sprite.move(direction * speed * dt.asSeconds());
  }
  if (rotateL) {
    sprite.rotate(-50.f * dt.asSeconds());
  }
  if (rotateR) {
    sprite.rotate(50.f * dt.asSeconds());
  }
  if (checkCollision(walls, tanks)) {
    sprite.setPosition(previousPosition);
  }
  if (checkCollision(walls, tanks)) {
    sprite.setRotation(previousRotation);
  }
  missileCooldown -= dt.asSeconds();
  machinegunCooldown -= dt.asSeconds();
  for (auto &bullet : bullets) {
    bullet->setRotation(sprite.getRotation());
    bullet->update(dt, walls);
  }
}

void Tank::handleInput(sf::Event &event) {
  std::unique_ptr<Command> command;

  if (event.type == sf::Event::KeyPressed) {
    if (event.key.code == up) {
      command = std::make_unique<MoveUpCommand>();
    }
    if (event.key.code == down) {
      command = std::make_unique<MoveDownCommand>();
    }
    if (event.key.code == left) {
      command = std::make_unique<RotateLeftCommand>();
    }
    if (event.key.code == right) {
      command = std::make_unique<RotateRightCommand>();
    }
    if (event.key.code == shoot2 && missileCooldown <= 0) {
      command = std::make_unique<Shoot2Command>();
      missileCooldown = missileCooldownTime;
    }
    if (event.key.code == shoot1 && machinegunCooldown <= 0) {
      command = std::make_unique<Shoot1Command>();
      machinegunCooldown = machinegunCooldownTime;
    }
    if (command) {
      command->execute(*this);
    }
  }
  if (event.type == sf::Event::KeyReleased) {
    if (event.key.code == up) {
      running = false;
    }
    if (event.key.code == down) {
      running = false;
    }
    if (event.key.code == left) {
      rotateL = false;
      rotateR = false;
    }
    if (event.key.code == right) {
      rotateR = false;
      rotateL = false;
    }
  }
}

void Tank::draw(sf::RenderWindow &window) {
  window.draw(sprite);
  for (const auto &bullet : bullets) {
    bullet->draw(window);
  }
}

sf::FloatRect Tank::getBounds() const { return sprite.getGlobalBounds(); }

sf::Vector2f Tank::getPosition() const { return sprite.getPosition(); }

sf::Vector2f Tank::getDirection() const { return direction; }

bool Tank::checkCollision(const std::vector<Wall> &walls,
                          const std::vector<std::unique_ptr<Tank>> &tanks) {
  for (const Wall &wall : walls) {
    if (wall.getBounds().intersects(getBounds())) {
      return true;
    }
  }
  for (size_t i = 0; i < tanks.size(); ++i) {
    if (tanks[i].get() != this) {
      if (tanks[i]->getBounds().intersects(getBounds())) {
        return true;
      }
    }
  }
  return false;
}

void Tank::fireBullet(const std::string &type, sf::Texture &bulletTexture) {
  sf::Vector2f tmp(0, sprite.getLocalBounds().height / 2);
  sf::Vector2f bulletPosition = sprite.getTransform().transformPoint(tmp);
  auto bullet = BulletFactory::createBullet(type, bulletTexture, bulletPosition,
                                            400, -direction);
  if (bullet) {
    bullets.push_back(std::move(bullet));
  }
}

const std::vector<std::unique_ptr<Bullet>> &Tank::getBullets() const {
  return bullets;
}
