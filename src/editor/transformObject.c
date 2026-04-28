
#define TRANSFORM_OBJECT(object,min,max) \
    if(editor.transform == 1){ \
         transformObject(&object[editor.indexSelected].x,&object[editor.indexSelected].y); \
      } \
      else if (editor.transform == 0){ \
         transformObject(&object[editor.indexSelected].width,&object[editor.indexSelected].height); \
      CLAMP_MINMAX(object[editor.indexSelected].width,min,max); \
      CLAMP_MINMAX(object[editor.indexSelected].height,min,max); \
      } \

void transformObject(double* x, double* y){
      editorMouseToObject_CalculateDistances(x,y);
      if(x != NULL){
       *x = (mouse.x-gameWidth/2)/camera.scale + gameWidth/2 - camera.x - editor.mouseToObjectDistances[0];
       *x = roundToNearestNumber(*x,editor.gridMove);  
       
      }
      if (y != NULL){
       *y = (mouse.y-gameHeight/2)/camera.scale + gameHeight/2 - camera.y - editor.mouseToObjectDistances[1];
       *y = roundToNearestNumber(*y,editor.gridMove);  
       
      }
}


void transform_player() {
  if(editor.transform == 1){
    transformObject(&player[0].x,&player[0].y);
  }
  else if (editor.transform == 0){
    transformObject(&player[0].width,NULL);
    CLAMP_MIN(player[0].width,5);
    player[0].height = player[0].width*10/9;
    player[0].Owidth = player[0].width;
  }
}

void FTransformState(){
  if(mouse.left == 1 && editor.selected && !((mouse.y <= 100 && mouse.x > 0 && mouse.x < gameWidthBase-200) || (mouse.x > gameWidthBase-200))){
    mouse.dX = mouse.x - mouse.oldX;
    mouse.dY = mouse.y - mouse.oldY;
    if(SDL_abs(mouse.dX) >= 5*app.deltaTime || SDL_abs(mouse.dY) >= 5*app.deltaTime){
      editor.unSelect = false;
    }
    else{
      return;
    }

    switch(editor.typeSelected) {
      case PLAYER:
          if(editor.transform == 2){
              editor.transform = 1;
              buttons[1].highlight = true;
              buttons[2].highlight = false;
              buttons[4].highlight = false;
          }
          transform_player();
          break;
      case PLATFORM:  TRANSFORM_OBJECT(platforms,   5, 1500); break;
      case TRIGGER:  TRANSFORM_OBJECT(triggers,    5, 1500); break;
      case LIGHT:  TRANSFORM_OBJECT(light,       5, 1500); break;
      case DISPLACEMENT:  TRANSFORM_OBJECT(displacement,5, 1500); break;
      case DEATHBOX:  TRANSFORM_OBJECT(deathbox,    5, 1500); break;
      case MOVENODE:
          transformObject(
              &movenodes[editor.indexSelected].positions[editor.movenodeSelected][0],
              &movenodes[editor.indexSelected].positions[editor.movenodeSelected][1]
          );
          break;
      case SCRIPT:  TRANSFORM_OBJECT(scripts,    5, 1500); break;
      case ENEMY:  TRANSFORM_OBJECT(enemy,      5, 1500); break;
      case SPECIAL:  TRANSFORM_OBJECT(specials,   5, 1500); break;
      case TEXTPOPUP: TRANSFORM_OBJECT(textpopups, 5, 1500); break;
    }
  }

}