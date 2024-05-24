#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <stdlib.h>
// Variables
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
int windowWidth = 800;
int windowHeight = 500;
float deltaTime = 0;
int WINDOW_TICKS = 0;
bool WINDOW_LOOP = false;
#define GRAVITY 500


SDL_Surface* Asset_Surface = NULL;
SDL_Texture* Asset_Texture = NULL;
// players 

struct Players {
    float x;
    float y;
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
} player;

struct Platform{
   bool reserved;
   float x1;
   float y1;
   float x2;
   float y2;
   float x3;
   float y3;
   float x4;
   float y4;
};
struct KeyboardBind{
   bool up;
   bool down;
   bool left;
   bool right;
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
  // IMG_Init(IMG_INIT_PNG);

   //Asset_Surface = IMG_Load("assets.png");
   //Asset_Texture = SDL_CreateTextureFromSurface(renderer,Asset_Surface);

   SDL_FreeSurface(Asset_Surface);


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
     } 
   }
   
}
int FLineIntersect(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4){
   float uA = ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1)); 
   float uB = ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));

   if (uA > 0 && uA < 1 && uB > 0 && uB < 1){return 1;}
   else {return 0;}
}

int FLineIntersect_returnX(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4){
   float uA = ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1)); 
   float uB = ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
   if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1){
      return (x1*(1-uA) + x2*uA);
   }
   else {return -999;}
}

bool FCheck_Collision(int platformID,int pos){
   float heightDiff = (player.height/2)*(pos == 2 || pos == 1) + player.height*(pos == 3);
   float widthDiff = player.width/2*(pos == 0 || pos == 3) + (player.width)*(pos == 1);


   float x1 = player.x+widthDiff;
   float y1 = player.y+heightDiff;
   float x2 = 0;
   float y2 = player.y+heightDiff;
   int count = 0;
   int count2 = 0;
   count = FLineIntersect(x1,y1,x2,y2,platforms[platformID].x1,platforms[platformID].y1,platforms[platformID].x2,platforms[platformID].y2) + FLineIntersect(x1,y1,x2,y2,platforms[platformID].x2,platforms[platformID].y2,platforms[platformID].x3,platforms[platformID].y3) + FLineIntersect(x1,y1,x2,y2,platforms[platformID].x3,platforms[platformID].y3,platforms[platformID].x4,platforms[platformID].y4) + FLineIntersect(x1,y1,x2,y2,platforms[platformID].x4,platforms[platformID].y4,platforms[platformID].x1,platforms[platformID].y1);
   x2 = windowWidth;
   count2 = FLineIntersect(x1,y1,x2,y2,platforms[platformID].x1,platforms[platformID].y1,platforms[platformID].x2,platforms[platformID].y2) + FLineIntersect(x1,y1,x2,y2,platforms[platformID].x2,platforms[platformID].y2,platforms[platformID].x3,platforms[platformID].y3) + FLineIntersect(x1,y1,x2,y2,platforms[platformID].x3,platforms[platformID].y3,platforms[platformID].x4,platforms[platformID].y4) + FLineIntersect(x1,y1,x2,y2,platforms[platformID].x4,platforms[platformID].y4,platforms[platformID].x1,platforms[platformID].y1);
   if (count % 2 != 0 && count2 % 2 != 0){
      return true;
   }
   else{return false;}
}
void fillQuad(SDL_Point points[5]){
    // points[0] == points[4]

   float minPointX = min(min(min(points[0].x,points[1].x),points[2].x),points[3].x);
   float minPointY = min(min(min(points[0].y,points[1].y),points[2].y),points[3].y);
   float maxPointX = max(max(max(points[0].x,points[1].x),points[2].x),points[3].x);
   float maxPointY = max(max(max(points[0].y,points[1].y),points[2].y),points[3].y);


   for(int i = (int)minPointY;i<(int)maxPointY;i++){
      
      float minPoint = (float)windowWidth;
      float maxPoint = 0;

      for(int j = 0;j<5;j++){
      float minValue = FLineIntersect_returnX(minPointX,(float)i,maxPointX,(float)i,(float)points[j].x,(float)points[j].y,(float)points[(j+1)%4].x,(float)points[(j+1)%4].y);
         if(minPoint > minValue && (int)minValue != -999){
           minPoint = minValue;  
         }
      }

      for(int j = 0;j<5;j++){
         float maxValue = FLineIntersect_returnX(minPointX,(float)i,maxPointX,(float)i,(float)points[j].x,(float)points[j].y,(float)points[(j+1)%4].x,(float)points[(j+1)%4].y);
         if(maxPoint < maxValue && (int)maxValue != -999){
           maxPoint = maxValue;
         }
      }
      SDL_RenderDrawLine(renderer,minPoint,i,maxPoint,i);
   }
}
void FDraw_Video(){
   SDL_SetRenderDrawColor(renderer,100,100,100,255);
   SDL_RenderClear(renderer);

   SDL_RendererFlip flip = SDL_FLIP_NONE;
   if(player.direction < 0){
      flip = SDL_FLIP_HORIZONTAL;
   } 
   //SDL_RenderCopyEx(renderer,Asset_Texture,&(SDL_Rect){6+18*((int)player.animationIndex % 16),7,15,18},&(SDL_Rect){player.x,player.y,player.width,player.height},0,NULL,flip);
   SDL_SetRenderDrawColor(renderer,50,50,50,255);
   SDL_RenderFillRect(renderer,&(SDL_Rect){player.x,player.y,player.width,player.height});
   SDL_SetRenderDrawColor(renderer,120,120,120,255);
   SDL_RenderDrawRect(renderer,&(SDL_Rect){player.x,player.y,player.width,player.height});
   for (int i = 0;i<sizeof(platforms)/sizeof(platforms[0]);i++){
      if(platforms[i].reserved){
         SDL_SetRenderDrawColor(renderer,200,200,200,255);
         SDL_Point points[5];
         points[0].x = platforms[i].x1;
         points[0].y = platforms[i].y1;
         points[1].x = platforms[i].x2;
         points[1].y = platforms[i].y2;
         points[2].x = platforms[i].x3;
         points[2].y = platforms[i].y3;
         points[3].x = platforms[i].x4;
         points[3].y = platforms[i].y4;
         points[4].x = platforms[i].x1;
         points[4].y = platforms[i].y1;
         fillQuad(points);
          SDL_SetRenderDrawColor(renderer,0,0,0,255);
         SDL_RenderDrawLines(renderer,points,5);
      }
   }
   
   SDL_RenderPresent(renderer);
}
void FPlayer_Movement(){
   if (key.up && player.onPlatform){
      player.jumpVelo = -150;
   }
   if (key.left){
      player.accX = -500;
      player.animationIndex += 10*deltaTime;
      player.direction = -1;
   }
   else if (key.right){
      player.accX = 500;
      player.animationIndex += 10*deltaTime;
      player.direction = 1;
   }
   else {player.accX = 0;}
   player.veloX += player.accX*deltaTime;
   player.veloY += (player.accY + GRAVITY)*deltaTime;
   player.veloX *= pow(0.05,deltaTime);
   if (fabs(player.veloX) >= 200){
      player.veloX = 200*(1-2*(player.veloX < 0));
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
   }
}
float returnDistance(float x1,float y1,float x2,float y2){
   return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}
