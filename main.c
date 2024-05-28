#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
// Variables
#define PI 3.14159 

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
int windowWidth = 900;
int windowHeight = 600;

#define GRAVITY 500


SDL_Surface* surface_tile = NULL;
SDL_Texture* tex_tile = NULL;

SDL_Surface* surface_tile2 = NULL;
SDL_Texture* tex_tile2 = NULL;

SDL_Surface* surface_tile3 = NULL;
SDL_Texture* tex_tile3 = NULL;

SDL_Surface* surface_tile4 = NULL;
SDL_Texture* tex_tile4 = NULL;

SDL_Surface* surface_tileBnW = NULL;
SDL_Texture* tex_tileBnW = NULL;

SDL_Surface* surface_tileStart = NULL;
SDL_Texture* tex_tileStart = NULL;

SDL_Surface* surface_player = NULL;
SDL_Texture* tex_player = NULL;

SDL_Surface* surface_font = NULL;
SDL_Texture* tex_font = NULL;

SDL_Surface* surface_background = NULL;
SDL_Texture* tex_background = NULL;

// players 
struct LevelsList{
   bool reserved;
   char levelPath[256];
   char PB[9];
   char levelName[256];
   int levelNameSize;
};

struct Level{
  char absolutePath[256];
  int absolutePathSize;
  double timer;
  bool Paused;
  bool Finished;
  bool Started;
  char keyInputs[2000];
  bool tempFileMade;
  int keyInputsSize;
  bool newRecord;
} level;

struct Camera{
   double x;
   double y;
   double scale;
   double randValue;
   bool freeCam;
} camera;

struct App{
   double backgroundMoving;
   int status;
   int statusTo;
   double deltaTime;
   double deltaTimeGhost;
   double WINDOW_TICKS;
   bool WINDOW_LOOP;
   bool fetchedList;
   bool inputChange;
   bool transition;
   int transitionInt;
}app;

struct Button{
  bool reserved;
  double x;
  double y;
  char* text;
  int textSize;
  double ButtonFontHeight;
  double ButtonFontWidth;
  double hoverWidth;
  double hoverHeight;
  double hoverOpacity;
  bool hoverable;
};

struct MapData{
   // for clarity these values that the camera will not follow if the player goes beyond them.
   int PBTimer;
   char mapName[256];
   char creatorName[256];
   int mapNameLen;
   int creatorNameLen;
   double xMin;
   double yMin;
   double xMax;
   double yMax;
   int ghostNextInput; 
   int fileadditionIndex;
   int ghostCurrentIndex;
   bool ghostInGame;
   bool ghostEnd;
   int tickDifference;
} mapData;
struct Players {
    double spawnX;
    double spawnY;
    double x;
    double y;
    double xDraw;
    double yDraw;
    double Owidth;
    double width;
    double height;
    double widthDraw;
    double heightDraw;
    double veloX;
    double veloY;
    double jumpVelo;
    double accX;
    double accY;
    bool onPlatform;
    int onWall;
    int direction;
    double animationIndex;
    double idleIndex;
    double playerControl;

};


struct Platform{
   bool reserved;
   double x;
   double y;
   double slope;
   double width;
   double height;
   bool slopeInv;
   double textureScale;
   SDL_Texture* texture;
   bool textureStretch;
   bool textureStretchPer;
   int platformType;
};

struct KeyboardBind{
   bool up;
   bool down;
   bool left;
   bool right;
   bool shift;
   bool r;
   bool escape;
   bool escapeRelease;
};


struct MouseBind{
   // 0 idle
   // 1 pressed
   // -1 released (status with one frame per click)

   int x;
   int y;
   int left;
   int right;
   bool middle;
   int roll;
} mouse;


struct KeyboardBind key;
struct KeyboardBind ghostKey;
struct Players player;
struct Players Ghostplayer;
struct Platform platforms[100];
struct Button buttons[100];
struct LevelsList levelsList[256];
void FswitchAppStatus(int from, int to);
void FSetDataMap(char* path,int pathSize);
char* FGetDataMap(char* fileName,char* type,int dataType,int fileNameSize);
char* msToTimer(int ms);
void FapplyMovementGhost();
void FGameRestart();
void appendTransition(int from ,int to);
void FDrawTransition();
double min(double a, double b){
   return a < b ? a : b;
}
double max(double a, double b){
   return a > b ? a : b;
}
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

   tex_tile = SDL_CreateTextureFromSurface(renderer,surface_tile);
   tex_tile2 = SDL_CreateTextureFromSurface(renderer,surface_tile2);
   tex_tile3 = SDL_CreateTextureFromSurface(renderer,surface_tile3);
   tex_tile4 = SDL_CreateTextureFromSurface(renderer,surface_tile4);
   tex_player = SDL_CreateTextureFromSurface(renderer,surface_player);
   tex_background = SDL_CreateTextureFromSurface(renderer,surface_background);
   tex_tileBnW = SDL_CreateTextureFromSurface(renderer,surface_tileBnW);
   tex_tileStart = SDL_CreateTextureFromSurface(renderer,surface_tileStart);
   tex_font = SDL_CreateTextureFromSurface(renderer,surface_font);

   SDL_FreeSurface(surface_tile);
   SDL_FreeSurface(surface_tile2);
   SDL_FreeSurface(surface_tile3);
   SDL_FreeSurface(surface_tile4);
   SDL_FreeSurface(surface_player);
   SDL_FreeSurface(surface_background);
   SDL_FreeSurface(surface_tileBnW);
   SDL_FreeSurface(surface_tileStart);

   SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_BLEND);
   app.WINDOW_LOOP = true;
   return 0;
}

