void FLoadTextures(){    
   for(int i = 0;i<sizeof(textures)/sizeof(textures[0]);i++){
      textures[i].texture = NULL;
      textures[i].SizeScale = 1;
   }

   surface_player = IMG_Load("assets/player/player.png");
   surface_background = IMG_Load("assets/backgrounds/background2.png");
   surface_font = IMG_Load("assets/fonts/font_atlas.png");
   surface_trigger = IMG_Load("assets/editor/flag.png");

   tex_background = SDL_CreateTextureFromSurface(renderer,surface_background);
   tex_font = SDL_CreateTextureFromSurface(renderer,surface_font);
   tex_player = SDL_CreateTextureFromSurface(renderer,surface_player);
   tex_trigger = SDL_CreateTextureFromSurface(renderer,surface_trigger);

  DIR *p;
  struct dirent *pp;     
  p = opendir ("./assets/textures");
  int index = 1;
  if (p != NULL)
  {
    while ((pp = readdir (p))!=NULL) {
      int length = strlen(pp->d_name);
      if (FCompareStrings(FlowerCase(&(pp->d_name[length-4]),4),".png\0")) {
         char tempName[256];
         int tempNameSize = 0;
         for(int i = 0;i<sizeof(pp->d_name);i++){
           if(pp->d_name[i] == '.'){break;}
           SDL_memcpy(&tempName[tempNameSize],&pp->d_name[i],1);
           tempNameSize++;
         }
         tempName[tempNameSize] = '\0';
         char path[256];
         SDL_memcpy(textures[index].textureName,tempName,tempNameSize+1);
         sprintf(path,"assets/textures/%s\0",pp->d_name);
         printf("Loaded %s\n",path);
         SDL_Surface *texture_Surface = IMG_Load(path);
         SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer,texture_Surface); 
         textures[index].texture = texture;
         textures[index].reserved = true;
         index++;
         SDL_FreeSurface(texture_Surface);
      }
    }
    (void) closedir (p);
  }
  textures[0].reserved = true;
  SDL_memcpy(textures[0].textureName,"None\0",5);
/////////
 
}
void FLoadBackgrounds(){
   
  for(int i = 0;i<sizeof(backgrounds)/sizeof(backgrounds[0]);i++){
      backgrounds[i].texture = NULL;
   }

   surface_player = IMG_Load("assets/player/player.png");
   surface_font = IMG_Load("assets/fonts/font_atlas.png");
   surface_trigger = IMG_Load("assets/editor/flag.png");
   surface_bulb = IMG_Load("assets/editor/bulb.png");
   surface_displacement = IMG_Load("assets/editor/displacement.png");
   surface_light = IMG_Load("assets/light/light.png");
   surface_skull = IMG_Load("assets/editor/skull.png");

   backgroundLayer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, windowWidth, windowHeight);
   lightLayer      = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, windowWidth, windowHeight);
   lightLayer2     = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, windowWidth, windowHeight);
   resultLayer     = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, windowWidth, windowHeight);
   HUDLayer     = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, windowWidth, windowHeight);
   

   tex_light = SDL_CreateTextureFromSurface(renderer,surface_light);
   tex_font = SDL_CreateTextureFromSurface(renderer,surface_font);
   tex_player = SDL_CreateTextureFromSurface(renderer,surface_player);
   tex_trigger = SDL_CreateTextureFromSurface(renderer,surface_trigger);
   tex_bulb = SDL_CreateTextureFromSurface(renderer,surface_bulb);
   tex_displacement = SDL_CreateTextureFromSurface(renderer,surface_displacement);
   tex_skull = SDL_CreateTextureFromSurface(renderer,surface_skull);
 
   SDL_FreeSurface(surface_font);
   SDL_FreeSurface(surface_trigger);
   SDL_FreeSurface(surface_player);
   SDL_FreeSurface(surface_bulb);
   SDL_FreeSurface(surface_displacement);
   SDL_FreeSurface(surface_light);

  DIR *p;
  struct dirent *pp;     
  p = opendir ("./assets/backgrounds");
  int index = 1;
  if (p != NULL)
  {
    while ((pp = readdir (p))!=NULL) {
      int length = strlen(pp->d_name);
      if (FCompareStrings(FlowerCase(&(pp->d_name[length-4]),4),".png\0")) {
         char tempName[256];
         int tempNameSize = 0;
         for(int i = 0;i<sizeof(pp->d_name);i++){
           if(pp->d_name[i] == '.'){break;}
           SDL_memcpy(&tempName[tempNameSize],&pp->d_name[i],1);
           tempNameSize++;
         }
         tempName[tempNameSize] = '\0';
         char path[256];
         SDL_memcpy(backgrounds[index].textureName,tempName,tempNameSize+1);
         sprintf(path,"assets/backgrounds/%s\0",pp->d_name);
         printf("Loaded %s\n",path);
         SDL_Surface *texture_Surface = IMG_Load(path);
         SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer,texture_Surface); 
         backgrounds[index].texture = texture;
         backgrounds[index].reserved = true;
         SDL_QueryTexture(backgrounds[index].texture,NULL,NULL,&backgrounds[index].textureWidth,&backgrounds[index].textureHeight);
         index++;
         SDL_FreeSurface(texture_Surface);
      }
    }
    (void) closedir (p);
  }
  backgrounds[0].reserved = true;
  SDL_memcpy(backgrounds[0].textureName,"None\0",5);
}


int FindTextureInt(char* textureName){
   for(int i = 1;i<sizeof(textures)/sizeof(textures[0]);i++){
     if(textures[i].reserved){
      if(FCompareStrings(textures[i].textureName,textureName)){
         return i;
      }
     }
   }
}

int FindBackgroundInt(char* textureName){
   for(int i = 1;i<sizeof(backgrounds)/sizeof(backgrounds[0]);i++){
     if(backgrounds[i].reserved){
      if(FCompareStrings(backgrounds[i].textureName,textureName)){
         
         return i;
      }
     }
   }
}