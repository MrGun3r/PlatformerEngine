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
      if(editor.typing){
         if(event.key.keysym.sym == SDLK_BACKSPACE){
            if(editor.fileNameSize>0){
            editor.fileNameSize--;
            editor.fileNameSave[editor.fileNameSize] = '\0';
            }  
         }
         else if((int)event.key.keysym.sym>=32){
          editor.fileNameSave[editor.fileNameSize] = (char)event.key.keysym.sym;
          editor.fileNameSize++;
          editor.fileNameSave[editor.fileNameSize] = '\0';
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
          if(app.status == 1){
            if(editor.typing){
               editor.typing = false;
            }
            else{
               appendTransition(app.status,4);
            }
          }
          if(app.status == 2){
            FswitchAppStatus(app.status,4);
            app.fetchedList = false;
          }
          break;
     } 
   }
   if(event.type == SDL_MOUSEMOTION){
    SDL_GetMouseState(&mouse.x,&mouse.y);
    if(!mouse.right && !mouse.left){
      SDL_GetMouseState(&mouse.oldX,&mouse.oldY);
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
   if(event.type == SDL_MOUSEWHEEL){
      mouse.wheel = event.wheel.y;
   }
   else {
      mouse.wheel = 0;
   }
}