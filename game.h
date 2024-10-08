void FDisplayHUD(){
   SDL_SetRenderTarget(renderer,HUDLayer);
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
   if(app.showFPS){
      char FPS[30];
      sprintf(FPS,"%d FPS\0",(int)(1/app.deltaTime));
      renderText(len(FPS),FPS,5,40,8*len(FPS),10,255,200,(int[3]){255,255,255});
   }
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
   
   SDL_SetRenderDrawColor(renderer,0,0,0,max(level.resetTransition,0));
   SDL_RenderFillRect(renderer,&(SDL_Rect){0,0,gameWidth,gameHeight});
   renderButtons();
   FGUIHover();
   SDL_SetRenderTarget(renderer,backgroundLayer);
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
         else if (i == 4){
            app.campaignLevel++;
            findLevelCampaign();
            sprintf(level.absolutePath,"levels/%s.txt\0",app.campaignLevelName);
            appendTransition(app.status,0);
         }
         else if (i == 5){
            appendTransition(app.status,8);
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

       
   camera.x  > gameWidth/(2*camera.scale) + gameWidth/2 - mapData.xMax;
   if(camera.freeCam){
     camera.x += (-player[0].x-player[0].width/2+gameWidth/2 - camera.x)*10*app.deltaTime;
     camera.y += (-player[0].y-player[0].height/2+gameHeight/2 - camera.y)*10*app.deltaTime;
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
   
   
   app.backgroundMoving += 5*app.deltaTime;
   if(app.backgroundMoving >= backgrounds[app.backgroundInt].textureWidth){
      app.backgroundMoving = 0;
   }
   SDL_RenderClear(renderer);
   DrawBackground();
   

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
         // Add texture to platform
         FtexturePlatform(i);
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
         SDL_RenderCopyEx(renderer,tex_blank,NULL,&(SDL_Rect){particles[i].xDraw,particles[i].yDraw,particles[i].sizeDraw,particles[i].sizeDraw},particles[i].rotation,NULL,SDL_FLIP_NONE);
         //SDL_RenderFillRect(renderer,&(SDL_Rect){particles[i].xDraw,particles[i].yDraw,particles[i].sizeDraw,particles[i].sizeDraw});
      }
   }
   // Draw Nodes
   
   for(int i = 1;i<sizeof(platforms)/sizeof(platforms[0]);i++){
      if(platforms[i].reserved && platforms[i].collidable){

         // Camera offsetted data !
         platforms[i].xDraw = platforms[i].x;
         platforms[i].yDraw = platforms[i].y;
         platforms[i].widthDraw = platforms[i].width*camera.scale;
         platforms[i].heightDraw = platforms[i].height*camera.scale;
         platforms[i].xDraw  += camera.x;
         platforms[i].yDraw  += camera.y;
         platforms[i].xDraw  = gameWidth/2 + (platforms[i].xDraw - gameWidth/2) * camera.scale;
         platforms[i].yDraw  = gameHeight/2 + (platforms[i].yDraw - gameHeight/2) * camera.scale;
         // Add texture to platform
         FtexturePlatform(i);
      }
   }
    // Display timer
   // Draw player
   // i == 0 => player
   // i > 0 => Ghost
   for(int i = sizeof(player)/sizeof(player[0]) - 1;i>=0;i--){
      if((i > 0 && mapData.ghostInGame) || i == 0){  
       player[i].xDraw = player[i].x;
       player[i].yDraw = player[i].y;
       player[i].widthDraw = player[i].width;
       player[i].heightDraw = player[i].height;
       player[i].widthDraw  *= camera.scale;
       player[i].heightDraw *= camera.scale;
       player[i].xDraw += camera.x;
       player[i].yDraw += camera.y;
       player[i].xDraw = gameWidth/2 + (player[i].xDraw - gameWidth/2) * camera.scale;
       player[i].yDraw = gameHeight/2 + (player[i].yDraw - gameHeight/2) * camera.scale;
      if(i > 0){
         SDL_SetTextureAlphaMod(tex_player,100);
      }
       SDL_RendererFlip flip1 = SDL_FLIP_NONE;
   if(player[i].direction < 0){
      flip1 = SDL_FLIP_HORIZONTAL;
   }
   if(player[i].dead){
      if((int)(player[0].deathAnimationTimer/1000)>=1 && (int)(player[0].deathAnimationTimer/1000) <= 6){
      SDL_RenderCopyEx(renderer,tex_player,&(SDL_Rect){95+(int)(player[0].deathAnimationTimer/1000)*24,24,22,22},&(SDL_Rect){player[i].xDraw,player[i].yDraw,player[i].widthDraw,player[i].heightDraw},0,NULL,SDL_FLIP_NONE);
      }
      else if((int)(player[0].deathAnimationTimer/1000) <= 6){
         SDL_RenderCopyEx(renderer,tex_player,&(SDL_Rect){98,26,16,16},&(SDL_Rect){player[i].xDraw,player[i].yDraw,player[i].widthDraw,player[i].heightDraw},0,NULL,SDL_FLIP_NONE);
      }
      
   }
   else if(player[i].onWall){
      if(player[i].onWall > 0){
      flip1 = SDL_FLIP_HORIZONTAL;
      }
      else {flip1 = SDL_FLIP_NONE;}
      player[i].width = player[i].Owidth;
   SDL_RenderCopyEx(renderer,tex_player,&(SDL_Rect){73,27,16,16},&(SDL_Rect){player[i].xDraw,player[i].yDraw,player[i].widthDraw,player[i].heightDraw},0,NULL,flip1);}
 
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
   SDL_SetTextureAlphaMod(tex_player,255);
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
   for(int i = 1;i<sizeof(light)/sizeof(light[0]);i++){
      light[i].xDraw = light[i].x;
      light[i].yDraw = light[i].y;
      light[i].sizeDraw = light[i].size*camera.scale;
      light[i].xDraw  += camera.x;
      light[i].yDraw  += camera.y;
      light[i].xDraw  = gameWidth/2 + (light[i].xDraw - gameWidth/2) * camera.scale;
      light[i].yDraw  = gameHeight/2 + (light[i].yDraw - gameHeight/2) * camera.scale;
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
   FDisplayHUD();

   
   /////-------------------------------END OF RENDERING
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
   // Player Collision
   player[0].onPlatform = 0;
   player[0].onWall = 0;
   player[1].onPlatform = 0;
   player[1].onWall = 0;
   


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
            if(!level.Finished && platforms[i].type == 1 && level.checkpointCount >= level.checkpointsSize){
                level.Finished = true;
                if(level.campaignLevel){
                  FcheckPB();
                }
                Mix_PlayChannel(-1,Sound_finish,0);
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
      }
      // Player Platform Collision
      
    } 
   }
   // Player displacement

   for(int i = 0;i<sizeof(player)/sizeof(player[0]);i++){
     
     if(i > 0 && !mapData.ghostInGame){
         continue;
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
                  light[(int)triggers[j].Value3].x = movenodes[(int)triggers[j].Value1].positions[0][0] - (light[(int)triggers[j].Value3].size-25)/2;
                  light[(int)triggers[j].Value3].y = movenodes[(int)triggers[j].Value1].positions[0][1] - (light[(int)triggers[j].Value3].size-25)/2;   
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
                  player[0].dead = true;
                  Mix_PlayChannel(-1,Sound_Death,0);
               }
            }
         }
      }
      
   }
   // PARTICLES 
   for (int i = 0;i<sizeof(particles)/sizeof(particles[0]);i++){
      if(particles[i].reserved){
         particles[i].size -= 20*app.deltaTime;
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
         }
         
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
      level.Paused = false;
      level.endShowCoins = 0;
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
      player[0].keys.left = false;
      player[0].keys.right = false;
      player[0].dead = false;
      player[0].deathAnimationTimer = 0;
      player[1].x = player[0].spawnX;
      player[1].y = player[0].spawnY;
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