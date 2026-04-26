void FSaveMap(char mapName[256]){
      char filePath[256];
      sprintf(filePath,"levels/%s.txt",mapName);
      FILE *file = fopen(filePath,"w");
      char mapDatal[256];
      char playerData[256];
      sprintf(mapDatal,"m:%s,-1,%d,%d,%d,%d,%s,%d,%f,%d,0;\n\0",textbox[0].textContent,(int)mapData.xMin,(int)mapData.yMin,(int)mapData.xMax,(int)mapData.yMax,backgrounds[app.backgroundInt].textureName,(int)app.backgroundOpacity,(double)editor.GameScale,(int)(editor.StarTimeMs*10+editor.StarTime*1000));
      sprintf(playerData,"p:%d,%d,%d,%d;\n\0",(int)player[0].x,(int)player[0].y,(int)player[0].width,(int)player[0].height);
      fputs(mapDatal,file);
      fputs(playerData,file);
      for(int i = 0;i<sizeof(platforms)/sizeof(platforms[1]);i++){
         if(platforms[i].reserved){
            char* platformData = malloc(2000);
 
            sprintf(platformData,"%d:%d,%d,%d,%d,%f,%d,%d,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d;\n\0",i,(int)platforms[i].x,(int)platforms[i].y,(int)platforms[i].width,(int)platforms[i].height,platforms[i].slope,(int)platforms[i].slopeInv,(int)platforms[i].textureScale,textures[(int)platforms[i].textureInt].textureName,(int)platforms[i].textureStretch,platforms[i].type,(int)platforms[i].textureOffsetX,(int)platforms[i].textureOffsetY,platforms[i].collidable,(int)platforms[i].opacity,(int)platforms[i].red,(int)platforms[i].green,(int)platforms[i].blue,(int)platforms[i].textureAnimationTime,(int)platforms[i].moveNodeInt,(int)platforms[i].moveSpeed,(int)platforms[i].textureRotation,platforms[i].NofinishAnimation,(int)platforms[i].textureOffsetX_Move,(int)platforms[i].textureOffsetY_Move,(int)platforms[i].grapplable);
            fputs(platformData,file);
            free(platformData);
         }
      }
      for(int i = 0;i<sizeof(triggers)/sizeof(triggers[0]);i++){
         if(triggers[i].reserved){
            char* triggerData = malloc(2000);   
            sprintf(triggerData,"t%d:%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d;\n\0",i,(int)triggers[i].x,(int)triggers[i].y,(int)triggers[i].width,(int)triggers[i].height,(int)triggers[i].triggerType,(int)triggers[i].opacity,(int)triggers[i].Value1,(int)triggers[i].Value2,(int)triggers[i].Value3,(int)triggers[i].Value4,(int)triggers[i].useDelay,(int)triggers[i].reuseDelay);
            fputs(triggerData,file);
            free(triggerData);
         }
      }
      for(int i = 0;i<sizeof(light)/sizeof(light[0]);i++){
        if(light[i].reserved){
            char* lightData = malloc(2000);   
            sprintf(lightData,"l%d:%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s;\n\0",i,(int)light[i].x,(int)light[i].y,(int)light[i].width,(int)light[i].height,(int)light[i].rotation,(int)light[i].angle,(int)light[i].brightness,(int)light[i].visibility,(int)light[i].red,(int)light[i].green,(int)light[i].blue,(int)light[i].moveNodeInt,(int)light[i].moveSpeed,lightTextures[light[i].lightInt].textureName);
            fputs(lightData,file);
            free(lightData);
         } 
      }
      for(int i = 0;i<sizeof(displacement)/sizeof(displacement[0]);i++){
        if(displacement[i].reserved){
            char* displacementData = malloc(2000);   
            sprintf(displacementData,"d%d:%d,%d,%d,%d,%d,%d,%d,%d,%d,%d;\n\0",i,(int)displacement[i].x,(int)displacement[i].y,(int)displacement[i].width,(int)displacement[i].height,(int)displacement[i].type,(int)displacement[i].powerType,(int)displacement[i].power,(int)displacement[i].opacity,(int)displacement[i].moveNodeInt,(int)displacement[i].moveSpeed);

            fputs(displacementData,file);
            free(displacementData);
         } 
      }
      for(int i = 0;i<sizeof(deathbox)/sizeof(deathbox[0]);i++){
        if(deathbox[i].reserved){
            char* deathboxData = malloc(2000);   
            sprintf(deathboxData,"k%d:%d,%d,%d,%d,%d,%d,%d;\n\0",i,(int)deathbox[i].x,(int)deathbox[i].y,(int)deathbox[i].width,(int)deathbox[i].height,(int)deathbox[i].opacity,(int)deathbox[i].moveNodeInt,(int)deathbox[i].moveSpeed);

            fputs(deathboxData,file);
            free(deathboxData);
         } 
      }
      for(int i = 0;i<sizeof(movenodes)/sizeof(movenodes[0]);i++){
         if(movenodes[i].reserved){
            char* movenodeIndex = malloc(100);
            sprintf(movenodeIndex,"n%d:%d",i,movenodes[i].wrap);
            fputs(movenodeIndex,file);
            free(movenodeIndex);
            for(int j = 0;j<movenodes[i].nodesCount;j++){
               char* movenodeData = malloc(100);   
               sprintf(movenodeData,",%d,%d",(int)movenodes[i].positions[j][0],(int)movenodes[i].positions[j][1]); 
               fputs(movenodeData,file);
               free(movenodeData);
            }
            fputs(";\n\0",file);
         }
      }
      for(int i = 0;i<sizeof(scripts)/sizeof(scripts[0]);i++){
         if(scripts[i].reserved){
            char* scriptData = malloc(2000);   
            sprintf(scriptData,"s%d:%d,%d,%d,%d,%s,%d,%d;\n\0",i,(int)scripts[i].x,(int)scripts[i].y,(int)scripts[i].width,(int)scripts[i].height,scriptfiles[scripts[i].scriptInt].scriptName,(int)scripts[i].useDelay,(int)scripts[i].reuseDelay);
            fputs(scriptData,file);
            free(scriptData);
         }
      }
      for(int i = 0;i<sizeof(enemy)/sizeof(enemy[0]);i++){
         if(enemy[i].reserved){
            char* enemyData = malloc(2000);   
            sprintf(enemyData,"e%d:%d,%d,%d,%d,%d,%d,%d;\n\0",i,(int)enemy[i].type,(int)enemy[i].x,(int)enemy[i].y,(int)enemy[i].width,(int)enemy[i].height,(int)enemy[i].maxSpeed,(int)enemy[i].maxHealth);
            fputs(enemyData,file);
            free(enemyData);
         }
      }
      for(int i = 0;i<sizeof(specials)/sizeof(specials[0]);i++){
         if(specials[i].reserved){
            char* specialsData = malloc(2000);   
            sprintf(specialsData,"c%d:%d,%d,%d,%d,%d;\n\0",i,(int)specials[i].x,(int)specials[i].y,(int)specials[i].width,(int)specials[i].height,(int)specials[i].type);
            fputs(specialsData,file);
            free(specialsData);
         }
      }
      for(int i = 0;i<sizeof(textpopups)/sizeof(textpopups[0]);i++){
         if(textpopups[i].reserved){
            char* textpopupsData = malloc(2000);   
            sprintf(textpopupsData,"x%d:%d,%d,%d,%d,%s,%d,%d,%d;\n\0",i,(int)textpopups[i].x,(int)textpopups[i].y,(int)textpopups[i].width,(int)textpopups[i].height,textpopups[i].textContent,(int)textpopups[i].xPopup,(int)textpopups[i].yPopup,(int)textpopups[i].font);
            fputs(textpopupsData,file);
            free(textpopupsData);
         }
      }
      fputs("/",file);
      fclose(file);
      sprintf(editor.alertText,"Saved Map: %s",editor.mapName);
      editor.alertTimer = 5000;
}


