///// Main menu buttons
void play_button() {
    startMenu_2();
}

void editor_button() {
    startEditor();
}

void settings_button() {
    startSettings();
}

void quit_game() {
    app.WINDOW_LOOP = false;
}

/// Menu 2 buttons

void load_campaign_level() {
    sprintf(level.absolutePath,"levels/%s.txt",profile.currentLevel);
    appendTransition(startLevel);
}

void browse_levels() {
    startLevelList();
}


/// Intro menu buttons
void set_username() {
    SetUsernameProfile();
}


/// Settings buttons 

void change_game_resolution() {
    app.resolutionInt++;
    app.resolutionInt=app.resolutionInt%6;
    sprintf(buttons[1].value,"%dx%d",app.resolutions[app.resolutionInt][0],app.resolutions[app.resolutionInt][1]);
}

void apply_settings_button() {
    app.resolutionUsed = app.resolutionInt;
    printf("apply changes\n");
    gameResolutionChange();

}

void toggle_show_fps() {
    app.showFPS = !app.showFPS;
    sprintf(buttons[3].value,"%d",app.showFPS);
}

///  Level list buttons
void nextButton_levelList() {
    if(app.listStartIndex > 0){
        app.listStartIndex-=app.listLengthMax;
        startLevelList();
    }
}

void prevButton_levelList() {
    if (app.listLength >= app.listLengthMax){
        app.listStartIndex+=app.listLengthMax;
        startLevelList();
    }
}

void choose_level() {
    sprintf(level.absolutePath,"%s",levelsList[app.lastButtonIndex-3].levelPath);
    startLevel();
}
