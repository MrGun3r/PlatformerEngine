#include "game_draw_objects_player.c"


/// Different player draw functions 
///
void (*Player_Draw_Functions[])(int) = {
    Draw_Player_Dead,
    Draw_Player_Groundpound,
    Draw_Player_Attack,
    Draw_Player_HangWall,
    Draw_Player_Movement,
    Draw_Player_Idle,
    Draw_Player_Jump
};


void Draw_Player(int i) {
    
    /// Normal and Ghost player opacities
    SDL_SetTextureAlphaMod(tex_player,255);     
    if(i > 0){
        SDL_SetTextureAlphaMod(tex_player,100);
    }
    
    //// Draw player trails
    //// 
    for(int j = 0;j < 5;j++){
        if(player[i].playerTrails[j][2] > 10){
            double playerTrailXDraw = gameWidthBase/2 + (player[i].playerTrails[j][0] + camera.x - gameWidthBase/2) * camera.scale;
            double playerTrailYDraw = gameHeightBase/2 + (player[i].playerTrails[j][1] + camera.y - gameHeightBase/2) * camera.scale;
            SDL_SetTextureAlphaMod(tex_player,player[i].playerTrails[j][2]);
            RenderCopyEx(renderer,tex_player,&(SDL_Rect){2+((int)(player[0].playerTrails[j][3]))*24,2,15,18},&(SDL_Rect){playerTrailXDraw,playerTrailYDraw,player[i].widthDraw,player[i].heightDraw},0,NULL,(int)player[0].playerTrails[j][4]); 
        } 
    }

    SDL_SetTextureAlphaMod(tex_player,255);
    
    /// Different player states
    /// Last is true because we need to always draw the player
    bool playerStates[] = {
        player[i].dead,
        player[i].groundPound || player[i].keys.down,
        player[i].attack && player[i].specialDelayTimer < player[i].specialDelay,
        player[i].onWall,
        ((int)player[i].accX != 0) && ((int)player[i].jumpVelo == 0),
        (int)player[i].jumpVelo == 0,
        true
    };
    

    for(int k = 0;k<sizeof(playerStates)/sizeof(playerStates[0]);k++){
        if( playerStates[k] ) {
            Player_Draw_Functions[k](i);
            break;
        }
    }
    
    if(player[i].attack && player[i].special == 1){
        double xAttackDraw = gameWidthBase/2 + (player[i].attackX + camera.x - gameWidthBase/2) * camera.scale;
        double yAttackDraw = gameHeightBase/2 + (player[i].attackY + camera.y - gameHeightBase/2) * camera.scale;
        double sizeattackDraw = player[0].attackSize*camera.scale;
        RenderCopyEx(renderer,tex_player,&(SDL_Rect){player[i].attackDrawInt*23,63,20,25},&(SDL_Rect){xAttackDraw,yAttackDraw,sizeattackDraw,sizeattackDraw},0,NULL,(1-player[i].attackDirection)/2);
    }
    if(player[i].special == 5){
        RenderCopyEx(renderer,tex_player,&(SDL_Rect){(int)(player[i].arrowPull/100)*23+170,63,20,25},&(SDL_Rect){player[i].xDraw+player[i].widthDraw/2,player[i].yDraw+player[i].heightDraw/3,4*player[i].widthDraw/5,4*player[i].heightDraw/5},player[i].ProjectileAngle,&(SDL_Point){0,4*player[i].heightDraw/10},0);
    }
    
    if(player[i].EButtonOpacity > 1){
        SDL_SetTextureAlphaMod(tex_player,player[i].EButtonOpacity);
        RenderCopy(renderer,tex_player,&(SDL_Rect){0,85,32,32},&(SDL_Rect){player[i].xDraw+player[i].widthDraw/8,player[i].yDraw-player[i].heightDraw/1.5,player[i].widthDraw/1.5,player[i].heightDraw/1.5});
    }
    
    SDL_SetTextureAlphaMod(tex_player,255);
    // Draw grappling hook
    if(player[i].grappling){
        double grappleDrawX = gameWidthBase/2 + (player[i].grappleX + camera.x - gameWidthBase/2) * camera.scale;
        double grappleDrawY = gameHeightBase/2 + (player[i].grappleY + camera.y - gameHeightBase/2) * camera.scale;
        RenderCopyEx(renderer,tex_player,&(SDL_Rect){0,190,5,5},&(SDL_Rect){grappleDrawX,grappleDrawY-2,player[i].grappleLength*camera.scale,4},player[i].grappleAngle*180/PI,&(SDL_Point){0,5},0);
        SDL_SetRenderDrawColor(renderer,200,200,200,255);
        RenderFillRect(renderer,&(SDL_Rect){grappleDrawX-5,grappleDrawY-5,10,10});
        
    }
    if(player[i].grappleFailed > 50){
        SDL_SetTextureAlphaMod(tex_grappleFail,player[i].grappleFailed);
        RenderCopy(renderer,tex_grappleFail,NULL,&(SDL_Rect){player[i].xDraw-150/2*camera.scale+player[i].widthDraw/2,player[i].yDraw-150/2*camera.scale+player[i].heightDraw/2,150*camera.scale,150*camera.scale});
    }
}

