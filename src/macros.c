
#define DRAW_OBJECTS_EDITOR(obj, type, under_condition,draw_function) \
   for (int i = 0;i<sizeof(obj)/sizeof(obj[0]);i++){ \
      if(obj[i].reserved  && under_condition){ \
         /* Camera offsetted data ! */ \
         obj[i].xDraw = obj[i].x; \
         obj[i].yDraw = obj[i].y; \
         obj[i].widthDraw = obj[i].width*camera.scale; \
         obj[i].heightDraw = obj[i].height*camera.scale; \
         obj[i].xDraw  += camera.x; \
         obj[i].yDraw  += camera.y; \
         obj[i].xDraw  = gameWidthBase/2 + (obj[i].xDraw - gameWidthBase/2) * camera.scale; \
         obj[i].yDraw  = gameHeightBase/2 + (obj[i].yDraw - gameHeightBase/2) * camera.scale; \
         draw_function; \
         if(editor.selected && editor.typeSelected == type && editor.indexSelected == i){  \
         SDL_SetRenderDrawColor(renderer,0,255,0,255); \
         RenderDrawRect(renderer,&(SDL_Rect){obj[editor.indexSelected].xDraw, \
                                                 obj[editor.indexSelected].yDraw, \
                                                 obj[editor.indexSelected].widthDraw, \
                                                 obj[editor.indexSelected].heightDraw}); \
         } \
      } \
   } \


#define DRAW_OBJECTS(obj, under_condition,draw_function) \
   for (int i = 0;i<sizeof(obj)/sizeof(obj[0]);i++){ \
      if(obj[i].reserved  && under_condition){ \
         /* Camera offsetted data ! */ \
         obj[i].xDraw = obj[i].x; \
         obj[i].yDraw = obj[i].y; \
         obj[i].widthDraw = obj[i].width*camera.scale; \
         obj[i].heightDraw = obj[i].height*camera.scale; \
         obj[i].xDraw  += camera.x; \
         obj[i].yDraw  += camera.y; \
         obj[i].xDraw  = gameWidthBase/2 + (obj[i].xDraw - gameWidthBase/2) * camera.scale; \
         obj[i].yDraw  = gameHeightBase/2 + (obj[i].yDraw - gameHeightBase/2) * camera.scale; \
         draw_function; \
      } \
   } \




