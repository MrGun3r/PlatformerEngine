#define SET_INFO_TEXT(obj,idx,label) \
      sprintf(Xvalue,"x:%d\0",(int)obj[idx].x); \
      sprintf(Yvalue,"y:%d\0",(int)obj[idx].y); \
      sprintf(Widthvalue,"width:%d\0",(int)obj[idx].width); \
      sprintf(Heightvalue,"height:%d\0",(int)obj[idx].height); \
      sprintf(upperText,"%s %d\0",(label),idx);
   

void Editor_DrawInfoBox(){
   char* infoText = malloc(100);
   for(int i = 0;i<sizeof(buttons)/sizeof(buttons[0]);i++){
    if(buttons[i].reserved && buttons[i].hoverOpacity>1 && !buttons[i].highlight){
       SDL_memcpy(infoText,infoTextMessages[i],len(&infoTextMessages[i][0])+1);     
      renderText(len(infoText),infoText,gameWidthBase-190,gameHeightBase-16,7*len(infoText),10,255,200,(int[3]){200,200,200});
      free(infoText);
      return;
    }
   }
   for(int i = 0;i<sizeof(knobs)/sizeof(knobs[0]);i++){
      if(knobs[i].reserved && knobs[i].hoverOpacity>1){
      SDL_memcpy(infoText,knobInfoText[i],len(&knobInfoText[i][0])+1); 
      renderText(len(infoText),infoText,gameWidthBase-190,gameHeightBase-16,7*len(infoText),10,255,200,(int[3]){200,200,200});
      free(infoText);
      return;
      }
   }
   for(int i = 0 ;i<sizeof(sliders)/sizeof(sliders[0]);i++){
      if(sliders[i].reserved && sliders[i].hoverOpacity>1 && !sliders[i].highlight){
       SDL_memcpy(infoText,sliderInfoText[i],len(&sliderInfoText[i][0]) +1 );
      renderText(len(infoText),infoText,gameWidthBase-190,gameHeightBase-16,7*len(infoText),10,255,200,(int[3]){200,200,200});
      free(infoText);
      return;
      }
   }
}
void Editor_renderCameraInfo() {
   
   char posX[10]; 
   char posY[10];
   char CameraposX[15]; 
   char CameraposY[15];
   char CameraScale[15];
   sprintf(posX,"X:%d\0",(int)editor.mouseProjected[0]);
   sprintf(posY,"Y:%d\0",(int)editor.mouseProjected[1]);
   sprintf(CameraposX,"Cam X:%d\0",(int)-camera.x);
   sprintf(CameraposY,"Y:%d\0",(int)-camera.y);
   sprintf(CameraScale,"%d\0",(int)(camera.scale*100));
  
   renderText(len(posX),posX,5,gameHeightBase-14,len(posX)*7,15,255,200,(int[3]){255,255,255});
   renderText(len(posY),posY,len(posX)*7+15,gameHeightBase-14,len(posY)*7,15,255,200,(int[3]){255,255,255});
   renderText(len(CameraposX),CameraposX,5,gameHeightBase-30,len(CameraposX)*7,15,255,200,(int[3]){255,255,255});
   renderText(len(CameraposY),CameraposY,len(CameraposX)*7+15,gameHeightBase-30,len(CameraposY)*7,15,255,200,(int[3]){255,255,255});
   renderText(len(CameraScale),CameraScale,gameWidthBase-240,gameHeightBase-30,len(CameraposY)*7,15,255,200,(int[3]){255,255,255});
   // Render alert text
   if(editor.alertTimer > 0){
      int TextLength = len(editor.alertText);
      renderText(TextLength,editor.alertText,5,60,TextLength*12,17,255,255,(int[3]){255,255,255});
   }
}
void Editor_Draw_ObjectInfo(){
   // draw info box
   Editor_DrawInfoBox();

   if(editor.selected){
   // Info texts that will be drawn (x , y , width , height , top text)
   char* Xvalue = malloc(256);
   char* Yvalue = malloc(256);
   char* Widthvalue = malloc(256);
   char* Heightvalue = malloc(256);
   char* upperText = malloc(256);
   
   int idx = editor.indexSelected;

   switch (editor.typeSelected)
   {
      case PLAYER:  
         SET_INFO_TEXT(player, 0, "Player");       
         break;
      case PLATFORM:
         SET_INFO_TEXT(platforms, idx, "Platform");
         break;
      case TRIGGER:  
         SET_INFO_TEXT(triggers, idx, "Trigger");      
         break;
      case LIGHT:  
         SET_INFO_TEXT(light, idx, "Light");        
         break;
      case DISPLACEMENT:  
         SET_INFO_TEXT(displacement, idx, "Displacement"); 
         break;
      case DEATHBOX:  
         SET_INFO_TEXT(deathbox, idx, "DeathBox");     
         break;
      case SCRIPT:  
         SET_INFO_TEXT(scripts, idx, "Script");       
         break;
      case ENEMY:  
         SET_INFO_TEXT(enemy, idx, "Enemy");        
         break;
      case SPECIAL:  
         SET_INFO_TEXT(specials, idx, "Special");      
         break;
      case TEXTPOPUP: 
         SET_INFO_TEXT(textpopups, idx, "Text");         
         break;

      case MOVENODE:
        sprintf(Xvalue, "x:%d", (int)movenodes[idx].positions[editor.movenodeSelected][0]);
        sprintf(Yvalue, "y:%d", (int)movenodes[idx].positions[editor.movenodeSelected][1]);
        sprintf(Widthvalue, "size:%d", 25);
        sprintf(Heightvalue, "Node ID:%d", idx);
        sprintf(upperText, "Move Node %d", editor.movenodeSelected);
        break;
   }

   /// Draw the text info
   if(editor.typeSelected != NONE){
      renderText(len(Xvalue),Xvalue,gameWidthBase-190,100,len(Xvalue)*10,15,255,200,(int[3]){255,255,255});
      renderText(len(Yvalue),Yvalue,gameWidthBase-190,120,len(Yvalue)*10,15,255,200,(int[3]){255,255,255});
      renderText(len(Widthvalue),Widthvalue,gameWidthBase-190,140,len(Widthvalue)*10,15,255,200,(int[3]){255,255,255});
      renderText(len(Heightvalue),Heightvalue,gameWidthBase-190,160,len(Heightvalue)*10,15,255,200,(int[3]){255,255,255});
      renderText(len(upperText),upperText,gameWidthBase-100-len(upperText)*6,10,len(upperText)*12,15,255,200,(int[3]){255,255,255});
   }

   free(upperText);
   free(Xvalue);
   free(Yvalue);
   free(Heightvalue);
   free(Widthvalue);
  }
}