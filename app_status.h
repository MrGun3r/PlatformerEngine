
void appendTransition(int from,int to){
   app.transition = true;
   app.statusTo = to;
}

void FDrawTransition(){
  SDL_SetRenderDrawColor(renderer,0,0,0,255);
  if(app.transition){
   SDL_RenderFillRect(renderer,&(SDL_Rect){-windowWidth+app.transitionInt,0,windowWidth,windowHeight});
   app.transitionInt+=2.5*windowWidth*app.deltaTime;
   if(app.transitionInt>=windowWidth){
      FswitchAppStatus(app.status,app.statusTo);
   }
   if(app.transitionInt>=2*windowWidth){
      app.transitionInt = 0;
      app.transition = false;
   }
  } 
}

void FswitchAppStatus(int from, int to){
   if(from == 0){
      level.checkpointCount = 0;
      FGameRestart();
   }
   for(int i = 0;i<sizeof(buttons)/sizeof(buttons[0]);i++){
      buttons[i].reserved = false;
      buttons[i].highlight = false;
   }
   app.status = to;
   
   // Menu
   if(to == 4){
    SetButton(true,0,"Play",30,200,20,true,-1,-1,false);
    SetButton(true,1,"Editor",30,250,20,true,-1,-1,false);
    SetButton(true,2,"Settings",30,300,20,true,-1,-1,false);
    SetButton(true,3,"Exit",30,350,20,true,-1,-1,false);

   }
   // levels list
   if(to == 2){
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
   }
   player[0].x = 0;
   player[0].y = 0;
   player[0].width = 18;
   player[0].height = 20;
   camera.x = windowWidth/2;
   camera.y = windowHeight/2;
   camera.scaleReal = 1;
   camera.scale = 1;
    SetButton(true,0," ",70,10,30,true,-1,40,false);
    SetButtonIcon(0,tex_tile3,0,1,0,1);
    SetButton(false,1,"Translate",windowWidth-190,50,10,true,-1,-1,true);
    SetButton(false,2,"Resize",windowWidth-190,75,10,true,-1,-1,false);
    SetButton(true,4,"Save Map",windowWidth-190,windowHeight-50,10,true,-1,-1,false);
    SetButton(false,5,"Delete",windowWidth-190,windowHeight-90,10,true,-1,-1,false);
    SetButton(true,6,"Load Map",windowWidth-190,windowHeight-70,10,true,-1,-1,false);
    SetButton(false,7,"Texture:",windowWidth-190,270,10,true,-1,-1,false);
    SetButton(false,8,"SlopeInv",windowWidth-190,290,10,true,-1,-1,false);
    SetButton(false,9,"Copy",windowWidth-sizeof("Copy")*8-20,windowHeight-90,10,true,-1,-1,false);
    SetButton(true,10,"New",5,5,10,true,-1,-1,false);
    SetButton(true,11,"Test",5,30,10,true,-1,-1,false);

    SetButton(true,12," ",120,10,30,true,-1,40,false);
    SetButtonIcon(12,tex_trigger,0,1,0,1);
    SetButton(true,13," ",170,10,30,true,-1,40,false);
    SetButtonIcon(13,tex_tileBnW,0,0.5,0,0.5);
    SetButton(true,14," ",220,10,30,true,-1,40,false);
    SetButtonIcon(14,tex_checkpoint,0,0.5,0,0.5);

    SetButton(true,15,"+",windowWidth-220,windowHeight-15,10,true,-1,-1,false);
    SetButton(true,16,"-",windowWidth-240,windowHeight-15,10,true,-1,-1,false);

    SetSlider(false,0,"Slope",windowWidth-190,250,10,true,-1,-1,false,-45,45,80,0);
    SetSlider(false,1,"Tex x",windowWidth-190,310,10,true,-1,-1,false,0,100,80,0);
    SetSlider(false,2,"Tex y",windowWidth-190,330,10,true,-1,-1,false,0,100,80,0);
    SetSlider(false,3,"Tex Scale",windowWidth-190,350,10,true,-1,-1,false,10,150,60,10);
    editor.transform = 1;
    editor.selected = false;
    editor.typeSelected = 0;
    editor.indexSelected = 0;
   }
} 