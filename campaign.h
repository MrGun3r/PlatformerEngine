void findLevelCampaign(){
    if(app.chapter == 1){
        if(app.campaignLevel == 0){
         sprintf(app.campaignLevelName,"Pilot");
        }
        else if(app.campaignLevel == 1){
         sprintf(app.campaignLevelName,"Spikes");
        }
        else if(app.campaignLevel == 2){
         sprintf(app.campaignLevelName,"Temple");
        }
        else if(app.campaignLevel == 3){
         sprintf(app.campaignLevelName,"Climb");
        }
        else if(app.campaignLevel == 4){
         sprintf(app.campaignLevelName,"Ancient");
        }
        else if(app.campaignLevel == 5){
         sprintf(app.campaignLevelName,"Elevator");
        }
        char path[256];
        sprintf(path,"levels/%s.txt\0",app.campaignLevelName);
        app.campaignLevelPB = atoi(FGetDataMap(path,"m",1,len(app.campaignLevelName)+12));
        app.campaignLevelStarTime = atoi(FGetDataMap(path,"m",9,len(app.campaignLevelName)+12));
    }
}




void FDraw_Campaign(){
    camera.scale = (double)gameHeight/1080;
    if(player[0].stepSoundCount>100){
       if(player[0].stepSoundInt == 0){
       Mix_PlayChannel(-1,Sound_Step1,0);
      }
      else if(player[0].stepSoundInt == 1){
         Mix_PlayChannel(-1,Sound_Step2,0);
      }
      player[0].stepSoundCount = 0;
      player[0].stepSoundInt = (player[0].stepSoundInt + 1) % 2; 
    }
      
    
    int i = -1;
    int j = 0;
    while(500*camera.scale*i < gameWidth){
        while(500*camera.scale*j < gameHeight){
         SDL_RenderCopy(renderer,tex_water,NULL,&(SDL_Rect){500*camera.scale*i+((int)app.backgroundMoving%((int)(500*camera.scale))),500*camera.scale*j,500*camera.scale + 20,500*camera.scale + 20});
         j++;
        }
        i++;
        j = 0;
    }
     // Draw Island
      campaignXIsland = 150*gameWidth/1920;
      campaignYIsland = 150*gameHeight/1080;
     i = 0;
     j = 0;
     while(campaignXIsland+i*200*gameWidth/1920 < 1600*gameWidth/1920){
        while(campaignYIsland+j*200*gameHeight/1080 < 800*gameHeight/1080){
            SDL_RenderCopy(renderer,tex_sand,NULL,&(SDL_Rect){campaignXIsland+i*200*gameWidth/1920,campaignYIsland+j*200*gameHeight/1080,200*gameWidth/1920 +10,200*gameHeight/1080 + 10});    
            j++;
            
        }
        i++;
        campaignWidthIsland  = max(i*200*gameWidth/1920,campaignWidthIsland);
        campaignHeightIsland = max(j*200*gameHeight/1080,campaignHeightIsland);
        j=0;
     }


    
    // Draw levelPads
    char levelnum[10];
    for(int i = 0;i<5;i++){
        if(profile.levelsUnlocked >= i){
            SDL_SetTextureColorMod(tex_levelPad,10,255,30);
        }
        else{
            SDL_SetTextureColorMod(tex_levelPad,100,100,100);
        }
        SDL_RenderCopy(renderer,tex_levelPad,NULL,&(SDL_Rect){campaignXIsland + i*campaignWidthIsland/5 + 50,campaignYIsland + 100,70*camera.scale,70*camera.scale});
        SDL_itoa(i+1,levelnum,10);
        renderText(1,levelnum,campaignXIsland + i*campaignWidthIsland/5 + 50+70*camera.scale/2-20/2*gameWidth/1920,campaignYIsland + 100+70*camera.scale/2-(30*gameHeight/1080)/2,20*gameWidth/1920,30*gameHeight/1080,255,200,(int[3]){255,255,255});
    }
    for(int i = 0;i<5;i++){
        if(profile.levelsUnlocked >= i+5){
            SDL_SetTextureColorMod(tex_levelPad,10,255,30);
        }
        else{
            SDL_SetTextureColorMod(tex_levelPad,100,100,100);
        }
        SDL_RenderCopy(renderer,tex_levelPad,NULL,&(SDL_Rect){campaignXIsland + i*campaignWidthIsland/5 + 50,campaignYIsland + campaignHeightIsland - 100,70*camera.scale,70*camera.scale});
        SDL_itoa(i+6,levelnum,10);
        renderText(1+1*(i == 4),levelnum,campaignXIsland + i*campaignWidthIsland/5 + 50+70*camera.scale/2-10*gameWidth/1920,campaignYIsland + campaignHeightIsland - 100+70*camera.scale/2-30/2*gameHeight/1080,(20+10*(i == 4))*gameWidth/1920,30*gameHeight/1080,255,200,(int[3]){255,255,255});
    }

    // Draw Player
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if(player[0].direction < 0){
        flip = SDL_FLIP_HORIZONTAL;
    }
    if(SDL_abs(player[0].veloX)>0 ||SDL_abs(player[0].veloY)>0){
        SDL_RenderCopyEx(renderer,tex_player,&(SDL_Rect){2+((int)(player[0].animationIndex) % 6 )*24,2,15,18},&(SDL_Rect){player[0].xDraw,player[0].yDraw,player[0].widthDraw,player[0].heightDraw},0,NULL,flip);
    }
    else{
       SDL_RenderCopyEx(renderer,tex_player,&(SDL_Rect){2+((int)(player[0].idleIndex) % 2 )*24,24,15,18},&(SDL_Rect){player[0].xDraw,player[0].yDraw,player[0].widthDraw,player[0].heightDraw},0,NULL,flip); 
    }

   char coins[256];
   sprintf(coins,"%d\0",profile.coins);
   renderText(len(coins),coins,gameWidth-10*len(coins)-10,10,10*len(coins),15,255,200,(int[3]){255,255,255});   


     SDL_RenderCopy(renderer,tex_coin,NULL,&(SDL_Rect){gameWidth-35-10*len(coins),5,20,20}); 
    
    

    if(app.chapter == 1){
        renderText(len("Chapter 1:Desert"),"Chapter 1:Desert",gameWidth/2 - 12*len("Chapter 1:Desert")/2,5,len("Chapter 1:Desert")*12,18,255,200,(int[3]){255,255,255});
    }
    renderText(len("Enter to select"),"Enter To Select",10,gameHeight - 20,10*len("Enter to select"),15,255,200,(int[3]){255,255,255});


 /// Level Showcase Render
    SDL_SetRenderDrawColor(renderer,100,100,100,100);
    SDL_RenderFillRect(renderer,&(SDL_Rect){(-290+app.campaignLevelShowcase),5,300*gameWidth/1920,200*gameHeight/1080});
    renderText(len(app.campaignLevelName),app.campaignLevelName,-280+app.campaignLevelShowcase,10,12*len(app.campaignLevelName),15,255,200,(int[3]){255,255,255});

    SDL_RenderCopy(renderer,tex_trophy,NULL,&(SDL_Rect){-280+app.campaignLevelShowcase,40,20,20});

    renderText(len(msToTimer(app.campaignLevelPB)),msToTimer(app.campaignLevelPB),-250+app.campaignLevelShowcase,40,12*len(msToTimer(app.campaignLevelPB)),15,255,200,(int[3]){200,200,200});

    SDL_RenderCopy(renderer,tex_star,NULL,&(SDL_Rect){-280+app.campaignLevelShowcase,65,20,20});
    
    renderText(len(msToTimer(app.campaignLevelStarTime)),msToTimer(app.campaignLevelStarTime),-250+app.campaignLevelShowcase,70,12*len(msToTimer(app.campaignLevelStarTime)),15,255,200,(int[3]){255,255,30});
    

}



