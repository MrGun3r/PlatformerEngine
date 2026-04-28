void setValuesPlatforms() {
    int index = editor.indexSelected;
    platforms[index].textureOffsetX      = sliders[1].sliderValue;
    platforms[index].textureOffsetY      = sliders[2].sliderValue;
    platforms[index].textureScale        = knobs[0].knobValue;
    platforms[index].moveNodeInt         = knobs[8].knobValue;
    platforms[index].moveSpeed           = knobs[9].knobValue;
    platforms[index].textureOffsetX_Move = knobs[16].knobValue;
    platforms[index].textureOffsetY_Move = knobs[17].knobValue;
    platforms[index].opacity             = sliders[14].sliderValue;
    platforms[index].textureAnimationTime= knobs[5].knobValue;
    if(platforms[index].type == 0){
        platforms[index].slope = sliders[0].sliderValue/(180/(2*PI)); 
        platforms[index].red   = sliders[10].sliderValue;
        platforms[index].green = sliders[11].sliderValue;
        platforms[index].blue  = sliders[12].sliderValue;
    } else {
        platforms[index].red   = 255;
        platforms[index].green = 255;
        platforms[index].blue  = 255;
    }
}

void setValuesMapSettings() {
    mapData.xMin        = -knobs[3].knobValue;
    mapData.xMax        =  knobs[3].knobValue;
    mapData.yMin        = -knobs[4].knobValue;
    mapData.yMax        =  knobs[4].knobValue;
    editor.StarTime     =  knobs[7].knobValue;
    editor.StarTimeMs   =  knobs[6].knobValue;
    editor.gridMove     =  knobs[19].knobValue;
    app.backgroundOpacity = sliders[6].sliderValue;
    editor.GameScale    =  sliders[15].sliderValue / 100;
}

void setValuesTriggers() {
    int index = editor.indexSelected;
    triggers[index].opacity    = sliders[14].sliderValue;
    triggers[index].Value1     = knobs[8].knobValue;
    triggers[index].Value2     = knobs[9].knobValue;
    triggers[index].Value3     = knobs[10].knobValue;
    triggers[index].useDelay   = knobs[11].knobValue;
    triggers[index].reuseDelay = knobs[12].knobValue;
}

void setValuesLight() {
    int index = editor.indexSelected;
    light[index].rotation    = sliders[7].sliderValue;
    light[index].brightness  = sliders[8].sliderValue;
    light[index].visibility  = sliders[9].sliderValue;
    light[index].moveNodeInt = knobs[8].knobValue;
    light[index].moveSpeed   = knobs[9].knobValue;
    light[index].red         = sliders[10].sliderValue;
    light[index].green       = sliders[11].sliderValue;
    light[index].blue        = sliders[12].sliderValue;
}

void setValuesDisplacement() {
    int index = editor.indexSelected;
    displacement[index].power      = sliders[13].sliderValue;
    displacement[index].opacity    = sliders[14].sliderValue;
    displacement[index].moveNodeInt= knobs[8].knobValue;
    displacement[index].moveSpeed  = knobs[9].knobValue;
}

void setValuesDeathBox() {
    int index = editor.indexSelected;
    deathbox[index].opacity    = sliders[14].sliderValue;
    deathbox[index].moveNodeInt= knobs[8].knobValue;
    deathbox[index].moveSpeed  = knobs[9].knobValue;
}

void setValuesScript() {
    int index = editor.indexSelected;
    scripts[index].useDelay   = knobs[11].knobValue;
    scripts[index].reuseDelay = knobs[12].knobValue;
}

void setValuesEnemy() {
    int index = editor.indexSelected;
    enemy[index].maxSpeed  = sliders[16].sliderValue;
    enemy[index].maxHealth = sliders[17].sliderValue;
    enemy[index].type      = knobs[18].knobValue;
}

void setValuesTextPopup() {
    int index = editor.indexSelected;
    textpopups[index].xPopup = knobs[13].knobValue;
    textpopups[index].yPopup = knobs[14].knobValue;
    textpopups[index].font   = knobs[15].knobValue;
}