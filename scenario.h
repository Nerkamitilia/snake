/*************************************
 * Main class 'Scenario' for Snake Game
 *
 * Néstor Nápoles, nnapoles@acm.org
 *************************************/

#ifndef SCENARIO_H_
#define SCENARIO_H_
#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

class Scenario{  
private:
  bool initializeWindow();
  void destroyWindow();  
  bool initializeGrid();
  void destroyGrid();
  int screenWidth_;
  int screenHeight_;
  int gameRows_;
  int gameColumns_;
  bool scenarioInitialized_;
  SDL_Window *window_;
  SDL_Renderer *renderer_;
  SDL_Texture *backgroundTexture_;
  SDL_Texture *foodTexture_;
  SDL_Rect *gameGrid_;
public:
  //I didn't write up a parser for the Resolution and Rows-Columns taken as arguments from console. However, changing these default values should work straight-forward.
  Scenario(int screenWidth=600,int screenHeight=600,int gameRows=12,int gameColumns=12);
  ~Scenario();
  int getScreenWidth();
  int getScreenHeight();
  int getGameRows();
  int getGameColumns();
  /*I considered this attributes won't be changed after the class is instantiated. Therefore, i didn't fill them up.
  void setScreenWidth();
  void setScreenHeight();
  void setGameRows();
  void setGameColumns();*/
  bool IsInitialized();
  SDL_Rect *getRectFromCoordinates(int row,int column);
  void getCoordinatesFromRect(SDL_Rect *rect,int *row,int *column);
  static SDL_Surface *loadSurface(std::string path);
  SDL_Texture *loadTexture(SDL_Surface *surface);
  bool drawTexture(SDL_Texture *texture,SDL_Rect *rect);
  //bool spawnFood(const Snake& snake);
  bool flushRenderer();  
};
#endif 
