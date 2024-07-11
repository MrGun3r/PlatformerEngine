void FaddReplay(bool checkpoint){ 
   FILE *fileMap = fopen(level.absolutePath,"r");
   FILE *fileMapNew = NULL;
   if(!level.tempFileMade){
      fileMapNew = fopen("levels/temp.txt","w");
   }
   
   char buffer[256];
   bool add = false;
   while(fgets(buffer,256,fileMap)){
     
      if(!level.tempFileMade){
      if(buffer[0] == '/'){
       fputs("/\n",fileMapNew);
       add = true;
      }
      if(!add){
         fputs(buffer,fileMapNew);
         continue;
      }
      fclose(fileMapNew);
      }
      fileMapNew = fopen("levels/temp.txt","a");
      for(int i = 0;i<level.keyInputsSize;i++){
         fputc((int)level.keyInputs[i],fileMapNew);
      }
      if(checkpoint){
         char checkpointStr[256];
         sprintf(checkpointStr,"c%d:%d;\n\0",level.checkpointCount-1,level.checkpoints[level.checkpointCount-1]);
         
         fputs(checkpointStr,fileMapNew);

         char type[10];
         sprintf(type,"c%d",level.checkpointCount-1);
         level.LastCheckpointTimer = atoi(FGetDataMap(level.absolutePath,type,0,len(level.absolutePath)));
      }
      fclose(fileMapNew);
      break;
   }
   fclose(fileMap); 
}




void FcheckPB(){
   FaddReplay(false);
   level.tempFileMade = true;
   level.keyInputsSize = 0;

   FILE *fileMap = fopen("levels/temp.txt","r"); 
   if(level.timer >= mapData.PBTimer && mapData.PBTimer > 0){
    level.tempFileMade = false;
    fclose(fileMap);
    remove("levels/temp.txt");
    return;
   }
   level.newRecord = true;
   mapData.PBTimer = (int)level.timer;
   FILE *NewfileMap = (FILE*)fopen("levels/levelDataN.txt","w");
   char PBchar[(int)(SDL_log10(level.timer+1))+2];
   SDL_itoa((int)level.timer,PBchar,10);
   
   PBchar[(int)(SDL_log10(level.timer+1))+1] = ',';
   
   char buffer[256];
   int tempBufferSize = 0;
   char TempBuffer[256];
   while(fgets(buffer,256,fileMap)){
      if(buffer[0] == 'm'){
        int count = 0;
        for(int i = 0;i<256;i++){
         if(buffer[i] == ';'){
            TempBuffer[tempBufferSize]  = ';';
            TempBuffer[tempBufferSize+1]  = '\n';
            TempBuffer[tempBufferSize+2]  = '\0';
            break;
         }
         if(count == 1){
            if(buffer[i] == ','){
              SDL_memcpy(&TempBuffer[tempBufferSize],PBchar,(int)(SDL_log10(level.timer+1)) + 2);
              tempBufferSize += (int)(SDL_log10(level.timer+1) + 2);
              count++;
              continue;
            }
            continue;
         }
         if(buffer[i] == ','){
            count++;
         }
         TempBuffer[tempBufferSize] = buffer[i];
         tempBufferSize++;
        }
        fputs(TempBuffer,NewfileMap);
      }
      else{
         fputs(buffer,NewfileMap);
      }
   }
   fclose(NewfileMap);
   fclose(fileMap);

   remove("levels/temp.txt");
   remove(level.absolutePath);
   rename("levels/levelDataN.txt",level.absolutePath);

   
   return;
}