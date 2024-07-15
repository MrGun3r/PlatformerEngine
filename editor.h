// Buttons layout

// 0 => Add platform
// 1 => Translate 
// 2 => Resize
// 3 => Slope
// 4 => Save Map
// 5 => Delete
// 6 => Load Map
// 7 => Texture
// 8 => SlopeInv
// 9 => Copy
// 10 => New
// 11 => Test
// 12 => Add Trigger
// 13 => Add Finish Line
// 14 => Add Checkpoint
// 15 => Zoom in
// 16 => Zoom Out
// 17 => Texture Stretch
// 18 => Background Change

// Slider Layout
// 0 => Slope
// 1 => Texture offset X
// 2 => Texture offset Y
// 3 => Texture Scale
// 4 => Border X
// 5 => Border Y


void FUpdate_Editor(){
   
     // Update Selection
     if(player[0].editorSelectionTime <= 1000){
      player[0].editorSelectionTime += 1000*app.deltaTime;
     }
     for(int i = 1;i<sizeof(platforms)/sizeof(platforms[0]);i++){
      if(platforms[i].reserved && platforms[i].editorSelectionTime <= 1000){
         platforms[i].editorSelectionTime += 1000*app.deltaTime;
      }
     }

     for(int i = 0;i<sizeof(deathbox)/sizeof(deathbox[0]);i++){
      if(deathbox[i].reserved && deathbox[i].editorSelectionTime <= 1000){
         deathbox[i].editorSelectionTime += 1000*app.deltaTime;
      }
     }
     for(int i = 0;i<sizeof(light)/sizeof(light[0]);i++){
      if(light[i].reserved && light[i].editorSelectionTime <= 1000){
         light[i].editorSelectionTime += 1000*app.deltaTime;
      }
     }
     for(int i = 0;i<sizeof(triggers)/sizeof(triggers[0]);i++){
      if(triggers[i].reserved && triggers[i].editorSelectionTime <= 1000){
         triggers[i].editorSelectionTime += 1000*app.deltaTime;
      }
     }
     for(int i = 0;i<sizeof(displacement)/sizeof(displacement[0]);i++){
      if(displacement[i].reserved && displacement[i].editorSelectionTime <= 1000){
         displacement[i].editorSelectionTime += 1000*app.deltaTime;
      }
     }
    // Update Selection


    Update_Slider();
    Update_Knobs();
    Update_TextBox();
   camera.scale += (camera.scaleReal - camera.scale)*app.deltaTime*5;
   
   if(mouse.wheel == 1){
      camera.scaleReal *= 1.2;
      camera.scaleReal = min(4,camera.scaleReal);
   }
   else if (mouse.wheel == -1){
      camera.scaleReal /= 1.2;
      camera.scaleReal = max(0.5,camera.scaleReal);
   }
   if(editor.status < 0){
      FTransformState();
   }

   // Change texture platform
   for(int i = 1;i<sizeof(platforms)/sizeof(platforms[0]);i++){
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




   // Buttons
   for(int i = 0;i<sizeof(buttons)/sizeof(buttons[0]);i++){
    if(buttons[i].reserved){
      int yMin = buttons[i].y;
      int yMax = buttons[i].y+buttons[i].hoverHeight;
      int xMin = buttons[i].x;
      int xMax = buttons[i].x+buttons[i].hoverWidth;      
      if(mouse.x >= xMin && mouse.x <= xMax && mouse.y >= yMin && mouse.y <= yMax && mouse.left == -1){
        mouse.left = 0;
       if(i == 0){
         addPlatform(gameWidth/2-camera.x,gameHeight/2-camera.y,25,25,0,false,FindTextureInt("stone"),0,50,0,0,false,true,255,0,0,100,0);
       } 
       if(i == 1 && editor.selected){
         editor.transform = 1;
         buttons[1].highlight = true;
         buttons[2].highlight = false;
         
       }  
       else if (i == 2  && editor.selected){
         editor.transform = 0;
         buttons[1].highlight = false;
         buttons[2].highlight = true;
         
       }
       else if (i == 4){
         editor.status = 0;
         editorShowButtons();
       }
       else if (i == 5  && editor.selected){
         // delete
         if(editor.typeSelected == 1){
            platforms[editor.indexSelected].reserved = false;
         }
         else if(editor.typeSelected == 2){
            triggers[editor.indexSelected].reserved = false;
         }
         else if (editor.typeSelected == 3){
            light[editor.indexSelected].reserved = false;
         }
         else if (editor.typeSelected == 4){
            displacement[editor.indexSelected].reserved = false;
         }
         else if (editor.typeSelected == 5){
            deathbox[editor.indexSelected].reserved = false;
         }
         editor.selected = false;
         editorShowButtons();
       }
       else if (i == 6){
         editor.status = 1;
         editorShowButtons();
       }
       else if (i == 7 && editor.selected){
         platforms[editor.indexSelected].textureInt++;
         if(!textures[platforms[editor.indexSelected].textureInt].reserved){
            platforms[editor.indexSelected].textureInt = 0;
         }
       }
       else if (i == 8){
         platforms[editor.indexSelected].slopeInv = !platforms[editor.indexSelected].slopeInv;
       }
       else if (i == 9){
         // Copy Object
         if(editor.typeSelected == 1){
            if(platforms[editor.indexSelected].type == 0){
               addPlatform(gameWidth/2-camera.x,gameHeight/2-camera.y,platforms[editor.indexSelected].width,platforms[editor.indexSelected].height,platforms[editor.indexSelected].slope,platforms[editor.indexSelected].slopeInv,platforms[editor.indexSelected].textureInt,0,platforms[editor.indexSelected].textureScale,platforms[editor.indexSelected].textureOffsetX,platforms[editor.indexSelected].textureOffsetY,platforms[editor.indexSelected].textureStretch,platforms[editor.indexSelected].collidable,platforms[editor.indexSelected].opacity,platforms[editor.indexSelected].moveAngle,platforms[editor.indexSelected].moveModule,platforms[editor.indexSelected].moveTime,platforms[editor.indexSelected].textureAnimationTime);
            }
            else if (platforms[editor.indexSelected].type == 1){
               addPlatform(gameWidth/2-camera.x,gameHeight/2-camera.y,platforms[editor.indexSelected].width,platforms[editor.indexSelected].height,platforms[editor.indexSelected].slope,platforms[editor.indexSelected].slopeInv,platforms[editor.indexSelected].textureInt,1,platforms[editor.indexSelected].textureScale,platforms[editor.indexSelected].textureOffsetX,platforms[editor.indexSelected].textureOffsetY,platforms[editor.indexSelected].textureStretch,platforms[editor.indexSelected].collidable,platforms[editor.indexSelected].opacity,platforms[editor.indexSelected].moveAngle,platforms[editor.indexSelected].moveModule,platforms[editor.indexSelected].moveTime,platforms[editor.indexSelected].textureAnimationTime);
            }
            else if (platforms[editor.indexSelected].type == 2){
               addPlatform(gameWidth/2-camera.x,gameHeight/2-camera.y,platforms[editor.indexSelected].width,platforms[editor.indexSelected].height,platforms[editor.indexSelected].slope,platforms[editor.indexSelected].slopeInv,platforms[editor.indexSelected].textureInt,2,platforms[editor.indexSelected].textureScale,platforms[editor.indexSelected].textureOffsetX,platforms[editor.indexSelected].textureOffsetY,platforms[editor.indexSelected].textureStretch,platforms[editor.indexSelected].collidable,platforms[editor.indexSelected].opacity,platforms[editor.indexSelected].moveAngle,platforms[editor.indexSelected].moveModule,platforms[editor.indexSelected].moveTime,platforms[editor.indexSelected].textureAnimationTime);
            }

         }
         else if (editor.typeSelected == 2){
           addTrigger(gameWidth/2-camera.x,gameHeight/2-camera.y,triggers[i].width,triggers[i].height,triggers[i].triggerType,triggers[i].opacity); 
         }
         else if (editor.typeSelected == 3){
            addLight(gameWidth/2-camera.x,gameHeight/2-camera.y,light[editor.indexSelected].size,light[editor.indexSelected].red,light[editor.indexSelected].green,light[editor.indexSelected].blue,light[editor.indexSelected].visibility,light[editor.indexSelected].brightness);
         }
         else if (editor.typeSelected == 4){
            addDisplacement(gameWidth/2-camera.x,gameHeight/2-camera.y,displacement[editor.indexSelected].width,displacement[editor.indexSelected].height,displacement[editor.indexSelected].type,displacement[editor.indexSelected].power,displacement[editor.indexSelected].powerType,displacement[editor.indexSelected].opacity);
         }
         else if (editor.typeSelected == 5){
            addDeathBox(gameWidth/2-camera.x,gameHeight/2-camera.y,deathbox[editor.indexSelected].width,deathbox[editor.indexSelected].height,deathbox[editor.indexSelected].opacity);
         }
         
       }
       else if (i == 10){
         // nothin
       }
       else if (i == 11){
         editor.typeSelected = -1;
         editor.selected = true;
         editorShowButtons();
       }
       else if (i == 12){
         addTrigger(gameWidth/2-camera.x,gameHeight/2-camera.y,25,25,0,255);
       }
       else if (i == 13){
         addPlatform(gameWidth/2-camera.x,gameHeight/2-camera.y,25,25,0,false,-1,1,50,0,0,false,true,255,0,0,255,0);
       }
       else if (i == 14){
         addPlatform(gameWidth/2-camera.x,gameHeight/2-camera.y,25,25,0,false,-1,2,50,0,0,false,true,255,0,0,255,0);
       }
       else if (i == 15){
         camera.scaleReal *= 1.2;
         camera.scaleReal = min(4,camera.scaleReal);
       }
       else if (i == 16){
         camera.scaleReal /= 1.2;
         camera.scaleReal = max(0.5,camera.scaleReal);
       }
       else if(i == 17){
         platforms[editor.indexSelected].textureStretch = !platforms[editor.indexSelected].textureStretch; 
       }
       else if(i == 18){
         app.backgroundInt++;
         if(!backgrounds[app.backgroundInt].reserved){
           app.backgroundInt = 0;
         }
       }
       else if (i == 19){
         addLight(gameWidth/2-camera.x,gameHeight/2-camera.y,25.0f,255,255,255,255,100);
       }
       else if (i == 20){
         addDisplacement(gameWidth/2-camera.x,gameHeight/2-camera.y,25.0f,25.0f,0,50,0,255);
       }
       else if (i == 21){
         displacement[editor.indexSelected].type++;
         displacement[editor.indexSelected].type = displacement[editor.indexSelected].type % 4;
       }
       else if (i == 22){
         displacement[editor.indexSelected].powerType++;
         displacement[editor.indexSelected].powerType = displacement[editor.indexSelected].powerType % 2;
       }
       else if (i == 23){
         addDeathBox(gameWidth/2-camera.x,gameHeight/2-camera.y,25.0f,25.0f,255);
       }
       else if (i == 24){
         platforms[editor.indexSelected].collidable = !platforms[editor.indexSelected].collidable;
       }
      }
    }
   }
   if(mouse.left == -1){
      if(editor.status < 0){
        FCheck_Select_Editor(); 
      }
     
     editorShowButtons();
   }
 if(editor.typeSelected == 1){
   platforms[editor.indexSelected].textureOffsetX = sliders[1].sliderValue;
   platforms[editor.indexSelected].textureOffsetY = sliders[2].sliderValue;
   platforms[editor.indexSelected].textureScale = knobs[0].knobValue;
   if(platforms[editor.indexSelected].type == 0){
   platforms[editor.indexSelected].slope = sliders[0].sliderValue/(180/(2*PI)); 
  }
  platforms[editor.indexSelected].opacity = sliders[14].sliderValue;
  platforms[editor.indexSelected].moveAngle = knobs[2].knobValue;
  platforms[editor.indexSelected].moveModule = sliders[17].sliderValue;
  platforms[editor.indexSelected].moveTime = sliders[18].sliderValue;
  platforms[editor.indexSelected].textureAnimationTime = knobs[5].knobValue;
  if(platforms[editor.indexSelected].type == 0){
    platforms[editor.indexSelected].red = sliders[10].sliderValue;
    platforms[editor.indexSelected].green = sliders[11].sliderValue;
    platforms[editor.indexSelected].blue = sliders[12].sliderValue;
  }
  else {
    platforms[editor.indexSelected].red = 255;
    platforms[editor.indexSelected].green = 255;
    platforms[editor.indexSelected].blue = 255;
  }
  
 }
 else if (editor.typeSelected == -1){
   mapData.xMin = -knobs[3].knobValue;
   mapData.xMax = knobs[3].knobValue;
   mapData.yMin = -knobs[4].knobValue;
   mapData.yMax = knobs[4].knobValue;
   app.backgroundOpacity = sliders[6].sliderValue;
 }
 else if (editor.typeSelected == 2){
   triggers[editor.indexSelected].opacity = sliders[14].sliderValue;
 }
 else if (editor.typeSelected == 3){
   light[editor.indexSelected].rotation = sliders[7].sliderValue;
   light[editor.indexSelected].brightness = sliders[8].sliderValue;
   light[editor.indexSelected].visibility = sliders[9].sliderValue;
   light[editor.indexSelected].red = sliders[10].sliderValue;
   light[editor.indexSelected].green = sliders[11].sliderValue;
   light[editor.indexSelected].blue = sliders[12].sliderValue;
 }
 else if (editor.typeSelected  == 4){
   displacement[editor.indexSelected].power = sliders[13].sliderValue; 
   displacement[editor.indexSelected].opacity = sliders[14].sliderValue;
 }
 else if (editor.typeSelected  == 5){
   deathbox[editor.indexSelected].opacity = sliders[14].sliderValue;
 }
}

void addTrigger(int x,int y,double width,double height,int Type,double opacity){
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
        triggers[i].opacity = 255;
        triggers[i].triggerType = Type;
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
         sliders[14].sliderValue = 255;
         break;
      }
   }
   editorShowButtons();
}