void FlistLevels(){
   // copy pasted off of stackoverflow
  DIR *p;
  struct dirent *pp;     
  p = opendir ("./levels");
  int index = 0;
  if (p != NULL)
  {
    while ((pp = readdir (p))!=NULL) {
      int length = strlen(pp->d_name);
      if (strncmp(pp->d_name + length - 4, ".txt", 4) == 0) {
         char tempName[256];
         int tempNameSize = 0;
         for(int i = 0;i<sizeof(pp->d_name);i++){
           if(pp->d_name[i] == '.'){break;}
           SDL_memcpy(&tempName[tempNameSize],&pp->d_name[i],1);
           tempNameSize++;
         }
         tempName[tempNameSize] = '\0';
         SDL_memcpy(levelsList[index].levelName,tempName,tempNameSize+1);
         sprintf(levelsList[index].levelPath,"levels/%s.txt",levelsList[index].levelName);
         levelsList[index].levelPath[tempNameSize+11] = '\0';
         levelsList[index].levelNameSize = tempNameSize+1;
         levelsList[index].reserved = true;
         index++;
      }
    }
    (void) closedir (p);
  }
}

char* FGetDataMap(char* path,char* type,int dataType,int fileNameSize){
   FILE *fileMap = fopen(path,"r");
   char buffer[256];
   char tempBuffer[256];
   int tempBufferSize = 0;
   char *exportBuffer = malloc(256);
   bool typeFound = false;
   bool finished = false;
   int exportBufferSize = 0;
   while(fgets(buffer,256,fileMap) && !finished){   
    int count = 0;
    for(int i = 0;i<256;i++){
      if(typeFound && count == dataType && buffer[i] != ',' && buffer[i] != ';'){
         exportBuffer[exportBufferSize] = buffer[i];
         exportBufferSize++;
      }
      if(buffer[i] == ';'){
         if(typeFound){
            finished = true;
            exportBuffer[exportBufferSize] = '\0';
         }
         tempBufferSize = 0;
         break;
      }
      else if(buffer[i] == ':'){
         if (!FCompareStrings(tempBuffer,type)){tempBufferSize = 0;break;}  
         else{typeFound = true;}     
      }
      else if(buffer[i] == ','){
       count++;
      }
      tempBuffer[tempBufferSize] = buffer[i];
      tempBufferSize++;
      tempBuffer[tempBufferSize] = '\0';
    }
   }
   fclose(fileMap);
   if(!typeFound){return NULL;}
   return exportBuffer;
}

