
void renderText(int stringCount,char *Text,int x ,int y, int width,int height,int opacity,int shadowOpacity,int color[3]){
  // DEALS WITH TEXT AS WELL AS NUMBERS
  
  char str[stringCount+1];
  for(int i = 0;i<stringCount;i++){
    str[i] = *(Text+i);
  }
  int posX;
  int cap;
  int num;
  // OUTLINE --> TEXT (order of rendering)   
  int outLineOffset = 2;
    // {text}
  
  for (int i = 0;i<stringCount;i++){
      cap = 0;
      num = 0;
      int charValue = str[i] - 'a';
      if (str[i]>=65 && str[i]<=90){
        cap = 1;
        num = 0;
        charValue += 32;
      }
      else if (str[i]>= 43 && str[i]<= 58){
        num = 1;
        cap = 0;
        charValue += 54;
      }
      posX = charValue*40;
     
    SDL_SetTextureAlphaMod(tex_font,max(0,shadowOpacity));
    SDL_SetTextureColorMod( tex_font, 0,0,0);
    SDL_RenderCopy(renderer,tex_font,&(SDL_Rect){posX,80*cap+150*num,40,70-(6*cap)}
                                    ,&(SDL_Rect){x-outLineOffset+i*(width/stringCount),y-outLineOffset,width/stringCount,height});
    SDL_SetTextureAlphaMod(tex_font,opacity); 
    SDL_SetTextureColorMod( tex_font, color[0],color[1],color[2]);
    SDL_RenderCopy(renderer,tex_font,&(SDL_Rect){posX,80*cap+150*num,40,70-(6*cap)}
                                    ,&(SDL_Rect){x+i*(width/stringCount),y,width/stringCount,height});
   } 
    SDL_SetTextureAlphaMod(tex_font,255);
}
void FGUIHover(){
  for(int i = 0;i<sizeof(buttons)/sizeof(buttons[0]);i++){
   if(buttons[i].reserved && buttons[i].hoverable){
      int yMin = buttons[i].y;
      int yMax = buttons[i].y+buttons[i].hoverHeight;
      int xMin = buttons[i].x;
      int xMax = buttons[i].x+buttons[i].hoverWidth;
      
     if(!buttons[i].highlight){
      if(mouse.x >= xMin && mouse.x <= xMax && mouse.y >= yMin && mouse.y <= yMax){
         buttons[i].hoverOpacity += 1000*app.deltaTime;
         if(buttons[i].hoverOpacity >= 100){
            buttons[i].hoverOpacity = 100;
         }
         if(buttons[i].hoverSound){
              Mix_PlayChannel(-1,Sound_Hover,0);
              buttons[i].hoverSound = false;
         }
      }
      else{
         buttons[i].hoverOpacity -= 1000*app.deltaTime;
         buttons[i].hoverSound = true;
         if(buttons[i].hoverOpacity < 0){
            buttons[i].hoverOpacity = 0;
         }
      }
     }
     else{buttons[i].hoverOpacity = 100;}
      
      SDL_SetRenderDrawColor(renderer,255,255,255,(int)(buttons[i].hoverOpacity));
     
      SDL_RenderFillRect(renderer,&(SDL_Rect){buttons[i].x-5,buttons[i].y-5,(buttons[i].hoverWidth),buttons[i].hoverHeight});
      
   }  
  }

  for(int i = 0;i<sizeof(sliders)/sizeof(sliders[0]);i++){
   if(sliders[i].reserved && sliders[i].hoverable){
      int yMin = sliders[i].y;
      int yMax = sliders[i].y+sliders[i].hoverHeight;
      int xMin = sliders[i].x;
      int xMax = sliders[i].x+sliders[i].hoverWidth+sliders[i].sliderLength+10;
     if(!sliders[i] .highlight){
      if(mouse.x >= xMin && mouse.x <= xMax && mouse.y >= yMin && mouse.y <= yMax){
         sliders[i].hoverOpacity += 1000*app.deltaTime;
         if(sliders[i].hoverOpacity >= 100){
            sliders[i].hoverOpacity = 100;
         }
      }
      else{
         sliders[i].hoverOpacity -= 1000*app.deltaTime;
         if(sliders[i].hoverOpacity < 0){
            sliders[i].hoverOpacity = 0;
         }
      }
     }
     else{sliders[i].hoverOpacity = 100;}
      
      SDL_SetRenderDrawColor(renderer,255,255,255,(int)(sliders[i].hoverOpacity));
     
      SDL_RenderFillRect(renderer,&(SDL_Rect){sliders[i].x-5,sliders[i].y-5,sliders[i].hoverWidth+sliders[i].sliderLength+10,sliders[i].hoverHeight});
   }
  }

  for(int i = 0;i<sizeof(knobs)/sizeof(knobs[0]);i++){
   if(knobs[i].reserved && knobs[i].hoverable){
      int yMin = knobs[i].y;
      int yMax = knobs[i].y+knobs[i].hoverHeight+10;
      int xMin = knobs[i].x;
      int xMax = knobs[i].x+knobs[i].hoverWidth+knobs[i].ButtonFontWidth*len(knobs[i].value)+30;
     
      if(mouse.x >= xMin && mouse.x <= xMax && mouse.y >= yMin && mouse.y <= yMax){
         knobs[i].hoverOpacity += 1000*app.deltaTime;
         if(knobs[i].hoverOpacity >= 100){
            knobs[i].hoverOpacity = 100;
         }
        
      }
      else{
         knobs[i].hoverOpacity -= 1000*app.deltaTime;
         if(knobs[i].hoverOpacity < 0){
            knobs[i].hoverOpacity = 0;
         }
      }
      
      SDL_SetRenderDrawColor(renderer,255,255,255,(int)(knobs[i].hoverOpacity));
     
      SDL_RenderFillRect(renderer,&(SDL_Rect){knobs[i].x-5,knobs[i].y-5,knobs[i].hoverWidth+knobs[i].ButtonFontWidth*len(knobs[i].value)+30,knobs[i].hoverHeight+10});
   }
  }
  for(int i = 0;i<sizeof(textbox)/sizeof(textbox[0]);i++){
   if(textbox[i].reserved){
      int yMin = textbox[i].y;
      int yMax = textbox[i].y+textbox[i].font*1.5+10;
      int xMin = textbox[i].x;
      int xMax = textbox[i].x+textbox[i].hoverLength;
      
      if(i == app.textboxSelected){
        textbox[i].hoverOpacity = 100;
      }

      else if(mouse.x >= xMin && mouse.x <= xMax && mouse.y >= yMin && mouse.y <= yMax){
         textbox[i].hoverOpacity += 1000*app.deltaTime;
         if(textbox[i].hoverOpacity >= 100){
            textbox[i].hoverOpacity = 100;
         }
        
      }
      else{
         textbox[i].hoverOpacity -= 1000*app.deltaTime;
         if(textbox[i].hoverOpacity < 0){
            textbox[i].hoverOpacity = 0;
         }
      }
      
      SDL_SetRenderDrawColor(renderer,255,255,255,(int)(textbox[i].hoverOpacity));
     
      SDL_RenderFillRect(renderer,&(SDL_Rect){textbox[i].x-5,textbox[i].y-5,textbox[i].hoverLength,textbox[i].font*1.5+10});
      if(i == app.textboxSelected){
        renderText(1,"-",textbox[i].x+(len(textbox[i].textBoxName)+textbox[i].textContentSize)*textbox[i].font+5,textbox[i].y+5,12,15,255*(1+sin(textbox[i].blink))/2,255*(1+sin(textbox[i].blink))/2,(int[3]){255,255,255});
      }
   }
  }
}