void addLight(double x,double y,double size,double red,double green,double blue,double visibility,double brightness){
   for(int i = 1;i<sizeof(light)/sizeof(light[0]);i++){
      if(!light[i].reserved){
         editor.selected = true;
         editor.typeSelected = 3;
         editor.indexSelected = i;
         light[i].reserved = true;
         light[i].x = x;
         light[i].y = y;
         light[i].size = size;
         light[i].red =   red;
         light[i].green = green;
         light[i].blue =  blue;
         light[i].visibility = visibility;
         light[i].brightness = brightness;
         
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
         sliders[14].sliderValue = 255;
         break;
      }
   }
   editorShowButtons();
}

void addPlatform(int x,int y,double width,double height,double slope,bool slopeInv,int texture,int type,double scale,double offsetX,double offsetY,bool stretch,bool collidable,double opacity,double moveAngle,double moveModule,double moveTime,double animation){
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
        platforms[i].moveAngle = moveAngle;
        platforms[i].moveModule = moveModule;
        platforms[i].moveTime = moveTime;
        platforms[i].textureAnimationTime = animation;

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

        knobs[2].knobValue = moveAngle;
        sliders[17].sliderValue = moveModule;
        sliders[18].sliderValue = moveTime;

        sliders[10].sliderValue = 255;
        sliders[11].sliderValue = 255;
        sliders[12].sliderValue = 255;

        
        break;
      }
   }
   editorShowButtons();
}

