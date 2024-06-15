// Buttons layout

// 0 => Add platform
// 1 => Translate 
// 2 => Resize
// 3 => Slope
// 4 => Save Map
// 5 => Delete
// 6 => Load Map
// 7 => Texture
// 8 => SlopeInv
// 9 => Copy
// 10 => New
// 11 => Test
// 12 => Add Trigger
// 13 => Add Finish Line




void FUpdate_Editor(){
   if(!editor.typing){
       FTransformState();
   }
  // printf("%f\n",sliders[0].sliderValue);
   platforms[editor.indexSelected].slope = sliders[0].sliderValue/(180/(2*PI));
   platforms[editor.indexSelected].textureOffsetX = sliders[1].sliderValue;
   platforms[editor.indexSelected].textureOffsetY = sliders[2].sliderValue;


   // Buttons
   for(int i = 0;i<sizeof(buttons)/sizeof(buttons[0]);i++){
    if(buttons[i].reserved){
      int yMin = buttons[i].y;
      int yMax = buttons[i].y+buttons[i].hoverHeight;
      int xMin = buttons[i].x;
      int xMax = buttons[i].x+buttons[i].hoverWidth;      
      if(mouse.x >= xMin && mouse.x <= xMax && mouse.y >= yMin && mouse.y <= yMax && mouse.left == -1){
        mouse.left = 0;
       if(i == 0){
         addPlatform(windowWidth/2-camera.x,windowHeight/2-camera.y,25,25,0,false,1,false);
       } 
       if(i == 1 && editor.selected){
         editor.transform = 1;
         buttons[1].highlight = true;
         buttons[2].highlight = false;
         buttons[3].highlight = false;
       }  
       else if (i == 2  && editor.selected){
         editor.transform = 0;
         buttons[1].highlight = false;
         buttons[2].highlight = true;
         buttons[3].highlight = false;
       }
       
       else if (i == 3  && editor.selected){
         editor.transform = 2;
         buttons[1].highlight = false;
         buttons[2].highlight = false;
         buttons[3].highlight = true;
       }
       else if (i == 4){
         editor.typing = true;
         editor.status = 0;
       }
       else if (i == 5  && editor.selected){
         if(editor.typeSelected == 1){
            platforms[editor.indexSelected].reserved = false;
         }
         else if(editor.typeSelected == 2){
            triggers[editor.indexSelected].reserved = false;
         }
         
         editor.selected = false;
       }
       else if (i == 6){
         editor.typing = true;
         editor.status = 1;
       }
       else if (i == 7 && editor.selected){
         platforms[editor.indexSelected].textureInt++;
         platforms[editor.indexSelected].textureInt %= 7;
       }
       else if (i == 8){
         platforms[editor.indexSelected].slopeInv = !platforms[editor.indexSelected].slopeInv;
       }
       else if (i == 9){
         // Copy Object
         if(editor.typeSelected == 1){
            if(platforms[editor.indexSelected].type == 0){
               addPlatform(windowWidth/2-camera.x,windowHeight/2-camera.y,platforms[editor.indexSelected].width,platforms[editor.indexSelected].height,platforms[editor.indexSelected].slope,platforms[editor.indexSelected].slopeInv,-1,0);
            }
            else if (platforms[editor.indexSelected].type == 1){
               addPlatform(windowWidth/2-camera.x,windowHeight/2-camera.y,platforms[editor.indexSelected].width,platforms[editor.indexSelected].height,platforms[editor.indexSelected].slope,platforms[editor.indexSelected].slopeInv,platforms[editor.indexSelected].textureInt,1);
            }
            else if (platforms[editor.indexSelected].type == 2){
               addPlatform(windowWidth/2-camera.x,windowHeight/2-camera.y,platforms[editor.indexSelected].width,platforms[editor.indexSelected].height,platforms[editor.indexSelected].slope,platforms[editor.indexSelected].slopeInv,platforms[editor.indexSelected].textureInt,2);
            }
         }
         else if (editor.typeSelected == 2){
           addTrigger(windowWidth/2-camera.x,windowHeight/2-camera.y,triggers[i].width,triggers[i].height,triggers[i].triggerType); 
         }
         
       }
       else if (i == 12){
         addTrigger(windowWidth/2-camera.x,windowHeight/2-camera.y,25,25,0);
       }
       else if (i == 13){
         addPlatform(windowWidth/2-camera.x,windowHeight/2-camera.y,25,25,0,false,-1,1);
       }
       else if (i == 14){
         addPlatform(windowWidth/2-camera.x,windowHeight/2-camera.y,25,25,0,false,-1,2);
       }
      }
    }
   }
   if(mouse.left == -1){
     FCheck_Select_Editor();
     editorShowButtons();
   }
}

