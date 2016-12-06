/***********************************
 * Snake Game, Feb 2014
 *
 * Néstor Nápoles, nnapoles@acm.org 
 ***********************************/

#include "scenario.cpp"
#include "snake.cpp"



int main(int argc,char *argv[]){
  Scenario scenario;
  Snake snake(&scenario);
  snake.initializeTextures();
  snake.initializeCoordinates();
  
  return 0;
}


/*int main(int argc,char *argv[]){
  int x,y;
  Scenario scenario;
  if(scenario.IsInitialized()){
    SDL_Surface *backgrounds;
    SDL_Texture *backgroundt;
    SDL_Rect *rect;
    backgrounds=loadSurface("./background.png");
    backgroundt=scenario.loadTexture(backgrounds);
    for(int i=0;i<scenario.getGameRows();i++){
      for(int j=0;j<scenario.getGameColumns();j++){
	rect=scenario.getRectFromCoordinates(i,j);
	scenario.getCoordinatesFromRect(rect,&x,&y);
	std::cout<<"("<<x<<","<<y<<")"<<std::endl;
	scenario.drawTexture(backgroundt,rect);
	scenario.flushRenderer();
	SDL_Delay(50);
      }
    }
  }
  return 0;
}
*/
