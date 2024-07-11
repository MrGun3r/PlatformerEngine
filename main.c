
#include "include.c"
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
   app.status = 4;
   app.editorPlatformSize = 0;
   app.fetchedList = false;
   app.backgroundMoving = 0; 
   app.transition = false;
   app.transitionInt = 0;
   SDL_memcpy(app.backgroundName,"background\0",len("background\0"));
   FswitchAppStatus(0,4);

   level.timer = 0;
   level.tempFileMade = false;
   level.keyInputsSize = 0;
   level.Finished = false;
   level.Started = false;
   
   camera.x = 0;
   camera.y = 0;
   camera.scale = 1;
   camera.randValue = 0;
   camera.freeCam = true;
   app.backgroundInt = 1;

   SDL_SetTextureBlendMode(backgroundLayer, SDL_BLENDMODE_BLEND);
   SDL_SetTextureBlendMode(lightLayer, SDL_BLENDMODE_MOD);
   SDL_SetTextureBlendMode(lightLayer2, SDL_BLENDMODE_ADD);
   SDL_SetTextureBlendMode(HUDLayer, SDL_BLENDMODE_BLEND);
   SDL_SetTextureBlendMode(resultLayer,SDL_BLENDMODE_ADD);
}


void FWindow_Loop(){
   
   while(app.WINDOW_LOOP){
        
      if(!app.transition){
         FInput_Listener();
      }
      // Clear all textures.
      SDL_SetRenderDrawColor(renderer, 0,0,0,0);
      SDL_RenderClear(renderer);

      SDL_SetRenderTarget(renderer,HUDLayer);
      SDL_RenderClear(renderer);
      SDL_SetRenderTarget(renderer,lightLayer);
      SDL_RenderClear(renderer);
      SDL_SetRenderTarget(renderer,lightLayer2);
      SDL_RenderClear(renderer);
      SDL_SetRenderTarget(renderer,backgroundLayer);

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

    FDrawTransition();
    FdeltaTime();
    // Light
    DrawLight(app.backgroundOpacity);

   // compositing resultLayer
    SDL_SetRenderTarget(renderer,resultLayer);
    
    SDL_RenderCopy(renderer,backgroundLayer,NULL,NULL);
    SDL_RenderCopy(renderer,lightLayer,NULL,NULL);
    SDL_RenderCopy(renderer,lightLayer2,NULL,NULL);
    SDL_RenderCopy(renderer,HUDLayer,NULL,NULL);

   // adding to window
    SDL_SetRenderTarget(renderer,NULL);
    SDL_RenderCopy(renderer,resultLayer,NULL,NULL);
    SDL_RenderPresent(renderer);
    
    
   }
}

int main(int argc,char *argv[]){
   if (initVideo() == 0){
      FAppInit_Values();
      FWindow_Loop();
   }
   remove("levels/temp.txt");
   SDL_Quit();
   return 0;
}