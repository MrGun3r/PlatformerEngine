

void Select_Platform_UI_Update() {
   sliders[0].sliderValue = platforms[editor.indexSelected].slope*(180/(2*PI));
   sliders[1].sliderValue = platforms[editor.indexSelected].textureOffsetX;
   sliders[2].sliderValue = platforms[editor.indexSelected].textureOffsetY;
   knobs[0].knobValue = platforms[editor.indexSelected].textureScale;
   knobs[8].knobValue = platforms[editor.indexSelected].moveNodeInt;
   knobs[9].knobValue = platforms[editor.indexSelected].moveSpeed;
   sliders[14].sliderValue = platforms[editor.indexSelected].opacity;
   knobs[5].knobValue = platforms[editor.indexSelected].textureAnimationTime;
   sliders[10].sliderValue = platforms[editor.indexSelected].red;
   sliders[11].sliderValue = platforms[editor.indexSelected].green;
   sliders[12].sliderValue = platforms[editor.indexSelected].blue;
   knobs[16].knobValue = platforms[editor.indexSelected].textureOffsetX_Move;
   knobs[17].knobValue = platforms[editor.indexSelected].textureOffsetY_Move;
}

void Select_Trigger_UI_Update() {
   sliders[14].sliderValue = triggers[editor.indexSelected].opacity;
   knobs[8].knobValue = triggers[editor.indexSelected].Value1;
   knobs[9].knobValue = triggers[editor.indexSelected].Value2;
   knobs[10].knobValue = triggers[editor.indexSelected].Value3;
   knobs[11].knobValue = triggers[editor.indexSelected].useDelay;
   knobs[12].knobValue = triggers[editor.indexSelected].reuseDelay;
}

void Select_Displacement_UI_Update() {
   sliders[13].sliderValue = displacement[editor.indexSelected].power;  
   sliders[14].sliderValue = displacement[editor.indexSelected].opacity;  
   knobs[8].knobValue = displacement[editor.indexSelected].moveNodeInt;   
   knobs[9].knobValue = displacement[editor.indexSelected].moveSpeed;
}

void Select_Deathbox_UI_Update() {
   sliders[14].sliderValue = deathbox[editor.indexSelected].opacity;
   knobs[8].knobValue = deathbox[editor.indexSelected].moveNodeInt;
   knobs[9].knobValue = deathbox[editor.indexSelected].moveSpeed;
}

void Select_Light_UI_Update() {
   sliders[7].sliderValue = light[editor.indexSelected].rotation;
   sliders[8].sliderValue = light[editor.indexSelected].brightness;
   sliders[9].sliderValue = light[editor.indexSelected].visibility;
   sliders[10].sliderValue = light[editor.indexSelected].red;
   sliders[11].sliderValue = light[editor.indexSelected].green;
   sliders[12].sliderValue = light[editor.indexSelected].blue;
   knobs[8].knobValue = light[editor.indexSelected].moveNodeInt;
   knobs[9].knobValue = light[editor.indexSelected].moveSpeed;
}

void Select_Movenode_UI_Update(int j) {
   editor.movenodeSelected = j;
}

void Select_Scripts_UI_Update() {
   knobs[11].knobValue = scripts[editor.indexSelected].useDelay;
   knobs[12].knobValue = scripts[editor.indexSelected].reuseDelay;
}

void Select_Enemy_UI_Update(int i) {
   sliders[16].sliderValue = enemy[i].maxSpeed;
   sliders[17].sliderValue = enemy[i].maxHealth;
   knobs[18].knobValue = enemy[i].type;
}

void Select_Textpopup_UI_Update() {
   knobs[13].knobValue = textpopups[editor.indexSelected].xPopup;
   knobs[14].knobValue = textpopups[editor.indexSelected].yPopup;
   knobs[15].knobValue = textpopups[editor.indexSelected].font;
}