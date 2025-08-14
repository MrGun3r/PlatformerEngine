void addEnemy(int x,int y,int width,int height){
   for(int i = 0;i<sizeof(enemy)/sizeof(enemy[0]);i++){
      if(!enemy[i].reserved){
         editor.selected = true;
         editor.indexSelected = i;
         editor.typeSelected = 8;
         enemy[i].reserved = true;
         enemy[i].x = x;
         enemy[i].y = y;
         enemy[i].width = width;
         enemy[i].height = height;
           
         editorShowButtons();
         break;
      }
   }
}


void addTrigger(int x,int y,double width,double height,int Type,double opacity,double Value1,double Value2,double Value3,double Value4){
   for(int i = 1;i<sizeof(triggers)/sizeof(triggers[0]);i++){
      if(!triggers[i].reserved){
        editor.selected = true;
        editor.typeSelected = 2;
        editor.indexSelected = i;
        triggers[i].reserved = true;
        triggers[i].x = x;
        triggers[i].y = y;
        triggers[i].width = width;
        triggers[i].height = height;
        triggers[i].opacity = opacity;
        triggers[i].triggerType = Type;
        triggers[i].Value1 = Value1;
        triggers[i].Value2 = Value2;
        triggers[i].Value3 = Value3;
        triggers[i].Value4 = Value4;

         
         knobs[8].knobValue = -1;
         knobs[9].knobValue = 0;
           
        break;
      }
   }
   editorShowButtons();
}

void addDisplacement(double x, double y, double width,double height,double type,double power,double powerType,double opacity){
   for(int i = 0;i < sizeof(displacement)/sizeof(displacement[0]);i++){
      if(!displacement[i].reserved){
         editor.selected = true;
         editor.typeSelected = 4;
         editor.indexSelected = i;

         displacement[i].reserved = true;
         displacement[i].x = x;
         displacement[i].y = y;
         displacement[i].width = width;
         displacement[i].height = height;
         displacement[i].type = type;
         displacement[i].powerType = powerType;
         displacement[i].power = power;
         displacement[i].opacity = opacity;

         displacement[i].moveSpeed = 0;
         displacement[i].moveNodeInt = -1;
         
         knobs[8].knobValue = -1;
         knobs[9].knobValue = 0;

         sliders[14].sliderValue = 255;
           
         break;
      }
   }
   editorShowButtons();
}

void addLight(double x,double y,double width,double height,double red,double green,double blue,double visibility,double brightness,double moveSpeed,int lightInt){
   for(int i = 1;i<sizeof(light)/sizeof(light[0]);i++){
      if(!light[i].reserved){
         editor.selected = true;
         editor.typeSelected = 3;
         editor.indexSelected = i;
         light[i].reserved = true;
         light[i].x = x;
         light[i].y = y;
         light[i].width = width;
         light[i].height = height;
         light[i].red =   red;
         light[i].green = green;
         light[i].blue =  blue;
         light[i].visibility = visibility;
         light[i].brightness = brightness;
          
         light[i].moveSpeed = moveSpeed;
         light[i].moveNodeInt = -1;
         light[i].lightInt = lightInt;
         
         knobs[8].knobValue = -1;
         knobs[9].knobValue = light[i].moveSpeed;

         sliders[8].sliderValue = brightness;
         sliders[9].sliderValue = visibility;

         sliders[10].sliderValue = red;
         sliders[11].sliderValue = green;
         sliders[12].sliderValue = blue;
           
         break;
         
      }
   }
   editorShowButtons();
}

void addScript(double x,double y,double width,double height){
   for(int i = 0;i<sizeof(scripts)/sizeof(scripts[0]);i++){
      if(!scripts[i].reserved){
         editor.selected = true;
         editor.typeSelected = 7;
         editor.indexSelected = i;
         scripts[i].reserved = true;
         scripts[i].x = x;
         scripts[i].y = y;
         scripts[i].width = width;
         scripts[i].height = height;
         scripts[i].scriptInt = 0;
           
         break;
      }
   }
   editorShowButtons();
}

void addDeathBox(double x, double y, double width,double height,double opacity){
   for(int i = 0;i<sizeof(deathbox)/sizeof(deathbox[0]);i++){
      if(!deathbox[i].reserved){
         editor.selected = true;
         editor.typeSelected = 5;
         editor.indexSelected = i;
         deathbox[i].reserved = true;
         deathbox[i].x = x;
         deathbox[i].y = y;
         deathbox[i].width = width;
         deathbox[i].height = height;
         deathbox[i].opacity = opacity;

         deathbox[i].moveSpeed = 0;
         deathbox[i].moveNodeInt = -1;
         
         knobs[8].knobValue = -1;
         knobs[9].knobValue = 0;

         sliders[14].sliderValue = opacity;
           
   
         break;
      }
   }
   editorShowButtons();
}

