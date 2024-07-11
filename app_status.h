
void appendTransition(int from,int to){
   app.transition = true;
   app.statusTo = to;
}

void FDrawTransition(){
  SDL_SetRenderTarget(renderer,HUDLayer);
  
  SDL_SetRenderDrawColor(renderer,0,0,0,255);
  if(app.transition){
   SDL_RenderFillRect(renderer,&(SDL_Rect){-windowWidth+app.transitionInt,0,windowWidth,windowHeight});
   app.transitionInt+=2.5*windowWidth*app.deltaTime;
   if(app.transitionInt>=windowWidth && app.status != app.statusTo){
      FswitchAppStatus(app.status,app.statusTo);
      
   }
   if(app.transitionInt>=2*windowWidth){
      app.transitionInt = 0;
      app.transition = false;
   }
  } 
  SDL_SetRenderTarget(renderer,backgroundLayer);
}

void FswitchAppStatus(int from, int to){
   if(from == 1 && to == 0){
      FGameRestart();
   }
   else if(to == 0){
      app.backgroundInt = FindBackgroundInt(FGetDataMap(level.absolutePath,"m",6,len(level.absolutePath)));
      app.backgroundOpacity = atoi(FGetDataMap(level.absolutePath,"m",7,len(level.absolutePath)));
      level.checkpointCount = 0;
      FGameRestart();
   } 
   for(int i = 0;i<sizeof(buttons)/sizeof(buttons[0]);i++){
      buttons[i].reserved  = false;
      buttons[i].highlight = false;
   }
   app.status = to;
   
   // Menu
   if(to == 4){
      remove("levels/temp.txt");
    for(int i = 0 ;i<sizeof(light)/sizeof(light[0]);i++){
      light[i].reserved = false;
    } 
    app.backgroundInt = FindBackgroundInt("background");
    app.backgroundOpacity = 255;
    SetButton(true,0,"Play",30,200,20,true,-1,-1,false);
    SetButton(true,1,"Editor",30,250,20,true,-1,-1,false);
    SetButton(true,2,"Settings",30,300,20,true,-1,-1,false);
    SetButton(true,3,"Exit",30,350,20,true,-1,-1,false);

   }
   // levels list
   if(to == 2){
      remove("levels/temp.txt");
     app.fetchedList = false;
     SetButton(true,0,"Levels",30,50,30,true,-1,-1,false);
     FlistLevels();
     for(int i = 0;i<(sizeof(levelsList)/sizeof(levelsList[0]));i++){
      if(levelsList[i].reserved){
        SetButton(true,i+1,levelsList[i].levelName,20,150+i*20,10,true,500,-1,false); 
      }
     }
     return;
   }

   // Editor
   if(to == 1){
      if(from != 1){
          for(int i = 0;i<sizeof(buttons)/sizeof(buttons[0]);i++){
            platforms[i].reserved = false;
          }
          for(int i = 0;i<sizeof(buttons)/sizeof(buttons[0]);i++){
            triggers[i].reserved = false;
          }
          for(int i = 0;i<sizeof(buttons)/sizeof(buttons[0]);i++){
            light[i].reserved = false;
          }
          for(int i = 0;i<sizeof(displacement)/sizeof(displacement[0]);i++){
            displacement[i].reserved = false;
          }
          for(int i = 0;i<sizeof(displacement)/sizeof(displacement[0]);i++){
            deathbox[i].reserved = false;
          }
          app.backgroundInt = FindBackgroundInt("background");
          player[0].x = 0;
          player[0].y = 0;
          player[0].spawnX = 0;
          player[0].spawnY = 0;
          player[0].width = 18;
          player[0].height = 20;
          camera.x = windowWidth/2;
          camera.y = windowHeight/2;
          camera.scaleReal = 1;
          camera.scale = 1;
          mapData.xMin = -5000;
          mapData.yMin = -5000;
          mapData.xMax = 5000;
          mapData.yMax = 5000;
         
   }
          
          SetButton(false,1,"Translate",windowWidth-190,50,10,true,-1,-1,true);
          SetButton(false,2,"Resize",windowWidth-190,75,10,true,-1,-1,false);
          SetButton(true,4,"Save Map",windowWidth-190,windowHeight-50,10,true,-1,-1,false);
          SetButton(false,5,"Delete",windowWidth-190,windowHeight-90,10,true,-1,-1,false);
          SetButton(true,6,"Load Map",windowWidth-190,windowHeight-70,10,true,-1,-1,false);
          SetButton(false,7,"Texture:",windowWidth-190,220,10,true,-1,-1,false);
          SetButton(false,8,"SlopeInv",windowWidth-190,240,10,true,-1,-1,false);
          SetButton(false,17,"Stretch",windowWidth-190,320,10,true,-1,-1,false);
          SetButton(false,9,"Copy",windowWidth-sizeof("Copy")*8-20,windowHeight-90,10,true,-1,-1,false);
          SetButton(true,10,"New",5,5,10,true,-1,-1,false);
          SetButton(true,11,"Map",5,30,10,true,-1,-1,false);
          
          SetButton(true,0," ",70,10,30,true,-1,40,false);
          SetButtonIcon(0,textures[FindTextureInt("stone")].texture,0,1,0,1);
          SetButton(true,12," ",120,10,30,true,-1,40,false);
          SetButtonIcon(12,tex_trigger,0,1,0,1);
          SetButton(true,13," ",170,10,30,true,-1,40,false);
          SetButtonIcon(13,textures[FindTextureInt("check")].texture,0,0.5,0,0.5);
          SetButton(true,14," ",220,10,30,true,-1,40,false);
          SetButtonIcon(14,textures[FindTextureInt("Bcheck")].texture,0,0.5,0,0.5);
          SetButton(true,19," ",270,10,30,true,-1,40,false);
          SetButtonIcon(19,tex_bulb,0,1,0,1);
          SetButton(true,20," ",320,10,30,true,-1,40,false);
          SetButtonIcon(20,tex_displacement,0,1,0,1);
          SetButton(true,23," ",370,10,30,true,-1,40,false);
          SetButtonIcon(23,tex_skull,0,1,0,1);
      
          SetButton(true,15,"+",windowWidth-220,windowHeight-15,10,true,-1,-1,false);
          SetButton(true,16,"-",windowWidth-240,windowHeight-15,10,true,-1,-1,false);
          
          SetSlider(false,0,"Slope",windowWidth-190,200,10,true,-1,-1,false,-45,45,80,0);
          SetSlider(false,1,"Tex x",windowWidth-190,260,10,true,-1,-1,false,0,100,80,0);
          SetSlider(false,2,"Tex y",windowWidth-190,280,10,true,-1,-1,false,0,100,80,0);
          SetSlider(false,3,"Tex Scale",windowWidth-190,300,10,true,-1,-1,false,30,150,60,10);
          SetSlider(false,14,"Opacity",windowWidth-190,340,10,true,-1,-1,false,0,255,60,255);
          SetButton(false,24,"Collidable",windowWidth-190,360,10,true,-1,-1,false);

          SetSlider(false,4,"Border X",windowWidth-190,200,10,true,-1,-1,false,500,10000,50,5000);
          SetSlider(false,5,"Border Y",windowWidth-190,220,10,true,-1,-1,false,500,10000,50,5000);
          SetSlider(false,6,"Map Light",windowWidth-190,160,10,true,-1,-1,false,10,255,50,255);
          SetSlider(false,7,"Rotation",windowWidth-190,200,10,true,-1,-1,false,0,360,50,0);
          SetSlider(false,8,"Brightness",windowWidth-190,220,10,true,-1,-1,false,0,255,50,100);
          SetSlider(false,9,"Visibility",windowWidth-190,240,10,true,-1,-1,false,0,255,50,255);

          SetSlider(false,10,"Red",windowWidth-190,260,10,true,-1,-1,false,0,255,50,255);
          SetSlider(false,11,"Green",windowWidth-190,280,10,true,-1,-1,false,0,255,50,255);
          SetSlider(false,12,"Blue",windowWidth-190,300,10,true,-1,-1,false,0,255,50,255);

          SetButton(false,18,"Bg",windowWidth-190,180,10,true,-1,-1,false);

          SetButton(false,21,"Type",windowWidth-190,180,10,true,-1,-1,false);
          SetButton(false,22,"Displace",windowWidth-190,200,10,true,-1,-1,false);
          SetSlider(false,13,"Power",windowWidth-190,220,10,true,-1,-1,false,0,1500,50,50);


    editor.transform = 1;
    editor.selected = false;
    editor.typeSelected = 0;
    editor.indexSelected = 0;
   }
} 