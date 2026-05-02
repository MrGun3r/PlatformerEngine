////// Buttons

void SetButton(bool reserved,int i,char* Text,double x,double y,int textFont,bool hoverable,int hoverWidth,int hoverHeight,bool highlight,void (*button_func)(void),bool enableTransition){
    buttons[i].iconTexture = NULL;
    buttons[i].x = x;
    buttons[i].y = y;
    buttons[i].text = Text;
    buttons[i].textSize = len(Text);
    buttons[i].ButtonFontHeight = textFont*1.5;
    buttons[i].ButtonFontWidth = textFont;
    buttons[i].hoverOpacity = 0;
    buttons[i].hoverable = true;
    // Fill all text
    if(hoverWidth < 0){
        hoverWidth = (buttons[i].textSize)*buttons[i].ButtonFontWidth + 5*(buttons[i].textSize>0);
    }
    if(hoverHeight < 0){
        hoverHeight = buttons[i].ButtonFontHeight + 5;
    }
    buttons[i].hoverWidth = hoverWidth;
    buttons[i].hoverHeight = hoverHeight;
    buttons[i].reserved = reserved;
    buttons[i].highlight = highlight;

    buttons[i].button_func = button_func;
    buttons[i].transitionEnable = enableTransition;
    
}

void SetButtonIcon(int i,SDL_Texture* texture,double u1,double u2,double v1,double v2){
    buttons[i].iconTexture = texture;
    buttons[i].u1 = u1;
    buttons[i].u2 = u2;
    buttons[i].v1 = v1;
    buttons[i].v2 = v2;
    buttons[i].hoverWidth += buttons[i].ButtonFontWidth + 10;
}

void ChangeButtonPosition(int i,double x,double y){
    buttons[i].x = x;
    buttons[i].y = y;
}

void Update_Buttons() {
    /// Check if escape is pressed , its included as a button
    if(player[0].keys.escape == -1) {
        printf("escape pressed\n");
        if(app.escapeFunction != NULL){
            if(app.transitionEnabled){
                appendTransition(app.escapeFunction);
            }
            else{
                app.escapeFunction();
            }
        }
        return;
    }

    for(int i = 0;i<sizeof(buttons)/sizeof(buttons[0]);i++){
        if(buttons[i].reserved && buttons[i].button_func != NULL){
            int yMin = (buttons[i].y);
            int yMax = (buttons[i].y+buttons[i].hoverHeight);
            int xMin = (buttons[i].x);
            int xMax = (buttons[i].x+buttons[i].hoverWidth);      
            if(mouse.x >= xMin && mouse.x <= xMax && mouse.y >= yMin && mouse.y <= yMax && (mouse.left == -1 || mouse.right == -1)){
                // If we press on a button , call the function that corresponds to it
                app.lastButtonIndex = i;
                if(buttons[i].transitionEnable){
                appendTransition(buttons[i].button_func);
                }
                else{
                    buttons[i].button_func();
                }
                return;
            }
        }
    }
}

void clearButtons() {
    for (int i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++)
    {
        buttons[i].reserved = false;
        buttons[i].highlight = false;
        buttons[i].button_func = NULL;
        sprintf(buttons[i].value, "\0");
    }
}

void GUIHover_Buttons() {
    for(int i = 0;i<sizeof(buttons)/sizeof(buttons[0]);i++){
   if(buttons[i].reserved && buttons[i].hoverable){
      int yMin = (buttons[i].y);
      int yMax = (buttons[i].y+buttons[i].hoverHeight);
      int xMin = (buttons[i].x);
      int xMax = (buttons[i].x+buttons[i].hoverWidth);
      
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
   }  
  }
}

///// -------------------------------------

///// Knobs

void SetKnob(bool reserved,int i,char* Text,double x,double y,int textFont,bool hoverable,double knobMin,double knobMax,double defaultValue){
    knobs[i].reserved = reserved;
    knobs[i].x = x;
    knobs[i].y = y;
    knobs[i].text = Text;
    knobs[i].textSize = len(Text);
    knobs[i].ButtonFontWidth = textFont;
    knobs[i].ButtonFontHeight = textFont*1.5;
    knobs[i].hoverable = true;
    knobs[i].hoverOpacity = 0;
    knobs[i].knobValue = defaultValue;
    knobs[i].knobMin = knobMin;
    knobs[i].knobMax = knobMax;

    knobs[i].hoverWidth = len(Text)*textFont +25;
    knobs[i].hoverHeight = textFont*1.5 + 10;
    SDL_itoa(knobs[i].knobValue,knobs[i].value,10);
}

