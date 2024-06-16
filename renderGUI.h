
void renderText(int stringCount,char *Text,int x ,int y, int width,int height,int opacity,int shadowOpacity,int color[3]){
  // DEALS WITH TEXT AS WELL AS NUMBERS
  
  char str[stringCount];
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
     if(!buttons[i] .highlight){
      if(mouse.x >= xMin && mouse.x <= xMax && mouse.y >= yMin && mouse.y <= yMax){
         buttons[i].hoverOpacity += 1000*app.deltaTime;
         if(buttons[i].hoverOpacity >= 100){
            buttons[i].hoverOpacity = 100;
         }
      }
      else{
         buttons[i].hoverOpacity -= 1000*app.deltaTime;
         if(buttons[i].hoverOpacity < 0){
            buttons[i].hoverOpacity = 0;
         }
      }
     }
     else{buttons[i].hoverOpacity = 100;}
      
      SDL_SetRenderDrawColor(renderer,255,255,255,(int)(buttons[i].hoverOpacity));
     
      SDL_RenderFillRect(renderer,&(SDL_Rect){buttons[i].x-5,buttons[i].y-5,buttons[i].hoverWidth,buttons[i].hoverHeight});
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
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderDrawRect(renderer,&(SDL_Rect){buttons[i].x,buttons[i].y+2,buttons[i].ButtonFontWidth,buttons[i].ButtonFontWidth});
        offset = buttons[i].ButtonFontWidth + 7;
      }
      renderText(buttons[i].textSize,buttons[i].text,buttons[i].x+offset,buttons[i].y,buttons[i].textSize*buttons[i].ButtonFontWidth,buttons[i].ButtonFontHeight,255,200,(int[3]){255,255,255});
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
   
      SDL_SetRenderDrawColor(renderer,200,200,200,255);
      SDL_RenderFillRect(renderer,&(SDL_Rect){(int)sliders[i].x+offset+sliders[i].textSize*sliders[i].ButtonFontWidth+5,(int)sliders[i].y+sliders[i].ButtonFontHeight/3,(int)sliders[i].sliderLength,5});
      
      SDL_SetRenderDrawColor(renderer,100,100,255,255);
      SDL_RenderFillRect(renderer,&(SDL_Rect){(int)sliders[i].x+offset+sliders[i].textSize*sliders[i].ButtonFontWidth+sliders[i].sliderLength*(sliders[i].sliderValue-sliders[i].sliderMinValue)/(sliders[i].sliderMaxValue-sliders[i].sliderMinValue) + 2.5,(int)sliders[i].y+sliders[i].ButtonFontHeight/3-2,5,9});
    }
  }
}