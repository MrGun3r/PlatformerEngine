void DrawBackground(){
   
   int textureWidth = backgrounds[app.backgroundInt].textureWidth;
   int textureHeight = backgrounds[app.backgroundInt].textureHeight;
  
   if (app.backgroundMoving < 0){
      app.backgroundMoving += backgrounds[app.backgroundInt].textureWidth;
   }
   SDL_RenderCopy(renderer,backgrounds[app.backgroundInt].texture,&(SDL_Rect){app.backgroundMoving,0,textureWidth,textureHeight},&(SDL_Rect){0,0,gameWidth-app.backgroundMoving*gameWidth/textureWidth,gameHeight});
   SDL_RenderCopy(renderer,backgrounds[app.backgroundInt].texture,&(SDL_Rect){0,0,app.backgroundMoving,textureHeight},&(SDL_Rect){gameWidth-app.backgroundMoving*gameWidth/textureWidth,0,app.backgroundMoving*gameWidth/textureWidth,gameHeight});
   
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
        SDL_RenderCopyEx(renderer,lightTextures[light[i].lightInt].texture,NULL,&(SDL_Rect){light[i].xDraw,light[i].yDraw,light[i].widthDraw,light[i].heightDraw},light[i].rotation,NULL,SDL_FLIP_NONE);
       }
   }

   SDL_SetRenderTarget(renderer,lightLayer2);
   SDL_SetRenderDrawColor(renderer, 0,0,0,0);
   SDL_RenderClear(renderer);
   for(int i = 0;i<sizeof(light)/sizeof(light[0]);i++){
      if(light[i].reserved){   
         SDL_SetTextureColorMod(lightTextures[light[i].lightInt].texture,light[i].red,light[i].green,light[i].blue);
        SDL_SetTextureAlphaMod(lightTextures[light[i].lightInt].texture,light[i].brightness);   
        SDL_RenderCopyEx(renderer,lightTextures[light[i].lightInt].texture,NULL,&(SDL_Rect){light[i].xDraw,light[i].yDraw,light[i].widthDraw,light[i].heightDraw},light[i].rotation,NULL,SDL_FLIP_NONE);
       }
   }

   SDL_SetRenderTarget(renderer,resultLayer);
   SDL_RenderCopy(renderer,lightLayer,NULL,NULL);
   SDL_RenderCopy(renderer,lightLayer2,NULL,NULL);
}