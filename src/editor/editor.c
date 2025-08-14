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

char* infoTextMessages[] = {
   "Add Platform",
   "Translate",
   "Resize",
   "Save Map",
   "Save Map As",
   "Delete Object",
   "Load Map",
   "Change Texture",
   "Inverse Slope",
   "Copy Object",
   "Load New Map",
   "Map Settings",
   "Add Trigger",
   "Add Finish Line",
   "Add Checkpoint",
   "Zoom In",
   "Zoom Out",
   "Texture Stretch",
   "Change Background",
   "Add Light",
   "Add Displacement Block",
   "Change Displacement Direction",
   "Change Displacement Type",
   "Add DeathBox",
   "Toggle Collidable",
   "Add Move Node",
   "Add Node",
   "Remove Node",
   "Wrap Nodes",
   "Trigger Type",
   "Add Script Block",
   "Change Name",
   "Change Light",
   "Add Enemy",
   "Add Special",
   "Change Special",
   "Add TextBox",
   "Set Text",
   "Change Texture Rotation",
   "Toggle Finish Animation"
};

char* knobInfoText[] = {
      "Change Texture Scale\0",
      "None\0",
      "None\0",
      "Change Border X\0",
      "Change Border Y\0",
      "Change Animation Speed\0",
      "Change Star Time Ms\0",
      "Change Star Time\0",
      "Change Node ID\0",
      "Change Move Speed\0",
      "Change Object ID\0",
      "Change Use Time Delay",
      "Change Reuse Time Delay",
      "Change Text X Coordinate",
      "Change Text Y Coordinate",
      "Change Text Font",
      "Change Unit",
      "Change Unit2",
      "Change Unit3",
      "Change Unit3",
      "Change Unit3"

};

char* sliderInfoText[] = {
      "Change Slope\0",
      "Change Texture Offset X\0",
      "Change Texture Offset Y\0",
      "Change Texture Scale\0",
      "Change Map Border X\0",
      "Change Map Border Y\0",
      "Change Map Light\0",
      "Change Light Rotation\0",
      "Change Light Brightness\0",
      "Change Light Visibility\0",
      "Change Red Value\0",
      "Change Green Value\0",
      "Change Blue Value\0",
      "Change Displacement Power\0",
      "Change Opacity\0",
      "Change Camera Zoom\0",
      "Change Max Speed",
      "Change Enemy Health"

};

char* specialTypes_Array[] = {
         "Slash",
         "Wings",
         "Double Jump",
         "Dash",
         "Arrow",
         "Projectile",
         "Grapple"
};

char* displacement_directionTypes[] = {
      "Right",
      "Up",
      "Left",
      "Down"
};

char* displacement_powerTypes[] = {
      "Velocity",
      "Accelerate"
};


