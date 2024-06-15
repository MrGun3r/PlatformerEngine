void FSaveMap(){
   SDL_SetRenderDrawColor(renderer,100,100,100,100);
   SDL_RenderFillRect(renderer,&(SDL_Rect){30,100,windowWidth-60,150});
   renderText(sizeof("Name file:"),"Name file:",35,170,sizeof("Name file:")*12,15,255,(int[3]){255,255,255});
   renderText(editor.fileNameSize,editor.fileNameSave,45+sizeof("Name file:")*12,170,editor.fileNameSize*12,15,255,(int[3]){255,255,255});
   if(editor.status == 0){
      renderText(33,"Enter to save . Escape to cancel",45,210,33*12,15,255,(int[3]){255,255,255});
   }
   else if (editor.status == 1){
      renderText(33,"Enter to load . Escape to cancel",45,210,33*12,15,255,(int[3]){255,255,255});
   }
   
   if(editor.saving){
      editor.typing = false;
      printf("boo");
      char filePath[256];
      sprintf(filePath,"levels/%s.txt",editor.fileNameSave);
      FILE *file = fopen(filePath,"w");
      char mapData[256];
      char playerData[256];
      int checkPointsCount = 0;
      for(int i = 1;i<sizeof(platforms)/sizeof(platforms[0]);i++){
       if(platforms[i].reserved && platforms[i].type == 2){
         checkPointsCount++;
       }
      }
      sprintf(mapData,"m:%s,-1,-10000,-10000,10000,10000,%d;\n\0",editor.fileNameSave,checkPointsCount);
      sprintf(playerData,"p:%d,%d,%d,%d,%d;\n\0",(int)player[0].x,(int)player[0].y,(int)player[0].width,(int)player[0].width,(int)player[0].height);
      fputs(mapData,file);
      fputs(playerData,file);
      for(int i = 0;i<sizeof(platforms)/sizeof(platforms[0]);i++){
         if(platforms[i].reserved){
            char* platformData = malloc(2000);
            char slopeInv;
            char textureStr;
            char textureStrPer;
          if(platforms[i].slopeInv){
            slopeInv = 't';
          }else{slopeInv = 'f';}
          if(platforms[i].textureStretch){
            textureStr = 't';
          }else{textureStr = 'f';}
          if(platforms[i].textureStretchPer){
            textureStrPer = 't';
          }else{textureStrPer = 'f';}    
            sprintf(platformData,"%d:%d,%d,%d,%d,%f,%c,%d,%d,%c,%c,%d;\n\0",i,(int)platforms[i].x,(int)platforms[i].y,(int)platforms[i].width,(int)platforms[i].height,platforms[i].slope,slopeInv,(int)platforms[i].textureScale,(int)platforms[i].textureInt,textureStr,textureStrPer,platforms[i].type);
            fputs(platformData,file);
            free(platformData);
         }
      }
      for(int i = 0;i<sizeof(triggers)/sizeof(triggers[0]);i++){
         if(triggers[i].reserved){
            char* triggerData = malloc(2000);   
            sprintf(triggerData,"t%d:%d,%d,%d,%d,%d;\n\0",i,(int)triggers[i].x,(int)triggers[i].y,(int)triggers[i].width,(int)triggers[i].height,(int)triggers[i].triggerType);
            fputs(triggerData,file);
            free(triggerData);
         }
      }
      fputs("/",file);
      fclose(file);
      editor.typing = false;
      editor.saving = false;
   
   }
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
      if(typeFound && count == dataType && buffer[i] != ','){
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

void FSetDataMap(char* path,int pathSize){
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
   
   
   // Read from txt file Map Data

   SDL_memcpy(level.absolutePath,path,pathSize+7);
   FILE *fileMap = fopen(path,"r");
   if(!fileMap){return;}
 
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
         else{
            // platforms
            DataImport = 0;
         }
         if(DataImport == 0){
            ID = atoi(importBufferShortened);
         }
         else if(DataImport == 3){
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

}

void FSetValue(char* importBuffer,int importBufferSize,int data,int ID,int dataType){
   if(dataType == 0){
     platforms[ID].reserved = true;
     bool boolean;
     SDL_Texture* texture = NULL;
     switch(data){
      case 0:
       platforms[ID].x = atof(importBuffer);
       break;
      case 1:
       platforms[ID].y = atof(importBuffer);
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
       if(importBuffer[0] == 'f'){boolean = false;}
       else{boolean = true;}
       platforms[ID].slopeInv = boolean;
       break;
      case 6:
       platforms[ID].textureScale = atof(importBuffer);
       break;
      case 7:
       if(atoi(importBuffer) == 1){
         texture = tex_tile;
       }
       else if(atoi(importBuffer) == 2){
         texture = tex_tile2;
       }
       else if(atoi(importBuffer) == 3){
         texture = tex_tile3;
       }
       else if(atoi(importBuffer) == 4){
         texture = tex_tile4;
       }
       else if(atoi(importBuffer) == 5){
         texture = tex_tileStart;
       }
       else if(atoi(importBuffer) == 6){
         texture = tex_tileBnW;
       }
       platforms[ID].textureInt = atoi(importBuffer);
       platforms[ID].texture = texture;
      case 8:
       if(importBuffer[0] == 'f'){boolean = false;}
       else{boolean = true;}
       platforms[ID].textureStretchPer = boolean;
       break;
      case 9:
       if(importBuffer[0] == 'f'){boolean = false;}
       else{boolean = true;}
       platforms[ID].textureStretch = boolean;
       break;
      case 10:
       platforms[ID].type = atoi(importBuffer);
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
         break;
      case 3:
         player[0].width = atof(importBuffer);
         player[1].width = atof(importBuffer);
         break;
      case 4:
         player[0].height = atof(importBuffer);
         player[1].height = atof(importBuffer);
         break;
      case 5:
         level.checkpointsSize = atoi(importBuffer);
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
     }
     }
     else if (dataType == 3){
      triggers[ID].reserved = true;
      switch(data){
      case 0:
         triggers[ID].x = atof(importBuffer);
         break;
      case 1:
         triggers[ID].y = atof(importBuffer);
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
     }
     }
}