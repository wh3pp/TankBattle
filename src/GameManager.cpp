#include "../include/GameManager.hpp"
GameManager *GameManager::instance = nullptr;

GameManager::GameManager() : gameInstance(Game::getInstance()) {}

GameManager *GameManager::getInstance() {
  if (!instance) {
    instance = new GameManager();
  }
  return instance;
}

void GameManager::startGame() { gameInstance->run(); }

void GameManager::restartGame() { gameInstance->resetGame(); }

void GameManager::handleInput(const sf::Event &event) {
  gameInstance->processEvents();
}
