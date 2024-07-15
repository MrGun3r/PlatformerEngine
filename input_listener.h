void FInput_Listener(){
   SDL_Event event;
   SDL_PollEvent(&event);
   player[0].keys.escapeRelease = false;
   if (event.type == SDL_QUIT){
      app.WINDOW_LOOP = false;
   }
   if(event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED){
         FwindowResize();
   }
   if (event.type == SDL_KEYDOWN){
      if(app.textboxSelected >= 0){
         if(event.key.keysym.sym == SDLK_BACKSPACE){
            if(textbox[app.textboxSelected].textContentSize>0){
            textbox[app.textboxSelected].textContentSize--;
            textbox[app.textboxSelected].textContent[textbox[app.textboxSelected].textContentSize] = '\0';
            }  
         }
         else if((int)event.key.keysym.sym>=32){
          textbox[app.textboxSelected].textContent[textbox[app.textboxSelected].textContentSize] = (char)event.key.keysym.sym;
          textbox[app.textboxSelected].textContentSize++;
          textbox[app.textboxSelected].textContent[textbox[app.textboxSelected].textContentSize] = '\0';
      }
      if((int)event.key.keysym.sym == 13){
            FapplyText();
           } 
      }
      switch(event.key.keysym.sym){
         case SDLK_UP:
         if(!player[0].keys.up){app.inputChange = true;}
          player[0].keys.up = true;
          break;
         case SDLK_DOWN:
         if(!player[0].keys.down){app.inputChange = true;}
          player[0].keys.down = true;
          break;
         case SDLK_LEFT:
         if(!player[0].keys.left){app.inputChange = true;}
          player[0].keys.left = true;
          break;
         case SDLK_RIGHT:
         if(!player[0].keys.right){app.inputChange = true;}
          player[0].keys.right = true;
          break;
         case SDLK_LSHIFT:
         if(!player[0].keys.shift){app.inputChange = true;}
          player[0].keys.shift = true;
          break;
         case SDLK_r:
          player[0].keys.r = true;
          break;
         case SDLK_ESCAPE:
          player[0].keys.escape = true;
          break;
     } 
   }
   if (event.type == SDL_KEYUP){
      app.inputChange = true;
      switch(event.key.keysym.sym){
         case SDLK_UP:
         if(player[0].keys.up){app.inputChange = true;}
          player[0].keys.up = false;
          break;
         case SDLK_DOWN:
         if(player[0].keys.down){app.inputChange = true;}
          player[0].keys.down = false;
          break;
         case SDLK_LEFT:
         if(player[0].keys.left){app.inputChange = true;}
          player[0].keys.left = false;
          break;
         case SDLK_RIGHT:
         if(player[0].keys.right){app.inputChange = true;}
          player[0].keys.right = false;
          break;
         case SDLK_LSHIFT:
         if(player[0].keys.shift){app.inputChange = true;}
          player[0].keys.shift = false;
          break;
         case SDLK_r:
          player[0].keys.r = false;
          break;
         case SDLK_ESCAPE:
          player[0].keys.escape = false;
          if(app.status == 0){ 
               appendTransition(app.status,4);
          }
          else if(app.status == 1){
            if(editor.status >= 0){
               editor.status = -1;
            }
            else {
               appendTransition(app.status,4);
            }
               
          }
          else if(app.status == 2){
            FswitchAppStatus(app.status,4);
            app.fetchedList = false;
          }
          break;
     } 
   }
   if(mouse.left == -1){
      mouse.left = 0;
   }
   if(mouse.right == -1){
      mouse.right = 0;
   }
   if(event.type == SDL_MOUSEBUTTONDOWN){
      if(event.button.button == SDL_BUTTON_LEFT){
         mouse.left = 1;
      }
      else if(event.button.button == SDL_BUTTON_RIGHT){
         mouse.right = 1;
      }
   }
   if(event.type == SDL_MOUSEBUTTONDOWN){
      if(event.button.button == SDL_BUTTON_LEFT){
         mouse.left = 1;
      }
      if(event.button.button == SDL_BUTTON_RIGHT){
         mouse.right = 1;
      }
   }
   if(event.type == SDL_MOUSEBUTTONUP){
      if(event.button.button == SDL_BUTTON_LEFT){
         mouse.left = -1;
      }
      if(event.button.button == SDL_BUTTON_RIGHT){
         mouse.right = -1;
      }
   }
   // Mouse Handling
   mouse.oldX = mouse.x;
   mouse.oldY = mouse.y;
   if(event.type == SDL_MOUSEMOTION){
   int windowGameHeight = ((double)gameHeight/(double)gameWidth)*windowWidth;
   
    SDL_GetMouseState(&mouse.x,&mouse.y);
    mouse.y -= (windowHeight-windowGameHeight)/2*(windowHeight>windowGameHeight);
    mouse.x *= (double)(gameWidth)/(double)(windowWidth);
    mouse.y *= (double)(gameHeight)/(double)(windowHeight - (windowHeight-windowGameHeight)*(windowHeight>windowGameHeight));
    
   }
   if(event.type == SDL_MOUSEWHEEL){
      mouse.wheel = event.wheel.y;
   }
   else {
      mouse.wheel = 0;
   }
}