void ChangeKnobPosition(int i,double x,double y){
    knobs[i].x = x;
    knobs[i].y = y;
}

void SetKnobCoef(int i,double Coef){
    knobs[i].knobCoef = Coef;
    return;
}

void Set_KnobValues(){
    for(int i = 0;i<sizeof(knobs)/sizeof(knobs[0]);i++){
        if(knobs[i].reserved){
            SDL_itoa(knobs[i].knobValue,knobs[i].value,10);
        }
    }
}

void Update_Knobs(){
    if(app.knobTextBoxSelected >= 0){
      app.TextBlink += 2*PI*app.deltaTime;
    if(app.TextBlink>2*PI){app.TextBlink = 0;} 
    }
    // Check whether im clicking on the slider value to modify
    bool knobTextModify = false;
    for(int i = 0;i<sizeof(knobs)/sizeof(knobs[0]);i++){
        if(knobs[i].reserved){
            if(mouse.left && app.knobTextBoxSelected == -1){
                SDL_itoa(knobs[i].knobValue,knobs[i].value,10);
            }
            int offset = 0;
            if(mouse.left == 1 && mouse.x > knobs[i].x && mouse.x < knobs[i].x+knobs[i].hoverWidth+25 && mouse.y > knobs[i].y && mouse.y < knobs[i].y+knobs[i].hoverHeight){
                knobs[i].knobValue += knobs[i].knobCoef*(mouse.x-mouse.oldX);
                knobs[i].knobValue = min(max(knobs[i].knobValue,knobs[i].knobMin),knobs[i].knobMax);
                break;
            }
            else if(mouse.left == -1){
                if (mouse.x > knobs[i].x+knobs[i].hoverWidth && mouse.x < knobs[i].x+knobs[i].hoverWidth+len(knobs[i].value)*knobs[i].ButtonFontWidth && mouse.y > knobs[i].y && mouse.y < knobs[i].y+knobs[i].hoverHeight){
                    app.knobTextBoxSelected = i;
                    knobTextModify = true;        
                }
            } 
        }
    }
    if(mouse.left == -1 && !knobTextModify){
        applyKnobNumBox(app.knobTextBoxSelected);
        app.knobTextBoxSelected = -1;   
    }
}

void GUIHover_Knobs() {
  for(int i = 0;i<sizeof(knobs)/sizeof(knobs[0]);i++){
   if(knobs[i].reserved && knobs[i].hoverable){
      int yMin = (knobs[i].y);
      int yMax = (knobs[i].y+knobs[i].hoverHeight);
      int xMin = (knobs[i].x);
      int xMax = (knobs[i].x+knobs[i].hoverWidth);
     
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
   }
  }
}

///// -------------------------------------

///// Sliders

void SetSlider(bool reserved,int i,char* Text,double x,double y,int textFont,bool hoverable,int hoverWidth,int hoverHeight,bool highlight,double sliderMin,double sliderMax,double sliderLength,double defaultValue){
    sliders[i].iconTexture = NULL;
    sliders[i].x = x;
    sliders[i].y = y;
    sliders[i].text = Text;
    sliders[i].textSize = len(Text);
    sliders[i].ButtonFontHeight = textFont*1.5;
    sliders[i].ButtonFontWidth = textFont;
    sliders[i].hoverOpacity = 0;
    sliders[i].hoverable = true;
    sliders[i].sliderLength = sliderLength;
    sliders[i].sliderMinValue = sliderMin;
    sliders[i].sliderMaxValue = sliderMax;
    sliders[i].sliderValue = defaultValue;
    SDL_itoa(sliders[i].sliderValue,sliders[i].value,10); 
    // Fill all text

    if(hoverWidth < 0){
        hoverWidth = sliders[i].textSize*sliders[i].ButtonFontWidth + 10;
    }
    if(hoverHeight < 0){
        hoverHeight = sliders[i].ButtonFontHeight + 5;
    }
    sliders[i].hoverWidth = hoverWidth;
    sliders[i].hoverHeight = hoverHeight;
    sliders[i].reserved = reserved;
    sliders[i].highlight = highlight;

}

void ChangeSliderPosition(int i,double x,double y){
    sliders[i].x = x;
    sliders[i].y = y;
}

void Set_SlidersValues(){
    for(int i = 0;i<sizeof(sliders)/sizeof(sliders[0]);i++){
        if(sliders[i].reserved){
            SDL_itoa(sliders[i].sliderValue,sliders[i].value,10);
        }
    }
}