void addTrigger(int x,int y,double width,double height,int Type){
   for(int i = 1;i<sizeof(triggers)/sizeof(triggers[0]);i++){
      if(!triggers[i].reserved){
        editor.selected = true;
        editor.typeSelected = 2;
        editor.indexSelected = i;
        triggers[i].reserved = true;
        triggers[i].x = x;
        triggers[i].y = y;
        triggers[i].width = width;
        triggers[i].height = height;
        triggers[i].triggerType = Type;
        break;
      }
   }
   editorShowButtons();
}


void addPlatform(int x,int y,double width,double height,double slope,bool slopeInv,int texture,int type){
   for(int i = 1;i<sizeof(platforms)/sizeof(platforms[0]);i++){
      if(!platforms[i].reserved){
        editor.selected = true;
        editor.typeSelected = 1;
        editor.indexSelected = i;
        platforms[i].reserved = true;
        platforms[i].x = x;
        platforms[i].y = y;
        platforms[i].width = width;
        platforms[i].height = height;
        platforms[i].slope = slope;
        platforms[i].slopeInv = slopeInv;
        platforms[i].textureScale = 50;
        if(type == 1){platforms[i].textureInt = 6;platforms[i].type = 1;}
        else if(type == 2){platforms[i].textureInt = 7;platforms[i].type = 2;}
        else{platforms[i].textureInt = texture;platforms[i].type = 0;}
        platforms[i].textureStretch = false;
        platforms[i].textureStretchPer = false;
        platforms[i].textureOffsetX = 0;
        platforms[i].textureOffsetY = 0;
        break;
      }
   }
   editorShowButtons();
}

void editorShowButtons(){
   for(int i = 0 ;i<sizeof(buttons)/sizeof(buttons[0]); i++){
      buttons[i].reserved = false;
   }
   for(int i = 0 ;i<sizeof(buttons)/sizeof(buttons[0]); i++){
      sliders[i].reserved = false;
   }
   buttons[0].reserved = true;
   buttons[4].reserved = true;
   buttons[6].reserved = true;
   buttons[10].reserved = true;
   buttons[11].reserved = true;
   buttons[12].reserved = true;
   buttons[13].reserved = true;
   buttons[14].reserved = true;

   if(editor.selected){
      buttons[1].reserved = true;
      buttons[2].reserved = true;
      buttons[5].reserved = true;
      buttons[9].reserved = true;
      if(editor.typeSelected == 0){
            // Nothing so far
      }
      else if(editor.typeSelected == 1){
         if(!platforms[editor.indexSelected].type){
         sliders[0].reserved = true;
         sliders[1].reserved = true;
         sliders[2].reserved = true;
         buttons[7].reserved = true;
         buttons[8].reserved = true;  
         }
      }
      else if (editor.typeSelected == 2){
       // Nothing for trigger so far
      }
   }
}