int FSetDataMap(char* path,int pathSize){
   // Read from txt file Map Data
   SDL_memcpy(level.absolutePath,path,pathSize+7);
   FILE *fileMap = fopen(path,"r");
   // Check if file exists
   if(!fileMap){return -1;}



   // This function will load upon starting a map
   // Hard coded set values
   
   player[0].veloX = 0;
   player[0].veloY = 0;
   player[0].accX = 0;
   player[0].accY = 0;
   player[0].jumpVelo = 0;
   player[0].onPlatform = false;
   player[0].playerControl = 1;
   player[1].playerControl = 1;
   
   player[0].keys.up = false;
   player[0].keys.down = false;
   player[0].keys.left = false;
   player[0].keys.right = false;
   player[0].keys.shift = false;
   player[0].keys.r = false;
   player[0].keys.escapeRelease = true;
   player[0].keys.escape = false;
   
   mapData.ghostEnd = false;
   mapData.ghostInGame = false;
  
   player[1].keys.up = false;
   player[1].keys.down = false;
   player[1].keys.left = false;
   player[1].keys.right = false;
   player[1].keys.shift = false;
   mapData.ghostNextInput = -10;
   mapData.fileadditionIndex = 0;
   mapData.ghostCurrentIndex = 0;
   camera.scale = 1;
   camera.x = 0;camera.y = 0;

   for(int i = 0;i<sizeof(triggers)/sizeof(triggers[0]);i++){
      triggers[i].reserved = false;
   }
   for(int i = 0;i<sizeof(platforms)/sizeof(platforms[0]);i++){
      platforms[i].reserved = false;
   }
   for(int i = 0;i<sizeof(light)/sizeof(light[0]);i++){
      light[i].reserved = false;
   }
   for(int i = 0;i<sizeof(displacement)/sizeof(displacement[0]);i++){
      displacement[i].reserved = false;
   }
    for(int i = 0;i<sizeof(deathbox)/sizeof(deathbox[0]);i++){
      deathbox[i].reserved = false;
   }
   for(int i = 0;i<sizeof(movenodes)/sizeof(movenodes[0]);i++){
      movenodes[i].reserved = false;
      movenodes[i].nodesCount = 0;
   }
   for(int i = 0;i<sizeof(enemy)/sizeof(enemy[0]);i++){
      enemy[i].reserved = false;
   }
   for(int i = 0;i<sizeof(scripts)/sizeof(scripts[0]);i++){
      scripts[i].reserved = false;  
   }
   for(int i = 0;i<sizeof(specials)/sizeof(specials[0]);i++){
      specials[i].reserved = false; 
   }
   for(int i = 0;i<sizeof(textpopups)/sizeof(textpopups[0]);i++){
     if(textpopups[i].reserved){
      textpopups[i].reserved = false;
      if(textpopups[i].textContent != NULL){
         free(textpopups[i].textContent);
      }
     } 
      
      
   }

   
 
   char buffer[256];
   char importBuffer[256];
   while(fgets(buffer,256,fileMap)){
     
     int importBufferSize = 0;
     int DataImport = -1;
     int IndexData = 0;
     int ID = 0;
     for(int i = 0;i<256;i++){ 
      if(buffer[i] == ';'){
         char *importBufferShortened = malloc(importBufferSize+1);
         SDL_memcpy(importBufferShortened,importBuffer,importBufferSize+1);
         importBufferShortened[importBufferSize] = '\0';
         
         
         FSetValue(importBufferShortened,importBufferSize,IndexData,ID,DataImport);
         importBufferSize = 0;
         DataImport = -1;
         free(importBufferShortened);
         break;
      }
      if(buffer[i] == ':'){
         char *importBufferShortened = malloc(importBufferSize+1);
         SDL_memcpy(importBufferShortened,importBuffer,importBufferSize+1);
         importBufferShortened[importBufferSize] = '\0';
         
   
         importBufferSize = 0;
         if(importBufferShortened[0] == 'p'){
            // player
            DataImport = 1;
         }
         else if(importBufferShortened[0] == 'm'){
            // map data
            DataImport = 2;
         }
         else if (importBufferShortened[0] == 't'){
            // Trigger
            DataImport = 3;
         }
         else if (importBufferShortened[0] == 'l'){
            // Light
            DataImport = 4;
         }
         else if (importBufferShortened[0] == 'd'){
            // Displacement
            DataImport = 5;
         }
         else if (importBufferShortened[0] == 'k'){
            // DeathBox
            DataImport = 6;
         }
         else if (importBufferShortened[0] == 'n'){
            // DeathBox
            DataImport = 7;
         }
         else if (importBufferShortened[0] == 's'){
            // Script
            DataImport = 8;
         }
         else if (importBufferShortened[0] == 'e'){
            // Enemy
            DataImport = 9;
         }
         else if (importBufferShortened[0] == 'c'){
            // special
            DataImport = 10;
         }
         else if (importBufferShortened[0] == 'x'){
            // text
            DataImport = 11;
         }
         else{
            // platforms
            DataImport = 0;
         }
         if(DataImport == 0){
            ID = atoi(importBufferShortened);
         }
         else if(DataImport >= 3 && DataImport <= 11){
            ID = atoi(&importBufferShortened[1]);
         }
         else{ID = -1;}
         free(importBufferShortened);
         continue;
      }
      if(buffer[i] == ','){
         char* importBufferShortened = malloc(importBufferSize+1);
         SDL_memcpy(importBufferShortened,importBuffer,importBufferSize);
         importBufferShortened[importBufferSize] = '\0';

         FSetValue(importBufferShortened,importBufferSize,IndexData,ID,DataImport);
         importBufferSize = 0;
         free(importBufferShortened);
         IndexData += 1;
         continue;
         
      }
      /// fill importBuffer ----------
      importBuffer[importBufferSize] = buffer[i];
      importBufferSize++;
      //------------------------------
     
     }
   }
   if(mapData.PBTimer>0){
    mapData.ghostInGame = true; 
   }
   fclose(fileMap);
   if(app.status == 1){
      app.backgroundInt = FindBackgroundInt(FGetDataMap(level.absolutePath,"m",6,len(level.absolutePath)));
      app.backgroundOpacity = atoi(FGetDataMap(level.absolutePath,"m",7,len(level.absolutePath)));
   }
   int checkPointsCount = 0;
   for(int i = 1;i<sizeof(platforms)/sizeof(platforms[0]);i++){
       if(platforms[i].reserved && platforms[i].type == 2){
         checkPointsCount++;
       }
      }
      level.checkpointsSize = checkPointsCount; 
   return 0;
}

