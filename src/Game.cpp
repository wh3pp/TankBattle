#include "../include/Game.hpp"
#include "../include/MachineGun.hpp"
#include "../include/Missile.hpp"

Game *Game::instance = nullptr;

Game *Game::getInstance() {
  if (instance == nullptr) {
    instance = new Game();
  }
  return instance;
}

Game::Game() : window(sf::VideoMode(1920, 1080), "TankBattle"), maze() {
  tank1Texture.loadFromFile("../resources/tank1.png");
  tank2Texture.loadFromFile("../resources/tank2.png");
  misTexture1.loadFromFile("../resources/misile.png");
  maTexture1.loadFromFile("../resources/machinegun.png");
  misTexture2.loadFromFile("../resources/misile.png");
  maTexture2.loadFromFile("../resources/machinegun.png");
  maze.setTexture("../resources/wall.png");
  maze.generate();
  backgroundTexture.loadFromFile("../resources/background.png");
  backgroundSprite.setTexture(backgroundTexture);
  std::unique_ptr<Tank> tank1 =
      std::make_unique<Tank>(tank1Texture, misTexture1, maTexture1);
  tank1->setPosition({100, 970});
  tank1->setRotation(90);
  tank1->setSpeed(200);
  tank1->setKeymaps(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A,
                    sf::Keyboard::D, sf::Keyboard::Space, sf::Keyboard::LShift);
  tanks.push_back(std::move(tank1));

  std::unique_ptr<Tank> tank2 =
      std::make_unique<Tank>(tank2Texture, misTexture2, maTexture2);
  tank2->setPosition({1800, 120});
  tank2->setRotation(-90);
  tank2->setSpeed(200);
  tank2->setKeymaps(sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left,
                    sf::Keyboard::Right, sf::Keyboard::Enter,
                    sf::Keyboard::RShift);
  tanks.push_back(std::move(tank2));
  for (size_t i = 0; i < tanks.size(); ++i) {
    healthBars.emplace_back(200, sf::Vector2f(10 + (i * 1690), 10),
                            sf::Vector2f(200, 20));
  }
  font.loadFromFile("../resources/arial.ttf");
  winMessage.setFont(font);
  winMessage.setString("You Win!");
  winMessage.setCharacterSize(150);
  winMessage.setFillColor(sf::Color::White);
  winMessage.setPosition(700, 400);

  restartButton.setSize(sf::Vector2f(200, 50));
  restartButton.setFillColor(sf::Color::Blue);
  restartButton.setPosition(860, 600);

  restartButtonText.setFont(font);
  restartButtonText.setString("Restart");
  restartButtonText.setCharacterSize(30);
  restartButtonText.setFillColor(sf::Color::Black);
  restartButtonText.setPosition(900, 610);
}

void Game::resetGame() {
  tanks.clear();
  healthBars.clear();
  maze.reset();
  std::unique_ptr<Tank> tank1 =
      std::make_unique<Tank>(tank1Texture, misTexture1, maTexture1);
  tank1->setPosition({100, 970});
  tank1->setRotation(90);
  tank1->setSpeed(300);
  tank1->setKeymaps(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A,
                    sf::Keyboard::D, sf::Keyboard::Space, sf::Keyboard::LShift);
  tanks.push_back(std::move(tank1));

  std::unique_ptr<Tank> tank2 =
      std::make_unique<Tank>(tank2Texture, misTexture1, maTexture1);
  tank2->setPosition({1800, 120});
  tank2->setRotation(-90);
  tank2->setSpeed(300);
  tank2->setKeymaps(sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left,
                    sf::Keyboard::Right, sf::Keyboard::Enter,
                    sf::Keyboard::RShift);
  tanks.push_back(std::move(tank2));

  for (size_t i = 0; i < tanks.size(); ++i) {
    healthBars.emplace_back(100, sf::Vector2f(10 + (i * 1690), 10),
                            sf::Vector2f(200, 20));
  }
  gameOver = false;
};

void Game::run() {
  sf::Clock clock;
  while (window.isOpen()) {
    processEvents();
    sf::Time dt = clock.restart();
    update(dt);
    render();
  }
}

void Game::processEvents() {
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed)
      window.close();
    if (gameOver) {
      if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
          sf::Vector2i mousePos = sf::Mouse::getPosition(window);
          if (restartButton.getGlobalBounds().contains(
                  static_cast<sf::Vector2f>(mousePos))) {
            resetGame();
          }
        }
      }
    } else {
      for (size_t i = 0; i < tanks.size(); ++i) {
        tanks[i]->handleInput(event);
      }
    }
  }
}
void Game::update(sf::Time &dt) {
  tankThreads.clear();
  for (auto &tank : tanks) {
    tankThreads.emplace_back(&Game::updateTank, this, tank.get(), dt);
  }

  for (auto &thread : tankThreads) {
    if (thread.joinable()) {
      thread.join();
    }
  }
  for (size_t i = 0; i < healthBars.size(); i++) {
    if (healthBars[i].getCurrentHealth() == 0) {
      tanks.erase(tanks.begin() + i);
      healthBars.erase(healthBars.begin() + i);
      gameOver = true;
    }
  }
}

void Game::updateTank(Tank *tank, sf::Time dt) {
  std::lock_guard<std::mutex> lock(updateMutex);
  tank->update(dt, maze.getWalls(), tanks);
  for (size_t i = 0; i < tanks.size(); ++i) {
    if (tank != tanks[i].get()) {
      for (auto &bullet : tank->getBullets()) {
        if (bullet->isActive() &&
            bullet->getBounds().intersects(tanks[i]->getBounds())) {
          if (dynamic_cast<Missile *>(bullet.get())) {
            healthBars[i].updateHealth(healthBars[i].getCurrentHealth() - 50);
          } else if (dynamic_cast<MachineGun *>(bullet.get())) {
            healthBars[i].updateHealth(healthBars[i].getCurrentHealth() - 10);
          }
          bullet->deactivate();
        }
      }
    }
  }
}
void Game::render() {
  window.clear();
  window.draw(backgroundSprite);
  maze.draw(window);
  if (gameOver) {
    window.draw(winMessage);
    window.draw(restartButton);
    window.draw(restartButtonText);
  }
  for (auto &tank : tanks) {
    tank->draw(window);
  }
  for (auto &healthBar : healthBars) {
    healthBar.draw(window);
  }
  window.display();
}