void renderButtons(){
  for(int i = 0;i<sizeof(buttons)/sizeof(buttons[0]);i++){
    if(buttons[i].reserved){
      int offset = 0;
      if(buttons[i].iconTexture != NULL){
        SDL_Vertex vertices[] = 
          {
          {{buttons[i].x, buttons[i].y+2}, {255, 255, 255, 255}, {buttons[i].u1, buttons[i].v1}},
          {{buttons[i].x+buttons[i].ButtonFontWidth, buttons[i].y+2}, {255, 255, 255, 255}, {buttons[i].u2, buttons[i].v1}},
          {{buttons[i].x+buttons[i].ButtonFontWidth, buttons[i].y+2+buttons[i].ButtonFontWidth}, {255, 255, 255, 255}, {buttons[i].u2, buttons[i].v2}},
          {{buttons[i].x, buttons[i].y+buttons[i].ButtonFontWidth+2}, {255, 255, 255, 255}, {buttons[i].u1, buttons[i].v2}}
          };
          
        SDL_RenderGeometry(renderer, buttons[i].iconTexture,vertices, 4, (int[6]){1,2,3,0,1,3}, 6);
        //SDL_SetRenderDrawColor(renderer,0,0,0,255);
        //SDL_RenderDrawRect(renderer,&(SDL_Rect){buttons[i].x,buttons[i].y+2,buttons[i].ButtonFontWidth,buttons[i].ButtonFontWidth});
        offset = buttons[i].ButtonFontWidth + 7;
      }
      renderText(buttons[i].textSize,buttons[i].text,buttons[i].x+offset,buttons[i].y,buttons[i].textSize*buttons[i].ButtonFontWidth,buttons[i].ButtonFontHeight,255,200,(int[3]){255,255,255});
      renderText(len(buttons[i].value),buttons[i].value,buttons[i].x+offset+5+buttons[i].textSize*buttons[i].ButtonFontWidth,buttons[i].y,len(buttons[i].value)*buttons[i].ButtonFontWidth,buttons[i].ButtonFontHeight,255,200,(int[3]){255,255,255});
    }
  }
}

