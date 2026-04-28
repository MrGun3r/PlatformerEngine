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
           renderText(9,msToTimer(atoi(levelsList[i-3].PB)),buttons[i].hoverWidth-70,buttons[i].y,(buttons[i].ButtonFontWidth)*9,buttons[i].ButtonFontHeight,255,200,(int[3]){255,255,255}); 
           
           if(buttons[i].y > gameHeight-50){
            break;
           } 
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
   for(int i = 0;i<sizeof(buttons)/sizeof(buttons[0]);i++){
    if(buttons[i].reserved){
      int yMin = (buttons[i].y);
      int yMax = (buttons[i].y+buttons[i].hoverHeight);
      int xMin = (buttons[i].x);
      int xMax = (buttons[i].x+buttons[i].hoverWidth);
     
      if(mouse.x >= xMin && mouse.x <= xMax && mouse.y >= yMin && mouse.y <= yMax && mouse.left == -1){
        Mix_PlayChannel(-1,Sound_buttonClick,0);
        mouse.left = 0;
        if(app.status == 2){
         if(i == 1){
          if(app.listStartIndex > 0){
            app.listStartIndex-=app.listLengthMax;
            FswitchAppStatus(app.status,2);
             
          }
         }
         else if(i == 2){
            if (app.listLength >= app.listLengthMax){
               app.listStartIndex+=app.listLengthMax;
               FswitchAppStatus(app.status,2);
                
            }
         }
         else if(i > 2){
         for(int j = 0;j<sizeof(platforms)/sizeof(platforms[0]);j++){
          platforms[j].reserved = false;
         }
         sprintf(level.absolutePath,"%s\0",levelsList[i-3].levelPath);       
         appendTransition(app.status,0);
         break; 
         }
        }
        if(app.status == 4){
         // play button
         if(i == 0){
            FswitchAppStatus(app.status,7);
         }
         // Editor
         else if(i == 1){
            appendTransition(app.status,1);
         }
         // Settings
         else if (i == 2){
            FswitchAppStatus(app.status,6);
         }
         else if (i == 3){
            app.WINDOW_LOOP = false;
         }


        }
        else if (app.status == 5){
            if(i == 0){
               SetUsernameProfile();
            }
        }
        else if (app.status == 6){
         if (i == 1){
            // change resolution
            app.resolutionInt++;
            app.resolutionInt=app.resolutionInt%6;
            sprintf(buttons[1].value,"%dx%d",app.resolutions[app.resolutionInt][0],app.resolutions[app.resolutionInt][1]);
            
         }
         else if (i == 2){
            // apply
            app.resolutionUsed = app.resolutionInt;
            gameResolutionChange();
            
         }
         else if (i == 3){
            
            app.showFPS = !app.showFPS;
            sprintf(buttons[3].value,"%d",app.showFPS);
         }
        }
        else if (app.status == 7){
         if(i == 0){
           // Campaign
           appendTransition(app.status,8);
         }
         else if(i == 1){
            // Browse levels
            FswitchAppStatus(app.status,2);
         }
        }
      }
    }
   }
   
}