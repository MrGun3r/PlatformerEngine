void FDisplayHUD(){
   // Pause menu
   if(level.Paused){
    buttons[0].reserved = true;
    buttons[1].reserved = true;
    buttons[2].reserved = true;
    if(level.campaignLevel){
     buttons[5].reserved = true;
    }
    
   SDL_SetRenderDrawColor(renderer,200,200,200,150);
   SDL_RenderFillRect(renderer,&(SDL_Rect){gameWidth/2 - 150,gameHeight/2 - 150,300,300});
   }
   else{
    buttons[0].reserved = false;
    buttons[1].reserved  = false;
    buttons[2].reserved  = false; 
    buttons[5].reserved = false;
   }

   // level ending
   if(level.Finished){
      buttons[3].reserved = true;
      if(level.campaignLevel){
        buttons[4].reserved = true; 
      }
      SDL_SetRenderDrawColor(renderer,100,100,100,200);
      SDL_RenderFillRect(renderer,&(SDL_Rect){0,0,gameWidth*level.endTransition,100});
      SDL_RenderFillRect(renderer,&(SDL_Rect){gameWidth,gameHeight,-gameWidth*level.endTransition,-100});
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
   renderText(mapData.mapNameLen,mapData.mapName,gameWidth-mapData.mapNameLen*12,5,mapData.mapNameLen*12,18,255,200,(int[3]){255,255,255});
   char* checkpointsLeft = malloc(20);
   sprintf(checkpointsLeft,"%d/%d\0",level.checkpointCount,level.checkpointsSize);
   renderText(len(checkpointsLeft),checkpointsLeft,gameWidth-len(checkpointsLeft)*12,30,len(checkpointsLeft)*12,15,255,200,(int[3]){255,255,255});
   free(checkpointsLeft);

   // Checkpoint Timer
   if(level.checkpointShowTimer>0){
      char* checkpointTimer = msToTimer((int)(level.checkpoints[level.checkpointCount-1]));
      renderText(8,checkpointTimer,gameWidth/2-4*10,20,8*10,15,255,200,(int[3]){255,255,255});
      if(mapData.ghostInGame){
      char* timeDiff = msToTimer((int)(SDL_abs(level.checkpoints[level.checkpointCount-1]-level.LastCheckpointTimer)));
      if(level.checkpoints[level.checkpointCount-1]<level.LastCheckpointTimer){
       renderText(1,"-",gameWidth/2-4*8-8,40,8,15,255,200,(int[3]){0,0,255});    
       renderText(8,timeDiff,gameWidth/2-4*8,40,8*8,15,255,200,(int[3]){0,0,255});    
      }
      else {
       renderText(1,"+",gameWidth/2-4*8-8,40,8,12,255,200,(int[3]){255,0,0});    
       renderText(8,timeDiff,gameWidth/2-4*8,40,8*8,12,255,200,(int[3]){255,0,0});    
      }      
   }
   }
   }
   else {
    renderText(sizeof("Level Complete"),"Level Complete",gameWidth/2 - 12*sizeof("Level Complete")/2,20,12*sizeof("Level Complete"),15,255,200,(int[3]){255,255,255});
    
    char* timer = msToTimer((int)level.timer);
    renderText(8,timer,15,15,8*12,20,255,200,(int[3]){255,255,255});
    free(timer);
    
    if(level.newRecord){
      renderText(sizeof("New Record"),"New Record",gameWidth/2 - 12*sizeof("New Record")/2,45,sizeof("New Record")*12,15,255,200,(int[3]){0,200,0});
     }
     char* timerStarTime = msToTimer((int)level.StarTime);
     SDL_RenderCopy(renderer,tex_star,NULL,&(SDL_Rect){10,42,18,18});   
     renderText(8,timerStarTime,30,45,8*10,16,255,200,(int[3]){255,255,0});
     free(timerStarTime);


     char coins[256];
     sprintf(coins,"%d\0",profile.coins);
     SDL_RenderCopy(renderer,tex_coin,NULL,&(SDL_Rect){gameWidth-35-10*len(coins),level.endShowCoins-90,20,20}); 
     renderText(len(coins),coins,gameWidth-10*len(coins)-10,level.endShowCoins-90,10*len(coins),15,255,200,(int[3]){255,255,255});  
     renderText(3,"+10",gameWidth-10*3-10,35,3*10,12,min(255,level.coinsReceivedOpacity),min(255,level.coinsReceivedOpacity),(int[3]){20,255,30});
     
     if(mapData.PBTimer>0){
     char* PBtimer = msToTimer(mapData.PBTimer);
     SDL_RenderCopy(renderer,tex_trophy,NULL,&(SDL_Rect){10,72,18,18});
     renderText(8,PBtimer,30,72,8*10,16,255,200,(int[3]){200,200,200});
     free(PBtimer);
     }
  
   }
   if(player[0].special >= 0){
      
      SDL_RenderCopy(renderer,tex_specials,&(SDL_Rect){5+150*(player[0].special - 1),0,125,125},&(SDL_Rect){gameWidth-player[0].specialshow,gameHeight-100,70,70});
   }
   // Health
   char* healthText = malloc(3*sizeof(char));
   SDL_itoa((int)player[0].health,healthText,10);
   renderText(len(healthText),healthText,40,gameHeight-60,len(healthText)*18,30,255,255,(int[3]){255,255,255});
   free(healthText);
     
   SDL_SetRenderDrawColor(renderer,0,255,0,255);
   SDL_RenderFillRect(renderer,&(SDL_Rect){10,gameHeight-25,100*(double)player[0].health/30,10});
   SDL_SetRenderDrawColor(renderer,0,0,0,255);
   SDL_RenderDrawRect(renderer,&(SDL_Rect){10,gameHeight-25,100,10});

   // Draw textpopups
   for(int i = 0;i<sizeof(textpopups)/sizeof(textpopups[0]);i++){
      if(textpopups[i].reserved){ 
            int textLen = textpopups[i].showProgress/255*len(textpopups[i].textContent);
            if(textLen >= 1){
            SDL_SetRenderDrawColor(renderer,50,50,50,100);

            SDL_RenderFillRect(renderer,&(SDL_Rect){(double)(textpopups[i].xPopup)/100*gameWidth - textLen*textpopups[i].font/2-10,(double)(textpopups[i].yPopup)/100*gameHeight-textpopups[i].font*1.5/2-10,textLen*textpopups[i].font+20,textpopups[i].font*1.5+20});

            renderText(textLen,textpopups[i].textContent,(double)(textpopups[i].xPopup)/100*gameWidth - textLen*textpopups[i].font/2,(double)(textpopups[i].yPopup)/100*gameHeight-textpopups[i].font*1.5/2,textLen*textpopups[i].font,textpopups[i].font*1.5,255,255,(int[3]){255,255,255}); 
            }
            
            
         
      }
   }
   SDL_SetRenderDrawColor(renderer,0,0,0,max(level.resetTransition,0));
   SDL_RenderFillRect(renderer,&(SDL_Rect){0,0,gameWidth,gameHeight});
   renderButtons();
   FGUIHover();
   // Special showcase
   
   
   
}

void Check_Buttons(){
   for(int i = 0;i<sizeof(buttons)/sizeof(buttons[0]);i++){
      if(buttons[i].reserved){
      int yMin = buttons[i].y;
      int yMax = buttons[i].y+buttons[i].hoverHeight;
      int xMin = buttons[i].x;
      int xMax = buttons[i].x+buttons[i].hoverWidth;   
       
      if(mouse.x >= xMin && mouse.x <= xMax && mouse.y >= yMin && mouse.y <= yMax && mouse.left == -1){
         if(i == 1){
            level.Paused = false;
         }  
         else if(i == 2){
            appendTransition(app.status,4);
         }
         else if(i == 3){
            FGameRestart();
         }
         else if(i == 4){
            profile.levelsUnlocked++;
            FSaveProfile();
            appendTransition(0,8);
            
         }   
      }
      }
   }
}

