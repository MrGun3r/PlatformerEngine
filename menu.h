void FDraw_Menu(){
   
   SDL_RenderClear(renderer);
   SDL_RenderCopy(renderer,tex_background,&(SDL_Rect){app.backgroundMoving,0,576,324},&(SDL_Rect){0,0,(windowWidth-app.backgroundMoving*windowWidth/576),windowHeight});
   SDL_RenderCopy(renderer,tex_background,&(SDL_Rect){0,0,app.backgroundMoving,324},&(SDL_Rect){windowWidth-app.backgroundMoving*windowWidth/576,0,app.backgroundMoving*windowWidth/576,windowHeight});
   
   FGUIHover();
   
   for(int i = 0;i<sizeof(buttons)/sizeof(buttons[0]);i++){
      if(buttons[i].reserved){
         renderButtons();

         if(app.status == 2 && i > 0){
           if(!app.fetchedList){
           char* PBTemp = FGetDataMap(levelsList[i-1].levelPath,"m",1,levelsList[i-1].levelNameSize);
           SDL_memcpy(levelsList[i-1].PB,PBTemp,9);
           free(PBTemp);
           }
           renderText(9,msToTimer(atoi(levelsList[i-1].PB)),buttons[i].hoverWidth-70,buttons[i].y,(buttons[i].ButtonFontWidth)*9,buttons[i].ButtonFontHeight,255,200,(int[3]){255,255,255});
         }
         
      }
   }
   
   if(app.status == 2){
      app.fetchedList = true;
      SDL_SetRenderDrawColor(renderer,100,100,100,100);
      SDL_RenderFillRect(renderer,&(SDL_Rect){10,10,windowWidth-30,windowHeight-30});
   }
   renderText(sizeof("Made by mrGun3r"),"Made by mrGun3r",windowWidth-sizeof("Made by mrGun3r")*9,windowHeight - 15,sizeof("Made by mrGun3r")*9,15,255,200,(int[3]){220,220,220});
}


void FUpdate_Data_Menu(){
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
        if(app.status == 2 && i > 0){
         for(int i = 0;i<sizeof(buttons)/sizeof(buttons[0]);i++){
          platforms[i].reserved = false;
         }
         FSetDataMap(levelsList[i-1].levelPath,levelsList[i-1].levelNameSize+12);
         appendTransition(app.status,0);
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
      }
    }
   }
}