#ifndef EDITOR_BUTTONS
#define EDITOR_BUTTONS
/// This should define button functions ( Action listeners )

void createNewPlatform_button() {
    addPlatform(gameWidth/2-camera.x,gameHeight/2-camera.y,25,25,0,false,FindTextureInt("stone"),0,knobs[0].knobValue,0,0,false,true,255,0,255,255,255);
}

void enableTranslateObjects_button() {
    editor.transform = 1;
    buttons[1].highlight = true;
    buttons[2].highlight = false; 
}
  
void enableResizeObjects_button() {
    editor.transform = 0;
    buttons[1].highlight = false;
    buttons[2].highlight = true;
}

void saveMap_button() {
    if(editor.mapNameSet){
        FSaveMap(editor.mapName);
    }
    else{
        sprintf(editor.alertText,"No map name is loaded");
        editor.alertTimer = 5000;
    }
}
 
void saveMapAs_button() {
    SetTextBox(false,0,"Map Name:",45,150,15,450);
    textbox[0].textContentSize = 0;
    textbox[0].textContent[0] = '\0';
    editor.status = 0;
    editorShowButtons();
}

void deleteObject_button() {
    switch(editor.typeSelected) {
        case PLATFORM:  platforms[editor.indexSelected].reserved   = false; break;
        case TRIGGER:  triggers[editor.indexSelected].reserved    = false; break;
        case LIGHT:  light[editor.indexSelected].reserved       = false; break;
        case DISPLACEMENT:  displacement[editor.indexSelected].reserved= false; break;
        case DEATHBOX:  deathbox[editor.indexSelected].reserved    = false; break;
        case MOVENODE:  movenodes[editor.indexSelected].reserved   = false; break;
        case SCRIPT:  scripts[editor.indexSelected].reserved     = false; break;
        case ENEMY:  enemy[editor.indexSelected].reserved       = false; break;
        case SPECIAL:  specials[editor.indexSelected].reserved    = false; break;
        case TEXTPOPUP: textpopups[editor.indexSelected].reserved  = false; break;
    }
    editor.selected = false;
    editorShowButtons();
}

void changePlatformTexture_button() {
    if (mouse.left == -1){
        platforms[editor.indexSelected].textureInt++;
    }
    else{
        platforms[editor.indexSelected].textureInt--;
    }
         
    if(!textures[platforms[editor.indexSelected].textureInt].reserved){
        platforms[editor.indexSelected].textureInt = 0;
    }
}

void toggleSlopeInv_button() {
    platforms[editor.indexSelected].slopeInv = !platforms[editor.indexSelected].slopeInv;
}

void loadMap_button() {
    SetTextBox(false, 0, "Map Name:", 45, 150, 15, 450);
    textbox[0].textContentSize = 0;
    textbox[0].textContent[0] = '\0';
    editor.status = 1;
    editorShowButtons();
}

