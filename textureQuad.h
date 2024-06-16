
void setTexturePlatform(int platformID){
  switch(platforms[platformID].textureInt){
    case 0:
      platforms[platformID].texture = NULL;
      break;
    case 1:
      platforms[platformID].texture = tex_tile;
      break;
    case 2:
      platforms[platformID].texture = tex_tile2;
      break;
    case 3:
      platforms[platformID].texture = tex_tile3;
      break;
    case 4:
      platforms[platformID].texture = tex_tile4;
      break;
    case 5:
      platforms[platformID].texture = tex_tileStart;
      break;
    case 6:
      platforms[platformID].texture = tex_tileBnW;
      break;
    case 7:
      platforms[platformID].texture = tex_checkpoint;
      break;
  }
}



SDL_Texture* CreateRepeatedTexture(SDL_Renderer* renderer, SDL_Texture* originalTexture, int width, int height,double scale,double offsetX,double offsetY){
    // Get the width and height of the original texture
    int textureWidth, textureHeight;
    SDL_QueryTexture(originalTexture, NULL, NULL, &textureWidth, &textureHeight);

    // Create the new texture
    SDL_Texture* repeatedTexture = SDL_CreateTexture(
        renderer, 
        SDL_PIXELFORMAT_RGBA8888, 
        SDL_TEXTUREACCESS_TARGET, 
        width, 
        height
    );

    // Set the new texture as the rendering target
    SDL_SetRenderTarget(renderer, repeatedTexture);

    // Clear the texture with transparency
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    offsetX = (int)(textureWidth*scale*offsetX/100);
    offsetY = (int)(textureHeight*scale*offsetY/100);
    textureHeight *= scale*camera.scale;
    textureWidth *= scale*camera.scale;
    // Copy the original texture into the new texture, repeating it
    for (int y = -1; y < height/(textureHeight) + 1; ++y) {
        for (int x = -1; x < width/(textureWidth) + 1; ++x) {
            SDL_Rect destRect = { x * textureWidth+offsetX, y * textureHeight+offsetY, textureWidth, textureHeight };
            SDL_RenderCopy(renderer, originalTexture, NULL, &destRect);
        }
    }

    // Reset the render target to the default (screen)
    SDL_SetRenderTarget(renderer, NULL);

    return repeatedTexture;
}



void FtexturePlatform(int platformID){
     setTexturePlatform(platformID);
     SDL_Point points[5]; 
     points[0].x = platforms[platformID].x;
     points[0].y = platforms[platformID].y-(platforms[platformID].height*sin(platforms[platformID].slope))*(platforms[platformID].slopeInv);
     points[1].x = platforms[platformID].x+platforms[platformID].width;
     points[1].y = platforms[platformID].y-(platforms[platformID].height*sin(platforms[platformID].slope))*(!platforms[platformID].slopeInv);
     points[2].x = platforms[platformID].x+platforms[platformID].width;
     points[2].y = platforms[platformID].y+platforms[platformID].height;
     points[3].x = platforms[platformID].x;
     points[3].y = platforms[platformID].y+platforms[platformID].height;
     points[4].x = points[0].x;
     points[4].y = points[0].y;
     SDL_Texture* RepeatedTexture = NULL;
     int tick = SDL_GetTicks();
     if(platforms[platformID].texture!=NULL){
     // RepeatedTexture = CreateRepeatedTexture(renderer,platforms[platformID].texture,(int)platforms[platformID].width,(int)(platforms[platformID].height*(1+sin(platforms[platformID].slope)*(platforms[platformID].slope > 0))),platforms[platformID].textureScale/80,platforms[platformID].textureOffsetX,platforms[platformID].textureOffsetY);
     }
     printf("%f\n",1/app.deltaTime);
       
       double yTexture0 = 0;
       double yTexture1 = 0;
       
       if(points[0].y < points[1].y){
        yTexture0 = 0;
        yTexture1 = 1 - SDL_abs((points[1].y - points[3].y))/(platforms[platformID].height*(1+sin(platforms[platformID].slope)*(platforms[platformID].slope>0)));
       }
       else {
        yTexture1 = 0;
        yTexture0 = 1 - SDL_abs((points[0].y - points[3].y))/(platforms[platformID].height*(1+sin(platforms[platformID].slope)*(platforms[platformID].slope>0)));
       }
       yTexture0 = max(min(yTexture0,1),0);
       yTexture1 = max(min(yTexture1,1),0);
       
       SDL_Vertex vertex_1 = {{(int)points[0].x, (int)points[0].y}, {255, 255, 255, 255}, {0, yTexture0}};
       SDL_Vertex vertex_2 = {{(int)points[1].x, (int)points[1].y}, {255, 255, 255, 255}, {1, yTexture1}};
       SDL_Vertex vertex_3 = {{(int)points[2].x, (int)points[2].y}, {255, 255, 255, 255}, {1, 1}};
       SDL_Vertex vertex_4 = {{(int)points[3].x, (int)points[3].y}, {255, 255, 255, 255}, {0, 1}}; 

       SDL_Vertex vertices[] = {
         vertex_1,
         vertex_2,
         vertex_3,
         vertex_4  
       };
       if(platforms[platformID].type){
        platforms[platformID].texture = tex_tileBnW;
       }
       SDL_RenderGeometry(renderer, RepeatedTexture, vertices, 4, (int[6]){1,2,3,0,1,3}, 6);

       SDL_DestroyTexture(RepeatedTexture);
   
   return; 
}

