void FDisplayHUD(){
   char* timer = msToTimer((int)level.timer);
   renderText(8,timer,5,5,8*12,20,255,(int[3]){255,255,255});
   free(timer);
   if(mapData.PBTimer>0){
     char* PBtimer = msToTimer(mapData.PBTimer);
     renderText(sizeof("PB"),"PB",5,30,sizeof("PB")*7,10,255,(int[3]){200,0,0});
     renderText(8,PBtimer,30,30,8*7,10,255,(int[3]){200,200,200});
     free(PBtimer);
   }
   char fps[5];
   SDL_itoa((int)1/app.deltaTime,fps,10);
   renderText(len(fps),fps,200,500,30,30,255,(int[3]){200,200,200});
   renderText(mapData.mapNameLen,mapData.mapName,windowWidth-mapData.mapNameLen*12,5,mapData.mapNameLen*12,18,255,(int[3]){255,255,255});
    if(level.newRecord){
      renderText(sizeof("New Record"),"New Record",10+8*12,8,sizeof("New Record")*12,15,255,(int[3]){0,200,0});
   }

   if(level.checkpointShowTimer>0){
      char* checkpointTimer = msToTimer((int)(level.checkpoints[level.checkpointCount-1]));
      renderText(8,checkpointTimer,windowWidth/2-4*10,20,8*10,15,255,(int[3]){255,255,255});
      if(mapData.ghostInGame){
      char* timeDiff = msToTimer((int)(SDL_abs(level.checkpoints[level.checkpointCount-1]-level.LastCheckpointTimer)));
      if(level.checkpoints[level.checkpointCount-1]<level.LastCheckpointTimer){
       renderText(1,"-",windowWidth/2-4*8-8,40,8,15,255,(int[3]){0,0,255});    
       renderText(8,timeDiff,windowWidth/2-4*8,40,8*8,15,255,(int[3]){0,0,255});    
      }
      else {
       renderText(1,"+",windowWidth/2-4*8-8,40,8,12,255,(int[3]){255,0,0});    
       renderText(8,timeDiff,windowWidth/2-4*8,40,8*8,12,255,(int[3]){255,0,0});    
      }
       
   }
   }
}