void Draw_Projectile(int i) {
    if(projectiles[i].projectileType == 1){
        RenderCopyEx(renderer,tex_player,&(SDL_Rect){145,68,20,13},&(SDL_Rect){projectiles[i].xDraw,
        projectiles[i].yDraw,projectiles[i].widthDraw,projectiles[i].heightDraw},projectiles[i].angle,NULL,0);
        }
    else if(projectiles[i].projectileType == 2){
        if(!projectiles[i].fromEnemy){
            RenderCopyEx(renderer,tex_player,&(SDL_Rect){0,120,56,56},&(SDL_Rect){projectiles[i].xDraw,
            projectiles[i].yDraw,projectiles[i].widthDraw,projectiles[i].heightDraw},projectiles[i].angle,NULL,0); 
        }
        else{
            RenderCopyEx(renderer,tex_enemy,&(SDL_Rect){3,214,56,56},&(SDL_Rect){projectiles[i].xDraw,
                projectiles[i].yDraw,projectiles[i].widthDraw,projectiles[i].heightDraw},projectiles[i].angle,NULL,0); 
        }        
    }
}

void Draw_Players() {
    for(int i = sizeof(player)/sizeof(player[0]) - 1;i>=0;i--){
        // invis 
        if(player[i].invisTimer > 0 && fmod(player[i].invisTimer,200) > 100 && !player[i].dead){
            continue;
        }
        
        if((i > 0 && mapData.ghostInGame) || i == 0){  
            player[i].widthDraw = player[i].width;
            player[i].heightDraw = player[i].height;
            player[i].widthDraw  *= camera.scale;
            player[i].heightDraw *= camera.scale;
            player[i].xDraw = gameWidthBase/2 + (player[i].x + camera.x - gameWidthBase/2) * camera.scale;
            player[i].yDraw = gameHeightBase/2 + (player[i].y + camera.y - gameHeightBase/2) * camera.scale;
            printf("Drawing %d player\n",i);
            Draw_Player(i);
        }
    }
}

void Draw_Platforms() {
    DRAW_OBJECTS(platforms, !platforms[i].collidable, FtexturePlatform(i))
    DRAW_OBJECTS(platforms, platforms[i].collidable,  FtexturePlatform(i))
}

