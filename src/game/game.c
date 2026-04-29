
void Update_Buttons(){
   for(int i = 0;i<sizeof(buttons)/sizeof(buttons[0]);i++){
      if(buttons[i].reserved){
      int yMin = buttons[i].y;
      int yMax = buttons[i].y+buttons[i].hoverHeight;
      int xMin = buttons[i].x;
      int xMax = buttons[i].x+buttons[i].hoverWidth;   
       
      if(mouse.x >= xMin && mouse.x <= xMax && mouse.y >= yMin && mouse.y <= yMax && mouse.left == -1){
         if(i == 1){
            level.Paused = false;
         }  
         else if(i == 2){
            appendTransition(app.status,4);
         }
         else if(i == 3){
            FGameRestart();
         }
         else if(i == 4){
            profile.levelsUnlocked++;
            FSaveProfile();
            appendTransition(0,8);
            
         }   
      }
      }
   }
}



void playerHurt(int i,double damage){
   if(player[i].invisTimer > 0){
      return;
   }
   Mix_PlayChannel(-1,Sound_Death,0);
   player[i].health -= damage;
   addDamagePopUp(-10,player[i].x,player[i].y-10,10,0,-15);
   player[i].invisTimer = 2000;
   player[i].veloX *= -0.5;
   player[i].veloY *= -0.25;
   if(player[i].health < 0){
      player[i].dead = true;
   }
}

void enemyHurt(int i , double damage){
   Mix_PlayChannel(-1,Sound_enemyHurt,0);
   enemy[i].veloX = 0;
   enemy[i].health -= damage;
   
   addDamagePopUp(-10,enemy[i].x,enemy[i].y-10,10,0,-15);

   if (enemy[i].health <= 0.01f){
      enemy[i].killed = true;
   } 
   enemy[i].attackCoolDown = 0;
   if(enemy[i].killed){
         Mix_PlayChannel(-1,Sound_enemyDead,0);
         
      for(int k = 0;k<15;k++){
         addParticle(tex_explosion,enemy[i].x,enemy[i].y,(((double)(rand()%100))/100-0.5)*100,(((double)(rand()%100))/100-0.5)*100,20,255,255,255,2*PI*(rand()%100)/100);
      }
         
   } 
   
}

#include "game_update.c"
#include "game_draw.c"


void addProjectile(bool fromEnemy,int enemyIndex,double x, double y, double veloX,double veloY,int type){
   for(int i = 0;i<sizeof(projectiles)/sizeof(projectiles[0]);i++){
      if(!projectiles[i].reserved){
         projectiles[i].fromEnemy = fromEnemy;
         if(fromEnemy){
            projectiles[i].enemyIndex = enemyIndex;
         }
         projectiles[i].reserved = true;
         projectiles[i].x = x;
         projectiles[i].y = y;
         projectiles[i].width = (int)(15);
         projectiles[i].height =  (int)(15);
         projectiles[i].accY = GRAVITY;
         projectiles[i].veloX = veloX;
         projectiles[i].veloY = veloY;
         projectiles[i].projectileType = type;

         break;
      }
   }
}


