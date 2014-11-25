// Copyright 2014, flackbash
// Author: flackbash <flack2bash@gmail.com>

#include <vector>
#include "./Biker.h"

// _____________________________________________________________________________
Biker::Biker(size_t x, size_t y, Direction direction, int number) {
  _xPos = x;
  _yPos = y;
  _direction = direction;
  _bikeNumber = number;
  _status = RACING;
}

// _____________________________________________________________________________
Biker::~Biker() {}

// _____________________________________________________________________________
std::vector<int> Biker::getNewPosition(Direction direction) const {
  std::vector<int> position;
  position.push_back(_xPos);
  position.push_back(_yPos);

  switch (direction) {
    case UP:
      position[1]++;
      break;
    case DOWN:
      position[1]--;
      break;
    case RIGHT:
      position[0]++;
      break;
    case LEFT:
      position[0]--;
      break;
  }
  return position = {position[0], position[1]};
}

// _____________________________________________________________________________
void Biker::move(Arena* arena) {
  std::vector<int> newPos = getNewPosition(_direction);

  int x = newPos[0];
  int y = newPos[1];

  if (crashControl(x, y, arena) == true) {
    crashHandling(arena);
  } else {
    _xPos = x;
    _yPos = y;
    arena->addWall(this);
  }
}

// _____________________________________________________________________________
void Biker::turn(Direction direction) {
  switch (direction) {
    case UP:
      _direction = UP;
      break;
    case DOWN:
      _direction = DOWN;
      break;
    case RIGHT:
      _direction = RIGHT;
      break;
    case LEFT:
      _direction = LEFT;
      break;
  }
}

// _____________________________________________________________________________
bool Biker::crashControl(size_t x, size_t y, Arena* arena) const {
  // no crash if cell status is EMPTY
  if (arena->getCellStatus(x, y) == 0) {
    return false;
  } else {
    return true;
  }
}

// _____________________________________________________________________________
void Biker::crashHandling(Arena* arena) {
  if (_bikeNumber > 0) {
    int checked[4] = {0, 0, 0, 0};
    int counter = 0;
    bool collision = true;
    std::vector<int> newPos;
    Direction direction = _direction;

    while (collision == true) {
      // check if direction has already been checked
      for (int i = 0; i < 4; i++) {
        if (checked[i] == direction) {
          direction = Direction((direction % 4) + 65);
          break;
        } else if (checked[i] == 0) {
          checked[i] = direction;
          counter++;
          break;
        }
      }

      // check if all directions have been checked already
      if (counter == 4) {
        arena->removeWall(this);
        _status = DESTROYED;
        break;
      }

      // check if moving into the new direction causes a crash
      newPos = getNewPosition(direction);
      collision = crashControl(newPos[0], newPos[1], arena);
    }
    // turn into the last checked direction (this does either not cause a crash
    // or the biker is DESTROYED already so it doesn't matter)
    turn(direction);
    move(arena);
  } else {
    arena->removeWall(this);
    _status = DESTROYED;
  }
}

// _____________________________________________________________________________
size_t Biker::getXPos() const {
  return _xPos;
}

// _____________________________________________________________________________
size_t Biker::getYPos() const {
  return _yPos;
}

// _____________________________________________________________________________
Biker::Direction Biker::getDirection() const {
  return _direction;
}

// _____________________________________________________________________________
int Biker::getNumber() const {
  return _bikeNumber;
}

// _____________________________________________________________________________
Biker::Status Biker::getStatus() const {
  return _status;
}

// _____________________________________________________________________________
Biker::Direction Biker::getRandomDirection() const {
  Direction direction;
  unsigned int seed = (unsigned int)(time(NULL));
  direction = Direction(65 + rand_r(&seed) % 4);
  return direction;
}

// _____________________________________________________________________________
Player::Player(size_t x, size_t y, Direction direction, int number)
: Biker(x, y, direction, number) {}