void FDraw_Game(){
  
   ///// The data used in the function is transformed to fit the camera's requirements 
   ///// They are camera-manipulated data for only rendering purposes
   // Here lies transformed data
   /////-------------------------------START OF RENDERING
   
       
   
  
   if(!camera.freeCam){
     camera.x += (-player[0].x-player[0].width/2+gameWidth/2 - camera.x)*10*app.deltaTime;
     camera.y += (-player[0].y-player[0].height/2+gameHeight/2 - camera.y)*10*app.deltaTime;
   }
   else{
      camera.x += (camera.xReal - camera.x)*10*app.deltaTime;
      camera.y += (camera.yReal - camera.y)*10*app.deltaTime;
   }

   if (camera.x > -gameWidth/(2*camera.scale) + gameWidth/2 - mapData.xMin) {
       camera.x = -gameWidth/(2*camera.scale) + gameWidth/2 - mapData.xMin;
   }
   else if (camera.x < gameWidth/(2*camera.scale) + gameWidth/2 - mapData.xMax){
      camera.x = gameWidth/(2*camera.scale) + gameWidth/2 - mapData.xMax;
   }

   if (camera.y > -gameHeight/(2*camera.scale) + gameHeight/2 - mapData.yMin) {
       camera.y = -gameHeight/(2*camera.scale) + gameHeight/2 - mapData.yMin;
   }
   else if (camera.y < gameHeight/(2*camera.scale) + gameHeight/2 - mapData.yMax){
      camera.y = gameHeight/(2*camera.scale) + gameHeight/2 - mapData.yMax;
   }
   
   
   app.backgroundMoving += player[0].veloX/5*app.deltaTime;
   ROUND_TO(app.backgroundMoving,0,backgrounds[app.backgroundInt].textureWidth)
   if(player[0].special >= 0){
      player[0].specialshow += (100 - player[0].specialshow)*10*app.deltaTime;
   }
   SDL_RenderClear(renderer);
   DrawBackground();
   
   for(int i = 1;i<sizeof(light)/sizeof(light[0]);i++){
      light[i].xDraw = light[i].x;
      light[i].yDraw = light[i].y;
      light[i].widthDraw = light[i].width*camera.scale;
      light[i].heightDraw = light[i].height*camera.scale;
      light[i].xDraw  += camera.x;
      light[i].yDraw  += camera.y;
      light[i].xDraw  = gameWidth/2 + (light[i].xDraw - gameWidth/2) * camera.scale;
      light[i].yDraw  = gameHeight/2 + (light[i].yDraw - gameHeight/2) * camera.scale;
   }

   

    // Draw platforms
   for(int i = 1;i<sizeof(platforms)/sizeof(platforms[0]);i++){
      if(platforms[i].reserved && !platforms[i].collidable){

         // Camera offsetted data !
         platforms[i].xDraw = platforms[i].x;
         platforms[i].yDraw = platforms[i].y;
         platforms[i].widthDraw = platforms[i].width*camera.scale;
         platforms[i].heightDraw = platforms[i].height*camera.scale;
         platforms[i].xDraw  += camera.x;
         platforms[i].yDraw  += camera.y;
         platforms[i].xDraw  = gameWidth/2 + (platforms[i].xDraw - gameWidth/2) * camera.scale;
         platforms[i].yDraw  = gameHeight/2 + (platforms[i].yDraw - gameHeight/2) * camera.scale;
         if(!Rect_inBounds(platforms[i].xDraw,platforms[i].yDraw,platforms[i].widthDraw,platforms[i].heightDraw))
         {
            continue;
         }
         
         // Add texture to platform
         FtexturePlatform(i);
      }
   }
   
   // Draw Nodes
   
   for(int i = 1;i<sizeof(platforms)/sizeof(platforms[0]);i++){
      if(platforms[i].reserved && platforms[i].collidable){

         // Camera offsetted data !
         platforms[i].widthDraw = platforms[i].width*camera.scale;
         platforms[i].heightDraw = platforms[i].height*camera.scale;
         platforms[i].xDraw  = gameWidth/2 + (platforms[i].x + camera.x - gameWidth/2) * camera.scale;
         platforms[i].yDraw  = gameHeight/2 + (platforms[i].y + camera.y - gameHeight/2) * camera.scale;
         // Add texture to platform
         FtexturePlatform(i);
      }
   }
   // Draw popup damages
   for(int i = 0;i<sizeof(damagepopups)/sizeof(damagepopups[0]);i++){
      if(damagepopups[i].reserved)
      {damagepopups[i].xDraw = gameWidth/2 + (damagepopups[i].x + camera.x - gameWidth/2) * camera.scale;
      damagepopups[i].yDraw = gameHeight/2 + (damagepopups[i].y + camera.y - gameHeight/2) * camera.scale;
      damagepopups[i].sizeDraw = damagepopups[i].size*camera.scale;
      char* buffer = malloc(20*sizeof(char));
      int numSize = len(buffer);
      SDL_itoa(damagepopups[i].number,buffer,10);
      int colors[3] = {0,0,0};
      if(damagepopups[i].number < 0){
         colors[0] = 255;
      }
      else{
         colors[1] = 255;
      }
      renderText(numSize,buffer,damagepopups[i].xDraw,damagepopups[i].yDraw,numSize*damagepopups[i].sizeDraw,damagepopups[i].sizeDraw*1.2,damagepopups[i].opacity,damagepopups[i].opacity,colors);
      free(buffer);
      }
   }
   for (int i = 0;i<sizeof(specials)/sizeof(specials[0]);i++){
      if(specials[i].reserved){
         // Camera offsetted data !
         specials[i].xDraw = specials[i].x;
         specials[i].yDraw = specials[i].y;
         specials[i].sizeDraw = specials[i].size*camera.scale;
       
         specials[i].xDraw  += camera.x;
         specials[i].yDraw  += camera.y;
         specials[i].xDraw  = gameWidth/2 + (specials[i].xDraw - gameWidth/2) * camera.scale;
         specials[i].yDraw  = gameHeight/2 + (specials[i].yDraw - gameHeight/2) * camera.scale;
         if(specials[i].taken){
            SDL_SetTextureAlphaMod(tex_specials,50);
         }

         SDL_RenderCopyEx(renderer,tex_specials,&(SDL_Rect){5+150*(specials[i].type - 1),0,125,125},&(SDL_Rect){specials[i].xDraw,specials[i].yDraw,specials[i].sizeDraw,specials[i].sizeDraw},0,NULL,0);

         SDL_SetTextureAlphaMod(tex_specials,255);
   }
   }

   // Draw player
   // i == 0 => player
   // i > 0 => Ghost
   
   for(int i = sizeof(player)/sizeof(player[0]) - 1;i>=0;i--){
      // invis 
      if(player[i].invisTimer > 0 && fmod(player[i].invisTimer,200) > 100 && !player[i].dead){
         continue;
      }


      if((i > 0 && mapData.ghostInGame) || i == 0){  
       player[i].widthDraw = player[i].width;
       player[i].heightDraw = player[i].height;
       player[i].widthDraw  *= camera.scale;
       player[i].heightDraw *= camera.scale;
       player[i].xDraw = gameWidth/2 + (player[i].x + camera.x - gameWidth/2) * camera.scale;
       player[i].yDraw = gameHeight/2 + (player[i].y + camera.y - gameHeight/2) * camera.scale;
      for(int j = 0;j<5;j++){
         if(player[i].playerTrails[j][2] > 10){
           double playerTrailXDraw = gameWidth/2 + (player[i].playerTrails[j][0] + camera.x - gameWidth/2) * camera.scale;
           double playerTrailYDraw = gameHeight/2 + (player[i].playerTrails[j][1] + camera.y - gameHeight/2) * camera.scale;
           SDL_SetTextureAlphaMod(tex_player,player[i].playerTrails[j][2]);
           
           SDL_RenderCopyEx(renderer,tex_player,&(SDL_Rect){2+((int)(player[0].playerTrails[j][3]))*24,2,15,18},&(SDL_Rect){playerTrailXDraw,playerTrailYDraw,player[i].widthDraw,player[i].heightDraw},0,NULL,(int)player[0].playerTrails[j][4]); 
            
            } 
         }
         SDL_SetTextureAlphaMod(tex_player,255); 
       
      if(i > 0){
         SDL_SetTextureAlphaMod(tex_player,100);
      }
      
      SDL_RendererFlip flip1 = (1 - player[i].direction)/2;
   
   if(player[i].dead){
      if((int)(player[0].deathAnimationTimer/1000)>=1 && (int)(player[0].deathAnimationTimer/1000) <= 6){
      SDL_RenderCopyEx(renderer,tex_player,&(SDL_Rect){95+(int)(player[0].deathAnimationTimer/1000)*24,24,22,22},&(SDL_Rect){player[i].xDraw,player[i].yDraw,player[i].widthDraw,player[i].heightDraw},0,NULL,SDL_FLIP_NONE);
      }
      else if((int)(player[0].deathAnimationTimer/1000) <= 6){
         SDL_RenderCopyEx(renderer,tex_player,&(SDL_Rect){98,26,16,16},&(SDL_Rect){player[i].xDraw,player[i].yDraw,player[i].widthDraw,player[i].heightDraw},0,NULL,SDL_FLIP_NONE);
      }
   }
   else if (player[i].groundPound || player[i].keys.down){
      player[i].width = player[i].Owidth;
     SDL_RenderCopyEx(renderer,tex_player,&(SDL_Rect){168,0,16,18},&(SDL_Rect){player[i].xDraw,player[i].yDraw,player[i].widthDraw,player[i].heightDraw},0,NULL,flip1);
   }
   else if (player[i].attack && player[i].specialDelayTimer < player[i].specialDelay){
     int attackInt = (int)(player[i].specialDelayTimer*2/(double)player[i].specialDelay);
     player[i].width = player[i].Owidth; 
     SDL_RenderCopyEx(renderer,tex_player,&(SDL_Rect){191+25*attackInt,2,16,16},&(SDL_Rect){player[i].xDraw,player[i].yDraw,player[i].widthDraw,player[i].heightDraw},0,NULL,flip1);  
   }
   else if(player[i].onWall){
      if(player[i].onWall > 0){
      flip1 = SDL_FLIP_HORIZONTAL;
      }
      else {flip1 = SDL_FLIP_NONE;}
      player[i].width = player[i].Owidth;
   SDL_RenderCopyEx(renderer,tex_player,&(SDL_Rect){73,27,16,16},&(SDL_Rect){player[i].xDraw,player[i].yDraw,player[i].widthDraw,player[i].heightDraw},0,NULL,flip1);
   }
 
   else if((int)player[i].accX != 0 && (int)player[i].jumpVelo == 0){
   if(SDL_abs(player[i].veloX)>=(player[i].width+player[i].height)*200/40){
      player[i].width = player[i].Owidth + 3;
      SDL_RenderCopyEx(renderer,tex_player,&(SDL_Rect){1+((int)(player[i].animationIndex) % 6 )*24,47,18,16},&(SDL_Rect){player[i].xDraw,player[i].yDraw,player[i].widthDraw,player[i].heightDraw},0,NULL,flip1);
   }
   else{
      player[i].width = player[i].Owidth;
   SDL_RenderCopyEx(renderer,tex_player,&(SDL_Rect){2+((int)(player[i].animationIndex) % 6 )*24,2,15,18},&(SDL_Rect){player[i].xDraw,player[i].yDraw,player[i].widthDraw,player[i].heightDraw},0,NULL,flip1);
   }
   }
   else if ((int)player[i].jumpVelo == 0){
      player[i].width = player[i].Owidth;
     SDL_RenderCopyEx(renderer,tex_player,&(SDL_Rect){2+((int)(player[i].idleIndex) % 2 )*24,24,15,18},&(SDL_Rect){player[i].xDraw,player[i].yDraw,player[i].widthDraw,player[i].heightDraw},0,NULL,flip1);
   }
   else{
      player[i].width = player[i].Owidth;
      SDL_RenderCopyEx(renderer,tex_player,&(SDL_Rect){49,24,15,18},&(SDL_Rect){player[i].xDraw,player[i].yDraw,player[i].widthDraw,player[i].heightDraw},0,NULL,flip1);
   }
   if(player[i].attack && player[i].special == 1){
      double xAttackDraw = gameWidth/2 + (player[i].attackX + camera.x - gameWidth/2) * camera.scale;
      double yAttackDraw = gameHeight/2 + (player[i].attackY + camera.y - gameHeight/2) * camera.scale;
      double sizeattackDraw = player[0].attackSize*camera.scale;
      SDL_RenderCopyEx(renderer,tex_player,&(SDL_Rect){player[i].attackDrawInt*23,63,20,25},&(SDL_Rect){xAttackDraw,yAttackDraw,sizeattackDraw,sizeattackDraw},0,NULL,(1-player[i].attackDirection)/2);
   }
   if(player[i].special == 5){
      SDL_RenderCopyEx(renderer,tex_player,&(SDL_Rect){(int)(player[i].arrowPull/100)*23+170,63,20,25},&(SDL_Rect){player[i].xDraw+player[i].widthDraw/2,player[i].yDraw+player[i].heightDraw/3,4*player[i].widthDraw/5,4*player[i].heightDraw/5},player[i].ProjectileAngle,&(SDL_Point){0,4*player[i].heightDraw/10},0);
      
   }
   if(player[i].EButtonOpacity > 1){
      SDL_SetTextureAlphaMod(tex_player,player[i].EButtonOpacity);
      SDL_RenderCopy(renderer,tex_player,&(SDL_Rect){0,85,32,32},&(SDL_Rect){player[i].xDraw+player[i].widthDraw/8,player[i].yDraw-player[i].heightDraw/1.5,player[i].widthDraw/1.5,player[i].heightDraw/1.5});
   }
   
   SDL_SetTextureAlphaMod(tex_player,255);
   // Draw grappling hook
   if(player[i].grappling){
   double grappleDrawX = gameWidth/2 + (player[i].grappleX + camera.x - gameWidth/2) * camera.scale;
   double grappleDrawY = gameHeight/2 + (player[i].grappleY + camera.y - gameHeight/2) * camera.scale;
   SDL_RenderCopyEx(renderer,tex_player,&(SDL_Rect){0,190,5,5},&(SDL_Rect){grappleDrawX,grappleDrawY-2,player[i].grappleLength*camera.scale,4},player[i].grappleAngle*180/PI,&(SDL_Point){0,5},0);
   SDL_SetRenderDrawColor(renderer,200,200,200,255);
   SDL_RenderFillRect(renderer,&(SDL_Rect){grappleDrawX-5,grappleDrawY-5,10,10});

   }
   if(player[i].grappleFailed > 50){
      SDL_SetTextureAlphaMod(tex_grappleFail,player[i].grappleFailed);
      SDL_RenderCopy(renderer,tex_grappleFail,NULL,&(SDL_Rect){player[i].xDraw-150/2*camera.scale+player[i].widthDraw/2,player[i].yDraw-150/2*camera.scale+player[i].heightDraw/2,150*camera.scale,150*camera.scale});
   }    
}    
   }
   // Draw enemy
   for(int i = 0;i<sizeof(enemy)/sizeof(enemy[0]);i++){
      if(enemy[i].reserved && !enemy[i].killed){
         enemy[i].xDraw = gameWidth/2 + (enemy[i].x + camera.x - gameWidth/2) * camera.scale;
         enemy[i].yDraw = gameHeight/2 + (enemy[i].y + camera.y - gameHeight/2) * camera.scale;
         enemy[i].widthDraw = enemy[i].width*camera.scale;
         enemy[i].heightDraw = enemy[i].height*camera.scale;
         if(enemy[i].type == 1){
           if(enemy[i].attackCoolDown > 50){
           SDL_RenderCopyEx(renderer,tex_enemy,&(SDL_Rect){0,0,80,80},&(SDL_Rect){enemy[i].xDraw,enemy[i].yDraw,enemy[i].widthDraw,enemy[i].heightDraw},enemy[i].angle*180/PI -180,NULL,SDL_FLIP_NONE);
           }
          else{
            SDL_RenderCopyEx(renderer,tex_enemy,&(SDL_Rect){100,0,80,80},&(SDL_Rect){enemy[i].xDraw,enemy[i].yDraw,enemy[i].widthDraw,enemy[i].heightDraw},enemy[i].angle*180/PI -180,NULL,SDL_FLIP_NONE);
          } 
         }
         if(enemy[i].type == 2){
           if(enemy[i].attackCoolDown > 50){
           SDL_RenderCopyEx(renderer,tex_enemy,&(SDL_Rect){3+24*((int)enemy[i].textureAnimationInt % 7),120,16,18},&(SDL_Rect){enemy[i].xDraw,enemy[i].yDraw,enemy[i].widthDraw,enemy[i].heightDraw},0,NULL,(1-enemy[i].direction)/2);
           }
          else{
            SDL_RenderCopyEx(renderer,tex_enemy,&(SDL_Rect){170,120,16,18},&(SDL_Rect){enemy[i].xDraw,enemy[i].yDraw,enemy[i].widthDraw,enemy[i].heightDraw},0,NULL,(1-enemy[i].direction)/2);
          } 
         }
         if(enemy[i].type == 3){
           if(enemy[i].attackCoolDown > 50){
           SDL_RenderCopyEx(renderer,tex_enemy,&(SDL_Rect){3+24*((int)enemy[i].textureAnimationInt % 7),144,16,18},&(SDL_Rect){enemy[i].xDraw,enemy[i].yDraw,enemy[i].widthDraw,enemy[i].heightDraw},0,NULL,(1-enemy[i].direction)/2);
           }
          else{
            SDL_RenderCopyEx(renderer,tex_enemy,&(SDL_Rect){170,144,16,18},&(SDL_Rect){enemy[i].xDraw,enemy[i].yDraw,enemy[i].widthDraw,enemy[i].heightDraw},0,NULL,(1-enemy[i].direction)/2);
          } 
         }
         if(enemy[i].type == 4){
           if(enemy[i].attackCoolDown > 50){
           SDL_RenderCopyEx(renderer,tex_enemy,&(SDL_Rect){2+24*((int)enemy[i].textureAnimationInt % 7),169,20,20},&(SDL_Rect){enemy[i].xDraw,enemy[i].yDraw,enemy[i].widthDraw,enemy[i].heightDraw},0,NULL,(1-enemy[i].direction)/2);
           }
          else{
            SDL_RenderCopyEx(renderer,tex_enemy,&(SDL_Rect){169,169,19,22},&(SDL_Rect){enemy[i].xDraw,enemy[i].yDraw,enemy[i].widthDraw,enemy[i].heightDraw},0,NULL,(1-enemy[i].direction)/2);
          } 
         }
         if(enemy[i].type == 5){
           if(enemy[i].attackCoolDown > 50 && !enemy[i].attackPrepare){
           SDL_RenderCopyEx(renderer,tex_enemy,&(SDL_Rect){3+24*((int)enemy[i].textureAnimationInt % 7),192,16,22},&(SDL_Rect){enemy[i].xDraw,enemy[i].yDraw,enemy[i].widthDraw,enemy[i].heightDraw},0,NULL,(1-enemy[i].direction)/2);
           }
           else if(enemy[i].attackPrepare){
            SDL_RenderCopyEx(renderer,tex_enemy,&(SDL_Rect){192,192,16,22},&(SDL_Rect){enemy[i].xDraw,enemy[i].yDraw,enemy[i].widthDraw,enemy[i].heightDraw},0,NULL,(1-enemy[i].direction)/2);
           }
          else{
            SDL_RenderCopyEx(renderer,tex_enemy,&(SDL_Rect){170,192,16,22},&(SDL_Rect){enemy[i].xDraw,enemy[i].yDraw,enemy[i].widthDraw,enemy[i].heightDraw},0,NULL,(1-enemy[i].direction)/2);
          } 
         }
      }
   }
   // Red Target Arrow
   if(player[0].enemyTarget != -1 && player[0].special == 5){
     player[0].angleTargetTexture += 200*app.deltaTime;
     if(player[0].angleTargetTexture > 360){
      player[0].angleTargetTexture = 0;
     }
     SDL_SetTextureAlphaMod(tex_player,exp(player[0].arrowPull/100)*200/exp(3));
     SDL_RenderCopyEx(renderer,tex_player,&(SDL_Rect){35,89,30,30},&(SDL_Rect){enemy[player[0].enemyTarget].xDraw,enemy[player[0].enemyTarget].yDraw,7*enemy[player[0].enemyTarget].widthDraw/8,7*enemy[player[0].enemyTarget].heightDraw/8},player[0].angleTargetTexture,NULL,0); 
     SDL_SetTextureAlphaMod(tex_player,255);
   }
   
   for(int i = 0;i<sizeof(projectiles)/sizeof(projectiles[0]);i++){
      if(projectiles[i].reserved){
         projectiles[i].xDraw = gameWidth/2 + (projectiles[i].x + camera.x - gameWidth/2) * camera.scale;
         projectiles[i].yDraw = gameHeight/2 + (projectiles[i].y + camera.y - gameHeight/2) * camera.scale;
         projectiles[i].widthDraw = projectiles[i].width*camera.scale;
         projectiles[i].heightDraw = projectiles[i].height*camera.scale;
         if(projectiles[i].projectileType == 1){
            SDL_RenderCopyEx(renderer,tex_player,&(SDL_Rect){145,68,20,13},&(SDL_Rect){projectiles[i].xDraw,
            projectiles[i].yDraw,projectiles[i].widthDraw,projectiles[i].heightDraw},projectiles[i].angle,NULL,0);
         }
         else if(projectiles[i].projectileType == 2){
            if(!projectiles[i].fromEnemy){
              SDL_RenderCopyEx(renderer,tex_player,&(SDL_Rect){0,120,56,56},&(SDL_Rect){projectiles[i].xDraw,
            projectiles[i].yDraw,projectiles[i].widthDraw,projectiles[i].heightDraw},projectiles[i].angle,NULL,0); 
            }
            else{
               SDL_RenderCopyEx(renderer,tex_enemy,&(SDL_Rect){3,214,56,56},&(SDL_Rect){projectiles[i].xDraw,
            projectiles[i].yDraw,projectiles[i].widthDraw,projectiles[i].heightDraw},projectiles[i].angle,NULL,0); 
            }
            
         }
      }
   }
   // Draw Particles 
   for(int i = 0;i<sizeof(particles)/sizeof(particles[0]);i++){
      if(particles[i].reserved){
         // Camera offsetted data !
         particles[i].xDraw = particles[i].x;
         particles[i].yDraw = particles[i].y;
         particles[i].sizeDraw = particles[i].size*camera.scale;
         particles[i].xDraw  += camera.x;
         particles[i].yDraw  += camera.y;
         particles[i].xDraw  = gameWidth/2 + (particles[i].xDraw - gameWidth/2) * camera.scale;
         particles[i].yDraw  = gameHeight/2 + (particles[i].yDraw - gameHeight/2) * camera.scale;
         SDL_SetRenderDrawColor(renderer,particles[i].red,particles[i].green,particles[i].blue,255);
         //SDL_SetTextureColorMod(NULL,particles[i].red,particles[i].green,particles[i].blue);
         // Render Particle
         SDL_RenderCopyEx(renderer,particles[i].texture,NULL,&(SDL_Rect){particles[i].xDraw,particles[i].yDraw,particles[i].sizeDraw,particles[i].sizeDraw},particles[i].rotation,NULL,SDL_FLIP_NONE);
         //SDL_RenderFillRect(renderer,&(SDL_Rect){particles[i].xDraw,particles[i].yDraw,particles[i].sizeDraw,particles[i].sizeDraw});
      }
   }
   ///////
   
   for(int i = 0;i<sizeof(displacement)/sizeof(displacement[0]);i++){
      if(displacement[i].reserved){
        displacement[i].xDraw = displacement[i].x;
        displacement[i].yDraw = displacement[i].y;
        displacement[i].widthDraw = displacement[i].width*camera.scale;
        displacement[i].heightDraw = displacement[i].height*camera.scale;
        displacement[i].xDraw  += camera.x;
        displacement[i].yDraw  += camera.y;
        displacement[i].xDraw  = gameWidth/2 + (displacement[i].xDraw - gameWidth/2) * camera.scale;
        displacement[i].yDraw  = gameHeight/2 + (displacement[i].yDraw - gameHeight/2) * camera.scale;
         
         FtextureQuad(displacement[i].xDraw,displacement[i].yDraw,displacement[i].widthDraw,displacement[i].heightDraw,tex_displacement,displacement[i].opacity,displacement[i].type);
         SDL_SetTextureAlphaMod(tex_displacement,255);
      }
   }
   for(int i = 1;i<sizeof(triggers)/sizeof(triggers[0]);i++){
      if(triggers[i].reserved){         
         // Camera offsetted data !
         triggers[i].xDraw = triggers[i].x + camera.x;
         triggers[i].yDraw = triggers[i].y + camera.y;
         triggers[i].widthDraw = triggers[i].width*camera.scale;
         triggers[i].heightDraw = triggers[i].height*camera.scale;
      
         triggers[i].xDraw      -= gameWidth/2;
         triggers[i].yDraw      -= gameHeight/2;
         triggers[i].xDraw      *= camera.scale;
         triggers[i].yDraw      *= camera.scale;
         triggers[i].xDraw      += gameWidth/2;
         triggers[i].yDraw      += gameHeight/2;
         

         FtextureQuad(triggers[i].xDraw,triggers[i].yDraw,triggers[i].widthDraw,triggers[i].heightDraw,tex_trigger,triggers[i].opacity,0);
      }
   }
   

   for (int i = 0;i<sizeof(deathbox)/sizeof(deathbox[0]);i++){
      if(deathbox[i].reserved){
         // Camera offsetted data !
         deathbox[i].xDraw = deathbox[i].x;
         deathbox[i].yDraw = deathbox[i].y;
         deathbox[i].widthDraw = deathbox[i].width*camera.scale;
         deathbox[i].heightDraw = deathbox[i].height*camera.scale;
         deathbox[i].xDraw  += camera.x;
         deathbox[i].yDraw  += camera.y;
         deathbox[i].xDraw  = gameWidth/2 + (deathbox[i].xDraw - gameWidth/2) * camera.scale;
         deathbox[i].yDraw  = gameHeight/2 + (deathbox[i].yDraw - gameHeight/2) * camera.scale;
         
         FtextureQuad(deathbox[i].xDraw,deathbox[i].yDraw,deathbox[i].widthDraw,deathbox[i].heightDraw,tex_skull,deathbox[i].opacity,0);
   }
   }
   

   DrawLight(app.backgroundOpacity);
   
   FDisplayHUD();

   
   /////-------------------------------END OF RENDERING
}

