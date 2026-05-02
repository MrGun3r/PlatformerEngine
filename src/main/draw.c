void DrawBackground(){
   
   int textureWidth = backgrounds[app.backgroundInt].textureWidth;
   int textureHeight = backgrounds[app.backgroundInt].textureHeight;
  
   if (app.backgroundMoving < 0){
      app.backgroundMoving += backgrounds[app.backgroundInt].textureWidth;
   }
   RenderCopy(renderer,backgrounds[app.backgroundInt].texture,&(SDL_Rect){app.backgroundMoving,0,textureWidth,textureHeight},&(SDL_Rect){0,0,gameWidthBase-app.backgroundMoving*gameWidthBase/textureWidth,gameHeightBase});
   RenderCopy(renderer,backgrounds[app.backgroundInt].texture,&(SDL_Rect){0,0,app.backgroundMoving,textureHeight},&(SDL_Rect){gameWidthBase-app.backgroundMoving*gameWidthBase/textureWidth,0,app.backgroundMoving*gameWidthBase/textureWidth,gameHeightBase});
   
}

int FindLightInt(char* textureName){
   for(int i = 0;i<sizeof(lightTextures)/sizeof(lightTextures[0]);i++){
     if(lightTextures[i].reserved){
      if(FCompareStrings(lightTextures[i].textureName,textureName)){
         return i;
      }
     }
   }
}

void DrawLight(double tint){
   SDL_SetRenderTarget(renderer,lightLayer);
   SDL_SetRenderDrawColor(renderer, 0,0,0,0);
   SDL_RenderClear(renderer);
   SDL_SetRenderDrawColor(renderer,tint,tint,tint,0);
   SDL_RenderClear(renderer);
   
   for(int i = 0;i<sizeof(light)/sizeof(light[0]);i++){
      if(light[i].reserved){
        
        SDL_SetTextureColorMod(lightTextures[light[i].lightInt].texture,light[i].red,light[i].green,light[i].blue);
        SDL_SetTextureAlphaMod(lightTextures[light[i].lightInt].texture,light[i].visibility);       
        RenderCopyEx(renderer,lightTextures[light[i].lightInt].texture,NULL,&(SDL_Rect){light[i].xDraw,light[i].yDraw,light[i].widthDraw,light[i].heightDraw},light[i].rotation,NULL,SDL_FLIP_NONE);
       }
   }

   SDL_SetRenderTarget(renderer,lightLayer2);
   SDL_SetRenderDrawColor(renderer, 0,0,0,0);
   SDL_RenderClear(renderer);
   for(int i = 0;i<sizeof(light)/sizeof(light[0]);i++){
      if(light[i].reserved){   
         SDL_SetTextureColorMod(lightTextures[light[i].lightInt].texture,light[i].red,light[i].green,light[i].blue);
        SDL_SetTextureAlphaMod(lightTextures[light[i].lightInt].texture,light[i].brightness);   
        RenderCopyEx(renderer,lightTextures[light[i].lightInt].texture,NULL,&(SDL_Rect){light[i].xDraw,light[i].yDraw,light[i].widthDraw,light[i].heightDraw},light[i].rotation,NULL,SDL_FLIP_NONE);
       }
   }

   SDL_SetRenderTarget(renderer,resultLayer);
   SDL_RenderCopy(renderer,lightLayer,NULL,NULL);
   SDL_RenderCopy(renderer,lightLayer2,NULL,NULL);
}



void FDrawTransition(){ 
  /// This draws the transition animation , which is essentially a function f(t) of which t is 
  /// app.transitionInt and it goes from 0 to 4, with 0 -> 2 being the fadeIn , and 2 -> 4 the fadeOut

  if(app.transition){
    
  SDL_SetRenderDrawColor(renderer,0,0,0,255);
  int transitionCubeSize = 50;
  int i = 0;
  int j = 0;
  if(app.transitionInt < 2){
    while(transitionCubeSize*i+transitionCubeSize/2-min(max(app.transitionInt,0),1)*transitionCubeSize/2<gameWidthBase){
      while(transitionCubeSize*j+transitionCubeSize/2-min(max(app.transitionInt,0),1)*transitionCubeSize/2<gameHeightBase){
        double cubeInterval = min(max(app.transitionInt-(double)i/(200/(double)transitionCubeSize*5),0),1);
        RenderFillRect(renderer,&(SDL_Rect){transitionCubeSize*i+transitionCubeSize/2-cubeInterval*transitionCubeSize/2,transitionCubeSize*j+transitionCubeSize/2-cubeInterval*transitionCubeSize/2,(transitionCubeSize+10)*cubeInterval,(transitionCubeSize+10)*cubeInterval});
        j++;
      }
      j = 0;
      i++;
    }
  }
  else{
    while(transitionCubeSize*i+transitionCubeSize/2-(2-app.transitionInt)*transitionCubeSize/2<gameWidthBase+transitionCubeSize){
      while(transitionCubeSize*j+transitionCubeSize/2-(2-app.transitionInt)*transitionCubeSize/2<gameHeightBase+transitionCubeSize){
        double cubeInterval = min(max(app.transitionInt-1-(double)i/(200/(double)transitionCubeSize*5),1),2);
        RenderFillRect(renderer,&(SDL_Rect){transitionCubeSize*i+transitionCubeSize/2-(2-cubeInterval)*transitionCubeSize/2,transitionCubeSize*j+transitionCubeSize/2-(2-cubeInterval)*transitionCubeSize/2,(transitionCubeSize+10)*(2-cubeInterval),(transitionCubeSize+10)*(2-cubeInterval)});
       j++;
      }
    j = 0;
    i++;
    }
    }
   app.transitionInt+=3*app.deltaTime;
   if(app.transitionInt>=2  && !app.statusChanged){
      app.transitionFunction();
      app.statusChanged = true;
   }
   if(app.transitionInt>=4){
      app.transitionInt = 0;
      app.transition = false;
   }
  } 
}