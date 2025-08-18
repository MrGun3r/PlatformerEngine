void FTransformState(){
   if(mouse.left == 1 && editor.selected && !((mouse.y <= 100 && mouse.x > 0 && mouse.x < gameWidth-200) || (mouse.x > gameWidth-200))){
     mouse.dX = mouse.x - mouse.oldX;
     mouse.dY = mouse.y - mouse.oldY;
   if(SDL_abs(mouse.dX) >= 5*app.deltaTime || SDL_abs(mouse.dY) >= 5*app.deltaTime){
      editor.unSelect = false;
   }
   else{
      return;
   }
   
   if(editor.typeSelected == 0){
      if(editor.transform == 2){
         editor.transform = 1;
         buttons[1].highlight = true;
         buttons[2].highlight = false;
         buttons[4].highlight = false;
      }
      if(editor.transform == 1){
      resizeObject(&player[0].x,&player[0].y);
      }
      else if (editor.transform == 0){
      resizeObject(&player[0].width,NULL);
      CLAMP_MIN(player[0].width,5);
      player[0].height = player[0].width*10/9;
      player[0].Owidth = player[0].width;
      }   
   }
   else if (editor.typeSelected == 1){
      if(editor.transform == 1){
         resizeObject(&platforms[editor.indexSelected].x,&platforms[editor.indexSelected].y);
      }
      else if (editor.transform == 0){
         resizeObject(&platforms[editor.indexSelected].width,&platforms[editor.indexSelected].height);

      CLAMP_MINMAX(platforms[editor.indexSelected].width,5,1500);
      CLAMP_MINMAX(platforms[editor.indexSelected].height,5,1500);

      }
   }
   else if (editor.typeSelected == 2){
      if(editor.transform == 1){
        resizeObject(&triggers[editor.indexSelected].x,&triggers[editor.indexSelected].y);
      }
      else if (editor.transform == 0){
        resizeObject(&triggers[editor.indexSelected].width,&triggers[editor.indexSelected].height);
      CLAMP_MIN(triggers[editor.indexSelected].width,5);
      CLAMP_MIN(triggers[editor.indexSelected].height,5);
     } 
   }
   else if (editor.typeSelected == 3){
      if(editor.transform == 1){
        resizeObject(&light[editor.indexSelected].x,&light[editor.indexSelected].y);   
      }
      else if (editor.transform == 0){
        resizeObject(&light[editor.indexSelected].width,&light[editor.indexSelected].height); 
        CLAMP_MIN(light[editor.indexSelected].width,5);
        CLAMP_MIN(light[editor.indexSelected].height,5);

     }
   }
   else if (editor.typeSelected == 4){
      if(editor.transform == 1){
         resizeObject(&displacement[editor.indexSelected].x,&displacement[editor.indexSelected].y);   
      }
      else if (editor.transform == 0){
         resizeObject(&displacement[editor.indexSelected].width,&displacement[editor.indexSelected].height); 
         CLAMP_MIN(displacement[editor.indexSelected].width,5);
         CLAMP_MIN(displacement[editor.indexSelected].height,5);
     } 
   }
   else if (editor.typeSelected == 5){
      if(editor.transform == 1){
       resizeObject(&deathbox[editor.indexSelected].x,&deathbox[editor.indexSelected].y);
      }
      else if (editor.transform == 0){
       resizeObject(&deathbox[editor.indexSelected].width,&deathbox[editor.indexSelected].height);
       CLAMP_MIN(deathbox[editor.indexSelected].width,5);
       CLAMP_MIN(deathbox[editor.indexSelected].height,5);
     } 
    }
    else if (editor.typeSelected == 6){
      resizeObject(&movenodes[editor.indexSelected].positions[editor.movenodeSelected][0],&movenodes[editor.indexSelected].positions[editor.movenodeSelected][1]);
      
    }
    else if (editor.typeSelected == 7){
      if(editor.transform == 1){
        resizeObject(&scripts[editor.indexSelected].x,&scripts[editor.indexSelected].y); 
      }
      else if (editor.transform == 0){
        resizeObject(&scripts[editor.indexSelected].width,&scripts[editor.indexSelected].height); 
      }
      CLAMP_MIN(scripts[editor.indexSelected].width,5);
      CLAMP_MIN(scripts[editor.indexSelected].height,5);
      
    }
    else if (editor.typeSelected == 8){
      if(editor.transform == 1){
         resizeObject(&enemy[editor.indexSelected].x,&enemy[editor.indexSelected].y); 
      }
      else if (editor.transform == 0){
      
       resizeObject(&enemy[editor.indexSelected].width,&enemy[editor.indexSelected].height); 
       CLAMP_MIN(enemy[editor.indexSelected].width,5);
       CLAMP_MIN(enemy[editor.indexSelected].height,5);

      }
    }
    else if (editor.typeSelected == 9){
      if(editor.transform == 1){
        resizeObject(&specials[editor.indexSelected].x,&specials[editor.indexSelected].y); 
      }
      else if (editor.transform == 0){
        resizeObject(&specials[editor.indexSelected].size,NULL); 
      }
      CLAMP_MIN(specials[editor.indexSelected].size,5);
    }
    else if (editor.typeSelected == 10){
      if(editor.transform == 1){
         resizeObject(&textpopups[editor.indexSelected].x,&textpopups[editor.indexSelected].y); 
      }
      else if (editor.transform == 0){
         resizeObject(&textpopups[editor.indexSelected].width,&textpopups[editor.indexSelected].height); 
      }
      CLAMP_MIN(textpopups[editor.indexSelected].width,5);
      CLAMP_MIN(textpopups[editor.indexSelected].height,5);
    }
   }
  if(mouse.right){
    mouse.dX = mouse.x - mouse.oldX;
    mouse.dY = mouse.y - mouse.oldY;
    camera.x += mouse.dX;
    camera.y += mouse.dY;
    
  }
  if(mouse.left == -1){
     editor.mouseToObjectDistanceBool = false;
   }
}