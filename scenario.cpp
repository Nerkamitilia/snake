/****************************************
 * 'Scenario' class, implementation file
 *
 *  Néstor Nápoles, nnapoles@acm.org
 ****************************************/

#include "scenario.h"

bool Scenario::initializeWindow(){
  bool hadSuccess=true;
  window_=SDL_CreateWindow("Snake Game",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,screenWidth_,screenHeight_,SDL_WINDOW_SHOWN);
  if(window_!=NULL){
    renderer_=SDL_CreateRenderer(window_,-1,SDL_RENDERER_ACCELERATED);
    if(renderer_!=NULL){
      if(!(IMG_Init(IMG_INIT_PNG)&IMG_INIT_PNG)){
	std::cout<<"SDL_image couldn't initialize. IMG_Error: "<<IMG_GetError()<<std::endl;
	hadSuccess=false;
      }
    }else{
      std::cout<<"SDL_Renderer couldn't initialize. SDL_Error: "<<SDL_GetError()<<std::endl;
      hadSuccess=false;
    }
  }else{
    std::cout<<"SDL_Window couldn't initialize. SDL_Error: "<<SDL_GetError()<<std::endl;
    hadSuccess=false;
  }
  return hadSuccess;
}

void Scenario::destroyWindow(){
  if(foodTexture_!=NULL){
    SDL_DestroyTexture(foodTexture_);
    foodTexture_=NULL;
  }
  if(backgroundTexture_!=NULL){
    SDL_DestroyTexture(backgroundTexture_);
    backgroundTexture_=NULL;
  }
  if(renderer_!=NULL){
    SDL_DestroyRenderer(renderer_);
    renderer_=NULL;
  }
  if(window_!=NULL){
    SDL_DestroyWindow(window_);
    window_=NULL;
  }
  IMG_Quit();
  SDL_Quit();
}

bool Scenario::initializeGrid(){
  int squareWidth=screenWidth_/gameColumns_;
  int squareHeight=screenHeight_/gameRows_;
  gameGrid_=(SDL_Rect *)malloc(sizeof(SDL_Rect)*gameRows_*gameColumns_);
  if(gameGrid_!=NULL){
    SDL_Rect *tmpGrid=gameGrid_;
    for(int i=0;i<gameRows_;i++){
      for(int j=0;j<gameColumns_;j++){
	tmpGrid->x=j*squareWidth;
	tmpGrid->y=i*squareHeight;
	tmpGrid->w=squareWidth;
	tmpGrid->h=squareHeight;
	//std::cout<<"["<<i<<","<<j<<"]: ("<<tmpGrid->x<<","<<tmpGrid->y<<","<<tmpGrid->w<<","<<tmpGrid->h<<")"<<std::endl;
	tmpGrid++;
      }
    }
  }else{
    std::cout<<"Unable to allocate memory for the game grid."<<std::endl;
    return false;
  }
  return true;
}

void Scenario::destroyGrid(){
  if(gameGrid_!=NULL){
    free(gameGrid_);
  }
} 

Scenario::Scenario(int screenWidth,int screenHeight,int gameRows,int gameColumns):
  screenWidth_(screenWidth),
  screenHeight_(screenHeight),
  gameRows_(gameRows),
  gameColumns_(gameColumns),
  scenarioInitialized_(false),
  window_(NULL),
  renderer_(NULL),
  backgroundTexture_(NULL),
  foodTexture_(NULL),
  gameGrid_(NULL){
  if(initializeWindow()&&initializeGrid()){
    scenarioInitialized_=true;
  }
}

Scenario::~Scenario(){
  destroyGrid();
  destroyWindow();
}

int Scenario::getScreenWidth(){
  return screenWidth_;
}

int Scenario::getScreenHeight(){
  return screenHeight_;
}

int Scenario::getGameRows(){
  return gameRows_;
}

int Scenario::getGameColumns(){
  return gameColumns_;
}

bool Scenario::IsInitialized(){
  return scenarioInitialized_;
}

SDL_Rect *Scenario::getRectFromCoordinates(int row,int column){
  if(gameGrid_!=NULL){
    if((row>=0&&row<gameRows_)&&(column>=0&&column<gameColumns_)){
      return (gameGrid_+(row*gameColumns_)+column);
    }else{
      std::cout<<"That coordinate doesn't exist."<<std::endl;
    }
  }else{
    std::cout<<"Game grid it's not correctly initialized."<<std::endl;
  }
  return NULL;
}

void Scenario::getCoordinatesFromRect(SDL_Rect *rect,int *row,int *column){
  int squareWidth=screenWidth_/gameColumns_;
  int squareHeight=screenHeight_/gameRows_;
  if(gameGrid_!=NULL){
    *row=rect->y/squareHeight;
    if((*row)<0||(*row)>gameRows_-1){
      *row=0;
    }
    *column=rect->x/squareWidth;
    if((*column)<0||(*column)>gameColumns_-1){
      *column=0;
    }
  }else{
    std::cout<<"Game grid hasn't been initialized properly."<<std::endl;
    *row=0;
    *column=0;
  }
}

SDL_Surface *Scenario::loadSurface(std::string path){
  SDL_Surface *surface=IMG_Load(path.c_str());
  if(surface==NULL){
    std::cout<<"Unable to load surface from '"<<path<<"'. IMG_Error: "<<IMG_GetError()<<std::endl;
  }
  return surface;
}
   
SDL_Texture *Scenario::loadTexture(SDL_Surface *surface){
  SDL_Texture *newTexture=NULL;
  if(surface!=NULL){
    newTexture=SDL_CreateTextureFromSurface(renderer_,surface);
    if(newTexture==NULL){
      std::cout<<"Unable to create texture from surface. SDL Error: "<<SDL_GetError()<<std::endl;
    }
  }else{
    std::cout<<"No surface provided to turn into texture."<<std::endl;  
  }
  return newTexture;
}

bool Scenario::drawTexture(SDL_Texture *texture,SDL_Rect *rect){
  bool hadSuccess=true;
  if(renderer_!=NULL){
    if(texture!=NULL){
      SDL_RenderCopy(renderer_,texture,NULL,rect);
    }else{
      std::cout<<"Missing texture to render."<<std::endl;
      hadSuccess=false;
    }
  }else{
    std::cout<<"Renderer is not correctly initialized for rendering textures."<<std::endl;
    hadSuccess=false;
  }
  return hadSuccess;
} 

bool Scenario::flushRenderer(){
  if(renderer_!=NULL){
    SDL_RenderPresent(renderer_);
    return true;
  }
}
