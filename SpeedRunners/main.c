#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <sdl2_renderparty.h>
#include <stdlib.h>
// Variables
#define PI 3.14159 
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
int windowWidth = 800;
int windowHeight = 500;
float deltaTime = 0;
int WINDOW_TICKS = 0;
bool WINDOW_LOOP = false;
#define GRAVITY 500


SDL_Surface* surface_tile = NULL;
SDL_Texture* tex_tile = NULL;

SDL_Surface* surface_tile2 = NULL;
SDL_Texture* tex_tile2 = NULL;

SDL_Surface* surface_tile3 = NULL;
SDL_Texture* tex_tile3 = NULL;

SDL_Surface* surface_player = NULL;
SDL_Texture* tex_player = NULL;

SDL_Surface* surface_font = NULL;
SDL_Texture* tex_font = NULL;

SDL_Surface* surface_background = NULL;
SDL_Texture* tex_background = NULL;
float cameraBackground = 0;
// players 
struct Camera{
   float x;
   float y;
} camera;

struct WorldBorder{
   // for clarity these values that the camera will not follow if the player goes beyond them.
   float xMin;
   float yMin;
   float xMax;
   float yMax;
} worldBorder;
struct Players {
    float x;
    float y;
    float Owidth;
    float width;
    float height;
    float veloX;
    float veloY;
    float jumpVelo;
    float accX;
    float accY;
    bool onPlatform;
    int onWall;
    int direction;
    float animationIndex;
    float idleIndex;
    float playerControl;

} player;

struct Platform{
   bool reserved;
   float x;
   float y;
   float slope;
   float width;
   float height;
   bool slopeInv;
   float textureScale;
   SDL_Texture* texture;
   bool textureStretch;
};
struct KeyboardBind{
   bool up;
   bool down;
   bool left;
   bool right;
   bool shift;
} key;


struct Platform platforms[10];

float min(float a, float b){
   return a < b ? a : b;
}
float max(float a, float b){
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
   surface_tile3 = IMG_Load("assets/tile5.png");
   surface_player = IMG_Load("assets/player.png");
   surface_background = IMG_Load("assets/background.png");
   surface_font = IMG_Load("assets/font_atlas.png");

   tex_tile = SDL_CreateTextureFromSurface(renderer,surface_tile);
   tex_tile2 = SDL_CreateTextureFromSurface(renderer,surface_tile2);
   tex_tile3 = SDL_CreateTextureFromSurface(renderer,surface_tile3);
   tex_player = SDL_CreateTextureFromSurface(renderer,surface_player);
   tex_background = SDL_CreateTextureFromSurface(renderer,surface_background);
   tex_font = SDL_CreateTextureFromSurface(renderer,surface_font);

   SDL_FreeSurface(surface_tile);
   SDL_FreeSurface(surface_tile2);
   SDL_FreeSurface(surface_tile3);
   SDL_FreeSurface(surface_player);
   SDL_FreeSurface(surface_background);


   WINDOW_LOOP = true;
   return 0;
}


void FInput_Listener(){
   SDL_Event event;
   SDL_PollEvent(&event);

   if (event.type == SDL_QUIT){
      WINDOW_LOOP = false;
   }
   if (event.type == SDL_KEYDOWN){
      switch(event.key.keysym.sym){
         case SDLK_UP:
          key.up = true;
          break;
         case SDLK_DOWN:
          key.down = true;
          break;
         case SDLK_LEFT:
          key.left = true;
          break;
         case SDLK_RIGHT:
          key.right = true;
          break;
         case SDLK_LSHIFT:
          key.shift = true;
          break;
     } 
   }
   if (event.type == SDL_KEYUP){
      switch(event.key.keysym.sym){
         case SDLK_UP:
          key.up = false;
          break;
         case SDLK_DOWN:
          key.down = false;
          break;
         case SDLK_LEFT:
          key.left = false;
          break;
         case SDLK_RIGHT:
          key.right = false;
          break;
         case SDLK_LSHIFT:
          key.shift = false;
          break;
     } 
   }
   
}
int FLineIntersect(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4){
   float uA = ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1)); 
   float uB = ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));

   if (uA > 0 && uA < 1 && uB > 0 && uB < 1){return 1;}
   else {return 0;}
}