void playerHurt(int i,double damage){
   if(player[i].invisTimer > 0){
      return;
   }
   Mix_PlayChannel(-1,Sound_Death,0);
   player[i].health -= damage;
   addDamagePopUp(-10,player[i].x,player[i].y-10,10,0,-15);
   player[i].invisTimer = 2000;
   player[i].veloX *= -0.5;
   player[i].veloY *= -0.25;
   if(player[i].health < 0){
      player[i].dead = true;
   }
}

void enemyHurt(int i , double damage){
   Mix_PlayChannel(-1,Sound_enemyHurt,0);
   enemy[i].veloX = 0;
   enemy[i].health -= damage;
   
   addDamagePopUp(-10,enemy[i].x,enemy[i].y-10,10,0,-15);

   if (enemy[i].health <= 0.01f){
      enemy[i].killed = true;
   } 
   enemy[i].attackCoolDown = 0;
   if(enemy[i].killed){
         Mix_PlayChannel(-1,Sound_enemyDead,0);
         
      for(int k = 0;k<15;k++){
         addParticle(tex_explosion,enemy[i].x,enemy[i].y,(((double)(rand()%100))/100-0.5)*100,(((double)(rand()%100))/100-0.5)*100,20,255,255,255,2*PI*(rand()%100)/100);
      }
         
   } 
   
}


