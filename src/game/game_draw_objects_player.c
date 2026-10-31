void Draw_Player_Dead(int i) {
    SDL_RendererFlip flip1 = (1 - player[i].direction)/2;
    
    if((int)(player[0].deathAnimationTimer/1000)>=1 && (int)(player[0].deathAnimationTimer/1000) <= 6){
        RenderCopyEx(renderer,tex_player,&(SDL_Rect){95+(int)(player[0].deathAnimationTimer/1000)*24,24,22,22},&(SDL_Rect){player[i].xDraw,player[i].yDraw,player[i].widthDraw,player[i].heightDraw},0,NULL,SDL_FLIP_NONE);
    }
    else if((int)(player[0].deathAnimationTimer/1000) <= 6){
        RenderCopyEx(renderer,tex_player,&(SDL_Rect){98,26,16,16},&(SDL_Rect){player[i].xDraw,player[i].yDraw,player[i].widthDraw,player[i].heightDraw},0,NULL,SDL_FLIP_NONE);
    }
}

void Draw_Player_Snap(int i) {
    SDL_RendererFlip flip1 = (1 - player[i].direction)/2;
    player[i].width = player[i].Owidth;
    RenderCopyEx(renderer,tex_player,&(SDL_Rect){3,105,19,31},&(SDL_Rect){player[i].xDraw,player[i].yDraw,player[i].widthDraw,player[i].heightDraw},0,NULL,flip1);
}

void Draw_Player_Groundpound(int i) {
    SDL_RendererFlip flip1 = (1 - player[i].direction)/2;
    player[i].width = player[i].Owidth;
    RenderCopyEx(renderer,tex_player,&(SDL_Rect){3,139,19,31},&(SDL_Rect){player[i].xDraw,player[i].yDraw,player[i].widthDraw,player[i].heightDraw},0,NULL,flip1);

}
void Draw_Player_Attack(int i) {
    SDL_RendererFlip flip1 = (1 - player[i].direction)/2;
    
    int attackInt = (int)(player[i].specialDelayTimer*2/(double)player[i].specialDelay);
    player[i].width = player[i].Owidth; 
    RenderCopyEx(renderer,tex_player,&(SDL_Rect){3+22*(attackInt % 2),207,19,31},&(SDL_Rect){player[i].xDraw,player[i].yDraw,player[i].widthDraw,player[i].heightDraw},0,NULL,flip1);  
}
void Draw_Player_HangWall(int i) {
    SDL_RendererFlip flip1 = (1 - player[i].direction)/2;
    
    if(player[i].onWall > 0){
        flip1 = SDL_FLIP_HORIZONTAL;
    }
    else {flip1 = SDL_FLIP_NONE;}
    player[i].width = player[i].Owidth;
    RenderCopyEx(renderer,tex_player,&(SDL_Rect){3,173,19,31},&(SDL_Rect){player[i].xDraw,player[i].yDraw,player[i].widthDraw,player[i].heightDraw},0,NULL,flip1);

}
void Draw_Player_Movement(int i) {
    SDL_RendererFlip flip1 = (1 - player[i].direction)/2;
    
    if(SDL_abs(player[i].veloX) >= (player[i].width+player[i].height)*200/40){
        // Running
        RenderCopyEx(renderer,tex_player,&(SDL_Rect){3+((int)(player[i].animationIndex) % 4 )*22,37,19,31},&(SDL_Rect){player[i].xDraw,player[i].yDraw,player[i].widthDraw,player[i].heightDraw},0,NULL,flip1);
    }
    else{
        // Walking
        RenderCopyEx(renderer,tex_player,&(SDL_Rect){3+((int)(player[i].animationIndex) % 4 )*22,3,19,31},&(SDL_Rect){player[i].xDraw,player[i].yDraw,player[i].widthDraw,player[i].heightDraw},0,NULL,flip1);
    }
}
void Draw_Player_Idle(int i){
    SDL_RendererFlip flip1 = (1 - player[i].direction)/2;
    
    player[i].width = player[i].Owidth;
    RenderCopyEx(renderer,tex_player,&(SDL_Rect){3,3,19,31},&(SDL_Rect){player[i].xDraw,player[i].yDraw,player[i].widthDraw,player[i].heightDraw},0,NULL,flip1);
}
void Draw_Player_Jump(int i){
    SDL_RendererFlip flip1 = (1 - player[i].direction)/2;
    
    player[i].width = player[i].Owidth;
    if (player[i].jumpVelo + player[i].veloY >= 0) {
        RenderCopyEx(renderer,tex_player,&(SDL_Rect){25,71,19,31},&(SDL_Rect){player[i].xDraw,player[i].yDraw,player[i].widthDraw,player[i].heightDraw},0,NULL,flip1);
    }
    else {
        RenderCopyEx(renderer,tex_player,&(SDL_Rect){3,71,19,31},&(SDL_Rect){player[i].xDraw,player[i].yDraw,player[i].widthDraw,player[i].heightDraw},0,NULL,flip1);
    }
    
}