void FInput_Listener(){
   SDL_Event event;
   SDL_PollEvent(&event);
   key.escapeRelease = false;
   if (event.type == SDL_QUIT){
      app.WINDOW_LOOP = false;
   }
   if (event.type == SDL_KEYDOWN){
      switch(event.key.keysym.sym){
         case SDLK_UP:
         if(!key.up){app.inputChange = true;}
          key.up = true;
          break;
         case SDLK_DOWN:
         if(!key.down){app.inputChange = true;}
          key.down = true;
          break;
         case SDLK_LEFT:
         if(!key.left){app.inputChange = true;}
          key.left = true;
          break;
         case SDLK_RIGHT:
         if(!key.right){app.inputChange = true;}
          key.right = true;
          break;
         case SDLK_LSHIFT:
         if(!key.shift){app.inputChange = true;}
          key.shift = true;
          break;
         case SDLK_r:
          key.r = true;
          break;
         case SDLK_ESCAPE:
          key.escape = true;
          break;
     } 
   }
   if (event.type == SDL_KEYUP){
      app.inputChange = true;
      switch(event.key.keysym.sym){
         case SDLK_UP:
         if(key.up){app.inputChange = true;}
          key.up = false;
          break;
         case SDLK_DOWN:
         if(key.down){app.inputChange = true;}
          key.down = false;
          break;
         case SDLK_LEFT:
         if(key.left){app.inputChange = true;}
          key.left = false;
          break;
         case SDLK_RIGHT:
         if(key.right){app.inputChange = true;}
          key.right = false;
          break;
         case SDLK_LSHIFT:
         if(key.shift){app.inputChange = true;}
          key.shift = false;
          break;
         case SDLK_r:
          key.r = false;
          break;
         case SDLK_ESCAPE:
          key.escape = false;
          if(app.status == 0){
            appendTransition(app.status,4);
          }
          
          break;
     } 
   }
   if(event.type == SDL_MOUSEMOTION){
    SDL_GetMouseState(&mouse.x,&mouse.y);
   }
   if(mouse.left == -1){
      mouse.left = 0;
   }
   if(mouse.right == -1){
      mouse.right = 0;
   }
   if(event.type == SDL_MOUSEBUTTONDOWN){
      if(event.button.button == SDL_BUTTON_LEFT){
         mouse.left = 1;
      }
      else if(event.button.button == SDL_BUTTON_RIGHT){
         mouse.right = 1;
      }
   }
   if(event.type == SDL_MOUSEBUTTONDOWN){
      if(event.button.button == SDL_BUTTON_LEFT){
         mouse.left = 1;
      }
      if(event.button.button == SDL_BUTTON_RIGHT){
         mouse.right = 1;
      }
   }
   if(event.type == SDL_MOUSEBUTTONUP){
      if(event.button.button == SDL_BUTTON_LEFT){
         mouse.left = -1;
      }
      if(event.button.button == SDL_BUTTON_RIGHT){
         mouse.right = -1;
         
      }
   }
}
void appendTransition(int from,int to){
   app.transition = true;
   app.statusTo = to;
}
void FdeltaTime(){
   app.deltaTime =      ((double)(SDL_GetTicks()-app.WINDOW_TICKS))/1000;
   app.deltaTimeGhost = ((double)(SDL_GetTicks()-app.WINDOW_TICKS))/1000;
   app.WINDOW_TICKS = SDL_GetTicks();
}
int FCheck_Collision(int platformID){
   double distanceRatio = (player.x + player.width/2 - platforms[platformID].x)/(platforms[platformID].width);
   if(platforms[platformID].slopeInv){
      distanceRatio = distanceRatio = 1 - (player.x + player.width/2 - platforms[platformID].x)/(platforms[platformID].width);
   } 
   return (player.x+player.width > platforms[platformID].x && platforms[platformID].x+platforms[platformID].width > player.x && player.y+player.height > platforms[platformID].y-(platforms[platformID].height*sin(platforms[platformID].slope))*distanceRatio && platforms[platformID].y+platforms[platformID].height > player.y);
}
int FCheck_Collision_Ghost(int platformID){
   double distanceRatio = (Ghostplayer.x + Ghostplayer.width/2 - platforms[platformID].x)/(platforms[platformID].width);
   if(platforms[platformID].slopeInv){
      distanceRatio = distanceRatio = 1 - (Ghostplayer.x + Ghostplayer.width/2 - platforms[platformID].x)/(platforms[platformID].width);
   } 
   return (Ghostplayer.x+Ghostplayer.width > platforms[platformID].x && platforms[platformID].x+platforms[platformID].width > Ghostplayer.x && Ghostplayer.y+Ghostplayer.height > platforms[platformID].y-(platforms[platformID].height*sin(platforms[platformID].slope))*distanceRatio && platforms[platformID].y+platforms[platformID].height > Ghostplayer.y);
}
void FtexturePlatform(int platformID){
     SDL_Point points[5]; 
     points[0].x = platforms[platformID].x;
     points[0].y = platforms[platformID].y-(platforms[platformID].height*sin(platforms[platformID].slope))*(platforms[platformID].slopeInv);
     points[1].x = platforms[platformID].x+platforms[platformID].width;
     points[1].y = platforms[platformID].y-(platforms[platformID].height*sin(platforms[platformID].slope))*(!platforms[platformID].slopeInv);
     points[2].x = platforms[platformID].x+platforms[platformID].width;
     points[2].y = platforms[platformID].y+platforms[platformID].height;
     points[3].x = platforms[platformID].x;
     points[3].y = platforms[platformID].y+platforms[platformID].height;
     points[4].x = points[0].x;
     points[4].y = points[0].y;
     
  if(platforms[platformID].textureStretch){
       SDL_Vertex vertex_1 = {{(int)points[0].x, (int)points[0].y}, {255, 255, 255, 255}, {0, 0}};
       SDL_Vertex vertex_2 = {{(int)points[1].x, (int)points[1].y}, {255, 255, 255, 255}, {1, 0}};
       SDL_Vertex vertex_3 = {{(int)points[2].x, (int)points[2].y}, {255, 255, 255, 255}, {1, 1}};
       SDL_Vertex vertex_4 = {{(int)points[3].x, (int)points[3].y}, {255, 255, 255, 255}, {0, 1}}; 

       SDL_Vertex vertices[] = {
         vertex_1,
         vertex_2,
         vertex_3,
         vertex_4  
       };
       SDL_RenderGeometry(renderer, platforms[platformID].texture, vertices, 4, (int[6]){1,2,3,0,1,3}, 6);
   return;
  }
   for(double i = platforms[platformID].x;i<platforms[platformID].x + platforms[platformID].width;i += platforms[platformID].textureScale){ 
      double j = platforms[platformID].y+platforms[platformID].height-platforms[platformID].textureScale;
      while(true){
       double distanceRatio1 = (i - platforms[platformID].x)/(platforms[platformID].width);
       double distanceRatio2 = (i + platforms[platformID].textureScale - platforms[platformID].x)/(platforms[platformID].width);
       if(platforms[platformID].slopeInv){
          distanceRatio1 = 1 - (i - platforms[platformID].x)/(platforms[platformID].width);
          distanceRatio2 = 1 - (i + platforms[platformID].textureScale - platforms[platformID].x)/(platforms[platformID].width);
       } 
       
       SDL_Point points2[4];
       
       points2[0].x = i;
       points2[0].y = max(j+platforms[platformID].textureScale,platforms[platformID].y - platforms[platformID].height*sin(platforms[platformID].slope)*distanceRatio1);
       points2[1].x = min(i+platforms[platformID].textureScale,platforms[platformID].x + platforms[platformID].width);
       points2[1].y = max(j+platforms[platformID].textureScale,platforms[platformID].y - platforms[platformID].height*sin(platforms[platformID].slope)*distanceRatio2);
       points2[2].x = min(i+platforms[platformID].textureScale,platforms[platformID].x + platforms[platformID].width);
       points2[2].y = max(j,platforms[platformID].y - platforms[platformID].height*sin(platforms[platformID].slope)*distanceRatio2);
       points2[3].x = i;
       points2[3].y = max(j,platforms[platformID].y - platforms[platformID].height*sin(platforms[platformID].slope)*distanceRatio1);    
       points2[4].x = points2[0].x;
       points2[4].y = points2[0].y;
       
       double xTexture =  (points2[1].x-i)/platforms[platformID].textureScale;
       double yTexture0 = SDL_abs((points2[1].y - points2[3].y))/platforms[platformID].textureScale;
       double yTexture1 = SDL_abs((points2[1].y - points2[2].y))/platforms[platformID].textureScale;
       
       if(xTexture >= 1){
         xTexture = 1;
       }
       else if(xTexture <= 0){
         xTexture = 0;
       }


       if(yTexture0 >= 1){
         yTexture0 = 1;
       }
       else if(yTexture0 <= 0){
         yTexture0 = 0;
       }
       if(yTexture1 >= 1){
         yTexture1 = 1;
       }
       else if(yTexture1 <= 0){
         yTexture1 = 0;
       }
       if(platforms[platformID].textureStretchPer){
         yTexture0 = 1;
         yTexture1 = 1;
       }
       SDL_Vertex vertex_1 = {{(int)points2[0].x, (int)points2[0].y}, {255, 255, 255, 255}, {0, 0}};
       SDL_Vertex vertex_2 = {{(int)points2[1].x, (int)points2[1].y}, {255, 255, 255, 255}, {xTexture, 0}};
       SDL_Vertex vertex_3 = {{(int)points2[2].x, (int)points2[2].y}, {255, 255, 255, 255}, {xTexture, yTexture1}};
       SDL_Vertex vertex_4 = {{(int)points2[3].x, (int)points2[3].y}, {255, 255, 255, 255}, {0, yTexture0}}; 

       SDL_Vertex vertices[] = {
         vertex_1,
         vertex_2,
         vertex_3,
         vertex_4  
       };
       SDL_RenderGeometry(renderer, platforms[platformID].texture, vertices, 4, (int[6]){1,2,3,0,1,3}, 6);
       
       if(j<platforms[platformID].y-2*platforms[platformID].height){
         break;
      }
      j -= platforms[platformID].textureScale;
      }
   }
   SDL_SetRenderDrawColor(renderer,50,50,50,255);
   SDL_RenderDrawLines(renderer,points,5);
}

