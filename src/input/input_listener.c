#define CLEAR_KEY(key) \
   if(key == -1) {key = 0;} \

void clearInputs() {
   if(mouse.left == -1){
      mouse.left = 0;
   }
   if(mouse.right == -1){
      mouse.right = 0;
   }
   mouse.wheel = 0;
   CLEAR_KEY(player[0].keys.up)
   CLEAR_KEY(player[0].keys.down)
   CLEAR_KEY(player[0].keys.left)
   CLEAR_KEY(player[0].keys.right)
   CLEAR_KEY(player[0].keys.e)
   CLEAR_KEY(player[0].keys.enter)
   CLEAR_KEY(player[0].keys.shift)
   CLEAR_KEY(player[0].keys.c)
   CLEAR_KEY(player[0].keys.escape)
   CLEAR_KEY(player[0].keys.r)
}

void FInput_Listener(){
   SDL_Event event;
   player[0].keys.escapeRelease = false;
   mouse.oldX = mouse.x;
   mouse.oldY = mouse.y;

   clearInputs();

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
             player[0].keys.up = 1;
             break;
            case SDLK_SPACE:
            if(!player[0].keys.up){app.inputChange = true;}
             player[0].keys.up = 1;
             break;
            case SDLK_DOWN:
            if(!player[0].keys.down){app.inputChange = true;}
             player[0].keys.down = 1;
             break;
            case SDLK_LEFT:
            if(!player[0].keys.left){app.inputChange = true;}
             player[0].keys.left = 1;
             break;
            case SDLK_RIGHT:
            if(!player[0].keys.right){app.inputChange = true;}
             player[0].keys.right = 1;
             break;
            case SDLK_LSHIFT:
            if(!player[0].keys.shift){app.inputChange = true;}
             player[0].keys.shift = 1;
             break;
            case SDLK_r:
             player[0].keys.r = 1;
             break;
            case SDLK_ESCAPE:
             player[0].keys.escape = 1;
             break;
            case SDLK_c:
             player[0].keys.c = 1;
             break;
            case SDLK_e:
             player[0].keys.e = 1;
             break;
            case 13:
             player[0].keys.enter = 1;
             break;
   
        } 
      }
      if (event.type == SDL_KEYUP){
         app.inputChange = true;
         switch(event.key.keysym.sym){
            case SDLK_UP:
            if(player[0].keys.up){app.inputChange = true;}
             player[0].keys.up = -1;
             break;
            case SDLK_SPACE:
            if(!player[0].keys.up){app.inputChange = true;}
             player[0].keys.up = -1;
             break;
            case SDLK_DOWN:
            if(player[0].keys.down){app.inputChange = true;}
             player[0].keys.down = -1;
             break;
            case SDLK_LEFT:
            if(player[0].keys.left){app.inputChange = true;}
             player[0].keys.left = -1;
             break;
            case SDLK_RIGHT:
            if(player[0].keys.right){app.inputChange = true;}
             player[0].keys.right = -1;
             break;
            case SDLK_LSHIFT:
            if(player[0].keys.shift){app.inputChange = true;}
             player[0].keys.shift = -1;
             break;
            case SDLK_r:
             player[0].keys.r = -1;
             break;
            case SDLK_c:
             player[0].keys.c = -1;
             break;
            case SDLK_e:
             player[0].keys.e = -1;
             break;
            case SDLK_ESCAPE:
             player[0].keys.escape = -1;
             break;
            case 13:
             player[0].keys.enter = -1;
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