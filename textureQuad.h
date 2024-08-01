
void setTexturePlatform(int platformID){
  
  platforms[platformID].texture = textures[platforms[platformID].textureInt].texture;
}



SDL_Texture* CreateRepeatedTexture(SDL_Renderer* renderer, SDL_Texture* originalTexture, int n){
    // Get the width and height of the original texture
    int textureWidth, textureHeight;
    SDL_QueryTexture(originalTexture, NULL, NULL, &textureWidth, &textureHeight);

    // Create the new texture
    SDL_Texture* repeatedTexture = SDL_CreateTexture(
        renderer, 
        SDL_PIXELFORMAT_RGBA8888, 
        SDL_TEXTUREACCESS_TARGET, 
        textureWidth, 
        textureHeight
    );

    // Set the new texture as the rendering target
    SDL_SetRenderTarget(renderer, repeatedTexture);

    // Clear the texture with transparency
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    // Copy the original texture into the new texture, repeating it
    for (int y = 0; y < n ; ++y) {
        for (int x = 0; x < n ; ++x) {
            SDL_Rect destRect = { x * textureWidth/n, y * textureHeight/n, textureWidth/n, textureHeight/n };
            SDL_RenderCopy(renderer, originalTexture, NULL, &destRect);
        }
    }

    // Reset the render target to the default (screen)
    SDL_SetRenderTarget(renderer, NULL);

    return repeatedTexture;
}



void FtexturePlatform(int platformID){

  // Texturing currently uses CPU , Which is stupidily inefficient , Waiting for SDL to add Texture UV Wrapping...
     
     setTexturePlatform(platformID);
     double textureInt = platforms[platformID].textureAnimationInt;
     double textureSize = textures[platforms[platformID].textureInt].textureAnimationSize;
     double textureStart = textureInt/textureSize;


     if(!platforms[platformID].textureStretch){
    double textureScale = platforms[platformID].textureScale*camera.scale;
       
       for(double i = platforms[platformID].xDraw-platforms[platformID].textureOffsetX*textureScale/100;i< platforms[platformID].xDraw + platforms[platformID].widthDraw;i+=textureScale){
        for(double j = platforms[platformID].yDraw-(platforms[platformID].heightDraw*sin(platforms[platformID].slope*(platforms[platformID].slope>0))) - platforms[platformID].textureOffsetY*textureScale/100;j<platforms[platformID].yDraw + platforms[platformID].heightDraw;j+=textureScale){
          
          double distanceRatio0 = (i-platforms[platformID].xDraw)/platforms[platformID].widthDraw;
          double distanceRatio1 = (i+textureScale-platforms[platformID].xDraw)/platforms[platformID].widthDraw;
          if(platforms[platformID].slopeInv){
            distanceRatio0 = 1 - distanceRatio0;
            distanceRatio1 = 1 - distanceRatio1;
          }
          distanceRatio0 = max(min(distanceRatio0,1),0);
          distanceRatio1 = max(min(distanceRatio1,1),0);
          
          SDL_Point points[5]; 
           // upper left
           points[0].x = max(i,platforms[platformID].xDraw);
           points[0].y = max(j,platforms[platformID].yDraw-(platforms[platformID].heightDraw*sin(platforms[platformID].slope)*distanceRatio0));
           // upper right
           points[1].x = min(i+textureScale,platforms[platformID].xDraw+platforms[platformID].widthDraw);
           points[1].y = max(j,platforms[platformID].yDraw-(platforms[platformID].heightDraw*sin(platforms[platformID].slope)*distanceRatio1));
           // lower right
           points[2].x = min(i+textureScale,platforms[platformID].xDraw+platforms[platformID].widthDraw);
           points[2].y = min(max(j+textureScale,platforms[platformID].yDraw-(platforms[platformID].heightDraw*sin(platforms[platformID].slope)*distanceRatio1)),platforms[platformID].yDraw+platforms[platformID].heightDraw);
           // lower left
           points[3].x = max(i,platforms[platformID].xDraw);
           points[3].y = min(max(j+textureScale,platforms[platformID].yDraw-(platforms[platformID].heightDraw*sin(platforms[platformID].slope)*distanceRatio0)),platforms[platformID].yDraw+platforms[platformID].heightDraw);
           
           // wrap
           points[4].x = points[0].x;
           points[4].y = points[0].y;
            
           double yTexture0 = (points[0].y-j)/textureScale;
           double yTexture1 = (points[1].y-j)/textureScale;
           double yTexture2 = (points[2].y-j)/textureScale;
           double xTexture0 = (points[0].x-i)/textureScale;
           double xTexture1 = (points[1].x-i)/textureScale;
           
           yTexture0 = max(min(yTexture0,1),0);
           yTexture1 = max(min(yTexture1,1),0);
           yTexture2 = max(min(yTexture2,1),0);
           xTexture0 = max(min(xTexture0/textureSize+textureStart,1),textureStart);
           xTexture1 = max(min(xTexture1/textureSize+textureStart,1),textureStart);


           SDL_Vertex vertex_1 = {{(int)points[0].x, (int)points[0].y}, {(int)platforms[platformID].red, (int)platforms[platformID].green, (int)platforms[platformID].blue, (int)platforms[platformID].opacity}, {xTexture0, yTexture0}};
           SDL_Vertex vertex_2 = {{(int)points[1].x, (int)points[1].y}, {(int)platforms[platformID].red, (int)platforms[platformID].green, (int)platforms[platformID].blue, (int)platforms[platformID].opacity}, {xTexture1, yTexture1}};
           SDL_Vertex vertex_3 = {{(int)points[2].x, (int)points[2].y}, {(int)platforms[platformID].red, (int)platforms[platformID].green, (int)platforms[platformID].blue, (int)platforms[platformID].opacity}, {xTexture1, yTexture2}};
           SDL_Vertex vertex_4 = {{(int)points[3].x, (int)points[3].y}, {(int)platforms[platformID].red, (int)platforms[platformID].green, (int)platforms[platformID].blue, (int)platforms[platformID].opacity}, {xTexture0, yTexture2}}; 
    
           SDL_Vertex vertices[] = {
             vertex_1,
             vertex_2,
             vertex_3,
             vertex_4  
           };
           
           SDL_RenderGeometry(renderer, textures[platforms[platformID].textureInt].texture, vertices, 4, (int[6]){1,2,3,0,1,3}, 6);
           //SDL_RenderDrawLines(renderer,points,5); 
    
        }
        }
     }
     else {
           SDL_Point points[5]; 
           // upper left
           points[0].x = platforms[platformID].xDraw;
           points[0].y = platforms[platformID].yDraw-platforms[platformID].heightDraw*sin(platforms[platformID].slope)*(platforms[platformID].slopeInv);
           // upper right
           points[1].x = platforms[platformID].xDraw+platforms[platformID].widthDraw;
           points[1].y = platforms[platformID].yDraw-platforms[platformID].heightDraw*sin(platforms[platformID].slope)*(!platforms[platformID].slopeInv);
           // lower right
           points[2].x = platforms[platformID].xDraw+platforms[platformID].widthDraw;
           points[2].y = platforms[platformID].yDraw+platforms[platformID].heightDraw;
           // lower left
           points[3].x = platforms[platformID].xDraw;
           points[3].y = platforms[platformID].yDraw+platforms[platformID].heightDraw;
           
           // wrap
           points[4].x = points[0].x;
           points[4].y = points[0].y;
           SDL_Vertex vertex_1 = {{(int)points[0].x, (int)points[0].y}, {(int)platforms[platformID].red, (int)platforms[platformID].green, (int)platforms[platformID].blue, (int)platforms[platformID].opacity}, {textureStart,0}};
           SDL_Vertex vertex_2 = {{(int)points[1].x, (int)points[1].y}, {(int)platforms[platformID].red, (int)platforms[platformID].green, (int)platforms[platformID].blue, (int)platforms[platformID].opacity}, {1/textureSize + textureStart,0}};
           SDL_Vertex vertex_3 = {{(int)points[2].x, (int)points[2].y}, {(int)platforms[platformID].red, (int)platforms[platformID].green, (int)platforms[platformID].blue, (int)platforms[platformID].opacity}, {1/textureSize + textureStart,1}};
           SDL_Vertex vertex_4 = {{(int)points[3].x, (int)points[3].y}, {(int)platforms[platformID].red, (int)platforms[platformID].green, (int)platforms[platformID].blue, (int)platforms[platformID].opacity}, {textureStart,1}}; 
    
           SDL_Vertex vertices[] = {
             vertex_1,
             vertex_2,
             vertex_3,
             vertex_4  
           };
           
           SDL_RenderGeometry(renderer, textures[platforms[platformID].textureInt].texture, vertices, 4, (int[6]){1,2,3,0,1,3}, 6);
           //SDL_RenderDrawLines(renderer,points,5); 
     }
       
    
    
   return; 
}