void renderText(int stringCount,char *Text,int x ,int y, int width,int height,int opacity,int color[3]){
  // DEALS WITH TEXT AS WELL AS NUMBERS
  
  char str[stringCount];
  for(int i = 0;i<stringCount;i++){
    str[i] = *(Text+i);
  }
  int posX;
  int cap;
  int num;
  SDL_SetTextureAlphaMod(tex_font,opacity); 
  // OUTLINE --> TEXT (order of rendering)   
  int outLineOffset = 2;
    // {text}
  for (int i = 0;i<stringCount;i++){
      cap = 0;
      num = 0;
      int charValue = str[i] - 'a';
      if (str[i]>=65 && str[i]<=90){
        cap = 1;
        num = 0;
        charValue += 32;
      }
      else if (str[i]>= 48 && str[i]<= 58){
        num = 1;
        cap = 0;
        charValue += 49;
      }
      posX = charValue*40;
     
    
    SDL_SetTextureColorMod( tex_font, 0,0,0);
    SDL_RenderCopy(renderer,tex_font,&(SDL_Rect){posX,80*cap+150*num,40,70-(6*cap)}
                                    ,&(SDL_Rect){x-outLineOffset+i*(width/stringCount),y-outLineOffset,width/stringCount,height});
    
    SDL_SetTextureColorMod( tex_font, color[0],color[1],color[2]);
    SDL_RenderCopy(renderer,tex_font,&(SDL_Rect){posX,80*cap+150*num,40,70-(6*cap)}
                                    ,&(SDL_Rect){x+i*(width/stringCount),y,width/stringCount,height});
   } 
    SDL_SetTextureAlphaMod(tex_font,255);
}

void FbuttonHover(){
  for(int i = 0;i<sizeof(buttons)/sizeof(buttons[0]);i++){
   if(buttons[i].reserved && buttons[i].hoverable){
      int yMin = buttons[i].y;
      int yMax = buttons[i].y+buttons[i].hoverHeight;
      int xMin = buttons[i].x;
      int xMax = buttons[i].x+buttons[i].hoverWidth;
     
      if(mouse.x >= xMin && mouse.x <= xMax && mouse.y >= yMin && mouse.y <= yMax){
         buttons[i].hoverOpacity += 1000*app.deltaTime;
         if(buttons[i].hoverOpacity >= 100){
            buttons[i].hoverOpacity = 100;
         }
      }
      else{
         buttons[i].hoverOpacity -= 1000*app.deltaTime;
         if(buttons[i].hoverOpacity < 0){
            buttons[i].hoverOpacity = 0;
         }
      }
      SDL_SetRenderDrawColor(renderer,255,255,255,(int)(buttons[i].hoverOpacity));
     
      SDL_RenderFillRect(renderer,&(SDL_Rect){buttons[i].x-5,buttons[i].y-5,buttons[i].hoverWidth,buttons[i].hoverHeight});
   }
  }
  SDL_SetRenderDrawColor(renderer,100,100,100,255);
}

void FlistLevels(){
   // copy pasted off of stackoverflow
  DIR *p;
  struct dirent *pp;     
  p = opendir ("./levels");
  int index = 0;
  if (p != NULL)
  {
    while ((pp = readdir (p))!=NULL) {
      int length = strlen(pp->d_name);
      if (strncmp(pp->d_name + length - 4, ".txt", 4) == 0) {
         char tempName[256];
         int tempNameSize = 0;
         for(int i = 0;i<sizeof(pp->d_name);i++){
           if(pp->d_name[i] == '.'){break;}
           SDL_memcpy(&tempName[tempNameSize],&pp->d_name[i],1);
           tempNameSize++;
         }
         tempName[tempNameSize] = '\0';
         SDL_memcpy(levelsList[index].levelName,tempName,tempNameSize+1);
         sprintf(levelsList[index].levelPath,"levels/%s.txt",levelsList[index].levelName);
         levelsList[index].levelPath[tempNameSize+11] = '\0';
         levelsList[index].levelNameSize = tempNameSize+1;
         levelsList[index].reserved = true;
         index++;
      }
    }
    (void) closedir (p);
  }
}
void FDrawTransition(){
  SDL_SetRenderDrawColor(renderer,0,0,0,255);
  if(app.transition){
   SDL_RenderFillRect(renderer,&(SDL_Rect){-windowWidth+app.transitionInt,0,windowWidth,windowHeight});
   app.transitionInt+=2*windowWidth*app.deltaTime;
   if(app.transitionInt>=windowWidth){
      FswitchAppStatus(app.status,app.statusTo);
   }
   if(app.transitionInt>=2*windowWidth){
      app.transitionInt = 0;
      app.transition = false;
   }
  } 
}
void FswitchAppStatus(int from, int to){
   if(from == 0){
      FGameRestart();
   }
   for(int i = 0;i<sizeof(buttons)/sizeof(buttons[0]);i++){
      buttons[i].reserved = false;
   }
   app.status = to;
   if(to == 4){
    buttons[0].x = 30;
    buttons[0].y = 200;
    buttons[0].text = "Play";
    buttons[0].textSize = sizeof("Play");
    buttons[0].ButtonFontHeight = 32;
    buttons[0].ButtonFontWidth = 20;
    buttons[0].hoverOpacity = 0;
    buttons[0].hoverable = true;
    buttons[0].hoverWidth = buttons[0].textSize*buttons[0].ButtonFontWidth + 10;
    buttons[0].hoverHeight = buttons[0].ButtonFontHeight + 5;
    buttons[0].reserved = true;
    
    buttons[1].x = 30;
    buttons[1].y = 250;
    buttons[1].text = "Editor";
    buttons[1].textSize = sizeof("Editor");
    buttons[1].ButtonFontHeight = 32;
    buttons[1].ButtonFontWidth = 20;
    buttons[1].hoverOpacity = 0;
    buttons[1].hoverWidth = buttons[1].textSize*buttons[1].ButtonFontWidth + 10;
    buttons[1].hoverHeight = buttons[0].ButtonFontHeight + 5;
    buttons[1].reserved = true;
    buttons[1].hoverable = true;
 
 
    buttons[2].x = 30;
    buttons[2].y = 300;
    buttons[2].text = "Settings";
    buttons[2].textSize = sizeof("Settings");
    buttons[2].ButtonFontHeight = 32;
    buttons[2].ButtonFontWidth = 20;
    buttons[2].hoverOpacity = 0;
    buttons[2].hoverWidth = buttons[2].textSize*buttons[2].ButtonFontWidth + 10;
    buttons[2].hoverHeight = buttons[0].ButtonFontHeight + 5;
    buttons[2].reserved = true;
    buttons[2].hoverable = true;
 
    buttons[3].x = 30;
    buttons[3].y = 350;
    buttons[3].text = "Exit";
    buttons[3].textSize = sizeof("Exit");
    buttons[3].ButtonFontHeight = 32;
    buttons[3].ButtonFontWidth = 20;
    buttons[3].hoverOpacity = 0;
    buttons[3].hoverWidth = buttons[3].textSize*buttons[3].ButtonFontWidth + 10;
    buttons[3].hoverHeight = buttons[0].ButtonFontHeight + 5;
    buttons[3].reserved = true;
    buttons[3].hoverable = true;
   }
   if(to == 2){
     app.fetchedList = false;
     buttons[0].reserved = true;
     buttons[0].x = 20;
     buttons[0].y = 50;
     buttons[0].hoverable = false;
     buttons[0].text = "Levels";
     buttons[0].textSize = sizeof("Levels");
     buttons[0].ButtonFontHeight = 60;
     buttons[0].ButtonFontWidth = 30;
     buttons[0].hoverHeight = buttons[0].ButtonFontHeight + 5;
     buttons[0].hoverWidth = buttons[0].ButtonFontWidth*buttons[0].textSize + 10;
     
     FlistLevels();
     
     for(int i = 0;i<(sizeof(levelsList)/sizeof(levelsList[0]));i++){
      if(levelsList[i].reserved){
        buttons[i+1].reserved = true;
        buttons[i+1].x = 20;
        buttons[i+1].y = 150+i*30;
        buttons[i+1].text = levelsList[i].levelName;
        buttons[i+1].textSize = levelsList[i].levelNameSize;
        buttons[i+1].ButtonFontHeight = 20;
        buttons[i+1].hoverable = true;
        buttons[i+1].ButtonFontWidth = 15;
        buttons[i+1].hoverHeight = buttons[i+1].ButtonFontHeight + 5;
        buttons[i+1].hoverWidth = 500; 
        
      }
      
     }
     return;
   }
}