void editorShowButtons(){
   for(int i = 0 ;i<sizeof(buttons)/sizeof(buttons[0]); i++){
      buttons[i].reserved = false;
   }
   for(int i = 0 ;i<sizeof(sliders)/sizeof(sliders[0]); i++){
      sliders[i].reserved = false;
   }
   for(int i = 0 ;i<sizeof(knobs)/sizeof(knobs[0]); i++){
      knobs[i].reserved = false;
   }
   for(int i = 0 ;i<sizeof(textbox)/sizeof(textbox[0]); i++){
      textbox[i].reserved = false;
   }

   buttons[0].reserved = true;
   buttons[4].reserved = true;
   buttons[6].reserved = true;
   buttons[10].reserved = true;
   buttons[11].reserved = true;
   buttons[12].reserved = true;
   buttons[13].reserved = true;
   buttons[14].reserved = true;
   buttons[15].reserved = true;
   buttons[16].reserved = true;
   buttons[19].reserved = true;
   buttons[20].reserved = true;
   buttons[23].reserved = true;
   if(editor.status >= 0){
      textbox[0].reserved = true;
   }

   if(editor.selected){
      if(editor.typeSelected == -1){
        knobs[3].reserved = true;
        knobs[4].reserved = true;
        sliders[6].reserved = true;
        buttons[18].reserved = true;
        return;
      } 
      buttons[1].reserved = true;
      buttons[2].reserved = true;
      buttons[5].reserved = true;
      buttons[9].reserved = true;
      if(editor.typeSelected == 0){
            // Nothing so far
      }
      else if(editor.typeSelected == 1){
         sliders[1].reserved = true;
         sliders[2].reserved = true;
         knobs[0].reserved = true;
         buttons[17].reserved = true;
         sliders[14].reserved = true;
         ChangeSliderPosition(14,sliders[14].x,340);
         knobs[5].reserved = true;
         buttons[24].reserved = true;

         knobs[2].reserved = true;
         sliders[17].reserved = true;
         sliders[18].reserved = true;
         if(platforms[editor.indexSelected].type == 0){

         sliders[0].reserved = true;
         buttons[7].reserved = true;
         buttons[8].reserved = true;
         sliders[10].reserved = true;
         sliders[11].reserved = true;
         sliders[12].reserved = true;
         
         
         ChangeSliderPosition(1,sliders[1].x,260);
         ChangeSliderPosition(2,sliders[2].x,280);
        // ChangeSliderPosition(3,knobs[0].x,300);

         ChangeSliderPosition(10,sliders[10].x,380);
         ChangeSliderPosition(11,sliders[11].x,400);
         ChangeSliderPosition(12,sliders[12].x,420);

         ChangeButtonPosition(17,buttons[17].x,320);

         }
         else if(platforms[editor.indexSelected].type == 1 || platforms[editor.indexSelected].type == 2){
            ChangeSliderPosition(1,sliders[1].x,210);
            ChangeSliderPosition(2,sliders[2].x,230);
          //  ChangeSliderPosition(3,sliders[3].x,250); 
            ChangeButtonPosition(17,buttons[17].x,270); 
         }
      }
      else if (editor.typeSelected == 2){
       sliders[14].reserved = true;
       ChangeSliderPosition(14,sliders[14].x,220);
      }
      else if (editor.typeSelected == 3){
         sliders[7].reserved = true;
         sliders[8].reserved = true;
         sliders[9].reserved = true;
         sliders[10].reserved = true;
         sliders[11].reserved = true;
         sliders[12].reserved = true;

         ChangeSliderPosition(10,sliders[10].x,260);
         ChangeSliderPosition(11,sliders[11].x,280);
         ChangeSliderPosition(12,sliders[12].x,300);
      }
      else if (editor.typeSelected == 4){
         buttons[21].reserved = true;
         buttons[22].reserved = true;
         sliders[13].reserved = true;
         sliders[14].reserved = true;
         ChangeSliderPosition(14,sliders[14].x,240);
      }
      else if (editor.typeSelected == 5){
          sliders[14].reserved = true;
         ChangeSliderPosition(14,sliders[14].x,220);
      }
       
   }
}

void FDrawLoadSave(){

   
      SDL_SetRenderTarget(renderer,HUDLayer);
      SDL_SetRenderDrawColor(renderer,100,100,100,200);
      SDL_RenderFillRect(renderer,&(SDL_Rect){30,100,windowWidth-180,150});

      if(editor.status == 0){
      renderText(33,"Enter to save / Escape to cancel",45,210,33*12,15,255,200,(int[3]){255,255,255});
      }
      else if (editor.status == 1){
         renderText(33,"Enter to load / Escape to cancel",45,210,33*12,15,255,200,(int[3]){255,255,255});
      }
   
}


