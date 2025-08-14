bool Rect_inBounds(double x, double y, double width,double height){
   return (x+width > 0 && y+height > 0 && x < gameWidth && y < gameHeight);  
}

int Player_Grapple(){
   
   double distance_min = (double)5000;


   for(int i = 0;i<sizeof(platforms)/sizeof(platforms[0]);i++){
      if(platforms[i].reserved && platforms[i].grapplable && Rect_inBounds(platforms[i].xDraw,platforms[i].yDraw,platforms[i].widthDraw,platforms[i].heightDraw)){
         double grappleX;
         double grappleY;
         double distance;
         if(player[0].y + player[0].height/2 < platforms[i].y){
            grappleX = player[0].x + player[0].width/2;
            CLAMP_MINMAX(grappleX,platforms[i].x,platforms[i].x+platforms[i].width);
            grappleY = platforms[i].y;
         }
         else if (player[0].y+player[0].height/2 > platforms[i].y+platforms[i].height){
            grappleX = player[0].x + player[0].width/2;
            CLAMP_MINMAX(grappleX,platforms[i].x,platforms[i].x+platforms[i].width);
            grappleY = platforms[i].y+platforms[i].height;
         }
         else{
            grappleY = player[0].y + player[0].height/2;
            if(player[0].x + player[0].width/2 < platforms[i].x){
               grappleX = platforms[i].x;
            }
            else{
               grappleX = platforms[i].x + platforms[i].width;
            }
         }
         
         distance = sqrt(pow(player[0].x + player[0].width/2-grappleX,2)+pow(player[0].y + player[0].height/2-grappleY,2));

         if(distance < distance_min){
            player[0].grappleX = grappleX;
            player[0].grappleY = grappleY;
            player[0].grappleLength = distance;
            distance_min = distance;
         }
      }
   }
   if(distance_min > 150/2){
      return -1;
   }

   // Calculate grapple angle

   player[0].grappleAngle = atan((player[0].y+player[0].height/2-player[0].grappleY)/(player[0].x+player[0].width/2-player[0].grappleX));
   if(player[0].x+player[0].width/2-player[0].grappleX < 0){
      player[0].grappleAngle += PI;
   } 

   player[0].grappling = true;
   
   player[0].jumpVelo = 0;
   if(player[0].grappleLength > 0.1){
      player[0].grappleAngularVelo = (-(player[0].veloX + player[0].groundPoundX+player[0].displacementVeloX)*sin(player[0].grappleAngle) + (player[0].veloY+500*player[0].groundPound+player[0].jumpVelo+player[0].displacementVeloY)*cos(player[0].grappleAngle))/(player[0].grappleLength+10);
   }
   else{
      player[0].grappleAngularVelo = 0;
   }
   player[0].groundPound = false;
   return 0;
   
}