void FUpdate_Data(){
 ///// Player play sounds
 ////// 
   level.coinsReceivedOpacity -= 255*app.deltaTime;
   if(level.coinsReceivedOpacity < 0){
      level.coinsReceivedOpacity = 0;
   }
   camera.scale += ( camera.scaleReal - camera.scale)*app.deltaTime*5;
   if(level.Finished){
      if(level.endTransition < 1){
         level.endTransition += 2*app.deltaTime;
      }
      if(level.endShowCoins < 100){
         level.endShowCoins += 200*app.deltaTime;
      }
      camera.scaleReal = 6;
   }
      Check_Buttons();
   
    if(level.resetTransition>0){
      level.resetTransition -= 1000*app.deltaTime;
    }
   if(level.checkpointShowTimer > 0){
      level.checkpointShowTimer -= 1000*app.deltaTime;
   }

   if(player[0].keys.r && level.Started){
    FGameRestart();
   }
    if(!level.Paused && !level.Finished){
    if(app.inputChange && !level.Finished && level.Started && level.campaignLevel){
      char keyInputChange[200];
      sprintf(keyInputChange,"i%d:%d,%d,%d,%d,%d,%d,%d,%d,%f,%f;\n\0",mapData.fileadditionIndex,(int)level.timer,player[0].keys.up,player[0].keys.left,player[0].keys.right,player[0].keys.down,player[0].keys.shift,(int)player[0].x,(int)player[0].y,player[0].veloX,player[0].veloY);
      mapData.fileadditionIndex++;
      SDL_memcpy(&level.keyInputs[level.keyInputsSize],keyInputChange,len(keyInputChange));  
      level.keyInputsSize += len(keyInputChange);
      if(level.keyInputsSize >= 1024){
         FaddReplay(false);
         level.tempFileMade = true;
         level.keyInputsSize = 0;
      }
      app.inputChange = false;
   }
    FPlayer_Movement();
    if(level.Started){
      FEnemy_Movement();
    }
    

    for(int i = 0;i<sizeof(damagepopups)/sizeof(damagepopups[0]);i++){
      if(damagepopups[i].reserved){
         
         damagepopups[i].opacity -= 255*app.deltaTime;
         if(damagepopups[i].opacity < 0){
            damagepopups[i].opacity = 0;
            damagepopups[i].reserved = false;
         }
         damagepopups[i].x += damagepopups[i].veloX*app.deltaTime;
         damagepopups[i].y += damagepopups[i].veloY*app.deltaTime;
      }
    }
   // enemy collision
   
    for(int i = 0;i<sizeof(enemy)/sizeof(enemy[0]);i++){
      if(enemy[i].reserved && !enemy[i].killed){
         
         if(player[0].arrowPull < 10 || player[0].special == 6){
          double distance_player_enemy = sqrt(pow(player[0].x-enemy[i].x,2)+pow(player[0].y-enemy[i].y,2));
         
          if(distance_player_enemy < 300 && (player[0].enemyTargetDistance > distance_player_enemy || player[0].enemyTarget == -1) && (fabs(player[0].x-enemy[i].x) > 1)){

            player[0].enemyTargetDistance = distance_player_enemy;
            player[0].enemyTarget = i;
            
           
         
          }
         }
         
         if(enemy[i].attackCoolDown <= 200){
            enemy[i].attackCoolDown += 200*app.deltaTime;
         }
         if(enemy[i].type == 2){
            enemy[i].onPlatform = false;
         }



         
         if(!player[0].dead && rectCollision((SDL_Rect){enemy[i].x+enemy[i].width*0.25,enemy[i].y+enemy[i].height*0.25,enemy[i].width*0.5,enemy[i].height*0.5},(SDL_Rect){player[0].x,player[0].y,player[0].width,player[0].height})){
            playerHurt(0,10);
         }
         
         
         
         if(player[0].special == 1 && player[0].attack && enemy[i].attackCoolDown > 100 && rectCollision((SDL_Rect){player[0].attackX,player[0].attackY,player[0].attackSize,player[0].attackSize},(SDL_Rect){enemy[i].x,enemy[i].y,enemy[i].width,enemy[i].height})){

            enemyHurt(i,10);
            enemy[i].bumpX = 175*player[0].attackDirection;
            
         } 
      }
   }
   for(int i = 0;i<sizeof(textpopups)/sizeof(textpopups[0]);i++){
      if(textpopups[i].reserved){ 
         if(rectCollision((SDL_Rect){textpopups[i].x,textpopups[i].y,textpopups[i].width,textpopups[i].height},(SDL_Rect){player[0].x,player[0].y,player[0].width,player[0].height})){
            if(textpopups[i].showProgress < 255){
               if(textpopups[i].showProgress < 252){
                  Mix_PlayChannel(-1,Sound_textTick,0);
               }
               textpopups[i].showProgress += 1000*app.deltaTime;
               
               if(textpopups[i].showProgress >= 255){
                 textpopups[i].showProgress = 255;
               }
            }
         }
         else{
            textpopups[i].showProgress -= 1000*app.deltaTime;
            if(textpopups[i].showProgress<0){
              textpopups[i].showProgress = 0;
            }
         }
      }
   }
   // Player Attack
   if(player[0].special == 1){
      if(player[0].specialDelayTimer >= player[0].specialDelay){
      player[0].attack = false;
      }
        
      if(player[0].specialDelayTimer < player[0].specialDelay){
         player[0].attackDrawInt = (int)((player[0].specialDelayTimer)*6/player[0].specialDelay);
      }
      
      
      
   }
   if(player[0].enemyTarget != -1 && (enemy[player[0].enemyTarget].killed)){
      player[0].enemyTarget = -1;
   }
   
   if(player[0].grappleFailed > 0){
      player[0].grappleFailed -= 500*app.deltaTime;
      CLAMP_MIN(player[0].grappleFailed,0);
   }

   // Player special delay usage
   if(player[0].specialDelayTimer < 5*player[0].specialDelay){
         player[0].specialDelayTimer += 1000*app.deltaTime;
   }
   
    
   // Player Collision
   player[0].onPlatform = 0;
   player[0].onWall = 0;
   player[1].onPlatform = 0;
   player[1].onWall = 0;
   
   // Arrow Movement
   for(int i = 0;i<sizeof(projectiles)/sizeof(projectiles[0]);i++){
      if(projectiles[i].reserved){
         if(projectiles[i].projectileType == 1){
            arrowMovement(i);
         }
         else if(projectiles[i].projectileType == 2){
            projectileMovement(i);
         }   
      
         projectiles[i].despawnTime += 1*app.deltaTime;
         if(projectiles[i].despawnTime > 5){
            projectiles[i].reserved = false;
            if(!projectiles[i].fromEnemy){
             player[0].projectileThrown--;  
            }
            projectiles[i].despawnTime = 0;
         }
         if((fabs(projectiles[i].veloX) > 10 || fabs(projectiles[i].veloY) > 10)){
            if(projectiles[i].projectileType == 1){
               for(int j = 1;j<sizeof(platforms)/sizeof(platforms[0]);j++){
               if(platforms[j].reserved && platforms[j].collidable){
                  if(FCheck_Collision_Rect_Platform((SDL_Rect){projectiles[i].x,projectiles[i].y,projectiles[i].width,projectiles[i].height},j)){
                     projectiles[i].veloX = 0;
                     projectiles[i].veloY = 0;
                     projectiles[i].accY = 0;
                     break;
                   }
               }
         }
            }
            
         // Arrow Enemy Collision
         if(!projectiles[i].fromEnemy){
            for(int j = 0;j<sizeof(enemy)/sizeof(enemy[0]);j++){
               if(enemy[j].reserved && !enemy[j].killed){
                  if(rectCollision((SDL_Rect){projectiles[i].x,projectiles[i].y,projectiles[i].width,projectiles[i].height},(SDL_Rect){enemy[j].x,enemy[j].y,enemy[j].width,enemy[j].height})){
                     enemyHurt(j,10);
                     if(projectiles[i].veloX > 0){
                        enemy[j].bumpX = 175;
                     }
                     else{
                        enemy[j].bumpX = -175;
                     }
                     
                     projectiles[i].reserved = false;
                     if(projectiles[i].projectileType == 2 && !projectiles[i].fromEnemy){
                      player[0].projectileThrown--;
                     }
                     break;
                   }
               }
         }
         }
         else{
            // Player collision
            if(rectCollision((SDL_Rect){projectiles[i].x,projectiles[i].y,projectiles[i].width,projectiles[i].height},(SDL_Rect){player[0].x,player[0].y,player[0].width,player[0].height})){
              playerHurt(0,10);
            }

            // Parry mechanism
            if(player[0].attack && rectCollision((SDL_Rect){projectiles[i].x,projectiles[i].y,projectiles[i].width,projectiles[i].height},(SDL_Rect){player[0].attackX,player[0].attackY,player[0].attackSize,player[0].attackSize})){
               printf("gay");
               player[0].attack = false;
               projectiles[i].veloX *= -1;
               projectiles[i].veloY *= -1;
            } 
         }
         

         }
         
         
      }
   }

   // DeathBox Movement
   for(int i = 0;i<sizeof(deathbox)/sizeof(deathbox[0]);i++){
      if(deathbox[i].reserved){
         deathboxMovement(i);
      }
   }
   for(int i = 0;i<sizeof(light)/sizeof(light[0]);i++){
      if(light[i].reserved){
        lightMovement(i);
        
      }
   }
   for(int i = 0;i<sizeof(displacement)/sizeof(displacement[0]);i++){
      if(displacement[i].reserved){
         displacementMovement(i);
      }
   }



   for (int i = 1;i<sizeof(platforms)/sizeof(platforms[0]);i++){
      if(platforms[i].reserved){

     // Texture Animation
      if(platforms[i].textureAnimationTime >= 1){
         platforms[i].textureAnimationTimer += 1000*app.deltaTime;
         if(platforms[i].textureAnimationTimer > platforms[i].textureAnimationTime){
            platforms[i].textureAnimationInt++;
            platforms[i].textureAnimationInt = (int)platforms[i].textureAnimationInt % ((int)textures[platforms[i].textureInt].textureAnimationSize);
            platforms[i].textureAnimationTimer = 0;
         }
      }
      else{
        platforms[i].textureAnimationInt = 0; 
        platforms[i].textureAnimationTimer = 0;
      }
      // Texture offset movement
      platforms[i].textureOffsetX += platforms[i].textureOffsetX_Move*app.deltaTime;
      platforms[i].textureOffsetY += platforms[i].textureOffsetY_Move*app.deltaTime;
      platforms[i].textureOffsetX = fmod(platforms[i].textureOffsetX,100);
      platforms[i].textureOffsetY = fmod(platforms[i].textureOffsetY,100);
      

      // Platform Movement
        platformMovement(i);
      // Player Platform Collision
      if((platforms[i].collidable || platforms[i].type != 0)){
      if(FCheck_Collision(player[1],i) && platforms[i].collidable){
         FCollision_Response(&player[1],i);
      }
      if(FCheck_Collision(player[0],i) && platforms[i].collidable){
         FCollision_Response(&player[0],i);
      }
      else if (FCheck_Collision(player[0],i) && !platforms[i].collidable){
         if(platforms[i].type == 1){
            if(!level.Finished && !level.transitionToLevel && platforms[i].type == 1 && level.checkpointCount >= level.checkpointsSize){
                
                if(level.campaignLevel){
                  FcheckPB();
                }
                if(!platforms[i].NofinishAnimation){
                  level.Finished = true;
                  Mix_PlayChannel(-1,Sound_finish,0);
                }
                else{
                  
                  level.transitionToLevel = true;
                  profile.levelsUnlocked++;
                  FSaveProfile();
                  appendTransition(0,8);
                  
                }
                
                
             }
         }
         else if(platforms[i].type == 2 && !platforms[i].platformUsed){
               platforms[i].platformUsed = true;
               level.checkpoints[level.checkpointCount] = level.timer;
               level.checkpointShowTimer = 3000;
               level.checkpointCount++;
               FaddReplay(true);
               level.tempFileMade = true;
               level.keyInputsSize = 0;
               level.LastCheckpointX = platforms[i].x + platforms[i].width/2;
               level.LastCheckpointY = platforms[i].y + platforms[i].height/2;
               Mix_PlayChannel(-1,Sound_Checkpoint,0);
         }
      }
      // Enemy Collision
      for (int j = 0;j<sizeof(enemy)/sizeof(enemy[0]);j++){
         if(FCheck_Collision_Enemy(enemy[j],i)){
            enemy[j].platformIndex = i;
            FCollision_Response_Enemy(&enemy[j],i);
         }
      }
      }
      // Player Platform Collision
      
    } 
   }
   // Player displacement
   
   
   for(int i = 0;i<sizeof(player)/sizeof(player[0]);i++){
     
      if(i > 0 && !mapData.ghostInGame){
         continue;
      }
      if(player[i].invisTimer > 0){
         player[i].invisTimer -= 1000*app.deltaTime;
      }
      
      /// Player play sounds
     if(player[i].stepSoundCount > 100 && player[i].onPlatform){
      if(player[i].stepSoundInt == 0){
          if(i == 0){
       Mix_PlayChannel(-1,Sound_Step1,0);
          }
      }
      else if(player[i].stepSoundInt == 1){
          if(i == 0){
         Mix_PlayChannel(-1,Sound_Step2,0);
          }
      }
      player[i].stepSoundCount = 0;
      player[i].stepSoundInt = (player[i].stepSoundInt + 1) % 2; 
     }
     if(player[i].wallHangingCount > 90 && player[i].onWall){
      if(i == 0){
        Mix_PlayChannel(-1,Sound_Wall,0); 
      }
      
      player[i].wallHangingCount = 0;
     } 
     
      for(int j = 0;j<sizeof(displacement)/sizeof(displacement[0]);j++){
       if(displacement[j].reserved){
         if(rectCollision((SDL_Rect){player[i].x,player[i].y,player[i].width,player[i].height},(SDL_Rect){displacement[j].x,displacement[j].y,displacement[j].width,displacement[j].height})){
            if(displacement[j].powerType == 0){
               if(displacement[j].type % 2 == 0){
                player[i].displacementVeloX = displacement[j].power*cos(displacement[j].type*PI/2);
               }
               else {
                  player[i].displacementVeloY = displacement[j].power*sin(-displacement[j].type*PI/2);
                  player[i].veloY = 0;
               }
            }
            else if(displacement[j].powerType == 1){
               if(displacement[j].type % 2 == 0){
                  player[i].displacementAccelX = displacement[j].power*cos(displacement[j].type*PI/2);
               }
               else{
                  player[i].displacementAccelY = displacement[j].power*sin(-displacement[j].type*PI/2);
               }  
            }
         }
         
       }
      }
     if(i == 0){
      // Arrow
      if(player[i].enemyTarget != -1){
         player[i].ProjectileAngle = atan((player[i].y-enemy[player[i].enemyTarget].y)/(player[i].x-enemy[player[i].enemyTarget].x))*180/PI;
         if((player[i].x-enemy[player[i].enemyTarget].x) < 0){
            player[i].ProjectileAngle += 180;
         }
         
      if(player[i].arrowPull < 10){
         player[i].enemyTargetDistance = sqrt(pow(player[0].x-enemy[player[i].enemyTarget].x,2)+pow(player[0].y-enemy[player[i].enemyTarget].y,2));
      }
      }
      else{
         player[i].ProjectileAngle = 0;
      }
      
      
      if(!player[i].keys.c){
         if(player[i].arrowPull > 0){
            player[i].arrowPull -= 2000*app.deltaTime;
         }
         else{
           player[i].arrowPull = 0; 
         }

      }
      if(player[i].enemyTarget != -1 && player[i].x-enemy[player[i].enemyTarget].x > 0){
         player[i].ProjectileAngle += 180;
      }

      for(int j = 1 ;j<sizeof(triggers)/sizeof(triggers[0]);j++){
         if(triggers[j].reserved){
            if(!triggers[j].triggerUsed){
               if(rectCollision((SDL_Rect){player[i].x,player[i].y,player[i].width,player[i].height},(SDL_Rect){triggers[j].x,triggers[j].y,triggers[j].width,triggers[j].height})){
               triggers[j].triggerUsed = true;      
              }
             }
          else{
            if(triggers[j].useDelayTimer >= triggers[j].useDelay && !triggers[j].timerStart){
               triggers[j].useDelayTimer = 0;
               triggers[j].timerStart = true;
               if(triggers[j].triggerType == 0){
                  if((int)triggers[j].Value1 >= 0){
                  platforms[(int)triggers[j].Value3].moveNodeInt = (int)triggers[j].Value1;
                  platforms[(int)triggers[j].Value3].x = movenodes[(int)triggers[j].Value1].positions[0][0] - (platforms[(int)triggers[j].Value3].width-25)/2;
                  platforms[(int)triggers[j].Value3].y = movenodes[(int)triggers[j].Value1].positions[0][1] - (platforms[(int)triggers[j].Value3].height-25)/2;   
                  }
                  platforms[(int)triggers[j].Value3].moveSpeed = triggers[j].Value2;
               } 
               else if(triggers[j].triggerType == 1){
                  if((int)triggers[j].Value1 >= 0){
                  deathbox[(int)triggers[j].Value3].moveNodeInt = (int)triggers[j].Value1;
                  deathbox[(int)triggers[j].Value3].x = movenodes[(int)triggers[j].Value1].positions[0][0] - (deathbox[(int)triggers[j].Value3].width-25)/2;
                  deathbox[(int)triggers[j].Value3].y = movenodes[(int)triggers[j].Value1].positions[0][1] - (deathbox[(int)triggers[j].Value3].height-25)/2;   
                  }
                  deathbox[(int)triggers[j].Value3].moveSpeed = triggers[j].Value2;
               } 
               else if(triggers[j].triggerType == 2){
                  if((int)triggers[j].Value1 >= 0){
                  light[(int)triggers[j].Value3].moveNodeInt = (int)triggers[j].Value1;
                  light[(int)triggers[j].Value3].x = movenodes[(int)triggers[j].Value1].positions[0][0] - (light[(int)triggers[j].Value3].width-25)/2;
                  light[(int)triggers[j].Value3].y = movenodes[(int)triggers[j].Value1].positions[0][1] - (light[(int)triggers[j].Value3].height-25)/2;   
                  }
                  light[(int)triggers[j].Value3].moveSpeed = triggers[j].Value2;
               }
               else if(triggers[j].triggerType == 3){
                  if((int)triggers[j].Value1 >= 0){
                  displacement[(int)triggers[j].Value3].moveNodeInt = (int)triggers[j].Value1;
                  displacement[(int)triggers[j].Value3].x = movenodes[(int)triggers[j].Value1].positions[0][0] - (displacement[(int)triggers[j].Value3].width-25)/2;
                  displacement[(int)triggers[j].Value3].y = movenodes[(int)triggers[j].Value1].positions[0][1] - (displacement[(int)triggers[j].Value3].height-25)/2;   
                  }
                  displacement[(int)triggers[j].Value3].moveSpeed = triggers[j].Value2;
               }   
            }
            else{
               triggers[j].useDelayTimer += 1000*app.deltaTime;
               
            } 
         }

         if(triggers[j].timerStart && triggers[j].reuseDelay >= 1){
            triggers[j].reuseDelayTimer += 1000*app.deltaTime;
            if(triggers[j].reuseDelayTimer >= triggers[j].reuseDelay){
               triggers[j].triggerUsed = false;
               triggers[j].timerStart = false;
               triggers[j].reuseDelayTimer = 0;
            }
         }
     }
      }
      
         
         
      }

      // Player check death
      if(i == 0 && !player[i].dead){
         for(int j = 0;j<sizeof(deathbox)/sizeof(deathbox[0]);j++){
            if(deathbox[j].reserved){
               if(rectCollision((SDL_Rect){player[i].x,player[i].y,player[i].width,player[i].height},(SDL_Rect){deathbox[j].x,deathbox[j].y,deathbox[j].width,deathbox[j].height})){
                  playerHurt(0,10);
               }
            }
         }
         if(player[0].health <= 0){
           player[0].dead = true;
           Mix_PlayChannel(-1,Sound_Death,0);
         }
      }
      
   }
   player[0].canTake = -1;
   for(int i = 0;i<sizeof(specials)/sizeof(specials[0]);i++){
      if(specials[i].reserved){
         if(rectCollision((SDL_Rect){player[0].x,player[0].y,player[0].width,player[0].height},(SDL_Rect){specials[i].x,specials[i].y,specials[i].size,specials[i].size})){
            player[0].canTake = i;
            break;
         }
      }
   }
   if(player[0].canTake >= 0){
      player[0].EButtonOpacity += 750*app.deltaTime;
      if(player[0].EButtonOpacity > 230){
         player[0].EButtonOpacity = 230;
      }
   }
   else{
      player[0].EButtonOpacity -= 750*app.deltaTime;
      if(player[0].EButtonOpacity < 0){
         player[0].EButtonOpacity = 0;
      }
   }

   // Scripts
   for(int i = 0;i<sizeof(scripts)/sizeof(scripts[0]);i++){
      if(scripts[i].reserved){
         if(rectCollision((SDL_Rect){player[0].x,player[0].y,player[0].width,player[0].height},(SDL_Rect){scripts[i].x,scripts[i].y,scripts[i].width,scripts[i].height})){
         if(!scripts[i].used){
            scripts[i].used = true;   
            scripts[i].startTimer = true;
         }
         }
         if(scripts[i].execute){
            ExecuteScript(scripts[i].scriptInt);
            scripts[i].execute = false;
            scripts[i].useDelayTimer = 0;
            
         }
         // Increment use delay
         if(scripts[i].startTimer){
          if(scripts[i].useDelay >= 1 && scripts[i].useDelayTimer <= scripts[i].useDelay){
            scripts[i].useDelayTimer += 1000*app.deltaTime;
     
          }
          else{
            scripts[i].execute = true;
            scripts[i].startTimer = false;
          }  
         }
         
            
         
         
         // Increment reuse delay
         if(scripts[i].used && scripts[i].reuseDelay >= 1){
           scripts[i].reuseDelayTimer += 1000*app.deltaTime;
           
           if(scripts[i].reuseDelayTimer > scripts[i].reuseDelay){
            scripts[i].used = false;
            scripts[i].reuseDelayTimer = 0;
           }
         }
      }

   }
   // Player Trails
   for(int i = 0;i<5;i++){
         if(player[0].playerTrails[i][2] > 0){
            player[0].playerTrails[i][2] -= 700*app.deltaTime;
            if (player[0].playerTrails[i][2] < 0){
               player[0].playerTrails[i][2] = 0;
            }
         }  
      }
   if (player[0].drawTrails){
      player[0].trailTime += 1000*app.deltaTime;
   if (player[0].trailTime >= 50 && !player[0].dead){
      player[0].playerTrails[player[0].trailIndex][0] = player[0].x;
      player[0].playerTrails[player[0].trailIndex][1] = player[0].y;
      player[0].playerTrails[player[0].trailIndex][2] = 255;
      player[0].playerTrails[player[0].trailIndex][3] = (int)(player[0].animationIndex) % 6;
      player[0].playerTrails[player[0].trailIndex][4] = (int)(1-player[0].direction)/2;
      player[0].trailIndex++;
      player[0].trailIndex %= 5;
      player[0].trailTime = 0;
   }
   }
   // PARTICLES 
   for (int i = 0;i<sizeof(particles)/sizeof(particles[0]);i++){
      if(particles[i].reserved){
         particles[i].size -= 20*app.deltaTime;
         particles[i].x += particles[i].veloX*app.deltaTime;
         particles[i].y += particles[i].veloY*app.deltaTime;
         
         if(particles[i].size < 0){
            particles[i].size = 0;
            particles[i].reserved = false;
         }
      }
   }
   if(!level.Finished && level.Started){
      level.timer += 1000*app.deltaTime;
   }
   else if(!level.Started){level.timer = 0;}
   // DeathBox Movement
   for(int i = 0;i<sizeof(deathbox)/sizeof(deathbox[0]);i++){
      if(deathbox[i].reserved){
         
      }
   }
   }

   if(player[0].dead){
      player[0].deathAnimationTimer += 10000*app.deltaTime;
      if(player[0].deathAnimationTimer > 10000){
         player[0].dead = false;
         player[0].deathAnimationTimer = 0;
         if(level.checkpointCount <= 0){
           FGameRestart(); 
         }
         else{
            player[0].x = level.LastCheckpointX;
            player[0].y = level.LastCheckpointY;
            player[0].health = 30;
            player[0].invisTimer = 2000;
         }
      }
   }
}
void addProjectile(bool fromEnemy,int enemyIndex,double x, double y, double veloX,double veloY,int type){
   for(int i = 0;i<sizeof(projectiles)/sizeof(projectiles[0]);i++){
      if(!projectiles[i].reserved){
         projectiles[i].fromEnemy = fromEnemy;
         if(fromEnemy){
            projectiles[i].enemyIndex = enemyIndex;
         }
         projectiles[i].reserved = true;
         projectiles[i].x = x;
         projectiles[i].y = y;
         projectiles[i].width = (int)(15);
         projectiles[i].height =  (int)(15);
         projectiles[i].accY = GRAVITY;
         projectiles[i].veloX = veloX;
         projectiles[i].veloY = veloY;
         projectiles[i].projectileType = type;

         break;
      }
   }
}