void FDraw_Editor(){  
    
   SDL_RenderClear(renderer);
   DrawBackground();
   SDL_SetRenderDrawColor(renderer,210,210,210,255);
   SDL_SetRenderDrawColor(renderer,200,0,0,100);

   FDrawObjects();
   if(editor.status >= 0){
    FDrawLoadSave();
   }
   

   
   // HUD
   SDL_SetRenderTarget(renderer,HUDLayer);
   SDL_SetRenderDrawColor(renderer,100,100,100,255);
   SDL_RenderFillRect(renderer,&(SDL_Rect){0,0,gameWidth,50});
   SDL_SetRenderDrawColor(renderer,20,20,20,255);
   SDL_RenderDrawRect(renderer,&(SDL_Rect){0,0,gameWidth,50});
   SDL_SetRenderDrawColor(renderer,100,100,100,255);
   SDL_RenderFillRect(renderer,&(SDL_Rect){gameWidth-200,0,200,gameHeight});
   SDL_SetRenderDrawColor(renderer,20,20,20,255);
   SDL_RenderDrawRect(renderer,&(SDL_Rect){gameWidth-200,0,200,gameHeight});
   SDL_SetRenderDrawColor(renderer,90,90,90,255);
   SDL_RenderFillRect(renderer,&(SDL_Rect){60,5,gameWidth-275,40});
   SDL_SetRenderDrawColor(renderer,80,80,80,255);
   SDL_RenderFillRect(renderer,&(SDL_Rect){gameWidth-195,gameHeight-20,190,15});
   SDL_SetRenderDrawColor(renderer,0,0,0,255);
   SDL_RenderDrawRect(renderer,&(SDL_Rect){60,5,gameWidth-275,40});
   SDL_RenderDrawRect(renderer,&(SDL_Rect){gameWidth-195,gameHeight-20,190,15});
   
   FDraw_SideBar_Editor();
   FGUIHover();
   renderButtons();
   renderSliders();
   renderKnobs();
   renderTextBox();
   char posX[10]; 
   char posY[10];
   sprintf(posX,"X:%d\0",(int)((mouse.x - gameWidth/2)/camera.scale + gameWidth/2 - camera.x));
   sprintf(posY,"Y:%d\0",(int)((mouse.y - gameHeight/2)/camera.scale + gameHeight/2 - camera.y));
  
   renderText(len(posX),posX,5,gameHeight-14,len(posX)*7,12,255,200,(int[3]){255,255,255});
   renderText(len(posY),posY,len(posX)*7+15,gameHeight-14,len(posY)*7,12,255,200,(int[3]){255,255,255});
   SDL_SetRenderTarget(renderer,backgroundLayer);
}

void FCheck_Select_Editor(){
   
   if(editor.unSelect){
      int xMin = player[0].xDraw;
      int xMax = player[0].xDraw+player[0].widthDraw;
      int yMin = player[0].yDraw;
      int yMax = player[0].yDraw+player[0].heightDraw; 
      
      if(mouse.x >= xMin && mouse.x <= xMax && mouse.y >= yMin && mouse.y <= yMax && player[0].editorSelectionTime >= 999){
         player[0].editorSelectionTime = 0;
         editor.selected = true;
         editor.typeSelected = 0;
         editor.indexSelected = 0;
         return;
      }
      if((mouse.y <= 100 && mouse.x > 0 && mouse.x < gameWidth-200) || (mouse.x > gameWidth-200)){return;}
      for(int i = 0;i<sizeof(platforms)/sizeof(platforms[0]);i++){
         if(platforms[i].reserved && platforms[i].editorSelectionTime >= 999){
            int xMin = platforms[i].xDraw;
            int xMax = platforms[i].xDraw+platforms[i].widthDraw;
            int yMin = platforms[i].yDraw;
            int yMax = platforms[i].yDraw+platforms[i].heightDraw; 
         if(mouse.x >= xMin && mouse.x <= xMax && mouse.y >= yMin && mouse.y <= yMax){
            platforms[i].editorSelectionTime = 0;
            editor.selected = true;
            editor.typeSelected = 1;
            editor.indexSelected = i;
            sliders[0].sliderValue = platforms[editor.indexSelected].slope*(180/(2*PI));
            sliders[1].sliderValue = platforms[editor.indexSelected].textureOffsetX;
            sliders[2].sliderValue = platforms[editor.indexSelected].textureOffsetY;
            knobs[0].knobValue = platforms[editor.indexSelected].textureScale;
            sliders[14].sliderValue = platforms[editor.indexSelected].opacity;
            knobs[5].knobValue = platforms[editor.indexSelected].textureAnimationTime;

            sliders[10].sliderValue = platforms[editor.indexSelected].red;
            sliders[11].sliderValue = platforms[editor.indexSelected].green;
            sliders[12].sliderValue = platforms[editor.indexSelected].blue;

            knobs[2].knobValue = platforms[editor.indexSelected].moveAngle;
            sliders[17].sliderValue = platforms[editor.indexSelected].moveModule;
            sliders[18].sliderValue = platforms[editor.indexSelected].moveTime;
            return;
          }
        }
      }
      for(int i = 0 ;i<sizeof(triggers)/sizeof(triggers[0]);i++){
         if(triggers[i].reserved && triggers[i].editorSelectionTime >= 999){
            int xMin = triggers[i].xDraw;
            int xMax = triggers[i].xDraw+triggers[i].widthDraw;
            int yMin = triggers[i].yDraw;
            int yMax = triggers[i].yDraw+triggers[i].heightDraw;
         if(mouse.x >= xMin && mouse.x <= xMax && mouse.y >= yMin && mouse.y <= yMax){
            triggers[i].editorSelectionTime = 0;
            editor.selected = true;
            editor.typeSelected = 2;
            editor.indexSelected = i;
            sliders[14].sliderValue = triggers[editor.indexSelected].opacity;
            return;
          }
         }
      }

      for(int i = 0 ;i<sizeof(displacement)/sizeof(displacement[0]);i++){
         if(displacement[i].reserved && displacement[i].editorSelectionTime >= 999){
            int xMin = displacement[i].xDraw;
            int xMax = displacement[i].xDraw+displacement[i].widthDraw;
            int yMin = displacement[i].yDraw;
            int yMax = displacement[i].yDraw+displacement[i].heightDraw;
         if(mouse.x >= xMin && mouse.x <= xMax && mouse.y >= yMin && mouse.y <= yMax){
            displacement[i].editorSelectionTime = 0;
            editor.selected = true;
            editor.typeSelected = 4;
            editor.indexSelected = i;
            sliders[13].sliderValue = displacement[editor.indexSelected].power;
            sliders[14].sliderValue = displacement[editor.indexSelected].opacity;
            return;
          }
         }
      }

      for(int i = 0;i<sizeof(deathbox)/sizeof(deathbox[0]);i++){
         if(deathbox[i].reserved && deathbox[i].editorSelectionTime >= 999){
            int xMin = deathbox[i].xDraw;
            int xMax = deathbox[i].xDraw+deathbox[i].widthDraw;
            int yMin = deathbox[i].yDraw;
            int yMax = deathbox[i].yDraw+deathbox[i].heightDraw;
         if(mouse.x >= xMin && mouse.x <= xMax && mouse.y >= yMin && mouse.y <= yMax){
            deathbox[i].editorSelectionTime = 0;
            editor.selected = true;
            editor.typeSelected = 5;
            editor.indexSelected = i;
            sliders[14].sliderValue = deathbox[editor.indexSelected].opacity;
            return;
          }
         }
      }

      for(int i = 0;i<sizeof(light)/sizeof(light[0]);i++){
         if(light[i].reserved && light[i].editorSelectionTime >= 999){
            int xMin = light[i].xDraw;
            int xMax = light[i].xDraw+light[i].sizeDraw;
            int yMin = light[i].yDraw;
            int yMax = light[i].yDraw+light[i].sizeDraw;
         if(mouse.x >= xMin && mouse.x <= xMax && mouse.y >= yMin && mouse.y <= yMax){
            light[i].editorSelectionTime = 0;
            editor.selected = true;
            editor.typeSelected = 3;
            editor.indexSelected = i;
            sliders[7].sliderValue = light[editor.indexSelected].rotation;
            sliders[8].sliderValue = light[editor.indexSelected].brightness;
            sliders[9].sliderValue = light[editor.indexSelected].visibility;
            sliders[10].sliderValue = light[editor.indexSelected].red;
            sliders[11].sliderValue = light[editor.indexSelected].green;
            sliders[12].sliderValue = light[editor.indexSelected].blue;
            return;
          }
         }
      }
      editor.selected = false;
      }
      editor.unSelect = true;
      return;
}

