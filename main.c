
#include "src/include.h"
// On execution commands to run.

void FAppInit_Values(){
   // app.status values
   // 0 => in game
   // 1 => in editor
   // 2 => in level select
   // 3 => in settings
   // 4 => in Menu
   
   for(int i = 0 ;i<sizeof(buttons)/sizeof(buttons[0]);i++){
      buttons[i].reserved = false;
      SDL_memcpy(buttons[i].value,"\0",1);
   }
   for(int i = 0 ;i<sizeof(sliders)/sizeof(sliders[0]);i++){
      sliders[i].reserved = false;
      SDL_memcpy(sliders[i].value,"\0",1);
   }
   for(int i = 0 ;i<sizeof(knobs)/sizeof(knobs[0]);i++){
      knobs[i].reserved = false;
      knobs[i].knobCoef = 1;
      SDL_memcpy(sliders[i].value,"\0",1);
   }
   for(int i = 0;i<sizeof(movenodes)/sizeof(movenodes[0]);i++){
      movenodes[i].reserved = false;
      movenodes[i].nodesCount = 0;
   }
   
  // Resolutions
  int resolutions[][2] = {
    {640,  480},
    {800,  600},
    {1024, 720},
    {1024, 768},
    {1280, 1080},
    {1366, 768},
    {1920, 1080}
};
memcpy(app.resolutions, resolutions, sizeof(resolutions));

   app.resolutionInt = 2;
   app.resolutionUsed = 2;
   gameWidth = app.resolutions[5][0];
   gameHeight = app.resolutions[5][1];


   app.status = 4;
   app.fetchedList = false;
   app.backgroundMoving = 0; 
   app.transition = false;
   app.transitionInt = 0;
   
   level.timer = 0;
   level.tempFileMade = false;
   level.keyInputsSize = 0;
   level.Finished = false;
   level.Started = false;
   app.textboxSelected = -1;
   app.sliderTextBoxSelected = -1;
   app.knobTextBoxSelected = -1;
   camera.x = 0;
   camera.y = 0;
   camera.scale = 1;
   camera.freeCam = true;
   app.backgroundInt = 1;
   for(int i = 0;i<5;i++){
      player[0].playerTrails[i][0] = 0;
      player[0].playerTrails[i][1] = 0;
      player[0].playerTrails[i][2] = 0;
   }

}


void FWindow_Loop(){
   
   while(app.WINDOW_LOOP){
      
   
      FInput_Listener();
      
      // Clear all textures.
      SDL_SetRenderDrawColor(renderer, 0,0,0,0);
      SDL_RenderClear(renderer);
      SDL_SetRenderTarget(renderer,resultLayer);
      SDL_RenderClear(renderer);

      
    int startTick = SDL_GetTicks();

    if(app.status == 0){
      FUpdate_Data();
      FDraw_Game();
    }
    else if (app.status == 1){
      FUpdate_Editor();
      FDraw_Editor();
    }
    else{
      FUpdate_Data_Menu();
      FDraw_Menu();
    }
   
    FdeltaTime();
    
   // adding to window
   int offset = 0;
   int windowGameHeight = ((double)gameHeight/(double)gameWidth)*windowWidth;
   if(windowHeight > windowGameHeight){
      offset = (windowHeight-windowGameHeight)/2;
   }

    FDrawTransition();
    SDL_SetRenderTarget(renderer,NULL);
    SDL_RenderCopy(renderer,resultLayer,NULL,&(SDL_Rect){0,offset,windowWidth,min(windowHeight,windowGameHeight)});
    SDL_RenderPresent(renderer);
   }
}
void freeMalloc(){
   // Later
   
}

int main(int argc,char *argv[]){
   if (initVideo() == 0){
      FWindow_Loop();
      
   }
   remove("levels/temp.txt");
   freeMalloc();
   SDL_Quit();
   return 0;
}