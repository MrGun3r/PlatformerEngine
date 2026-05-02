int initStruct() {
    // Textures
    for(int i = 0; i < sizeof(textures)/sizeof(textures[0]); i++) {
        textures[i].reserved = false;
        textures[i].textureName[0] = '\0';
        textures[i].texture = NULL;
        textures[i].SizeScale = 0;
        textures[i].textureSize = 0;
        textures[i].textureAnimationSize = 0;
    }

    // LightTextures
    for(int i = 0; i < sizeof(lightTextures)/sizeof(lightTextures[0]); i++) {
        lightTextures[i].reserved = false;
        lightTextures[i].textureName[0] = '\0';
        lightTextures[i].texture = NULL;
    }

    // Scripts
    for(int i = 0; i < sizeof(scriptfiles)/sizeof(scriptfiles[0]); i++) {
        scriptfiles[i].reserved = false;
        scriptfiles[i].scriptName[0] = '\0';
        scriptfiles[i].script = NULL;
        scriptfiles[i].scriptCompiled = NULL;
        scriptfiles[i].commandsNumber = 0;
    }

    // Backgrounds
    for(int i = 0; i < sizeof(backgrounds)/sizeof(backgrounds[0]); i++) {
        backgrounds[i].reserved = false;
        backgrounds[i].textureName[0] = '\0';
        backgrounds[i].texture = NULL;
        backgrounds[i].textureWidth = 0;
        backgrounds[i].textureHeight = 0;
    }

    // LevelsLists
    for(int i = 0; i < sizeof(levelsList)/sizeof(levelsList[0]); i++) {
       levelsList[i].levelPath[0] = '\0';
       levelsList[i].PB[0] = '\0';
       levelsList[i].levelName[0] = '\0';
       levelsList[i].levelNameSize = 0;
       levelsList[i].reserved = false;
    }

    // Enemies
    for(int i = 0; i < sizeof(enemy)/sizeof(enemy[0]); i++) {
      enemy[i].reserved = false;
      enemy[i].killed = false;
      enemy[i].attackPrepare = false;
      enemy[i].onPlatform = false;
      enemy[i].unbump = false;
    }

    // Platforms
    for(int i = 0; i < sizeof(platforms)/sizeof(platforms[0]); i++) {
        platforms[i].reserved = false;
        platforms[i].texture = NULL;
        platforms[i].platformUsed = false;
        platforms[i].collidable = false;
        platforms[i].slopeInv = false;
        platforms[i].textureStretch = false;
        platforms[i].NofinishAnimation = false;
        platforms[i].grapplable = false;
        platforms[i].moveNodeReverse = false;
    }

    // Triggers
    for(int i = 0; i < sizeof(triggers)/sizeof(triggers[0]); i++) {
        triggers[i].reserved = false;
        triggers[i].triggerUsed = false;
        triggers[i].timerStart = false;
    }

    // Lights
    for(int i = 0; i < sizeof(light)/sizeof(light[0]); i++) {
        light[i].reserved = false;
        light[i].moveNodeReverse = false;
    }

    // Displacements
    for(int i = 0; i < sizeof(displacement)/sizeof(displacement[0]); i++) {
        displacement[i].reserved = false;
        displacement[i].moveNodeReverse = false;
    }

    // DeathBoxes
    for(int i = 0; i < sizeof(deathbox)/sizeof(deathbox[0]); i++) {
        deathbox[i].reserved = false;
        deathbox[i].moveNodeReverse = false;
    }

    // MoveNodes
    for(int i = 0; i < sizeof(movenodes)/sizeof(movenodes[0]); i++) {
        movenodes[i].reserved = false;
        movenodes[i].nodesCount = 0;
        movenodes[i].wrap = false;
    }

    // ScriptBlocks
    for(int i = 0; i < sizeof(scripts)/sizeof(scripts[0]); i++) {
        scripts[i].reserved = false;
        scripts[i].used = false;
        scripts[i].startTimer = false;
        scripts[i].execute = false;
    }

    // Buttons
    for(int i = 0; i < sizeof(buttons)/sizeof(buttons[0]); i++) {
        buttons[i].reserved = false;
        buttons[i].iconTexture = NULL;
        buttons[i].text = NULL;
        buttons[i].textSize = 0;
        buttons[i].value[0] = '\0';
        buttons[i].button_func = NULL;
        buttons[i].hoverable = false;
        buttons[i].highlight = false;
        buttons[i].transitionEnable = false;
        buttons[i].hoverSound = false;
    }

    // Sliders
    for(int i = 0; i < sizeof(sliders)/sizeof(sliders[0]); i++) {
        sliders[i].reserved = false;
        sliders[i].iconTexture = NULL;
        sliders[i].text = NULL;
        sliders[i].textSize = 0;
        sliders[i].value[0] = '\0';
        sliders[i].hoverable = false;
        sliders[i].highlight = false;
    }

    // Knobs
    for(int i = 0; i < sizeof(knobs)/sizeof(knobs[0]); i++) {
        knobs[i].reserved = false;
        knobs[i].iconTexture = NULL;
        knobs[i].text = NULL;
        knobs[i].textSize = 0;
        knobs[i].value[0] = '\0';
        knobs[i].hoverable = false;
    }

    // TextBoxes
    for(int i = 0; i < sizeof(textbox)/sizeof(textbox[0]); i++) {
        textbox[i].reserved = false;
        textbox[i].textBoxName[0] = '\0';
        textbox[i].textContent[0] = '\0';
        textbox[i].textContentSize = 0;
    }

    // Damages
    for(int i = 0; i < sizeof(damagepopups)/sizeof(damagepopups[0]); i++) {
        damagepopups[i].reserved = false;
    }

    // Particles
    for(int i = 0; i < sizeof(particles)/sizeof(particles[0]); i++) {
        particles[i].reserved = false;
        particles[i].texture = NULL;
    }

    // Projectiles
    for(int i = 0; i < sizeof(projectiles)/sizeof(projectiles[0]); i++) {
        projectiles[i].reserved = false;
        projectiles[i].fromEnemy = false;
    }

    // Specials
    for(int i = 0; i < sizeof(specials)/sizeof(specials[0]); i++) {
        specials[i].reserved = false;
        specials[i].taken = false;
    }

    // TextPopups
    for(int i = 0; i < sizeof(textpopups)/sizeof(textpopups[0]); i++) {
         textpopups[i].reserved = false;
         textpopups[i].textContent = NULL;
         
    }

    // Editor (single instance)
    editor.selected = false;
    editor.saving = false;
    editor.unSelect = false;
    editor.mapNameSet = false;
    editor.mouseToObjectDistanceBool = false;
    editor.fileNameSave[0] = '\0';
    editor.mapName[0] = '\0';
    editor.alertText[0] = '\0';
    editor.fileNameSize = 0;

    // App (single instance)
    app.backgroundName[0] = '\0';
    app.campaignLevelName[0] = '\0';
    app.levelGoTo[0] = '\0';
    app.transitionFunction = NULL;
    app.escapeFunction = NULL;
    app.transitionEnabled = false;
    app.fetchedList = false;
    app.inputChange = false;
    app.transition = false;
    app.statusChanged = false;
    app.showFPS = false;

    // Level (single instance)
    level.keyInputs[0] = '\0';
    level.keyInputsSize = 0;
    level.Paused = false;
    level.Finished = false;
    level.Started = false;
    level.transitionToLevel = false;
    level.tempFileMade = false;
    level.newRecord = false;
    level.campaignLevel = false;
    level.absolutePath[0] = '\0';
    level.checkpointCount = 0;

    // MapData (single instance)
    mapData.mapName[0] = '\0';
    mapData.mapNameLen = 0;
    mapData.ghostInGame = false;
    mapData.ghostEnd = false;

    return 0;
}


