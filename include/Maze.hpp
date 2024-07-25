#ifndef MAZE_HPP
#define MAZE_HPP

#include "Cell.hpp"
#include "Wall.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <random>
#include <vector>

class Maze {
private:
  std::vector<std::vector<Cell>> cells;
  int rows, columns;
  std::random_device rd;
  std::mt19937 randomNumber;
  std::vector<Wall> walls;
  sf::Texture texture;

public:
  Maze();
  Maze(int rows, int columns);
  void generate();
  void draw(sf::RenderWindow &window);
  void setTexture(const std::string &image);
  void generateMaze(int row, int col);
  void createWalls();
  std::vector<Wall> &getWalls();
  void reset();
};

#endif