void Draw_Enemies() {
    // Draw enemy
    for(int i = 0;i<sizeof(enemy)/sizeof(enemy[0]);i++){
        if(enemy[i].reserved && !enemy[i].killed){
            enemy[i].xDraw = gameWidthBase/2 + (enemy[i].x + camera.x - gameWidthBase/2) * camera.scale;
            enemy[i].yDraw = gameHeightBase/2 + (enemy[i].y + camera.y - gameHeightBase/2) * camera.scale;
            enemy[i].widthDraw = enemy[i].width*camera.scale;
            enemy[i].heightDraw = enemy[i].height*camera.scale;
            if(enemy[i].type == 1){
                if(enemy[i].attackCoolDown > 50){
                    RenderCopyEx(renderer,tex_enemy,&(SDL_Rect){0,0,80,80},&(SDL_Rect){enemy[i].xDraw,enemy[i].yDraw,enemy[i].widthDraw,enemy[i].heightDraw},enemy[i].angle*180/PI -180,NULL,SDL_FLIP_NONE);
                }
                else{
                    RenderCopyEx(renderer,tex_enemy,&(SDL_Rect){100,0,80,80},&(SDL_Rect){enemy[i].xDraw,enemy[i].yDraw,enemy[i].widthDraw,enemy[i].heightDraw},enemy[i].angle*180/PI -180,NULL,SDL_FLIP_NONE);
                } 
            }
            if(enemy[i].type == 2){
                if(enemy[i].attackCoolDown > 50){
                    RenderCopyEx(renderer,tex_enemy,&(SDL_Rect){3+24*((int)enemy[i].textureAnimationInt % 7),120,16,18},&(SDL_Rect){enemy[i].xDraw,enemy[i].yDraw,enemy[i].widthDraw,enemy[i].heightDraw},0,NULL,(1-enemy[i].direction)/2);
                }
                else{
                    RenderCopyEx(renderer,tex_enemy,&(SDL_Rect){170,120,16,18},&(SDL_Rect){enemy[i].xDraw,enemy[i].yDraw,enemy[i].widthDraw,enemy[i].heightDraw},0,NULL,(1-enemy[i].direction)/2);
                } 
            }
            if(enemy[i].type == 3){
                if(enemy[i].attackCoolDown > 50){
                    RenderCopyEx(renderer,tex_enemy,&(SDL_Rect){3+24*((int)enemy[i].textureAnimationInt % 7),144,16,18},&(SDL_Rect){enemy[i].xDraw,enemy[i].yDraw,enemy[i].widthDraw,enemy[i].heightDraw},0,NULL,(1-enemy[i].direction)/2);
                }
                else{
                    RenderCopyEx(renderer,tex_enemy,&(SDL_Rect){170,144,16,18},&(SDL_Rect){enemy[i].xDraw,enemy[i].yDraw,enemy[i].widthDraw,enemy[i].heightDraw},0,NULL,(1-enemy[i].direction)/2);
                } 
            }
            if(enemy[i].type == 4){
                if(enemy[i].attackCoolDown > 50){
                    RenderCopyEx(renderer,tex_enemy,&(SDL_Rect){2+24*((int)enemy[i].textureAnimationInt % 7),169,20,20},&(SDL_Rect){enemy[i].xDraw,enemy[i].yDraw,enemy[i].widthDraw,enemy[i].heightDraw},0,NULL,(1-enemy[i].direction)/2);
                }
                else{
                    RenderCopyEx(renderer,tex_enemy,&(SDL_Rect){169,169,19,22},&(SDL_Rect){enemy[i].xDraw,enemy[i].yDraw,enemy[i].widthDraw,enemy[i].heightDraw},0,NULL,(1-enemy[i].direction)/2);
                } 
            }
            if(enemy[i].type == 5){
                if(enemy[i].attackCoolDown > 50 && !enemy[i].attackPrepare){
                    RenderCopyEx(renderer,tex_enemy,&(SDL_Rect){3+24*((int)enemy[i].textureAnimationInt % 7),192,16,22},&(SDL_Rect){enemy[i].xDraw,enemy[i].yDraw,enemy[i].widthDraw,enemy[i].heightDraw},0,NULL,(1-enemy[i].direction)/2);
                }
                else if(enemy[i].attackPrepare){
                    RenderCopyEx(renderer,tex_enemy,&(SDL_Rect){192,192,16,22},&(SDL_Rect){enemy[i].xDraw,enemy[i].yDraw,enemy[i].widthDraw,enemy[i].heightDraw},0,NULL,(1-enemy[i].direction)/2);
                }
                else{
                    RenderCopyEx(renderer,tex_enemy,&(SDL_Rect){170,192,16,22},&(SDL_Rect){enemy[i].xDraw,enemy[i].yDraw,enemy[i].widthDraw,enemy[i].heightDraw},0,NULL,(1-enemy[i].direction)/2);
                } 
            }
        }
    }
}

