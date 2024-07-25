#ifndef CELL_HPP
#define CELL_HPP

struct Cell {
  bool visited;
  bool top, bottom, left, right;
  Cell() : visited(false), top(true), bottom(true), left(true), right(true) {}
};
#endif