void FGameRestart(){
   
   if(level.newRecord){
      level.newRecord = false;
   }
   if(mapData.PBTimer>0){
        mapData.ghostInGame = true; 
   }

   
      for(int i = 0;i<sizeof(scripts)/sizeof(scripts[0]);i++){
         if(scripts[i].reserved){
            scripts[i].used = false;
            scripts[i].execute = false;
            scripts[i].useDelayTimer = 0;
            scripts[i].reuseDelayTimer = 0;
         }
      }
      for(int i = 1;i<sizeof(platforms)/sizeof(platforms[0]);i++){
        if(platforms[i].reserved){
         platforms[i].x = platforms[i].spawnX;
         platforms[i].y = platforms[i].spawnY;
         platforms[i].platformUsed = false;  
         platforms[i].moveNodeCount = 0;
         platforms[i].moveDistance = 0;
         platforms[i].moveNodeReverse = false;
         platforms[i].moveSpeed = platforms[i].moveSpeedSpawn;
         platforms[i].moveNodeInt = platforms[i].moveNodeIntSpawn;
         platforms[i].steepness = -atan((platforms[i].height*sin(platforms[i].slope))/(platforms[i].width));
         
        
        }        
      }
      for(int i = 0;i<sizeof(deathbox)/sizeof(deathbox[0]);i++){
        if(deathbox[i].reserved){
         deathbox[i].x = deathbox[i].spawnX;
         deathbox[i].y = deathbox[i].spawnY;
         deathbox[i].moveNodeCount = 0;
         deathbox[i].moveDistance = 0;
         deathbox[i].moveNodeReverse = false;
         deathbox[i].moveSpeed = deathbox[i].moveSpeedSpawn;
         deathbox[i].moveNodeInt = deathbox[i].moveNodeIntSpawn;
        }        
      }
      
      for(int i = 0;i<sizeof(light)/sizeof(light[0]);i++){
        if(light[i].reserved){
        light[i].x = light[i].spawnX;
        light[i].y = light[i].spawnY;
        light[i].moveNodeCount = 0;
        light[i].moveDistance = 0;
        light[i].moveNodeReverse = false;
        light[i].moveSpeed = light[i].moveSpeedSpawn;
         light[i].moveNodeInt = light[i].moveNodeIntSpawn;
       }
      }
      for(int i = 0;i<sizeof(triggers)/sizeof(triggers[0]);i++){
        if(triggers[i].reserved){
          triggers[i].triggerUsed = false;
          triggers[i].timerStart = false;
          triggers[i].useDelayTimer = 0;
          triggers[i].reuseDelayTimer = 0;
        }
       }
      for(int i = 0;i<sizeof(displacement)/sizeof(displacement[0]);i++){
        if(displacement[i].reserved){
         displacement[i].x = displacement[i].spawnX;
         displacement[i].y = displacement[i].spawnY;
         displacement[i].moveNodeCount = 0;
         displacement[i].moveDistance = 0;
         displacement[i].moveNodeReverse = false;
         displacement[i].moveSpeed = displacement[i].moveSpeedSpawn;
         displacement[i].moveNodeInt = displacement[i].moveNodeIntSpawn;
       }
       }
       for(int i = 0;i<sizeof(enemy)/sizeof(enemy[0]);i++){
        if(enemy[i].reserved){
         enemy[i].x = enemy[i].spawnX;
         enemy[i].y = enemy[i].spawnY;
         enemy[i].veloX = 0;
         enemy[i].veloY = 0;
         enemy[i].killed = false;
         enemy[i].health = enemy[i].maxHealth;
         enemy[i].unbump = false;
         enemy[i].bumpX = 0;
         enemy[i].textureAnimationInt = 0;
         enemy[i].attackCoolDown = 100;
         enemy[i].direction = 1;
         enemy[i].attackDelayTimer = 0;
         enemy[i].attackPrepare = false;
       }
       }
       for(int i = 0;i<sizeof(specials)/sizeof(specials[0]);i++){
        if(specials[i].reserved){
         specials[i].taken = false;
       }
       }
       for(int i = 0;i<sizeof(projectiles)/sizeof(projectiles[0]);i++){
        if(projectiles[i].reserved){
         projectiles[i].reserved = false;
         projectiles[i].despawnTime = 0;
       }
       }
      level.Paused = false;
      level.endShowCoins = 0;
      level.transitionToLevel = false;
      level.endTransition = 0;
      camera.scaleReal = level.cameraScaleStart;
      remove("levels/temp.txt");
      if(app.status == 0){
         level.resetTransition = 255;
      }
      mapData.ghostEnd = false;
      mapData.ghostNextInput = -10;
      mapData.fileadditionIndex = 0;
      mapData.ghostCurrentIndex = 0;
      level.Finished = false;
      level.Started = false;
      player[0].x = player[0].spawnX;
      player[0].y = player[0].spawnY;
      player[0].health = 30;
      player[0].invisTimer = -1;
      player[0].attackSize = player[0].width*1.5;
      player[0].walkingSpeed = 150;
      player[1].walkingSpeed = 150;
      player[0].sprintSpeed = (player[0].width+player[0].height)*500/40;
      player[1].sprintSpeed = (player[1].width+player[1].height)*500/40;
     
      camera.x = -player[0].x-player[0].width/2+gameWidth/2;
      camera.y = -player[0].y-player[0].height/2+gameHeight/2;
      camera.scale = 5;
      camera.freeCam = false;
      player[0].keys.left = false;
      player[0].keys.right = false;
      player[0].groundPound = false;
      player[1].groundPound = false;
      player[0].drawTrails = false;
      player[0].dead = false;
      player[0].deathAnimationTimer = 0;
      player[0].special = -1;
      player[0].doubleJump = 0;
      player[1].doubleJump = 0;
      player[1].x = player[0].spawnX;
      player[1].y = player[0].spawnY;
      player[0].projectileThrown = 0;
      player[1].groundPoundX = 0;
      player[0].groundPoundX = 0;
      player[0].veloX = 0;
      player[0].veloY = 0;
      player[0].displacementVeloX = 0;
      player[0].displacementVeloY = 0;
      player[0].displacementAccelX = 0;
      player[0].displacementAccelY = 0;
      player[1].displacementVeloX = 0;
      player[1].displacementVeloY = 0;
      player[1].displacementAccelX = 0;
      player[1].displacementAccelY = 0;
      player[0].accX = 0;
      player[0].accY = 0;
      player[0].jumpVelo = 0;
      player[1].veloY = 0;
      player[1].veloX = 0;
      player[1].accY = 0;
      player[1].accX = 0;
      player[1].jumpVelo = 0;
      level.tempFileMade = false;
      level.keyInputsSize = 0;
      level.checkpointCount = 0; 
      level.checkpointShowTimer = 0;

      player[1].keys.up = false;
      player[1].keys.left = false;
      player[1].keys.right = false;
      player[1].keys.down = false;
      player[1].keys.shift = false;
}