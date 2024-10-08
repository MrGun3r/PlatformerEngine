// Normal AABB Collision
int rectCollision(SDL_Rect Rect1, SDL_Rect Rect2){
   return (Rect1.x+Rect1.w > Rect2.x && Rect2.x+Rect2.w > Rect1.x && Rect1.y+Rect1.h > Rect2.y && Rect2.y+Rect2.h > Rect1.y);
}



// Player Platform Collision
int FCheck_Collision(struct Players Player,int platformID){
   double distanceRatio = (Player.x + Player.width/2 - platforms[platformID].x)/(platforms[platformID].width);
   if(platforms[platformID].slopeInv){
      distanceRatio = distanceRatio = 1 - (Player.x + Player.width/2 - platforms[platformID].x)/(platforms[platformID].width);
   } 
    if(distanceRatio >= 1){distanceRatio = 1;}
   if(distanceRatio <= 0){distanceRatio = 0;} 

   return (Player.x+Player.width > platforms[platformID].x && platforms[platformID].x+platforms[platformID].width > Player.x && Player.y+Player.height > platforms[platformID].y-(platforms[platformID].height*sin(platforms[platformID].slope))*distanceRatio && platforms[platformID].y+platforms[platformID].height > Player.y);
}
// Player Platform Collision Response
void FCollision_Response(struct Players *Player,int platformID){
   double distanceRatio = (Player->x - platforms[platformID].x + Player->width/2)/(platforms[platformID].width);
   if(platforms[platformID].slopeInv){
      distanceRatio = 1 - (Player->x + Player->width/2 - platforms[platformID].x)/(platforms[platformID].width);
   }
   if(distanceRatio >= 1){distanceRatio = 1;}
   if(distanceRatio <= 0){distanceRatio = 0;} 
   
   if (SDL_min(SDL_abs(Player->x+Player->width-platforms[platformID].x)+5,SDL_abs(Player->x-platforms[platformID].x-platforms[platformID].width)+5)>SDL_min(SDL_abs(Player->y+Player->height-platforms[platformID].y+platforms[platformID].height*sin(platforms[platformID].slope)*distanceRatio),SDL_abs(Player->y-platforms[platformID].y-platforms[platformID].height)))   
    {
      if (SDL_abs(Player->y + Player->height - platforms[platformID].y +platforms[platformID].height*sin(platforms[platformID].slope)*distanceRatio)>SDL_abs(Player->y - platforms[platformID].y - platforms[platformID].height)){
        Player->y = platforms[platformID].y + platforms[platformID].height;
        
         if(Player->jumpVelo + Player->veloY < 0){
            Player->jumpVelo = 0;
            Player->veloY = 0;
         }    
       }
       else {   
            if(!Player->ghost){
               if(!level.Finished && platforms[platformID].type == 1 && level.checkpointCount >= level.checkpointsSize){
                level.Finished = true;
                camera.scaleReal = 5;
                if(level.campaignLevel){
                  FcheckPB();
                }
                Mix_PlayChannel(-1,Sound_finish,0);
                }
             else if (platforms[platformID].type == 2 && !platforms[platformID].platformUsed){
               platforms[platformID].platformUsed = true;
               level.checkpoints[level.checkpointCount] = level.timer;
               level.checkpointShowTimer = 3000;
               level.checkpointCount++;
               level.LastCheckpointX = platforms[platformID].x + platforms[platformID].width/2;
               level.LastCheckpointY = platforms[platformID].y - Player->height;
               FaddReplay(true);
               level.tempFileMade = true;
               level.keyInputsSize = 0;
               Mix_PlayChannel(-1,Sound_Checkpoint,0);
             }
            }
            
             
             
             Player->y = platforms[platformID].y - Player->height - platforms[platformID].height*sin(platforms[platformID].slope)*distanceRatio;
             Player->onPlatform = true;
            
            
            
         
            if(Player->jumpVelo + Player->veloY > 0){
              Player->jumpVelo = 0;
              Player->veloY = 0;
            }       
         }
    }
    else {
      Player->veloX *= 0;
      if (SDL_abs(Player->x + Player->width - platforms[platformID].x)>SDL_abs(Player->x - platforms[platformID].x - platforms[platformID].width)){
      Player->x = platforms[platformID].x + platforms[platformID].width;
     }
     else {
      Player->x = platforms[platformID].x - Player->width ;
      }

     
      if(Player->x+Player->width/2 > platforms[platformID].x+platforms[platformID].width){
         Player->onWall = 1;
      }
      else{
         Player->onWall = -1;
      }
    }
} 