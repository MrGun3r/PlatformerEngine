void Player_Check_Hit(int i) {
    if(i == 0 && !player[i].dead){
         for(int j = 0;j<sizeof(deathbox)/sizeof(deathbox[0]);j++){
            if(deathbox[j].reserved){
               if(rectCollision((SDL_Rect){player[i].x,player[i].y,player[i].width,player[i].height},(SDL_Rect){deathbox[j].x,deathbox[j].y,deathbox[j].width,deathbox[j].height})){
                  playerHurt(0,10);
               }
            }
         }

         if(player[0].health <= 0){
           player[0].dead = true;
           Mix_PlayChannel(-1,Sound_Death,0);
         }
    }
}