void FtextureQuad(double x,double y,double width,double height,SDL_Texture* texture,double opacity,int rotationAngle){

   // Rotation Angle
   /// angle = 90*rotationAngle;
   // rotationAngle = {0,1,2,3};
  
  // Texturing currently uses CPU , Which is stupidily inefficient , Waiting for SDL to add Texture UV Wrapping..  
       rotationAngle = rotationAngle % 4;
       for(double i = x;i < x + width;i+=25*camera.scale){
        for(double j = y;j<y+height;j+=25*camera.scale){
          SDL_Point points[5]; 
           // upper left
           points[0].x = max(i,x);
           points[0].y = max(j,y);
           // upper right
           points[1].x = min(i+25*camera.scale,x+width);
           points[1].y = max(j,y);
           // lower right
           points[2].x = min(i+25*camera.scale,x+width);
           points[2].y = min(max(j+25*camera.scale,y),y+height);
           // lower left
           points[3].x = max(i,x);
           points[3].y = min(max(j+25*camera.scale,y),y+height);
           
           // wrap
           points[4].x = points[0].x;
           points[4].y = points[0].y;
            
           


           SDL_Vertex vertex_1 = {{(int)points[0].x, (int)points[0].y}, {255,255,255, opacity}, {1*(rotationAngle == 1 || rotationAngle == 2), 1*(rotationAngle == 1 || rotationAngle == 2)}};
           SDL_Vertex vertex_2 = {{(int)points[1].x, (int)points[1].y}, {255,255,255, opacity}, {1*(rotationAngle == 0 || rotationAngle == 1), 1*(rotationAngle == 2 || rotationAngle == 3)}};
           SDL_Vertex vertex_3 = {{(int)points[2].x, (int)points[2].y}, {255,255,255, opacity}, {1*(rotationAngle == 0 || rotationAngle == 3), 1*(rotationAngle == 0 || rotationAngle == 3)}};
           SDL_Vertex vertex_4 = {{(int)points[3].x, (int)points[3].y}, {255,255,255, opacity}, {1*(rotationAngle == 2 || rotationAngle == 3), 1*(rotationAngle == 0 || rotationAngle == 1)}}; 
    
           SDL_Vertex vertices[] = {
             vertex_1,
             vertex_2,
             vertex_3,
             vertex_4  
           };
           
           SDL_RenderGeometry(renderer, texture, vertices, 4, (int[6]){1,2,3,0,1,3}, 6);
        }
        }
     
   return; 
}