void FDraw_SideBar_Editor(){
   // info box
   FInfoBox();
  if(editor.selected){
   char* Xvalue = malloc(256);
   char* Yvalue = malloc(256);
   char* Widthvalue = malloc(256);
   char* Heightvalue = malloc(256);
   char* upperText = malloc(256);
   if(editor.typeSelected == 0){
     sprintf(Xvalue,"x:%d\0",(int)player[0].x);
     sprintf(Yvalue,"y:%d\0",(int)player[0].y);
     sprintf(Widthvalue,"width:%d\0",(int)player[0].width);
     sprintf(Heightvalue,"height:%d\0",(int)player[0].height);
     sprintf(upperText,"%s\0","Player");
   }
   else if(editor.typeSelected == 1){
     sprintf(Xvalue,"x:%d\0",(int)platforms[editor.indexSelected].x);
     sprintf(Yvalue,"y:%d\0",(int)platforms[editor.indexSelected].y);
     sprintf(Widthvalue,"width:%d\0",(int)platforms[editor.indexSelected].width);
     sprintf(Heightvalue,"height:%d\0",(int)platforms[editor.indexSelected].height);   
     SDL_memcpy(buttons[7].value,textures[platforms[editor.indexSelected].textureInt].textureName,len(textures[platforms[editor.indexSelected].textureInt].textureName)+1);
     SDL_itoa((int)platforms[editor.indexSelected].slopeInv,buttons[8].value,10);
     SDL_itoa((int)platforms[editor.indexSelected].textureStretch,buttons[17].value,10);
     SDL_itoa((int)platforms[editor.indexSelected].collidable,buttons[24].value,10);
     if(platforms[editor.indexSelected].type == 0){
      sprintf(upperText,"%s\0","Platform");
     }
     else if(platforms[editor.indexSelected].type == 1){
      sprintf(upperText,"%s\0","Finish");
     }
     else if(platforms[editor.indexSelected].type == 2){
      sprintf(upperText,"%s\0","Checkpoint");
     }
   }
   else if (editor.typeSelected == 2){
     sprintf(Xvalue,"x:%d\0",(int)triggers[editor.indexSelected].x);
     sprintf(Yvalue,"y:%d\0",(int)triggers[editor.indexSelected].y);
     sprintf(Widthvalue,"width:%d\0",(int)triggers[editor.indexSelected].width);
     sprintf(Heightvalue,"height:%d\0",(int)triggers[editor.indexSelected].height); 
     sprintf(upperText,"%s\0","Trigger");
   }
   else if (editor.typeSelected == 3){
     sprintf(Xvalue,"x:%d\0",(int)light[editor.indexSelected].x);
     sprintf(Yvalue,"y:%d\0",(int)light[editor.indexSelected].y);
     sprintf(Widthvalue,"width:%d\0",(int)light[editor.indexSelected].size);
     sprintf(Heightvalue,"height:%d\0",(int)light[editor.indexSelected].size);
     
     sprintf(upperText,"%s\0","Light");
   }
   else if (editor.typeSelected == 4) {
     sprintf(Xvalue,"x:%d\0",(int)displacement[editor.indexSelected].x);
     sprintf(Yvalue,"y:%d\0",(int)displacement[editor.indexSelected].y);
     sprintf(Widthvalue,"width:%d\0",(int)displacement[editor.indexSelected].width);
     sprintf(Heightvalue,"height:%d\0",(int)displacement[editor.indexSelected].height);
     sprintf(upperText,"%s\0","Displacement");
     

     char* displaceValue = malloc(100);
     char* typeValue = malloc(100);
    // Displacement value
    if(displacement[editor.indexSelected].type == 0){
      sprintf(typeValue,"Right");
    }
    else if (displacement[editor.indexSelected].type == 1){
      sprintf(typeValue,"Up");
    }
     else if (displacement[editor.indexSelected].type == 2){
      sprintf(typeValue,"Left");
    }
     else if (displacement[editor.indexSelected].type == 3){
      sprintf(typeValue,"Down");
    }
    // Type Value
    if(displacement[editor.indexSelected].powerType == 0){
      sprintf(displaceValue,"Velocity");
    }
    else if(displacement[editor.indexSelected].powerType == 1){
      sprintf(displaceValue,"Accelerate");
    }
     
     SDL_memcpy(buttons[21].value,typeValue,len(typeValue)+1);
     SDL_memcpy(buttons[22].value,displaceValue,len(displaceValue)+1);

     free(displaceValue);
     free(typeValue);
   }
   else if (editor.typeSelected == 5){
     sprintf(Xvalue,"x:%d\0",(int)deathbox[editor.indexSelected].x);
     sprintf(Yvalue,"y:%d\0",(int)deathbox[editor.indexSelected].y);
     sprintf(Widthvalue,"width:%d\0",(int)deathbox[editor.indexSelected].width);
     sprintf(Heightvalue,"height:%d\0",(int)deathbox[editor.indexSelected].height);
     
     sprintf(upperText,"%s\0","DeathBox");
   }
   else if(editor.typeSelected == -1){
   
   SDL_memcpy(buttons[18].value,backgrounds[app.backgroundInt].textureName,len(backgrounds[app.backgroundInt].textureName)+1);
   sprintf(upperText,"%s\0","Map");
  }
  if(editor.typeSelected != -1){
   renderText(len(Xvalue),Xvalue,gameWidth-190,100,len(Xvalue)*10,12,255,200,(int[3]){255,255,255});
   renderText(len(Yvalue),Yvalue,gameWidth-190,120,len(Yvalue)*10,12,255,200,(int[3]){255,255,255});
   renderText(len(Widthvalue),Widthvalue,gameWidth-190,140,len(Widthvalue)*10,12,255,200,(int[3]){255,255,255});
   renderText(len(Heightvalue),Heightvalue,gameWidth-190,160,len(Heightvalue)*10,12,255,200,(int[3]){255,255,255});
  }
   renderText(len(upperText),upperText,gameWidth-100-len(upperText)*6,10,len(upperText)*12,15,255,200,(int[3]){255,255,255});
   free(upperText);
   free(Xvalue);
   free(Yvalue);
   free(Heightvalue);
   free(Widthvalue);
  }
}
void FInfoBox(){
   char* infoText = malloc(100);
   for(int i = 0;i<sizeof(buttons)/sizeof(buttons[0]);i++){
    if(buttons[i].reserved && buttons[i].hoverOpacity>1 && !buttons[i].highlight){
      if(i == 0){  
        SDL_memcpy(infoText,"Add Platform\0",sizeof("Add Platform\0"));
      }
      else if(i == 1){  
        SDL_memcpy(infoText,"Translate\0",sizeof("Translate\0"));
      }
      else if(i == 2){  
        SDL_memcpy(infoText,"Resize\0",sizeof("Resize\0"));
      }
      else if(i == 4){  
        SDL_memcpy(infoText,"Save Map\0",sizeof("Save Map\0"));
      }
      else if(i == 5){  
        SDL_memcpy(infoText,"Delete Object\0",sizeof("Delete Object\0"));
      }
      else if(i == 6){  
        SDL_memcpy(infoText,"Load Map\0",sizeof("Load Map\0"));
      }
      else if(i == 7){  
        SDL_memcpy(infoText,"Change Texture\0",sizeof("Change Texture\0"));
      }
      else if(i == 8){  
        SDL_memcpy(infoText,"Inverse Slope\0",sizeof("Inverse Slope\0"));
      }
      else if(i == 9){  
        SDL_memcpy(infoText,"Copy Object\0",sizeof("Copy Object\0"));
      }
      else if(i == 10){  
        SDL_memcpy(infoText,"Load New Map\0",sizeof("Load New Map\0"));
      }
      else if(i == 11){  
        SDL_memcpy(infoText,"Map Settings\0",sizeof("Map Settings\0"));
      }
      else if(i == 12){  
        SDL_memcpy(infoText,"Add Trigger\0",sizeof("Add Trigger\0"));
      }
      else if(i == 13){  
        SDL_memcpy(infoText,"Add Finish Line\0",sizeof("Add Finish Line\0"));
      }
      else if(i == 14){  
        SDL_memcpy(infoText,"Add Checkpoint\0",sizeof("Add Checkpoint\0"));
      }
       else if(i == 15){  
        SDL_memcpy(infoText,"Zoom In\0",sizeof("Zoom In\0"));
      }
      
       else if(i == 16){  
        SDL_memcpy(infoText,"Zoom Out\0",sizeof("Zoom Out\0"));
      }
      else if (i == 17){
         SDL_memcpy(infoText,"Texture Stretch\0",sizeof("Texture Stretch\0"));
      }
      else if (i == 18){
         SDL_memcpy(infoText,"Change Background\0",sizeof("Change Background\0"));
      }
      else if (i == 19){
         SDL_memcpy(infoText,"Add Light\0",sizeof("Add Light\0"));
      }
      else if (i == 20){
         SDL_memcpy(infoText,"Add Displacement Block\0",sizeof("Add Displacement Block\0"));
      }
      else if (i == 21){
         SDL_memcpy(infoText,"Change Displacement Direction\0",sizeof("Change Displacement Direction\0"));
      }
      else if (i == 22){
         SDL_memcpy(infoText,"Change Displacement Type\0",sizeof("Change Displacement Type\0"));
      }
      else if (i == 23){
         SDL_memcpy(infoText,"Add DeathBox\0",sizeof("Add DeathBox\0"));
      }
      else if (i == 24){
         SDL_memcpy(infoText,"Toggle Collidable\0",sizeof("Toggle Collidable\0"));
      }
      

      renderText(len(infoText),infoText,gameWidth-190,gameHeight-16,7*len(infoText),10,255,200,(int[3]){200,200,200});
      return;
    }
   }
   for(int i = 0 ;i<sizeof(sliders)/sizeof(sliders[0]);i++){
      if(sliders[i].reserved && sliders[i].hoverOpacity>1 && !sliders[i].highlight){
         if(i == 0){  
            SDL_memcpy(infoText,"Change Slope\0",sizeof("Change Slope\0"));
      }
      else if(i == 1){  
            SDL_memcpy(infoText,"Change Texture Offset X\0",sizeof("Change Texture Offset X\0"));
      }
      else if(i == 2){  
            SDL_memcpy(infoText,"Change Texture Offset Y\0",sizeof("Change Texture Offset Y\0"));
      }
      else if(i == 3){  
            SDL_memcpy(infoText,"Change Texture Scale\0",sizeof("Change Texture Scale\0"));
      }
      else if(i == 4){  
            SDL_memcpy(infoText,"Change Map Border X\0",sizeof("Change Map Border X\0"));
      }
      else if(i == 5){  
            SDL_memcpy(infoText,"Change Map Border Y\0",sizeof("Change Map Border Y\0"));
      }
      else if(i == 6){  
            SDL_memcpy(infoText,"Change Map Light\0",sizeof("Change Map Light\0"));
      }
      else if(i == 7){  
            SDL_memcpy(infoText,"Change Light Rotation\0",sizeof("Change Light Rotation\0"));
      }
      else if(i == 8){  
            SDL_memcpy(infoText,"Change Light Brightness\0",sizeof("Change Light Brightness\0"));
      }
      else if(i == 9){  
            SDL_memcpy(infoText,"Change Light Visibility\0",sizeof("Change Light Visibility\0"));
      }
      else if(i == 10){  
            SDL_memcpy(infoText,"Change Red Value\0",sizeof("Change Red Value\0"));
      }
      else if(i == 11){  
            SDL_memcpy(infoText,"Change Green Value\0",sizeof("Change Green Value\0"));
      }
      else if(i == 12){  
            SDL_memcpy(infoText,"Change Blue Value\0",sizeof("Change Blue Value\0"));
      }
      else if(i == 13){  
            SDL_memcpy(infoText,"Change Displacement Power\0",sizeof("Change Displacement Power\0"));
      }
      else if(i == 14){  
            SDL_memcpy(infoText,"Change Opacity\0",sizeof("Change Opacity\0"));
      }
      else if(i == 15){  
            SDL_memcpy(infoText,"Change Animation Speed\0",sizeof("Change Animation Speed\0"));
      }

      renderText(len(infoText),infoText,gameWidth-190,gameHeight-16,7*len(infoText),10,255,200,(int[3]){200,200,200});
      free(infoText);
      return;
      }
   }
}

