



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
   renderer = SDL_CreateRenderer(window,-1,0); 
   if (!renderer){
      printf("Renderer failed to load:%s\n",SDL_GetError());
      return 1;
   }
   IMG_Init(IMG_INIT_PNG);

   FAppInit_Values();
   FLoadTextures();
   FLoadBackgrounds();



   // Load App Status(Ugly looking i know)
  SDL_memcpy(app.backgroundName,"background\0",len("background\0"));
   if(CheckUsernameProfile()){
      FswitchAppStatus(0,4);
   }
   else{
      FswitchAppStatus(0,5);
   }

   

   SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_BLEND);
   SDL_SetWindowResizable(window, SDL_TRUE);
   app.WINDOW_LOOP = true;
   
   return 0;
}


void FwindowResize(){
   SDL_GetWindowSize(window,&windowWidth,&windowHeight); 
   
   windowHeightScale = (float)windowHeight/gameHeight;
   windowWidthScale = (float)windowWidth/gameWidth;
   

   if(app.status == 1){
      FswitchAppStatus(app.status,1);
   }

}

void gameResolutionChange(){
   SDL_GetWindowSize(window,&windowWidth,&windowHeight);
   windowHeightScale = (float)windowHeight/gameHeight;
   windowWidthScale = (float)windowWidth/gameWidth; 
   gameWidth = app.resolutions[app.resolutionInt][0];
   gameHeight = app.resolutions[app.resolutionInt][1];
   FswitchAppStatus(app.status,app.status);
  SDL_DestroyTexture(resultLayer);
  SDL_DestroyTexture(HUDLayer);
  SDL_DestroyTexture(lightLayer);
  SDL_DestroyTexture(lightLayer2);
  SDL_DestroyTexture(backgroundLayer);
  
  backgroundLayer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, gameWidth, gameHeight);
  lightLayer      = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, gameWidth, gameHeight);
  lightLayer2     = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, gameWidth, gameHeight);
  HUDLayer        = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, gameWidth, gameHeight);
  resultLayer     = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, gameWidth, gameHeight);
  SDL_SetTextureBlendMode(backgroundLayer, SDL_BLENDMODE_BLEND);
   SDL_SetTextureBlendMode(lightLayer, SDL_BLENDMODE_MOD);
   SDL_SetTextureBlendMode(lightLayer2, SDL_BLENDMODE_ADD);
   SDL_SetTextureBlendMode(HUDLayer, SDL_BLENDMODE_BLEND);
   SDL_SetTextureBlendMode(resultLayer,SDL_BLENDMODE_ADD);

}