void FDraw_Menu(){
   SDL_RenderClear(renderer);
   SDL_RenderCopy(renderer,tex_background,&(SDL_Rect){app.backgroundMoving,0,576,324},&(SDL_Rect){0,0,windowWidth-app.backgroundMoving*windowWidth/576,windowHeight});
   SDL_RenderCopy(renderer,tex_background,&(SDL_Rect){0,0,app.backgroundMoving,324},&(SDL_Rect){windowWidth-app.backgroundMoving*windowWidth/576,0,app.backgroundMoving*windowWidth/576,windowHeight});
   
   FbuttonHover();

   for(int i = 0;i<sizeof(buttons)/sizeof(buttons[0]);i++){
      if(buttons[i].reserved){
         renderText(buttons[i].textSize,buttons[i].text,buttons[i].x,buttons[i].y,buttons[i].textSize*buttons[i].ButtonFontWidth,buttons[i].ButtonFontHeight,255,(int[3]){255,255,255});
         
         if(app.status == 2 && i > 0){
           if(!app.fetchedList){
           char* PBTemp = FGetDataMap(levelsList[i-1].levelPath,"m",2,levelsList[i-1].levelNameSize);
           SDL_memcpy(levelsList[i-1].PB,PBTemp,9);
           free(PBTemp);
           }
           renderText(9,msToTimer(atoi(levelsList[i-1].PB)),buttons[i].hoverWidth-70,buttons[i].y+3,(buttons[i].ButtonFontWidth-5)*9,buttons[i].ButtonFontHeight-5,255,(int[3]){255,255,255});
         }
      }
   }
   
   if(app.status == 2){
      app.fetchedList = true;
      SDL_SetRenderDrawColor(renderer,100,100,100,100);
      SDL_RenderFillRect(renderer,&(SDL_Rect){10,10,windowWidth-30,windowHeight-30});
   }
   renderText(sizeof("Made by mrGun3r"),"Made by mrGun3r",windowWidth-sizeof("Made by mrGun3r")*9,windowHeight - 15,sizeof("Made by mrGun3r")*9,15,255,(int[3]){220,220,220});
}