void FCollision_Response(int platformID,int pos){
   float heightDiff = (player.height/2)*(pos == 2 || pos == 1) + player.height*(pos == 3);
   float widthDiff = player.width/2*(pos == 0 || pos == 3) + (player.width)*(pos == 1);


   float playerx = player.x + widthDiff;
   float playery = player.y + heightDiff;
   float length1 = returnDistance(platforms[platformID].x1,platforms[platformID].y1,platforms[platformID].x2,platforms[platformID].y2);
   float length2 = returnDistance(platforms[platformID].x2,platforms[platformID].y2,platforms[platformID].x3,platforms[platformID].y3);
   float length3 = returnDistance(platforms[platformID].x3,platforms[platformID].y3,platforms[platformID].x4,platforms[platformID].y4);
   float length4 = returnDistance(platforms[platformID].x4,platforms[platformID].y4,platforms[platformID].x1,platforms[platformID].y1);
   
   float scale1 = ((playerx-platforms[platformID].x1)*(platforms[platformID].x2-platforms[platformID].x1) + (playery-platforms[platformID].y1)*(platforms[platformID].y2-platforms[platformID].y1))/length1;
   float scale2 = ((playerx-platforms[platformID].x2)*(platforms[platformID].x3-platforms[platformID].x2) + (playery-platforms[platformID].y2)*(platforms[platformID].y3-platforms[platformID].y2))/length2;
   float scale3 = ((playerx-platforms[platformID].x3)*(platforms[platformID].x4-platforms[platformID].x3) + (playery-platforms[platformID].y3)*(platforms[platformID].y4-platforms[platformID].y3))/length3;
   float scale4 = ((playerx-platforms[platformID].x4)*(platforms[platformID].x1-platforms[platformID].x4) + (playery-platforms[platformID].y4)*(platforms[platformID].y1-platforms[platformID].y4))/length4;

   

   float coord1x = platforms[platformID].x1*(1-(scale1/length1)) + platforms[platformID].x2*(scale1/length1);
   float coord1y = platforms[platformID].y1*(1-(scale1/length1)) + platforms[platformID].y2*(scale1/length1);
   float coord2x = platforms[platformID].x2*(1-(scale2/length2)) + platforms[platformID].x3*(scale2/length2);
   float coord2y = platforms[platformID].y2*(1-(scale2/length2)) + platforms[platformID].y3*(scale2/length2);
   float coord3x = platforms[platformID].x3*(1-(scale3/length3)) + platforms[platformID].x4*(scale3/length3);
   float coord3y = platforms[platformID].y3*(1-(scale3/length3)) + platforms[platformID].y4*(scale3/length3);
   float coord4x = platforms[platformID].x4*(1-(scale4/length4)) + platforms[platformID].x1*(scale4/length4);
   float coord4y = platforms[platformID].y4*(1-(scale4/length4)) + platforms[platformID].y1*(scale4/length4);

   float projectedCoords[4][7] = {{coord1x,coord1y,returnDistance(coord1x,coord1y,playerx,playery),platforms[platformID].x1,platforms[platformID].y1,platforms[platformID].x2,platforms[platformID].y2},
                                   {coord2x,coord2y,returnDistance(coord2x,coord2y,playerx,playery),platforms[platformID].x2,platforms[platformID].y2,platforms[platformID].x3,platforms[platformID].y3},
                                  {coord3x,coord3y,returnDistance(coord3x,coord3y,playerx,playery),platforms[platformID].x3,platforms[platformID].y3,platforms[platformID].x4,platforms[platformID].y4},
                                  {coord4x,coord4y,returnDistance(coord4x,coord4y,playerx,playery),platforms[platformID].x4,platforms[platformID].y4,platforms[platformID].x1,platforms[platformID].y1}};
   

   int minIndex = 0;
   for (int i = 1;i<sizeof(projectedCoords)/sizeof(projectedCoords[0]);i++){
     if(projectedCoords[minIndex][2] > projectedCoords[i][2]){
      minIndex = i;
     }
   }
   player.x = projectedCoords[minIndex][0] - widthDiff;
   player.y = projectedCoords[minIndex][1] - heightDiff;

   if((int)(projectedCoords[minIndex][3] - projectedCoords[minIndex][5]) != 0){     
      player.veloY = 0;
      player.jumpVelo = 0;
      if(pos != 0){
        player.onPlatform = true;
      }
   }
   else{
      player.veloX = 0;
      if(playerx > projectedCoords[minIndex][3]){
         player.onWall = -1;
      }
      else{player.onWall = 1;}
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
      ///// I FUCKING HATE HOW THIS IS DESIGNED BY THE WAY FOR ANY READING THIS !!!!!!!!!!!!
         // lower point
        if (FCheck_Collision(i,0)){
         FCollision_Response(i,0);
        }
        // upper point
        if (FCheck_Collision(i,1)){
         FCollision_Response(i,1);
        }
        // mid point
        if (FCheck_Collision(i,2)){
         FCollision_Response(i,2);
        }

        if (FCheck_Collision(i,3)){
         FCollision_Response(i,3);
        }
      }
   }
   //printf("%f\n",1/deltaTime);
}
void FWindow_Loop(){
   while(WINDOW_LOOP){
    FInput_Listener();
    FUpdate_Data();
    FDraw_Video();
   }
}

