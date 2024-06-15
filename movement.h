void FPlayer_Movement(){
    if(!level.Started){
      if(player[0].keys.left || player[0].keys.right){
         level.Started = true;
      }
    }
   for(int i = 0;i<sizeof(player)/sizeof(player[0]);i++){
      if(i > 0 && !mapData.ghostInGame){
         continue;
      }
      if(player[i].y > mapData.yMax){
        FGameRestart();
      }
   if(player[i].playerControl < 1){
      player[i].playerControl += 1*app.deltaTime;
      if(player[i].playerControl >= 1){
         player[i].playerControl = 1;
      }
   }
   player[i].idleIndex += 2*app.deltaTime;
   if (player[i].idleIndex >= 20){
      player[i].idleIndex = 0;
   }
   if (player[i].keys.up && player[i].onPlatform){
      player[i].jumpVelo = -150;
   }
   if (player[i].keys.left){
      player[i].accX = (-500-300*(player[i].keys.shift))*player[i].playerControl;
      player[i].animationIndex += 10*app.deltaTime;
      player[i].direction = -1;
   }
   else if (player[i].keys.right){
      player[i].accX = (500+300*(player[i].keys.shift))*player[i].playerControl;
      player[i].animationIndex += 10*app.deltaTime;
      player[i].direction = 1;
   }
   else {player[i].accX = 0;}
   player[i].veloX += player[i].accX*app.deltaTime;
   
   if(level.Started){
      player[i].veloY += (player[i].accY + GRAVITY)*app.deltaTime;
   }
   player[i].veloX *= pow(0.05,app.deltaTime);
   if (fabs(player[i].veloX) >= 150+500*(player[i].keys.shift)){
      player[i].veloX = (150+500*(player[i].keys.shift))*(1-2*(player[i].veloX < 0));
   }

   player[i].x += player[i].veloX*app.deltaTime;
   if(level.Started){
     player[i].y += (player[i].veloY + player[i].jumpVelo)*app.deltaTime; 
   }
   if(!player[i].onPlatform){
      player[i].accY = 0;
   }
   if (player[i].onWall && player[i].keys.up){
      player[i].veloY = 0;
      player[i].jumpVelo = -150;
      player[i].veloX = 100*player[i].onWall; 
      player[i].playerControl = 0;
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
      // if(app.deltaTimeGhost > ((int)level.timer - mapData.ghostNextInput)/1000){
      //    app.deltaTimeGhost += mapData.tickDifference/1000;
      // }
      // else{app.deltaTimeGhost = app.deltaTime;}
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