void FSetValue(char* importBuffer,int importBufferSize,int data,int ID,int dataType){
   if(dataType == 0){
     platforms[ID].reserved = true;
     bool boolean;
     SDL_Texture* texture = NULL;
     switch(data){
      case 0:
       platforms[ID].x = atof(importBuffer);
       platforms[ID].spawnX = atof(importBuffer);
       break;
      case 1:
       platforms[ID].y = atof(importBuffer);
       platforms[ID].spawnY = atof(importBuffer);
       break;
      case 2:
       platforms[ID].width = atof(importBuffer);
       break;
      case 3:
       platforms[ID].height = atof(importBuffer);
       break;
      case 4:
       platforms[ID].slope = atof(importBuffer);
       break;
      case 5: 
       platforms[ID].slopeInv = atoi(importBuffer);
       break;
      case 6:
       platforms[ID].textureScale = atof(importBuffer);
       break;
      case 7:
      if(FCompareStrings(importBuffer,"None\0")){
         platforms[ID].textureInt = 0;
         platforms[ID].texture = NULL;
      }
      else {
       platforms[ID].textureInt = FindTextureInt(importBuffer);  
       platforms[ID].texture = textures[platforms[ID].textureInt%50].texture;
      }
      case 8:
       platforms[ID].textureStretch = atoi(importBuffer);
       break;
      case 9:
       platforms[ID].type = atoi(importBuffer);
       break;
      case 10:
       platforms[ID].textureOffsetX = atof(importBuffer);
       break;
      case 11:
       platforms[ID].textureOffsetY = atof(importBuffer);
       break;
      case 12:
       platforms[ID].collidable = (bool)atoi(importBuffer);
       break;
      case 13:
       platforms[ID].opacity = atof(importBuffer);
       break;
      case 14:
       platforms[ID].red = atof(importBuffer);
       break;
      case 15:
       platforms[ID].green = atof(importBuffer);
       break;
      case 16:
       platforms[ID].blue = atof(importBuffer);
       break;
      case 17:
       platforms[ID].textureAnimationTime = atoi(importBuffer);
       break;
      case 18:
       platforms[ID].moveNodeInt = atoi(importBuffer);
       platforms[ID].moveNodeIntSpawn = atoi(importBuffer);
       break;
      case 19:
       platforms[ID].moveSpeed = atof(importBuffer);
       platforms[ID].moveSpeedSpawn = atof(importBuffer);
       break;
      case 20:
       platforms[ID].textureRotation = atoi(importBuffer);
       break;
      case 21:
       platforms[ID].NofinishAnimation = atoi(importBuffer);
       break;
      case 22:
       platforms[ID].textureOffsetX_Move = atof(importBuffer);
       break;
      case 23:
       platforms[ID].textureOffsetY_Move = atof(importBuffer);
       break;
      case 24:
       platforms[ID].grapplable = (bool)atoi(importBuffer);
       break;
      }
     }
     else if(dataType == 1){
      player[0].ghost = false;
      player[1].ghost = true;
      switch (data)
      {
      case 0:
         player[0].x = atof(importBuffer);
         player[0].spawnX = atof(importBuffer);
         player[1].x = atof(importBuffer);
         player[1].spawnX = atof(importBuffer);
         break;
      case 1:
         player[0].y = atof(importBuffer);
         player[0].spawnY = atof(importBuffer);
         player[1].y = atof(importBuffer);
         player[1].spawnY = atof(importBuffer);
         break;
      case 2:
         player[0].Owidth = atof(importBuffer);
         player[1].Owidth = atof(importBuffer);
         player[0].width = atof(importBuffer);
         player[1].width = atof(importBuffer);
         break;
      case 3:
         player[0].height = atof(importBuffer);
         player[1].height = atof(importBuffer);
         break;
      }
     }
     else if(dataType == 2){    
      switch(data){
      case 0:
         SDL_memcpy(mapData.mapName,importBuffer,importBufferSize);
         mapData.mapNameLen = importBufferSize;
         break;
      case 1:
         mapData.PBTimer = atoi(importBuffer);
         break;
      case 2:
         mapData.xMin = atof(importBuffer);
         break;
      case 3:
         mapData.yMin = atof(importBuffer);
         break;
      case 4:
         mapData.xMax = atof(importBuffer);
         break;
      case 5:
         mapData.yMax = atof(importBuffer);
         break;
      case 8:
         camera.scaleReal = atof(importBuffer);
         editor.GameScale = camera.scaleReal;
         level.cameraScaleStart = camera.scaleReal;
         break;
      case 9:
        level.StarTime = atoi(importBuffer);
        
        break;
     }
     }
     else if (dataType == 3){
      triggers[ID].reserved = true;
      switch(data){
      case 0:
         triggers[ID].x = atof(importBuffer);
         triggers[ID].spawnX = atof(importBuffer);
         break;
      case 1:
         triggers[ID].y = atof(importBuffer);
         triggers[ID].spawnY = atof(importBuffer);
         break;
      case 2:
         triggers[ID].width = atof(importBuffer);
         break;
      case 3:
         triggers[ID].height = atof(importBuffer);
         break;
      case 4:
         triggers[ID].triggerType = atoi(importBuffer);
         break;
      case 5:
         triggers[ID].opacity = atof(importBuffer);
         break;
      case 6:
         triggers[ID].Value1 = atof(importBuffer);
         break;
      case 7:
         triggers[ID].Value2 = atof(importBuffer);
         break;
      case 8:
         triggers[ID].Value3 = atof(importBuffer);
         break;
      case 9:
         triggers[ID].Value4 = atof(importBuffer);
         break;
      case 10:
         triggers[ID].useDelay = atof(importBuffer);
         break;
      case 11:
         triggers[ID].reuseDelay = atof(importBuffer);
         break;

     }
     }
     else if (dataType == 4){
      light[ID].reserved = true;
      
      switch(data){
      case 0:
         light[ID].x = atof(importBuffer);
         light[ID].spawnX = atof(importBuffer);
         break;
      case 1:
         light[ID].y = atof(importBuffer);
         light[ID].spawnY = atof(importBuffer);
         break;
      case 2:
         light[ID].width = atof(importBuffer);
         break;
      case 3:
         light[ID].height = atof(importBuffer);
         break;
      case 4:
         light[ID].rotation = atof(importBuffer);
         break;
      case 5:
         light[ID].angle = atof(importBuffer);
         break;
      case 6:
         light[ID].brightness = atof(importBuffer);
         break;
      case 7:
         light[ID].visibility = atof(importBuffer);
         break;
      case 8:
         light[ID].red = atof(importBuffer);
         break;
      case 9:
         light[ID].green = atof(importBuffer);
         break;
      case 10:
         light[ID].blue = atof(importBuffer);
         break;
      case 11:
         light[ID].moveNodeInt = atoi(importBuffer);
         light[ID].moveNodeIntSpawn = atoi(importBuffer);
         break;
      case 12:
         light[ID].moveSpeed = atof(importBuffer);
         light[ID].moveSpeedSpawn = atof(importBuffer);
         break;
      case 13:
         light[ID].lightInt = FindLightInt(importBuffer);
         break;
     }
     }
     else if (dataType == 5){
      displacement[ID].reserved = true;
      switch(data){
      case 0: 
         displacement[ID].x = atof(importBuffer);
         displacement[ID].spawnX = atof(importBuffer);
         break;
      case 1: 
         displacement[ID].y = atof(importBuffer);
         displacement[ID].spawnY = atof(importBuffer);
         break;
      case 2: 
         displacement[ID].width = atof(importBuffer);
         break;
      case 3: 
         displacement[ID].height = atof(importBuffer);
         break;
      case 4: 
         displacement[ID].type = atoi(importBuffer);
         break;
      case 5: 
         displacement[ID].powerType = atoi(importBuffer);
         break;
      case 6: 
         displacement[ID].power = atof(importBuffer);
         break;
      case 7: 
         displacement[ID].opacity = atof(importBuffer);
         break;
      case 8: 
         displacement[ID].moveNodeInt = atoi(importBuffer);
         displacement[ID].moveNodeIntSpawn = atoi(importBuffer);
         break;
      case 9: 
         displacement[ID].moveSpeed = atof(importBuffer);
         displacement[ID].moveSpeedSpawn = atof(importBuffer);
         break;
      } 
     }
     else if (dataType == 6){
      deathbox[ID].reserved = true;
      switch(data){
      case 0: 
         deathbox[ID].x = atof(importBuffer);
         deathbox[ID].spawnX = atof(importBuffer);
         break;
      case 1: 
         deathbox[ID].y = atof(importBuffer);
         deathbox[ID].spawnY = atof(importBuffer);
         break;

      case 2: 
         deathbox[ID].width = atof(importBuffer);
         break;
      case 3: 
         deathbox[ID].height = atof(importBuffer);
         break;   
      case 4: 
         deathbox[ID].opacity = atof(importBuffer);
         break;   
      case 5: 
         deathbox[ID].moveNodeInt = atoi(importBuffer);
         deathbox[ID].moveNodeIntSpawn = atoi(importBuffer);
         break;  
      case 6: 
         deathbox[ID].moveSpeed = atof(importBuffer);
         deathbox[ID].moveSpeedSpawn = atof(importBuffer);
         break;
      }
          
     }
     else if (dataType == 7){
      movenodes[ID].reserved = true;
      if(data == 0){
         movenodes[ID].wrap = (bool)atoi(importBuffer);
      }
      else{
         switch((data+1) % 2){
         case 0:
           movenodes[ID].positions[movenodes[ID].nodesCount][0] = atof(importBuffer);
           break;
         case 1:
           movenodes[ID].positions[movenodes[ID].nodesCount][1] = atof(importBuffer);
           movenodes[ID].nodesCount++;
           break;
      }
      }
     }
     else if (dataType == 8){
      scripts[ID].reserved = true;
       switch(data){
         case 0:
           scripts[ID].x = atof(importBuffer);
           break;
         case 1:
           scripts[ID].y = atof(importBuffer);
           break;
         case 2:
           scripts[ID].width = atof(importBuffer);
           break;
         case 3:
           scripts[ID].height = atof(importBuffer);
           break;
         case 4:
           scripts[ID].scriptInt = findScriptId(importBuffer);
           break;
         case 5:
           scripts[ID].useDelay = atoi(importBuffer);
           break;
         case 6:
           scripts[ID].reuseDelay = atoi(importBuffer);
           break;
      }
     }
     else if (dataType == 9){
      enemy[ID].reserved = true;
       switch(data){
         case 0:
           enemy[ID].type = atoi(importBuffer);
           break;
         case 1:
           enemy[ID].x = atof(importBuffer);
           enemy[ID].spawnX = enemy[ID].x;
           break;
         case 2:
           enemy[ID].y = atof(importBuffer);
           enemy[ID].spawnY = enemy[ID].y;
           break;
         case 3:
           enemy[ID].width = atof(importBuffer);
           break;
         case 4:
           enemy[ID].height = atof(importBuffer);
           break;
         case 5:
           enemy[ID].maxSpeed = atof(importBuffer);
           break;
         case 6:
           enemy[ID].maxHealth = atof(importBuffer);
           enemy[ID].health = atof(importBuffer);
           break;
         
      }
     }
     else if (dataType == 10){
      specials[ID].reserved = true;
       switch(data){
         case 0:
           specials[ID].x = atof(importBuffer);
           break;
         case 1:
           specials[ID].y = atof(importBuffer);
           break;
         case 2:
           specials[ID].width = atof(importBuffer);
           break;
         case 3:
           specials[ID].height = atof(importBuffer);
           break;
         case 4:
           specials[ID].type = atoi(importBuffer);
           break;
         
      }
     }
     else if (dataType == 11){
      textpopups[ID].reserved = true;
       switch(data){
         case 0:
           textpopups[ID].x = atof(importBuffer);
           break;
         case 1:
           textpopups[ID].y = atof(importBuffer);
           break;
         case 2:
           textpopups[ID].width = atof(importBuffer);
           break;
         case 3:
           textpopups[ID].height = atof(importBuffer);
           break;
         case 4:
           textpopups[ID].textContent = malloc(200);
           sprintf(textpopups[ID].textContent,importBuffer,len(importBuffer));
           break;
         case 5:
           textpopups[ID].xPopup = atof(importBuffer);
           break;
         case 6:
           textpopups[ID].yPopup = atof(importBuffer);
           break;
         case 7:
           textpopups[ID].font = atoi(importBuffer);
           break;
         
      }
     }
}