void FUpdate_Campaign(){
    app.backgroundMoving += 10*app.deltaTime;
    if(player[0].xDraw + player[0].widthDraw/2 > campaignXIsland + campaignWidthIsland){
        player[0].x = (campaignXIsland + campaignWidthIsland - player[0].widthDraw/2 - gameWidth/2)/camera.scale + gameWidth/2;
    }
    else if(player[0].xDraw + player[0].widthDraw/2 < campaignXIsland){
        player[0].x = (campaignXIsland - player[0].widthDraw/2 - gameWidth/2)/camera.scale + gameWidth/2;
    }

    if(player[0].yDraw + player[0].heightDraw < campaignYIsland ){
        player[0].y = (campaignYIsland - player[0].heightDraw - gameHeight/2)/camera.scale + gameHeight/2;
    }
    else if(player[0].yDraw + player[0].heightDraw > campaignYIsland + campaignHeightIsland){
        player[0].y = (campaignYIsland + campaignHeightIsland - player[0].heightDraw - gameHeight/2)/camera.scale + gameHeight/2;
    }

    player[0].idleIndex += 2*app.deltaTime;
    if(player[0].keys.left){
        player[0].stepSoundCount += 1000*app.deltaTime*(!player[0].keys.up && !player[0].keys.down);
        player[0].veloX = -300*app.deltaTime;
        player[0].direction = -1;
        player[0].animationIndex += 10*app.deltaTime*(!player[0].keys.up && !player[0].keys.down);
    }
    else if(player[0].keys.right){
        player[0].stepSoundCount += 1000*app.deltaTime*(!player[0].keys.up && !player[0].keys.down);
        player[0].veloX = 300*app.deltaTime;
        player[0].direction = 1;
        player[0].animationIndex += (10*app.deltaTime)*(!player[0].keys.up && !player[0].keys.down);
    }
    else{
       player[0].veloX = 0; 
    }
    if(player[0].keys.up){
        player[0].stepSoundCount += 1000*app.deltaTime;
        player[0].veloY = -300*app.deltaTime;
        player[0].animationIndex += 10*app.deltaTime;
    }
    else if(player[0].keys.down){
        player[0].stepSoundCount += 1000*app.deltaTime;
        player[0].veloY = 300*app.deltaTime;
        player[0].animationIndex += 10*app.deltaTime;
    }
    else{
        player[0].veloY = 0; 
    }

    player[0].x += player[0].veloX;
    player[0].y += player[0].veloY;


    player[0].xDraw  = gameWidth/2 + (player[0].x - gameWidth/2) * camera.scale;
    player[0].yDraw  = gameHeight/2 + (player[0].y - gameHeight/2) * camera.scale;
    player[0].widthDraw = player[0].width*camera.scale;
    player[0].heightDraw = player[0].height*camera.scale;
    bool levelFound = false;
    for(int i = 0;i<5;i++){
        if(rectCollision((SDL_Rect){campaignXIsland + i*campaignWidthIsland/5 + 50,campaignYIsland + 100,50*camera.scale,50*camera.scale},(SDL_Rect){player[0].xDraw,player[0].yDraw+player[0].heightDraw/2,player[0].widthDraw,player[0].heightDraw/2})){
           findLevelCampaign();  
            if(app.campaignLevelSelect < 0){
             Mix_PlayChannel(-1,Sound_levelSelect,0);
            }
           app.campaignLevelSelect = i;
           app.campaignLevel = i;
           levelFound = true;
           break;
        }
    }
    if(!levelFound){
    for(int i = 0;i<5;i++){
        if(rectCollision((SDL_Rect){campaignXIsland + i*campaignWidthIsland/5 + 50,campaignYIsland + campaignHeightIsland - 100,50*camera.scale,50*camera.scale},(SDL_Rect){player[0].xDraw,player[0].yDraw+player[0].heightDraw/2,player[0].widthDraw,player[0].heightDraw/2})){
           findLevelCampaign();
           if(app.campaignLevelSelect < 0){
             Mix_PlayChannel(-1,Sound_levelSelect,0);
            }
           app.campaignLevelSelect = i + 5; 
           app.campaignLevel = i + 5; 
           levelFound = true;
           break;
        }
    }    
    }
    
    
    if(!levelFound){
        app.campaignLevelSelect = -1;
    }
    if(app.campaignLevelSelect >= 0){
     app.campaignLevelShowcase += 5*(300 - app.campaignLevelShowcase)*app.deltaTime;   
    }
    else{
      app.campaignLevelShowcase -= 5*app.campaignLevelShowcase*app.deltaTime;   
    }
    if(app.campaignLevelSelect>=0 && app.campaignLevelSelect <= profile.levelsUnlocked){
        if(player[0].keys.enter){
            player[0].keys.enter = false;
            findLevelCampaign();
            sprintf(level.absolutePath,"levels/%s.txt",app.campaignLevelName);
            appendTransition(app.status,0);
        }
    }
    

//
    

   


}