void Draw_Specials() {
    DRAW_OBJECTS(specials, true,{
        if (specials[i].taken) {SDL_SetTextureAlphaMod(tex_specials, 100);}
        RenderCopyEx(renderer, tex_specials, &(SDL_Rect){5+150*(specials[i].type-1),0,125,125},
        &(SDL_Rect){specials[i].xDraw, specials[i].yDraw, specials[i].widthDraw, specials[i].heightDraw}, 0, NULL, 0);
        SDL_SetTextureAlphaMod(tex_specials, 255);}
    )
}

void Draw_DamagePopups() {
    // Draw popup damages
    for(int i = 0;i<sizeof(damagepopups)/sizeof(damagepopups[0]);i++){
        if(damagepopups[i].reserved){
            
            damagepopups[i].xDraw = gameWidthBase/2 + (damagepopups[i].x + camera.x - gameWidthBase/2) * camera.scale;
            damagepopups[i].yDraw = gameHeightBase/2 + (damagepopups[i].y + camera.y - gameHeightBase/2) * camera.scale;
            damagepopups[i].sizeDraw = damagepopups[i].size*camera.scale;
            
            char* buffer = malloc(20*sizeof(char));
            int numSize = len(buffer);
            SDL_itoa(damagepopups[i].number,buffer,10);
            int colors[3] = {0,0,0};
            if(damagepopups[i].number < 0){
                colors[0] = 255;
            }
            else{
                colors[1] = 255;
            }
            renderText(numSize,buffer,damagepopups[i].xDraw,damagepopups[i].yDraw,numSize*damagepopups[i].sizeDraw,damagepopups[i].sizeDraw*1.2,damagepopups[i].opacity,damagepopups[i].opacity,colors);
            free(buffer);
            
        }
    }
}

void Draw_Projectiles() {
    DRAW_OBJECTS(projectiles,true,Draw_Projectile(i))
}

void Draw_Particles() {
    // Draw Particles 
    DRAW_OBJECTS(particles,true,
        SDL_SetRenderDrawColor(renderer,particles[i].red,particles[i].green,particles[i].blue,255);
        RenderCopyEx(renderer,particles[i].texture,NULL,&(SDL_Rect){particles[i].xDraw,particles[i].yDraw,particles[i].widthDraw,particles[i].heightDraw},particles[i].rotation,NULL,SDL_FLIP_NONE);
    )
}

void Draw_Displacements() {
    DRAW_OBJECTS(displacement,true,
        FtextureQuad(displacement[i].xDraw,displacement[i].yDraw,displacement[i].widthDraw,displacement[i].heightDraw,tex_displacement,displacement[i].opacity,displacement[i].type);
        SDL_SetTextureAlphaMod(tex_displacement,255);
    )
}
        
void Draw_Triggers() {
    DRAW_OBJECTS(displacement,true,
        FtextureQuad(triggers[i].xDraw,triggers[i].yDraw,triggers[i].widthDraw,triggers[i].heightDraw,tex_trigger,triggers[i].opacity,0);
    )
}
        
void Draw_Deathboxes() {
    DRAW_OBJECTS(displacement,true,
        FtextureQuad(deathbox[i].xDraw,deathbox[i].yDraw,deathbox[i].widthDraw,deathbox[i].heightDraw,tex_skull,deathbox[i].opacity,0);
    )
}