void FUpdate_Data_Menu(){
   app.backgroundMoving += 5*app.deltaTime;
   if(app.backgroundMoving >= 576){
      app.backgroundMoving = 0;
   }
   for(int i = 0;i<sizeof(buttons)/sizeof(buttons[0]);i++){
    if(buttons[i].reserved){
      int yMin = buttons[i].y;
      int yMax = buttons[i].y+buttons[i].hoverHeight;
      int xMin = buttons[i].x;
      int xMax = buttons[i].x+buttons[i].hoverWidth;
     
      if(mouse.x >= xMin && mouse.x <= xMax && mouse.y >= yMin && mouse.y <= yMax && mouse.left == -1){
        mouse.left = 0;
        if(app.status == 2 && i > 0){
          FSetDataMap(levelsList[i-1].levelPath,levelsList[i-1].levelNameSize+12);
          appendTransition(app.status,0);
        }
        if(app.status == 4){
         // play button
         if(i == 0){
            FswitchAppStatus(app.status,2);
         }

        }
         
         
      }
    }
   }


}
// Game-----
int len(char* a){
   for(int i = 0;i<256;i++){
      if (a[i] == '\0'){
         return i;
      }
   }
   return 256;
}
void FaddReplay(){
   
   FILE *fileMap = fopen(level.absolutePath,"r");
   FILE *fileMapNew = NULL;
   if(!level.tempFileMade){
      fileMapNew = fopen("levels/temp.txt","w");
   }
   
   char buffer[256];
   bool add = false;
   while(fgets(buffer,256,fileMap)){
     
      if(!level.tempFileMade){
      if(buffer[0] == '/'){
       fputs("/\n",fileMapNew);
       add = true;
      }
      if(!add){
         fputs(buffer,fileMapNew);
         continue;
      }
      fclose(fileMapNew);
      }
      fileMapNew = fopen("levels/temp.txt","a");
      for(int i = 0;i<level.keyInputsSize;i++){
         fputc((int)level.keyInputs[i],fileMapNew);
      }    
      fclose(fileMapNew);
      break;
   }
   fclose(fileMap); 
}
void FDisplayHUD(){
   char* timer = msToTimer((int)level.timer);
   renderText(8,timer,5,5,8*12,20,255,(int[3]){255,255,255});
   free(timer);
   if(mapData.PBTimer>0){
     char* PBtimer = msToTimer(mapData.PBTimer);
     renderText(sizeof("PB"),"PB",5,30,sizeof("PB")*7,10,255,(int[3]){200,0,0});
     renderText(8,PBtimer,30,30,8*7,10,255,(int[3]){200,200,200});
     free(PBtimer);
   }
   char fps[5];
   SDL_itoa((int)1/app.deltaTime,fps,10);
   renderText(len(fps),fps,200,500,30,30,255,(int[3]){200,200,200});
   renderText(mapData.mapNameLen,mapData.mapName,windowWidth-mapData.mapNameLen*12,5,mapData.mapNameLen*12,18,255,(int[3]){255,255,255});
   renderText(mapData.creatorNameLen,mapData.creatorName,windowWidth-mapData.creatorNameLen*7,29,mapData.creatorNameLen*7,10,255,(int[3]){210,210,210});
    if(level.newRecord){
      renderText(sizeof("New Record"),"New Record",10+8*12,8,sizeof("New Record")*12,15,255,(int[3]){0,200,0});
   }
}
void FDraw_Game(){

   ///// The data used in the function is transformed to fit the camera's requirements 
   ///// They are camera-manipulated data for only rendering purposes
  // Here lies transformed data
 /////-------------------------------START OF RENDERING
   camera.randValue += 1*app.deltaTime;
   //camera.scale = (2+sin(camera.randValue));
      
   if(!camera.freeCam){
     camera.x = -windowWidth/2+player.x+player.width/2;
     camera.y = -windowHeight/2+player.y+player.height/2; 
   }
   else{
     camera.x += (player.x+player.width/2-windowWidth/2 - camera.x)*10*app.deltaTime;
     camera.y += (player.y+player.height/2-windowHeight/2 - camera.y)*10*app.deltaTime;
   } 
   if (camera.x > mapData.xMax - windowWidth + player.width/2){
       camera.x = mapData.xMax - windowWidth + player.width/2;
   }
   if (camera.x < mapData.xMin + player.width/2){
       camera.x = mapData.xMin + player.width/2;    
   }

   if (camera.y > mapData.yMax - windowHeight + player.height/2){
       camera.y = mapData.yMax - windowHeight + player.height/2;
   }
   if (camera.y < mapData.yMin + player.height/2){
       camera.y = mapData.yMin + player.height/2;    
   }
   app.backgroundMoving += 5*app.deltaTime;
   if(app.backgroundMoving >= 576){
      app.backgroundMoving = 0;
   }
   SDL_RenderClear(renderer);
   SDL_RenderCopy(renderer,tex_background,&(SDL_Rect){app.backgroundMoving,0,576,324},&(SDL_Rect){0,0,windowWidth-app.backgroundMoving*windowWidth/576,windowHeight});
   SDL_RenderCopy(renderer,tex_background,&(SDL_Rect){0,0,app.backgroundMoving,324},&(SDL_Rect){windowWidth-app.backgroundMoving*windowWidth/576,0,app.backgroundMoving*windowWidth/576,windowHeight});
   SDL_SetRenderDrawColor(renderer,50,50,50,255);
   // Display timer
   // Draw player
   player.xDraw = player.x;
   player.yDraw = player.y;
   player.widthDraw = player.width;
   player.heightDraw = player.height;

   player.xDraw -= camera.x;
   player.yDraw -= camera.y;

   player.widthDraw *= camera.scale;
   player.heightDraw *= camera.scale;

   player.xDraw      -= windowWidth/2;
   player.yDraw      -= windowHeight/2;
   player.xDraw      *= camera.scale;
   player.yDraw      *= camera.scale;
   player.xDraw      += windowWidth/2;
   player.yDraw      += windowHeight/2;
   
  Ghostplayer.xDraw = Ghostplayer.x;
  Ghostplayer.yDraw = Ghostplayer.y;
  Ghostplayer.widthDraw = Ghostplayer.width;
  Ghostplayer.heightDraw = Ghostplayer.height;
  if(mapData.ghostInGame){
   Ghostplayer.xDraw -= camera.x;
   Ghostplayer.yDraw -= camera.y;

   Ghostplayer.widthDraw  *= camera.scale;
   Ghostplayer.heightDraw *= camera.scale;

   Ghostplayer.xDraw      -= windowWidth/2;
   Ghostplayer.yDraw      -= windowHeight/2;
   Ghostplayer.xDraw      *= camera.scale;
   Ghostplayer.yDraw      *= camera.scale;
   Ghostplayer.xDraw      += windowWidth/2;
   Ghostplayer.yDraw      += windowHeight/2;
   SDL_SetTextureAlphaMod(tex_player,100);
   SDL_RendererFlip flip1 = SDL_FLIP_NONE;
   if(Ghostplayer.direction < 0){
      flip1 = SDL_FLIP_HORIZONTAL;
   }
   if((int)Ghostplayer.accX != 0 && (int)Ghostplayer.jumpVelo == 0){
   if(SDL_abs(Ghostplayer.veloX)>=200){
      Ghostplayer.width = Ghostplayer.Owidth + 3;
      SDL_RenderCopyEx(renderer,tex_player,&(SDL_Rect){1+((int)(Ghostplayer.animationIndex) % 6 )*24,47,18,16},&(SDL_Rect){Ghostplayer.xDraw,Ghostplayer.yDraw,Ghostplayer.widthDraw,Ghostplayer.heightDraw},0,NULL,flip1);
   }
   else{
      Ghostplayer.width = Ghostplayer.Owidth;
   SDL_RenderCopyEx(renderer,tex_player,&(SDL_Rect){2+((int)(Ghostplayer.animationIndex) % 6 )*24,2,15,18},&(SDL_Rect){Ghostplayer.xDraw,Ghostplayer.yDraw,Ghostplayer.widthDraw,Ghostplayer.heightDraw},0,NULL,flip1);
   }
   }
   else if ((int)Ghostplayer.jumpVelo == 0){
      Ghostplayer.width = Ghostplayer.Owidth;
     SDL_RenderCopyEx(renderer,tex_player,&(SDL_Rect){2+((int)(Ghostplayer.idleIndex) % 2 )*24,24,15,18},&(SDL_Rect){Ghostplayer.xDraw,Ghostplayer.yDraw,Ghostplayer.widthDraw,Ghostplayer.heightDraw},0,NULL,flip1);
   }
   else{
      Ghostplayer.width = Ghostplayer.Owidth;
      SDL_RenderCopyEx(renderer,tex_player,&(SDL_Rect){49,24,15,18},&(SDL_Rect){Ghostplayer.xDraw,Ghostplayer.yDraw,Ghostplayer.widthDraw,Ghostplayer.heightDraw},0,NULL,flip1);
   }
   SDL_SetTextureAlphaMod(tex_player,255);
  }
   
   
   SDL_RendererFlip flip = SDL_FLIP_NONE;
   if(player.direction < 0){
      flip = SDL_FLIP_HORIZONTAL;
   }
   if((int)player.accX != 0 && (int)player.jumpVelo == 0){
   if(SDL_abs(player.veloX)>=200){
      player.width = player.Owidth + 3;
      SDL_RenderCopyEx(renderer,tex_player,&(SDL_Rect){1+((int)(player.animationIndex) % 6 )*24,47,18,16},&(SDL_Rect){player.xDraw,player.yDraw,player.widthDraw,player.heightDraw},0,NULL,flip);
   }
   else{
      player.width = player.Owidth;
   SDL_RenderCopyEx(renderer,tex_player,&(SDL_Rect){2+((int)(player.animationIndex) % 6 )*24,2,15,18},&(SDL_Rect){player.xDraw,player.yDraw,player.widthDraw,player.heightDraw},0,NULL,flip);
   }
   }
   else if ((int)player.jumpVelo == 0){
      player.width = player.Owidth;
     SDL_RenderCopyEx(renderer,tex_player,&(SDL_Rect){2+((int)(player.idleIndex) % 2 )*24,24,15,18},&(SDL_Rect){player.xDraw,player.yDraw,player.widthDraw,player.heightDraw},0,NULL,flip);
   }
   else{
      player.width = player.Owidth;
      SDL_RenderCopyEx(renderer,tex_player,&(SDL_Rect){49,24,15,18},&(SDL_Rect){player.xDraw,player.yDraw,player.widthDraw,player.heightDraw},0,NULL,flip);
   }
   ///////

   // Draw platforms
   SDL_SetRenderDrawColor(renderer,120,120,120,255);
   for (int i = 0;i<sizeof(platforms)/sizeof(platforms[0]);i++){
      if(platforms[i].reserved){
         // Camera offsetted data !
         platforms[i].x -= camera.x;
         platforms[i].y -= camera.y;
         platforms[i].width  *= camera.scale;
         platforms[i].height *= camera.scale;
      
         platforms[i].x      -= windowWidth/2;
         platforms[i].y      -= windowHeight/2;
         platforms[i].x      *= camera.scale;
         platforms[i].y      *= camera.scale;
         platforms[i].x      += windowWidth/2;
         platforms[i].y      += windowHeight/2;
         platforms[i].textureScale *= camera.scale;
         SDL_SetRenderDrawColor(renderer,200,200,200,255);
         

         FtexturePlatform(i);
         
         // Reset data to normal map data!
         platforms[i].x = (platforms[i].x-windowWidth/2)/camera.scale  + windowWidth/2;
         platforms[i].y = (platforms[i].y-windowHeight/2)/camera.scale + windowHeight/2;
 
         platforms[i].width  /= camera.scale;
         platforms[i].height /= camera.scale;
             
         platforms[i].x += camera.x;
         platforms[i].y += camera.y;
         platforms[i].textureScale /= camera.scale;

      }
   }
   FDisplayHUD();
   /////-------------------------------END OF RENDERING
}
void FGameRestart(){
   if(level.newRecord){
      level.newRecord = false;
   }
    if(mapData.PBTimer>0){
        mapData.ghostInGame = true; 
      }
      remove("levels/temp.txt");
      mapData.ghostEnd = false;
      mapData.ghostNextInput = 0;
      mapData.fileadditionIndex = 0;
      mapData.ghostCurrentIndex = 0;
      level.Finished = false;
      level.Started = false;
      player.x = player.spawnX;
      player.y = player.spawnY;
      Ghostplayer.x = player.spawnX;
      Ghostplayer.y = player.spawnY;
      player.veloX = 0;
      player.veloY = 0;
      player.accX = 0;
      player.accY = 0;
      player.jumpVelo = 0;
      Ghostplayer.veloY = 0;
      Ghostplayer.veloX = 0;
      Ghostplayer.accY = 0;
      Ghostplayer.accX = 0;
      Ghostplayer.jumpVelo = 0;
      ghostKey.up = false;
      ghostKey.down = false;
      ghostKey.left = false;
      ghostKey.right = false;
      ghostKey.shift = false;
      level.tempFileMade = false;
      level.keyInputsSize = 0;
}
void FPlayer_Movement(){
    if(!level.Started){
      if(key.left || key.right){
         level.Started = true;
      }
    }
   if(player.y > mapData.yMax){
      FGameRestart();
   }
   if(player.playerControl < 1){
      player.playerControl += 1*app.deltaTime;
      if(player.playerControl >= 1){
         player.playerControl = 1;
      }
   }
   player.idleIndex += 2*app.deltaTime;
   if (player.idleIndex >= 20){
      player.idleIndex = 0;
   }
   if (key.up && player.onPlatform){
      player.jumpVelo = -150;
   }
   if (key.left){
      player.accX = (-500-300*(key.shift))*player.playerControl;
      player.animationIndex += 10*app.deltaTime;
      player.direction = -1;
   }
   else if (key.right){
      player.accX = (500+300*(key.shift))*player.playerControl;
      player.animationIndex += 10*app.deltaTime;
      player.direction = 1;
   }
   else {player.accX = 0;}
   player.veloX += player.accX*app.deltaTime;
   if(level.Started){
      player.veloY += (player.accY + GRAVITY)*app.deltaTime;
   }
   player.veloX *= pow(0.05,app.deltaTime);
   if (fabs(player.veloX) >= 150+500*(key.shift)){
      player.veloX = (150+500*(key.shift))*(1-2*(player.veloX < 0));
   }

   player.x += player.veloX*app.deltaTime;
   if(level.Started){
     player.y += (player.veloY + player.jumpVelo)*app.deltaTime; 
   }
   if(!player.onPlatform){
      player.accY = 0;
   }
   if (player.onWall && key.up){
      player.veloY = 0;
      player.jumpVelo = -150;
      player.veloX = 100*player.onWall; 
      player.playerControl = 0;
   }


   if(mapData.PBTimer>0){
    if(level.Started){
      FapplyMovementGhost();
    }
    
   if(mapData.ghostEnd){
         ghostKey.up = false;
         ghostKey.left = false;
         ghostKey.right = false;
         ghostKey.down = false;
         ghostKey .shift = false;
   }

   if(Ghostplayer.playerControl < 1){
      Ghostplayer.playerControl += 1*app.deltaTimeGhost;
      if(Ghostplayer.playerControl >= 1){
         Ghostplayer.playerControl = 1;
      }
   }
   Ghostplayer.idleIndex += 2*app.deltaTimeGhost;
   if (Ghostplayer.idleIndex >= 20){
      Ghostplayer.idleIndex = 0;
   }
   if (ghostKey.up && Ghostplayer.onPlatform){
      Ghostplayer.jumpVelo = -150;
   }
   if (ghostKey.left){
      Ghostplayer.accX = (-500-300*(ghostKey.shift))*Ghostplayer.playerControl;
      Ghostplayer.animationIndex += 10*app.deltaTimeGhost;
      Ghostplayer.direction = -1;
   }
   else if (ghostKey.right){
      Ghostplayer.accX = (500+300*(ghostKey.shift))*Ghostplayer.playerControl;
      Ghostplayer.animationIndex += 10*app.deltaTimeGhost;
      Ghostplayer.direction = 1;
   }
   else {Ghostplayer.accX = 0;}
   Ghostplayer.veloX += Ghostplayer.accX*app.deltaTimeGhost;
   if(level.Started){
     Ghostplayer.veloY += (Ghostplayer.accY + GRAVITY)*app.deltaTimeGhost; 
   }
   Ghostplayer.veloX *= pow(0.05,app.deltaTimeGhost);
   if (fabs(Ghostplayer.veloX) >= 150+500*(ghostKey.shift)){
      Ghostplayer.veloX = (150+500*(ghostKey.shift))*(1-2*(Ghostplayer.veloX < 0));
   }

   Ghostplayer.x += Ghostplayer.veloX*app.deltaTimeGhost;
   if(level.Started){
     Ghostplayer.y += (Ghostplayer.veloY + Ghostplayer.jumpVelo)*app.deltaTimeGhost; 
   }

   if(!Ghostplayer.onPlatform){
      Ghostplayer.accY = 0;
      
   }
   if (Ghostplayer.onWall && ghostKey.up){
      Ghostplayer.veloY = 0;
      Ghostplayer.jumpVelo = -150;
      Ghostplayer.veloX = 100*Ghostplayer.onWall; 
      Ghostplayer.playerControl = 0;
   }
   
   }
}
double returnDistance(double x1,double y1,double x2,double y2){
   return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}