void copyObject_button() {
    double cx = gameWidth/2 - camera.x;
    double cy = gameHeight/2 - camera.y;
    int idx = editor.indexSelected;
    switch(editor.typeSelected) {
        case PLATFORM:
            addPlatform(cx, cy,
                platforms[idx].width, platforms[idx].height,
                platforms[idx].slope, platforms[idx].slopeInv,
                platforms[idx].textureInt, platforms[idx].type,
                platforms[idx].textureScale,
                platforms[idx].textureOffsetX, platforms[idx].textureOffsetY,
                platforms[idx].textureStretch, platforms[idx].collidable,
                platforms[idx].opacity, platforms[idx].textureAnimationTime,
                platforms[idx].red, platforms[idx].green, platforms[idx].blue);
            break;
        case TRIGGER:
            addTrigger(cx, cy,
                triggers[idx].width, triggers[idx].height,
                triggers[idx].triggerType, triggers[idx].opacity,
                triggers[idx].Value1, triggers[idx].Value2,
                triggers[idx].Value3, triggers[idx].Value4);
            break;
        case LIGHT:
            addLight(cx, cy,
                light[idx].width, light[idx].height,
                light[idx].red, light[idx].green, light[idx].blue,
                light[idx].visibility, light[idx].brightness,
                light[idx].moveSpeed, light[idx].lightInt);
            break;
        case DISPLACEMENT:
            addDisplacement(cx, cy,
                displacement[idx].width, displacement[idx].height,
                displacement[idx].type, displacement[idx].power,
                displacement[idx].powerType, displacement[idx].opacity);
            break;
        case DEATHBOX:
            addDeathBox(cx, cy,
                deathbox[idx].width, deathbox[idx].height,
                deathbox[idx].opacity);
            break;
        case SCRIPT:
            addScript(cx, cy, scripts[idx].width, scripts[idx].height);
            break;
        case ENEMY:
            addEnemy(cx, cy, enemy[idx].width, enemy[idx].height);
            break;
        case SPECIAL:
            addSpecial(cx, cy, specials[idx].width, specials[idx].height, specials[idx].type);
            break;
        case TEXTPOPUP:
            addTextPopUp(cx, cy, textpopups[idx].width, textpopups[idx].height);
            break;
    }
}

void openMapSettings_button() {
    editor.typeSelected = NONE;
    editor.selected = true;
    sliders[6].sliderValue  = app.backgroundOpacity;
    sliders[15].sliderValue = editor.GameScale * 100;
    knobs[3].knobValue      = mapData.xMax;
    knobs[4].knobValue      = mapData.yMax;
    editorShowButtons();
}

void addTrigger_button() {
    addTrigger(gameWidth/2-camera.x, gameHeight/2-camera.y, 25, 25, 0, 255, -1, 0, 0, 0);
}

void addFinishLine_button() {
    addPlatform(gameWidth/2-camera.x, gameHeight/2-camera.y, 25, 25, 0, false, -1, 1, 50, 0, 0, false, true, 255, 0, 255, 255, 255);
}

void addCheckpoint_button() {
    addPlatform(gameWidth/2-camera.x, gameHeight/2-camera.y, 25, 25, 0, false, -1, 2, 50, 0, 0, false, true, 255, 0, 255, 255, 255);
}

void zoomIn_button() {
    camera.scaleReal *= 1.2;
    camera.scaleReal = min(4, camera.scaleReal);
}

void zoomOut_button() {
    camera.scaleReal /= 1.2;
    camera.scaleReal = max(0.5, camera.scaleReal);
}

void toggleTextureStretch_button() {
    platforms[editor.indexSelected].textureStretch = !platforms[editor.indexSelected].textureStretch;
}

void changeBackground_button() {
    app.backgroundInt++;
    if(!backgrounds[app.backgroundInt].reserved) {
        app.backgroundInt = 0;
    }
}

void addLight_button() {
    addLight(gameWidth/2-camera.x, gameHeight/2-camera.y, 25.0f, 25.0f, 255, 255, 255, 255, 100, 0, 0);
}

void addDisplacement_button() {
    addDisplacement(gameWidth/2-camera.x, gameHeight/2-camera.y, 25.0f, 25.0f, 0, 50, 0, 255);
}

void cycleDisplacementDirection_button() {
    displacement[editor.indexSelected].type++;
    displacement[editor.indexSelected].type %= 4;
}

void cycleDisplacementType_button() {
    displacement[editor.indexSelected].powerType++;
    displacement[editor.indexSelected].powerType %= 2;
}

void addDeathBox_button() {
    addDeathBox(gameWidth/2-camera.x, gameHeight/2-camera.y, 25.0f, 25.0f, 255);
}

void toggleCollidable_button() {
    platforms[editor.indexSelected].collidable = !platforms[editor.indexSelected].collidable;
}

