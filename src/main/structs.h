
struct Texture{
   bool reserved;
   char textureName[256];
   SDL_Texture* texture;
   int SizeScale;
   int textureSize;
   int textureAnimationSize;
};

struct LightTexture{
   bool reserved;
   char textureName[256];
   SDL_Texture* texture;
};

struct Script{
   bool reserved;
   char scriptName[100];
   char* script;
   int** scriptCompiled;
   int commandsNumber;
};

struct Background{
   bool reserved;
   char textureName[256];
   SDL_Texture* texture;
   int textureWidth;
   int textureHeight;
};


struct LevelsList{
   bool reserved;
   char levelPath[256];
   char PB[9];
   char levelName[256];
   int levelNameSize;
};


struct Light{
   double editorSelectionTime;
   bool reserved;
   
   double x;
   double y;
   double spawnX;
   double spawnY;
   double xDraw;
   double yDraw;
   double width;
   double height;
   double widthDraw;
   double heightDraw;
   

   double rotation;
   double angle;

   double brightness;
   double visibility;

   double red;
   double green;
   double blue;

   int moveNodeInt;
   double moveSpeed;
   double moveDistance;
   int moveNodeCount;
   bool moveNodeReverse;

   int moveNodeIntSpawn;
   double moveSpeedSpawn;

   int lightInt;
};

struct Profile{
   char username[256];
   int coins;
   int experience;
   int levelsUnlocked;
};

enum ObjectType {
      PLAYER,
      PLATFORM,
      TRIGGER,
      LIGHT,
      DISPLACEMENT,
      MOVENODE,
      DEATHBOX,
      SCRIPT,
      ENEMY,
      SPECIAL,
      TEXTPOPUP,
      NONE
};
typedef enum ObjectType ObjectType;

struct Editor{
  bool selected;
  ObjectType typeSelected;
  int indexSelected;
  int movenodeSelected;
  int transform;
  bool saving;
  char fileNameSave[256];
  int fileNameSize;
  int status;
  bool unSelect;
  int platformPageSelect;
  double GameScale;
  double StarTime;
  double StarTimeMs;
  double gridMove;
  double mouseProjected[2];
  double mouseToObjectDistances[2];
  char mapName[256];
  bool mapNameSet;
  bool mouseToObjectDistanceBool;
  char alertText[256];
  double alertTimer;
}editor;

struct Level{
  char absolutePath[256];
  int absolutePathSize;
  double timer;
  bool Paused;
  bool Finished;
  bool Started;
  bool transitionToLevel;
  char keyInputs[2000];
  bool tempFileMade;
  int keyInputsSize;
  bool newRecord;
  int checkpoints[50];
  int checkpointCount;
  int checkpointsSize;
  int checkpointShowTimer;
  int LastCheckpointTimer;
  double resetTransition;
  double endTransition;
  double cameraScaleStart;
  int StarTime;
  double endShowCoins;

  bool campaignLevel;
  double coinsReceivedOpacity;

  double LastCheckpointX;
  double LastCheckpointY;
} level;

struct Enemy{
   bool reserved;
   int type;
   double x;
   double y;
   double spawnX;
   double spawnY;
   double width;
   double height;
   double veloX;
   double veloY;
   double jumpVelo;
   bool onPlatform;
   int platformIndex;
   double bumpX;
   double accX;
   double accY;
   double maxSpeed;
   double xDraw;
   double yDraw;
   double heightDraw;
   double widthDraw;
   double editorSelectionTime;
   double textureAnimationInt;
   int direction;
   bool killed;
   double attackCoolDown;
   double health;
   int damageHit;
   int maxHealth;
   bool unbump;
   double angle;

   //// attack
   double attackDelayTimer;
   bool attackPrepare;
   double angleToPlayer;
   // dash
   double dashX;
   double dashY;



};

struct KeyboardBind{
   bool up;
   bool down;
   bool left;
   bool right;
   bool shift;
   bool r;
   bool c;
   bool e;
   bool escape;
   bool escapeRelease;
   bool enter;
};

struct Camera{
   double x;
   double y;
   double scale;
   double xReal;
   double yReal;
   double scaleReal;
   bool freeCam;
} camera;

