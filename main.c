
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
   gameWidth = app.resolutions[1][0];
   gameHeight = app.resolutions[1][1];
   
   windowHeightScale = (float)gameHeight/gameHeightBase;
   windowWidthScale = (float)gameWidth/gameWidthBase;

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
      Draw_Editor();
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
    SDL_SetRenderDrawColor(renderer,255,0,0,255);
    SDL_RenderDrawRect(renderer,&(SDL_Rect){10*windowWidthScale,10*windowHeightScale,30*windowWidthScale,30*windowHeightScale});    
    SDL_SetRenderTarget(renderer,NULL);
    SDL_RenderCopy(renderer,resultLayer,NULL,&(SDL_Rect){0,offset,windowWidth,min(windowHeight,windowGameHeight)});
    SDL_RenderPresent(renderer);
   }
}
void freeMalloc(){
   /// Textures
   SDL_DestroyTexture(tex_font);
   SDL_DestroyTexture(tex_trigger);
   SDL_DestroyTexture(tex_player);
   SDL_DestroyTexture(tex_bulb);
   SDL_DestroyTexture(tex_displacement);
   SDL_DestroyTexture(tex_skull);
   SDL_DestroyTexture(tex_coin);
   SDL_DestroyTexture(tex_star);
   SDL_DestroyTexture(tex_tools);
   SDL_DestroyTexture(tex_trophy);
   SDL_DestroyTexture(tex_blank);
   SDL_DestroyTexture(tex_water);
   SDL_DestroyTexture(tex_sand);
   SDL_DestroyTexture(tex_levelPad);
   SDL_DestroyTexture(tex_movenode);
   SDL_DestroyTexture(tex_script);
   SDL_DestroyTexture(tex_explosion);
   SDL_DestroyTexture(tex_enemy);
   SDL_DestroyTexture(tex_specials);
   SDL_DestroyTexture(tex_textIcon);
   SDL_DestroyTexture(tex_grappleFail);
   /// Sounds
   Mix_FreeChunk(Sound_Jump);
   Mix_FreeChunk(Sound_Step1);
   Mix_FreeChunk(Sound_Step2);
   Mix_FreeChunk(Sound_Wall);
   Mix_FreeChunk(Sound_JumpWall);
   Mix_FreeChunk(Sound_Death);
   Mix_FreeChunk(Sound_Checkpoint);
   Mix_FreeChunk(Sound_Hover);
   Mix_FreeChunk(Sound_buttonClick);
   Mix_FreeChunk(Sound_transition);
   Mix_FreeChunk(Sound_finish);
   Mix_FreeChunk(Sound_levelSelect);
   Mix_FreeChunk(Sound_textTick);
   Mix_FreeChunk(Sound_slash);
   Mix_FreeChunk(Sound_enemyHurt);
   Mix_FreeChunk(Sound_enemyDead);
   Mix_FreeChunk(Sound_woosh);
   Mix_FreeChunk(Sound_pickup);
   Mix_FreeChunk(Sound_enemyDash);
   Mix_FreeChunk(Sound_Throw);
   /// Array textures
   for(int i = 0;i<sizeof(textures)/sizeof(textures[0]);i++){
      if(textures[i].reserved) {
         SDL_DestroyTexture(textures[i].texture);
      }
   }
   for(int i = 0;i<sizeof(lightTextures)/sizeof(lightTextures[0]);i++){
      if(lightTextures[i].reserved) {
         SDL_DestroyTexture(lightTextures[i].texture);
      }
   }

   for(int i = 0;i<sizeof(backgrounds)/sizeof(backgrounds[0]);i++){
      if(backgrounds[i].reserved) {
         SDL_DestroyTexture(backgrounds[i].texture);
      }
   }
   /// Scripts
   for(int i = 0;i<sizeof(scriptfiles)/sizeof(scriptfiles[0]);i++) {
      if(scriptfiles[i].script != NULL) {free(scriptfiles[i].script);}
      for(int k = 0;k < scriptfiles[i].commandsNumber;k++){
         if(scriptfiles[i].scriptCompiled[k] != NULL) {free(scriptfiles[i].scriptCompiled[k]);}
      }
      if(scriptfiles[i].scriptCompiled != NULL) {free(scriptfiles[i].scriptCompiled);}
   }

   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);

}

void quitSDL() {

   Mix_CloseAudio();   // SDL_mixer
   Mix_Quit();

   IMG_Quit();

   SDL_Quit();
}

int main(int argc,char *argv[]){
   if (initVideo() == 0){
      FWindow_Loop();
   }
   remove("levels/temp.txt");
   freeMalloc();
   quitSDL();
   return 0;
}