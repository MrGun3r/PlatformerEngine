void writeText(SDL_Event* event){
    if(app.textboxSelected >= 0){
       if(event->key.keysym.sym == SDLK_BACKSPACE){
        if(textbox[app.textboxSelected].textContentSize>0){
          textbox[app.textboxSelected].textContentSize--;
          textbox[app.textboxSelected].textContent[textbox[app.textboxSelected].textContentSize] = '\0';
         }  
        }
    else if(((int)event->key.keysym.sym>=97 && (int)event->key.keysym.sym<=122) || (int)event->key.keysym.sym == 32 || ((int)event->key.keysym.sym>=48 && (int)event->key.keysym.sym<=57)){
        if((SDL_GetModState() == KMOD_CAPS || SDL_GetModState() == KMOD_LSHIFT ) && (int)event->key.keysym.sym>=97 && (int)event->key.keysym.sym<=122){
            event->key.keysym.sym -= 32;
        }
        textbox[app.textboxSelected].textContent[textbox[app.textboxSelected].textContentSize] = (char)event->key.keysym.sym;
        textbox[app.textboxSelected].textContentSize++;
        textbox[app.textboxSelected].textContent[textbox[app.textboxSelected].textContentSize] = '\0';
        }
    if((int)event->key.keysym.sym == 13){
        FapplyText();
    } 
  }  
  else if (app.sliderTextBoxSelected >= 0){
        int valueTextSize = len(sliders[app.sliderTextBoxSelected].value);
        if(event->key.keysym.sym == SDLK_BACKSPACE){
          if(valueTextSize>0){
            sliders[app.sliderTextBoxSelected].value[valueTextSize-1] = '\0';
         }  
        }
        else if(((int)event->key.keysym.sym>= 48 && (int)event->key.keysym.sym<=57) ){
         
         sliders[app.sliderTextBoxSelected].value[valueTextSize] = (char)event->key.keysym.sym;
         sliders[app.sliderTextBoxSelected].value[valueTextSize+1] = '\0';
        }
        else if((int)event->key.keysym.sym == SDLK_KP_MINUS){
         sliders[app.sliderTextBoxSelected].value[valueTextSize] = '-';
         sliders[app.sliderTextBoxSelected].value[valueTextSize+1] = '\0';
        }
        if((int)event->key.keysym.sym == 13){
          applySliderNumBox(app.sliderTextBoxSelected);
          app.sliderTextBoxSelected = -1;
        }     
  }
  else if (app.knobTextBoxSelected >= 0){
        int valueTextSize = len(knobs[app.knobTextBoxSelected].value);
        if(event->key.keysym.sym == SDLK_BACKSPACE){
          if(valueTextSize>0){
            knobs[app.knobTextBoxSelected].value[valueTextSize-1] = '\0';
         }  
        }
        else if(((int)event->key.keysym.sym>= 48 && (int)event->key.keysym.sym<=57) ){
         
         knobs[app.knobTextBoxSelected].value[valueTextSize] = (char)event->key.keysym.sym;
         knobs[app.knobTextBoxSelected].value[valueTextSize+1] = '\0';
         
        }
        else if((int)event->key.keysym.sym == SDLK_KP_MINUS){
         knobs[app.knobTextBoxSelected].value[valueTextSize] = '-';
         knobs[app.knobTextBoxSelected].value[valueTextSize+1] = '\0';
        }
        if((int)event->key.keysym.sym == 13){
          applyKnobNumBox(app.knobTextBoxSelected);
          app.knobTextBoxSelected = -1;
        }     
  }
  
}

void applySliderNumBox(int index){
    sliders[index].sliderValue = atof(sliders[index].value);
    if (sliders[index].sliderValue > sliders[index].sliderMaxValue){
        sliders[index].sliderValue = sliders[index].sliderMaxValue;
    }
    else if (sliders[index].sliderValue < sliders[index].sliderMinValue){
        sliders[index].sliderValue = sliders[index].sliderMinValue;
    }
    SDL_itoa(sliders[index].sliderValue,sliders[index].value,10);
}

void applyKnobNumBox(int index){
    knobs[index].knobValue = atof(knobs[index].value);
    if (knobs[index].knobValue > knobs[index].knobMax){
        knobs[index].knobValue = knobs[index].knobMax;
    }
    else if (knobs[index].knobValue < knobs[index].knobMin){
        knobs[index].knobValue = knobs[index].knobMin;
    }
    SDL_itoa(knobs[index].knobValue,knobs[index].value,10);
}

void FapplyText(){
    
    
    // Text Box
    if(app.textboxSelected == 0){
        // editor
       if(app.status == 1){
        if(editor.status == 0){
            // saving map
            FSaveMap(textbox[0].textContent);
            SDL_memcpy(editor.mapName,textbox[0].textContent,len(textbox[0].textContent)+1);
            editor.mapNameSet = true;
            app.textboxSelected = -1;
            editor.status = -1;
            editorShowButtons();
        }
        else if (editor.status == 1){
            // loading map
            char path[256];
            sprintf(path,"levels/%s.txt\0",textbox[0].textContent);
            editor.selected = false;
            editor.typeSelected = 0;
            if(FSetDataMap(path,textbox[0].textContentSize+12) == -1){
              sprintf(editor.alertText,"Cannot find map named: %s",textbox[0].textContent);
              editor.alertTimer = 5000;
              return;
            }
            SDL_memcpy(editor.mapName,textbox[0].textContent,len(textbox[0].textContent)+1);
            editor.mapNameSet = true;
            app.textboxSelected = -1;
            editor.status = -1;
            
            editorShowButtons();
        }
        else if (editor.status == 2){
            sprintf(textpopups[editor.indexSelected].textContent ,textbox[0].textContent,len(textbox[0].textContent));
            editor.status = -1;
            app.textboxSelected = -1;
            editorShowButtons();
        }
      } 
    }   
}