struct App{
   double backgroundMoving;
   int status;
   int statusTo;
   double deltaTime;
   double WINDOW_TICKS;
   bool WINDOW_LOOP;
   bool fetchedList;
   bool inputChange;
   bool transition;
   double transitionInt;
   double TextBlink;

   char backgroundName[256];
   int backgroundInt;
   double backgroundOpacity;
   int textboxSelected;
   int sliderTextBoxSelected;
   int knobTextBoxSelected;
   int listStartIndex;
   int listLength;
   int listLengthMax;

   int resolutions[6][2];
   int resolutionInt;
   int resolutionUsed;

   double musicVolume;
   double sfxVolume;

   bool showFPS;

   int chapter;
   int campaignLevel;
   int campaignLevelSelect;
   char campaignLevelName[256];
   int campaignLevelPB;
   double campaignLevelShowcase;
   int campaignLevelStarTime;

   char levelGoTo[256];
   bool statusChanged;

}app;

struct Damage{
  bool reserved;
  double x;
  double y;
  double size;
  double veloX;
  double veloY;
  double xDraw;
  double yDraw;
  double sizeDraw;
  int number;
  double opacity;

};

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
  char value[256];
  bool hoverSound;

};

struct Knob{
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
  
  double knobValue;
  double knobMax;
  double knobMin; 

  double knobCoef;

  char value[256];
};

struct TextBox{
   bool reserved;
   double x;
   double y;
   double font;
   char textBoxName[256];
   char textContent[256];
   double hoverLength;
   double hoverOpacity;
   int textContentSize;
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
  char value[256];
};

struct Channel{
   bool playing;
   double playtime;
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
   double editorSelectionTime;
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
    double groundPoundX;
    double wallveloX;
    double jumpVelo;
    double walkingSpeed;
    double sprintSpeed;

    double displacementVeloX;
    double displacementVeloY;
    double displacementAccelX;
    double displacementAccelY;
    
    bool drawTrails;
    double playerTrails[5][5];
    int trailIndex;
    double trailTime;
    double accX;
    double accY;
    bool onPlatform;
    int platformIndex;
    int onWall;
    int direction;
    double animationIndex;
    double idleIndex;
    double playerControl;
    bool ghost;
    struct KeyboardBind keys;
    double particleTimer;
    bool jumpBool;
    bool dead;
    double deathAnimationTimer;
    bool groundPound;
    double poundHeight;
    double poundPotential;
    int health;
    double invisTimer;
    double stepSoundCount;
    int stepSoundInt;
    double wallHangingCount;
    
    double specialDelay;
    double specialDelayTimer;
   // Attack slash
    bool attack;
    double attackX;
    double attackY;
    double attackSize;
    int attackDirection;
    int attackDrawInt;
   // Double jump
    int doubleJump;
    
   // Wings
    //none
   // Dash
    
    double specialshow;
    int special;
    int canTake;
    double EButtonOpacity;
    // Arrows
    int enemyTarget;
    double arrowPull;
    double enemyTargetDistance;
    double ProjectileAngle;
    double angleTargetTexture;
    double opacityTargetTexture;

    // Projectile
    int projectileThrown;

    // grapple
    bool grappling;
    double grappleX;
    double grappleY;
    double grappleAngle;
    double grappleAngularVelo;
    double grappleAngularAcc;
    double grappleLength;
    double grappleFailed;


};
struct Special{
   bool reserved;
   double editorSelectionTime;
   double x;
   double y;
   double height;
   double width;
   double xDraw;
   double yDraw;
   double heightDraw;
   double widthDraw;
   int type;
   bool taken;
};
struct Projectile{
   bool reserved;
   double x;
   double y;
   double width;
   double height;
   double veloX;
   double veloY;
   double accX;
   double accY;
   double xDraw;
   double yDraw;
   double widthDraw;
   double heightDraw;
   double angle;
   double followAngle;
   double despawnTime;
    
   bool fromEnemy;
   int enemyIndex;
   int projectileType;
};
struct Particle{
   bool reserved;
   double x;
   double y;
   double xDraw;
   double yDraw;
   double veloX;
   double veloY;
   double size;
   double sizeDraw;
   double red;
   double green;
   double blue;
   SDL_Texture* texture;
   double rotation;
};

struct textPopup{
   bool reserved;
   double editorSelectionTime;
   double x;
   double y;
   double width;
   double height;
   double xDraw;
   double yDraw;
   double widthDraw;
   double heightDraw;