void FInit_Values(){
   player.x = 50;
   player.y = 50;
   player.width = 18;
   player.height = 20;
   player.veloX = 0;
   player.veloY = 0;
   player.accX = 0;
   player.accY = 0;
   player.jumpVelo = 0;
   player.onPlatform = false;
   
   platforms[0].reserved = true;
   platforms[0].x1 = 50;
   platforms[0].y1 = 480;
   platforms[0].x2 = 500;
   platforms[0].y2 = 480;
   platforms[0].x3 = 500;
   platforms[0].y3 = 490;
   platforms[0].x4 = 50;
   platforms[0].y4 = 490;


  platforms[1].reserved = true;
  platforms[1].x1 = 50;
  platforms[1].y1 = 470;
  platforms[1].x2 = 100;
  platforms[1].y2 = 470;
  platforms[1].x3 = 120;
  platforms[1].y3 = 482;
  platforms[1].x4 = 50;
  platforms[1].y4 = 482;


  platforms[2].reserved = true;
  platforms[2].x1 = 200;
  platforms[2].y1 = 475;
  platforms[2].x2 = 250;
  platforms[2].y2 = 460;
  platforms[2].x3 = 250;
  platforms[2].y3 = 482;
  platforms[2].x4 = 190;
  platforms[2].y4 = 482;

  platforms[3].reserved = true;
  platforms[3].x1 = 275;
  platforms[3].y1 = 450;
  platforms[3].x2 = 300;
  platforms[3].y2 = 445;
  platforms[3].x3 = 350;
  platforms[3].y3 = 465;
  platforms[3].x4 = 260;
  platforms[3].y4 = 480;

  platforms[4].reserved = true;
  platforms[4].x1 = 260;
  platforms[4].y1 = 439;
  platforms[4].x2 = 300;
  platforms[4].y2 = 439;
  platforms[4].x3 = 300;
  platforms[4].y3 = 445;
  platforms[4].x4 = 260;
  platforms[4].y4 = 445;

  platforms[5].reserved = true;
  platforms[5].x1 = 350;
  platforms[5].y1 = 410;
  platforms[5].x2 = 360;
  platforms[5].y2 = 415;
  platforms[5].x3 = 360;
  platforms[5].y3 = 460;
  platforms[5].x4 = 350;
  platforms[5].y4 = 455;
   
  
   key.up = false;
   key.down = false;
   key.left = false;
   key.right = false;
}


int main(int argc,char *argv[]){
  
   if (initVideo() == 0){
      FInit_Values();
      FWindow_Loop();
   }
   return 0;
}