void FDraw_Editor(){  
   SDL_RenderClear(renderer);
   SDL_RenderCopy(renderer,tex_background,&(SDL_Rect){app.backgroundMoving,0,576,324},&(SDL_Rect){0,0,(windowWidth-app.backgroundMoving*windowWidth/576),windowHeight});
   SDL_RenderCopy(renderer,tex_background,&(SDL_Rect){0,0,app.backgroundMoving,324},&(SDL_Rect){windowWidth-app.backgroundMoving*windowWidth/576,0,app.backgroundMoving*windowWidth/576,windowHeight});
   SDL_SetRenderDrawColor(renderer,210,210,210,255);
   for(int i = (int)(camera.x-windowWidth/2)%20;i<windowWidth;i+=20*camera.scale){
      SDL_RenderDrawLine(renderer,i,0,i,windowHeight);
   }
   for(int j =  (int)(camera.y-windowHeight/2)%20;j<windowHeight;j+=20*camera.scale){
      SDL_RenderDrawLine(renderer,0,j,windowWidth,j);
   }
   FDrawObjects();
   if(editor.typing){
      FSaveMap();
   }
   SDL_SetRenderDrawColor(renderer,100,100,100,255);
   SDL_RenderFillRect(renderer,&(SDL_Rect){0,0,windowWidth,50});
   SDL_SetRenderDrawColor(renderer,20,20,20,255);
   SDL_RenderDrawRect(renderer,&(SDL_Rect){0,0,windowWidth,50});
   SDL_SetRenderDrawColor(renderer,100,100,100,255);
   SDL_RenderFillRect(renderer,&(SDL_Rect){windowWidth-200,0,200,windowHeight});
   SDL_SetRenderDrawColor(renderer,20,20,20,255);
   SDL_RenderDrawRect(renderer,&(SDL_Rect){windowWidth-200,0,200,windowHeight});
   SDL_SetRenderDrawColor(renderer,90,90,90,255);
   SDL_RenderFillRect(renderer,&(SDL_Rect){60,5,windowWidth-275,40});
   SDL_SetRenderDrawColor(renderer,80,80,80,255);
   SDL_RenderFillRect(renderer,&(SDL_Rect){windowWidth-145,windowHeight-20,140,15});
   SDL_SetRenderDrawColor(renderer,0,0,0,255);
   SDL_RenderDrawRect(renderer,&(SDL_Rect){60,5,windowWidth-275,40});
   SDL_RenderDrawRect(renderer,&(SDL_Rect){windowWidth-145,windowHeight-20,140,15});

   FDraw_SideBar_Editor();
   FGUIHover();
   renderButtons();
   renderSliders();
   Update_Slider();
   char posX[10]; 
   char posY[10];
   sprintf(posX,"X:%d\0",mouse.x-(int)camera.x);
   sprintf(posY,"Y:%d\0",mouse.y-(int)camera.y);
   renderText(len(posX),posX,5,windowHeight-14,len(posX)*7,12,255,(int[3]){255,255,255});
   renderText(len(posY),posY,len(posX)*7+15,windowHeight-14,len(posY)*7,12,255,(int[3]){255,255,255});
}

void FCheck_Select_Editor(){
      int xMin = (player[0].x)*camera.scale+camera.x;
      int xMax = (player[0].x+player[0].width)*camera.scale+camera.x;
      int yMin = (player[0].y)*camera.scale+camera.y;
      int yMax = (player[0].y+player[0].height)*camera.scale+camera.y; 
      
      if(mouse.x >= xMin && mouse.x <= xMax && mouse.y >= yMin && mouse.y <= yMax){
         editor.selected = true;
         editor.typeSelected = 0;
         editor.indexSelected = 0;
         return;
      }
      if((mouse.y <= 100 && mouse.x > 0 && mouse.x < windowWidth-150) || (mouse.x > windowWidth-150)){return;}
      for(int i = 0;i<sizeof(platforms)/sizeof(platforms[0]);i++){
         if(platforms[i].reserved){
            int xMin = (platforms[i].x)*camera.scale+camera.x;
            int xMax = (platforms[i].x+platforms[i].width)*camera.scale+camera.x;
            int yMin = (platforms[i].y-platforms[i].height*SDL_abs(sin(platforms[i].slope))*(sin(platforms[i].slope)>=0))*camera.scale+camera.y;
            int yMax = (platforms[i].y+platforms[i].height)*camera.scale+camera.y;
         if(mouse.x >= xMin && mouse.x <= xMax && mouse.y >= yMin && mouse.y <= yMax){
            editor.selected = true;
            editor.typeSelected = 1;
            editor.indexSelected = i;
            sliders[0].sliderValue = platforms[editor.indexSelected].slope*(180/(2*PI));
            printf("%f\n",sliders[0].sliderValue);
            return;
          }
        }
      }
      for(int i = 0 ;i<sizeof(triggers)/sizeof(triggers[0]);i++){
         if(triggers[i].reserved){
            int xMin = (triggers[i].x)*camera.scale+camera.x;
            int xMax = (triggers[i].x+triggers[i].width)*camera.scale+camera.x;
            int yMin = (triggers[i].y)*camera.scale+camera.y;
            int yMax = (triggers[i].y+triggers[i].height)*camera.scale+camera.y;
         if(mouse.x >= xMin && mouse.x <= xMax && mouse.y >= yMin && mouse.y <= yMax){
            editor.selected = true;
            editor.typeSelected = 2;
            editor.indexSelected = i;
            return;
          }
         }
      }
      if(editor.unSelect){
         editor.selected = false;
      }
      editor.unSelect = true;
      return;
}

