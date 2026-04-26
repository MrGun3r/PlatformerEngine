void update_platformButtons() {
    SDL_memcpy(buttons[7].value,textures[platforms[editor.indexSelected].textureInt].textureName,len(textures[platforms[editor.indexSelected].textureInt].textureName)+1);
    SDL_itoa((int)platforms[editor.indexSelected].slopeInv,buttons[8].value,10);
    SDL_itoa((int)platforms[editor.indexSelected].textureStretch,buttons[17].value,10);
    SDL_itoa((int)platforms[editor.indexSelected].collidable,buttons[24].value,10);
    SDL_itoa((int)platforms[editor.indexSelected].textureRotation,buttons[38].value,10);
    SDL_itoa((int)!platforms[editor.indexSelected].NofinishAnimation,buttons[39].value,10);
    SDL_itoa((int)platforms[editor.indexSelected].grapplable,buttons[40].value,10);
}

void update_triggerButtons() {
    char* typeValue = malloc(100);
    if(triggers[editor.indexSelected].triggerType == 0){
        sprintf(typeValue,"Platform\0");
    }
    else if(triggers[editor.indexSelected].triggerType == 1){
        sprintf(typeValue,"DeathBox\0");
    }
    else if(triggers[editor.indexSelected].triggerType == 2){
        sprintf(typeValue,"Light\0");
    }
    else if(triggers[editor.indexSelected].triggerType == 3){
        sprintf(typeValue,"Displacement\0");
    }
    SDL_memcpy(buttons[29].value,typeValue,len(typeValue)+1);
}

void update_lightButtons() {
    int NameSize = len(lightTextures[light[editor.indexSelected].lightInt].textureName);
    SDL_memcpy(buttons[32].value,lightTextures[light[editor.indexSelected].lightInt].textureName,NameSize+1);
}

void update_scriptButtons() {
    if(scripts[editor.indexSelected].scriptInt >= 1){
        int NameSize = len(scriptfiles[scripts[editor.indexSelected].scriptInt].scriptName);
        SDL_memcpy(buttons[31].value,scriptfiles[scripts[editor.indexSelected].scriptInt].scriptName,NameSize+1);
    }
    else{
        SDL_memcpy(buttons[31].value,"None",5);
    }
}

void update_specialButtons() {
    char* specialType = malloc(100*sizeof(char));
    specialType = specialTypes_Array[specials[editor.indexSelected].type-1];
    sprintf(buttons[35].value,specialType,len(specialType));

}

void update_settingsButtons() {
    SDL_memcpy(buttons[18].value,backgrounds[app.backgroundInt].textureName,len(backgrounds[app.backgroundInt].textureName)+1);
}