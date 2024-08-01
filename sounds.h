void FLoadSounds(){
    Sound_Jump = Mix_LoadWAV("assets/sound/jump.wav");
    Sound_Step1 = Mix_LoadWAV("assets/sound/step1.wav");
    Sound_Step2 = Mix_LoadWAV("assets/sound/step2.wav");
    Sound_Wall = Mix_LoadWAV("assets/sound/wall.wav");
    Sound_JumpWall = Mix_LoadWAV("assets/sound/wallJump.wav");
    Sound_Death = Mix_LoadWAV("assets/sound/death.wav");
    Sound_Checkpoint = Mix_LoadWAV("assets/sound/checkpoint.wav");
    Sound_Hover = Mix_LoadWAV("assets/sound/hover.wav");
    Sound_buttonClick = Mix_LoadWAV("assets/sound/buttonSelect.wav");
    Sound_transition = Mix_LoadWAV("assets/sound/transition.wav");
    Sound_finish = Mix_LoadWAV("assets/sound/finish.wav");
    Sound_levelSelect = Mix_LoadWAV("assets/sound/levelSelect.wav");
}



void Play_Sound(Mix_Chunk *sound,int channel,int loops){
    int MixChannel = Mix_PlayChannel(channel,sound,loops);
    if(MixChannel == -1){return;}
    channels[MixChannel].playing = true;
    channels[MixChannel].playtime = 0;
}

void Stop_SoundChannel(Mix_Chunk *sound,int channel,int loops){
    Mix_HaltChannel(channel);
    channels[channel].playing = false;
    channels[channel].playtime = 0;
}

int GetAvailableChannel(){
    for(int i = 0;i<sizeof(channels)/sizeof(channels[0]);i++){
        if(!channels[i].playing){
            return i;
        }
    }
    return -1;
}