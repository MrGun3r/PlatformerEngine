// Normal AABB Collision
int rectCollision(SDL_Rect Rect1, SDL_Rect Rect2){
   return (Rect1.x+Rect1.w > Rect2.x && Rect2.x+Rect2.w > Rect1.x && Rect1.y+Rect1.h > Rect2.y && Rect2.y+Rect2.h > Rect1.y);
}

int FCheck_Collision_Rect_Platform(SDL_Rect Rect,int platformID){
   double distanceRatio = (Rect.x + Rect.w/2 - platforms[platformID].x)/(platforms[platformID].width);
   if(platforms[platformID].slopeInv){
      distanceRatio = distanceRatio = 1 - (Rect.x + Rect.w/2 - platforms[platformID].x)/(platforms[platformID].width);
   } 
    if(distanceRatio >= 1){distanceRatio = 1;}
   if(distanceRatio <= 0){distanceRatio = 0;} 

   return (Rect.x+Rect.w > platforms[platformID].x && platforms[platformID].x+platforms[platformID].width > Rect.x && Rect.y+Rect.h > platforms[platformID].y-(platforms[platformID].height*sin(platforms[platformID].slope))*distanceRatio && platforms[platformID].y+platforms[platformID].height > Rect.y);
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
int FCheck_Collision_Enemy(struct Enemy enemy,int platformID){
   double distanceRatio = (enemy.x + enemy.width/2 - platforms[platformID].x)/(platforms[platformID].width);
   if(platforms[platformID].slopeInv){
      distanceRatio = distanceRatio = 1 - (enemy.x + enemy.width/2 - platforms[platformID].x)/(platforms[platformID].width);
   } 
    if(distanceRatio >= 1){distanceRatio = 1;}
   if(distanceRatio <= 0){distanceRatio = 0;} 

   return (enemy.x+enemy.width > platforms[platformID].x && platforms[platformID].x+platforms[platformID].width > enemy.x && enemy.y+enemy.height > platforms[platformID].y-(platforms[platformID].height*sin(platforms[platformID].slope))*distanceRatio && platforms[platformID].y+platforms[platformID].height > enemy.y);
}
// Player Platform Collision Response
void FCollision_Response(struct Players *Player,int platformID){
   double distanceRatio = (Player->x - platforms[platformID].x + Player->width/2)/(platforms[platformID].width);
   if(platforms[platformID].slopeInv){
      distanceRatio = 1 - (Player->x + Player->width/2 - platforms[platformID].x)/(platforms[platformID].width);
   }
   if(distanceRatio >= 1){distanceRatio = 1;}
   if(distanceRatio <= 0){distanceRatio = 0;} 
   
   double topSideThreshold = 10;


   if (SDL_min(SDL_abs(Player->x+Player->width-platforms[platformID].x)+topSideThreshold,SDL_abs(Player->x-platforms[platformID].x-platforms[platformID].width)+topSideThreshold)>SDL_min(SDL_abs(Player->y+Player->height-platforms[platformID].y+platforms[platformID].height*sin(platforms[platformID].slope)*distanceRatio),SDL_abs(Player->y-platforms[platformID].y-platforms[platformID].height)))   
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
             Player->platformIndex = platformID;
             Player->drawTrails = false;
             if(Player->special == 3){
               Player->doubleJump = 0;
             }
             
             if (Player->groundPound){
               Player->groundPound = false;
               for(int i = 0;i<3;i++){
                 double value = (((double)(rand()%100))/100-0.5)*100;
                 addParticle(tex_blank,Player->x+Player->width/2-5+7*(2-i),Player->y+Player->height-5,value,0,15,200,200,200,rand()%360);
                
               }
               Player->playerControl = 1;
               Player->poundPotential = (Player->poundHeight - Player->y);
               if(Player->poundPotential < -50){
                  Player->jumpBool = false;
                  Player->jumpVelo = cos(platforms[platformID].steepness)*(-175+max(1.5*Player->poundPotential,-600));
                  
                  Player->groundPoundX = -sin(platforms[platformID].steepness*(0.5 - platforms[platformID].slopeInv )*2)*(-175+max(1.5*Player->poundPotential,-600));
                  
                  if(!Player->ghost){
                     Mix_PlayChannel(-1,Sound_JumpWall,0);  
                  }
                  Player->veloY = 0; 
               } 
             }         
            else if(Player->jumpVelo + Player->veloY > 0){
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

     
      if(Player->x+Player->width/2 > platforms[platformID].x+platforms[platformID].width && (Player->keys.left)){
        Player->onWall = 1;
      }
      else if(Player->x+Player->width/2 < platforms[platformID].x && Player->keys.right){
         Player->onWall = -1;
      }
    }
} 

void FCollision_Response_Enemy(struct Enemy *enemy,int platformID){
   double distanceRatio = (enemy->x - platforms[platformID].x + enemy->width/2)/(platforms[platformID].width);
   if(platforms[platformID].slopeInv){
      distanceRatio = 1 - (enemy->x + enemy->width/2 - platforms[platformID].x)/(platforms[platformID].width);
   }
   if(distanceRatio >= 1){distanceRatio = 1;}
   if(distanceRatio <= 0){distanceRatio = 0;} 
   
   if (SDL_min(SDL_abs(enemy->x+enemy->width-platforms[platformID].x)+7,SDL_abs(enemy->x-platforms[platformID].x-platforms[platformID].width)+7)>SDL_min(SDL_abs(enemy->y+enemy->height-platforms[platformID].y+platforms[platformID].height*sin(platforms[platformID].slope)*distanceRatio),SDL_abs(enemy->y-platforms[platformID].y-platforms[platformID].height)))   
    {
      if (SDL_abs(enemy->y + enemy->height - platforms[platformID].y +platforms[platformID].height*sin(platforms[platformID].slope)*distanceRatio)>SDL_abs(enemy->y - platforms[platformID].y - platforms[platformID].height)){
        enemy->y = platforms[platformID].y + platforms[platformID].height;
        
         if(enemy->jumpVelo + enemy->veloY < 0){
            enemy->jumpVelo = 0;
            enemy->veloY = 0;
         }    
       }
       else {    
             enemy->y = platforms[platformID].y - enemy->height - platforms[platformID].height*sin(platforms[platformID].slope)*distanceRatio;
             enemy->onPlatform = true;   
            if(enemy->jumpVelo + enemy->veloY > 0){
              enemy->jumpVelo = 0;
              enemy->veloY = 0;
            }       
         }
    }
    else {
      enemy->veloX *= 0;
      if (SDL_abs(enemy->x + enemy->width - platforms[platformID].x)>SDL_abs(enemy->x - platforms[platformID].x - platforms[platformID].width)){
      enemy->x = platforms[platformID].x + platforms[platformID].width;
      enemy->bumpX = 0;
     }
     else {
      enemy->x = platforms[platformID].x - enemy->width ;
      enemy->bumpX = 0;
     }
    }
} 