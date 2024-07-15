void FDraw_Menu(){
   
   SDL_RenderClear(renderer);
   DrawBackground();

   // Draw HUD
   SDL_SetRenderTarget(renderer,HUDLayer);
   FGUIHover();
   renderButtons();
   renderTextBox();
 
   
   if(app.status == 4 || app.status == 2){
      SDL_SetRenderDrawColor(renderer,100,100,100,200);
   SDL_RenderFillRect(renderer,&(SDL_Rect){0,0,gameWidth,75});
   SDL_RenderCopy(renderer,tex_player,&(SDL_Rect){2,0,16,16},&(SDL_Rect){5,5,40,40});
   SDL_SetRenderDrawColor(renderer,0,0,0,255);
   SDL_RenderDrawRect(renderer,&(SDL_Rect){5,5,40,40});
   renderText(len(profile.username),profile.username,50,5,10*len(profile.username),15,255,200,(int[3]){255,255,255});
   char exp[256];
   sprintf(exp,"%d XP\0",profile.experience);
   renderText(len(exp),exp,10,50,10*len(exp),15,255,200,(int[3]){255,255,255});
   
   char coins[256];
   sprintf(coins,"%d\0",profile.coins);
   renderText(len(coins),coins,gameWidth-10*len(coins)-10,10,10*len(coins),15,255,200,(int[3]){255,255,255});   

   int level = log2(profile.experience+2);
   char levelText[256];
   sprintf(levelText,"Level %d\0",level);
   renderText(len(levelText),levelText,50,25,10*len(levelText),15,255,200,(int[3]){255,255,255});
   
   SDL_RenderCopy(renderer,tex_coin,NULL,&(SDL_Rect){gameWidth-35-10*len(coins),5,20,20}); 
   }
   int num = 7;
   
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
   
   
   
   if(app.status == 2){
      app.fetchedList = true;
      SDL_SetRenderDrawColor(renderer,100,100,100,100);
      SDL_RenderFillRect(renderer,&(SDL_Rect){10,100,gameWidth-30,gameHeight-130});
   }
   //renderText(sizeof("Made by mrGun3r"),"Made by mrGun3r",gameWidth-sizeof("Made by mrGun3r")*9,gameHeight - 15,sizeof("Made by mrGun3r")*9,15,255,200,(int[3]){220,220,220});
   SDL_SetRenderTarget(renderer,backgroundLayer);
}

void FUpdate_Data_Menu(){
    
   Update_TextBox();
   app.backgroundMoving += 5*app.deltaTime;
   if(app.backgroundMoving >= 576){
      app.backgroundMoving = 0;
   }
   for(int i = 0;i<sizeof(buttons)/sizeof(buttons[0]);i++){
    if(buttons[i].reserved){
      int yMin = buttons[i].y;
      int yMax = buttons[i].y+buttons[i].hoverHeight;
      int xMin = buttons[i].x;
      int xMax = buttons[i].x+buttons[i].hoverWidth;
     
      if(mouse.x >= xMin && mouse.x <= xMax && mouse.y >= yMin && mouse.y <= yMax && mouse.left == -1){
        
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
         FSetDataMap(levelsList[i-3].levelPath,levelsList[i-3].levelNameSize+12);
         appendTransition(app.status,0);
         break; 
         }
         
        }
        if(app.status == 4){
         // play button
         if(i == 0){
            FswitchAppStatus(app.status,2);
         }
         // Editor
         if(i == 1){
            appendTransition(app.status,1);
         }         
        }
        else if (app.status == 5){
            if(i == 0){
               SetUsernameProfile();
            }
        }
      }
    }
   }
   
}