void FDraw_SideBar_Editor(){
   // info box
   FInfoBox();
  if(editor.selected){
   char Xvalue[10];
   char Yvalue[10];
   char Widthvalue[20];
   char Heightvalue[20];
   char slope[10];
   char texture[5];
   char SlopeInv[5];
   char textureOffsetx[10];
   char textureOffsety[10];
   if(editor.typeSelected == 0){
      renderText(sizeof("Player"),"Player",windowWidth-125,10,sizeof("Player")*12,15,255,(int[3]){255,255,255});
      sprintf(Xvalue,"x:%d\0",(int)player[0].x);
      sprintf(Yvalue,"y:%d\0",(int)player[0].y);
      sprintf(Widthvalue,"width:%d\0",(int)player[0].width);
      sprintf(Heightvalue,"height:%d\0",(int)player[0].height);
   }
   if(editor.typeSelected == 1){
      if(platforms[editor.indexSelected].type == 1){
       renderText(sizeof("Finish"),"Finish",windowWidth-150,10,sizeof("Finish")*12,15,255,(int[3]){255,255,255});
      }
      else if (platforms[editor.indexSelected].type == 2){
       renderText(sizeof("Checkpoint"),"Checkpoint",windowWidth-150,10,sizeof("Checkpoint")*12,15,255,(int[3]){255,255,255});
      }
      else {
      renderText(sizeof("Platform"),"Platform",windowWidth-150,10,sizeof("Platform")*12,15,255,(int[3]){255,255,255});
      sprintf(slope,"%d\0",(int)(platforms[editor.indexSelected].slope*180/(2*PI)));
      sprintf(texture,"%d\0",(int)platforms[editor.indexSelected].textureInt);
      sprintf(SlopeInv,"%d\0",(int)platforms[editor.indexSelected].slopeInv);
      sprintf(textureOffsetx,"%d\0",(int)platforms[editor.indexSelected].textureOffsetX);
      sprintf(textureOffsety,"%d\0",(int)platforms[editor.indexSelected].textureOffsetY);
      renderText(len(slope),slope,windowWidth-40,252,len(slope)*10,10,255,(int[3]){255,255,255});
      renderText(len(texture),texture,windowWidth-40,272,len(texture)*10,10,255,(int[3]){255,255,255});
      renderText(len(SlopeInv),SlopeInv,windowWidth-40,292,len(SlopeInv)*10,10,255,(int[3]){255,255,255});
      renderText(len(textureOffsetx),textureOffsetx,windowWidth-40,312,len(textureOffsetx)*10,10,255,(int[3]){255,255,255});
      renderText(len(textureOffsety),textureOffsety,windowWidth-40,332,len(textureOffsety)*10,10,255,(int[3]){255,255,255});
      }
      sprintf(Xvalue,"x:%d\0",(int)platforms[editor.indexSelected].x);
      sprintf(Yvalue,"y:%d\0",(int)platforms[editor.indexSelected].y);
      sprintf(Widthvalue,"width:%d\0",(int)platforms[editor.indexSelected].width);
      sprintf(Heightvalue,"height:%d\0",(int)platforms[editor.indexSelected].height);
   }
   if (editor.typeSelected == 2){
      sprintf(Xvalue,"x:%d\0",(int)triggers[editor.indexSelected].x);
      sprintf(Yvalue,"y:%d\0",(int)triggers[editor.indexSelected].y);
      sprintf(Widthvalue,"width:%d\0",(int)triggers[editor.indexSelected].width);
      sprintf(Heightvalue,"height:%d\0",(int)triggers[editor.indexSelected].height);
     renderText(sizeof("Trigger"),"Trigger",windowWidth-150,10,sizeof("Trigger")*12,15,255,(int[3]){255,255,255});
      
   }
    renderText(len(Xvalue),Xvalue,windowWidth-190,100,len(Xvalue)*10,12,255,(int[3]){255,255,255});
    renderText(len(Yvalue),Yvalue,windowWidth-190,120,len(Yvalue)*10,12,255,(int[3]){255,255,255});
    renderText(len(Widthvalue),Widthvalue,windowWidth-190,140,len(Widthvalue)*10,12,255,(int[3]){255,255,255});
    renderText(len(Heightvalue),Heightvalue,windowWidth-190,160,len(Heightvalue)*10,12,255,(int[3]){255,255,255});
  }
}

