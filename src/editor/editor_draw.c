/// Draw editor objects

#include "editor_object_draw.c"
#include "editor_info_draw.c"



void Editor_DrawLoadSave(){  
   SDL_SetRenderDrawColor(renderer,100,100,100,200);
   RenderFillRect(renderer,&(SDL_Rect){30,100,windowWidth-180,150});
   if(editor.status == 0){
      renderText(33,"Enter to save / Escape to cancel",45,210,33*12,15,255,200,(int[3]){255,255,255});
   }
   else if (editor.status == 1){
      renderText(33,"Enter to load / Escape to cancel",45,210,33*12,15,255,200,(int[3]){255,255,255});
   }
   else if (editor.status == 2){
      renderText(36,"Enter to Set Text / Escape to cancel",45,210,33*12,15,255,200,(int[3]){255,255,255});
   }
   
}
void Editor_Draw_GUIBackground() {

   SDL_SetRenderDrawColor(renderer,100,100,100,255);
   RenderFillRect(renderer,&(SDL_Rect){0,0,gameWidthBase,50});
   SDL_SetRenderDrawColor(renderer,20,20,20,255);
   RenderDrawRect(renderer,&(SDL_Rect){0,0,gameWidthBase,50});
   SDL_SetRenderDrawColor(renderer,100,100,100,255);
   RenderFillRect(renderer,&(SDL_Rect){gameWidthBase-200,0,200,gameHeightBase});
   SDL_SetRenderDrawColor(renderer,20,20,20,255);
   RenderDrawRect(renderer,&(SDL_Rect){gameWidthBase-200,0,200,gameHeightBase});
   SDL_SetRenderDrawColor(renderer,90,90,90,255);
   RenderFillRect(renderer,&(SDL_Rect){60,5,gameWidthBase-275,40});
   SDL_SetRenderDrawColor(renderer,80,80,80,255);
   RenderFillRect(renderer,&(SDL_Rect){gameWidthBase-195,gameHeightBase-20,190,15});
   SDL_SetRenderDrawColor(renderer,0,0,0,255);
   RenderDrawRect(renderer,&(SDL_Rect){60,5,gameWidthBase-275,40});
   RenderDrawRect(renderer,&(SDL_Rect){gameWidthBase-195,gameHeightBase-20,190,15});
}
void Editor_Draw_Borders() {
   SDL_SetRenderDrawColor(renderer,200,0,0,100);
   double xMin =  max(min(gameWidthBase/2 + (mapData.xMin + camera.x - gameWidthBase/2)*camera.scale,gameWidthBase),0);
   double yMin =  max(min(gameHeightBase/2 + (mapData.yMin + camera.y - gameHeightBase/2)*camera.scale,gameHeightBase),0);
   double xMax =  max(min(gameWidthBase/2 + (mapData.xMax + camera.x - gameWidthBase/2)*camera.scale,gameWidthBase),0);
   double yMax =  max(min(gameHeightBase/2 + (mapData.yMax + camera.y - gameHeightBase/2)*camera.scale,gameHeightBase),0);
   RenderFillRect(renderer,&(SDL_Rect){0,0,xMin,gameHeightBase});
   RenderFillRect(renderer,&(SDL_Rect){xMax,0,gameWidthBase-xMax,gameHeightBase});
   RenderFillRect(renderer,&(SDL_Rect){xMin,0,xMax-xMin,yMin});
   RenderFillRect(renderer,&(SDL_Rect){xMin,yMax,xMax-xMin,gameHeightBase-yMax});
}
void Draw_Editor(){  
   
   SDL_RenderClear(renderer);
   /// Draw the background 
   DrawBackground();
   /// Draw every object available
   Editor_DrawObjects();
   /// Draw the lights 
   DrawLight(app.backgroundOpacity);

   // Draw the save / load text
   if(editor.status >= 0){
    Editor_DrawLoadSave();
   }

   // Draw map borders
   Editor_Draw_Borders();
   // Draw the GUI background
   Editor_Draw_GUIBackground();

   // Draw Object info (xy coords , size , etc)
   Editor_Draw_ObjectInfo();
   
   // update the gui hover mecanism
   GUIHover();
   // render GUI elements
   renderButtons();
   renderSliders();
   renderKnobs();
   renderTextBox();

   /// Render camera editor info
   Editor_renderCameraInfo();
}