void FTransformState(){
  if(mouse.left && editor.selected && !((mouse.y <= 100 && mouse.x > 0 && mouse.x < gameWidth-200) || (mouse.x > gameWidth-200))){
   mouse.dX = mouse.x - mouse.oldX;
   mouse.dY = mouse.y - mouse.oldY;
   if(SDL_abs(mouse.dX) >= 4 || SDL_abs(mouse.dY) >= 4){
      editor.unSelect = false;
   }
   
   if(editor.typeSelected == 0){
      if(editor.transform == 2){
         editor.transform = 1;
         buttons[1].highlight = true;
         buttons[2].highlight = false;
         buttons[4].highlight = false;
      }
      if(editor.transform == 1){
      player[0].x += (float)mouse.dX/camera.scale;
      player[0].y += (float)mouse.dY/camera.scale;
      }
      else if (editor.transform == 0){
      player[0].width += (float)(mouse.dX+mouse.dY)/(2*camera.scale);
      player[0].height = player[0].width*10/9;
      
      if(player[0].width <= 5){
         player[0].width = 5;
      }
      if(player[0].height <= 5){
         player[0].height = 5;
      }
      player[0].Owidth = player[0].width;
      }   
   }
   else if (editor.typeSelected == 1){
      if(editor.transform == 1){
         platforms[editor.indexSelected].x += mouse.dX/camera.scale;
         platforms[editor.indexSelected].y += mouse.dY/camera.scale; 
      }
      else if (editor.transform == 0){
           platforms[editor.indexSelected].width += mouse.dX/camera.scale;
           platforms[editor.indexSelected].height += mouse.dY/camera.scale; 
      
      if(platforms[editor.indexSelected].width <= 5){
         platforms[editor.indexSelected].width=5;
      }
      if(platforms[editor.indexSelected].height <= 5){
         platforms[editor.indexSelected].height = 5;
      }

      if(platforms[editor.indexSelected].width >= 1500){
         platforms[editor.indexSelected].width = 1500;
      }
      if(platforms[editor.indexSelected].height >= 1500){
         platforms[editor.indexSelected].height = 1500;
      }
      }
   }
   else if (editor.typeSelected == 2){
      if(editor.transform == 1){
         triggers[editor.indexSelected].x += mouse.dX/camera.scale;
         triggers[editor.indexSelected].y += mouse.dY/camera.scale; 
      }
      else if (editor.transform == 0){
           triggers[editor.indexSelected].width += mouse.dX/camera.scale;
           triggers[editor.indexSelected].height += mouse.dY/camera.scale; 
      
      if(triggers[editor.indexSelected].width <= 5){
         triggers[editor.indexSelected].width=5;
      }
      if(triggers[editor.indexSelected].height <= 5){
         triggers[editor.indexSelected].height = 5;
      }
     } 
   }
   else if (editor.typeSelected == 3){
      if(editor.transform == 1){
         light[editor.indexSelected].x += mouse.dX/camera.scale;
         light[editor.indexSelected].y += mouse.dY/camera.scale; 
      }
      else if (editor.transform == 0){
           light[editor.indexSelected].size += (mouse.dX+mouse.dY)/(2*camera.scale);
      if(light[editor.indexSelected].size <= 20){
         light[editor.indexSelected].size=20;
      }
      if(light[editor.indexSelected].size <= 20){
         light[editor.indexSelected].size = 20;
      }
     }
   }
   else if (editor.typeSelected == 4){
      if(editor.transform == 1){
         displacement[editor.indexSelected].x += mouse.dX/camera.scale;
         displacement[editor.indexSelected].y += mouse.dY/camera.scale; 
      }
      else if (editor.transform == 0){
           displacement[editor.indexSelected].width += mouse.dX/camera.scale;
           displacement[editor.indexSelected].height += mouse.dY/camera.scale; 
      
      if(displacement[editor.indexSelected].width <= 5){
         displacement[editor.indexSelected].width = 5;
      }
      if(displacement[editor.indexSelected].height <= 5){
         displacement[editor.indexSelected].height = 5;
      }
     } 
   }
   else if (editor.typeSelected == 5){
      if(editor.transform == 1){
         deathbox[editor.indexSelected].x += mouse.dX/camera.scale;
         deathbox[editor.indexSelected].y += mouse.dY/camera.scale; 
      }
      else if (editor.transform == 0){
           deathbox[editor.indexSelected].width += mouse.dX/camera.scale;
           deathbox[editor.indexSelected].height += mouse.dY/camera.scale; 
      
      if(deathbox[editor.indexSelected].width <= 5){
         deathbox[editor.indexSelected].width = 5;
      }
      if(deathbox[editor.indexSelected].height <= 5){
         deathbox[editor.indexSelected].height = 5;
      }
     } 
    }
   }
  if(mouse.right){
    mouse.dX = mouse.x - mouse.oldX;
    mouse.dY = mouse.y - mouse.oldY;
    camera.x += mouse.dX;
    camera.y += mouse.dY;
    
  }
}