void addMoveNode_button() {
    addMoveNode(gameWidth/2-camera.x, gameHeight/2-camera.y);
}

void addNode_button() {
    if(movenodes[editor.indexSelected].nodesCount < 20) {
        movenodes[editor.indexSelected].nodesCount++;
        int last = movenodes[editor.indexSelected].nodesCount - 1;
        movenodes[editor.indexSelected].positions[last][0] = gameWidth/2 - camera.x;
        movenodes[editor.indexSelected].positions[last][1] = gameHeight/2 - camera.y;
        editor.movenodeSelected = last;
    }
}

void removeNode_button() {
    if(movenodes[editor.indexSelected].nodesCount > 1) {
        movenodes[editor.indexSelected].nodesCount--;
        editor.movenodeSelected = movenodes[editor.indexSelected].nodesCount - 1;
    }
}

void toggleWrapNodes_button() {
    movenodes[editor.indexSelected].wrap = !movenodes[editor.indexSelected].wrap;
}

void cycleTriggerType_button() {
    triggers[editor.indexSelected].triggerType++;
    triggers[editor.indexSelected].triggerType %= 4;
}

void addScript_button() {
    addScript(gameWidth/2-camera.x, gameHeight/2-camera.y, 25.0f, 25.0f);
}

void changeScriptName_button() {
    int idx = editor.indexSelected;
    if(mouse.right == -1) {
        if(scripts[idx].scriptInt > 0)
            scripts[idx].scriptInt--;
    } else {
        scripts[idx].scriptInt++;
        if(scripts[idx].scriptInt < 50 && !scriptfiles[scripts[idx].scriptInt].reserved)
            scripts[idx].scriptInt = 0;
    }
}

void changeLightTexture_button() {
    int idx = editor.indexSelected;
    if(mouse.left == -1) {
        light[idx].lightInt++;
        if(light[idx].lightInt > 50 || !lightTextures[light[idx].lightInt].reserved)
            light[idx].lightInt = 0;
    } else if(mouse.right == -1) {
        if(light[idx].lightInt > 0)
            light[idx].lightInt--;
    }
}

void addEnemy_button() {
    addEnemy(gameWidth/2-camera.x, gameHeight/2-camera.y, 20, 20);
}

void addSpecial_button() {
    addSpecial(gameWidth/2-camera.x, gameHeight/2-camera.y, 18, 18, 1);
}

void cycleSpecialType_button() {
    int idx = editor.indexSelected;
    if(mouse.left == -1) {
        specials[idx].type++;
        if(specials[idx].type > 7) specials[idx].type = 1;
    } else if(mouse.right == -1) {
        if(specials[idx].type > 1) specials[idx].type--;
    }
}

void addTextPopUp_button() {
    addTextPopUp(gameWidth/2-camera.x, gameHeight/2-camera.y, 25, 25);
}

void setPopUpText_button() {
    SetTextBox(false, 0, "Text:", 45, 150, 15, 450);
    int textLength = 0;
    if(textpopups[editor.indexSelected].textContent != NULL) {
        textLength = len(textpopups[editor.indexSelected].textContent);
    }
    if(textLength > 0){
        SDL_memcpy(textbox[0].textContent, textpopups[editor.indexSelected].textContent, textLength);
    }
    textbox[0].textContentSize = textLength;
    textbox[0].textContent[textLength] = '\0';
    editor.status = 2;
    editorShowButtons();
}

void cycleTextureRotation_button() {
    if(mouse.left == -1) {
        platforms[editor.indexSelected].textureRotation++;
        platforms[editor.indexSelected].textureRotation %= 4;
    }
}

void toggleFinishAnimation_button() {
    platforms[editor.indexSelected].NofinishAnimation = !platforms[editor.indexSelected].NofinishAnimation;
}

void toggleGrapplable_button() {
    platforms[editor.indexSelected].grapplable = !platforms[editor.indexSelected].grapplable;
}


#endif