int initVideo(){
   if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
      printf("SDL Unsupported\n");
      return 1;
   }

   window = SDL_CreateWindow("Game",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,windowWidth,windowHeight,0);
   if (!window){
      printf("Window failed to load:%s\n",SDL_GetError());
      return 1;
      }
   renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_PRESENTVSYNC); 
   if (!renderer){
      printf("Renderer failed to load:%s\n",SDL_GetError());
      return 1;
   }
   IMG_Init(IMG_INIT_PNG);
   initStruct();
   FAppInit_Values();
   FLoadTextures();
   FLoadScripts();
   FLoadBackgrounds();
    /// Load SDL mixer 
   
   if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 8, 128) == -1 )
   {
       return 0;    
   }
   FLoadSounds();
   // Load App Status(Ugly looking i know)
   SDL_memcpy(app.backgroundName,"background\0",len("background\0"));
   
   if(CheckUsernameProfile()){
      startMenu();
   }
   else{
      startGameIntro();
   }
   SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_BLEND);
   SDL_SetWindowResizable(window, SDL_TRUE);
   app.WINDOW_LOOP = true;
   return 0;
}


void FwindowResize(){
   SDL_GetWindowSize(window,&windowWidth,&windowHeight); 
   
   windowHeightScale = (float)gameHeight/gameHeightBase;
   windowWidthScale = (float)gameWidth/gameWidthBase;
   

   if(app.status == 1){
      FswitchAppStatus(app.status,1);
   }

}

void gameResolutionChange(){
   SDL_GetWindowSize(window,&windowWidth,&windowHeight);
   gameWidth = app.resolutions[app.resolutionInt][0];
   gameHeight = app.resolutions[app.resolutionInt][1];
   windowHeightScale = (float)gameHeight/gameHeightBase;
   windowWidthScale = (float)gameWidth/gameWidthBase;
   
   SDL_DestroyTexture(resultLayer);
   SDL_DestroyTexture(lightLayer);
   SDL_DestroyTexture(lightLayer2);
 
   lightLayer      = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, gameWidth, gameHeight);
   lightLayer2     = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, gameWidth, gameHeight);
   resultLayer     = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, gameWidth, gameHeight);
   SDL_SetTextureBlendMode(lightLayer, SDL_BLENDMODE_MOD);
   SDL_SetTextureBlendMode(lightLayer2, SDL_BLENDMODE_ADD);
   SDL_SetTextureBlendMode(resultLayer,SDL_BLENDMODE_ADD);

}