void FGameRestart(){
   
   if(level.newRecord){
      level.newRecord = false;
   }
   if(mapData.PBTimer>0){
        mapData.ghostInGame = true; 
   }

   
      for(int i = 0;i<sizeof(scripts)/sizeof(scripts[0]);i++){
         if(scripts[i].reserved){
            scripts[i].used = false;
            scripts[i].execute = false;
            scripts[i].useDelayTimer = 0;
            scripts[i].reuseDelayTimer = 0;
         }
      }
      for(int i = 0;i<sizeof(platforms)/sizeof(platforms[0]);i++){
        if(platforms[i].reserved){
         platforms[i].x = platforms[i].spawnX;
         platforms[i].y = platforms[i].spawnY;
         platforms[i].platformUsed = false;  
         platforms[i].moveNodeCount = 0;
         platforms[i].moveDistance = 0;
         platforms[i].moveNodeReverse = false;
         platforms[i].moveSpeed = platforms[i].moveSpeedSpawn;
         platforms[i].moveNodeInt = platforms[i].moveNodeIntSpawn;
         platforms[i].steepness = -atan((platforms[i].height*sin(platforms[i].slope))/(platforms[i].width));
         
        
        }        
      }
      for(int i = 0;i<sizeof(deathbox)/sizeof(deathbox[0]);i++){
        if(deathbox[i].reserved){
         deathbox[i].x = deathbox[i].spawnX;
         deathbox[i].y = deathbox[i].spawnY;
         deathbox[i].moveNodeCount = 0;
         deathbox[i].moveDistance = 0;
         deathbox[i].moveNodeReverse = false;
         deathbox[i].moveSpeed = deathbox[i].moveSpeedSpawn;
         deathbox[i].moveNodeInt = deathbox[i].moveNodeIntSpawn;
        }        
      }
      
      for(int i = 0;i<sizeof(light)/sizeof(light[0]);i++){
        if(light[i].reserved){
        light[i].x = light[i].spawnX;
        light[i].y = light[i].spawnY;
        light[i].moveNodeCount = 0;
        light[i].moveDistance = 0;
        light[i].moveNodeReverse = false;
        light[i].moveSpeed = light[i].moveSpeedSpawn;
         light[i].moveNodeInt = light[i].moveNodeIntSpawn;
       }
      }
      for(int i = 0;i<sizeof(triggers)/sizeof(triggers[0]);i++){
        if(triggers[i].reserved){
          triggers[i].triggerUsed = false;
          triggers[i].timerStart = false;
          triggers[i].useDelayTimer = 0;
          triggers[i].reuseDelayTimer = 0;
        }
       }
      for(int i = 0;i<sizeof(displacement)/sizeof(displacement[0]);i++){
        if(displacement[i].reserved){
         displacement[i].x = displacement[i].spawnX;
         displacement[i].y = displacement[i].spawnY;
         displacement[i].moveNodeCount = 0;
         displacement[i].moveDistance = 0;
         displacement[i].moveNodeReverse = false;
         displacement[i].moveSpeed = displacement[i].moveSpeedSpawn;
         displacement[i].moveNodeInt = displacement[i].moveNodeIntSpawn;
       }
       }
       for(int i = 0;i<sizeof(enemy)/sizeof(enemy[0]);i++){
        if(enemy[i].reserved){
         enemy[i].x = enemy[i].spawnX;
         enemy[i].y = enemy[i].spawnY;
         enemy[i].veloX = 0;
         enemy[i].veloY = 0;
         enemy[i].killed = false;
         enemy[i].health = enemy[i].maxHealth;
         enemy[i].unbump = false;
         enemy[i].bumpX = 0;
         enemy[i].textureAnimationInt = 0;
         enemy[i].attackCoolDown = 100;
         enemy[i].direction = 1;
         enemy[i].attackDelayTimer = 0;
         enemy[i].attackPrepare = false;
       }
       }
       for(int i = 0;i<sizeof(specials)/sizeof(specials[0]);i++){
        if(specials[i].reserved){
         specials[i].taken = false;
       }
       }
       for(int i = 0;i<sizeof(projectiles)/sizeof(projectiles[0]);i++){
        if(projectiles[i].reserved){
         projectiles[i].reserved = false;
         projectiles[i].despawnTime = 0;
       }
       }
      level.Paused = false;
      level.endShowCoins = 0;
      level.transitionToLevel = false;
      level.endTransition = 0;
      camera.scaleReal = level.cameraScaleStart;
      remove("levels/temp.txt");
      if(app.status == 0){
         level.resetTransition = 255;
      }
      mapData.ghostEnd = false;
      mapData.ghostNextInput = -10;
      mapData.fileadditionIndex = 0;
      mapData.ghostCurrentIndex = 0;
      level.Finished = false;
      level.Started = false;
      player[0].x = player[0].spawnX;
      player[0].y = player[0].spawnY;
      player[0].health = 30;
      player[0].invisTimer = -1;
      player[0].attackSize = player[0].width*1.5;
      player[0].walkingSpeed = 150;
      player[1].walkingSpeed = 150;
      player[0].sprintSpeed = (player[0].width+player[0].height)*500/40;
      player[1].sprintSpeed = (player[1].width+player[1].height)*500/40;
     
      camera.x = -player[0].x-player[0].width/2+gameWidthBase/2;
      camera.y = -player[0].y-player[0].height/2+gameHeightBase/2;
      camera.scale = 5;
      camera.freeCam = false;
      player[0].keys.left = false;
      player[0].keys.right = false;
      player[0].groundPound = false;
      player[1].groundPound = false;
      player[0].drawTrails = false;
      player[0].dead = false;
      player[0].deathAnimationTimer = 0;
      player[0].special = -1;
      player[0].doubleJump = 0;
      player[1].doubleJump = 0;
      player[1].x = player[0].spawnX;
      player[1].y = player[0].spawnY;
      player[0].projectileThrown = 0;
      player[1].groundPoundX = 0;
      player[0].groundPoundX = 0;
      player[0].veloX = 0;
      player[0].veloY = 0;
      player[0].displacementVeloX = 0;
      player[0].displacementVeloY = 0;
      player[0].displacementAccelX = 0;
      player[0].displacementAccelY = 0;
      player[1].displacementVeloX = 0;
      player[1].displacementVeloY = 0;
      player[1].displacementAccelX = 0;
      player[1].displacementAccelY = 0;
      player[0].accX = 0;
      player[0].accY = 0;
      player[0].jumpVelo = 0;
      player[1].veloY = 0;
      player[1].veloX = 0;
      player[1].accY = 0;
      player[1].accX = 0;
      player[1].jumpVelo = 0;
      level.tempFileMade = false;
      level.keyInputsSize = 0;
      level.checkpointCount = 0; 
      level.checkpointShowTimer = 0;

      player[1].keys.up = false;
      player[1].keys.left = false;
      player[1].keys.right = false;
      player[1].keys.down = false;
      player[1].keys.shift = false;
}