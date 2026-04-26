/// MACROS
#define UPDATE_SELECTION_TIME(obj) \
      for(int i = 0;i<sizeof(obj)/sizeof(obj[0]);i++){ \
         if(obj[i].reserved && obj[i].editorSelectionTime <= 1000){ \
            obj[i].editorSelectionTime += 1000*app.deltaTime; \
         } \
      } \

#define SET_TO_NODE(obj) \
      for(int i = 0;i<sizeof(obj)/sizeof(obj[0]);i++){ \
         if(obj[i].moveNodeInt >= 0 && movenodes[obj[i].moveNodeInt].reserved){ \
            obj[i].x = movenodes[obj[i].moveNodeInt].positions[0][0]-(obj[i].width-25)/2; \
            obj[i].y = movenodes[obj[i].moveNodeInt].positions[0][1]-(obj[i].height-25)/2; \
         } \
      } \

#define UPDATE_CHECK_SELECT(obj,type, update_ui_func) \
      for(int i = 0;i<sizeof(obj)/sizeof(obj[0]);i++){ \
         if(obj[i].reserved && obj[i].editorSelectionTime >= 999){ \
            printf("object %d of coords %f %f\n",i,obj[i].xDraw,obj[i].yDraw); \
            int xMin = obj[i].xDraw; \
            int xMax = obj[i].xDraw+obj[i].widthDraw; \
            int yMin = obj[i].yDraw; \
            int yMax = obj[i].yDraw+obj[i].heightDraw; \
         if(mouse.x >= xMin && mouse.x <= xMax && mouse.y >= yMin && mouse.y <= yMax){ \
            obj[i].editorSelectionTime = 0; \
            editor.selected = true; \
            editor.typeSelected = type; \
            editor.indexSelected = i; \
            update_ui_func; \
            return; \
          } \
        } \
      } \

#define UPDATE_CHECK_SELECT_PLAYER \
   if(player[0].editorSelectionTime >= 999){ \
      int xMin = player[0].xDraw; \
      int xMax = player[0].xDraw+player[0].widthDraw; \
      int yMin = player[0].yDraw; \
      int yMax = player[0].yDraw+player[0].heightDraw; \
      if(mouse.x >= xMin && mouse.x <= xMax && mouse.y >= yMin && mouse.y <= yMax){ \
         player[0].editorSelectionTime = 0; \
         editor.selected = true; \
         editor.typeSelected = PLAYER; \
         editor.indexSelected = 0; \
         return; \
      } \
   } \

#define UPDATE_CHECK_SELECT_MOVENODES \
   for(int i = 0;i<sizeof(movenodes)/sizeof(movenodes[0]);i++){ \
         if(movenodes[i].reserved && movenodes[i].editorSelectionTime >= 999){ \
            for(int j = 0;j<movenodes[i].nodesCount;j++){ \
               int xMin = movenodes[i].positionsDraw[j][0]; \
               int xMax = movenodes[i].positionsDraw[j][0]+25*camera.scale; \
               int yMin = movenodes[i].positionsDraw[j][1]; \
               int yMax = movenodes[i].positionsDraw[j][1]+25*camera.scale; \
            if(mouse.x >= xMin && mouse.x <= xMax && mouse.y >= yMin && mouse.y <= yMax){ \
               movenodes[i].editorSelectionTime = 0; \
               editor.selected = true; \
               editor.typeSelected = MOVENODE; \
               editor.indexSelected = i; \
               Select_Movenode_UI_Update(j); \
                \
               return; \
               } \
            } \
         } \
      } \

void Update_Selection_Time_Player() {
   if(player[0].editorSelectionTime <= 1000){
      player[0].editorSelectionTime += 1000*app.deltaTime;
   }
}

#include "editor_select_update.c"
#include "editor_object_update.c"
#include "editor_buttons.c"
#include "editor_buttons_update.c"

