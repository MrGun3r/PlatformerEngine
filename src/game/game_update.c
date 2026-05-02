void Update_Camera() {
   if(!camera.freeCam){
     camera.x += (-player[0].x-player[0].width/2+gameWidthBase/2 - camera.x)*10*app.deltaTime;
     camera.y += (-player[0].y-player[0].height/2+gameHeightBase/2 - camera.y)*10*app.deltaTime;
   }
   else{
      camera.x += (camera.xReal - camera.x)*10*app.deltaTime;
      camera.y += (camera.yReal - camera.y)*10*app.deltaTime;
   }

   if (camera.x > -gameWidthBase/(2*camera.scale) + gameWidthBase/2 - mapData.xMin) {
       camera.x = -gameWidthBase/(2*camera.scale) + gameWidthBase/2 - mapData.xMin;
   }
   else if (camera.x < gameWidthBase/(2*camera.scale) + gameWidthBase/2 - mapData.xMax){
      camera.x = gameWidthBase/(2*camera.scale) + gameWidthBase/2 - mapData.xMax;
   }

   if (camera.y > -gameHeightBase/(2*camera.scale) + gameHeightBase/2 - mapData.yMin) {
       camera.y = -gameHeightBase/(2*camera.scale) + gameHeightBase/2 - mapData.yMin;
   }
   else if (camera.y < gameHeightBase/(2*camera.scale) + gameHeightBase/2 - mapData.yMax){
      camera.y = gameHeightBase/(2*camera.scale) + gameHeightBase/2 - mapData.yMax;
   }

   camera.scale += ( camera.scaleReal - camera.scale)*app.deltaTime*5;
}
void Update_Movement() {
   FPlayer_Movement();

   if(level.Started){
      FEnemy_Movement();

      // DeathBox Movement
      for(int i = 0;i<sizeof(deathbox)/sizeof(deathbox[0]);i++){
         if(deathbox[i].reserved){
            deathboxMovement(i);
         }
      }
      // Light movement
      for(int i = 0;i<sizeof(light)/sizeof(light[0]);i++){
         if(light[i].reserved){
           lightMovement(i); 
         }
      }
      // Displacement movement
      for(int i = 0;i<sizeof(displacement)/sizeof(displacement[0]);i++){
         if(displacement[i].reserved){
            displacementMovement(i);
         }
      }
   
   }
   
}
void Update_DamagePopups() {
   for(int i = 0;i<sizeof(damagepopups)/sizeof(damagepopups[0]);i++){
      if(damagepopups[i].reserved){
         
         damagepopups[i].opacity -= 255*app.deltaTime;
         if(damagepopups[i].opacity < 0){
            damagepopups[i].opacity = 0;
            damagepopups[i].reserved = false;
         }
         damagepopups[i].x += damagepopups[i].veloX*app.deltaTime;
         damagepopups[i].y += damagepopups[i].veloY*app.deltaTime;
      }
   }
}
void Update_Enemy() {
   for(int i = 0;i<sizeof(enemy)/sizeof(enemy[0]);i++){
      if(enemy[i].reserved && !enemy[i].killed){
         
         if(player[0].arrowPull < 10 || player[0].special == 6){
          double distance_player_enemy = sqrt(pow(player[0].x-enemy[i].x,2)+pow(player[0].y-enemy[i].y,2));
         
          if(distance_player_enemy < 300 && (player[0].enemyTargetDistance > distance_player_enemy || player[0].enemyTarget == -1) && (fabs(player[0].x-enemy[i].x) > 1)){
            player[0].enemyTargetDistance = distance_player_enemy;
            player[0].enemyTarget = i;
          }
         }
         
         if(enemy[i].attackCoolDown <= 200){
            enemy[i].attackCoolDown += 200*app.deltaTime;
         }
         if(enemy[i].type == 2){
            enemy[i].onPlatform = false;
         }

         if(!player[0].dead && rectCollision((SDL_Rect){enemy[i].x+enemy[i].width*0.25,enemy[i].y+enemy[i].height*0.25,enemy[i].width*0.5,enemy[i].height*0.5},(SDL_Rect){player[0].x,player[0].y,player[0].width,player[0].height})){
            playerHurt(0,10);
         }

         if(player[0].special == 1 && player[0].attack && enemy[i].attackCoolDown > 100 && rectCollision((SDL_Rect){player[0].attackX,player[0].attackY,player[0].attackSize,player[0].attackSize},(SDL_Rect){enemy[i].x,enemy[i].y,enemy[i].width,enemy[i].height})){
            enemyHurt(i,10);
            enemy[i].bumpX = 175*player[0].attackDirection;
         } 
      }
   }
}
void Update_Textpopups() {
   for(int i = 0;i<sizeof(textpopups)/sizeof(textpopups[0]);i++){
      if(textpopups[i].reserved){ 
         if(rectCollision((SDL_Rect){textpopups[i].x,textpopups[i].y,textpopups[i].width,textpopups[i].height},(SDL_Rect){player[0].x,player[0].y,player[0].width,player[0].height})){
            if(textpopups[i].showProgress < 255){
               if(textpopups[i].showProgress < 252){
                  Mix_PlayChannel(-1,Sound_textTick,0);
               }
               textpopups[i].showProgress += 1000*app.deltaTime;
               
               if(textpopups[i].showProgress >= 255){
                 textpopups[i].showProgress = 255;
               }
            }
         }
         else{
            textpopups[i].showProgress -= 1000*app.deltaTime;
            if(textpopups[i].showProgress<0){
              textpopups[i].showProgress = 0;
            }
         }
      }
   }
}
void Update_Projectiles() {
   for(int i = 0;i<sizeof(projectiles)/sizeof(projectiles[0]);i++){
      if(projectiles[i].reserved){
         if(projectiles[i].projectileType == 1){
            arrowMovement(i);
         }
         else if(projectiles[i].projectileType == 2){
            projectileMovement(i);
         }   
      
         projectiles[i].despawnTime += 1*app.deltaTime;
         if(projectiles[i].despawnTime > 5){
            projectiles[i].reserved = false;
            if(!projectiles[i].fromEnemy){
             player[0].projectileThrown--;  
            }
            projectiles[i].despawnTime = 0;
         }
         if((fabs(projectiles[i].veloX) > 10 || fabs(projectiles[i].veloY) > 10)){
            if(projectiles[i].projectileType == 1){
               for(int j = 1;j<sizeof(platforms)/sizeof(platforms[0]);j++){
               if(platforms[j].reserved && platforms[j].collidable){
                  if(FCheck_Collision_Rect_Platform((SDL_Rect){projectiles[i].x,projectiles[i].y,projectiles[i].width,projectiles[i].height},j)){
                     projectiles[i].veloX = 0;
                     projectiles[i].veloY = 0;
                     projectiles[i].accY = 0;
                     break;
                   }
               }
         }
            }
            
         // Arrow Enemy Collision
         if(!projectiles[i].fromEnemy){
            for(int j = 0;j<sizeof(enemy)/sizeof(enemy[0]);j++){
               if(enemy[j].reserved && !enemy[j].killed){
                  if(rectCollision((SDL_Rect){projectiles[i].x,projectiles[i].y,projectiles[i].width,projectiles[i].height},(SDL_Rect){enemy[j].x,enemy[j].y,enemy[j].width,enemy[j].height})){
                     enemyHurt(j,0);
                     if(projectiles[i].veloX > 0){
                        enemy[j].bumpX = 175;
                     }
                     else{
                        enemy[j].bumpX = -175;
                     }
                     
                     projectiles[i].reserved = false;
                     if(projectiles[i].projectileType == 2 && !projectiles[i].fromEnemy){
                      player[0].projectileThrown--;
                     }
                     break;
                   }
               }
         }
         }
         else{
            // Player collision
            if(rectCollision((SDL_Rect){projectiles[i].x,projectiles[i].y,projectiles[i].width,projectiles[i].height},(SDL_Rect){player[0].x,player[0].y,player[0].width,player[0].height})){
              playerHurt(0,10);
            }

            // Parry mechanism
            if(player[0].attack && rectCollision((SDL_Rect){projectiles[i].x,projectiles[i].y,projectiles[i].width,projectiles[i].height},(SDL_Rect){player[0].attackX,player[0].attackY,player[0].attackSize,player[0].attackSize})){
               player[0].attack = false;
               projectiles[i].veloX *= -1;
               projectiles[i].veloY *= -1;
            } 
         }
         

         }
         
         
      }
   }
}
void Update_Finished_Level() {
   
   if(level.Finished){
      if(level.endTransition < 1){
         level.endTransition += 2*app.deltaTime;
      }
      if(level.endShowCoins < 100){
         level.endShowCoins += 200*app.deltaTime;
      }
      camera.scaleReal = 6;
   }
}
void Update_Platforms() {
   for (int i = 0;i<sizeof(platforms)/sizeof(platforms[0]);i++){
      if(platforms[i].reserved){

     // Texture Animation
      if(platforms[i].textureAnimationTime >= 1){
         platforms[i].textureAnimationTimer += 1000*app.deltaTime;
         if(platforms[i].textureAnimationTimer > platforms[i].textureAnimationTime){
            platforms[i].textureAnimationInt++;
            platforms[i].textureAnimationInt = (int)platforms[i].textureAnimationInt % ((int)textures[platforms[i].textureInt].textureAnimationSize);
            platforms[i].textureAnimationTimer = 0;
         }
      }
      else{
        platforms[i].textureAnimationInt = 0; 
        platforms[i].textureAnimationTimer = 0;
      }
      // Texture offset movement
      platforms[i].textureOffsetX += platforms[i].textureOffsetX_Move*app.deltaTime;
      platforms[i].textureOffsetY += platforms[i].textureOffsetY_Move*app.deltaTime;
      platforms[i].textureOffsetX = fmod(platforms[i].textureOffsetX,100);
      platforms[i].textureOffsetY = fmod(platforms[i].textureOffsetY,100);
      

      // Platform Movement
      platformMovement(i);

      // Player Platform Collision
      if((platforms[i].collidable || platforms[i].type != 0)){
      if(FCheck_Collision(player[1],i) && platforms[i].collidable){
         FCollision_Response(&player[1],i);
      }
      if(FCheck_Collision(player[0],i) && platforms[i].collidable){
         FCollision_Response(&player[0],i);
      }
      else if (FCheck_Collision(player[0],i) && !platforms[i].collidable){
         if(platforms[i].type == 1){
            if(!level.Finished && !level.transitionToLevel && platforms[i].type == 1 && level.checkpointCount >= level.checkpointsSize){
                
                
               FcheckPB();
                
                if(!platforms[i].NofinishAnimation){
                  level.Finished = true;
                  Mix_PlayChannel(-1,Sound_finish,0);
                }
                else{    
                  level.transitionToLevel = true;
                  FSaveProfile();
                }
                
                
             }
         }
         else if(platforms[i].type == 2 && !platforms[i].platformUsed){
               platforms[i].platformUsed = true;
               level.checkpoints[level.checkpointCount] = level.timer;
               level.checkpointShowTimer = 3000;
               level.checkpointCount++;
               FaddReplay(true);
               level.tempFileMade = true;
               level.keyInputsSize = 0;
               level.LastCheckpointX = platforms[i].x + platforms[i].width/2;
               level.LastCheckpointY = platforms[i].y + platforms[i].height/2;
               Mix_PlayChannel(-1,Sound_Checkpoint,0);
         }
      }
      // Enemy Collision
      for (int j = 0;j<sizeof(enemy)/sizeof(enemy[0]);j++){
         if(FCheck_Collision_Enemy(enemy[j],i)){
            enemy[j].platformIndex = i;
            FCollision_Response_Enemy(&enemy[j],i);
         }
      }
      }
      } 
   }
}
void Update_Player_Record() {
   if(app.inputChange && !level.Finished && level.Started){
      char keyInputChange[200];
      sprintf(keyInputChange,"i%d:%d,%d,%d,%d,%d,%d,%d,%d,%f,%f;\n\0",mapData.fileadditionIndex,(int)level.timer,player[0].keys.up == 1,
                                                                                                                 player[0].keys.left == 1,
                                                                                                                 player[0].keys.right == 1,
                                                                                                                 player[0].keys.down == 1,
                                                                                                                 player[0].keys.shift == 1,
                                                                                                                 (int)player[0].x,(int)player[0].y,player[0].veloX,player[0].veloY);
      mapData.fileadditionIndex++;
      SDL_memcpy(&level.keyInputs[level.keyInputsSize],keyInputChange,len(keyInputChange));  
      level.keyInputsSize += len(keyInputChange);
      if(level.keyInputsSize >= 1024){
         FaddReplay(false);
         level.tempFileMade = true;
         level.keyInputsSize = 0;
      }
      app.inputChange = false;
   }
}
void Update_Triggers() {
   for(int j = 1 ;j<sizeof(triggers)/sizeof(triggers[0]);j++){
         if(triggers[j].reserved){
            if(!triggers[j].triggerUsed){
               if(rectCollision((SDL_Rect){player[0].x,player[0].y,player[0].width,player[0].height},(SDL_Rect){triggers[j].x,triggers[j].y,triggers[j].width,triggers[j].height})){
               triggers[j].triggerUsed = true;      
              }
             }
          else{
            if(triggers[j].useDelayTimer >= triggers[j].useDelay && !triggers[j].timerStart){
               triggers[j].useDelayTimer = 0;
               triggers[j].timerStart = true;
               if(triggers[j].triggerType == 0){
                  if((int)triggers[j].Value1 >= 0){
                  platforms[(int)triggers[j].Value3].moveNodeInt = (int)triggers[j].Value1;
                  platforms[(int)triggers[j].Value3].x = movenodes[(int)triggers[j].Value1].positions[0][0] - (platforms[(int)triggers[j].Value3].width-25)/2;
                  platforms[(int)triggers[j].Value3].y = movenodes[(int)triggers[j].Value1].positions[0][1] - (platforms[(int)triggers[j].Value3].height-25)/2;   
                  }
                  platforms[(int)triggers[j].Value3].moveSpeed = triggers[j].Value2;
               } 
               else if(triggers[j].triggerType == 1){
                  if((int)triggers[j].Value1 >= 0){
                  deathbox[(int)triggers[j].Value3].moveNodeInt = (int)triggers[j].Value1;
                  deathbox[(int)triggers[j].Value3].x = movenodes[(int)triggers[j].Value1].positions[0][0] - (deathbox[(int)triggers[j].Value3].width-25)/2;
                  deathbox[(int)triggers[j].Value3].y = movenodes[(int)triggers[j].Value1].positions[0][1] - (deathbox[(int)triggers[j].Value3].height-25)/2;   
                  }
                  deathbox[(int)triggers[j].Value3].moveSpeed = triggers[j].Value2;
               } 
               else if(triggers[j].triggerType == 2){
                  if((int)triggers[j].Value1 >= 0){
                  light[(int)triggers[j].Value3].moveNodeInt = (int)triggers[j].Value1;
                  light[(int)triggers[j].Value3].x = movenodes[(int)triggers[j].Value1].positions[0][0] - (light[(int)triggers[j].Value3].width-25)/2;
                  light[(int)triggers[j].Value3].y = movenodes[(int)triggers[j].Value1].positions[0][1] - (light[(int)triggers[j].Value3].height-25)/2;   
                  }
                  light[(int)triggers[j].Value3].moveSpeed = triggers[j].Value2;
               }
               else if(triggers[j].triggerType == 3){
                  if((int)triggers[j].Value1 >= 0){
                  displacement[(int)triggers[j].Value3].moveNodeInt = (int)triggers[j].Value1;
                  displacement[(int)triggers[j].Value3].x = movenodes[(int)triggers[j].Value1].positions[0][0] - (displacement[(int)triggers[j].Value3].width-25)/2;
                  displacement[(int)triggers[j].Value3].y = movenodes[(int)triggers[j].Value1].positions[0][1] - (displacement[(int)triggers[j].Value3].height-25)/2;   
                  }
                  displacement[(int)triggers[j].Value3].moveSpeed = triggers[j].Value2;
               }   
            }
            else{
               triggers[j].useDelayTimer += 1000*app.deltaTime;
               
            } 
         }

         if(triggers[j].timerStart && triggers[j].reuseDelay >= 1){
            triggers[j].reuseDelayTimer += 1000*app.deltaTime;
            if(triggers[j].reuseDelayTimer >= triggers[j].reuseDelay){
               triggers[j].triggerUsed = false;
               triggers[j].timerStart = false;
               triggers[j].reuseDelayTimer = 0;
            }
         }
     }
      }
}
void Update_Player() {
   if(player[0].special == 1){
      if(player[0].specialDelayTimer >= player[0].specialDelay){
         player[0].attack = false;
      }
        
      if(player[0].specialDelayTimer < player[0].specialDelay){
         player[0].attackDrawInt = (int)((player[0].specialDelayTimer)*6/player[0].specialDelay);
      }
   }
   if(player[0].enemyTarget != -1 && (enemy[player[0].enemyTarget].killed)){
      player[0].enemyTarget = -1;
   }
   
   if(player[0].grappleFailed > 0){
      player[0].grappleFailed -= 500*app.deltaTime;
      CLAMP_MIN(player[0].grappleFailed,0);
   }

   // Player special delay usage
   if(player[0].specialDelayTimer < 5*player[0].specialDelay){
         player[0].specialDelayTimer += 1000*app.deltaTime;
   }
   
   // Player Collision
   player[0].onPlatform = 0;
   player[0].onWall = 0;
   player[1].onPlatform = 0;
   player[1].onWall = 0;

   if(player[0].dead){
      player[0].deathAnimationTimer += 10000*app.deltaTime;
      if(player[0].deathAnimationTimer > 10000){
         player[0].dead = false;
         player[0].deathAnimationTimer = 0;
         if(level.checkpointCount <= 0){
           FGameRestart(); 
         }
         else{
            player[0].x = level.LastCheckpointX;
            player[0].y = level.LastCheckpointY;
            player[0].health = 30;
            player[0].invisTimer = 2000;
         }
      }
   }

   if (player[0].drawTrails){
      player[0].trailTime += 1000*app.deltaTime;
   if (player[0].trailTime >= 50 && !player[0].dead){
      player[0].playerTrails[player[0].trailIndex][0] = player[0].x;
      player[0].playerTrails[player[0].trailIndex][1] = player[0].y;
      player[0].playerTrails[player[0].trailIndex][2] = 255;
      player[0].playerTrails[player[0].trailIndex][3] = (int)(player[0].animationIndex) % 6;
      player[0].playerTrails[player[0].trailIndex][4] = (int)(1-player[0].direction)/2;
      player[0].trailIndex++;
      player[0].trailIndex %= 5;
      player[0].trailTime = 0;
   }
   
   }

   for(int i = 0;i<5;i++){
         if(player[0].playerTrails[i][2] > 0){
            player[0].playerTrails[i][2] -= 700*app.deltaTime;
            if (player[0].playerTrails[i][2] < 0){
               player[0].playerTrails[i][2] = 0;
            }
         }  
   }
   
   if(player[0].canTake >= 0){
      player[0].EButtonOpacity += 750*app.deltaTime;
      if(player[0].EButtonOpacity > 230){
         player[0].EButtonOpacity = 230;
      }
   }
   else{
      player[0].EButtonOpacity -= 750*app.deltaTime;
      if(player[0].EButtonOpacity < 0){
         player[0].EButtonOpacity = 0;
      }
   }
   for(int i = 0;i<sizeof(player)/sizeof(player[0]);i++){
     
      if(i > 0 && !mapData.ghostInGame){
         continue;
      }
      if(player[i].invisTimer > 0){
         player[i].invisTimer -= 1000*app.deltaTime;
      }
      
      /// Player play sounds
     if(player[i].stepSoundCount > 100 && player[i].onPlatform){
      if(player[i].stepSoundInt == 0){
          if(i == 0){
       Mix_PlayChannel(-1,Sound_Step1,0);
          }
      }
      else if(player[i].stepSoundInt == 1){
          if(i == 0){
         Mix_PlayChannel(-1,Sound_Step2,0);
          }
      }
      player[i].stepSoundCount = 0;
      player[i].stepSoundInt = (player[i].stepSoundInt + 1) % 2; 
     }
     if(player[i].wallHangingCount > 90 && player[i].onWall){
      if(i == 0){
        Mix_PlayChannel(-1,Sound_Wall,0); 
      }
      
      player[i].wallHangingCount = 0;
     } 
     
      for(int j = 0;j<sizeof(displacement)/sizeof(displacement[0]);j++){
       if(displacement[j].reserved){
         if(rectCollision((SDL_Rect){player[i].x,player[i].y,player[i].width,player[i].height},(SDL_Rect){displacement[j].x,displacement[j].y,displacement[j].width,displacement[j].height})){
            if(displacement[j].powerType == 0){
               if(displacement[j].type % 2 == 0){
                player[i].displacementVeloX = displacement[j].power*cos(displacement[j].type*PI/2);
               }
               else {
                  player[i].displacementVeloY = displacement[j].power*sin(-displacement[j].type*PI/2);
                  player[i].veloY = 0;
               }
            }
            else if(displacement[j].powerType == 1){
               if(displacement[j].type % 2 == 0){
                  player[i].displacementAccelX = displacement[j].power*cos(displacement[j].type*PI/2);
               }
               else{
                  player[i].displacementAccelY = displacement[j].power*sin(-displacement[j].type*PI/2);
               }  
            }
         }
         
       }
      }

      if(player[0].enemyTarget != -1){
         player[0].ProjectileAngle = atan2((player[0].y-enemy[player[0].enemyTarget].y),(player[0].x-enemy[player[0].enemyTarget].x))*180/PI;
      if(player[0].arrowPull < 10){
         player[0].enemyTargetDistance = sqrt(pow(player[0].x-enemy[player[i].enemyTarget].x,2)+pow(player[0].y-enemy[player[0].enemyTarget].y,2));
      }
      }
      else{
         player[0].ProjectileAngle = 0;
      }
      if(!player[0].keys.c){
         if(player[0].arrowPull > 0){
            player[0].arrowPull -= 2000*app.deltaTime;
         }
         else{
           player[0].arrowPull = 0; 
         }
      }
      if(player[0].enemyTarget != -1 && player[0].x-enemy[player[0].enemyTarget].x > 0){
         player[0].ProjectileAngle += 180;
      }     
   }
}
void Update_UI_Elements() {
   if(level.resetTransition>0){
      level.resetTransition -= 1000*app.deltaTime;
   }
   
   if(level.checkpointShowTimer > 0){
      level.checkpointShowTimer -= 1000*app.deltaTime;
   }

   level.coinsReceivedOpacity -= 255*app.deltaTime;
   if(level.coinsReceivedOpacity < 0){
      level.coinsReceivedOpacity = 0;
   }


}
void Update_Particles() {
   for (int i = 0;i<sizeof(particles)/sizeof(particles[0]);i++){
      if(particles[i].reserved){
         particles[i].width -= 20*app.deltaTime;
         particles[i].height -= 20*app.deltaTime;
         particles[i].x += particles[i].veloX*app.deltaTime;
         particles[i].y += particles[i].veloY*app.deltaTime;
         
         if(particles[i].width < 0 || particles[i].height < 0){
            particles[i].width = 0;
            particles[i].height = 0;
            particles[i].reserved = false;
         }
      }
   }
}
void Update_Scripts() {
   for(int i = 0;i<sizeof(scripts)/sizeof(scripts[0]);i++){
      if(scripts[i].reserved){
         if(rectCollision((SDL_Rect){player[0].x,player[0].y,player[0].width,player[0].height},(SDL_Rect){scripts[i].x,scripts[i].y,scripts[i].width,scripts[i].height})){
         if(!scripts[i].used){
            scripts[i].used = true;   
            scripts[i].startTimer = true;
         }
         }
         if(scripts[i].execute){
            ExecuteScript(scripts[i].scriptInt);
            scripts[i].execute = false;
            scripts[i].useDelayTimer = 0;
            
         }
         // Increment use delay
         if(scripts[i].startTimer){
          if(scripts[i].useDelay >= 1 && scripts[i].useDelayTimer <= scripts[i].useDelay){
            scripts[i].useDelayTimer += 1000*app.deltaTime;
     
          }
          else{
            scripts[i].execute = true;
            scripts[i].startTimer = false;
          }  
         }
         // Increment reuse delay
         if(scripts[i].used && scripts[i].reuseDelay >= 1){
           scripts[i].reuseDelayTimer += 1000*app.deltaTime;
           
           if(scripts[i].reuseDelayTimer > scripts[i].reuseDelay){
            scripts[i].used = false;
            scripts[i].reuseDelayTimer = 0;
           }
         }
      }
   }
}
void Update_Specials() {
   player[0].canTake = -1;
   for(int i = 0;i<sizeof(specials)/sizeof(specials[0]);i++){
      if(specials[i].reserved){
         if(rectCollision((SDL_Rect){player[0].x,player[0].y,player[0].width,player[0].height},(SDL_Rect){specials[i].x,specials[i].y,specials[i].width,specials[i].height})){
            player[0].canTake = i;
            break;
         }
      }
   }
}
void FUpdate_Data(){

   Update_Camera();
   
   app.backgroundMoving += player[0].veloX/5*app.deltaTime;
   ROUND_TO(app.backgroundMoving,0,backgrounds[app.backgroundInt].textureWidth)
   if(player[0].special >= 0){
      player[0].specialshow += (100 - player[0].specialshow)*10*app.deltaTime;
   }
 
   Update_Finished_Level();
   Update_Buttons();
   Update_UI_Elements();

   if(player[0].keys.r && level.Started){
    FGameRestart();
   }

   if(level.Paused || level.Finished) {return;}
   
   // The following code is executed only when the game is not paused or is running
   Update_Player_Record();
   Update_Movement();
   Update_DamagePopups();
   Update_Enemy();
   Update_Textpopups();
   Update_Specials();
   Update_Player();
   Update_Triggers();
   Update_Projectiles();
   Update_Platforms();
   

   // Scripts
   Update_Scripts();
   
   // PARTICLES 
   Update_Particles();
   
   if(!level.Finished && level.Started) { level.timer += 1000*app.deltaTime;}
   else if(!level.Started){level.timer = 0;}
   
}