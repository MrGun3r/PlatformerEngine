
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
#define GRAVITY 500
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
int windowWidth = 900;
int windowHeight = 600;
float windowWidthScale = 1;
float windowHeightScale = 1;
int gameWidth = 900;
int gameHeight = 600;

// Texture and surface tiles
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
SDL_Surface* surface_trigger = NULL;
SDL_Texture* tex_trigger = NULL;
SDL_Surface* surface_checkpoint = NULL;
SDL_Texture* tex_checkpoint = NULL;

// Variable Types

#include "structs.h"
#include "useFunctions.h"

// dTime
void FdeltaTime();

// This file includes all the necessary files needed to run the game !


// Map Data Read/Write
void FSetDataMap(char* path,int pathSize);
char* FGetDataMap(char* fileName,char* type,int dataType,int fileNameSize);
void FSetValue(char* importBuffer,int importBufferSize,int data,int ID,int dataType);

// Rendering 
void FtexturePlatform(int platformID);
void renderText(int stringCount,char *Text,int x ,int y, int width,int height,int opacity,int shadowOpacity,int color[3]);
void FGUIHover();
SDL_Texture* CreateRepeatedTexture(SDL_Renderer* renderer, SDL_Texture* originalTexture, int width, int height,double scale,double offsetX,double offsetY);
// GUI
void SetButton(bool reserved,int i,char* Text,double x,double y,int textFont,bool hoverable,int hoverWidth,int hoverHeight,bool highlight);
void SetButtonIcon(int i,SDL_Texture* texture,double u1,double u2,double v1,double v2);
void SetSlider(bool reserved,int i,char* Text,double x,double y,int textFont,bool hoverable,int hoverWidth,int hoverHeight,bool highlight,double sliderMin,double sliderMax,double sliderLength,double defaultValue);
void Update_Slider();
// Text
void FapplyText();

// Movement
void FapplyMovementGhost();
void FPlayer_Movement();


// App change state
void FswitchAppStatus(int from, int to);
void appendTransition(int from ,int to);
void FDrawTransition();

// Editor functions 
void FUpdate_Editor();
void FCheck_Select_Editor();
void FDraw_SideBar_Editor();
void FTransformState(); // transforms an object or a camera view
void FDrawObjects();
void FDraw_Editor();
void FSaveMap();
void addPlatform(int x,int y,double width,double height,double slope,bool slopeInv,int texture,int type,double scale,double offsetX,double offsetY);
void editorShowButtons();
void addTrigger(int x,int y,double width,double height,int Type);
void FInfoBox();

// In Game functions
void FcheckPB(); 
int FCheck_Collision(struct Players Player,int platformID);
void FCollision_Response(struct Players *Player,int platformID);
void FDraw_Game();
void FUpdate_Data();
void FaddReplay(bool checkpoint);
void FDisplayHUD();
void FGameRestart();

// Levels listing
void FlistLevels();

// Menu Functions 
void FDraw_Menu();
void FUpdate_Data_Menu();




// Initial Values for the App
void FAppInit_Values();

// Window function
void FwindowResize();
void FWindow_Loop();

// Include Headers and Logistics
#include "init.h"
#include "input_listener.h"
#include "renderGUI.h"
#include "textureQuad.h"
#include "mapdata.h"
#include "collision.h"
#include "menu.h"
#include "app_status.h"
#include "movement.h"
#include "game.h"
#include "recordReplay.h"
#include "editor.h"
#include "GUIElements.h"
#include "text.h"