void FInfoBox(){
   char infoText[100];
   for(int i = 0;i<sizeof(buttons)/sizeof(buttons[0]);i++){
    if(buttons[i].reserved && buttons[i].hoverOpacity>1 && !buttons[i].highlight){
      if(i == 0){  
        SDL_memcpy(infoText,"Add Platform\0",sizeof("Add Platform\0"));
      }
      else if(i == 1){  
        SDL_memcpy(infoText,"Translate\0",sizeof("Translate\0"));
      }
      else if(i == 2){  
        SDL_memcpy(infoText,"Resize\0",sizeof("Resize\0"));
      }
      else if(i == 4){  
        SDL_memcpy(infoText,"Save Map\0",sizeof("Save Map\0"));
      }
      else if(i == 5){  
        SDL_memcpy(infoText,"Delete Object\0",sizeof("Delete Object\0"));
      }
      else if(i == 6){  
        SDL_memcpy(infoText,"Load Map\0",sizeof("Load Map\0"));
      }
      else if(i == 7){  
        SDL_memcpy(infoText,"Change Texture\0",sizeof("Change Texture\0"));
      }
      else if(i == 8){  
        SDL_memcpy(infoText,"Inverse Slope\0",sizeof("Inverse Slope\0"));
      }
      else if(i == 9){  
        SDL_memcpy(infoText,"Copy Object\0",sizeof("Copy Object\0"));
      }
      else if(i == 10){  
        SDL_memcpy(infoText,"Load New Map\0",sizeof("Load New Map\0"));
      }
      else if(i == 11){  
        SDL_memcpy(infoText,"Test Map\0",sizeof("Test Map\0"));
      }
      else if(i == 12){  
        SDL_memcpy(infoText,"Add Trigger\0",sizeof("Add Trigger\0"));
      }
      else if(i == 13){  
        SDL_memcpy(infoText,"Add Finish Line\0",sizeof("Add Finish Line\0"));
      }
      else if(i == 14){  
        SDL_memcpy(infoText,"Add Checkpoint\0",sizeof("Add Checkpoint\0"));
      }

      renderText(len(infoText),infoText,windowWidth-138,windowHeight-16,7*len(infoText),10,255,(int[3]){200,200,200});
      return;
    }
   }
   for(int i = 0 ;i<sizeof(sliders)/sizeof(sliders[0]);i++){
      if(sliders[i].reserved && sliders[i].hoverOpacity>1 && !sliders[i].highlight){
         if(i == 0){  
            SDL_memcpy(infoText,"Change Slope\0",sizeof("Change Slope\0"));
      }
      else if(i == 1){  
            SDL_memcpy(infoText,"Texture Offset X\0",sizeof("Texture Offset X\0"));
      }
      else if(i == 2){  
            SDL_memcpy(infoText,"Texture Offset Y\0",sizeof("Texture Offset Y\0"));
      }
      renderText(len(infoText),infoText,windowWidth-138,windowHeight-16,7*len(infoText),10,255,(int[3]){200,200,200});
      return;
      }
   }
}

