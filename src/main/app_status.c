
void appendTransition(int from,int to){
   app.transition = true;
   app.statusTo = to;
   app.statusChanged = false;
   Mix_PlayChannel(-1,Sound_transition,0);
}

void FDrawTransition(){ 
  if(app.transition){
    
  SDL_SetRenderDrawColor(renderer,0,0,0,255);
  int transitionCubeSize = 200;
  
    int i = 0;
    int j = 0;
  if(app.transitionInt < 2){
    
    while(transitionCubeSize*i+transitionCubeSize/2-min(max(app.transitionInt,0),1)*transitionCubeSize/2<gameWidth){
      while(transitionCubeSize*j+transitionCubeSize/2-min(max(app.transitionInt,0),1)*transitionCubeSize/2<gameHeight){

        double cubeInterval = min(max(app.transitionInt-(double)i/(200/(double)transitionCubeSize*5),0),1);

        SDL_RenderFillRect(renderer,&(SDL_Rect){transitionCubeSize*i+transitionCubeSize/2-cubeInterval*transitionCubeSize/2,transitionCubeSize*j+transitionCubeSize/2-cubeInterval*transitionCubeSize/2,transitionCubeSize*cubeInterval,transitionCubeSize*cubeInterval});
        j++;
      }
      j = 0;
      i++;
    }
    
  }
  else{
    while(transitionCubeSize*i+transitionCubeSize/2-(2-app.transitionInt)*transitionCubeSize/2<gameWidthBase+transitionCubeSize){
      while(transitionCubeSize*j+transitionCubeSize/2-(2-app.transitionInt)*transitionCubeSize/2<gameHeight+transitionCubeSize){
        double cubeInterval = min(max(app.transitionInt-1-(double)i/(200/(double)transitionCubeSize*5),1),2);
        SDL_RenderFillRect(renderer,&(SDL_Rect){transitionCubeSize*i+transitionCubeSize/2-(2-cubeInterval)*transitionCubeSize/2,transitionCubeSize*j+transitionCubeSize/2-(2-cubeInterval)*transitionCubeSize/2,transitionCubeSize*(2-cubeInterval),transitionCubeSize*(2-cubeInterval)});
       j++;
      }
    j = 0;
    i++;
    }
    }
   
   
   
   app.transitionInt+=3*app.deltaTime;
   if(app.transitionInt>=2  && !app.statusChanged){
      FswitchAppStatus(app.status,app.statusTo);
      app.statusChanged = true;
      
   }
   if(app.transitionInt>=4){
      app.transitionInt = 0;
      app.transition = false;
   }
  } 
}

