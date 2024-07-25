#ifndef GAME_HPP
#define GAME_HPP

#include "HealthBar.hpp"
#include "Maze.hpp"
#include "Tank.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <mutex>
#include <thread>

class Game {
private:
  static Game *instance;
  sf::RenderWindow window;
  sf::Texture tank1Texture, tank2Texture, misTexture1, maTexture1, misTexture2,
      maTexture2;
  std::vector<std::unique_ptr<Tank>> tanks;
  std::vector<HealthBar> healthBars;
  Maze maze;
  std::vector<std::thread> tankThreads;
  std::mutex updateMutex;
  Game();
  bool gameOver;
  sf::Text winMessage;
  sf::Font font;
  sf::RectangleShape restartButton;
  sf::Text restartButtonText;
  sf::Texture backgroundTexture;
  sf::Sprite backgroundSprite;

public:
  Game(Game &) = delete;
  void operator=(const Game &) = delete;
  static Game *getInstance();
  void run();
  void processEvents();
  void update(sf::Time &dt);
  void render();
  void updateTank(Tank *tank, sf::Time dt);
  void resetGame();
};

#endif