void FDraw_Game(){

   ///// The data used in the function is transformed to fit the camera's requirements 
   ///// They are camera-manipulated data for only rendering purposes
  // Here lies transformed data
 /////-------------------------------START OF RENDERING
 
   camera.randValue += 1*app.deltaTime;
   //    camera.scale = (2+sin(camera.randValue));
      
   if(!camera.freeCam){
     camera.x = -windowWidth/2+player[0].x+player[0].width/2;
     camera.y = -windowHeight/2+player[0].y+player[0].height/2; 
   }
   else{
     camera.x += (player[0].x+player[0].width/2-windowWidth/2 - camera.x)*10*app.deltaTime;
     camera.y += (player[0].y+player[0].height/2-windowHeight/2 - camera.y)*10*app.deltaTime;
   } 
   if (camera.x > mapData.xMax - windowWidth + player[0].width/2){
       camera.x = mapData.xMax - windowWidth + player[0].width/2;
   }
   if (camera.x < mapData.xMin + player[0].width/2){
       camera.x = mapData.xMin + player[0].width/2;    
   }

   if (camera.y > mapData.yMax - windowHeight + player[0].height/2){
       camera.y = mapData.yMax - windowHeight + player[0].height/2;
   }
   if (camera.y < mapData.yMin + player[0].height/2){
       camera.y = mapData.yMin + player[0].height/2;    
   }
   app.backgroundMoving += 5*app.deltaTime;
   if(app.backgroundMoving >= 576){
      app.backgroundMoving = 0;
   }
   SDL_RenderClear(renderer);
   SDL_RenderCopy(renderer,tex_background,&(SDL_Rect){app.backgroundMoving,0,576,324},&(SDL_Rect){0,0,windowWidth-app.backgroundMoving*windowWidth/576,windowHeight});
   SDL_RenderCopy(renderer,tex_background,&(SDL_Rect){0,0,app.backgroundMoving,324},&(SDL_Rect){windowWidth-app.backgroundMoving*windowWidth/576,0,app.backgroundMoving*windowWidth/576,windowHeight});
   SDL_SetRenderDrawColor(renderer,50,50,50,255);
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

      player[i].xDraw -= camera.x;
      player[i].yDraw -= camera.y;

      player[i].widthDraw *= camera.scale;
      player[i].heightDraw *= camera.scale;

      player[i].xDraw      -= windowWidth/2;
      player[i].yDraw      -= windowHeight/2;
      player[i].xDraw      *= camera.scale;
      player[i].yDraw      *= camera.scale;
      player[i].xDraw      += windowWidth/2;
      player[i].yDraw      += windowHeight/2;
      if(i > 0){
         SDL_SetTextureAlphaMod(tex_player,100);
      }
       SDL_RendererFlip flip1 = SDL_FLIP_NONE;
   if(player[i].direction < 0){
      flip1 = SDL_FLIP_HORIZONTAL;
   }
   if((int)player[i].accX != 0 && (int)player[i].jumpVelo == 0){
   if(SDL_abs(player[i].veloX)>=200){
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

   // Draw platforms
   SDL_SetRenderDrawColor(renderer,120,120,120,255);
   for (int i = 0;i<sizeof(platforms)/sizeof(platforms[0]);i++){
      if(platforms[i].reserved){

         // Camera offsetted data !
         platforms[i].x -= camera.x;
         platforms[i].y -= camera.y;
         platforms[i].width  *= camera.scale;
         platforms[i].height *= camera.scale;
      
         platforms[i].x      -= windowWidth/2;
         platforms[i].y      -= windowHeight/2;
         platforms[i].x      *= camera.scale;
         platforms[i].y      *= camera.scale;
         platforms[i].x      += windowWidth/2;
         platforms[i].y      += windowHeight/2;
         platforms[i].textureScale *= camera.scale;
         SDL_SetRenderDrawColor(renderer,200,200,200,255);
         
         // Add texture to platform
         FtexturePlatform(i);
         
         // Reset data to normal map data!
         platforms[i].x = (platforms[i].x-windowWidth/2)/camera.scale  + windowWidth/2;
         platforms[i].y = (platforms[i].y-windowHeight/2)/camera.scale + windowHeight/2;
 
         platforms[i].width  /= camera.scale;
         platforms[i].height /= camera.scale;
             
         platforms[i].x += camera.x;
         platforms[i].y += camera.y;
         platforms[i].textureScale /= camera.scale;

      }
   }
   for(int i = 0;i<sizeof(triggers)/sizeof(triggers[0]);i++){
      if(triggers[i].reserved){         
         // Camera offsetted data !
         triggers[i].x -= camera.x;
         triggers[i].y -= camera.y;
         triggers[i].width  *= camera.scale;
         triggers[i].height *= camera.scale;
      
         triggers[i].x      -= windowWidth/2;
         triggers[i].y      -= windowHeight/2;
         triggers[i].x      *= camera.scale;
         triggers[i].y      *= camera.scale;
         triggers[i].x      += windowWidth/2;
         triggers[i].y      += windowHeight/2;
         
         SDL_SetRenderDrawColor(renderer,200,200,200,255);
         SDL_SetTextureAlphaMod(tex_trigger,100);
         for(int j = 0;j<triggers[i].width;j += 25){
            for(int k = 0;k<triggers[i].height;k += 25){
               int u;int v;
               if(j > triggers[i].width-25){u = (-j+triggers[i].width);}
               else{u = 25;}
               if(k > triggers[i].height-25){v = (-k+triggers[i].height);}
               else{v = 25;}
               
               SDL_RenderCopy(renderer,tex_trigger,
               NULL,
               &(SDL_Rect){triggers[i].x+j,triggers[i].y+k,u,v});
            }
         }
         SDL_SetTextureAlphaMod(tex_trigger,255);
         SDL_SetRenderDrawColor(renderer,0,0,0,255);
         SDL_RenderDrawRect(renderer,&(SDL_Rect){triggers[i].x,triggers[i].y,triggers[i].width,triggers[i].height});
         
         // Reset data to normal map data!
         triggers[i].x = (triggers[i].x-windowWidth/2)/camera.scale  + windowWidth/2;
         triggers[i].y = (triggers[i].y-windowHeight/2)/camera.scale + windowHeight/2;
 
         triggers[i].width  /= camera.scale;
         triggers[i].height /= camera.scale;
             
         triggers[i].x += camera.x;
         triggers[i].y += camera.y;
 
      }
   }
   FDisplayHUD();
   /////-------------------------------END OF RENDERING
}
void FUpdate_Data(){
   if(level.checkpointShowTimer > 0){
      level.checkpointShowTimer -= 1000*app.deltaTime;
   }
    if(!level.Paused){
    FPlayer_Movement();
    if(app.inputChange && !level.Finished && level.Started){
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
   app.deltaTimeGhost = app.deltaTime;
   if(player[0].keys.r){
    FGameRestart();
   }
   player[0].onPlatform = false;
   player[0].onWall = false;
   player[1].onPlatform = false;
   player[1].onWall = false;
   for (int i = 0;i<sizeof(platforms)/sizeof(platforms[0]);i++){
      if (platforms[i].reserved){
      if(FCheck_Collision(player[1],i)){
         FCollision_Response(&player[1],i);
      }
      if(FCheck_Collision(player[0],i)){
         FCollision_Response(&player[0],i);
      }
    } 
   }
   if(!level.Finished && level.Started){
      level.timer += 1000*app.deltaTime;
   }
   else if(!level.Started){level.timer = 0;}
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
         platforms[i].platformUsed = false;  
        }        
      }
      remove("levels/temp.txt");
      mapData.ghostEnd = false;
      mapData.ghostNextInput = -10;
      mapData.fileadditionIndex = 0;
      mapData.ghostCurrentIndex = 0;
      level.Finished = false;
      level.Started = false;
      player[0].x = player[0].spawnX;
      player[0].y = player[0].spawnY;
      player[1].x = player[0].spawnX;
      player[1].y = player[0].spawnY;
      player[0].veloX = 0;
      player[0].veloY = 0;
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