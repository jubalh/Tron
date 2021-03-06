// Copyright 2014, flackbash
// Author: flackbash <flack2bash@gmail.com>


#ifndef PROGRAMMING_ARMAGETRON_ARENA_H_  // NOLINT
#define PROGRAMMING_ARMAGETRON_ARENA_H_  // NOLINT

#include <stdio.h>
#include <gtest/gtest.h>

class Biker;

// class for the arena
class Arena {
 public:
  // constructor
  Arena(int x, int y);

  // destructor
  ~Arena();

  // print the arena borders
  void printBorders();

  // print a new cell
  void printCell(int x, int y);

  // add a new part of wall to the arena
  void addWall(Biker* biker);

  // remove the walls of the player that has just crashed
  void removeWall(Biker* biker);

  // delete  the walls in the direct surrounding of an explosion
  void clearArea(int x, int y);

  // reset (affects _cells)
  void reset();

  // get the x-size
  int getXAl() const;

  // get the y-size
  int getYAl() const;

  // check if and by whom a cell is occupied
  enum CellStatus {
    EMPTY = 0, PLAYER1 = -1, PLAYER2 = -2, PLAYER3 = -3, PLAYER4 = -4,
    COMPUTER1 = 1, COMPUTER2 = 2, COMPUTER3 = 3, COMPUTER4 = 4, COMPUTER5 = 5,
    OUTSIDE = -10
  };
  CellStatus getCellStatus(int x, int y) const;
  FRIEND_TEST(TronTest, getCellStatus);
  FRIEND_TEST(TronTest, crashControl);
  FRIEND_TEST(TronTest, removeWall);
  FRIEND_TEST(TronTest, crashHandling);

 private:
  // x and y size
  int _xAl;
  int _yAl;

  // holds which cells are occupied by which player and which are empty
  CellStatus** _cells;
};

#endif  // PROGRAMMING_ARMAGETRON_ARENA_H_  // NOLINT