void Update_Slider(){
    // Update Blink
    if(app.sliderTextBoxSelected >= 0){
      app.TextBlink += 2*PI*app.deltaTime;
    if(app.TextBlink>2*PI){app.TextBlink = 0;} 
    }
    // Check whether im clicking on the slider value to modify
    bool sliderTextModify = false;

    for(int i = 0;i<sizeof(sliders)/sizeof(sliders[0]);i++){
        if(sliders[i].reserved){
            if(mouse.left && app.knobTextBoxSelected == -1){
                SDL_itoa(sliders[i].sliderValue,sliders[i].value,10);
            }
            int offset = 0;
            if(sliders[i].iconTexture){
                offset = sliders[i].ButtonFontWidth+sliders[i].textSize*sliders[i].ButtonFontWidth;
            }
            if(mouse.left == 1 && mouse.x > sliders[i].x+offset+sliders[i].textSize*sliders[i].ButtonFontWidth-5 && mouse.x < sliders[i].x+offset+sliders[i].textSize*sliders[i].ButtonFontWidth+sliders[i].sliderLength+10  && mouse.y > sliders[i].y && mouse.y < sliders[i].y+20){
                // Change slider value
                if(app.sliderTextBoxSelected != i){
                  SDL_itoa(sliders[i].sliderValue,sliders[i].value,10);
                }
                double sliderRatio = (mouse.x - (sliders[i].x+offset+sliders[i].textSize*sliders[i].ButtonFontWidth+5))/sliders[i].sliderLength;
                sliderRatio = min(max(sliderRatio,0),1);
                sliders[i].sliderValue = sliders[i].sliderMinValue*(1-sliderRatio) + sliders[i].sliderMaxValue*sliderRatio;   
            }
            else if(mouse.left == -1){ 
                if (mouse.y > sliders[i].y && mouse.y < sliders[i].y+20 && mouse.x > sliders[i].x+sliders[i].sliderLength+sliders[i].textSize*sliders[i].ButtonFontWidth ){
                    app.sliderTextBoxSelected = i;
                    sliderTextModify = true;
                }
            }   
        }
    }
    if(mouse.left == -1 && !sliderTextModify){
        applySliderNumBox(app.sliderTextBoxSelected);
        app.sliderTextBoxSelected = -1;   
    }
}

void clearSliders() {
    for (int i = 0; i < sizeof(sliders) / sizeof(sliders[0]); i++)
    {
        sliders[i].reserved = false;
    }
}

void GUIHover_Sliders() {
  for(int i = 0;i<sizeof(sliders)/sizeof(sliders[0]);i++){
   if(sliders[i].reserved && sliders[i].hoverable){
      int yMin = (sliders[i].y);
      int yMax = (sliders[i].y+sliders[i].hoverHeight);
      int xMin = (sliders[i].x);
      int xMax = (sliders[i].x+sliders[i].hoverWidth+sliders[i].sliderLength);
     if(!sliders[i].highlight){
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
   }
  }
}

///// -------------------------------------

///// Textboxes

void SetTextBox(bool reserved,int i,char* textName,double x,double y,double font,double hoverLength){
     textbox[i].reserved = reserved;
     textbox[i].x = x;
     textbox[i].y = y;
     textbox[i].font = font;
     sprintf(textbox[i].textBoxName,"%s\0",textName);
     textbox[i].hoverLength = hoverLength;
}

void Update_TextBox(){
    // Update Blink
    if(app.textboxSelected >= 0){
      app.TextBlink += 2*PI*app.deltaTime;
    if(app.TextBlink>2*PI){app.TextBlink = 0;} 
    }
    for(int i = 0;i<sizeof(textbox)/sizeof(textbox[0]);i++){
        if(textbox[i].reserved){

            
            
           int yMin = textbox[i].y;
           int yMax = textbox[i].y+textbox[i].font*1.5+10;
           int xMin = textbox[i].x;
           int xMax = textbox[i].x+textbox[i].hoverLength;
           if(mouse.left == -1){
            if(mouse.x > xMin && mouse.y > yMin && mouse.x < xMax && mouse.y < yMax){
              app.textboxSelected = i; 
              break; 
            }
            else{
              app.textboxSelected = -1;
            }
           }
        }
    }
}

void clearTextBoxes() {
    for (int i = 0; i < sizeof(textbox) / sizeof(textbox[0]); i++)
    {
        textbox[i].reserved = false;
    }
}

void GUIHover_Textboxes() {
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
   }
  }
}

//// -------------------------------------

////////// -------

void GUIHover(){
    GUIHover_Buttons();
    GUIHover_Sliders();
    GUIHover_Knobs();
    GUIHover_Textboxes();
}

void clearUI() {
    clearButtons();
    clearSliders();
    clearTextBoxes();
}


