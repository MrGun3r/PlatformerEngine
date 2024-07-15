void SetButton(bool reserved,int i,char* Text,double x,double y,int textFont,bool hoverable,int hoverWidth,int hoverHeight,bool highlight){
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
        hoverWidth = buttons[i].textSize*buttons[i].ButtonFontWidth + 10;
    }
    if(hoverHeight < 0){
        hoverHeight = buttons[i].ButtonFontHeight + 5;
    }
    buttons[i].hoverWidth = hoverWidth;
    buttons[i].hoverHeight = hoverHeight;
    buttons[i].reserved = reserved;
    buttons[i].highlight = highlight;
    
}

void SetButtonIcon(int i,SDL_Texture* texture,double u1,double u2,double v1,double v2){
    buttons[i].iconTexture = texture;
    buttons[i].u1 = u1;
    buttons[i].u2 = u2;
    buttons[i].v1 = v1;
    buttons[i].v2 = v2;
}

void ChangeButtonPosition(int i,double x,double y){
    buttons[i].x = x;
    buttons[i].y = y;
}

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

    knobs[i].hoverWidth = len(Text)*textFont;
    knobs[i].hoverHeight = textFont*1.5;


}
void ChangeSliderPosition(int i,double x,double y){
    sliders[i].x = x;
    sliders[i].y = y;
}
void Update_Slider(){
    for(int i = 0;i<sizeof(sliders)/sizeof(sliders[0]);i++){
        if(sliders[i].reserved){
            SDL_itoa(sliders[i].sliderValue,sliders[i].value,10);
            int offset = 0;
            if(sliders[i].iconTexture){
             offset = sliders[i].ButtonFontWidth+sliders[i].textSize*sliders[i].ButtonFontWidth;
            }
            if(mouse.left && mouse.x > sliders[i].x+offset+sliders[i].textSize*sliders[i].ButtonFontWidth-5 && mouse.x < sliders[i].x+offset+sliders[i].textSize*sliders[i].ButtonFontWidth+sliders[i].sliderLength+10  && mouse.y > sliders[i].y && mouse.y < sliders[i].y+20){
                double sliderRatio = (mouse.x - (sliders[i].x+offset+sliders[i].textSize*sliders[i].ButtonFontWidth+5))/sliders[i].sliderLength;
                sliderRatio = min(max(sliderRatio,0),1);
                sliders[i].sliderValue = sliders[i].sliderMinValue*(1-sliderRatio) + sliders[i].sliderMaxValue*sliderRatio;
            }   
        }
    }
}

void Update_Knobs(){
    for(int i = 0;i<sizeof(knobs)/sizeof(knobs[0]);i++){
        if(knobs[i].reserved){
            sprintf(knobs[i].value,"%d\0",(int)knobs[i].knobValue);
            int offset = 0;
            if(mouse.left && mouse.x > knobs[i].x && mouse.x < knobs[i].x+knobs[i].hoverWidth+knobs[i].ButtonFontWidth*len(knobs[i].value) && mouse.y > knobs[i].y && mouse.y < knobs[i].y+knobs[i].hoverHeight){
                knobs[i].knobValue += knobs[i].knobCoef*(mouse.x-mouse.oldX);
                knobs[i].knobValue = min(max(knobs[i].knobValue,knobs[i].knobMin),knobs[i].knobMax);
                break;
            }
        }
    }
}

void Update_TextBox(){
    for(int i = 0;i<sizeof(textbox)/sizeof(textbox[0]);i++){
        if(textbox[i].reserved){

            // Update Blink
            if(i == app.textboxSelected){
               textbox[i].blink += 2*PI*app.deltaTime;
            if(textbox[i].blink>2*PI){textbox[i].blink = 0;} 
            }
            
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


void SetKnobCoef(int i,double Coef){
    knobs[i].knobCoef = Coef;
    return;
}

void SetTextBox(bool reserved,int i,char* textName,double x,double y,double font,double hoverLength){
     textbox[i].reserved = reserved;
     textbox[i].x = x;
     textbox[i].y = y;
     textbox[i].font = font;
     sprintf(textbox[i].textBoxName,"%s\0",textName);
     textbox[i].hoverLength = hoverLength;

}