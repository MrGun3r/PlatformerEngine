#include "main_buttons.c"

void FDraw_Menu(){
   
   SDL_RenderClear(renderer);
   DrawBackground();

   // Draw HUD
   
   GUIHover();
   renderButtons();
   renderSliders();
   renderTextBox();

   for(int i = 3;i<sizeof(buttons)/sizeof(buttons[0]);i++){
      if(buttons[i].reserved){
         if(app.status == 2){
           if(!app.fetchedList){
            
           char* PBTemp = FGetDataMap(levelsList[i-3].levelPath,"m",1,levelsList[i].levelNameSize);
           SDL_memcpy(levelsList[i-3].PB,PBTemp,9);
           free(PBTemp);
           }
           char* msToTimerText = msToTimer(atoi(levelsList[i-3].PB));
           renderText(9,msToTimerText,buttons[i].hoverWidth-70,buttons[i].y,(buttons[i].ButtonFontWidth)*9,buttons[i].ButtonFontHeight,255,200,(int[3]){255,255,255}); 
           if(buttons[i].y > gameHeight-50){
            free(msToTimerText);
            break;
           } 
           free(msToTimerText);
         }
      }
   }
   if(app.status == 2 || app.status == 6){
      app.fetchedList = true;
      SDL_SetRenderDrawColor(renderer,100,100,100,100);
      SDL_RenderFillRect(renderer,&(SDL_Rect){10,100,gameWidth-30,gameHeight-130});
   }
}

void FUpdate_Data_Menu(){
   Update_TextBox();
   Update_Slider();
   app.backgroundMoving += 5*app.deltaTime;
   if(app.backgroundMoving >= 576){
      app.backgroundMoving = 0;
   }

   Update_Buttons();
}