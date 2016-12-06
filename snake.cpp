#include "snake.h"

Snake::Snake(Scenario *scenario):
  headTexture_(NULL),
  tailTexture_(NULL),
  centerTexture_(NULL),
  headDirection_(DIRECTION_EAST),
  tailDirection_(DIRECTION_EAST){
  if(scenario!=NULL){
    scenario_=scenario;
  }else{
    std::cout<<"Instantiate an scenario object first, and use it as argument for snake class."<<std::endl;
  }
}

bool Snake::initializeTextures(){
  SDL_Surface *tmpSurface=Scenario::loadSurface("head.png");
  bool hadSuccess=false;
  if(tmpSurface!=NULL){
    headTexture_=scenario_->loadTexture(tmpSurface);
    SDL_FreeSurface(tmpSurface);
    tmpSurface=Scenario::loadSurface("tail.png");
    if(tmpSurface!=NULL){
      tailTexture_=scenario_->loadTexture(tmpSurface);
      SDL_FreeSurface(tmpSurface);
      tmpSurface=Scenario::loadSurface("center.png");
      if(tmpSurface!=NULL){
	centerTexture_=scenario_->loadTexture(tmpSurface);
	SDL_FreeSurface(tmpSurface);
	if(headTexture_!=NULL&&tailTexture_!=NULL&&centerTexture_!=NULL){
	  hadSuccess=true;
	}
      }
    }
  }
  return hadSuccess;
}

void Snake::initializeCoordinates(){
  int middleRow=scenario_->getGameRows()/2;
  int middleColumn=scenario_->getGameColumns()/2;
  SDL_Rect *headRect=NULL,*centerRect=NULL,*tailRect=NULL;
  headRect=scenario_->getRectFromCoordinates(middleRow,middleColumn);
  centerRect=scenario_->getRectFromCoordinates(middleRow,middleColumn-1);
  tailRect=scenario_->getRectFromCoordinates(middleRow,middleColumn-2);
  bodyCoordinates_.push_back(headRect);
  bodyCoordinates_.push_back(centerRect);
  bodyCoordinates_.push_back(tailRect);
  scenario_->drawTexture(headTexture_,bodyCoordinates_[0]);
  scenario_->drawTexture(centerTexture_,bodyCoordinates_[1]);
  scenario_->drawTexture(tailTexture_,bodyCoordinates_[2]);
  scenario_->flushRenderer();
  SDL_Delay(2000);
}

Snake::~Snake(){
  bodyCoordinates_.clear();
  if(headTexture_!=NULL){
    SDL_DestroyTexture(headTexture_);
    headTexture_=NULL;
  }
  if(tailTexture_!=NULL){
    SDL_DestroyTexture(tailTexture_);
    tailTexture_=NULL;
  }
  if(centerTexture_!=NULL){
    SDL_DestroyTexture(centerTexture_);
    centerTexture_=NULL;
  } 
}


//bool Snake::hasCollisions(){
  /* if(!borderCollisions(headNextDirection)&&!snakebodyCollision()){
   *    go ahead!...
   */
