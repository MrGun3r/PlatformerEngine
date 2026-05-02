
void appendTransition(void (*transitionFunction)(void))
{
    app.transition = true;
    app.transitionFunction = transitionFunction;
    app.statusChanged = false;
    Mix_PlayChannel(-1, Sound_transition, 0);
}

void startLevel() {

    printf("last button is : %d\n",app.lastButtonIndex);
    printf("Map is :%s\n", level.absolutePath);
    FSetDataMap(level.absolutePath, len(level.absolutePath));
    char* backgroundIntText = FGetDataMap(level.absolutePath, "m", 6, len(level.absolutePath));
    app.backgroundInt = FindBackgroundInt(backgroundIntText);
    free(backgroundIntText);
    char* backgroundOpacity = FGetDataMap(level.absolutePath, "m", 7, len(level.absolutePath));
    app.backgroundOpacity = atoi(backgroundOpacity);
    free(backgroundOpacity);
    level.checkpointCount = 0;
    if(mapData.PBTimer>0){player[1].playerMovementIndex = GetPlayerMovementData(level.absolutePath,&player[1].playerMovement);}
    FGameRestart();
    level.campaignLevel = true;
    /// Init pause values
    initPauseUI();
    app.transitionEnabled = false;
    app.escapeFunction = toggle_pause_level;
    app.status = INGAME;
}


void startMenu_2() {
    initMenu_2_UI();
    app.escapeFunction = startMenu;
    app.transitionEnabled = false;
    app.status = MENU_2;
}
void startMenu() {

    remove("levels/temp.txt");
    app.backgroundInt = FindBackgroundInt("background");
    app.backgroundOpacity = 255;
    initMenu_1_UI();
    app.escapeFunction = NULL;
    app.transitionEnabled = false;
    app.status = MAIN_MENU;
}
void startGameIntro() {
    
    app.backgroundInt = FindBackgroundInt("background");
    app.backgroundOpacity = 255;
    initGameIntroUI();

    app.transitionEnabled = false;
    app.escapeFunction = NULL;
    app.status = INTRO_MENU;
}
void startSettings() {
    
    initSettingsUI();
    sprintf(buttons[1].value, "%dx%d", app.resolutions[app.resolutionUsed][0], app.resolutions[app.resolutionUsed][1]);
    sprintf(buttons[3].value, "%d", app.showFPS);
    
    app.transitionEnabled = false;
    app.escapeFunction = startMenu;
    app.status = SETTINGS;
}
void startLevelList() {
    
    clearLight();
    remove("levels/temp.txt");
    app.fetchedList = false;
    initLevelsUI();
    app.transitionEnabled = false;
    app.escapeFunction = startMenu_2;
    app.status = LEVEL_LIST;
}
void startEditor() {
    
    clearAllElements();
    initEditor();
    initEditorUI();
    app.transitionEnabled = true;
    app.escapeFunction = startMenu;
    app.status = EDITOR;
}
void FswitchAppStatus(int from, int to)
{
    

    if (from != to)
    {
        clearLight();
    }

    startEditor();
}
