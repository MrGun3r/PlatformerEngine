
char* infoTextMessages[] = {
   "Add Platform",
   "Translate",
   "Resize",
   "Save Map",
   "Save Map As",
   "Delete Object",
   "Load Map",
   "Change Texture",
   "Inverse Slope",
   "Copy Object",
   "Load New Map",
   "Map Settings",
   "Add Trigger",
   "Add Finish Line",
   "Add Checkpoint",
   "Zoom In",
   "Zoom Out",
   "Texture Stretch",
   "Change Background",
   "Add Light",
   "Add Displacement Block",
   "Change Displacement Direction",
   "Change Displacement Type",
   "Add DeathBox",
   "Toggle Collidable",
   "Add Move Node",
   "Add Node",
   "Remove Node",
   "Wrap Nodes",
   "Trigger Type",
   "Add Script Block",
   "Change Name",
   "Change Light",
   "Add Enemy",
   "Add Special",
   "Change Special",
   "Add TextBox",
   "Set Text",
   "Change Texture Rotation",
   "Toggle Finish Animation"
};

char* knobInfoText[] = {
      "Change Texture Scale\0",
      "None\0",
      "None\0",
      "Change Border X\0",
      "Change Border Y\0",
      "Change Animation Speed\0",
      "Change Star Time Ms\0",
      "Change Star Time\0",
      "Change Node ID\0",
      "Change Move Speed\0",
      "Change Object ID\0",
      "Change Use Time Delay",
      "Change Reuse Time Delay",
      "Change Text X Coordinate",
      "Change Text Y Coordinate",
      "Change Text Font",
      "Change Unit",
      "Change Unit2",
      "Change Unit3",
      "Change Unit3",
      "Change Unit3"

};

char* sliderInfoText[] = {
      "Change Slope\0",
      "Change Texture Offset X\0",
      "Change Texture Offset Y\0",
      "Change Texture Scale\0",
      "Change Map Border X\0",
      "Change Map Border Y\0",
      "Change Map Light\0",
      "Change Light Rotation\0",
      "Change Light Brightness\0",
      "Change Light Visibility\0",
      "Change Red Value\0",
      "Change Green Value\0",
      "Change Blue Value\0",
      "Change Displacement Power\0",
      "Change Opacity\0",
      "Change Camera Zoom\0",
      "Change Max Speed",
      "Change Enemy Health"

};

char* specialTypes_Array[] = {
         "Slash",
         "Wings",
         "Double Jump",
         "Dash",
         "Arrow",
         "Projectile",
         "Grapple"
};

char* displacement_directionTypes[] = {
      "Right",
      "Up",
      "Left",
      "Down"
};

char* displacement_powerTypes[] = {
      "Velocity",
      "Accelerate"
};

#include "editor_buttons.c"
#include "editor_utils.c"
#include "editor_draw.c"
#include "editor_state.c"
#include "editor_update.c"