void (*editor_buttons[])(void) = {
    createNewPlatform_button,       // 0
    enableTranslateObjects_button,  // 1
    enableResizeObjects_button,     // 2
    saveMap_button,                 // 3
    saveMapAs_button,               // 4
    deleteObject_button,            // 5
    loadMap_button,                 // 6
    changePlatformTexture_button,   // 7
    toggleSlopeInv_button,          // 8
    copyObject_button,              // 9
    NULL,                           // 10 (nothing)
    openMapSettings_button,         // 11
    addTrigger_button,              // 12
    addFinishLine_button,           // 13
    addCheckpoint_button,           // 14
    zoomIn_button,                  // 15
    zoomOut_button,                 // 16
    toggleTextureStretch_button,    // 17
    changeBackground_button,        // 18
    addLight_button,                // 19
    addDisplacement_button,         // 20
    cycleDisplacementDirection_button, // 21
    cycleDisplacementType_button,   // 22
    addDeathBox_button,             // 23
    toggleCollidable_button,        // 24
    addMoveNode_button,             // 25
    addNode_button,                 // 26
    removeNode_button,              // 27
    toggleWrapNodes_button,         // 28
    cycleTriggerType_button,        // 29
    addScript_button,               // 30
    changeScriptName_button,        // 31
    changeLightTexture_button,      // 32
    addEnemy_button,                // 33
    addSpecial_button,              // 34
    cycleSpecialType_button,        // 35
    addTextPopUp_button,            // 36
    setPopUpText_button,            // 37
    cycleTextureRotation_button,    // 38
    toggleFinishAnimation_button,   // 39
    toggleGrapplable_button,        // 40
};

void FCheck_Select_Editor(){
   
   if(editor.unSelect){
      // If mouse is outside of editor canvas , do nothing
      if ((mouse.y <= 100 && mouse.x > 0 && mouse.x < gameWidthBase-200) || (mouse.x > gameWidthBase-200)) { return;}
      
      UPDATE_CHECK_SELECT_PLAYER
      UPDATE_CHECK_SELECT(platforms,PLATFORM,Select_Platform_UI_Update())
      UPDATE_CHECK_SELECT(triggers,TRIGGER,Select_Trigger_UI_Update())
      UPDATE_CHECK_SELECT(displacement,DISPLACEMENT,Select_Displacement_UI_Update())
      UPDATE_CHECK_SELECT(deathbox,DEATHBOX,Select_Deathbox_UI_Update())
      UPDATE_CHECK_SELECT(light,LIGHT,Select_Light_UI_Update())
      UPDATE_CHECK_SELECT_MOVENODES
      UPDATE_CHECK_SELECT(scripts,SCRIPT,Select_Scripts_UI_Update())
      UPDATE_CHECK_SELECT(enemy,ENEMY,Select_Enemy_UI_Update(i))
      UPDATE_CHECK_SELECT(specials,SPECIAL, )
      UPDATE_CHECK_SELECT(textpopups,TEXTPOPUP,Select_Textpopup_UI_Update())
      
      // If we reach here , it means no object was selected
      editor.selected = false;
   }
   
   editor.unSelect = true;
   return;
}
void Update_Objects() {
   switch (editor.typeSelected)
   {
    case NONE: setValuesMapSettings();  break;
    case PLATFORM:  setValuesPlatforms();    break;
    case TRIGGER:  setValuesTriggers();     break;
    case LIGHT:  setValuesLight();        break;
    case DISPLACEMENT:  setValuesDisplacement(); break;
    case DEATHBOX:  setValuesDeathBox();     break;
    case SCRIPT:  setValuesScript();       break;
    case ENEMY:  setValuesEnemy();        break;
    case TEXTPOPUP: setValuesTextPopup();    break;
   }
}
void Update_Camera() {
   camera.scale += (camera.scaleReal - camera.scale)*app.deltaTime*5;
   
   if(mouse.wheel == 1){
      camera.scaleReal *= 1.2;
      camera.scaleReal = min(4,camera.scaleReal);
   }
   else if (mouse.wheel == -1){
      camera.scaleReal /= 1.2;
      camera.scaleReal = max(0.5,camera.scaleReal);
   }

   if(mouse.right){
    mouse.dX = mouse.x - mouse.oldX;
    mouse.dY = mouse.y - mouse.oldY;
    camera.x += mouse.dX;
    camera.y += mouse.dY;
   }
   if(mouse.left == -1){
     editor.mouseToObjectDistanceBool = false;
   }
}
void Update_Platform_Animation() {

   for(int i = 0;i<sizeof(platforms)/sizeof(platforms[0]);i++){
         if(platforms[i].reserved){
            if(platforms[i].textureAnimationTime >= 1){
               platforms[i].textureAnimationTimer += 1000*app.deltaTime;
            if(platforms[i].textureAnimationTimer > platforms[i].textureAnimationTime){
               platforms[i].textureAnimationInt++;
               platforms[i].textureAnimationInt = (int)platforms[i].textureAnimationInt % ((int)textures[platforms[i].textureInt].textureAnimationSize);
               platforms[i].textureAnimationTimer = 0;
            }
            }
            else {
               platforms[i].textureAnimationInt = 0;
               platforms[i].textureAnimationTimer = 0;
            }
         }
   }
}
void Update_Buttons() {
   for(int i = 0;i<sizeof(buttons)/sizeof(buttons[0]);i++){
      if(buttons[i].reserved){
         int yMin = (buttons[i].y);
         int yMax = (buttons[i].y+buttons[i].hoverHeight);
         int xMin = (buttons[i].x);
         int xMax = (buttons[i].x+buttons[i].hoverWidth);      
         if(mouse.x >= xMin && mouse.x <= xMax && mouse.y >= yMin && mouse.y <= yMax && (mouse.left == -1 || mouse.right == -1)){
            
            // If we press on a button , call the function that corresponds to it
            editor_buttons[i]();
         }
      }
   }
}
void Set_ButtonValues(){
   switch(editor.typeSelected) {
      case NONE:
         update_settingsButtons(); break;
      case PLATFORM:
         update_platformButtons(); break;
      case TRIGGER:
         update_triggerButtons(); break;
      case LIGHT:
         update_lightButtons(); break;
      case SCRIPT:
         update_scriptButtons(); break;
      case SPECIAL:
         update_specialButtons(); break;
   }
}
void Update_UI_Values() {
   /// This function restricts UI value updates to only when mouse is clicked
   
   if(mouse.left == -1){      
      if(editor.status < 0){
         FCheck_Select_Editor(); 
      }
      Set_ButtonValues();
      Set_KnobValues();
      Set_SlidersValues();
      editorShowButtons();     
   }
}


