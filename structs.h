
struct LevelsList{
   bool reserved;
   char levelPath[256];
   char PB[9];
   char levelName[256];
   int levelNameSize;
};


struct Editor{
  bool selected;
  int typeSelected;
  int indexSelected;
  int transform;
  bool typing;
  bool saving;
  char fileNameSave[256];
  int fileNameSize;
  int status;
  bool unSelect;
}editor;

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
  int checkpoints[50];
  int checkpointCount;
  int checkpointsSize;
  int checkpointShowTimer;
  int LastCheckpointTimer;
} level;

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
   int editorPlatformSize;
}app;

struct Button{
  bool reserved;
  double x;
  double y;
  SDL_Texture* iconTexture;
  double u1;
  double u2;
  double v1;
  double v2;
  char* text;
  int textSize;
  double ButtonFontHeight;
  double ButtonFontWidth;
  double hoverWidth;
  double hoverHeight;
  double hoverOpacity;
  bool hoverable;
  bool highlight;
};

struct Slider{
  bool reserved;
  double x;
  double y;
  SDL_Texture* iconTexture;
  double u1;
  double u2;
  double v1;
  double v2;
  char* text;
  int textSize;
  double ButtonFontHeight;
  double ButtonFontWidth;
  double hoverWidth;
  double hoverHeight;
  double hoverOpacity;
  bool hoverable;
  bool highlight;
  double sliderLength;
  double sliderMinValue;
  double sliderMaxValue;
  double sliderValue;
};

struct MapData{
   // for clarity these are the values that the camera will not follow if the player goes beyond them.
   double xMin;
   double yMin;
   double xMax;
   double yMax;
   
   
   int PBTimer;
   char mapName[256];
   int mapNameLen;
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
    bool ghost;
    struct KeyboardBind keys;

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
   double textureOffsetX;
   double textureOffsetY;
   int textureInt;
   int type;
   bool platformUsed;

};

struct Trigger{
   bool reserved;
   double x;
   double y;
   double width;
   double height;
   int triggerType;

   // 0 Camera Switch
   // 1 CheckPoint
   // 2 Finish Line
};


struct MouseBind{
   // 0 idle
   // 1 pressed
   // -1 released (status with one frame per click)
   int oldX;
   int oldY;
   int x;
   int y;
   int dX;
   int dY;
   int left;
   int right;
   bool middle;
   int roll;
} mouse;

// Allocate buffers for the data
struct Players player[2];
struct Platform platforms[100];
struct Button buttons[100];
struct LevelsList levelsList[256];
struct Trigger triggers[100];
struct Slider sliders[100];
