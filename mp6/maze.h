/* Your code here! */
#pragma once

#include <iostream>
#include <vector>
#include "dsets.h"
#include <stdlib.h>     /* srand, rand */
#include "cs225/PNG.h"
#include <stack>
#include <map>

using namespace cs225;

class SquareMaze{
  //Creates an empty maze
public:
  SquareMaze();

  //Makes a new SquareMaze of the given height and width.
  void makeMaze(int width,int height);

  //This uses your representation of the maze to determine whether
  //it is possible to travel in the given direction from the square at coordinates (x,y).
  bool canTravel(int x, int y, int dir) const;

  //sets whether or not the specified wall exists
  void setWall(int x, int y, int dir, bool exists);

  //solves this square maze
  vector<int> solveMaze();

  //draws the maze without the solution
  PNG * drawMaze() const;

  //This function calls drawMaze, then solveMaze;
  //it modifies the PNG from drawMaze to show the solution vector and the exit.
  PNG * drawMazeWithSolution();
  //creates a creative maze
  // void makeCreativeMaze(int width, int height);
  PNG *drawCreativeMaze() const;
  PNG *drawCreativeMazeSolution() const;

private:
  DisjointSets maze_squares;
  // DisjointSets creative_maze;
  int width_;
  int height_;

  // vector<int> cells;
  vector<vector<int>> edges;
  vector<bool> setWall_right;
  vector<bool> setWall_down;
  vector<int> path_finder;
  vector<int> path_finder_creative;
  int zero =0;

};