void FUpdate_Editor(){
      // Calculate mouse coordinates in the projected world
      editor.mouseProjected[0] = (mouse.x-gameWidth/2)/camera.scale + gameWidth/2 - camera.x;
      editor.mouseProjected[1] = (mouse.y-gameHeight/2)/camera.scale + gameHeight/2 - camera.y;
      // Update Alerts
      if(editor.alertTimer > 0){
         editor.alertTimer -= 1000*app.deltaTime;
      }

      if(editor.status < 0){
         FTransformState();
      }

      // Update Selection Timer for each object
      Update_Selection_Time_Player();
      UPDATE_SELECTION_TIME(platforms)
      UPDATE_SELECTION_TIME(deathbox)
      UPDATE_SELECTION_TIME(light)
      UPDATE_SELECTION_TIME(triggers)
      UPDATE_SELECTION_TIME(displacement)
      UPDATE_SELECTION_TIME(movenodes)
      UPDATE_SELECTION_TIME(scripts)
      UPDATE_SELECTION_TIME(enemy)
      UPDATE_SELECTION_TIME(specials)
      UPDATE_SELECTION_TIME(textpopups)

      // Set objects to node positions if moveNodeInt is positive 
      SET_TO_NODE(deathbox)
      SET_TO_NODE(light)
      SET_TO_NODE(displacement)
      SET_TO_NODE(platforms)

      // Update Camera (Makes it smoother)
      Update_Camera();
      // Change texture platform (Animate)
      Update_Platform_Animation();      

      /// Update objects according to UI values (sliders and knobs and text boxes)
      /// Object values <= UI values 
      Update_Objects();

      // This applies the visual UI values to their real values
      // UI (Data) Values <= UI (visual) values
      // These visuals are coming from user input
      Update_UI_Values();

      /// Update the sliders and knobs interaction with user input
      /// UI values <= User input 
      Update_Buttons();
      Update_Slider();
      Update_Knobs();
      Update_TextBox();  
}