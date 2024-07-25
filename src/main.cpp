#include "../include/GameManager.hpp"

int main() {
  GameManager *manager = GameManager::getInstance();
  manager->startGame();
}
