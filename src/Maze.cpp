#include "../include/Maze.hpp"

Maze::Maze() {
  std::random_device rdtmp;
  std::mt19937 rntmp(rdtmp());
  std::uniform_int_distribution<> distribution(2, 6);
  rows = distribution(rdtmp);
  columns = distribution(rdtmp);
  cells.resize(rows, std::vector<Cell>(columns));
}

Maze::Maze(int rows, int columns)
    : rows(rows), columns(columns), randomNumber(rd()) {
  cells.resize(rows, std::vector<Cell>(columns));
}
void Maze::reset() {
  cells.resize(rows, std::vector<Cell>(columns));
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      cells[i][j].visited = false;
      cells[i][j].top = true;
      cells[i][j].bottom = true;
      cells[i][j].left = true;
      cells[i][j].right = true;
    }
  }

  walls.clear();
  generate();
}

void Maze::setTexture(const std::string &name) { texture.loadFromFile(name); }

void Maze::generate() {
  generateMaze(0, 0);
  createWalls();
}
void Maze::generateMaze(int row, int col) {
  cells[row][col].visited = true;
  std::vector<std::pair<int, int>> directions = {
      {1, 0}, {-1, 0}, {0, 1}, {0, -1}};
  std::shuffle(directions.begin(), directions.end(), randomNumber);

  for (const auto &dir : directions) {
    int newRow = row + dir.first;
    int newCol = col + dir.second;

    if (newRow < 0 || newRow >= rows || newCol < 0 || newCol >= columns ||
        cells[newRow][newCol].visited) {
      continue;
    }

    if (dir.first == 1) {
      cells[row][col].bottom = false;
      cells[newRow][newCol].top = false;
    } else if (dir.first == -1) {
      cells[row][col].top = false;
      cells[newRow][newCol].bottom = false;
    } else if (dir.second == 1) {
      cells[row][col].right = false;
      cells[newRow][newCol].left = false;
    } else if (dir.second == -1) {
      cells[row][col].left = false;
      cells[newRow][newCol].right = false;
    }

    generateMaze(newRow, newCol);
  }
}

void Maze::createWalls() {
  sf::Vector2f cellSize(1920.f / columns, 1080.f / rows);
  const float wallThickness = 5.0f;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      if (cells[i][j].top) {
        Wall wall;
        wall.setSize(sf::Vector2f(cellSize.x, wallThickness));
        wall.setPosition(sf::Vector2f(j * cellSize.x, i * cellSize.y));
        wall.setTexture(texture);
        walls.push_back(wall);
      }
      if (cells[i][j].bottom) {
        Wall wall;
        wall.setSize(sf::Vector2f(cellSize.x, wallThickness));
        wall.setPosition(
            sf::Vector2f(j * cellSize.x, (i + 1) * cellSize.y - wallThickness));
        wall.setTexture(texture);
        walls.push_back(wall);
      }
      if (cells[i][j].left) {
        Wall wall;
        wall.setSize(sf::Vector2f(wallThickness, cellSize.y));
        wall.setPosition(sf::Vector2f(j * cellSize.x, i * cellSize.y));
        wall.setTexture(texture);
        walls.push_back(wall);
      }
      if (cells[i][j].right) {
        Wall wall;
        wall.setSize(sf::Vector2f(wallThickness, cellSize.y));
        wall.setPosition(
            sf::Vector2f((j + 1) * cellSize.x - wallThickness, i * cellSize.y));
        wall.setTexture(texture);
        walls.push_back(wall);
      }
    }
  }
}

void Maze::draw(sf::RenderWindow &window) {
  for (Wall &wall : walls) {
    wall.draw(window);
  }
}

std::vector<Wall> &Maze::getWalls() { return walls; }