void FcheckPB(){
   FaddReplay();
   level.tempFileMade = true;
   level.keyInputsSize = 0;

   FILE *fileMap = fopen("levels/temp.txt","r"); 
   if(level.timer >= mapData.PBTimer && mapData.PBTimer > 0){
    level.tempFileMade = false;
    fclose(fileMap);
    remove("levels/temp.txt");
    return;
   }
   level.newRecord = true;
   mapData.PBTimer = (int)level.timer;
   FILE *NewfileMap = (FILE*)fopen("levels/levelDataN.txt","w");
   char PBchar[(int)(SDL_log10(level.timer+1))+2];
   SDL_itoa((int)level.timer,PBchar,10);
   
   PBchar[(int)(SDL_log10(level.timer+1))+1] = ',';
   
   char buffer[256];
   int tempBufferSize = 0;
   char TempBuffer[256];
   while(fgets(buffer,256,fileMap)){
      if(buffer[0] == 'm'){
        int count = 0;
        for(int i = 0;i<256;i++){
         if(buffer[i] == ';'){
            TempBuffer[tempBufferSize]  = ';';
            TempBuffer[tempBufferSize+1]  = '\n';
            TempBuffer[tempBufferSize+2]  = '\0';
            break;
         }
         if(count == 2){
            if(buffer[i] == ','){
              SDL_memcpy(&TempBuffer[tempBufferSize],PBchar,(int)(SDL_log10(level.timer+1)) + 2);
              tempBufferSize += (int)(SDL_log10(level.timer+1) + 2);
              count++;
              continue;
            }
            continue;
         }
         if(buffer[i] == ','){
            count++;
         }
         TempBuffer[tempBufferSize] = buffer[i];
         tempBufferSize++;
        }
        fputs(TempBuffer,NewfileMap);
      }
      else{
         fputs(buffer,NewfileMap);
      }
   }
   fclose(NewfileMap);
   fclose(fileMap);

   remove("levels/temp.txt");
   remove(level.absolutePath);
   rename("levels/levelDataN.txt",level.absolutePath);

   
   return;
}
void FCollision_Response(int platformID){
   double distanceRatio = (player.x - platforms[platformID].x + player.width/2)/(platforms[platformID].width);
   if(platforms[platformID].slopeInv){
      distanceRatio = 1 - (player.x + player.width/2 - platforms[platformID].x)/(platforms[platformID].width);
   } 

   if (SDL_min(SDL_abs(player.x+player.width-platforms[platformID].x)+1,SDL_abs(player.x-platforms[platformID].x-platforms[platformID].width)+1)>SDL_min(SDL_abs(player.y+player.height-platforms[platformID].y+platforms[platformID].height*sin(platforms[platformID].slope)*distanceRatio),SDL_abs(player.y-platforms[platformID].y-platforms[platformID].height)))   
    {
      if (SDL_abs(player.y + player.height - platforms[platformID].y +platforms[platformID].height*sin(platforms[platformID].slope)*distanceRatio)>SDL_abs(player.y - platforms[platformID].y - platforms[platformID].height)){
        player.y = platforms[platformID].y + platforms[platformID].height;
         if(player.jumpVelo + player.veloY < 0){
            player.jumpVelo = 0;
         player.veloY = 0;
         }
         
        
       }
       else {   
         if(platforms[platformID].platformType == 2 && !level.Finished){
            level.Finished = true;
            
               FcheckPB();
            
         }
             player.y = platforms[platformID].y - player.height - platforms[platformID].height*sin(platforms[platformID].slope)*distanceRatio;
             player.onPlatform = true;
            if(player.jumpVelo + player.veloY > 0){
              player.jumpVelo = 0;
              player.veloY = 0;
            }       
         }
    }
    else {
      player.veloX *= pow(0.9,app.deltaTime);
      if (SDL_abs(player.x + player.width - platforms[platformID].x)>SDL_abs(player.x - platforms[platformID].x - platforms[platformID].width)){
      player.x = platforms[platformID].x + platforms[platformID].width;
      
     }
     else {
      player.x = platforms[platformID].x - player.width;
      }

      player.onWall = -1;
      if(player.x+player.width/2 > platforms[platformID].x+platforms[platformID].width){
         player.onWall *= -1;
      }
    }
} 
void FCollision_Response_Ghost(int platformID){
   double distanceRatio = (Ghostplayer.x - platforms[platformID].x + Ghostplayer.width/2)/(platforms[platformID].width);
   if(platforms[platformID].slopeInv){
      distanceRatio = 1 - (Ghostplayer.x + Ghostplayer.width/2 - platforms[platformID].x)/(platforms[platformID].width);
   } 

   if (SDL_min(SDL_abs(Ghostplayer.x+Ghostplayer.width-platforms[platformID].x)+1,SDL_abs(Ghostplayer.x-platforms[platformID].x-platforms[platformID].width)+1)>SDL_min(SDL_abs(Ghostplayer.y+Ghostplayer.height-platforms[platformID].y+platforms[platformID].height*sin(platforms[platformID].slope)*distanceRatio),SDL_abs(Ghostplayer.y-platforms[platformID].y-platforms[platformID].height)))   
    {
      if (SDL_abs(Ghostplayer.y + Ghostplayer.height - platforms[platformID].y +platforms[platformID].height*sin(platforms[platformID].slope)*distanceRatio)>SDL_abs(Ghostplayer.y - platforms[platformID].y - platforms[platformID].height)){
        Ghostplayer.y = platforms[platformID].y + platforms[platformID].height;
         if(Ghostplayer.jumpVelo + Ghostplayer.veloY < 0){
            Ghostplayer.jumpVelo = 0;
            Ghostplayer.veloY = 0;
         }
         
        
       }
       else {   
         if(platforms[platformID].platformType == 2 && !level.Finished){
            mapData.ghostEnd = true;
         }
             Ghostplayer.y = platforms[platformID].y - Ghostplayer.height - platforms[platformID].height*sin(platforms[platformID].slope)*distanceRatio;
             Ghostplayer.onPlatform = true;
            if(Ghostplayer.jumpVelo + Ghostplayer.veloY > 0){
              Ghostplayer.jumpVelo = 0;
              Ghostplayer.veloY = 0;
            }       
         }
    }
    else {
      Ghostplayer.veloX *= pow(0.9,app.deltaTimeGhost);
      if (SDL_abs(Ghostplayer.x + Ghostplayer.width - platforms[platformID].x)>SDL_abs(Ghostplayer.x - platforms[platformID].x - platforms[platformID].width)){
      Ghostplayer.x = platforms[platformID].x + platforms[platformID].width;
      
     }
     else {
      Ghostplayer.x = platforms[platformID].x - Ghostplayer.width;
      }

      Ghostplayer.onWall = -1;
      if(Ghostplayer.x + Ghostplayer.width/2 > platforms[platformID].x + platforms[platformID].width){
         Ghostplayer.onWall *= -1;
      }
    }
} 
void FapplyMovementGhost(){
   if(mapData.ghostInGame){
      if(mapData.PBTimer <= level.timer && mapData.PBTimer > 0){
         mapData.ghostEnd = true;
         return;
      }
      char type[20];
      sprintf(type,"i%d",mapData.ghostCurrentIndex);
      char* msPress = FGetDataMap(level.absolutePath,type,0,level.absolutePathSize);
      mapData.ghostNextInput = atoi(msPress);
      // if(app.deltaTimeGhost > ((int)level.timer - mapData.ghostNextInput)/1000){
      //    app.deltaTimeGhost += mapData.tickDifference/1000;
      // }
      // else{app.deltaTimeGhost = app.deltaTime;}
      if(level.timer < mapData.ghostNextInput-1){return;}
      if(msPress){
         mapData.ghostCurrentIndex++;
      }
      else{return;}
      mapData.tickDifference = ((int)level.timer - mapData.ghostNextInput);
      char* up = FGetDataMap(level.absolutePath,type,1,level.absolutePathSize);
      char* left = FGetDataMap(level.absolutePath,type,2,level.absolutePathSize);
      char* right = FGetDataMap(level.absolutePath,type,3,level.absolutePathSize);
      char* down = FGetDataMap(level.absolutePath,type,4,level.absolutePathSize);
      char* shift = FGetDataMap(level.absolutePath,type,5,level.absolutePathSize);
      char* pX =  FGetDataMap(level.absolutePath,type,6,level.absolutePathSize);
      char* pY =  FGetDataMap(level.absolutePath,type,7,level.absolutePathSize);
      char* pvX =  FGetDataMap(level.absolutePath,type,8,level.absolutePathSize);
      char* pvY =  FGetDataMap(level.absolutePath,type,9,level.absolutePathSize);
      
      ghostKey.up = (bool)atoi(up);
      ghostKey.left = (bool)atoi(left);
      ghostKey.right = (bool)atoi(right);
      ghostKey.down = (bool)atoi(down);
      ghostKey.shift = (bool)atoi(shift);
      Ghostplayer.x = (float)atoi(pX);
      Ghostplayer.y = (float)atoi(pY);
      Ghostplayer.veloX = (float)atof(pvX);
      Ghostplayer.veloY = (float)atof(pvY);  
      free(up);
      free(left);
      free(right);
      free(down);
      free(shift);
      free(msPress);
   }
}
void FUpdate_Data(){
    if(!level.Paused){
    FPlayer_Movement();
    if(app.inputChange && !level.Finished && level.Started){
      char keyInputChange[200];
      sprintf(keyInputChange,"i%d:%d,%d,%d,%d,%d,%d,%d,%d,%f,%f;\n\0",mapData.fileadditionIndex,(int)level.timer,key.up,key.left,key.right,key.down,key.shift,(int)player.x,(int)player.y,player.veloX,player.veloY);
      mapData.fileadditionIndex++;
      SDL_memcpy(&level.keyInputs[level.keyInputsSize],keyInputChange,len(keyInputChange));  
      level.keyInputsSize += len(keyInputChange);
      if(level.keyInputsSize >= 1024){
         FaddReplay();
         level.tempFileMade = true;
         level.keyInputsSize = 0;
      }
      app.inputChange = false;
   }
   app.deltaTimeGhost = app.deltaTime;
   if(key.r){
    FGameRestart();
   }
   player.onPlatform = false;
   player.onWall = false;
   Ghostplayer.onPlatform = false;
   Ghostplayer.onWall = false;
   for (int i = 0;i<sizeof(platforms)/sizeof(platforms[0]);i++){
      if (platforms[i].reserved){
      if(FCheck_Collision_Ghost(i)){
         FCollision_Response_Ghost(i);
      }
      if(FCheck_Collision(i)){
         FCollision_Response(i);
      }
    }
   }
   if(!level.Finished && level.Started){
      level.timer += 1000*app.deltaTime;
   }
   else if(!level.Started){level.timer = 0;}
   }
}
//----
void FWindow_Loop(){
   while(app.WINDOW_LOOP){
    FInput_Listener();

    if(app.status == 0){
      FUpdate_Data();
      FDraw_Game();
    }
    else{
      FUpdate_Data_Menu();
      FDraw_Menu();
    }  
    FDrawTransition();
    FdeltaTime();
    SDL_RenderPresent(renderer);
   }
}