void renderSliders(){
  for(int i = 0;i<sizeof(sliders)/sizeof(sliders[0]);i++){
    if(sliders[i].reserved){
      int offset = 0;
      if(sliders[i].iconTexture != NULL){
        SDL_Vertex vertices[] = 
          {
          {{sliders[i].x, sliders[i].y+2}, {255, 255, 255, 255}, {sliders[i].u1, sliders[i].v1}},
          {{sliders[i].x+sliders[i].ButtonFontWidth, sliders[i].y+2}, {255, 255, 255, 255}, {sliders[i].u2, sliders[i].v1}},
          {{sliders[i].x+sliders[i].ButtonFontWidth, sliders[i].y+2+sliders[i].ButtonFontWidth}, {255, 255, 255, 255}, {sliders[i].u2, sliders[i].v2}},
          {{sliders[i].x, sliders[i].y+sliders[i].ButtonFontWidth+2}, {255, 255, 255, 255}, {sliders[i].u1, sliders[i].v2}}
          };
          
        SDL_RenderGeometry(renderer, sliders[i].iconTexture,vertices, 4, (int[6]){1,2,3,0,1,3}, 6);
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderDrawRect(renderer,&(SDL_Rect){sliders[i].x,sliders[i].y+2,sliders[i].ButtonFontWidth,sliders[i].ButtonFontWidth});
        offset = sliders[i].ButtonFontWidth + 10;
      }

      renderText(sliders[i].textSize,sliders[i].text,(int)sliders[i].x+offset,sliders[i].y,sliders[i].textSize*sliders[i].ButtonFontWidth,sliders[i].ButtonFontHeight,255,200,(int[3]){255,255,255});

      renderText(len(sliders[i].value),sliders[i].value,sliders[i].x+offset+10+sliders[i].textSize*sliders[i].ButtonFontWidth + sliders[i].sliderLength,sliders[i].y,len(sliders[i].value)*sliders[i].ButtonFontWidth,sliders[i].ButtonFontHeight,255,200,(int[3]){255,255,255});

      SDL_SetRenderDrawColor(renderer,200,200,200,255);

      SDL_RenderFillRect(renderer,&(SDL_Rect){(int)sliders[i].x+offset+sliders[i].textSize*sliders[i].ButtonFontWidth+5,(int)sliders[i].y+sliders[i].ButtonFontHeight/3,(int)sliders[i].sliderLength,5});
      
      SDL_SetRenderDrawColor(renderer,100,100,255,255);
      SDL_RenderFillRect(renderer,&(SDL_Rect){(int)sliders[i].x+offset+sliders[i].textSize*sliders[i].ButtonFontWidth+sliders[i].sliderLength*(sliders[i].sliderValue-sliders[i].sliderMinValue)/(sliders[i].sliderMaxValue-sliders[i].sliderMinValue) + 2.5,(int)sliders[i].y+sliders[i].ButtonFontHeight/3-2,5,9});
    }
  }
}

