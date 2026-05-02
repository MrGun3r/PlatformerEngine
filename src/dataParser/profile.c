
void SetUsernameProfile(){
    FILE *textfile = fopen("profiles/player.txt","w");
    char profileData[256];
    sprintf(profileData,"%s,0,250,main;",textbox[0].textContent); 
    fputs(profileData,textfile);
    fclose(textfile);
    CheckUsernameProfile();
    
    appendTransition(startMenu);
}

void FSaveProfile(){
    FILE* textfileN = fopen("profiles/playerN.txt","w");
    FILE* textfile = fopen("profiles/player.txt","r");
    char buffer[256];
    int type = 0;
    char tempBuffer[256];
    int tempBufferSize = 0;
    bool coinsAdded = false;
    bool levelsAdded = false;
    while(fgets(buffer,256,textfile)){
        for(int i = 0;i<255;i++){
            if(buffer[i] == '\n'){break;}
            if(type == 2 && !coinsAdded){
                char coins[256];
                sprintf(coins,",%d\0",profile.coins);
                SDL_memcpy(&(tempBuffer[tempBufferSize]),coins,len(coins));
                tempBufferSize+=len(coins);
                coinsAdded = true;
            }
            if(type == 3 && !levelsAdded){
                char levelsUnlocked[256];
                sprintf(levelsUnlocked,",%s\0",profile.currentLevel);
                SDL_memcpy(&(tempBuffer[tempBufferSize]),levelsUnlocked,len(levelsUnlocked));
                tempBufferSize+=len(levelsUnlocked);
                levelsAdded = true;
            }
            if(buffer[i] == ',' || buffer[i] == ';'){
             type++;
            }
            if(type == 2 || type == 3){
                continue;
            }
            SDL_memcpy(&tempBuffer[tempBufferSize],&buffer[i],1);
            tempBufferSize++;
            tempBuffer[tempBufferSize] = '\0';
        }
        fputs(tempBuffer,textfileN);
        tempBufferSize = 0;
    }
    fclose(textfile);
    fclose(textfileN);
    remove("profiles/player.txt");
    rename("profiles/playerN.txt","profiles/player.txt");



}
void ReadLevelCampaign(){
    FILE *textfile = fopen("profiles/player.txt","r");
    if (textfile != NULL){
        char buffer[256];
        fgets(buffer,256,textfile);
        int type = 0;
        char returnArray[20];
        int returnArraySize = 0;
        for (int i = 0;i<255;i++){
           if (buffer[i] == ','){
            type++;
            continue;
           }
           if (buffer[i] == ';'){
            break;
           }
           if (type == 3){
            SDL_memcpy(&returnArray[returnArraySize],&buffer[i],1);
            returnArraySize++;
           }
           
        }
    returnArray[returnArraySize] = '\0';
    fclose(textfile);
    sprintf(level.absolutePath,"%s.txt",returnArray);
    printf("%s\n",level.absolutePath);
    return;
   }  
}

bool CheckUsernameProfile(){
    FILE *textfile = fopen("profiles/player.txt","r");
    if(textfile == NULL){
      return false;
    }
    char buffer[256];
    fgets(buffer,256,textfile);
    char tempBuffer[256];
    int tempBufferSize = 0;
    int tempBufferType = 0;
    for(int i = 0;i<255;i++){
     
     if(buffer[i] == ',' || buffer[i] == ';'){
        if(tempBufferType == 0){
            SDL_memcpy(profile.username,tempBuffer,tempBufferSize);
            tempBufferSize = 0;
        }
        else if (tempBufferType == 1){
            profile.experience = atoi(tempBuffer);
        }
        else if (tempBufferType == 2){
            profile.coins = atoi(tempBuffer);
        }
        else if (tempBufferType == 3){
            printf("%s\n",tempBuffer);
            SDL_memcpy(profile.currentLevel,tempBuffer,4);
            printf("current level :%s\n",profile.currentLevel);
        }
        if(buffer[i] == ';'){
            break;
        }

        tempBufferType++;
        tempBufferSize = 0;
        continue;
     }
     SDL_memcpy(&tempBuffer[tempBufferSize],&buffer[i],1);
     tempBufferSize++;
     tempBuffer[tempBufferSize] = '\0';
    }
    
    fclose(textfile);
    return true;
}