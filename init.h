



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

   FLoadTextures();
   FLoadBackgrounds();

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