void FPlayer_Special(){
   if(player[0].special == 1){
      // Attack
      if(player[0].specialDelay >= player[0].specialDelay){
      player[0].attack = true;
      player[0].playerControl = 0.3;
      player[0].specialDelay = 0;
      Mix_PlayChannel(-1,Sound_slash,0);
      if(player[0].direction > 0){
         player[0].attackDirection = 1;
         player[0].attackX = player[0].x+player[0].width;
      }
      else{
         player[0].attackDirection = -1;
         player[0].attackX = player[0].x-player[0].width;
      }
      player[0].attackY = player[0].y;
   }
   }
   else if(player[0].special == 2){
     if(player[0].veloY+player[0].jumpVelo > 100){
      player[0].veloY = 100-player[0].jumpVelo;
      player[0].drawTrails = true;
     }   
   }
   else if(player[0].special == 4){
      if(player[0].specialDelayTimer >= player[0].specialDelay){
         Mix_PlayChannel(-1,Sound_woosh,0);
         
         player[0].specialDelayTimer = 0;
         player[0].drawTrails = true;
         player[0].veloX = player[0].direction*700;
         player[0].veloY = 0;
         player[0].jumpVelo = 0;
      }
      
   }
   else if(player[0].special == 5){
      if(player[0].specialDelay >= 500 && player[0].arrowPull < 300){
         player[0].arrowPull += 800*app.deltaTime;
      }
   }
   else if(player[0].special == 6 && player[0].specialDelayTimer >= player[0].specialDelay && player[0].projectileThrown < 3){
         player[0].projectileThrown++;
        
         addProjectile(false,player[0].x+player[0].width/2,player[0].y+player[0].height/3,player[0].direction*300*cos(player[0].ProjectileAngle*PI/180),300*sin(player[0].ProjectileAngle*PI/180),2);
         player[0].specialDelayTimer = 0;
         
      }
   else if(player[0].special == 7){
       if(!player[0].grappling && player[0].grappleFailed < 210){
         if(Player_Grapple() == -1){
            player[0].grappleFailed = 255;
         }
         
       }   
   }
   
}
void FEnemy_Movement(){
   for(int i = 0;i<sizeof(enemy)/sizeof(enemy[0]);i++){
      if(enemy[i].reserved && !enemy[i].killed){
         
         double distance = sqrt(pow(enemy[i].x-player[0].x,2)+pow(enemy[i].y-player[0].y,2));         
         if(distance <= 300){
         if(enemy[i].type == 1){
          enemy[i].angle  = atan((enemy[i].y - player[0].y)/(enemy[i].x - player[0].x));
         if(enemy[i].x < player[0].x){
            enemy[i].angle += PI;
         }

         enemy[i].accX = -500*cos(enemy[i].angle);
         enemy[i].accY = -500*sin(enemy[i].angle);
         
          enemy[i].veloX += (enemy[i].accX)*app.deltaTime;
          enemy[i].veloY += (enemy[i].accY)*app.deltaTime;
          enemy[i].veloX *= pow(0.8-0.7*fabs(cos(enemy[i].angle)),app.deltaTime);
          enemy[i].veloY *= pow(0.8-0.7*fabs(sin(enemy[i].angle)),app.deltaTime);
          enemy[i].bumpX *= pow(0.2,app.deltaTime);
          if(SDL_abs(enemy[i].veloX) > enemy[i].maxSpeed){
            if(enemy[i].veloX>0){
              enemy[i].veloX = enemy[i].maxSpeed;
            }
            else{
               enemy[i].veloX = -enemy[i].maxSpeed;
            } 
          }
          if(SDL_abs(enemy[i].veloY) > enemy[i].maxSpeed){
            if(enemy[i].veloY>0){
              enemy[i].veloY = enemy[i].maxSpeed;
            }
            else{
               enemy[i].veloY = -enemy[i].maxSpeed;
            }
            
          } 
         
         enemy[i].veloX *= pow(0.8,app.deltaTime);
          enemy[i].veloY *= pow(0.8,app.deltaTime);
         enemy[i].x += (enemy[i].veloX+enemy[i].bumpX)*app.deltaTime;
          enemy[i].y += (enemy[i].veloY)*app.deltaTime;
         }  
         else if (enemy[i].type == 2){
            enemy[i].direction = -1;
            if(player[0].x - enemy[i].x > 0){
               enemy[i].direction = 1;
            }
            enemy[i].accX = enemy[i].direction*400;
            enemy[i].textureAnimationInt += fabs(enemy[i].veloX)/4*app.deltaTime;
            
            enemy[i].veloX += enemy[i].accX*app.deltaTime;
            enemy[i].veloY += (enemy[i].accY + GRAVITY)*app.deltaTime;
            
            if(player[0].y+player[0].height < enemy[i].y+enemy[i].height - player[0].height && enemy[i].onPlatform){
               enemy[i].jumpVelo = -175;
            }
            if(enemy[i].veloX > enemy[i].maxSpeed){
               enemy[i].veloX = enemy[i].maxSpeed;
            }
            else if (enemy[i].veloX < -enemy[i].maxSpeed){
               enemy[i].veloX = -enemy[i].maxSpeed;
            }
            enemy[i].veloX *= pow(0.05,app.deltaTime);
            enemy[i].bumpX *= pow(0.1,app.deltaTime);
            enemy[i].x += (enemy[i].veloX + enemy[i].bumpX)*app.deltaTime;
            enemy[i].y += (enemy[i].veloY + enemy[i].jumpVelo)*app.deltaTime;
            
         }
      }
   }
   }
}
void FPlayer_Movement(){
    if(!level.Started){
      if(player[0].keys.left || player[0].keys.right){
         level.Started = true;
      }
    }
    if(player[0].y > mapData.yMax){
        FGameRestart();
    }
   for(int i = 0;i<sizeof(player)/sizeof(player[0]);i++){
      if(i > 0 && !mapData.ghostInGame){
         continue;
      }
   if(player[i].playerControl < 1){
      player[i].playerControl += 4*app.deltaTime;
      if(player[i].playerControl >= 1){
         player[i].playerControl = 1;
      }
   }
   player[i].idleIndex += 2*app.deltaTime;

   if(SDL_abs(player[i].veloX) > 10 && player[i].onPlatform && player[i].particleTimer > 50 + rand()%100){
       addParticle(tex_blank,player[i].x+player[i].width/2-5,player[i].y+player[i].height-5,0,0,10,200,200,200,rand()%360);
       player[i].particleTimer = 0;
   }
   else if (SDL_abs(player[i].veloY)> 10 && player[i].onWall && player[i].particleTimer > 50 + rand()%100){
       addParticle(tex_blank,player[i].x+(player[i].width)*(player[i].onWall<0)-5,player[i].y,0,0,10,200,200,200,rand()%360);
       player[i].particleTimer = 0;
   }

   if (player[i].idleIndex >= 20){
      player[i].idleIndex = 0;
   }
   
     if(!player[i].keys.up){
      player[i].jumpBool = true;
      if(!player[i].onPlatform && player[i].special == 3 && player[i].doubleJump != -1){
         player[i].doubleJump = 1;
      } 
   }

   if(player[i].keys.down){
      if(!player[i].onPlatform && !player[i].grappling){
         player[i].drawTrails = true;
         player[i].groundPound = true;
         player[i].poundHeight = player[i].y;
      }
      player[i].playerControl = 0.25;
      
   }
   else if (player[i].keys.up && ((player[i].jumpBool && player[i].onPlatform) || (player[i].special == 3 && player[i].doubleJump == 1))){
      player[i].jumpBool = false;
      player[i].jumpVelo = -175-100*(player[i].doubleJump == 1);
      if(!player[i].onPlatform){
         player[i].veloY = 0;
         player[i].doubleJump = -1;
         if(i == 0){
            player[i].drawTrails = true;
         }
      }

      if(i == 0){
        Mix_PlayChannel(-1,Sound_Jump,0); 
      }
   } 
   if (player[i].keys.left){
      player[i].animationIndex += 20*app.deltaTime;
      player[i].direction = -1;
      if(!player[i].grappling){
        player[i].accX = 500*(-(player[i].width+player[i].height)/40-3.0f/5.0f*(player[i].keys.shift))*player[i].playerControl;
      if(SDL_abs(player[i].veloX) > 10){
         player[i].stepSoundCount += (1000 - 500*(!player[i].keys.shift))*app.deltaTime;
      } 
      }
      else{
      if(player[i].grappleAngle < PI && player[i].grappleAngle > 0){
         player[i].grappleAngularAcc = 200/player[i].grappleLength;
      }
      else{
         player[i].grappleAngularAcc = -200/player[i].grappleLength;
      }
      }
      
          
   }
   else if (player[i].keys.right){
      player[i].animationIndex += 20*app.deltaTime;
      player[i].direction = 1;
      if(!player[i].grappling){
        player[i].accX = 500*((player[i].width+player[i].height)/40+3.0f/5.0f*(player[i].keys.shift))*player[i].playerControl;
      if(SDL_abs(player[i].veloX) > 10){
         player[i].stepSoundCount += (1000 - 500*(!player[i].keys.shift))*app.deltaTime;
      } 
      }
      else {
      if(player[i].grappleAngle < PI && player[i].grappleAngle > 0){
         player[i].grappleAngularAcc = -200/player[i].grappleLength;
      }
      else{
         player[i].grappleAngularAcc =  200/player[i].grappleLength;
      }
   }
      
   }
   else {player[i].accX = 0;player[i].grappleAngularAcc = 0;}


   // If grappling transform the movement
   
   
   
   
   
   
   if(player[i].keys.c){
      FPlayer_Special();
   }
   if(!player[i].keys.c){
      if(player[i].special == 5 && player[i].arrowPull > 10 && player[i].specialDelayTimer >= player[0].specialDelay){
         addProjectile(false,player[i].x+player[i].width/2,player[i].y+player[i].height/3,player[i].arrowPull*3*cos(player[i].ProjectileAngle*PI/180),player[i].arrowPull*3*sin(player[i].ProjectileAngle*PI/180),1);
         player[0].specialDelayTimer = 0;
      }
      if(player[i].special == 7 && player[i].grappling){
         player[i].grappling = false;
         player[i].veloX = -player[i].grappleLength*player[i].grappleAngularVelo*sin(player[i].grappleAngle);
         player[i].veloY =  player[i].grappleLength*player[i].grappleAngularVelo*cos(player[i].grappleAngle);
      }
   }
   
   if(player[i].canTake >= 0 && player[i].keys.e && !specials[player[i].canTake].taken){
      specials[player[i].canTake].taken = true;
      Mix_PlayChannel(-1,Sound_pickup,0);
      player[i].special = specials[player[i].canTake].type;
      if(i == 0){
         player[0].specialshow = 0;
      }
      player[i].specialDelayTimer = 5000;
      
      //// Set the timer of usage of special
       
      player[i].specialDelay = delayTimers_forSpecials[player[i].canTake];
   }
   
   player[i].particleTimer += 1000*app.deltaTime;
   if (player[i].onWall){
      if(player[i].veloY>10){
         player[i].wallHangingCount += 1000*app.deltaTime;
      }
      
     if(player[i].veloY+player[i].jumpVelo > 100){
        player[i].veloY = 100-player[i].jumpVelo;    
     }
     if (player[i].keys.up && player[i].jumpBool){
      player[i].jumpBool = false;
      player[i].veloY = 0;
      player[i].jumpVelo = -175;
      if(i == 0){
       Mix_PlayChannel(-1,Sound_JumpWall,0);  
      }
      
      player[i].wallveloX = 100*player[i].onWall; 
      player[i].playerControl = 0;
      player[i].onWall = false;
     } 
   }
   
   /////
   
   if(level.Started){
      if(!player[i].grappling){
        player[i].veloX += (player[i].accX+player[i].displacementAccelX)*app.deltaTime;
      if(!player[i].groundPound){
         player[i].veloY += (player[i].accY + (GRAVITY)*(SDL_abs(player[i].displacementAccelY) < 10 || SDL_abs(player[i].displacementVeloY) < 10) + player[i].displacementAccelY)*app.deltaTime;
      } 
      }
      else{
         double gravityGrapplePullDown = GRAVITY/player[i].grappleLength*cos(player[i].grappleAngle);
         
        player[i].grappleAngularVelo += (player[i].grappleAngularAcc+gravityGrapplePullDown)*app.deltaTime;
      }
      
      
   }
   /////
   
   if(player[i].grappling){
      player[i].grappleAngularVelo *= pow(0.5,app.deltaTime);
   }
   player[i].veloX *= pow(0.05,app.deltaTime);
   player[i].wallveloX *= pow(0.05,app.deltaTime);
   double player_slope_speed_change = 0;
   if(player[i].onPlatform){player_slope_speed_change = sin(fabs(platforms[player[i].platformIndex].steepness));}
   
   if (fabs(player[i].veloX) >= (1-0.999*player_slope_speed_change)*(player[i].walkingSpeed+player[i].sprintSpeed*(player[i].keys.shift))){
      player[i].veloX = ( (1-0.999*player_slope_speed_change)*(player[i].walkingSpeed+player[i].sprintSpeed*(player[i].keys.shift))*(1-2*(player[i].veloX < 0)));
   }
   if(player[i].grappling){
     // CLAMP_MINMAX(player[i].grappleAngularVelo,-10,10);
   }
   
   ////
   player[i].groundPoundX *= pow(0.2,app.deltaTime);
   if(level.Started && !player[i].dead){
     
      
      
      
      if(!player[i].grappling){
         player[i].x += (player[i].veloX + player[i].groundPoundX + (player[i].wallveloX)*(!player[i].onWall) + player[i].displacementVeloX)*app.deltaTime;
      }
      else{
         player[i].x = player[i].grappleLength*cos(player[i].grappleAngle) + player[i].grappleX - player[i].width/2;
      }
    
      
     if (!player[i].groundPound && !player[i].grappling){
      
         player[i].y += ((player[i].veloY) + player[i].jumpVelo  + player[i].displacementVeloY)*app.deltaTime;
      
      
     }
     else if(player[i].grappling){
      player[i].y = player[i].grappleLength*sin(player[i].grappleAngle) + player[i].grappleY - player[i].height/2;
     }
     else{
      player[i].y += 500*app.deltaTime;
     }

     if(player[i].grappling){
      player[i].grappleAngle+=player[i].grappleAngularVelo*app.deltaTime;
     }
     
     

   }
   ///// 
   player[i].displacementVeloX  *= pow(0.05,app.deltaTime);
   player[i].displacementVeloY  *= pow(0.05,app.deltaTime);
   player[i].displacementAccelX *= pow(0.05,app.deltaTime);
   player[i].displacementAccelY *= pow(0.05,app.deltaTime);
   if(!player[i].onPlatform){
      player[i].accY = 0;
   }
   
   }


   if(mapData.PBTimer>0){
    if(level.Started){
      FapplyMovementGhost();
    }
    
   if(mapData.ghostEnd){
         player[1].keys.up = false;
         player[1].keys.left = false;
         player[1].keys.right = false;
         player[1].keys.down = false;
         player[1].keys.shift = false;
   }
   }
}

