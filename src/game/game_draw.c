#include "game_draw_objects.c"

void Draw_Objects() {
   
   for(int i = 0;i<sizeof(light)/sizeof(light[0]);i++){
      light[i].xDraw = light[i].x;
      light[i].yDraw = light[i].y;
      light[i].widthDraw = light[i].width*camera.scale;
      light[i].heightDraw = light[i].height*camera.scale;
      light[i].xDraw  += camera.x;
      light[i].yDraw  += camera.y;
      light[i].xDraw  = gameWidthBase/2 + (light[i].xDraw - gameWidthBase/2) * camera.scale;
      light[i].yDraw  = gameHeightBase/2 + (light[i].yDraw - gameHeightBase/2) * camera.scale;
   }

   Draw_Platforms();
   Draw_DamagePopups();
   Draw_Specials();
   Draw_Players();
   Draw_Enemies();
   Draw_Particles();

   // Red Target Arrow
   if(player[0].enemyTarget != -1 && player[0].special == 5){
     player[0].angleTargetTexture += 200*app.deltaTime;
     if(player[0].angleTargetTexture > 360){
      player[0].angleTargetTexture = 0;
     }
     SDL_SetTextureAlphaMod(tex_player,exp(player[0].arrowPull/100)*200/exp(3));
     RenderCopyEx(renderer,tex_player,&(SDL_Rect){35,89,30,30},&(SDL_Rect){enemy[player[0].enemyTarget].xDraw,enemy[player[0].enemyTarget].yDraw,7*enemy[player[0].enemyTarget].widthDraw/8,7*enemy[player[0].enemyTarget].heightDraw/8},player[0].angleTargetTexture,NULL,0); 
     SDL_SetTextureAlphaMod(tex_player,255);
   }
   
   Draw_Projectiles();
   
   Draw_Displacements();
   
   Draw_Triggers();
   
   Draw_Deathboxes();
}

void FDraw_Game(){
  
   ///// The data used in the function is transformed to fit the camera's requirements 
   ///// They are camera-manipulated data for only rendering purposes
   // Here lies transformed data
   /////-------------------------------START OF RENDERING
   
   //// Drawing

   SDL_RenderClear(renderer);

   DrawBackground();
   
   Draw_Objects();
   
   DrawLight(app.backgroundOpacity);
   
   FDisplayHUD();

   
   /////-------------------------------END OF RENDERING
}