void FSetValue(char* importBuffer,int importBufferSize,int data,int ID,int dataType){
   if(dataType == 0){
     platforms[ID].reserved = true;
     bool boolean;
     SDL_Texture* texture = NULL;
     switch(data){
      case 0:
       platforms[ID].x = atof(importBuffer);
       break;
      case 1:
       platforms[ID].y = atof(importBuffer);
       break;
      case 2:
       platforms[ID].width = atof(importBuffer);
       break;
      case 3:
       platforms[ID].height = atof(importBuffer);
       break;
      case 4:
       platforms[ID].slope = atof(importBuffer);
       break;
      case 5: 
       if(importBuffer[0] == 'f'){boolean = false;}
       else{boolean = true;}
       platforms[ID].slopeInv = boolean;
       break;
      case 6:
       platforms[ID].textureScale = atof(importBuffer);
       break;
      case 7:
       if(atoi(importBuffer) == 1){
         texture = tex_tile;
       }
       else if(atoi(importBuffer) == 2){
         texture = tex_tile2;
       }
       else if(atoi(importBuffer) == 3){
         texture = tex_tile3;
       }
       else if(atoi(importBuffer) == 4){
         texture = tex_tile4;
       }
       else if(atoi(importBuffer) == 5){
         texture = tex_tileStart;
       }
       else if(atoi(importBuffer) == 6){
         texture = tex_tileBnW;
       }
       platforms[ID].texture = texture;
      case 8:
       if(importBuffer[0] == 'f'){boolean = false;}
       else{boolean = true;}
       platforms[ID].textureStretchPer = boolean;
       break;
      case 9:
       if(importBuffer[0] == 'f'){boolean = false;}
       else{boolean = true;}
       platforms[ID].textureStretch = boolean;
       break;
      case 10:
       
       platforms[ID].platformType = atoi(importBuffer);
       

       break;
       }
     }
     else if(dataType == 1){
      switch (data)
      {
      case 0:
         player.x = atof(importBuffer);
         player.spawnX = atof(importBuffer);
         Ghostplayer.x = atof(importBuffer);
         Ghostplayer.spawnX = atof(importBuffer);
         break;
      case 1:
         player.y = atof(importBuffer);
         player.spawnY = atof(importBuffer);
         Ghostplayer.y = atof(importBuffer);
         Ghostplayer.spawnY = atof(importBuffer);
         break;
      case 2:
         player.Owidth = atof(importBuffer);
         Ghostplayer.Owidth = atof(importBuffer);
         break;
      case 3:
         player.width = atof(importBuffer);
         Ghostplayer.width = atof(importBuffer);
         break;
      case 4:
         player.height = atof(importBuffer);
         Ghostplayer.height = atof(importBuffer);
         break;
      }
     }
     else if(dataType == 2){
     
      switch(data){
      case 0:
         SDL_memcpy(mapData.mapName,importBuffer,importBufferSize);
         mapData.mapNameLen = importBufferSize;
         break;
      case 1:
        SDL_memcpy(mapData.creatorName,importBuffer,importBufferSize);
         mapData.creatorNameLen = importBufferSize;
         break;
      case 2:
         mapData.PBTimer = atoi(importBuffer);
         break;
      case 3:
         mapData.xMin = atof(importBuffer);
         break;
      case 4:
         mapData.yMin = atof(importBuffer);
         break;
      case 5:
         mapData.xMax = atof(importBuffer);
         break;
      case 6:
         mapData.yMax = atof(importBuffer);
         break;
     }
     }
}
void FSetDataMap(char* path,int pathSize){
   mapData.ghostNextInput = 0;
   mapData.fileadditionIndex = 0;
   mapData.ghostCurrentIndex = 0;
   SDL_memcpy(level.absolutePath,path,pathSize+7);
   FILE *fileMap = fopen(path,"r");
 
   char buffer[256];
   char importBuffer[256];
   while(fgets(buffer,256,fileMap)){
     int importBufferSize = 0;
     int DataImport = -1;
     int IndexData = 0; 
     int ID = 0;
     for(int i = 0;i<256;i++){ 
      if(buffer[i] == ';'){
         char *importBufferShortened = malloc(importBufferSize+1);
         SDL_memcpy(importBufferShortened,importBuffer,importBufferSize+1);
         importBufferShortened[importBufferSize] = '\0';
         
         
         FSetValue(importBufferShortened,importBufferSize,IndexData,ID,DataImport);
         importBufferSize = 0;
         DataImport = -1;
         free(importBufferShortened);
         break;
      }
      if(buffer[i] == ':'){
         char *importBufferShortened = malloc(importBufferSize+1);
         SDL_memcpy(importBufferShortened,importBuffer,importBufferSize+1);
         importBufferShortened[importBufferSize] = '\0';
   
         importBufferSize = 0;
         if(importBufferShortened[0] == 'p'){
            // player
            DataImport = 1;
         }
         else if(importBufferShortened[0] == 'm'){
            // map data
            DataImport = 2;
         }
         else{
            // platforms
            DataImport = 0;
         }
         if(DataImport == 0){
            ID = atof(importBufferShortened);
         }
         else{ID = -1;}
         free(importBufferShortened);
         continue;
      }
      if(buffer[i] == ','){
         char* importBufferShortened = malloc(importBufferSize+1);
         SDL_memcpy(importBufferShortened,importBuffer,importBufferSize);
         importBufferShortened[importBufferSize] = '\0';

         FSetValue(importBufferShortened,importBufferSize,IndexData,ID,DataImport);
         importBufferSize = 0;
         free(importBufferShortened);
         IndexData += 1;
         continue;
         
      }
      /// fill importBuffer ----------
      importBuffer[importBufferSize] = buffer[i];
      importBufferSize++;
      //------------------------------
     
     }
   }
   if(mapData.PBTimer>0){
    mapData.ghostInGame = true; 
   }
   fclose(fileMap);

}
bool FCompareStrings(char* a,char* b){
  for(int i = 0;i<255;i++){
   if(a[i] == '\0' && b[i] == '\0'){
      return true;
   }
   if(a[i] != b[i]){
      return false;
   }
  }

}
char* FGetDataMap(char* path,char* type,int dataType,int fileNameSize){
   FILE *fileMap = fopen(path,"r");
   char buffer[256];
   char tempBuffer[256];
   int tempBufferSize = 0;
   char *exportBuffer = malloc(256);
   bool typeFound = false;
   bool finished = false;
   int exportBufferSize = 0;
   while(fgets(buffer,256,fileMap) && !finished){   
    int count = 0;
    for(int i = 0;i<256;i++){
      if(typeFound && count == dataType && buffer[i] != ','){
         exportBuffer[exportBufferSize] = buffer[i];
         exportBufferSize++;
      }
      if(buffer[i] == ';'){
         if(typeFound){
            finished = true;
            exportBuffer[exportBufferSize] = '\0';
         }
         tempBufferSize = 0;
         break;
      }
      else if(buffer[i] == ':'){
         if (!FCompareStrings(tempBuffer,type)){tempBufferSize = 0;break;}  
         else{typeFound = true;}     
      }
      else if(buffer[i] == ','){
       count++;
      }
      tempBuffer[tempBufferSize] = buffer[i];
      tempBufferSize++;
      tempBuffer[tempBufferSize] = '\0';
    }
   }
   fclose(fileMap);
   if(!typeFound){return NULL;}
   return exportBuffer;
}
char* msToTimer(int ms){
   char *timer = malloc(9);
   // milliSeconds
   int mSeconds1 = (ms/10) % 10;
   timer[7] = (char)(mSeconds1+48);
   int mSeconds2 = (ms/100) % 10;
   timer[6] = (char)(mSeconds2+48);
   timer[5] = ':';
   // Seconds
   int Seconds1 = (ms/1000) % 10;
   timer[4] = (char)(Seconds1+48);
   int Seconds2 = (ms/10000) % 6;
   timer[3] = (char)(Seconds2+48);
   timer[2] = ':';
   // Minutes
   int Minutes1 = (ms/60000) % 10;
   timer[1] = (char)(Minutes1+48);
   int Minutes2 = (ms/600000) % 10;
   timer[0] = (char)(Minutes2+48);
   timer[8] = '\0';
   return timer;
}
void FAppInit_Values(){
   // app.status values
   // 0 => in game
   // 1 => in editor
   // 2 => in level select
   // 3 => in settings
   // 4 => in Menu
   app.fetchedList = false;
   app.status = 4;
   app.backgroundMoving = 0; 
   app.transition = false;
   app.transitionInt = 0;
   
   FswitchAppStatus(0,4);

   level.timer = 0;
   level.tempFileMade = false;
   level.keyInputsSize = 0;
   level.Finished = false;
   level.Started = false;
   
   camera.x = 0;
   camera.y = 0;
   camera.scale = 1.2;
   camera.randValue = 0;
   camera.freeCam = true;
   player.veloX = 0;
   player.veloY = 0;
   player.accX = 0;
   player.accY = 0;
   player.jumpVelo = 0;
   player.onPlatform = false;
   player.playerControl = 1;
   Ghostplayer.playerControl = 1;
   
   key.up = false;
   key.down = false;
   key.left = false;
   key.right = false;
   key.shift = false;
   key.r = false;
   key.escapeRelease = true;
   key.escape = false;
   mapData.ghostEnd = false;
   mapData.ghostInGame = false;
  
   ghostKey.up = false;
   ghostKey.down = false;
   ghostKey.left = false;
   ghostKey.right = false;
   ghostKey.shift = false;
}


int main(int argc,char *argv[]){
  
   if (initVideo() == 0){
      FAppInit_Values();
      FWindow_Loop();
   }
   remove("levels/temp.txt");
   return 0;
}