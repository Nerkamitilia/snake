/************************************
 *  'Snake' Class for Snake game.
 * 
 *  Néstor Náṕoles, nnapoles@acm.org
 ************************************/


#ifndef SNAKE_H_
#define SNAKE_H_
#include "scenario.h"
#include <vector>

const int DIRECTION_NORTH=0;
const int DIRECTION_EAST=1;
const int DIRECTION_SOUTH=2;
const int DIRECTION_WEST=3;

class Snake{
 private:
  Scenario *scenario_;
  std::vector<SDL_Rect *> bodyCoordinates_;
  int headDirection_;
  int tailDirection_;
  SDL_Texture *headTexture_;
  SDL_Texture *tailTexture_;
  SDL_Texture *centerTexture_;

 public:
  Snake(Scenario *scenario);
  ~Snake();
  bool initializeTextures();
  void initializeCoordinates();
  //hasCollisions();
};
#endif