void addMoveNode(int x, int y){
   for(int i = 0;i<sizeof(movenodes)/sizeof(movenodes[0]);i++){
      if(!movenodes[i].reserved){
         editor.selected = true;
         editor.typeSelected = 6;
         editor.indexSelected = i;
         editor.movenodeSelected = 0;
         movenodes[i].reserved = true;
         movenodes[i].positions[0][0] = (double)x;
         movenodes[i].positions[0][1] = (double)y;
         movenodes[i].nodesCount = 1;
         movenodes[i].wrap = false;
         break;
      }
   }
   editorShowButtons();
}

void addSpecial(int x, int y,int size,int type){
   for(int i = 0;i<sizeof(specials)/sizeof(specials[0]);i++){
      if(!specials[i].reserved){
         editor.selected = true;
         editor.typeSelected = 9;
         editor.indexSelected = i;
         specials[i].reserved = true;
         specials[i].x = (double)x;
         specials[i].y = (double)y;
         specials[i].size = size;
         specials[i].type = type;

         break;
      }
   }
   editorShowButtons();
}

void addTextPopUp(int x, int y,double width,double height){
   for(int i = 0;i<sizeof(textpopups)/sizeof(textpopups[0]);i++){
      if(!textpopups[i].reserved){
         editor.selected = true;
         editor.typeSelected = 10;
         editor.indexSelected = i;
         textpopups[i].reserved = true;
         textpopups[i].x = (double)x;
         textpopups[i].y = (double)y;
         textpopups[i].width = width;
         textpopups[i].height = height;
         textpopups[i].textContent = malloc(200*sizeof(char));
         textpopups[i].xPopup = 0;
         textpopups[i].yPopup = 0;
         textpopups[i].font = 10;

         break;
      }
   }
   editorShowButtons();
}



void addPlatform(int x,int y,double width,double height,double slope,bool slopeInv,int texture,int type,double scale,double offsetX,double offsetY,bool stretch,bool collidable,double opacity,double animation
 ,double red,double green,double blue){
   for(int i = 1;i<sizeof(platforms)/sizeof(platforms[0]);i++){
      if(!platforms[i].reserved){
        editor.selected = true;
        editor.typeSelected = 1;
        editor.indexSelected = i;
        platforms[i].reserved = true;
        platforms[i].x = x;
        platforms[i].y = y;
        platforms[i].width = width;
        platforms[i].height = height;
        platforms[i].slope = slope;
        platforms[i].collidable = collidable;
        platforms[i].opacity = opacity;
        platforms[i].textureStretch = stretch;
        sliders[0].sliderValue = 0;
        platforms[i].slopeInv = slopeInv;
        platforms[i].textureScale = scale;
        platforms[i].textureAnimationTime = animation;
        
        platforms[i].red = red;
        platforms[i].green = green;
        platforms[i].blue = blue;
        platforms[i].moveSpeed = 0;
        platforms[i].moveNodeInt = -1;
        
        knobs[0].knobValue = 50;
        if(type == 1){platforms[i].textureInt = FindTextureInt("check");platforms[i].type = 1;}
        else if(type == 2){platforms[i].textureInt = FindTextureInt("Bcheck");platforms[i].type = 2;}
        else{platforms[i].textureInt = texture;platforms[i].type = 0;}
        
        platforms[i].textureOffsetX = offsetX;
        platforms[i].textureOffsetY = offsetY;
        sliders[0].sliderValue = platforms[i].slope*(180)/(2*PI);
        sliders[1].sliderValue = offsetX;
        sliders[2].sliderValue = offsetY;
        knobs[0].knobValue = scale;
        sliders[14].sliderValue = opacity;
        knobs[5].knobValue = animation;
        knobs[8].knobValue = -1;
        knobs[9].knobValue = 0;
        knobs[16].knobValue = 0;
        knobs[17].knobValue = 0;
        

        sliders[10].sliderValue = red;
        sliders[11].sliderValue = green;
        sliders[12].sliderValue = blue;
        


        
        break;
      }
   }
   editorShowButtons();
}