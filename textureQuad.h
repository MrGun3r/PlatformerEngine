
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
     
  if(platforms[platformID].textureStretch){
       SDL_Vertex vertex_1 = {{(int)points[0].x, (int)points[0].y}, {255, 255, 255, 255}, {0, 0}};
       SDL_Vertex vertex_2 = {{(int)points[1].x, (int)points[1].y}, {255, 255, 255, 255}, {1, 0}};
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
       SDL_RenderGeometry(renderer, platforms[platformID].texture, vertices, 4, (int[6]){1,2,3,0,1,3}, 6);
   return;
  }
   for(double i = platforms[platformID].x-platforms[platformID].textureScale*(platforms[platformID].textureOffsetX)/100;i<platforms[platformID].x + platforms[platformID].width;i += platforms[platformID].textureScale){ 
      double j = platforms[platformID].y+platforms[platformID].height-platforms[platformID].textureScale
      +platforms[platformID].textureScale*(platforms[platformID].textureOffsetY)/100;
      while(true){
       double distanceRatio1 = (i - platforms[platformID].x)/(platforms[platformID].width);
       double distanceRatio2 = (i + platforms[platformID].textureScale - platforms[platformID].x)/(platforms[platformID].width);
       if(platforms[platformID].slopeInv){
          distanceRatio1 = 1 - (i - platforms[platformID].x)/(platforms[platformID].width);
          distanceRatio2 = 1 - (i + platforms[platformID].textureScale - platforms[platformID].x)/(platforms[platformID].width);
       } 
       if(i + platforms[platformID].textureScale > platforms[platformID].x + platforms[platformID].width){
         distanceRatio2 = 1;
         if(platforms[platformID].slopeInv){distanceRatio2 = 0;}
       }
       SDL_Point points2[4];
       
       points2[0].x = max(i,(int)platforms[platformID].x);
       points2[0].y = min(max(j+platforms[platformID].textureScale,platforms[platformID].y - platforms[platformID].height*sin(platforms[platformID].slope)*distanceRatio1),platforms[platformID].y+platforms[platformID].height);
       points2[1].x = min(i+platforms[platformID].textureScale,platforms[platformID].x + platforms[platformID].width);
       points2[1].y = min(max(j+platforms[platformID].textureScale,platforms[platformID].y - platforms[platformID].height*sin(platforms[platformID].slope)*distanceRatio2),platforms[platformID].y+platforms[platformID].height);
       points2[2].x = min(i+platforms[platformID].textureScale,platforms[platformID].x + platforms[platformID].width);
       points2[2].y = max(j,platforms[platformID].y - platforms[platformID].height*sin(platforms[platformID].slope)*distanceRatio2);
       points2[3].x = max(i,(int)platforms[platformID].x);
       points2[3].y = max(j,platforms[platformID].y - platforms[platformID].height*sin(platforms[platformID].slope)*distanceRatio1);    
       points2[4].x = points2[0].x;
       points2[4].y = points2[0].y;

       double xTexture2 = 0;
       double yTexture2 = 0;
       double xTexture =  (points2[1].x-i)/platforms[platformID].textureScale;
       double yTexture0 = SDL_abs((points2[1].y - points2[3].y))/platforms[platformID].textureScale;
       double yTexture1 = SDL_abs((points2[1].y - points2[2].y))/platforms[platformID].textureScale;
       
       if(xTexture >= 1){
         xTexture = 1;
       }
       else if(xTexture <= 0){
         xTexture = 0;
       }

       if(yTexture0 >= 1){
         yTexture0 = 1;
       }
       else if(yTexture0 <= 0){
         yTexture0 = 0;
       }
       if(yTexture1 >= 1){
         yTexture1 = 1;
       }
       else if(yTexture1 <= 0){
         yTexture1 = 0;
       }
       if(platforms[platformID].textureStretchPer){
         yTexture0 = 1;
         yTexture1 = 1;
       }
        if(i < platforms[platformID].x){
           xTexture2 = (double)(platforms[platformID].textureOffsetX/100);
       }
       if(j > platforms[platformID].y+platforms[platformID].height-platforms[platformID].textureScale){
           yTexture2 = (double)(platforms[platformID].textureOffsetY/100);
           printf("%f\n",yTexture0);  
       }

       SDL_Vertex vertex_1 = {{(int)points2[0].x, (int)points2[0].y}, {255, 255, 255, 255}, {xTexture2, yTexture2}};
       SDL_Vertex vertex_2 = {{(int)points2[1].x, (int)points2[1].y}, {255, 255, 255, 255}, {xTexture, yTexture2}};
       SDL_Vertex vertex_3 = {{(int)points2[2].x, (int)points2[2].y}, {255, 255, 255, 255}, {xTexture, yTexture1}};
       SDL_Vertex vertex_4 = {{(int)points2[3].x, (int)points2[3].y}, {255, 255, 255, 255}, {xTexture2, yTexture0}}; 

       SDL_Vertex vertices[] = {
         vertex_1,
         vertex_2,
         vertex_3,
         vertex_4  
       };
      if(j > platforms[platformID].y+platforms[platformID].height-platforms[platformID].textureScale){
        SDL_RenderGeometry(renderer, tex_tile2, vertices, 4, (int[6]){1,2,3,0,1,3}, 6);
      }
      else {
        SDL_RenderGeometry(renderer, platforms[platformID].texture, vertices, 4, (int[6]){1,2,3,0,1,3}, 6);
      }
       
       
       if(j<platforms[platformID].y-2*platforms[platformID].height){
         break;
       }
      j -= platforms[platformID].textureScale;
      }
   }
   SDL_SetRenderDrawColor(renderer,50,50,50,255);
   SDL_RenderDrawLines(renderer,points,5);
}

