
void SetUsernameProfile(){
    FILE *textfile = fopen("profiles/player.txt","w");
    char profileData[256];
    sprintf(profileData,"%s,0,250;",textbox[0].textContent); 
    fputs(profileData,textfile);
    fclose(textfile);
    CheckUsernameProfile();
    
    appendTransition(app.status,4);
}


bool CheckUsernameProfile(){
    FILE *textfile = fopen("profiles/player.txt","r");
    if(textfile == NULL){
      fclose(textfile);
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
        tempBufferType++;
        tempBufferSize = 0;
        if(tempBuffer[tempBufferSize] == ';'){
            break;
        }
        continue;
     }
     SDL_memcpy(&tempBuffer[tempBufferSize],&buffer[i],1);
     tempBufferSize++;
     tempBuffer[tempBufferSize] = '\0';
    }
    
    fclose(textfile);
    return true;
}