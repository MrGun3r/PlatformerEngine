void toggle_pause_level() {
    level.Paused = !level.Paused;
}

void unpause_level() {
    level.Paused = false;
}

void restart_level() {
    FGameRestart();
}

void exit_level() {
    
    if(mapData.ghostInGame){
        int num_of_playerMovement = 15 + (int)(player[1].playerMovementIndex/15)*15;
        for(int i = 0;i<num_of_playerMovement;i++){
            free(player[1].playerMovement[i]);
        }
        free(player[1].playerMovement);
        printf("freed %d\n",num_of_playerMovement);
    }
    
    startMenu();
}

void next_level() {
    FSaveProfile();
}
