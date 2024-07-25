#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include "Game.hpp"
#include <memory>

class GameManager {
private:
  static GameManager *instance;
  std::unique_ptr<Game> gameInstance;
  GameManager();

public:
  GameManager(GameManager &) = delete;
  void operator=(const GameManager &) = delete;
  static GameManager *getInstance();
  void startGame();
  void restartGame();
  void handleInput(const sf::Event &event);
};

#endif