void FapplyMovementGhost(){
   if(mapData.ghostInGame){
      if(mapData.PBTimer <= level.timer && mapData.PBTimer > 0){
         mapData.ghostEnd = true;
         return;
      }
      char type[20];
      sprintf(type,"i%d",mapData.ghostCurrentIndex);
      char* msPress = FGetDataMap(level.absolutePath,type,0,level.absolutePathSize);
      mapData.ghostNextInput = atoi(msPress);
      
      if(level.timer < mapData.ghostNextInput-1){return;}
      if(msPress){
         mapData.ghostCurrentIndex++;
      }
      else{return;}
      mapData.tickDifference = ((int)level.timer - mapData.ghostNextInput);
      char* up = FGetDataMap(level.absolutePath,type,1,level.absolutePathSize);
      char* left = FGetDataMap(level.absolutePath,type,2,level.absolutePathSize);
      char* right = FGetDataMap(level.absolutePath,type,3,level.absolutePathSize);
      char* down = FGetDataMap(level.absolutePath,type,4,level.absolutePathSize);
      char* shift = FGetDataMap(level.absolutePath,type,5,level.absolutePathSize);
      char* pX =  FGetDataMap(level.absolutePath,type,6,level.absolutePathSize);
      char* pY =  FGetDataMap(level.absolutePath,type,7,level.absolutePathSize);
      char* pvX =  FGetDataMap(level.absolutePath,type,8,level.absolutePathSize);
      char* pvY =  FGetDataMap(level.absolutePath,type,9,level.absolutePathSize);
      
      player[1].keys.up = (bool)atoi(up);
      player[1].keys.left = (bool)atoi(left);
      player[1].keys.right = (bool)atoi(right);
      player[1].keys.down = (bool)atoi(down);
      player[1].keys.shift = (bool)atoi(shift);
      player[1].x = (float)atoi(pX);
      player[1].y = (float)atoi(pY);
      player[1].veloX = (float)atof(pvX);
      player[1].veloY = (float)atof(pvY);  

      free(up);
      free(left);
      free(right);
      free(down);
      free(shift);
      free(msPress);
   }
}