void FDrawObjects(){
  
   player[0].xDraw = player[0].x;
   player[0].yDraw = player[0].y;
   player[0].widthDraw = player[0].width;
   player[0].heightDraw = player[0].height;
   player[0].widthDraw  *= camera.scale;
   player[0].heightDraw *= camera.scale;
   player[0].xDraw += camera.x;
   player[0].yDraw += camera.y;
   player[0].xDraw = gameWidth/2 + (player[0].xDraw - gameWidth/2) * camera.scale;
   player[0].yDraw = gameHeight/2 + (player[0].yDraw - gameHeight/2) * camera.scale;
   
   
   SDL_RenderCopyEx(renderer,tex_player,&(SDL_Rect){2,24,15,18},&(SDL_Rect){player[0].xDraw,player[0].yDraw,player[0].widthDraw,player[0].heightDraw},0,NULL,SDL_FLIP_NONE);


   for (int i = 1;i<sizeof(platforms)/sizeof(platforms[0]);i++){
      if(platforms[i].reserved){
         // Camera offsetted data !
         platforms[i].xDraw = platforms[i].x;
         platforms[i].yDraw = platforms[i].y;
         platforms[i].widthDraw = platforms[i].width*camera.scale;
         platforms[i].heightDraw = platforms[i].height*camera.scale;
         platforms[i].xDraw  += camera.x;
         platforms[i].yDraw  += camera.y;
         platforms[i].xDraw  = gameWidth/2 + (platforms[i].xDraw - gameWidth/2) * camera.scale;
         platforms[i].yDraw  = gameHeight/2 + (platforms[i].yDraw - gameHeight/2) * camera.scale;


         
         SDL_SetRenderDrawColor(renderer,200,200,200,255);
         FtexturePlatform(i);
         
         
         
         if(editor.selected && editor.typeSelected == 1 && editor.indexSelected == i){ 
            if(platforms[i].moveModule >= 1){
            SDL_SetRenderDrawColor(renderer,200,200,200,255);
            SDL_RenderDrawLine(renderer,platforms[i].xDraw+platforms[i].widthDraw/2,platforms[i].yDraw+platforms[i].heightDraw/2,platforms[i].xDraw+platforms[i].widthDraw/2+camera.scale*platforms[i].moveModule*cos(platforms[i].moveAngle*(2*PI)/360),platforms[i].yDraw+platforms[i].heightDraw/2+camera.scale*platforms[i].moveModule*sin(platforms[i].moveAngle*(2*PI)/360));

            SDL_RenderDrawRect(renderer,&(SDL_Rect){platforms[i].xDraw+platforms[i].widthDraw/2+camera.scale*platforms[i].moveModule*cos(platforms[i].moveAngle*(2*PI)/360)-10/2*camera.scale,platforms[i].yDraw+platforms[i].heightDraw/2+camera.scale*platforms[i].moveModule*sin(platforms[i].moveAngle*(2*PI)/360)-10/2*camera.scale,10*camera.scale,10*camera.scale});
         }
         SDL_SetRenderDrawColor(renderer,0,255,0,255);
         SDL_RenderDrawRect(renderer,&(SDL_Rect){platforms[editor.indexSelected].xDraw,platforms[editor.indexSelected].yDraw-(platforms[editor.indexSelected].heightDraw*sin(platforms[editor.indexSelected].slope))*(platforms[editor.indexSelected].slope>=0),platforms[editor.indexSelected].widthDraw,platforms[editor.indexSelected].heightDraw+(platforms[editor.indexSelected].heightDraw*sin(platforms[editor.indexSelected].slope))*(platforms[editor.indexSelected].slope>=0)});
         }
         
                 
      }
   }

   for (int i = 0;i<sizeof(deathbox)/sizeof(deathbox[0]);i++){
      if(deathbox[i].reserved){
         // Camera offsetted data !
         deathbox[i].xDraw = deathbox[i].x;
         deathbox[i].yDraw = deathbox[i].y;
         deathbox[i].widthDraw = deathbox[i].width*camera.scale;
         deathbox[i].heightDraw = deathbox[i].height*camera.scale;
         deathbox[i].xDraw  += camera.x;
         deathbox[i].yDraw  += camera.y;
         deathbox[i].xDraw  = gameWidth/2 + (deathbox[i].xDraw - gameWidth/2) * camera.scale;
         deathbox[i].yDraw  = gameHeight/2 + (deathbox[i].yDraw - gameHeight/2) * camera.scale;

         FtextureQuad(deathbox[i].xDraw,deathbox[i].yDraw,deathbox[i].widthDraw,deathbox[i].heightDraw,tex_skull,min(deathbox[i].opacity+25,255),0);   

         if(editor.selected && editor.typeSelected == 5 && editor.indexSelected == i){ 
         SDL_SetRenderDrawColor(renderer,0,255,0,255);
         SDL_RenderDrawRect(renderer,&(SDL_Rect){deathbox[editor.indexSelected].xDraw,deathbox[editor.indexSelected].yDraw,deathbox[editor.indexSelected].widthDraw,deathbox[editor.indexSelected].heightDraw});          
      }
   }
   }

   for (int i = 0;i<sizeof(triggers)/sizeof(triggers[0]);i++){
      if(triggers[i].reserved){
         // Camera offsetted data !
        triggers[i].xDraw = triggers[i].x;
        triggers[i].yDraw = triggers[i].y;
        triggers[i].widthDraw = triggers[i].width*camera.scale;
        triggers[i].heightDraw = triggers[i].height*camera.scale;
        triggers[i].xDraw  += camera.x;
        triggers[i].yDraw  += camera.y;
        triggers[i].xDraw  = gameWidth/2 + (triggers[i].xDraw - gameWidth/2) * camera.scale;
        triggers[i].yDraw  = gameHeight/2 + (triggers[i].yDraw - gameHeight/2) * camera.scale;
         
          FtextureQuad(triggers[i].xDraw,triggers[i].yDraw,triggers[i].widthDraw,triggers[i].heightDraw,tex_trigger,min(triggers[i].opacity+25,255),0);


         if(editor.selected && editor.typeSelected == 2 && editor.indexSelected == i){ 
         SDL_SetRenderDrawColor(renderer,0,255,0,255);
         SDL_RenderDrawRect(renderer,&(SDL_Rect){triggers[editor.indexSelected].xDraw,triggers[editor.indexSelected].yDraw,triggers[editor.indexSelected].widthDraw,triggers[editor.indexSelected].heightDraw});
         }
      }
   }

   for (int i = 0;i<sizeof(displacement)/sizeof(displacement[0]);i++){
      if(displacement[i].reserved){
         // Camera offsetted data !
        displacement[i].xDraw = displacement[i].x;
        displacement[i].yDraw = displacement[i].y;
        displacement[i].widthDraw = displacement[i].width*camera.scale;
        displacement[i].heightDraw = displacement[i].height*camera.scale;
        displacement[i].xDraw  += camera.x;
        displacement[i].yDraw  += camera.y;
        displacement[i].xDraw  = gameWidth/2 + (displacement[i].xDraw - gameWidth/2) * camera.scale;
        displacement[i].yDraw  = gameHeight/2 + (displacement[i].yDraw - gameHeight/2) * camera.scale;
         
         FtextureQuad(displacement[i].xDraw,displacement[i].yDraw,displacement[i].widthDraw,displacement[i].heightDraw,tex_displacement,min(displacement[i].opacity+25,255),displacement[i].type);

         if(editor.selected && editor.typeSelected == 4 && editor.indexSelected == i){ 
         SDL_SetRenderDrawColor(renderer,0,255,0,255);
         SDL_RenderDrawRect(renderer,&(SDL_Rect){displacement[editor.indexSelected].xDraw,displacement[editor.indexSelected].yDraw,displacement[editor.indexSelected].widthDraw,displacement[editor.indexSelected].heightDraw});
         }
      }
   }

   for(int i = 0;i<sizeof(light)/sizeof(light[0]);i++){
      if(light[i].reserved){
         light[i].xDraw = light[i].x;
         light[i].yDraw = light[i].y;
         light[i].sizeDraw = light[i].size*camera.scale;
         light[i].xDraw  += camera.x;
         light[i].yDraw  += camera.y;
         light[i].xDraw  = gameWidth/2 + (light[i].xDraw - gameWidth/2) * camera.scale;
         light[i].yDraw  = gameHeight/2 + (light[i].yDraw - gameHeight/2) * camera.scale;
         SDL_SetTextureAlphaMod(tex_bulb,50);
         SDL_RenderCopy(renderer,tex_bulb,NULL,&(SDL_Rect){light[i].xDraw+light[i].sizeDraw/2-min(30,light[i].sizeDraw)/2,light[i].yDraw+light[i].sizeDraw/2-min(30,light[i].sizeDraw)/2,min(30,light[i].sizeDraw),min(30,light[i].sizeDraw)});
         SDL_SetTextureAlphaMod(tex_bulb,255);
         if(editor.selected && editor.typeSelected == 3 && editor.indexSelected == i){ 
         SDL_SetRenderDrawColor(renderer,0,255,0,255);
         SDL_RenderDrawRect(renderer,&(SDL_Rect){light[editor.indexSelected].xDraw,light[editor.indexSelected].yDraw,light[editor.indexSelected].sizeDraw,light[editor.indexSelected].sizeDraw});
         }
      }
   }
   if(editor.selected && editor.typeSelected == 0){
      SDL_SetRenderDrawColor(renderer,0,255,0,255);
      SDL_RenderDrawRect(renderer,&(SDL_Rect){player[0].xDraw,player[0].yDraw,player[0].widthDraw,player[0].heightDraw});
   }
}