void FDisplayHUD(){
   // Pause menu
   if(level.Paused){
      buttons[0].reserved = true;
      buttons[1].reserved = true;
      buttons[2].reserved = true;
   
   SDL_SetRenderDrawColor(renderer,200,200,200,150);
   RenderFillRect(renderer,&(SDL_Rect){gameWidthBase/2 - 150,gameHeightBase/2 - 150,300,300});
   }
   else{
    buttons[0].reserved = false;
    buttons[1].reserved  = false;
    buttons[2].reserved  = false; 
   }

   // level ending
   if(level.Finished){
      buttons[3].reserved = true;
      if(level.campaignLevel){
        buttons[4].reserved = true; 
      }
      SDL_SetRenderDrawColor(renderer,100,100,100,200);
      RenderFillRect(renderer,&(SDL_Rect){0,0,gameWidthBase*level.endTransition,100});
      RenderFillRect(renderer,&(SDL_Rect){gameWidthBase,gameHeightBase,-gameWidthBase*level.endTransition,-100});
   }
   else{
      buttons[3].reserved = false;
      buttons[4].reserved = false;
   }
   // Render FPS
   if(app.showFPS){
      char FPS[30];
      sprintf(FPS,"%d FPS\0",(int)(1/app.deltaTime));
      renderText(len(FPS),FPS,5,40,8*len(FPS),10,255,200,(int[3]){255,255,255});
   }
   // Render Timer
   if(!level.Finished){
      char* timer = msToTimer((int)level.timer);
      renderText(8,timer,5,5,8*12,20,255,200,(int[3]){255,255,255});
      free(timer);
   if(mapData.PBTimer>0){
     char* PBtimer = msToTimer(mapData.PBTimer);
     renderText(sizeof("PB"),"PB",5,30,sizeof("PB")*7,10,255,200,(int[3]){200,0,0});
     renderText(8,PBtimer,30,30,8*7,10,255,200,(int[3]){200,200,200});
     free(PBtimer);
   }
   renderText(mapData.mapNameLen,mapData.mapName,gameWidthBase-mapData.mapNameLen*12,5,mapData.mapNameLen*12,18,255,200,(int[3]){255,255,255});
   char* checkpointsLeft = malloc(20);
   sprintf(checkpointsLeft,"%d/%d\0",level.checkpointCount,level.checkpointsSize);
   renderText(len(checkpointsLeft),checkpointsLeft,gameWidthBase-len(checkpointsLeft)*12,30,len(checkpointsLeft)*12,15,255,200,(int[3]){255,255,255});
   free(checkpointsLeft);

   // Checkpoint Timer
   if(level.checkpointShowTimer>0){
      char* checkpointTimer = msToTimer((int)(level.checkpoints[level.checkpointCount-1]));
      renderText(8,checkpointTimer,gameWidthBase/2-4*10,20,8*10,15,255,200,(int[3]){255,255,255});
      if(mapData.ghostInGame){
      char* timeDiff = msToTimer((int)(SDL_abs(level.checkpoints[level.checkpointCount-1]-level.LastCheckpointTimer)));
      if(level.checkpoints[level.checkpointCount-1]<level.LastCheckpointTimer){
       renderText(1,"-",gameWidthBase/2-4*8-8,40,8,15,255,200,(int[3]){0,0,255});    
       renderText(8,timeDiff,gameWidthBase/2-4*8,40,8*8,15,255,200,(int[3]){0,0,255});    
      }
      else {
       renderText(1,"+",gameWidthBase/2-4*8-8,40,8,12,255,200,(int[3]){255,0,0});    
       renderText(8,timeDiff,gameWidthBase/2-4*8,40,8*8,12,255,200,(int[3]){255,0,0});    
      }      
   }
   }
   }
   else {
    renderText(sizeof("Level Complete"),"Level Complete",gameWidthBase/2 - 12*sizeof("Level Complete")/2,20,12*sizeof("Level Complete"),15,255,200,(int[3]){255,255,255});
    
    char* timer = msToTimer((int)level.timer);
    renderText(8,timer,15,15,8*12,20,255,200,(int[3]){255,255,255});
    free(timer);
    
    if(level.newRecord){
      renderText(sizeof("New Record"),"New Record",gameWidthBase/2 - 12*sizeof("New Record")/2,45,sizeof("New Record")*12,15,255,200,(int[3]){0,200,0});
     }
     char* timerStarTime = msToTimer((int)level.StarTime);
     RenderCopy(renderer,tex_star,NULL,&(SDL_Rect){10,42,18,18});   
     renderText(8,timerStarTime,30,45,8*10,16,255,200,(int[3]){255,255,0});
     free(timerStarTime);


     char coins[256];
     sprintf(coins,"%d\0",profile.coins);
     RenderCopy(renderer,tex_coin,NULL,&(SDL_Rect){gameWidthBase-35-10*len(coins),level.endShowCoins-90,20,20}); 
     renderText(len(coins),coins,gameWidthBase-10*len(coins)-10,level.endShowCoins-90,10*len(coins),15,255,200,(int[3]){255,255,255});  
     renderText(3,"+10",gameWidthBase-10*3-10,35,3*10,12,min(255,level.coinsReceivedOpacity),min(255,level.coinsReceivedOpacity),(int[3]){20,255,30});
     
     if(mapData.PBTimer>0){
     char* PBtimer = msToTimer(mapData.PBTimer);
     RenderCopy(renderer,tex_trophy,NULL,&(SDL_Rect){10,72,18,18});
     renderText(8,PBtimer,30,72,8*10,16,255,200,(int[3]){200,200,200});
     free(PBtimer);
     }
  
   }
   if(player[0].special >= 0){
      
      RenderCopy(renderer,tex_specials,&(SDL_Rect){5+150*(player[0].special - 1),0,125,125},&(SDL_Rect){gameWidthBase-player[0].specialshow,gameHeightBase-100,70,70});
   }
   // Health
   char* healthText = malloc(3*sizeof(char));
   SDL_itoa((int)player[0].health,healthText,10);
   renderText(len(healthText),healthText,40,gameHeightBase-60,len(healthText)*18,30,255,255,(int[3]){255,255,255});
   free(healthText);
     
   SDL_SetRenderDrawColor(renderer,0,255,0,255);
   RenderFillRect(renderer,&(SDL_Rect){10,gameHeightBase-25,100*(double)player[0].health/30,10});
   SDL_SetRenderDrawColor(renderer,0,0,0,255);
   RenderDrawRect(renderer,&(SDL_Rect){10,gameHeightBase-25,100,10});

   // Draw textpopups
   for(int i = 0;i<sizeof(textpopups)/sizeof(textpopups[0]);i++){
      if(textpopups[i].reserved){ 
            int textLen = textpopups[i].showProgress/255*len(textpopups[i].textContent);
            if(textLen >= 1){
            SDL_SetRenderDrawColor(renderer,50,50,50,100);

            RenderFillRect(renderer,&(SDL_Rect){(double)(textpopups[i].xPopup)/100*gameWidthBase - textLen*textpopups[i].font/2-10,(double)(textpopups[i].yPopup)/100*gameHeightBase-textpopups[i].font*1.5/2-10,textLen*textpopups[i].font+20,textpopups[i].font*1.5+20});

            renderText(textLen,textpopups[i].textContent,(double)(textpopups[i].xPopup)/100*gameWidthBase - textLen*textpopups[i].font/2,(double)(textpopups[i].yPopup)/100*gameHeightBase-textpopups[i].font*1.5/2,textLen*textpopups[i].font,textpopups[i].font*1.5,255,255,(int[3]){255,255,255}); 
            }
            
            
         
      }
   }
   SDL_SetRenderDrawColor(renderer,0,0,0,max(level.resetTransition,0));
   RenderFillRect(renderer,&(SDL_Rect){0,0,gameWidthBase,gameHeightBase});
   renderButtons();
   GUIHover();
   // Special showcase

}