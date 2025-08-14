int findScriptId(char* scriptName){
    for(int i = 0;i<sizeof(scriptfiles)/sizeof(scriptfiles[0]);i++){
        if(FCompareStrings(scriptfiles[i].scriptName,scriptName)){
            return i;
        }
    }
    return -1;
}


void ExecuteScript(int index){
  int** script = scriptfiles[index].scriptCompiled; 
  for(int i = 0;i<scriptfiles[index].commandsNumber;i++){
    
    if(script[i][0] == 0){
      if(script[i][1] != INT32_MIN){
        camera.xReal = script[i][1];
      }
      if(script[i][2] != INT32_MIN){
        camera.yReal = script[i][2];
      }
      if(script[i][3] != INT32_MIN){
        camera.scaleReal = (double)(script[i][3])/100;
      }
      if(script[i][4] != INT32_MIN){
        camera.freeCam = script[i][4];
      }  
    }
    else if (script[i][0] == 1){
      if(script[i][1] != INT32_MIN){
        player[0].x = (double)script[i][1];
      }
      if(script[i][2] != INT32_MIN){
        player[0].y = (double)script[i][2];
      }
      if(script[i][3] != INT32_MIN){
        player[0].width = (double)script[i][3];
      }
      if(script[i][4] != INT32_MIN){
        player[0].height = (double)script[i][4];
      }
      if(script[i][5] != INT32_MIN){
        player[0].playerControl = (double)(script[i][5])/100;
      }
    }
    else if (script[i][0] == 2){
      int ID = script[i][1];
      if(script[i][2] != INT32_MIN){
        platforms[ID].x = (double)script[i][2];
      }
      if(script[i][3] != INT32_MIN){
        platforms[ID].y = (double)script[i][3];
      }
      if(script[i][4] != INT32_MIN){
        platforms[ID].width = (double)script[i][4];
      }
      if(script[i][5] != INT32_MIN){
        platforms[ID].height = (double)script[i][5];
      }
    }
  }
}


int CommandNumbers(int index){
  int i = 0;
  
  char *pch=strchr(scriptfiles[index].script,';');
  while (pch!=NULL) {
    i++;
    pch=strchr(pch+1,';');
  }
  return i;
}


void CompileScript(int index){
  char* script = scriptfiles[index].script;
  // Load 2d array for script
  scriptfiles[index].commandsNumber = CommandNumbers(index);
  
  scriptfiles[index].scriptCompiled = (int**)malloc(scriptfiles[index].commandsNumber*sizeof(int*));
  for(int i = 0;i<scriptfiles[index].commandsNumber;i++){
   scriptfiles[index].scriptCompiled[i] = (int*)malloc(6*sizeof(int));
   scriptfiles[index].scriptCompiled[i][0] = -1;
  }
  
  char* buffer = malloc(256*sizeof(char));
  int bufferSize = 0;
  int i = 1;
  int type = -1;
  int commands = 0;
  int valuetype = 1;
  while(script[i] != '!' || len(script) <= i){
    if(script[i] == '\n'){
      i++;
      continue;
    }
    if (script[i] == ':'){
        if(FCompareStrings("camera",buffer)){
          type = 0;
        }
        else if(FCompareStrings("player",buffer)){
          type = 1;
        }
        else if(FCompareStrings("platform",buffer)){
          type = 2;
        }
        else{
          printf("Unknown value to change: %s\n",buffer);
          return;
        }
        bufferSize = 0;
        if(type >= 0){
          scriptfiles[index].scriptCompiled[commands][0] = type;
        }
        i++;
        continue;
    }
    else if(script[i] == ','){
      if(!FCompareStrings(buffer,"NULL")){
        scriptfiles[index].scriptCompiled[commands][valuetype] = atoi(buffer);
      }
      else{
        scriptfiles[index].scriptCompiled[commands][valuetype] = INT32_MIN;
      }
       
       bufferSize = 0;
       valuetype++;
       i++;
       continue;
    }
    else if(script[i] == ';'){
       if(!FCompareStrings(buffer,"NULL")){
        scriptfiles[index].scriptCompiled[commands][valuetype] = atoi(buffer);
      }
      else{
        scriptfiles[index].scriptCompiled[commands][valuetype] = INT32_MIN;
      }
       valuetype = 1;
       bufferSize = 0;
       commands++;
       i++;
       continue;
    }
    buffer[bufferSize] = script[i];
    buffer[bufferSize+1] = '\0';
    bufferSize++;
    
    i++;
  }
  free(buffer);

  
}



void FLoadScripts(){
  SDL_memcpy(scriptfiles[0].scriptName,"None",5);
  DIR *p;
  struct dirent *pp;     
  p = opendir ("./assets/scripts");
  int index = 1;
  if (p != NULL)
  {
    while ((pp = readdir (p))!=NULL) {
      int length = strlen(pp->d_name);
      if (FCompareStrings(FlowerCase(&(pp->d_name[length-4]),4),".txt\0")) {
         char tempName[256];
         int tempNameSize = 0;
         for(int i = 0;i<sizeof(pp->d_name);i++){
           if(pp->d_name[i] == '.'){break;}
           SDL_memcpy(&tempName[tempNameSize],&pp->d_name[i],1);
           tempNameSize++;
         }
         tempName[tempNameSize] = '\0';
         char path[256];
         // Read script name
         scriptfiles[index].reserved = true;
         SDL_memcpy(scriptfiles[index].scriptName,tempName,tempNameSize+1);
         sprintf(path,"assets/scripts/%s\0",pp->d_name);
         
         // Save script file
         FILE *file = fopen(path,"r");
         fseek(file, 0L, SEEK_END);
         int size = ftell(file);
         fseek(file, 0L, SEEK_SET);
         scriptfiles[index].script = malloc((size+1)*sizeof(char));
         
         fread(scriptfiles[index].script,sizeof(char),size,file);
         scriptfiles[index].script[size] = '\0';
         if(scriptfiles[index].script != NULL && scriptfiles[index].script[0] == '>'){
            CompileScript(index);
            printf("Loaded %s\n",path);
         }
         fclose(file);    
         index++;     
      }
      
    }
    (void) closedir (p);
  }
/////////
}