void FUpdate_Editor(){
     // Calculate mouse coordinates in the projected world
     editor.mouseProjected[0] = (mouse.x-gameWidth/2)/camera.scale + gameWidth/2 - camera.x;
     editor.mouseProjected[1] = (mouse.y-gameHeight/2)/camera.scale + gameHeight/2 - camera.y;
      
     // Update Selection
     if(player[0].editorSelectionTime <= 1000){
      player[0].editorSelectionTime += 1000*app.deltaTime;
     }
     for(int i = 1;i<sizeof(platforms)/sizeof(platforms[0]);i++){
      if(platforms[i].reserved && platforms[i].editorSelectionTime <= 1000){
         platforms[i].editorSelectionTime += 1000*app.deltaTime;
      }
     }
     // Update Alerts
     if(editor.alertTimer > 0){
      editor.alertTimer -= 1000*app.deltaTime;
     }

     if(editor.status < 0){
      FTransformState();
     }

     // Update Selection Timer for each object
     for(int i = 0;i<sizeof(deathbox)/sizeof(deathbox[0]);i++){
      if(deathbox[i].reserved && deathbox[i].editorSelectionTime <= 1000){
         deathbox[i].editorSelectionTime += 1000*app.deltaTime;
      }
      if(deathbox[i].moveNodeInt >= 0 && movenodes[deathbox[i].moveNodeInt].reserved){
         deathbox[i].x = movenodes[deathbox[i].moveNodeInt].positions[0][0]-(deathbox[i].width-25)/2;
         deathbox[i].y = movenodes[deathbox[i].moveNodeInt].positions[0][1]-(deathbox[i].height-25)/2;
      }
     }
     for(int i = 0;i<sizeof(light)/sizeof(light[0]);i++){
      if(light[i].reserved && light[i].editorSelectionTime <= 1000){
         light[i].editorSelectionTime += 1000*app.deltaTime;
      }
      if(light[i].moveNodeInt >= 0 && movenodes[light[i].moveNodeInt].reserved){
         light[i].x = movenodes[light[i].moveNodeInt].positions[0][0]-(light[i].width-25)/2;
         light[i].y = movenodes[light[i].moveNodeInt].positions[0][1]-(light[i].height-25)/2;
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
      if(displacement[i].moveNodeInt >= 0 && movenodes[displacement[i].moveNodeInt].reserved){
         displacement[i].x = movenodes[displacement[i].moveNodeInt].positions[0][0]-(displacement[i].width-25)/2;
         displacement[i].y = movenodes[displacement[i].moveNodeInt].positions[0][1]-(displacement[i].height-25)/2;
      }
     }
     for(int i = 0;i<sizeof(movenodes)/sizeof(movenodes[0]);i++){
      if(movenodes[i].reserved && movenodes[i].editorSelectionTime <= 1000){
         movenodes[i].editorSelectionTime += 1000*app.deltaTime;
      }
     }
      for(int i = 0;i<sizeof(scripts)/sizeof(scripts[0]);i++){
        if(scripts[i].reserved && scripts[i].editorSelectionTime <= 1000){
         scripts[i].editorSelectionTime += 1000*app.deltaTime;
        }
     }
     for(int i = 0;i<sizeof(enemy)/sizeof(enemy[0]);i++){
      if(enemy[i].reserved && enemy[i].editorSelectionTime <= 1000){
         enemy[i].editorSelectionTime += 1000*app.deltaTime;
      }
     }
     for(int i = 0;i<sizeof(specials)/sizeof(specials[0]);i++){
      if(specials[i].reserved && specials[i].editorSelectionTime <= 1000){
         specials[i].editorSelectionTime += 1000*app.deltaTime;
      }
     }
     for(int i = 0;i<sizeof(textpopups)/sizeof(textpopups[0]);i++){
      if(textpopups[i].reserved && textpopups[i].editorSelectionTime <= 1000){
         textpopups[i].editorSelectionTime += 1000*app.deltaTime;
      }
     }
    // Update Selection
    

    // Update Camera (Makes it smoother)
    camera.scale += (camera.scaleReal - camera.scale)*app.deltaTime*5;
   
   if(mouse.wheel == 1){
      camera.scaleReal *= 1.2;
      camera.scaleReal = min(4,camera.scaleReal);
   }
   else if (mouse.wheel == -1){
      camera.scaleReal /= 1.2;
      camera.scaleReal = max(0.5,camera.scaleReal);
   }
   

   // Change texture platform (Animate)
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
         
      if(platforms[i].moveNodeInt >= 0 && movenodes[platforms[i].moveNodeInt].reserved){
         platforms[i].x = movenodes[platforms[i].moveNodeInt].positions[0][0]-(platforms[i].width-25)/2;
         platforms[i].y = movenodes[platforms[i].moveNodeInt].positions[0][1]-(platforms[i].height-25)/2;
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
      if(mouse.x >= xMin && mouse.x <= xMax && mouse.y >= yMin && mouse.y <= yMax && (mouse.left == -1 || mouse.right == -1)){
       if(i == 0){
         addPlatform(gameWidth/2-camera.x,gameHeight/2-camera.y,25,25,0,false,FindTextureInt("stone"),0,knobs[0].knobValue,0,0,false,true,255,0,255,255,255);
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
       else if (i == 3){
         if(editor.mapNameSet){
            FSaveMap(editor.mapName);
         }
         else{
            sprintf(editor.alertText,"No map name is loaded");
            editor.alertTimer = 5000;
         }
       }
       else if (i == 4){
         SetTextBox(false,0,"Map Name:",45,150,15,450);
         textbox[0].textContentSize = 0;
         textbox[0].textContent[0] = '\0';
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
         else if (editor.typeSelected == 6){
            movenodes[editor.indexSelected].reserved = false;
         }
         else if (editor.typeSelected == 7){
            scripts[editor.indexSelected].reserved = false;
         }
         else if (editor.typeSelected == 8){
            enemy[editor.indexSelected].reserved = false;
         }
         else if (editor.typeSelected == 9){
            specials[editor.indexSelected].reserved = false;
         }
         else if (editor.typeSelected == 10){
            textpopups[editor.indexSelected].reserved = false;
         }
         editor.selected = false;
         editorShowButtons();
       }
       else if (i == 6){
         SetTextBox(false,0,"Map Name:",45,150,15,450);
         textbox[0].textContentSize = 0;
         textbox[0].textContent[0] = '\0';
         editor.status = 1;
         editorShowButtons();
       }
       else if (i == 7 && editor.selected){
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
       else if (i == 8){
         platforms[editor.indexSelected].slopeInv = !platforms[editor.indexSelected].slopeInv;
       }
       else if (i == 9){
         // Copy Object
         if(editor.typeSelected == 1){
            if(platforms[editor.indexSelected].type == 0){
               addPlatform(gameWidth/2-camera.x,gameHeight/2-camera.y,platforms[editor.indexSelected].width,platforms[editor.indexSelected].height,platforms[editor.indexSelected].slope,platforms[editor.indexSelected].slopeInv,platforms[editor.indexSelected].textureInt,0,platforms[editor.indexSelected].textureScale,platforms[editor.indexSelected].textureOffsetX,platforms[editor.indexSelected].textureOffsetY,platforms[editor.indexSelected].textureStretch,platforms[editor.indexSelected].collidable,platforms[editor.indexSelected].opacity,platforms[editor.indexSelected].textureAnimationTime,platforms[editor.indexSelected].red,platforms[editor.indexSelected].green,platforms[editor.indexSelected].blue);
            }
            else if (platforms[editor.indexSelected].type == 1){
               addPlatform(gameWidth/2-camera.x,gameHeight/2-camera.y,platforms[editor.indexSelected].width,platforms[editor.indexSelected].height,platforms[editor.indexSelected].slope,platforms[editor.indexSelected].slopeInv,platforms[editor.indexSelected].textureInt,1,platforms[editor.indexSelected].textureScale,platforms[editor.indexSelected].textureOffsetX,platforms[editor.indexSelected].textureOffsetY,platforms[editor.indexSelected].textureStretch,platforms[editor.indexSelected].collidable,platforms[editor.indexSelected].opacity,platforms[editor.indexSelected].textureAnimationTime,platforms[editor.indexSelected].red,platforms[editor.indexSelected].green,platforms[editor.indexSelected].blue);
            }
            else if (platforms[editor.indexSelected].type == 2){
               addPlatform(gameWidth/2-camera.x,gameHeight/2-camera.y,platforms[editor.indexSelected].width,platforms[editor.indexSelected].height,platforms[editor.indexSelected].slope,platforms[editor.indexSelected].slopeInv,platforms[editor.indexSelected].textureInt,2,platforms[editor.indexSelected].textureScale,platforms[editor.indexSelected].textureOffsetX,platforms[editor.indexSelected].textureOffsetY,platforms[editor.indexSelected].textureStretch,platforms[editor.indexSelected].collidable,platforms[editor.indexSelected].opacity,platforms[editor.indexSelected].textureAnimationTime,platforms[editor.indexSelected].red,platforms[editor.indexSelected].green,platforms[editor.indexSelected].blue);
            }

         }
         else if (editor.typeSelected == 2){
           addTrigger(gameWidth/2-camera.x,gameHeight/2-camera.y,triggers[i].width,triggers[i].height,triggers[i].triggerType,triggers[i].opacity,triggers[i].Value1,triggers[i].Value2,triggers[i].Value3,triggers[i].Value4); 
         }
         else if (editor.typeSelected == 3){
            addLight(gameWidth/2-camera.x,gameHeight/2-camera.y,light[editor.indexSelected].width,light[editor.indexSelected].height,light[editor.indexSelected].red,light[editor.indexSelected].green,light[editor.indexSelected].blue,light[editor.indexSelected].visibility,light[editor.indexSelected].brightness,light[editor.indexSelected].moveSpeed,light[editor.indexSelected].lightInt);
         }
         else if (editor.typeSelected == 4){
            addDisplacement(gameWidth/2-camera.x,gameHeight/2-camera.y,displacement[editor.indexSelected].width,displacement[editor.indexSelected].height,displacement[editor.indexSelected].type,displacement[editor.indexSelected].power,displacement[editor.indexSelected].powerType,displacement[editor.indexSelected].opacity);
         }
         else if (editor.typeSelected == 5){
            addDeathBox(gameWidth/2-camera.x,gameHeight/2-camera.y,deathbox[editor.indexSelected].width,deathbox[editor.indexSelected].height,deathbox[editor.indexSelected].opacity);
         }
         else if (editor.typeSelected == 7){
            addScript(gameWidth/2-camera.x,gameHeight/2-camera.y,scripts[editor.indexSelected].width,scripts[editor.indexSelected].height);
         }
         else if (editor.typeSelected == 8){
            addEnemy(gameWidth/2-camera.x,gameHeight/2-camera.y,enemy[editor.indexSelected].width,enemy[editor.indexSelected].height);
         }
         else if (editor.typeSelected == 9){
            addSpecial(gameWidth/2-camera.x,gameHeight/2-camera.y,specials[editor.indexSelected].size,specials[editor.indexSelected].type);
         }
         else if (editor.typeSelected == 10){
            addTextPopUp(gameWidth/2-camera.x,gameHeight/2-camera.y,textpopups[editor.indexSelected].width,textpopups[editor.indexSelected].height);
         }
         
       }
       else if (i == 10){
         // nothin
       }
       else if (i == 11){
         editor.typeSelected = -1;
         editor.selected = true;
         sliders[6].sliderValue = app.backgroundOpacity;
         sliders[15].sliderValue = editor.GameScale*100;
         knobs[3].knobValue = mapData.xMax;
         knobs[4].knobValue = mapData.yMax;
         
         editorShowButtons();
       }
       else if (i == 12){
         addTrigger(gameWidth/2-camera.x,gameHeight/2-camera.y,25,25,0,255,-1,0,0,0);
       }
       else if (i == 13){
         addPlatform(gameWidth/2-camera.x,gameHeight/2-camera.y,25,25,0,false,-1,1,50,0,0,false,true,255,0,255,255,255);
         
        }
       else if (i == 14){
         addPlatform(gameWidth/2-camera.x,gameHeight/2-camera.y,25,25,0,false,-1,2,50,0,0,false,true,255,0,255,255,255);
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
         addLight(gameWidth/2-camera.x,gameHeight/2-camera.y,25.0f,25.0f,255,255,255,255,100,0,0);
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
       else if (i == 25){
         addMoveNode(gameWidth/2-camera.x,gameHeight/2-camera.y);
       }
       else if (i == 26){
         if(movenodes[editor.indexSelected].nodesCount < 20){
            movenodes[editor.indexSelected].nodesCount++;
            movenodes[editor.indexSelected].positions[movenodes[editor.indexSelected].nodesCount-1][0] =  gameWidth/2-camera.x;
            movenodes[editor.indexSelected].positions[movenodes[editor.indexSelected].nodesCount-1][1] =  gameHeight/2-camera.y;
            editor.movenodeSelected = movenodes[editor.indexSelected].nodesCount - 1;
         }
         
       }
       else if (i == 27){
         if(movenodes[editor.indexSelected].nodesCount > 1){
          movenodes[editor.indexSelected].nodesCount--;
          editor.movenodeSelected = movenodes[editor.indexSelected].nodesCount - 1;
         }   
       }
       else if (i == 28){
         movenodes[editor.indexSelected].wrap = !movenodes[editor.indexSelected].wrap;
       }
       else if (i == 29){
         triggers[editor.indexSelected].triggerType++;
         triggers[editor.indexSelected].triggerType %= 4;
       }
       else if (i == 30){
         addScript(gameWidth/2-camera.x,gameHeight/2-camera.y,25.0f,25.0f);
       }
       else if (i == 31){
         if(mouse.right == -1){
            if(scripts[editor.indexSelected].scriptInt > 0){
               scripts[editor.indexSelected].scriptInt--;
            }
         }
         else
         {
            scripts[editor.indexSelected].scriptInt++;
            if (scripts[editor.indexSelected].scriptInt < 50 && !scriptfiles[scripts[editor.indexSelected].scriptInt].reserved){
            scripts[editor.indexSelected].scriptInt = 0;
         }
         }
       }
       else if (i == 32){
         if(mouse.left == -1){
            light[editor.indexSelected].lightInt++;
           if(light[editor.indexSelected].lightInt > 50 || !lightTextures[light[editor.indexSelected].lightInt].reserved){
              light[editor.indexSelected].lightInt = 0;
           }
         }
         else if(mouse.right == -1){
            if(light[editor.indexSelected].lightInt > 0){
               light[editor.indexSelected].lightInt--;
            }
         }
       }
       else if (i == 33){
         addEnemy(gameWidth/2-camera.x,gameHeight/2-camera.y,20,20);
       }
       else if (i == 34){
         addSpecial(gameWidth/2-camera.x,gameHeight/2-camera.y,18,1);
       }
       else if (i == 35){
         if(mouse.left == -1){
            specials[editor.indexSelected].type++;
         if(specials[editor.indexSelected].type > 7){
            specials[editor.indexSelected].type = 1;
         }
         }
         else if (mouse.right == -1){
            if(specials[editor.indexSelected].type > 1){
               specials[editor.indexSelected].type--;
            }  
         }
       }
       else if(i == 36){
         addTextPopUp(gameWidth/2-camera.x,gameHeight/2-camera.y,25,25);
       }
       else if(i == 37){
         
         SetTextBox(false,0,"Text:",45,150,15,450);
         int textLength = len(textpopups[editor.indexSelected].textContent);
         SDL_memcpy(textbox[0].textContent,textpopups[editor.indexSelected].textContent,textLength);
         textbox[0].textContentSize = textLength;
         textbox[0].textContent[textLength] = '\0';
         editor.status = 2;
         editorShowButtons();

       }
       else if(i == 38){
         if(mouse.left == -1){
         platforms[editor.indexSelected].textureRotation++;
         platforms[editor.indexSelected].textureRotation %= 4;
         }
       }
       else if(i == 39){
         platforms[editor.indexSelected].NofinishAnimation = !platforms[editor.indexSelected].NofinishAnimation;
       }
       else if(i == 40){
         platforms[editor.indexSelected].grapplable = !platforms[editor.indexSelected].grapplable;
       }
       mouse.left = 0;
       mouse.right = 0;
      }
    }
   }
   if(mouse.left == -1){
      if(editor.status < 0){
        FCheck_Select_Editor(); 
      }
     Set_KnobValues();
     Set_SlidersValues();
     editorShowButtons();     
   }
   
 if(editor.typeSelected == 1){
   platforms[editor.indexSelected].textureOffsetX = sliders[1].sliderValue;
   platforms[editor.indexSelected].textureOffsetY = sliders[2].sliderValue;
   platforms[editor.indexSelected].textureScale = knobs[0].knobValue;
   platforms[editor.indexSelected].moveNodeInt = knobs[8].knobValue;
   platforms[editor.indexSelected].moveSpeed = knobs[9].knobValue;
   platforms[editor.indexSelected].textureOffsetX_Move = knobs[16].knobValue;
   platforms[editor.indexSelected].textureOffsetY_Move = knobs[17].knobValue;
   if(platforms[editor.indexSelected].type == 0){
   platforms[editor.indexSelected].slope = sliders[0].sliderValue/(180/(2*PI)); 
  }
  platforms[editor.indexSelected].opacity = sliders[14].sliderValue;

  platforms[editor.indexSelected].textureAnimationTime = knobs[5].knobValue;
  if(platforms[editor.indexSelected].type == 0){
    platforms[editor.indexSelected].red = sliders[10].sliderValue;
    platforms[editor.indexSelected].green = sliders[11].sliderValue;
    platforms[editor.indexSelected].blue = sliders[12].sliderValue;
  }
  else {
    platforms[editor.indexSelected].red = 255;
    platforms[editor.indexSelected].green = 255;
    platforms[editor.indexSelected].blue = 255  ;
  }
  
 }
 else if (editor.typeSelected == -1){
   mapData.xMin = -knobs[3].knobValue;
   mapData.xMax = knobs[3].knobValue;
   mapData.yMin = -knobs[4].knobValue;
   mapData.yMax = knobs[4].knobValue;
   editor.StarTime = knobs[7].knobValue;
   editor.StarTimeMs = knobs[6].knobValue;
   editor.gridMove = knobs[19].knobValue;
   app.backgroundOpacity = sliders[6].sliderValue;
   editor.GameScale = sliders[15].sliderValue/100;
   
 }
 else if (editor.typeSelected == 2){
   triggers[editor.indexSelected].opacity = sliders[14].sliderValue;
   triggers[editor.indexSelected].Value1 = knobs[8].knobValue;
   triggers[editor.indexSelected].Value2 = knobs[9].knobValue;
   triggers[editor.indexSelected].Value3 = knobs[10].knobValue;
   triggers[editor.indexSelected].useDelay = knobs[11].knobValue;
   triggers[editor.indexSelected].reuseDelay = knobs[12].knobValue;

 }
 else if (editor.typeSelected == 3){
   light[editor.indexSelected].rotation = sliders[7].sliderValue;
   light[editor.indexSelected].brightness = sliders[8].sliderValue;
   light[editor.indexSelected].visibility = sliders[9].sliderValue;
   light[editor.indexSelected].moveNodeInt = knobs[8].knobValue;
   light[editor.indexSelected].moveSpeed = knobs[9].knobValue;
   light[editor.indexSelected].red = sliders[10].sliderValue;
   light[editor.indexSelected].green = sliders[11].sliderValue;
   light[editor.indexSelected].blue = sliders[12].sliderValue;
 }
 else if (editor.typeSelected  == 4){
   displacement[editor.indexSelected].power = sliders[13].sliderValue; 
   displacement[editor.indexSelected].opacity = sliders[14].sliderValue;
   displacement[editor.indexSelected].moveNodeInt = knobs[8].knobValue;
   displacement[editor.indexSelected].moveSpeed = knobs[9].knobValue;
 }
 else if (editor.typeSelected  == 5){
   deathbox[editor.indexSelected].opacity = sliders[14].sliderValue;
   deathbox[editor.indexSelected].moveNodeInt = knobs[8].knobValue;
   deathbox[editor.indexSelected].moveSpeed = knobs[9].knobValue;

 }
 else if(editor.typeSelected == 7){
   scripts[editor.indexSelected].useDelay = knobs[11].knobValue;
   scripts[editor.indexSelected].reuseDelay = knobs[12].knobValue;
 }
 else if(editor.typeSelected == 8){
   enemy[editor.indexSelected].maxSpeed = sliders[16].sliderValue;
   enemy[editor.indexSelected].maxHealth = sliders[17].sliderValue;
   enemy[editor.indexSelected].type = knobs[18].knobValue;
 }
 else if(editor.typeSelected == 10){
   textpopups[editor.indexSelected].xPopup = knobs[13].knobValue;
   textpopups[editor.indexSelected].yPopup = knobs[14].knobValue;
   textpopups[editor.indexSelected].font = knobs[15].knobValue;
 }

   
     Update_Slider();
     Update_Knobs();
     Update_TextBox(); 
     
    
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
   buttons[25].reserved = true;
   buttons[30].reserved = true;
   buttons[33].reserved = true;
   buttons[34].reserved = true;
   buttons[36].reserved = true;
   buttons[3].reserved = true;
   if(editor.status >= 0){
      textbox[0].reserved = true;
   }

   if(editor.selected){
      
      if(editor.typeSelected == -1){
        knobs[3].reserved = true;
        knobs[4].reserved = true;
        knobs[6].reserved = true;
        knobs[7].reserved = true;
        sliders[6].reserved = true;
        buttons[18].reserved = true;
        knobs[19].reserved = true;
        sliders[15].reserved = true;
        return;
      } 
      buttons[1].reserved = true;
      buttons[2].reserved = true;
      buttons[5].reserved = true; 
      if(editor.typeSelected != 6){
        
        buttons[9].reserved = true;  
      }
      

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
         knobs[8].reserved = true;
         knobs[9].reserved = true;
         knobs[16].reserved = true;
         knobs[17].reserved = true;
         buttons[40].reserved = true;
         
         
         if(platforms[editor.indexSelected].type == 0){

         sliders[0].reserved = true;
         buttons[7].reserved = true;
         buttons[8].reserved = true;
         sliders[10].reserved = true;
         sliders[11].reserved = true;
         sliders[12].reserved = true;
         buttons[38].reserved = true;
         
         ChangeSliderPosition(1,sliders[1].x,260);
         ChangeSliderPosition(2,sliders[2].x,280);
         ChangeKnobPosition(0,knobs[0].x,240);
         ChangeSliderPosition(10,sliders[10].x,380);
         ChangeSliderPosition(11,sliders[11].x,400);
         ChangeSliderPosition(12,sliders[12].x,420);
         ChangeButtonPosition(24,buttons[24].x,300);
         ChangeButtonPosition(17,buttons[17].x,320);
         ChangeKnobPosition(5,knobs[5].x,360);
         
         ChangeKnobPosition(8,knobs[8].x,440);
         ChangeKnobPosition(9,knobs[9].x,460);
        

         }
         else if(platforms[editor.indexSelected].type == 1 || platforms[editor.indexSelected].type == 2){
            buttons[39].reserved = true;
            ChangeSliderPosition(1,sliders[1].x,180);
            ChangeSliderPosition(2,sliders[2].x,200);
            ChangeKnobPosition(0,knobs[0].x,220); 
            ChangeButtonPosition(17,buttons[17].x,240); 
            ChangeButtonPosition(24,buttons[24].x,260);
            ChangeSliderPosition(14,sliders[14].x,280);
            
            ChangeKnobPosition(5,knobs[5].x,300);
            
            ChangeKnobPosition(8,knobs[8].x,340);
            ChangeKnobPosition(9,knobs[9].x,360);
         }
      }
      else if (editor.typeSelected == 2){
       sliders[14].reserved = true;
       buttons[29].reserved = true;
       knobs[8].reserved = true;
       knobs[9].reserved = true;
       knobs[10].reserved = true;
       knobs[11].reserved = true;
       knobs[12].reserved = true;
       ChangeSliderPosition(14,sliders[14].x,220);
       ChangeKnobPosition(8,knobs[8].x,260);
       ChangeKnobPosition(9,knobs[9].x,280);
       ChangeKnobPosition(10,knobs[10].x,300);
      }
      else if (editor.typeSelected == 3){
         sliders[7].reserved = true;
         sliders[8].reserved = true;
         sliders[9].reserved = true;
         sliders[10].reserved = true;
         sliders[11].reserved = true;
         sliders[12].reserved = true;
         knobs[8].reserved = true;
         knobs[9].reserved = true;
         buttons[32].reserved = true;

         ChangeSliderPosition(10,sliders[10].x,260);
         ChangeSliderPosition(11,sliders[11].x,280);
         ChangeSliderPosition(12,sliders[12].x,300);
         ChangeKnobPosition(8,knobs[8].x,340);
         ChangeKnobPosition(9,knobs[9].x,360);
      }
      else if (editor.typeSelected == 4){
         buttons[21].reserved = true;
         buttons[22].reserved = true;
         sliders[13].reserved = true;
         sliders[14].reserved = true;
         knobs[8].reserved = true;
         knobs[9].reserved = true;
         ChangeSliderPosition(14,sliders[14].x,240);
         ChangeKnobPosition(8,knobs[8].x,300);
         ChangeKnobPosition(9,knobs[9].x,320);
      }
      else if (editor.typeSelected == 5){

          sliders[14].reserved = true;
          knobs[8].reserved = true;
          knobs[9].reserved = true;
        
         ChangeSliderPosition(14,sliders[14].x,220);
         
         ChangeKnobPosition(8,knobs[8].x,260);
         ChangeKnobPosition(8,knobs[8].x,300);
         ChangeKnobPosition(9,knobs[9].x,320);
         
      }
      else if (editor.typeSelected == 6){
         buttons[26].reserved = true;
         buttons[27].reserved = true;
         buttons[28].reserved = true;
      }
      else if (editor.typeSelected == 7){
         buttons[31].reserved = true;
         knobs[11].reserved = true;
         knobs[12].reserved = true;
      }
      else if (editor.typeSelected == 8){
         sliders[16].reserved = true;
         sliders[17].reserved = true;
         knobs[18].reserved = true;
      }
      else if (editor.typeSelected == 9){
         buttons[35].reserved = true; 
      }
      else if (editor.typeSelected == 10){
         buttons[37].reserved = true; 
         knobs[13].reserved = true;
         knobs[14].reserved = true;
         knobs[15].reserved = true;
      }
       
   }
}

void FDrawLoadSave(){

   
      
      SDL_SetRenderDrawColor(renderer,100,100,100,200);
      SDL_RenderFillRect(renderer,&(SDL_Rect){30,100,windowWidth-180,150});

      if(editor.status == 0){
      renderText(33,"Enter to save / Escape to cancel",45,210,33*12,15,255,200,(int[3]){255,255,255});
      }
      else if (editor.status == 1){
         renderText(33,"Enter to load / Escape to cancel",45,210,33*12,15,255,200,(int[3]){255,255,255});
      }
      else if (editor.status == 2){
         renderText(36,"Enter to Set Text / Escape to cancel",45,210,33*12,15,255,200,(int[3]){255,255,255});
      }
   
}


void FDraw_Editor(){  
    
   SDL_RenderClear(renderer);
   DrawBackground();
   SDL_SetRenderDrawColor(renderer,210,210,210,255);
   SDL_SetRenderDrawColor(renderer,200,0,0,100);
   
   FDrawObjects();
   // Draw Borders
   DrawLight(app.backgroundOpacity);
   SDL_SetRenderDrawColor(renderer,200,0,0,100);
   double xMin =  max(min(gameWidth/2 + (mapData.xMin + camera.x - gameWidth/2)*camera.scale,gameWidth),0);
   double yMin =  max(min(gameHeight/2 + (mapData.yMin + camera.y - gameHeight/2)*camera.scale,gameHeight),0);
   double xMax =  max(min(gameWidth/2 + (mapData.xMax + camera.x - gameWidth/2)*camera.scale,gameWidth),0);
   double yMax =  max(min(gameHeight/2 + (mapData.yMax + camera.y - gameHeight/2)*camera.scale,gameHeight),0);
   SDL_RenderFillRect(renderer,&(SDL_Rect){0,0,xMin,gameHeight});
   SDL_RenderFillRect(renderer,&(SDL_Rect){xMax,0,gameWidth-xMax,gameHeight});
   SDL_RenderFillRect(renderer,&(SDL_Rect){xMin,0,xMax-xMin,yMin});
   SDL_RenderFillRect(renderer,&(SDL_Rect){xMin,yMax,xMax-xMin,gameHeight-yMax});

 

    // HUD
   if(editor.status >= 0){
    FDrawLoadSave();
   }
   
   
   
   
   
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
   char CameraposX[15]; 
   char CameraposY[15];
   char CameraScale[15];
   sprintf(posX,"X:%d\0",(int)editor.mouseProjected[0]);
   sprintf(posY,"Y:%d\0",(int)editor.mouseProjected[1]);
   sprintf(CameraposX,"Cam X:%d\0",(int)-camera.x);
   sprintf(CameraposY,"Y:%d\0",(int)-camera.y);
   sprintf(CameraScale,"%d\0",(int)(camera.scale*100));
  
   renderText(len(posX),posX,5,gameHeight-14,len(posX)*7,15,255,200,(int[3]){255,255,255});
   renderText(len(posY),posY,len(posX)*7+15,gameHeight-14,len(posY)*7,15,255,200,(int[3]){255,255,255});
   renderText(len(CameraposX),CameraposX,5,gameHeight-30,len(CameraposX)*7,15,255,200,(int[3]){255,255,255});
   renderText(len(CameraposY),CameraposY,len(CameraposX)*7+15,gameHeight-30,len(CameraposY)*7,15,255,200,(int[3]){255,255,255});
   renderText(len(CameraScale),CameraScale,gameWidth-240,gameHeight-30,len(CameraposY)*7,15,255,200,(int[3]){255,255,255});
   // Render alert text
   if(editor.alertTimer > 0){
      int TextLength = len(editor.alertText);
      renderText(TextLength,editor.alertText,5,60,TextLength*12,17,255,255,(int[3]){255,255,255});
   }
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
            knobs[8].knobValue = platforms[editor.indexSelected].moveNodeInt;
            knobs[9].knobValue = platforms[editor.indexSelected].moveSpeed;
            sliders[14].sliderValue = platforms[editor.indexSelected].opacity;
            knobs[5].knobValue = platforms[editor.indexSelected].textureAnimationTime;
            sliders[10].sliderValue = platforms[editor.indexSelected].red;
            sliders[11].sliderValue = platforms[editor.indexSelected].green;
            sliders[12].sliderValue = platforms[editor.indexSelected].blue;
            knobs[16].knobValue = platforms[editor.indexSelected].textureOffsetX_Move;
            knobs[17].knobValue = platforms[editor.indexSelected].textureOffsetY_Move;
            
           
            
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
            knobs[8].knobValue = triggers[editor.indexSelected].Value1;
            knobs[9].knobValue = triggers[editor.indexSelected].Value2;
            knobs[10].knobValue = triggers[editor.indexSelected].Value3;
            knobs[11].knobValue = triggers[editor.indexSelected].useDelay;
            knobs[12].knobValue = triggers[editor.indexSelected].reuseDelay;
            
            return;
          }
         }
      }

      for(int i = 0;i<sizeof(displacement)/sizeof(displacement[0]);i++){
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
            knobs[8].knobValue = displacement[editor.indexSelected].moveNodeInt;
            knobs[9].knobValue = displacement[editor.indexSelected].moveSpeed;
           
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
            knobs[8].knobValue = deathbox[editor.indexSelected].moveNodeInt;
            knobs[9].knobValue = deathbox[editor.indexSelected].moveSpeed;
           
            return;
          }
         }
      }

      for(int i = 0;i<sizeof(light)/sizeof(light[0]);i++){
         if(light[i].reserved && light[i].editorSelectionTime >= 999){
            int xMin = light[i].xDraw;
            int xMax = light[i].xDraw+light[i].widthDraw;
            int yMin = light[i].yDraw;
            int yMax = light[i].yDraw+light[i].heightDraw;
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
            knobs[8].knobValue = light[editor.indexSelected].moveNodeInt;
            knobs[9].knobValue = light[editor.indexSelected].moveSpeed;
           
            return;
          }
         }
      }

      for(int i = 0;i<sizeof(movenodes)/sizeof(movenodes[0]);i++){
         if(movenodes[i].reserved && movenodes[i].editorSelectionTime >= 999){
          for(int j = 0;j<movenodes[i].nodesCount;j++){
            int xMin = movenodes[i].positionsDraw[j][0];
            int xMax = movenodes[i].positionsDraw[j][0]+25*camera.scale;
            int yMin = movenodes[i].positionsDraw[j][1];
            int yMax = movenodes[i].positionsDraw[j][1]+25*camera.scale;
         if(mouse.x >= xMin && mouse.x <= xMax && mouse.y >= yMin && mouse.y <= yMax){
            movenodes[i].editorSelectionTime = 0;
            editor.selected = true;
            editor.typeSelected = 6;
            editor.indexSelected = i;
            editor.movenodeSelected = j;
           
            return;
          }
          }
         }
      }
      for(int i = 0;i<sizeof(scripts)/sizeof(scripts[0]);i++){
         if(scripts[i].reserved && scripts[i].editorSelectionTime >= 999){
            int xMin = scripts[i].xDraw;
            int xMax = scripts[i].xDraw+scripts[i].widthDraw;
            int yMin = scripts[i].yDraw;
            int yMax = scripts[i].yDraw+scripts[i].heightDraw;
         if(mouse.x >= xMin && mouse.x <= xMax && mouse.y >= yMin && mouse.y <= yMax){
            scripts[i].editorSelectionTime = 0;
            editor.selected = true;
            editor.typeSelected = 7;
            editor.indexSelected = i;
           
            knobs[11].knobValue = scripts[editor.indexSelected].useDelay;
            knobs[12].knobValue = scripts[editor.indexSelected].reuseDelay;

            return;
          }
         }
      }
      for(int i = 0;i<sizeof(enemy)/sizeof(enemy[0]);i++){
         if(enemy[i].reserved && enemy[i].editorSelectionTime >= 999){
            int xMin = enemy[i].xDraw;
            int xMax = enemy[i].xDraw+enemy[i].widthDraw;
            int yMin = enemy[i].yDraw;
            int yMax = enemy[i].yDraw+enemy[i].heightDraw;
         if(mouse.x >= xMin && mouse.x <= xMax && mouse.y >= yMin && mouse.y <= yMax){
            enemy[i].editorSelectionTime = 0;
            editor.selected = true;
            editor.typeSelected = 8;
            editor.indexSelected = i;
            sliders[16].sliderValue = enemy[i].maxSpeed;
            sliders[17].sliderValue = enemy[i].maxHealth;
            knobs[18].knobValue = enemy[i].type;
           
            

            return;
          }
         }
      }
      for(int i = 0;i<sizeof(specials)/sizeof(specials[0]);i++){
         if(specials[i].reserved && specials[i].editorSelectionTime >= 999){
            int xMin = specials[i].xDraw;
            int xMax = specials[i].xDraw+specials[i].sizeDraw;
            int yMin = specials[i].yDraw;
            int yMax = specials[i].yDraw+specials[i].sizeDraw;
         if(mouse.x >= xMin && mouse.x <= xMax && mouse.y >= yMin && mouse.y <= yMax){
            specials[i].editorSelectionTime = 0;
            editor.selected = true;
            editor.typeSelected = 9;
            editor.indexSelected = i;
             
            return;
          }
         }
      }

      for(int i = 0;i<sizeof(textpopups)/sizeof(textpopups[0]);i++){
         if(textpopups[i].reserved && textpopups[i].editorSelectionTime >= 999){
            int xMin = textpopups[i].xDraw;
            int xMax = textpopups[i].xDraw+textpopups[i].widthDraw;
            int yMin = textpopups[i].yDraw;
            int yMax = textpopups[i].yDraw+textpopups[i].heightDraw;
         if(mouse.x >= xMin && mouse.x <= xMax && mouse.y >= yMin && mouse.y <= yMax){
            textpopups[i].editorSelectionTime = 0;
            editor.selected = true;
            editor.typeSelected = 10;
            editor.indexSelected = i;

            knobs[13].knobValue = textpopups[editor.indexSelected].xPopup;
            knobs[14].knobValue = textpopups[editor.indexSelected].yPopup;
            knobs[15].knobValue = textpopups[editor.indexSelected].font;
            
            
             
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
     SDL_itoa((int)platforms[editor.indexSelected].textureRotation,buttons[38].value,10);
     SDL_itoa((int)!platforms[editor.indexSelected].NofinishAnimation,buttons[39].value,10);
     SDL_itoa((int)platforms[editor.indexSelected].grapplable,buttons[40].value,10);
     if(platforms[editor.indexSelected].type == 0){
      sprintf(upperText,"Platform %d\0",editor.indexSelected);
     }
     else if(platforms[editor.indexSelected].type == 1){
      sprintf(upperText,"Finish %d\0",editor.indexSelected);
     }
     else if(platforms[editor.indexSelected].type == 2){
      sprintf(upperText,"Checkpoint %d\0",editor.indexSelected);
     }
   }
   else if (editor.typeSelected == 2){
     sprintf(Xvalue,"x:%d\0",(int)triggers[editor.indexSelected].x);
     sprintf(Yvalue,"y:%d\0",(int)triggers[editor.indexSelected].y);
     sprintf(Widthvalue,"width:%d\0",(int)triggers[editor.indexSelected].width);
     sprintf(Heightvalue,"height:%d\0",(int)triggers[editor.indexSelected].height); 
     sprintf(upperText,"%s\0","Trigger");

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
   else if (editor.typeSelected == 3){
     sprintf(Xvalue,"x:%d\0",(int)light[editor.indexSelected].x);
     sprintf(Yvalue,"y:%d\0",(int)light[editor.indexSelected].y);
     sprintf(Widthvalue,"width:%d\0",(int)light[editor.indexSelected].width);
     sprintf(Heightvalue,"height:%d\0",(int)light[editor.indexSelected].height);
     
     sprintf(upperText,"%s\0","Light");
     int NameSize = len(lightTextures[light[editor.indexSelected].lightInt].textureName);
     SDL_memcpy(buttons[32].value,lightTextures[light[editor.indexSelected].lightInt].textureName,NameSize+1);
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
    
    typeValue = displacement_directionTypes[displacement[editor.indexSelected].type];
    displaceValue = displacement_powerTypes[displacement[editor.indexSelected].powerType];
    
     
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
   else if (editor.typeSelected == 6){
      sprintf(Xvalue,"x:%d\0",(int)movenodes[editor.indexSelected].positions[editor.movenodeSelected][0]);
      sprintf(Yvalue,"y:%d\0",(int)movenodes[editor.indexSelected].positions[editor.movenodeSelected][1]);
      sprintf(Widthvalue,"size:%d\0",25);
      sprintf(Heightvalue,"Node ID:%d\0",editor.indexSelected);
      sprintf(upperText,"%s %d\0","Move Node",editor.movenodeSelected);
   }
   else if (editor.typeSelected == 7){
      sprintf(Xvalue,"x:%d\0",(int)scripts[editor.indexSelected].x);
      sprintf(Yvalue,"y:%d\0",(int)scripts[editor.indexSelected].y);
      sprintf(Widthvalue,"width:%d\0",(int)scripts[editor.indexSelected].width);
      sprintf(Heightvalue,"height:%d\0",(int)scripts[editor.indexSelected].height);
      sprintf(upperText,"%s\0","Script");
      if(scripts[editor.indexSelected].scriptInt >= 1){
         int NameSize = len(scriptfiles[scripts[editor.indexSelected].scriptInt].scriptName);
         SDL_memcpy(buttons[31].value,scriptfiles[scripts[editor.indexSelected].scriptInt].scriptName,NameSize+1);
      }
      else{
         SDL_memcpy(buttons[31].value,"None",5);
      }
      
   }
   else if (editor.typeSelected == 8){
      sprintf(Xvalue,"x:%d\0",(int)enemy[editor.indexSelected].x);
      sprintf(Yvalue,"y:%d\0",(int)enemy[editor.indexSelected].y);
      sprintf(Widthvalue,"width:%d\0",(int)enemy[editor.indexSelected].width);
      sprintf(Heightvalue,"height:%d\0",(int)enemy[editor.indexSelected].height);
      sprintf(upperText,"%s %d\0","Enemy",editor.indexSelected);
   }
   else if (editor.typeSelected == 9){
      sprintf(Xvalue,"x:%d\0",(int)specials[editor.indexSelected].x);
      sprintf(Yvalue,"y:%d\0",(int)specials[editor.indexSelected].y);
      sprintf(Widthvalue,"width:%d\0",(int)specials[editor.indexSelected].size);
      sprintf(Heightvalue,"height:%d\0",(int)specials[editor.indexSelected].size);
      sprintf(upperText,"%s %d\0","Special",editor.indexSelected); 
      char* specialType = malloc(100*sizeof(char));
      specialType = specialTypes_Array[specials[editor.indexSelected].type-1];
      
      sprintf(buttons[35].value,specialType,len(specialType));

   }
   else if (editor.typeSelected == 10){
      sprintf(Xvalue,"x:%d\0",(int)textpopups[editor.indexSelected].x);
      sprintf(Yvalue,"y:%d\0",(int)textpopups[editor.indexSelected].y);
      sprintf(Widthvalue,"width:%d\0",(int)textpopups[editor.indexSelected].width);
      sprintf(Heightvalue,"height:%d\0",(int)textpopups[editor.indexSelected].height);
      sprintf(upperText,"%s %d\0","Text",editor.indexSelected);
      
      
   }
   else if(editor.typeSelected == -1){
   
   SDL_memcpy(buttons[18].value,backgrounds[app.backgroundInt].textureName,len(backgrounds[app.backgroundInt].textureName)+1);
   sprintf(upperText,"%s\0","Map");
  }
  if(editor.typeSelected != -1){
   renderText(len(Xvalue),Xvalue,gameWidth-190,100,len(Xvalue)*10,15,255,200,(int[3]){255,255,255});
   renderText(len(Yvalue),Yvalue,gameWidth-190,120,len(Yvalue)*10,15,255,200,(int[3]){255,255,255});
   renderText(len(Widthvalue),Widthvalue,gameWidth-190,140,len(Widthvalue)*10,15,255,200,(int[3]){255,255,255});
   renderText(len(Heightvalue),Heightvalue,gameWidth-190,160,len(Heightvalue)*10,15,255,200,(int[3]){255,255,255});
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
       SDL_memcpy(infoText,infoTextMessages[i],len(&infoTextMessages[i][0])+1);     
      renderText(len(infoText),infoText,gameWidth-190,gameHeight-16,7*len(infoText),10,255,200,(int[3]){200,200,200});
      free(infoText);
      return;
    }
   }
   for(int i = 0;i<sizeof(knobs)/sizeof(knobs[0]);i++){
      if(knobs[i].reserved && knobs[i].hoverOpacity>1){
      SDL_memcpy(infoText,knobInfoText[i],len(&knobInfoText[i][0])+1); 
      renderText(len(infoText),infoText,gameWidth-190,gameHeight-16,7*len(infoText),10,255,200,(int[3]){200,200,200});
      free(infoText);
      return;
      }
   }
   for(int i = 0 ;i<sizeof(sliders)/sizeof(sliders[0]);i++){
      if(sliders[i].reserved && sliders[i].hoverOpacity>1 && !sliders[i].highlight){
       SDL_memcpy(infoText,sliderInfoText[i],len(&sliderInfoText[i][0]) +1 );
      renderText(len(infoText),infoText,gameWidth-190,gameHeight-16,7*len(infoText),10,255,200,(int[3]){200,200,200});
      free(infoText);
      return;
      }
   }
   }


void editorMouseToObject_CalculateDistances(double* x,double* y){
   if(!editor.mouseToObjectDistanceBool){
      if(x != NULL){
         editor.mouseToObjectDistances[0] = editor.mouseProjected[0] - *x;
      }
      if(y != NULL){
         editor.mouseToObjectDistances[1] = editor.mouseProjected[1] - *y;
      }  
      editor.mouseToObjectDistanceBool = true;
   }
   
}

void resizeObject(double* x, double* y){
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



/// Draw editor objects
void FDrawObjects(){
   // Draw Platforms
    // not collidable first
   for (int i = 1;i<sizeof(platforms)/sizeof(platforms[0]);i++){
      if(platforms[i].reserved  && !platforms[i].collidable){
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
         SDL_SetRenderDrawColor(renderer,0,255,0,255);
         SDL_RenderDrawRect(renderer,&(SDL_Rect){platforms[editor.indexSelected].xDraw,platforms[editor.indexSelected].yDraw-(platforms[editor.indexSelected].heightDraw*sin(platforms[editor.indexSelected].slope))*(platforms[editor.indexSelected].slope>=0),platforms[editor.indexSelected].widthDraw,platforms[editor.indexSelected].heightDraw+(platforms[editor.indexSelected].heightDraw*sin(platforms[editor.indexSelected].slope))*(platforms[editor.indexSelected].slope>=0)});
         }                
      }
   }
    // collidable second
   for (int i = 1;i<sizeof(platforms)/sizeof(platforms[0]);i++){
      if(platforms[i].reserved && platforms[i].collidable){
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
         SDL_SetRenderDrawColor(renderer,0,255,0,255);
         SDL_RenderDrawRect(renderer,&(SDL_Rect){platforms[editor.indexSelected].xDraw,platforms[editor.indexSelected].yDraw-(platforms[editor.indexSelected].heightDraw*sin(platforms[editor.indexSelected].slope))*(platforms[editor.indexSelected].slope>=0),platforms[editor.indexSelected].widthDraw,platforms[editor.indexSelected].heightDraw+(platforms[editor.indexSelected].heightDraw*sin(platforms[editor.indexSelected].slope))*(platforms[editor.indexSelected].slope>=0)});
         }           
      }
   }

 // Draw Player
   player[0].widthDraw = player[0].width;
   player[0].heightDraw = player[0].height;
   player[0].widthDraw  *= camera.scale;
   player[0].heightDraw *= camera.scale;
   player[0].xDraw = gameWidth/2 + (player[0].x + camera.x - gameWidth/2) * camera.scale;
   player[0].yDraw = gameHeight/2 + (player[0].y + camera.y  - gameHeight/2) * camera.scale;

   SDL_RenderCopyEx(renderer,tex_player,&(SDL_Rect){2,24,15,18},&(SDL_Rect){player[0].xDraw,player[0].yDraw,player[0].widthDraw,player[0].heightDraw},0,NULL,SDL_FLIP_NONE);
   
   


 // Draw deathboxes
   for (int i = 0;i<sizeof(deathbox)/sizeof(deathbox[0]);i++){
      if(deathbox[i].reserved){
         // Camera offsetted data !
         
         deathbox[i].widthDraw = deathbox[i].width*camera.scale;
         deathbox[i].heightDraw = deathbox[i].height*camera.scale;
         deathbox[i].xDraw  = gameWidth/2 + (deathbox[i].x + camera.x - gameWidth/2) * camera.scale;
         deathbox[i].yDraw  = gameHeight/2 + (deathbox[i].y + camera.y - gameHeight/2) * camera.scale;

         FtextureQuad(deathbox[i].xDraw,deathbox[i].yDraw,deathbox[i].widthDraw,deathbox[i].heightDraw,tex_skull,min(deathbox[i].opacity+25,255),0);   
         
         if(editor.selected && editor.typeSelected == 5 && editor.indexSelected == i){ 
            
         SDL_SetRenderDrawColor(renderer,0,255,0,255);
         SDL_RenderDrawRect(renderer,&(SDL_Rect){deathbox[editor.indexSelected].xDraw,deathbox[editor.indexSelected].yDraw,deathbox[editor.indexSelected].widthDraw,deathbox[editor.indexSelected].heightDraw});          
      }
   }
   }
   
 // Draw Triggers
   for (int i = 0;i<sizeof(triggers)/sizeof(triggers[0]);i++){
      if(triggers[i].reserved){
         // Camera offsetted data !
        triggers[i].widthDraw = triggers[i].width*camera.scale;
        triggers[i].heightDraw = triggers[i].height*camera.scale;
        triggers[i].xDraw  = gameWidth/2 + (triggers[i].x + camera.x - gameWidth/2) * camera.scale;
        triggers[i].yDraw  = gameHeight/2 + (triggers[i].y + camera.y - gameHeight/2) * camera.scale;
         
          FtextureQuad(triggers[i].xDraw,triggers[i].yDraw,triggers[i].widthDraw,triggers[i].heightDraw,tex_trigger,min(triggers[i].opacity+25,255),0);
        if(triggers[i].triggerType == 0 && platforms[(int)triggers[i].Value3].reserved){
         SDL_RenderDrawLine(renderer,triggers[i].xDraw+triggers[i].widthDraw/2,triggers[i].yDraw+triggers[i].heightDraw/2,platforms[(int)triggers[i].Value3].xDraw+platforms[(int)triggers[i].Value3].widthDraw/2,platforms[(int)triggers[i].Value3].yDraw+platforms[(int)triggers[i].Value3].heightDraw/2);
        }
        else if(triggers[i].triggerType == 1 && deathbox[(int)triggers[i].Value3].reserved){
         SDL_RenderDrawLine(renderer,triggers[i].xDraw+triggers[i].widthDraw/2,triggers[i].yDraw+triggers[i].heightDraw/2,deathbox[(int)triggers[i].Value3].xDraw+deathbox[(int)triggers[i].Value3].widthDraw/2,deathbox[(int)triggers[i].Value3].yDraw+deathbox[(int)triggers[i].Value3].heightDraw/2);
        }
        else if(triggers[i].triggerType == 2 && light[(int)triggers[i].Value3].reserved){
         SDL_RenderDrawLine(renderer,triggers[i].xDraw+triggers[i].widthDraw/2,triggers[i].yDraw+triggers[i].heightDraw/2,light[(int)triggers[i].Value3].xDraw+light[(int)triggers[i].Value3].widthDraw/2,light[(int)triggers[i].Value3].yDraw+light[(int)triggers[i].Value3].heightDraw/2);
        }
        else if(triggers[i].triggerType == 3 && displacement[(int)triggers[i].Value3].reserved){
         SDL_RenderDrawLine(renderer,triggers[i].xDraw+triggers[i].widthDraw/2,triggers[i].yDraw+triggers[i].heightDraw/2,displacement[(int)triggers[i].Value3].xDraw+displacement[(int)triggers[i].Value3].widthDraw/2,displacement[(int)triggers[i].Value3].yDraw+displacement[(int)triggers[i].Value3].heightDraw/2);
        }


         if(editor.selected && editor.typeSelected == 2 && editor.indexSelected == i){ 
         SDL_SetRenderDrawColor(renderer,0,255,0,255);
         SDL_RenderDrawRect(renderer,&(SDL_Rect){triggers[editor.indexSelected].xDraw,triggers[editor.indexSelected].yDraw,triggers[editor.indexSelected].widthDraw,triggers[editor.indexSelected].heightDraw});
         }
      }
   }
 // Draw displacement block
   for (int i = 0;i<sizeof(displacement)/sizeof(displacement[0]);i++){
      if(displacement[i].reserved){
         // Camera offsetted data !
        displacement[i].widthDraw = displacement[i].width*camera.scale;
        displacement[i].heightDraw = displacement[i].height*camera.scale;
        displacement[i].xDraw  = gameWidth/2 + (displacement[i].x + camera.x - gameWidth/2) * camera.scale;
        displacement[i].yDraw  = gameHeight/2 + (displacement[i].y + camera.y - gameHeight/2) * camera.scale;
         
         FtextureQuad(displacement[i].xDraw,displacement[i].yDraw,displacement[i].widthDraw,displacement[i].heightDraw,tex_displacement,min(displacement[i].opacity+25,255),displacement[i].type);

         if(editor.selected && editor.typeSelected == 4 && editor.indexSelected == i){ 
         SDL_SetRenderDrawColor(renderer,0,255,0,255);
         SDL_RenderDrawRect(renderer,&(SDL_Rect){displacement[editor.indexSelected].xDraw,displacement[editor.indexSelected].yDraw,displacement[editor.indexSelected].widthDraw,displacement[editor.indexSelected].heightDraw});
         }
      }
   }
 // Draw light
   for(int i = 0;i<sizeof(light)/sizeof(light[0]);i++){
      if(light[i].reserved){
         light[i].widthDraw = light[i].width*camera.scale;
         light[i].heightDraw = light[i].height*camera.scale;
         light[i].xDraw  = gameWidth/2 + (light[i].x + camera.x - gameWidth/2) * camera.scale;
         light[i].yDraw  = gameHeight/2 + (light[i].y + camera.y - gameHeight/2) * camera.scale;
         SDL_SetTextureAlphaMod(tex_bulb,50);
         SDL_RenderCopy(renderer,tex_bulb,NULL,&(SDL_Rect){light[i].xDraw+light[i].widthDraw/2-min(30,light[i].widthDraw)/2,light[i].yDraw+light[i].heightDraw/2-min(30,light[i].heightDraw)/2,min(30,light[i].widthDraw),min(30,light[i].heightDraw)});
         SDL_SetTextureAlphaMod(tex_bulb,255);
         if(editor.selected && editor.typeSelected == 3 && editor.indexSelected == i){ 
         SDL_SetRenderDrawColor(renderer,0,255,0,255);
         SDL_RenderDrawRect(renderer,&(SDL_Rect){light[editor.indexSelected].xDraw,light[editor.indexSelected].yDraw,light[editor.indexSelected].widthDraw,light[editor.indexSelected].heightDraw});
         }
      }
   }
   SDL_SetTextureAlphaMod(tex_movenode,100);
 // Draw movenodes
   for(int i = 0;i<sizeof(movenodes)/sizeof(movenodes[0]);i++){
      if(movenodes[i].reserved){
         for(int j = 0;j<movenodes[i].nodesCount;j++){
           movenodes[i].positionsDraw[j][0] = gameWidth/2 + (movenodes[i].positions[j][0] + camera.x - gameWidth/2) * camera.scale;
           movenodes[i].positionsDraw[j][1] = gameHeight/2 + (movenodes[i].positions[j][1] + camera.y - gameHeight/2) * camera.scale;
           SDL_SetRenderDrawColor(renderer,200,200,200,255);
           if(movenodes[i].nodesCount>1){
            if(j != movenodes[i].nodesCount - 1 || movenodes[i].wrap){
              SDL_RenderDrawLine(renderer,movenodes[i].positionsDraw[j][0]+12*camera.scale,movenodes[i].positionsDraw[j][1]+12*camera.scale,movenodes[i].positionsDraw[(j+1)%(movenodes[i].nodesCount)][0]+12*camera.scale,movenodes[i].positionsDraw[(j+1)%(movenodes[i].nodesCount)][1]+12*camera.scale); 
            }
            
           }
           SDL_RenderCopy(renderer,tex_movenode,NULL,&(SDL_Rect){movenodes[i].positionsDraw[j][0],movenodes[i].positionsDraw[j][1],25*camera.scale,25*camera.scale});
           char nodeNumber[5];
           sprintf(nodeNumber,"%d\0",j);
           renderText(2,nodeNumber,movenodes[i].positionsDraw[j][0]+11*camera.scale,movenodes[i].positionsDraw[j][1]+8*camera.scale,10*camera.scale,10*camera.scale,100,100,(int[3]){255,255,255});
         
           
           if(editor.selected && editor.typeSelected == 6 && editor.indexSelected == i && editor.movenodeSelected == j){ 
            SDL_SetRenderDrawColor(renderer,0,255,0,255);
            SDL_RenderDrawRect(renderer,&(SDL_Rect){movenodes[i].positionsDraw[j][0],movenodes[i].positionsDraw[j][1],25*camera.scale,25*camera.scale});
           }
         }
      }
   }
   SDL_SetTextureAlphaMod(tex_movenode,255);
 // Draw script blocks 
   for(int i = 0;i<sizeof(scripts)/sizeof(scripts[0]);i++){
      if(scripts[i].reserved){
         scripts[i].xDraw = gameWidth/2 + (scripts[i].x + camera.x - gameWidth/2) * camera.scale;
         scripts[i].yDraw = gameHeight/2 + (scripts[i].y + camera.y - gameHeight/2) * camera.scale;
         scripts[i].widthDraw = scripts[i].width*camera.scale;
         scripts[i].heightDraw = scripts[i].height*camera.scale;
         FtextureQuad(scripts[i].xDraw,scripts[i].yDraw,scripts[i].widthDraw,scripts[i].heightDraw,tex_script,50,0);
         if(editor.selected && editor.typeSelected == 7 && editor.indexSelected == i){ 
         SDL_SetRenderDrawColor(renderer,0,255,0,255);
         SDL_RenderDrawRect(renderer,&(SDL_Rect){scripts[i].xDraw,scripts[i].yDraw,scripts[i].widthDraw,scripts[i].heightDraw}); 
      }
   }
   }
 // Draw enemies
   for(int i = 0;i<sizeof(enemy)/sizeof(enemy[0]);i++){
      if(enemy[i].reserved){
         enemy[i].xDraw = gameWidth/2 + (enemy[i].x + camera.x - gameWidth/2) * camera.scale;
         enemy[i].yDraw = gameHeight/2 + (enemy[i].y + camera.y - gameHeight/2) * camera.scale;
         enemy[i].widthDraw = enemy[i].width*camera.scale;
         enemy[i].heightDraw = enemy[i].height*camera.scale;
         if(enemy[i].type == 1){
            SDL_RenderCopyEx(renderer,tex_enemy,&(SDL_Rect){0,0,80,80},&(SDL_Rect){enemy[i].xDraw,enemy[i].yDraw,enemy[i].widthDraw,enemy[i].heightDraw},0,NULL,SDL_FLIP_NONE);
         }
         else if (enemy[i].type == 2){
            SDL_RenderCopyEx(renderer,tex_enemy,&(SDL_Rect){3,120,16,18},&(SDL_Rect){enemy[i].xDraw,enemy[i].yDraw,enemy[i].widthDraw,enemy[i].heightDraw},0,NULL,SDL_FLIP_NONE);
         }
          
         
         

         if(editor.selected && editor.typeSelected == 8 && editor.indexSelected == i){ 
         SDL_SetRenderDrawColor(renderer,0,255,0,255);
         SDL_RenderDrawRect(renderer,&(SDL_Rect){enemy[i].xDraw,enemy[i].yDraw,enemy[i].widthDraw,enemy[i].heightDraw}); 
      }
   }
   }
 // Draw Specials
   for(int i = 0;i<sizeof(specials)/sizeof(specials[0]);i++){
      if(specials[i].reserved){
         specials[i].xDraw = gameWidth/2 + (specials[i].x + camera.x - gameWidth/2) * camera.scale;
         specials[i].yDraw = gameHeight/2 + (specials[i].y + camera.y - gameHeight/2) * camera.scale;
         specials[i].sizeDraw = specials[i].size*camera.scale;
        

         SDL_RenderCopyEx(renderer,tex_specials,&(SDL_Rect){5+150*(specials[i].type - 1),0,125,125},&(SDL_Rect){specials[i].xDraw,specials[i].yDraw,specials[i].sizeDraw,specials[i].sizeDraw},0,NULL,SDL_FLIP_NONE);

         if(editor.selected && editor.typeSelected == 9 && editor.indexSelected == i){ 
         SDL_SetRenderDrawColor(renderer,0,255,0,255);
         SDL_RenderDrawRect(renderer,&(SDL_Rect){specials[i].xDraw,specials[i].yDraw,specials[i].sizeDraw,specials[i].sizeDraw}); 
      }
   }
   }
 // Draw textpopups  
   for(int i = 0;i<sizeof(textpopups)/sizeof(textpopups[0]);i++){
      if(textpopups[i].reserved){
         textpopups[i].xDraw = gameWidth/2 + (textpopups[i].x + camera.x - gameWidth/2) * camera.scale;
         textpopups[i].yDraw = gameHeight/2 + (textpopups[i].y + camera.y - gameHeight/2) * camera.scale;
         textpopups[i].widthDraw = textpopups[i].width*camera.scale;
         textpopups[i].heightDraw = textpopups[i].height*camera.scale;
        
         FtextureQuad(textpopups[i].xDraw,textpopups[i].yDraw,textpopups[i].widthDraw,textpopups[i].heightDraw,tex_textIcon,150,0);

         if(editor.selected && editor.typeSelected == 10 && editor.indexSelected == i){ 
         SDL_SetRenderDrawColor(renderer,0,255,0,255);
         SDL_RenderDrawRect(renderer,&(SDL_Rect){textpopups[i].xDraw,textpopups[i].yDraw,textpopups[i].widthDraw,textpopups[i].heightDraw}); 
      }
   }
   }
   if(editor.selected && editor.typeSelected == 0){
      SDL_SetRenderDrawColor(renderer,0,255,0,255);
      SDL_RenderDrawRect(renderer,&(SDL_Rect){player[0].xDraw,player[0].yDraw,player[0].widthDraw,player[0].heightDraw});
   }
}