void renderKnobs(){
  for(int i = 0;i<sizeof(knobs)/sizeof(knobs[0]);i++){
    if(knobs[i].reserved){
      int offset = 0;
      if(knobs[i].iconTexture != NULL){
        SDL_Vertex vertices[] = 
          {
          {{knobs[i].x, knobs[i].y+2}, {255, 255, 255, 255}, {knobs[i].u1, knobs[i].v1}},
          {{knobs[i].x+knobs[i].ButtonFontWidth, knobs[i].y+2}, {255, 255, 255, 255}, {knobs[i].u2, knobs[i].v1}},
          {{knobs[i].x+knobs[i].ButtonFontWidth, knobs[i].y+2+knobs[i].ButtonFontWidth}, {255, 255, 255, 255}, {knobs[i].u2, knobs[i].v2}},
          {{knobs[i].x, knobs[i].y+knobs[i].ButtonFontWidth+2}, {255, 255, 255, 255}, {knobs[i].u1, knobs[i].v2}}
          };
          
        SDL_RenderGeometry(renderer, knobs[i].iconTexture,vertices, 4, (int[6]){1,2,3,0,1,3}, 6);
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderDrawRect(renderer,&(SDL_Rect){knobs[i].x,knobs[i].y+2,knobs[i].ButtonFontWidth,knobs[i].ButtonFontWidth});
        offset = knobs[i].ButtonFontWidth + 7;
      }
      renderText(knobs[i].textSize,knobs[i].text,knobs[i].x+offset,knobs[i].y,knobs[i].textSize*knobs[i].ButtonFontWidth,knobs[i].ButtonFontHeight,255,200,(int[3]){255,255,255});

      renderText(len(knobs[i].value),knobs[i].value,knobs[i].x+offset+25+knobs[i].textSize*knobs[i].ButtonFontWidth,knobs[i].y,len(knobs[i].value)*knobs[i].ButtonFontWidth,knobs[i].ButtonFontHeight,255,200,(int[3]){255,255,255});
    }
  }
}



void renderTextBox(){
  for(int i = 0;i<sizeof(textbox)/sizeof(textbox[0]);i++){
    if(textbox[i].reserved){
      renderText(len(textbox[i].textBoxName),textbox[i].textBoxName,textbox[i].x,textbox[i].y,len(textbox[i].textBoxName)*textbox[i].font,textbox[i].font*1.5,255,200,(int[3]){255,255,255});
      renderText(len(textbox[i].textContent),textbox[i].textContent,textbox[i].x+len(textbox[i].textBoxName)*textbox[i].font,textbox[i].y,len(textbox[i].textContent)*textbox[i].font,textbox[i].font*1.5,255,200,(int[3]){255,255,255});
    }
  }
}