void FswitchAppStatus(int from, int to){ 
    for(int i = 0 ;i<sizeof(buttons)/sizeof(buttons[0]);i++){
      buttons[i].reserved = false;
      buttons[i].highlight = false;
      sprintf(buttons[i].value,"\0");
    }
    for(int i = 0 ;i<sizeof(sliders)/sizeof(sliders[0]);i++){
      sliders[i].reserved = false;
    }
    for(int i = 0 ;i<sizeof(textbox)/sizeof(textbox[0]);i++){
      textbox[i].reserved = false;
    }
    if(from != to){
      for(int i = 0 ;i<sizeof(light)/sizeof(light[0]);i++){
      light[i].reserved = false;
    }
    }
    
   if(to == 0){
      printf("Map is :%s\n",level.absolutePath);
      FSetDataMap(level.absolutePath,len(level.absolutePath)); 
      app.backgroundInt = FindBackgroundInt(FGetDataMap(level.absolutePath,"m",6,len(level.absolutePath)));
      app.backgroundOpacity = atoi(FGetDataMap(level.absolutePath,"m",7,len(level.absolutePath)));
      level.checkpointCount = 0;
      
      FGameRestart();  
   }

   app.status = to;
   if(to == 0){
      if(from == 2){
        level.campaignLevel = false;
      }
      else{
        level.campaignLevel = true;
      }
      SetButton(false,0,"Paused",gameWidthBase/2 - len("Paused\0")*30/2,gameHeightBase/2-150,30,true,-1,-1,false);
      SetButton(false,1,"Resume",gameWidthBase/2 - len("Resume\0")*15/2,gameHeightBase/2-80,15,true,-1,-1,false);  
      SetButton(false,3,"Restart Level",50,gameWidthBase-50,15,true,-1,-1,false);
      SetButton(false,4,"Next Level",gameWidthBase-200,gameWidthBase-50,15,true,-1,-1,false);
      SetButton(false,2,"Exit to Menu",gameWidthBase/2 - len("Exit to Menu\0")*15/2,gameHeightBase/2-20-30,15,true,-1,-1,false);
      
    }
   // Play Menu
   if(to == 7){
    SetButton(true,0,"Campaign",30,200,20,true,-1,-1,false);
    SetButton(true,1,"Browse Levels",30,250,20,true,-1,-1,false);
    SetButtonIcon(0,tex_tools,0.225,0.48,0.25,0.5);
    SetButtonIcon(1,tex_tools,0.725,1,0,0.24);
   }
   if (to == 8){
    printf("Hi i am reading the profile\n");
    ReadLevelCampaign();
    
    FswitchAppStatus(from,0);

   }
   // Menu
   if(to == 4){
     remove("levels/temp.txt");
    app.backgroundInt = FindBackgroundInt("background");
    app.backgroundOpacity = 255;
    SetButton(true,0,"Play",30,200,20,true,-1,-1,false);
    SetButton(true,1,"Editor",30,250,20,true,-1,-1,false);
    SetButton(true,2,"Settings",30,300,20,true,-1,-1,false);
    SetButton(true,3,"Exit",30,350,20,true,-1,-1,false);
    SetButtonIcon(0,tex_tools,0,0.21,0,0.21);
    SetButtonIcon(1,tex_tools,0,0.225,0.25,0.48);
    SetButtonIcon(2,tex_tools,0.225,0.48,0,0.25);
    SetButtonIcon(3,tex_tools,0.50,0.725,0,0.24);

   }
   else if (to == 5){
    app.backgroundInt = FindBackgroundInt("background");
    app.backgroundOpacity = 255;
    SetTextBox(true,0,"Set Username:",gameWidthBase/2 - len("Set Username:\0")*15/2-250,100,15,750);
    SetButton(true,0,"Start",gameWidthBase/2 - len("Start\0")*15/2,130,15,true,-1,-1,false);
   }
   // levels list
   if(to == 2){
    for(int i = 0 ;i<sizeof(light)/sizeof(light[0]);i++){
      light[i].reserved = false;
    }
      remove("levels/temp.txt");
     app.fetchedList = false;
     SetButton(true,0,"Levels",30,120,30,true,-1,-1,false);
  
     FlistLevels();
     
     for(int i = app.listStartIndex;i<(sizeof(levelsList)/sizeof(levelsList[0]));i++){
      
      if(i > 0 && levelsList[i-1].reserved){
        SetButton(true,i+2,levelsList[i-1].levelName,20,180+(i-app.listStartIndex)*20,10,true,500,-1,false);
        
       if(180+(i-app.listStartIndex)*20>gameWidthBase-100){
        app.listLengthMax = i - app.listStartIndex;
        app.listLength = i - app.listStartIndex;
        break;
      }
      else {
        app.listLength = i - app.listStartIndex;
      }
      }
     }
     
     SetButton(true,1,"Prev",30,gameHeightBase-60,15,true,-1,-1,false);
     SetButton(true,2,"Next",150,gameHeightBase-60,15,true,-1,-1,false);
    
     return;
   }
   // Settings 
   if(to == 6){
    SetButton(true,0,"Settings",30,120,30,true,-1,-1,false);
    SetSlider(true,0,"SFX Volume",20,180,15,true,-1,-1,false,0,100,80,100);
    SetSlider(true,1,"Music Volume",20,210,15,true,-1,-1,false,0,100,80,100);
    SetButton(true,1,"Resolution",20,240,15,true,-1,-1,false);
    SetButton(true,3,"Show FPS",20,270,15,true,-1,-1,false);
    SetButton(true,2,"Apply",20,gameHeightBase-50,10,true,-1,-1,false);

    sprintf(buttons[1].value,"%dx%d",app.resolutions[app.resolutionUsed][0],app.resolutions[app.resolutionUsed][1]);
    sprintf(buttons[3].value,"%d",app.showFPS);
   }
   // Editor
   if(to == 1){
      
      if(from != 1){
          for(int i = 0;i<sizeof(platforms)/sizeof(platforms[0]);i++){
            platforms[i].reserved = false;
          }
          for(int i = 0;i<sizeof(triggers)/sizeof(triggers[0]);i++){
            triggers[i].reserved = false;
          }
          for(int i = 0;i<sizeof(displacement)/sizeof(displacement[0]);i++){
            displacement[i].reserved = false;
          }
          for(int i = 0;i<sizeof(deathbox)/sizeof(deathbox[0]);i++){
            deathbox[i].reserved = false;
          }
          for(int i = 0;i<sizeof(movenodes)/sizeof(movenodes[0]);i++){
            movenodes[i].reserved = false;
          }
          for(int i = 0;i<sizeof(scripts)/sizeof(scripts[0]);i++){
            scripts[i].reserved = false;
          }
          for(int i = 0;i<sizeof(enemy)/sizeof(enemy[0]);i++){
            enemy[i].reserved = false;
          }
          for(int i = 0;i<sizeof(specials)/sizeof(specials[0]);i++){
            specials[i].reserved = false;
          }
          for(int i = 0;i<sizeof(textpopups)/sizeof(textpopups[0]);i++){
            textpopups[i].reserved = false;
            free(textpopups[i].textContent);
          }
          
          editor.mapNameSet = false;
          app.backgroundInt = FindBackgroundInt("background");
          editor.GameScale = 2;
          app.backgroundOpacity = 255;
          editor.gridMove = 1;
          editor.StarTime = 60;
          editor.StarTimeMs = 0;
          player[0].x = 0;
          player[0].y = 0;
          player[0].spawnX = 0;
          player[0].spawnY = 0;
          player[0].width = 18;
          player[0].height = 20;
          camera.x = gameWidth/2;
          camera.y = gameHeight/2;
          camera.scaleReal = 1;
          camera.scale = 1;
          mapData.xMin = -5000;
          mapData.yMin = -5000;
          mapData.xMax = 5000;
          mapData.yMax = 5000;
          editor.status = -1;       
   }
          
          // Buttons
          SetButton(false,1,"Translate",gameWidthBase-190,50,10,true,-1,-1,true);
          SetButton(false,2,"Resize",gameWidthBase-190,75,10,true,-1,-1,false);
          SetButton(true,3,"Save Map",gameWidthBase-190,gameHeightBase-70,10,true,-1,-1,false);
          SetButton(true,4,"Save Map As",gameWidthBase-190,gameHeightBase-50,10,true,-1,-1,false);
          SetButton(false,5,"Delete",gameWidthBase-190,gameHeightBase-120,10,true,-1,-1,false);
          SetButton(true,6,"Load Map",gameWidthBase-190,gameHeightBase-90,10,true,-1,-1,false);
          SetButton(false,7,"Texture:",gameWidthBase-190,200,10,true,-1,-1,false);
          SetButton(false,8,"SlopeInv",gameWidthBase-190,220,10,true,-1,-1,false);
          SetButton(false,17,"Stretch",gameWidthBase-190,300,10,true,-1,-1,false);
          SetButton(false,9,"Copy",gameWidthBase-sizeof("Copy")*8-20,gameHeightBase-120,10,true,-1,-1,false);
          SetButton(true,10,"New",5,5,10,true,-1,-1,false);
          SetButton(true,11,"Map",5,30,10,true,-1,-1,false);
          SetButton(false,24,"Collidable",gameWidthBase-190,300,10,true,-1,-1,false);
          SetButton(false,26,"Add Node",gameWidthBase-190,180,10,true,-1,-1,false);
          SetButton(false,27,"Remove Node",gameWidthBase-190,200,10,true,-1,-1,false);
          SetButton(false,28,"Wrap",gameWidthBase-190,220,10,true,-1,-1,false);
          SetButton(false,29,"Type",gameWidthBase-190,240,10,true,-1,-1,false);
          SetButton(true,15,"+",gameWidthBase-220,gameHeightBase-15,10,true,-1,-1,false);
          SetButton(true,16,"-",gameWidthBase-240,gameHeightBase-15,10,true,-1,-1,false);
          SetButton(false,18,"Bg",gameWidthBase-190,180,10,true,-1,-1,false);
          SetButton(false,21,"Type",gameWidthBase-190,180,10,true,-1,-1,false);
          SetButton(false,22,"Displace",gameWidthBase-190,200,10,true,-1,-1,false);
          SetButton(false,31,"Name",gameWidthBase-190,200,10,true,-1,-1,false);
          SetButton(false,32,"Light",gameWidthBase-190,400,10,true,-1,-1,false);
          SetButton(false,35,"Special",gameWidthBase-190,180,10,true,-1,-1,false);
          SetButton(false,37,"Set Text",gameWidthBase-190,180,10,true,-1,-1,false);
          SetButton(false,38,"Rotate",gameWidthBase-190,480,10,true,-1,-1,false);
          SetButton(false,39,"Finish Animation",gameWidthBase-190,380,10,true,-1,-1,false);
          SetButton(false,40,"Grapplable",gameWidthBase-190,540,10,true,-1,-1,false);

          SetButton(true,0,"",70,10,30,true,-1,40,false);
          SetButtonIcon(0,textures[FindTextureInt("stone")].texture,0,1,0,1);
          SetButton(true,12,"",120,10,30,true,-1,40,false);
          SetButtonIcon(12,tex_trigger,0,1,0,1);
          SetButton(true,13,"",170,10,30,true,-1,40,false);
          SetButtonIcon(13,textures[FindTextureInt("check")].texture,0,0.5,0,0.5);
          SetButton(true,14,"",220,10,30,true,-1,40,false);
          SetButtonIcon(14,textures[FindTextureInt("Bcheck")].texture,0,0.5,0,0.5);
          SetButton(true,19,"",270,10,30,true,-1,40,false);
          SetButtonIcon(19,tex_bulb,0,1,0,1);
          SetButton(true,20,"",320,10,30,true,-1,40,false);
          SetButtonIcon(20,tex_displacement,0,1,0,1);
          SetButton(true,23,"",370,10,30,true,-1,40,false);
          SetButtonIcon(23,tex_skull,0,1,0,1);
          SetButton(true,25,"",420,10,30,true,-1,40,false);
          SetButtonIcon(25,tex_movenode,0,1,0,1);
          SetButton(true,30,"",470,10,30,true,-1,40,false);
          SetButtonIcon(30,tex_script,0,1,0,1);
          SetButton(true,33,"",520,10,30,true,-1,40,false);
          SetButtonIcon(33,tex_enemy,0,0.28,0,0.23);
          SetButton(true,34,"",570,10,30,true,-1,40,false);
          SetButtonIcon(34,tex_specials,0.25,0.36,0,0.65);
          SetButton(true,36,"",620,10,30,true,-1,40,false);
          SetButtonIcon(36,tex_textIcon,0,1,0,1);
          
          // Text Box
          SetTextBox(false,0,"Map Name:",45,150,15,450);

          // Sliders
          SetSlider(false,0,"Slope",gameWidthBase-190,180,10,true,-1,-1,false,-45,45,80,0);
          SetSlider(false,1,"Texture x",gameWidthBase-190,200,10,true,-1,-1,false,0,100,50,0);
          SetSlider(false,2,"Texture y",gameWidthBase-190,220,10,true,-1,-1,false,0,100,50,0);
          SetSlider(false,14,"Opacity",gameWidthBase-190,300,10,true,-1,-1,false,0,255,60,255);
          SetSlider(false,6,"Map Light",gameWidthBase-190,100,10,true,-1,-1,false,10,255,50,255);
          SetSlider(false,7,"Rotation",gameWidthBase-190,200,10,true,-1,-1,false,0,360,50,0);
          SetSlider(false,8,"Brightness",gameWidthBase-190,220,10,true,-1,-1,false,0,255,50,100);
          SetSlider(false,9,"Visibility",gameWidthBase-190,240,10,true,-1,-1,false,0,255,50,255);
          SetSlider(false,15,"Camera",gameWidthBase-190,160,10,true,-1,-1,false,50,600,50,300);
          SetSlider(false,10,"Red",gameWidthBase-190,260,10,true,-1,-1,false,0,255,70,255);
          SetSlider(false,11,"Green",gameWidthBase-190,280,10,true,-1,-1,false,0,255,70,255);
          SetSlider(false,12,"Blue",gameWidthBase-190,300,10,true,-1,-1,false,0,255,70,255);
          SetSlider(false,13,"Power",gameWidthBase-190,220,10,true,-1,-1,false,0,1500,50,50);
          SetSlider(false,16,"Max Speed",gameWidthBase-190,220,10,true,-1,-1,false,5,400,60,20);
          SetSlider(false,17,"Health",gameWidthBase-190,240,10,true,-1,-1,false,5,200,80,30);

          // Knobs
          SetKnob(false,0,"Tex Scale",gameWidthBase-190,240,10,true,5,250,30);
          SetKnob(false,5,"Animation",gameWidthBase-190,360,10,true,0,1000,0);
          SetKnobCoef(5,0.5);
          SetKnob(false,8,"Node ID",gameWidthBase-190,440,10,true,-1,50,-1);
          SetKnobCoef(8,0.1);
          SetKnob(false,10,"Object ID",gameWidthBase-190,300,10,true,0,300,0);
          SetKnobCoef(10,0.1);
          SetKnob(false,9,"Move Speed",gameWidthBase-190,460,10,true,0,500,0);
          SetKnobCoef(9,1);
          SetKnob(false,11,"Use Delay",gameWidthBase-190,320,10,true,0,5000,0);
          SetKnob(false,12,"Reuse Time",gameWidthBase-190,340,10,true,0,5000,0);
          SetKnob(false,16,"Texture Move X",gameWidthBase-190,500,10,true,0,500,0);
          SetKnob(false,17,"Texture Move Y",gameWidthBase-190,520,10,true,0,500,0);

          SetKnob(false,3,"Border X",gameWidthBase-190,120,10,true,500,10000,5000);
          SetKnob(false,4,"Border Y",gameWidthBase-190,140,10,true,500,10000,5000);
          SetKnobCoef(3,10);  
          SetKnobCoef(4,10);
          
          SetKnob(false,6,"Star Time Ms",gameWidthBase-190,200,10,true,0,99,0);
          SetKnobCoef(6,0.5);
          SetKnob(false,7,"Star Time",gameWidthBase-190,220,10,true,0,10000,60);
          SetKnob(false,18,"Type",gameWidthBase-190,260,10,true,1,5,1);
          SetKnobCoef(18,0.1);
          SetKnob(false,19,"Grid Unit",gameWidthBase-190,240,10,true,1,100,1);
          SetKnobCoef(19,0);
          SetKnob(false,13,"X:",gameWidthBase-190,220,10,true,0,100,0);
          SetKnob(false,14,"Y:",gameWidthBase-190,250,10,true,0,100,0);
          SetKnob(false,15,"Font:",gameWidthBase-190,280,10,true,10,120,10);

    editor.mouseToObjectDistances[0] = 0;
    editor.mouseToObjectDistances[1] = 0;   
    editor.mouseToObjectDistanceBool = false;   
    editor.gridMove = 1;
    editor.transform = 1;
    editor.selected = false;
    editor.typeSelected = 0;
    editor.indexSelected = 0;
   }
} 