   double xPopup;
   double yPopup;
   double font;
   
   double showProgress;


   char* textContent;
};

struct DeathBox{
   double editorSelectionTime;
   bool reserved;
   double spawnX;
   double spawnY;
   double x;
   double y;
   double xDraw;
   double yDraw;
   double width;
   double height;
   double widthDraw;
   double heightDraw;
   double opacity;

   int moveNodeInt;
   double moveSpeed; 
   double moveDistance;
   int moveNodeCount;
   bool moveNodeReverse;

   int moveNodeIntSpawn;
   double moveSpeedSpawn;
};


struct Displacement{
   double editorSelectionTime;
   bool reserved;
   double x;
   double y;
   double spawnX;
   double spawnY;
   double xDraw;
   double yDraw;
   double width;
   double height;
   double widthDraw;
   double heightDraw;
   int type;
   int powerType;
   double power;
   double opacity;

   int moveNodeInt;
   double moveSpeed;
   double moveDistance;
   int moveNodeCount;
   bool moveNodeReverse;

   int moveNodeIntSpawn;
   double moveSpeedSpawn;
};


struct Platform{
   double editorSelectionTime;
   bool reserved;
   double spawnX;
   double spawnY;
   double x;
   double y;
   double xDraw;
   double yDraw;
   double widthDraw;
   double heightDraw;
   double slope;
   double steepness;
   double width;
   double height;
   bool slopeInv;
   double textureScale;
   SDL_Texture* texture;
   bool textureStretch;
   double textureOffsetX;
   double textureOffsetY;
   double textureOffsetX_Move;
   double textureOffsetY_Move;
   int textureInt;
   int type;
   bool platformUsed;
   bool collidable;
   double opacity;
   double red;
   double green;
   double blue;
   int textureRotation;
   double textureAnimationInt;
   double textureAnimationTime;
   double textureAnimationTimer;

   int moveNodeInt;
   double moveSpeed;
   double moveDistance;
   int moveNodeCount;
   bool moveNodeReverse;


   int moveNodeIntSpawn;
   double moveSpeedSpawn;

   // finish line
   bool NofinishAnimation;

   // Grapplable
   bool grapplable;
   
};

struct Trigger{
   double editorSelectionTime;
   bool reserved;
   double x;
   double y;
   double spawnX;
   double spawnY;
   double xDraw;
   double yDraw;
   double widthDraw;
   double heightDraw;
   double width;
   double height;
   int triggerType;
   double opacity;
   bool triggerUsed;
   bool timerStart;

   double Value1;
   double Value2;
   double Value3;
   double Value4;


   double useDelay;
   double reuseDelay;

   double useDelayTimer;
   double reuseDelayTimer;

   // 0 Platform 
   // 1 DeathBox
   // 2 Displacement
};
struct MoveNode{
   bool reserved;
   double positions[20][2];
   double positionsDraw[20][2];
   int nodesCount;
   double editorSelectionTime;
   bool wrap;
};

struct ScriptBlock{
   double editorSelectionTime;
   bool reserved;
   double x;
   double y;
   double xDraw;
   double yDraw;
   double widthDraw;
   double heightDraw;
   double width;
   double height;
   bool used;
   int scriptInt;
   double useDelay;
   double reuseDelay;
   
   bool startTimer;

   double useDelayTimer;
   double reuseDelayTimer;
   bool execute;
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
   int wheel;
} mouse;

// Allocate buffers for the data
struct Players player[2];
struct Platform platforms[300];
struct Button buttons[100];
struct Knob knobs[50];
struct LevelsList levelsList[256];
struct Trigger triggers[100];
struct Slider sliders[100];
struct Texture textures[50];
struct Background backgrounds[50];
struct Light light[100];
struct LightTexture lightTextures[50];
struct Particle particles[200];
struct Displacement displacement[100];
struct DeathBox deathbox[100];
struct TextBox textbox[20];
struct Profile profile;
struct Channel channels[8];
struct MoveNode movenodes[50];
struct ScriptBlock scripts[50];
struct Script scriptfiles[50];
struct Enemy enemy[50];
struct Special specials[20];
struct textPopup textpopups[20];
struct Damage damagepopups[20];
struct Projectile projectiles[20];