void FTransformState(){
  if(mouse.left && editor.selected && !((mouse.y <= 100 && mouse.x > 0 && mouse.x < windowWidth-150) || (mouse.x > windowWidth-150)  )){
   mouse.dX = mouse.x - mouse.oldX;
   mouse.dY = mouse.y - mouse.oldY;
   if(SDL_abs(mouse.dX) >= 4 || SDL_abs(mouse.dY) >= 4){
      editor.unSelect = false;
   }
   if(editor.typeSelected == 0){
      if(editor.transform == 2){
         editor.transform = 1;
         buttons[1].highlight = true;
         buttons[2].highlight = false;
         buttons[4].highlight = false;
      }
      if(editor.transform == 1){
      player[0].x += (float)mouse.dX;
      player[0].y += (float)mouse.dY;
      }
      else if (editor.transform == 0){
      player[0].width += (float)mouse.dX;
      player[0].height += (float)mouse.dY;
      
      if(player[0].width <= 5){
         player[0].width = 5;
      }
      if(player[0].height <= 5){
         player[0].height = 5;
      }
      player[0].Owidth = player[0].width;
      }
      
   }
   else if (editor.typeSelected == 1){
      if(editor.transform == 1){
         platforms[editor.indexSelected].x += mouse.dX;
         platforms[editor.indexSelected].y += mouse.dY; 
      }
      else if (editor.transform == 0){
           platforms[editor.indexSelected].width += mouse.dX;
           platforms[editor.indexSelected].height += mouse.dY; 
      
      if(platforms[editor.indexSelected].width <= 5){
         platforms[editor.indexSelected].width=5;
      }
      if(platforms[editor.indexSelected].height <= 5){
         platforms[editor.indexSelected].height = 5;
      }
      }
      else if (editor.transform == 2){
         platforms[editor.indexSelected].slope += 0.01*mouse.dY; 
         if(platforms[editor.indexSelected].slope > PI/2){
            platforms[editor.indexSelected].slope = PI/2;
         }
         else if (platforms[editor.indexSelected].slope < -PI/2){
             platforms[editor.indexSelected].slope = -PI/2;
         }
      }  
   }
   else if (editor.typeSelected == 2){
      if(editor.transform == 1){
         triggers[editor.indexSelected].x += mouse.dX;
         triggers[editor.indexSelected].y += mouse.dY; 
      }
      else if (editor.transform == 0){
           triggers[editor.indexSelected].width += mouse.dX;
           triggers[editor.indexSelected].height += mouse.dY; 
      
      if(triggers[editor.indexSelected].width <= 5){
         triggers[editor.indexSelected].width=5;
      }
      if(triggers[editor.indexSelected].height <= 5){
         triggers[editor.indexSelected].height = 5;
      }
     } 
   }
   mouse.oldX = mouse.x;
   mouse.oldY = mouse.y;
  }
  if(mouse.right){
    mouse.dX = mouse.x - mouse.oldX;
    mouse.dY = mouse.y - mouse.oldY;
    camera.x += mouse.dX;
    camera.y += mouse.dY;
    mouse.oldX = mouse.x;
    mouse.oldY = mouse.y;
  }
}


