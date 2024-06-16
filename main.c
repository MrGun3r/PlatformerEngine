
#include "include.c"



// On execution commands to run.

void FAppInit_Values(){
   // app.status values
   // 0 => in game
   // 1 => in editor
   // 2 => in level select
   // 3 => in settings
   // 4 => in Menu
   app.status = 4;
   app.editorPlatformSize = 0;
   app.fetchedList = false;
   app.backgroundMoving = 0; 
   app.transition = false;
   app.transitionInt = 0;
   
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
}


void FWindow_Loop(){
   
   while(app.WINDOW_LOOP){
    FInput_Listener();
   
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