void arrowMovement(int i){
   if(fabs(projectiles[i].veloX) > 1){
      projectiles[i].angle = (atan(projectiles[i].veloY/projectiles[i].veloX))*180/PI;
   }
   if (projectiles[i].veloX < 0){
     projectiles[i].angle += 180;
   }
   projectiles[i].veloY += projectiles[i].accY*app.deltaTime;
   projectiles[i].x += projectiles[i].veloX*app.deltaTime;
   projectiles[i].y += projectiles[i].veloY*app.deltaTime;
}

void projectileMovement(int i){
   projectiles[i].angle += 360*app.deltaTime;
   if(projectiles[i].angle > 360){
      projectiles[i].angle = 0;
   }

   
   projectiles[i].followAngle = (atan((projectiles[i].y-player[0].y)/(projectiles[i].x-player[0].x)));
   
   if (projectiles[i].x-player[0].x < 0){
     projectiles[i].followAngle += PI;
   }
   double distance = sqrt(pow(projectiles[i].x-player[0].x,2)+pow(projectiles[i].y-player[0].y,2));
   if(distance > 10){
      projectiles[i].accX = -5*cos(projectiles[i].followAngle)*distance;
      projectiles[i].accY = -5*sin(projectiles[i].followAngle)*distance;
   }
   
   projectiles[i].veloX += projectiles[i].accX*app.deltaTime;
   projectiles[i].veloY += projectiles[i].accY*app.deltaTime;
   projectiles[i].veloX *= pow(0.95,app.deltaTime);
   projectiles[i].veloY *= pow(0.95,app.deltaTime);

   CLAMP_MAX(projectiles[i].veloX,400);
   CLAMP_MAX(projectiles[i].veloY,400);
   projectiles[i].x += projectiles[i].veloX*app.deltaTime;
   projectiles[i].y += projectiles[i].veloY*app.deltaTime;
}