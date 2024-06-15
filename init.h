int initVideo(){
   if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
      printf("SDL Unsupported\n");
      return 1;
   }

   window = SDL_CreateWindow("Game",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,windowWidth,windowHeight,SDL_WINDOW_OPENGL);
   if (!window){
      printf("Window failed to load:%s\n",SDL_GetError());
      return 1;
      }
   renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
   if (!renderer){
      printf("Renderer failed to load:%s\n",SDL_GetError());
      return 1;
   }
   IMG_Init(IMG_INIT_PNG);

   surface_tile = IMG_Load("assets/tile.png");
   surface_tile2 = IMG_Load("assets/tile2.png");
   surface_tile3 = IMG_Load("assets/tile3.png");
   surface_tile4 = IMG_Load("assets/tile4.png");
   surface_player = IMG_Load("assets/player.png");
   surface_background = IMG_Load("assets/background.png");
   surface_tileBnW = IMG_Load("assets/tileEnd.png");
   surface_tileStart = IMG_Load("assets/startTile.png");
   surface_font = IMG_Load("assets/font_atlas.png");
   surface_trigger = IMG_Load("assets/trigger.png");
   surface_checkpoint = IMG_Load("assets/tileCheckPoint.png");

   tex_tile = SDL_CreateTextureFromSurface(renderer,surface_tile);
   tex_tile2 = SDL_CreateTextureFromSurface(renderer,surface_tile2);
   tex_tile3 = SDL_CreateTextureFromSurface(renderer,surface_tile3);
   tex_tile4 = SDL_CreateTextureFromSurface(renderer,surface_tile4);
   tex_player = SDL_CreateTextureFromSurface(renderer,surface_player);
   tex_background = SDL_CreateTextureFromSurface(renderer,surface_background);
   tex_tileBnW = SDL_CreateTextureFromSurface(renderer,surface_tileBnW);
   tex_tileStart = SDL_CreateTextureFromSurface(renderer,surface_tileStart);
   tex_font = SDL_CreateTextureFromSurface(renderer,surface_font);
   tex_trigger = SDL_CreateTextureFromSurface(renderer,surface_trigger);
   tex_checkpoint = SDL_CreateTextureFromSurface(renderer,surface_checkpoint);

   SDL_FreeSurface(surface_tile);
   SDL_FreeSurface(surface_tile2);
   SDL_FreeSurface(surface_tile3);
   SDL_FreeSurface(surface_tile4);
   SDL_FreeSurface(surface_player);
   SDL_FreeSurface(surface_background);
   SDL_FreeSurface(surface_tileBnW);
   SDL_FreeSurface(surface_tileStart);
   SDL_FreeSurface(surface_trigger);
   SDL_FreeSurface(surface_checkpoint);

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