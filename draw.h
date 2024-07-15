void DrawBackground(){
   
   int textureWidth = backgrounds[app.backgroundInt].textureWidth;
   int textureHeight = backgrounds[app.backgroundInt].textureHeight;
  
   SDL_RenderCopy(renderer,backgrounds[app.backgroundInt].texture,&(SDL_Rect){app.backgroundMoving,0,textureWidth,textureHeight},&(SDL_Rect){0,0,gameWidth-app.backgroundMoving*gameWidth/textureWidth,gameHeight});
   SDL_RenderCopy(renderer,backgrounds[app.backgroundInt].texture,&(SDL_Rect){0,0,app.backgroundMoving,textureHeight},&(SDL_Rect){gameWidth-app.backgroundMoving*gameWidth/textureWidth,0,app.backgroundMoving*gameWidth/textureWidth,gameHeight});
   
}


void DrawLight(double tint){
   SDL_SetRenderTarget(renderer,lightLayer);
   SDL_SetRenderDrawColor(renderer,tint,tint,tint,0);
   SDL_RenderClear(renderer);
   
   for(int i = 0;i<sizeof(light)/sizeof(light[0]);i++){
      if(light[i].reserved){
         SDL_SetTextureColorMod(tex_light,light[i].red,light[i].green,light[i].blue);
        SDL_SetTextureAlphaMod(tex_light,light[i].visibility);       
        SDL_RenderCopyEx(renderer,tex_light,NULL,&(SDL_Rect){light[i].xDraw,light[i].yDraw,light[i].sizeDraw,light[i].sizeDraw},light[i].rotation,NULL,SDL_FLIP_NONE);
       }
   }

   SDL_SetRenderTarget(renderer,lightLayer2);
   
   for(int i = 0;i<sizeof(light)/sizeof(light[0]);i++){
      if(light[i].reserved){   
         SDL_SetTextureColorMod(tex_light,light[i].red,light[i].green,light[i].blue);
        SDL_SetTextureAlphaMod(tex_light,light[i].brightness);   
        SDL_RenderCopyEx(renderer,tex_light,NULL,&(SDL_Rect){light[i].xDraw,light[i].yDraw,light[i].sizeDraw,light[i].sizeDraw},light[i].rotation,NULL,SDL_FLIP_NONE);
       }
   }
}