void FDrawObjects(){
   player[0].widthDraw = player[0].width;
   player[0].heightDraw = player[0].height;
   player[0].widthDraw  *= camera.scale;
   player[0].heightDraw *= camera.scale;
   player[0].xDraw      *= camera.scale;
   player[0].yDraw      *= camera.scale;

   player[0].xDraw += camera.x;
   player[0].yDraw += camera.y;
   SDL_RenderCopyEx(renderer,tex_player,&(SDL_Rect){2,24,15,18},&(SDL_Rect){player[0].xDraw,player[0].yDraw,player[0].widthDraw,player[0].heightDraw},0,NULL,SDL_FLIP_NONE);


   for (int i = 0;i<sizeof(platforms)/sizeof(platforms[0]);i++){
      if(platforms[i].reserved){
         // Camera offsetted data !
         platforms[i].width  *= camera.scale;
         platforms[i].height *= camera.scale;
         platforms[i].x      *= camera.scale;
         platforms[i].y      *= camera.scale;
         platforms[i].x      += camera.x;
         platforms[i].y      += camera.y;
         SDL_SetRenderDrawColor(renderer,200,200,200,255);
         FtexturePlatform(i);
         if(editor.selected && editor.typeSelected == 1 && editor.indexSelected == i){ 
         SDL_SetRenderDrawColor(renderer,0,255,0,255);
         SDL_RenderDrawRect(renderer,&(SDL_Rect){platforms[editor.indexSelected].x,platforms[editor.indexSelected].y-(platforms[editor.indexSelected].height*sin(platforms[editor.indexSelected].slope))*(platforms[editor.indexSelected].slope>=0),platforms[editor.indexSelected].width,platforms[editor.indexSelected].height+(platforms[editor.indexSelected].height*sin(platforms[editor.indexSelected].slope))*(platforms[editor.indexSelected].slope>=0)});
         }
         // Reset data to normal map data!
         platforms[i].x      -= camera.x;
         platforms[i].y      -= camera.y;
         platforms[i].x      /= camera.scale;
         platforms[i].y      /= camera.scale;
         platforms[i].width  /= camera.scale;
         platforms[i].height /= camera.scale;
         
      }
   }

   for (int i = 0;i<sizeof(triggers)/sizeof(triggers[0]);i++){
      if(triggers[i].reserved){
         // Camera offsetted data !
         triggers[i].width  *= camera.scale;
         triggers[i].height *= camera.scale;
         triggers[i].x      *= camera.scale;
         triggers[i].y      *= camera.scale;
         triggers[i].x      += camera.x;
         triggers[i].y      += camera.y;
         SDL_SetRenderDrawColor(renderer,200,200,200,255);
         SDL_SetTextureAlphaMod(tex_trigger,100);
         for(int j = 0;j<triggers[i].width;j += 25){
            for(int k = 0;k<triggers[i].height;k += 25){
               int u;int v;
               if(j > triggers[i].width-25){u = (-j+triggers[i].width);}
               else{u = 25;}
               if(k > triggers[i].height-25){v = (-k+triggers[i].height);}
               else{v = 25;}
               
               SDL_RenderCopy(renderer,tex_trigger,
               NULL,
               &(SDL_Rect){triggers[i].x+j,triggers[i].y+k,u,v});
            }
         }
         SDL_SetTextureAlphaMod(tex_trigger,255);
         SDL_SetRenderDrawColor(renderer,0,0,0,255);
         SDL_RenderDrawRect(renderer,&(SDL_Rect){triggers[i].x,triggers[i].y,triggers[i].width,triggers[i].height});
         
         if(editor.selected && editor.typeSelected == 2 && editor.indexSelected == i){ 
         SDL_SetRenderDrawColor(renderer,0,255,0,255);
         SDL_RenderDrawRect(renderer,&(SDL_Rect){triggers[editor.indexSelected].x,triggers[editor.indexSelected].y,triggers[editor.indexSelected].width,triggers[editor.indexSelected].height});
         }
         
         // Reset data to normal map data!
         triggers[i].x      -= camera.x;
         triggers[i].y      -= camera.y;
         triggers[i].x      /= camera.scale;
         triggers[i].y      /= camera.scale;
         triggers[i].width  /= camera.scale;
         triggers[i].height /= camera.scale;
         
      }
   }
   if(editor.selected && editor.typeSelected == 0){
      SDL_SetRenderDrawColor(renderer,0,255,0,255);
      SDL_RenderDrawRect(renderer,&(SDL_Rect){player[0].xDraw,player[0].yDraw,player[0].widthDraw,player[0].heightDraw});
   }
   player[0].xDraw = player[0].x;
   player[0].yDraw = player[0].y;
}