void FPlayer_Movement(){
    if(!level.Started){
      if(player[0].keys.left || player[0].keys.right){
         level.Started = true;
      }
    }
    if(player[0].y > mapData.yMax){
        FGameRestart();
      }
   for(int i = 0;i<sizeof(player)/sizeof(player[0]);i++){
      if(i > 0 && !mapData.ghostInGame){
         continue;
      }
   if(player[i].playerControl < 1){
      player[i].playerControl += 2*app.deltaTime;
      if(player[i].playerControl >= 1){
         player[i].playerControl = 1;
      }
   }
   player[i].idleIndex += 2*app.deltaTime;

   if(SDL_abs(player[i].veloX) > 10 && player[i].onPlatform && player[i].particleTimer > 50 + rand()%100){
       addParticle(player[i].x+player[i].width/2-5,player[i].y+player[i].height-5,10,200,200,200,rand()%360);
       player[i].particleTimer = 0;
   }
   else if (SDL_abs(player[i].veloY)> 10 && player[i].onWall && player[i].particleTimer > 50 + rand()%100){
       addParticle(player[i].x+(player[i].width)*(player[i].onWall<0)-5,player[i].y,10,200,200,200,rand()%360);
       player[i].particleTimer = 0;
   }

   if (player[i].idleIndex >= 20){
      player[i].idleIndex = 0;
   }
   if(!player[i].keys.up){
      player[i].jumpBool = true;
   }
   if (player[i].keys.up && player[i].jumpBool && player[i].onPlatform){
      player[i].jumpBool = false;
      player[i].jumpVelo = -150;
   }
   if (player[i].keys.left){
      player[i].accX = (-(player[i].width+player[i].height)*500/40-300*(player[i].keys.shift))*player[i].playerControl;
      player[i].animationIndex += 10*app.deltaTime;
      player[i].direction = -1;
      
   }
   else if (player[i].keys.right){
      player[i].accX = ((player[i].width+player[i].height)*500/40+300*(player[i].keys.shift))*player[i].playerControl;
      player[i].animationIndex += 10*app.deltaTime;
      player[i].direction = 1;
   }
   else {player[i].accX = 0;}
   player[i].particleTimer += 1000*app.deltaTime;

   /////
   
   if(level.Started){
      player[i].veloX += (player[i].accX+player[i].displacementAccelX)*app.deltaTime;
      player[i].veloY += (player[i].accY + (GRAVITY)*(SDL_abs(player[i].displacementAccelY) < 10 || SDL_abs(player[i].displacementVeloY) < 10) + player[i].displacementAccelY)*app.deltaTime;
   }
   /////
   player[i].veloX *= pow(0.05,app.deltaTime);
   player[i].wallveloX *= pow(0.05,app.deltaTime);

   if (fabs(player[i].veloX) >= 150+(player[i].width+player[i].height)*500/40*(player[i].keys.shift)){
      player[i].veloX = (150+(player[i].width+player[i].height)*500/40*(player[i].keys.shift))*(1-2*(player[i].veloX < 0));
   }
   ////
   if(level.Started && !player[i].dead){
     player[i].x += (player[i].veloX + player[i].wallveloX + player[i].displacementVeloX)*app.deltaTime;
     player[i].y += ((player[i].veloY) + player[i].jumpVelo  + player[i].displacementVeloY)*app.deltaTime; 
   }
   ///// 
   player[i].displacementVeloX  *= pow(0.05,app.deltaTime);
   player[i].displacementVeloY  *= pow(0.05,app.deltaTime);
   player[i].displacementAccelX *= pow(0.05,app.deltaTime);
   player[i].displacementAccelY *= pow(0.05,app.deltaTime);
   if(!player[i].onPlatform){
      player[i].accY = 0;
   }
   if (player[i].onWall){
     if(player[i].veloY+player[i].jumpVelo > 100){
        player[i].veloY = 100-player[i].jumpVelo;
        
     }
     if (player[i].keys.up && player[i].jumpBool){
      player[i].jumpBool = false;
      player[i].veloY = 0;
      player[i].jumpVelo = -150;
      player[i].wallveloX = 100*player[i].onWall; 
      player[i].playerControl = 0;
     } 
   }
   
   }


   if(mapData.PBTimer>0){
    if(level.Started){
      FapplyMovementGhost();
    }
    
   if(mapData.ghostEnd){
         player[1].keys.up = false;
         player[1].keys.left = false;
         player[1].keys.right = false;
         player[1].keys.down = false;
         player[1].keys.shift = false;
   }
   }
}

void FapplyMovementGhost(){
   if(mapData.ghostInGame){
      if(mapData.PBTimer <= level.timer && mapData.PBTimer > 0){
         mapData.ghostEnd = true;
         return;
      }
      char type[20];
      sprintf(type,"i%d",mapData.ghostCurrentIndex);
      char* msPress = FGetDataMap(level.absolutePath,type,0,level.absolutePathSize);
      mapData.ghostNextInput = atoi(msPress);
      
      if(level.timer < mapData.ghostNextInput-1){return;}
      if(msPress){
         mapData.ghostCurrentIndex++;
      }
      else{return;}
      mapData.tickDifference = ((int)level.timer - mapData.ghostNextInput);
      char* up = FGetDataMap(level.absolutePath,type,1,level.absolutePathSize);
      char* left = FGetDataMap(level.absolutePath,type,2,level.absolutePathSize);
      char* right = FGetDataMap(level.absolutePath,type,3,level.absolutePathSize);
      char* down = FGetDataMap(level.absolutePath,type,4,level.absolutePathSize);
      char* shift = FGetDataMap(level.absolutePath,type,5,level.absolutePathSize);
      char* pX =  FGetDataMap(level.absolutePath,type,6,level.absolutePathSize);
      char* pY =  FGetDataMap(level.absolutePath,type,7,level.absolutePathSize);
      char* pvX =  FGetDataMap(level.absolutePath,type,8,level.absolutePathSize);
      char* pvY =  FGetDataMap(level.absolutePath,type,9,level.absolutePathSize);
      
      player[1].keys.up = (bool)atoi(up);
      player[1].keys.left = (bool)atoi(left);
      player[1].keys.right = (bool)atoi(right);
      player[1].keys.down = (bool)atoi(down);
      player[1].keys.shift = (bool)atoi(shift);
      player[1].x = (float)atoi(pX);
      player[1].y = (float)atoi(pY);
      player[1].veloX = (float)atof(pvX);
      player[1].veloY = (float)atof(pvY);  

      free(up);
      free(left);
      free(right);
      free(down);
      free(shift);
      free(msPress);
   }
}