int FCheck_Collision(int platformID){
   float distanceRatio = (player.x + player.width/2 - platforms[platformID].x)/(platforms[platformID].width);
   if(platforms[platformID].slopeInv){
      distanceRatio = distanceRatio = 1 - (player.x + player.width/2 - platforms[platformID].x)/(platforms[platformID].width);
   } 
   return (player.x+player.width > platforms[platformID].x && platforms[platformID].x+platforms[platformID].width > player.x && player.y+player.height > platforms[platformID].y-(platforms[platformID].height*sin(platforms[platformID].slope))*distanceRatio && platforms[platformID].y+platforms[platformID].height > player.y);
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
     

   for(int i = platforms[platformID].x;i<platforms[platformID].x + platforms[platformID].width;i += platforms[platformID].textureScale){ 
      int j = platforms[platformID].y+platforms[platformID].height-platforms[platformID].textureScale;
      while(true){
       float distanceRatio1 = (i - platforms[platformID].x)/(platforms[platformID].width);
       float distanceRatio2 = (i + platforms[platformID].textureScale - platforms[platformID].x)/(platforms[platformID].width);
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
       
       float xTexture =  (points2[1].x-i)/platforms[platformID].textureScale;
       float yTexture0 = SDL_abs((points2[1].y - points2[3].y))/platforms[platformID].textureScale;
       float yTexture1 = SDL_abs((points2[1].y - points2[2].y))/platforms[platformID].textureScale;
       //printf("%f\n",yTexture1);
       if(platforms[platformID].textureStretch){
         yTexture0 = 1;
         yTexture1 = 1;
       }
       SDL_Vertex vertex_1 = {{points2[0].x, points2[0].y}, {255, 255, 255, 255}, {0, 0}};
       SDL_Vertex vertex_2 = {{points2[1].x, points2[1].y}, {255, 255, 255, 255}, {xTexture, 0}};
       SDL_Vertex vertex_3 = {{points2[2].x, points2[2].y}, {255, 255, 255, 255}, {xTexture, yTexture1}};
       SDL_Vertex vertex_4 = {{points2[3].x, points2[3].y}, {255, 255, 255, 255}, {0, yTexture0}}; 

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
  //int stringCount = (sizeof(Text)/sizeof(char);
  printf("%d\n",stringCount);
  char str[stringCount];
  for(int i = 0;i<stringCount;i++){
    str[i] = *(Text+i);
  }
  int posX;
  int cap;
  int num;
  SDL_SetTextureAlphaMod(tex_font,opacity); 
  // OUTLINE --> TEXT (order of rendering) 
   // {outline}
  for(int i = 0;i<stringCount;i++){
      cap = 0;
      num = 0;
      int charValue = str[i] - 'a';
      if (str[i]>=65 && str[i]<=90){
        cap = 1;
        num = 0;
        charValue += 32;
      }
      else if (str[i]>= 48 && str[i]<= 57){
        num = 1;
        cap = 0;
        charValue += 49;
      }
      posX = charValue*40;
      SDL_Rect srcRect = {
      posX,
      80*cap+150*num,
      40,
      70-(6*cap)
    };
    int deviation = SDL_floor((width/(stringCount*5))+1);
     SDL_Rect OUTLINEdstRect = {
      x+i*(width/stringCount)-deviation,
      y-deviation,
      width/stringCount+deviation,
      height+deviation
    };
    SDL_SetTextureColorMod( tex_font, 0,0,0);
    SDL_RenderCopy(renderer,tex_font,&srcRect,&OUTLINEdstRect);
    }
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
      else if (str[i]>= 48 && str[i]<= 57){
        num = 1;
        cap = 0;
        charValue += 49;
      }
      posX = charValue*40;
    
    SDL_Rect srcRect = {
      posX,
      80*cap+150*num,
      40,
      70-(6*cap)
    };
    SDL_Rect dstRect = {
      x+i*(width/stringCount)
      ,y
      ,width/stringCount
      ,height
    };
    
    
    SDL_SetTextureColorMod( tex_font, color[0],color[1],color[2]);
    SDL_RenderCopy(renderer,tex_font,&srcRect,&dstRect);
    }  
    SDL_SetTextureAlphaMod(tex_font,255);
}



void FDraw_Video(){
   
   camera.x = -windowWidth/2+player.x+player.width/2;
   camera.y = -windowHeight/2+player.y+player.height/2; 
   
   if (player.x > worldBorder.xMax - windowWidth/2){
       camera.x = worldBorder.xMax - windowWidth + player.width/2;
   }
   if (player.x < worldBorder.xMin + windowWidth/2){
       camera.x = worldBorder.xMin + player.width/2;    
   }

   if (player.y > worldBorder.yMax - windowHeight/2){
       camera.y = worldBorder.yMax - windowHeight + player.height/2;
   }
   if (player.y < worldBorder.yMin + windowHeight/2){
       camera.y = worldBorder.yMin + player.height/2;    
   }
   cameraBackground += 5*deltaTime;
   if(cameraBackground >= 576){
      cameraBackground = 0;
   }
   SDL_RenderClear(renderer);
   SDL_RenderCopy(renderer,tex_background,&(SDL_Rect){cameraBackground,0,576,324},&(SDL_Rect){0,0,windowWidth-cameraBackground*windowWidth/576,windowHeight});
   SDL_RenderCopy(renderer,tex_background,&(SDL_Rect){0,0,cameraBackground,324},&(SDL_Rect){windowWidth-cameraBackground*windowWidth/576,0,cameraBackground*windowWidth/576,windowHeight});
   SDL_SetRenderDrawColor(renderer,50,50,50,255);
   renderText(sizeof("hello world"),"hello world",0,20,sizeof("hello world")*12,20,255,(int[3]){255,255,255});
   // Draw player
   player.x -= camera.x;
   player.y -= camera.y;
   SDL_RendererFlip flip = SDL_FLIP_NONE;
   if(player.direction < 0){
      flip = SDL_FLIP_HORIZONTAL;
   }
   if((int)player.accX != 0 && (int)player.jumpVelo == 0){
   if(SDL_abs(player.veloX)>=200){
      player.width = player.Owidth + 3;
      SDL_RenderCopyEx(renderer,tex_player,&(SDL_Rect){1+((int)(player.animationIndex) % 6 )*24,47,18,16},&(SDL_Rect){player.x,player.y,player.width,player.height},0,NULL,flip);
   }
   else{
      player.width = player.Owidth;
   SDL_RenderCopyEx(renderer,tex_player,&(SDL_Rect){2+((int)(player.animationIndex) % 6 )*24,2,15,18},&(SDL_Rect){player.x,player.y,player.width,player.height},0,NULL,flip);
   }
   }
   else if ((int)player.jumpVelo == 0){
      player.width = player.Owidth;
     SDL_RenderCopyEx(renderer,tex_player,&(SDL_Rect){2+((int)(player.idleIndex) % 2 )*24,24,15,18},&(SDL_Rect){player.x,player.y,player.width,player.height},0,NULL,flip);
   }
   else{
      player.width = player.Owidth;
      SDL_RenderCopyEx(renderer,tex_player,&(SDL_Rect){49,24,15,18},&(SDL_Rect){player.x,player.y,player.width,player.height},0,NULL,flip);
   }
   ///////

   // Draw platforms
   SDL_SetRenderDrawColor(renderer,120,120,120,255);
   for (int i = 0;i<sizeof(platforms)/sizeof(platforms[0]);i++){
      if(platforms[i].reserved){
         platforms[i].x -= camera.x;
         platforms[i].y -= camera.y;
         SDL_SetRenderDrawColor(renderer,200,200,200,255);
         FtexturePlatform(i);

         platforms[i].x += camera.x;
         platforms[i].y += camera.y;

      }
   }
   player.x += camera.x;
   player.y += camera.y;
   SDL_RenderPresent(renderer);
}
void FPlayer_Movement(){
   if(player.playerControl < 1){
      player.playerControl += 1*deltaTime;
      if(player.playerControl>=1){
         player.playerControl = 1;
      }
   }
   player.idleIndex += 2*deltaTime;
   if (player.idleIndex >= 20){
      player.idleIndex = 0;
   }
   if (key.up && player.onPlatform){
      player.jumpVelo = -150;
   }
   if (key.left){
      player.accX = (-500-200*(key.shift))*player.playerControl;
      player.animationIndex += 10*deltaTime;
      player.direction = -1;
   }
   else if (key.right){
      player.accX = (500+200*(key.shift))*player.playerControl;
      player.animationIndex += 10*deltaTime;
      player.direction = 1;
   }
   else {player.accX = 0;}
   player.veloX += player.accX*deltaTime;
   player.veloY += (player.accY + GRAVITY)*deltaTime;
   player.veloX *= pow(0.05,deltaTime);
   if (fabs(player.veloX) >= 150+500*(key.shift)){
      player.veloX = (150+500*(key.shift))*(1-2*(player.veloX < 0));
   }

   player.x += player.veloX*deltaTime;
   player.y += (player.veloY + player.jumpVelo)*deltaTime;

   if (key.up){
      player.jumpVelo -= 100*deltaTime;
   }
   if (player.y+player.height >= windowHeight){
      player.y = windowHeight-player.height;
      player.accY = -GRAVITY;
      player.veloY = 0;
      player.jumpVelo = -500;
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
}
float returnDistance(float x1,float y1,float x2,float y2){
   return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}
void FCollision_Response(int platformID){
   float distanceRatio = (player.x - platforms[platformID].x + player.width/2)/(platforms[platformID].width);
   if(platforms[platformID].slopeInv){
      distanceRatio = 1 - (player.x + player.width/2 - platforms[platformID].x)/(platforms[platformID].width);
   } 

   if (SDL_min(SDL_abs(player.x+player.width-platforms[platformID].x)+5,SDL_abs(player.x-platforms[platformID].x-platforms[platformID].width)+5)>SDL_min(SDL_abs(player.y+player.height-platforms[platformID].y+platforms[platformID].height*sin(platforms[platformID].slope)*distanceRatio),SDL_abs(player.y-platforms[platformID].y-platforms[platformID].height)))   
    {
      if (SDL_abs(player.y + player.height - platforms[platformID].y +platforms[platformID].height*sin(platforms[platformID].slope)*distanceRatio)>SDL_abs(player.y - platforms[platformID].y - platforms[platformID].height)){
        player.y = platforms[platformID].y + platforms[platformID].height;
        player.jumpVelo = 0;
        player.veloY = 0;
       }
       else {  
           
         player.y = platforms[platformID].y - player.height - platforms[platformID].height*sin(platforms[platformID].slope)*distanceRatio;
             player.onPlatform = true;
             player.veloY = 0;
             player.jumpVelo = 0;
             
        }
    }
    else {
      player.veloX *= pow(0.9,deltaTime);
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

void FUpdate_Data(){
   deltaTime = ((float)(SDL_GetTicks()-WINDOW_TICKS))/1000;
   WINDOW_TICKS = SDL_GetTicks();
   FPlayer_Movement();
   
   player.onPlatform = false;
   player.onWall = false;
   for (int i = 0;i<sizeof(platforms)/sizeof(platforms[0]);i++){
      if (platforms[i].reserved){
      if(FCheck_Collision(i)){
         FCollision_Response(i);
      }
      }
   }
   platforms[1].slope += 1*deltaTime;
   platforms[3].slope += 1*deltaTime;
   platforms[2].slope += 1*deltaTime;
 
}
void FWindow_Loop(){
   while(WINDOW_LOOP){
    FInput_Listener();
    FUpdate_Data();
    FDraw_Video();
   }
}

void FInit_Values(){
   camera.x = 0;
   camera.y = 0;
   worldBorder.xMin = 0;
   worldBorder.yMin = 0;
   worldBorder.xMax = 1000;
   worldBorder.yMax = 600;
   player.x = 50;
   player.y = 50;
   player.Owidth = 18;
   player.width = 18;
   player.height = 20;
   player.veloX = 0;
   player.veloY = 0;
   player.accX = 0;
   player.accY = 0;
   player.jumpVelo = 0;
   player.onPlatform = false;
   player.playerControl = 1;
   
   platforms[0].reserved = true;
   platforms[0].x = 50;
   platforms[0].y = 480;
   platforms[0].width = 500;
   platforms[0].height = 100;
   platforms[0].slope = 0;
   platforms[0].slopeInv = false;
   platforms[0].textureScale = 50;
   platforms[0].texture = tex_tile;
   platforms[0].textureStretch = false;

   platforms[1].reserved = true;
   platforms[1].x = 100;
   platforms[1].y = 460;
   platforms[1].width = 100;
   platforms[1].height = 50;
   platforms[1].slope = 0;
   platforms[1].slopeInv = false;
   platforms[1].textureScale = 20;
   platforms[1].texture = tex_tile3;
   platforms[1].textureStretch = true;

   platforms[3].reserved = true;
   platforms[3].x = 300;
   platforms[3].y = 470 ;
   platforms[3].width = 50;
   platforms[3].height = 10;
   platforms[3].slope = 0;
   platforms[3].slopeInv = true;
   platforms[3].textureScale = 20;
   platforms[3].texture = tex_tile3;
   platforms[3].textureStretch = true;

   platforms[2].reserved = true;
   platforms[2].x = 500;
   platforms[2].y = 440;
   platforms[2].width = 50;
   platforms[2].height = 10;
   platforms[2].slope = 0;
   platforms[2].slopeInv = true;
   platforms[2].textureScale = 50;
   platforms[2].texture = tex_tile2;
   platforms[2].textureStretch = false;

  
   
  
   key.up = false;
   key.down = false;
   key.left = false;
   key.right = false;
   key.shift = false;
}


int main(int argc,char *argv[]){
  
   if (initVideo() == 0){
      FInit_Values();
      FWindow_Loop();
   }
   return 0;
}