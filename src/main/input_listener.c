void FInput_Listener(){
   SDL_Event event;
   player[0].keys.escapeRelease = false;
   mouse.oldX = mouse.x;
   mouse.oldY = mouse.y;
   if(mouse.left == -1){
      mouse.left = 0;
   }
   if(mouse.right == -1){
      mouse.right = 0;
   }
   mouse.wheel = 0;

   while(SDL_PollEvent(&event)){
      // Quit
      if (event.type == SDL_QUIT){
         app.WINDOW_LOOP = false;
      }
      if(event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED){
            FwindowResize();
      }
      if(event.type == SDL_MOUSEMOTION){
      int windowGameHeight = ((double)gameHeight/(double)gameWidth)*windowWidth;
      
       SDL_GetMouseState(&mouse.x,&mouse.y);
       mouse.y -= (windowHeight-windowGameHeight)/2*(windowHeight>windowGameHeight);
       mouse.x *= (double)(gameWidth)/(double)(windowWidth);
       mouse.y *= (double)(gameHeight)/(double)(windowHeight - (windowHeight-windowGameHeight)*(windowHeight>windowGameHeight));
       
       /// Mouse.x and Mouse.y will be between 0 and base res (0 -> 1028)
       mouse.x /= windowWidthScale;
       mouse.y /= windowHeightScale; 


      }
      if(app.transition){
         return;
      }
      if(event.type == SDL_MOUSEWHEEL){
         mouse.wheel = event.wheel.y;
      }
      if (event.type == SDL_KEYDOWN){
         writeText(&event);
         switch(event.key.keysym.sym){
            case SDLK_UP:
            if(!player[0].keys.up){app.inputChange = true;}
             player[0].keys.up = true;
             break;
            case SDLK_SPACE:
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
            case SDLK_c:
             player[0].keys.c = true;
             break;
            case SDLK_e:
             player[0].keys.e = true;
             break;
            case 13:
             player[0].keys.enter = true;
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
            case SDLK_SPACE:
            if(!player[0].keys.up){app.inputChange = true;}
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
            case SDLK_c:
             player[0].keys.c = false;
             break;
            case SDLK_e:
             player[0].keys.e = false;
             break;
            case SDLK_ESCAPE:
             app.textboxSelected = -1;
             player[0].keys.escape = false;
             if(app.status == 0){ 
                  level.Paused = !level.Paused;
             }
             else if(app.status == 1){
               if(editor.status >= 0){
                  editor.status = -1;
               }
               else {
                  appendTransition(app.status,4);
               }
               editorShowButtons();
             }
             else if(app.status == 2){
               FswitchAppStatus(app.status,7);
               app.fetchedList = false;
             }
             else if (app.status == 6){
               FswitchAppStatus(app.status,4);
               app.resolutionInt = app.resolutionUsed;
             }
             else if(app.status == 7){
               FswitchAppStatus(app.status,4);
             }
             else if(app.status == 8){
               appendTransition(app.status,7);
             }
             break;
            case 13:
             player[0].keys.enter = false;
             break;
        } 
      }
      if(event.type == SDL_MOUSEBUTTONDOWN){
         if(event.button.button == SDL_BUTTON_LEFT){
            mouse.left = 1;
         }
         else if(event.button.button == SDL_BUTTON_RIGHT){
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
      
   }
}