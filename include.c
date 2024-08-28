
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <SDL2/SDL_mixer.h>
// Variables

#define PI 3.14159 
#define GRAVITY 500
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;


float windowWidthScale = 1;
float windowHeightScale = 1;

double campaignXIsland;
double campaignYIsland;
double campaignWidthIsland;
double campaignHeightIsland;

/// Window size (Actual window size , Window Size will be resizable as desired)

int windowWidth = 800;
int windowHeight = 600;

/// Game Size (Meaning The size of the textures layers , Game size will have decrete values to chosen)
int gameWidth;
int gameHeight;



// Texture and surface tiles

SDL_Surface* surface_player = NULL;
SDL_Texture* tex_player = NULL;
SDL_Surface* surface_font = NULL;
SDL_Texture* tex_font = NULL;
SDL_Surface* surface_background = NULL;
SDL_Texture* tex_background = NULL;
SDL_Surface* surface_trigger = NULL;
SDL_Texture* tex_trigger = NULL;
SDL_Surface* surface_bulb = NULL;
SDL_Texture* tex_bulb = NULL;
SDL_Surface* surface_displacement = NULL;
SDL_Texture* tex_displacement = NULL;
SDL_Surface* surface_skull = NULL;
SDL_Texture* tex_skull = NULL;
SDL_Surface* surface_coin = NULL;
SDL_Texture* tex_coin = NULL;
SDL_Surface* surface_star = NULL;
SDL_Texture* tex_star = NULL;
SDL_Surface* surface_tools = NULL;
SDL_Texture* tex_tools = NULL;
SDL_Surface* surface_trophy = NULL;
SDL_Texture* tex_trophy = NULL;
SDL_Surface* surface_blank = NULL;
SDL_Texture* tex_blank = NULL;
SDL_Surface* surface_water = NULL;
SDL_Texture* tex_water = NULL;
SDL_Surface* surface_sand = NULL;
SDL_Texture* tex_sand = NULL;
SDL_Surface* surface_levelPad = NULL;
SDL_Texture* tex_levelPad = NULL;
SDL_Surface* surface_movenode = NULL;
SDL_Texture* tex_movenode = NULL;

// Game window Textures
SDL_Texture* backgroundLayer = NULL;
SDL_Texture* lightLayer = NULL; 
SDL_Texture* lightLayer2 = NULL; 
SDL_Texture* HUDLayer = NULL;
SDL_Texture* TransitionLayer = NULL;
SDL_Texture* resultLayer = NULL;    
SDL_Surface* surface_light = NULL;
SDL_Texture* tex_light = NULL;


/// Sounds

Mix_Chunk* Sound_Jump = NULL;
Mix_Chunk* Sound_JumpWall = NULL;
Mix_Chunk* Sound_Step1 = NULL;
Mix_Chunk* Sound_Step2 = NULL;
Mix_Chunk* Sound_Wall = NULL;
Mix_Chunk* Sound_Death = NULL;
Mix_Chunk* Sound_Checkpoint = NULL;
Mix_Chunk* Sound_Hover = NULL;
Mix_Chunk* Sound_buttonClick = NULL;
Mix_Chunk* Sound_transition = NULL;
Mix_Chunk* Sound_finish = NULL;
Mix_Chunk* Sound_levelSelect = NULL;

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

// Texture Init
void FLoadTextures();
void FLoadBackgrounds();
int FindTextureInt(char *textureName);
int FindBackgroundInt(char *backgroundName);

// Sound Init
void FLoadSounds();

// Rendering 
void FtexturePlatform(int platformID);
void FtextureQuad(double x,double y,double width,double height,SDL_Texture* texture,double opacity,int rotationAngle);
void renderText(int stringCount,char *Text,int x ,int y, int width,int height,int opacity,int shadowOpacity,int color[3]);
void FGUIHover();
SDL_Texture* CreateRepeatedTexture(SDL_Renderer* renderer, SDL_Texture* originalTexture, int n);
void DrawBackground();

// GUI
void SetButton(bool reserved,int i,char* Text,double x,double y,int textFont,bool hoverable,int hoverWidth,int hoverHeight,bool highlight);
void SetButtonIcon(int i,SDL_Texture* texture,double u1,double u2,double v1,double v2);
void SetSlider(bool reserved,int i,char* Text,double x,double y,int textFont,bool hoverable,int hoverWidth,int hoverHeight,bool highlight,double sliderMin,double sliderMax,double sliderLength,double defaultValue);
void SetTextBox(bool reserved,int i,char* textName,double x,double y,double font,double hoverLength);
void Update_Slider();
void Update_Knobs();
void Update_TextBox();
void SetKnobCoef(int i,double Coef);
void SetKnob(bool reserved,int i,char* Text,double x,double y,int textFont,bool hoverable,double knobMin,double knobMax,double defaultValue);
void ChangeSliderPosition(int i,double x,double y);
void ChangeButtonPosition(int i,double x,double y);
void ChangeKnobPosition(int i,double x,double y);

// Text
void FapplyText();

// Movement
void FapplyMovementGhost();
void FPlayer_Movement();

// Profile setup
void SetUsernameProfile();
bool CheckUsernameProfile();
void FSaveProfile();

// Campaign

void FDraw_Campaign();
void FUpdate_Campaign();
void findLevelCampaign();

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
void addMoveNode(int x, int y);
void addDisplacement(double x, double y, double width,double height,double type,double power,double powerType,double opacity);
void addPlatform(int x,int y,double width,double height,double slope,bool slopeInv,int texture,int type,double scale,double offsetX,double offsetY,bool stretch,bool collidable,double opacity,double animation,double red,double green,double blue);
void addParticle(double x,double y,double size,double red,double green,double blue,double angle);
void editorShowButtons();
void addTrigger(int x,int y,double width,double height,int Type,double opacity);
void addLight(double x,double y,double size,double red,double green,double blue,double visibility,double brightness);
void addDeathBox(double x, double y, double width,double height,double opacity);
void FInfoBox();

// In Game functions
void FcheckPB(); 
int FCheck_Collision(struct Players Player,int platformID);
void FCollision_Response(struct Players *Player,int platformID);
int rectCollision(SDL_Rect Rect1, SDL_Rect Rect2);
void FDraw_Game();
void FUpdate_Data();
void FaddReplay(bool checkpoint);
void FDisplayHUD();
void FGameRestart();

// Movement
void platformMovement(int i);
void deathboxMovement(int i);
void triggerMovement(int i);
void displacementMovement(int i);
void lightMovement(int i);


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
#include "draw.h"
#include "initTexture.h"
#include "particles.h"
#include "profile.h"
#include "campaign.h"
#include "sounds.h"
#include "objectMovement.h"
