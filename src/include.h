
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
#define CLAMP_MIN(x,min) if(x < min) x = min
#define CLAMP_MAX(x,max) if(x > max) x = max

#define CLAMP_MINMAX(x, min, max) do { if ((x) < (min)) (x) = (min); else if ((x) > (max)) (x) = (max);} while(0) 
#define ROUND_TO(x,start,max) if(x > max) x = start;


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


char* campaignLevel[] = {
    "levels/introduction.txt",
    "levels/introduction2.txt",
    "levels/introduction3.txt",
    "levels/introduction4.txt",
    "levels/introduction4.txt",
    "levels/introduction4.txt"
};

int delayTimers_forSpecials[] = {
      400,
      800,
      800,
      400,
      500,
      200,
      300
};


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
SDL_Surface* surface_script = NULL;
SDL_Texture* tex_script = NULL;
SDL_Surface* surface_enemy = NULL;
SDL_Texture* tex_enemy = NULL;
SDL_Surface* surface_explosion = NULL;
SDL_Texture* tex_explosion  = NULL;
SDL_Surface* surface_specials = NULL;
SDL_Texture* tex_specials = NULL;
SDL_Surface* surface_textIcon = NULL;
SDL_Texture* tex_textIcon = NULL;
SDL_Surface* surface_grappleFail = NULL;
SDL_Texture* tex_grappleFail = NULL;

// Game window Textures
SDL_Texture* backgroundLayer = NULL;
SDL_Texture* lightLayer = NULL; 
SDL_Texture* lightLayer2 = NULL; 
SDL_Texture* HUDLayer = NULL;
SDL_Texture* TransitionLayer = NULL;
SDL_Texture* resultLayer = NULL;    



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
Mix_Chunk* Sound_textTick = NULL;
Mix_Chunk* Sound_slash = NULL;
Mix_Chunk* Sound_enemyHurt = NULL;
Mix_Chunk* Sound_enemyDead = NULL;
Mix_Chunk* Sound_woosh = NULL;
Mix_Chunk* Sound_pickup = NULL;


// Variable Types

#include "main/structs.h"
#include "main/useFunctions.c"

// dTime
void FdeltaTime();

// This file includes all the necessary files needed to run the game !


// Map Data Read/Write
int FSetDataMap(char* path,int pathSize);
char* FGetDataMap(char* fileName,char* type,int dataType,int fileNameSize);
void FSetValue(char* importBuffer,int importBufferSize,int data,int ID,int dataType);

// Texture Init
void FLoadTextures();
void FLoadBackgrounds();
int FindTextureInt(char *textureName);
int FindBackgroundInt(char *backgroundName);

// Sound Init
void FLoadSounds();

// Scripts Load
void FLoadScripts();
int findScriptId(char* scriptName);
void ExecuteScript(int index);

// Rendering 
void FtexturePlatform(int platformID);
void FtextureQuad(double x,double y,double width,double height,SDL_Texture* texture,double opacity,int rotationAngle);
void renderText(int stringCount,char *Text,int x ,int y, int width,int height,int opacity,int shadowOpacity,int color[3]);
void FGUIHover();
SDL_Texture* CreateRepeatedTexture(SDL_Renderer* renderer, SDL_Texture* originalTexture, int n);
void DrawBackground();
void ReadLevelCampaign();

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
void Set_KnobValues();
void Set_SlidersValues();

// Text
void FapplyText();
void writeText(SDL_Event* event);
void applySliderNumBox(int index);
void applyKnobNumBox(int index);

// Movement
void FapplyMovementGhost();
void FPlayer_Movement();
void FPlayer_Special();

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
void DrawLight(double tint);

// Editor functions 
void FUpdate_Editor();
void FCheck_Select_Editor();
void FDraw_SideBar_Editor();
void FTransformState(); // transforms an object or a camera view
void FDrawObjects();
void FDraw_Editor();
void FSaveMap(char mapName[256]);
void addMoveNode(int x, int y);
void addDisplacement(double x, double y, double width,double height,double type,double power,double powerType,double opacity);
void addPlatform(int x,int y,double width,double height,double slope,bool slopeInv,int texture,int type,double scale,double offsetX,double offsetY,bool stretch,bool collidable,double opacity,double animation,double red,double green,double blue);
void addParticle(SDL_Texture* texture,double x,double y,double veloX,double veloY,double size,double red,double green,double blue,double angle);
void editorShowButtons();
void addTrigger(int x,int y,double width,double height,int Type,double opacity,double Value1,double Value2,double Value3,double Value4);
void addLight(double x,double y,double width,double height,double red,double green,double blue,double visibility,double brightness,double moveSpeed,int lightInt);
void addDeathBox(double x, double y, double width,double height,double opacity);
void addScript(double x,double y,double width,double height);
void addEnemy(int x,int y,int width,int height);
void addSpecial(int x, int y,int size,int type);
void addTextPopUp(int x, int y,double width,double height);
void addDamagePopUp(int value,double x,double y,double size,double veloX,double veloY);
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
void addProjectile(bool fromEnemy,double x, double y, double veloX,double veloY,int type);
void FGameRestart();

// Movement
void platformMovement(int i);
void deathboxMovement(int i);
void triggerMovement(int i);
void displacementMovement(int i);
void lightMovement(int i);

// Light
int FindLightInt(char* textureName);


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
#include "init.c"
#include "editor/addObject.c"
#include "main/input_listener.c"
#include "main/renderGUI.c"
#include "main/textureQuad.c"
#include "main/mapdata.c"
#include "game/collision.c"
#include "main/menu.c"
#include "main/app_status.c"
#include "game/movement.c"
#include "game/game.c"
#include "main/recordReplay.c"
#include "editor/editor.c"
#include "editor/transformObject.c"
#include "main/GUIElements.c"
#include "main/text.c"
#include "main/draw.c"
#include "main/initTexture.c"
#include "game/particles.c"
#include "main/profile.c"
#include "game/script.c"
#include "main/sounds.c"
#include "game/objectMovement.c"
