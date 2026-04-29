
/// ----------------------------------------------
/// ---------------------------------------------- 
void Editor_drawTriggers(int i) {
      FtextureQuad(triggers[i].xDraw,triggers[i].yDraw,triggers[i].widthDraw,triggers[i].heightDraw,tex_trigger,min(triggers[i].opacity+25,255),0);
      
      if(triggers[i].triggerType == 0 && platforms[(int)triggers[i].Value3].reserved){
         RenderDrawLine(renderer,triggers[i].xDraw+triggers[i].widthDraw/2,triggers[i].yDraw+triggers[i].heightDraw/2,platforms[(int)triggers[i].Value3].xDraw+platforms[(int)triggers[i].Value3].widthDraw/2,platforms[(int)triggers[i].Value3].yDraw+platforms[(int)triggers[i].Value3].heightDraw/2);
      }
      else if(triggers[i].triggerType == 1 && deathbox[(int)triggers[i].Value3].reserved){
         RenderDrawLine(renderer,triggers[i].xDraw+triggers[i].widthDraw/2,triggers[i].yDraw+triggers[i].heightDraw/2,deathbox[(int)triggers[i].Value3].xDraw+deathbox[(int)triggers[i].Value3].widthDraw/2,deathbox[(int)triggers[i].Value3].yDraw+deathbox[(int)triggers[i].Value3].heightDraw/2);
      }
      else if(triggers[i].triggerType == 2 && light[(int)triggers[i].Value3].reserved){
         RenderDrawLine(renderer,triggers[i].xDraw+triggers[i].widthDraw/2,triggers[i].yDraw+triggers[i].heightDraw/2,light[(int)triggers[i].Value3].xDraw+light[(int)triggers[i].Value3].widthDraw/2,light[(int)triggers[i].Value3].yDraw+light[(int)triggers[i].Value3].heightDraw/2);
      }
      else if(triggers[i].triggerType == 3 && displacement[(int)triggers[i].Value3].reserved){
         RenderDrawLine(renderer,triggers[i].xDraw+triggers[i].widthDraw/2,triggers[i].yDraw+triggers[i].heightDraw/2,displacement[(int)triggers[i].Value3].xDraw+displacement[(int)triggers[i].Value3].widthDraw/2,displacement[(int)triggers[i].Value3].yDraw+displacement[(int)triggers[i].Value3].heightDraw/2);
      }
}
void Editor_drawLights(int i) {
   SDL_SetTextureAlphaMod(tex_bulb,50);
   RenderCopy(renderer,tex_bulb,NULL,&(SDL_Rect){light[i].xDraw+light[i].widthDraw/2-min(30,light[i].widthDraw)/2,light[i].yDraw+light[i].heightDraw/2-min(30,light[i].heightDraw)/2,min(30,light[i].widthDraw),min(30,light[i].heightDraw)});
   SDL_SetTextureAlphaMod(tex_bulb,255);
}
void Editor_drawMovenodes() {
   SDL_SetTextureAlphaMod(tex_movenode,100);
   // Draw movenodes
   for(int i = 0;i<sizeof(movenodes)/sizeof(movenodes[0]);i++){
      if(movenodes[i].reserved){
         for(int j = 0;j<movenodes[i].nodesCount;j++){
           movenodes[i].positionsDraw[j][0] = gameWidthBase/2 + (movenodes[i].positions[j][0] + camera.x - gameWidthBase/2) * camera.scale;
           movenodes[i].positionsDraw[j][1] = gameHeightBase/2 + (movenodes[i].positions[j][1] + camera.y - gameHeightBase/2) * camera.scale;

           SDL_SetRenderDrawColor(renderer,200,200,200,255);
           if(movenodes[i].nodesCount>1){
            if(j != movenodes[i].nodesCount - 1 || movenodes[i].wrap){
              RenderDrawLine(renderer,movenodes[i].positionsDraw[j][0]+12*camera.scale,movenodes[i].positionsDraw[j][1]+12*camera.scale,movenodes[i].positionsDraw[(j+1)%(movenodes[i].nodesCount)][0]+12*camera.scale,movenodes[i].positionsDraw[(j+1)%(movenodes[i].nodesCount)][1]+12*camera.scale); 
            }
            
           }
           RenderCopy(renderer,tex_movenode,NULL,&(SDL_Rect){movenodes[i].positionsDraw[j][0],movenodes[i].positionsDraw[j][1],25*camera.scale*windowWidthScale,25*camera.scale*windowHeightScale});
           char nodeNumber[5];
           sprintf(nodeNumber,"%d\0",j);
           renderText(2,nodeNumber,movenodes[i].positionsDraw[j][0]+11*camera.scale,movenodes[i].positionsDraw[j][1]+8*camera.scale,10*camera.scale,10*camera.scale,100,100,(int[3]){255,255,255});
         
           
           if(editor.selected && editor.typeSelected == MOVENODE && editor.indexSelected == i && editor.movenodeSelected == j){ 
            SDL_SetRenderDrawColor(renderer,0,255,0,255);
            RenderDrawRect(renderer,&(SDL_Rect){movenodes[i].positionsDraw[j][0],movenodes[i].positionsDraw[j][1],25*camera.scale,25*camera.scale});
           }
         }
      }
   }
   SDL_SetTextureAlphaMod(tex_movenode,255);
}
void Editor_drawScripts(int i) {
   FtextureQuad(scripts[i].xDraw,scripts[i].yDraw,scripts[i].widthDraw,scripts[i].heightDraw,tex_script,50,0);
}
void Editor_drawEnemies(int i) {
   SDL_Rect src;
   switch(enemy[i].type) {
        case 1: src = (SDL_Rect){0,   0,  80, 80}; break;
        case 2: src = (SDL_Rect){3,  120, 16, 18}; break;
        case 3: src = (SDL_Rect){3,  144, 16, 18}; break;
        case 4: src = (SDL_Rect){2,  169, 19, 20}; break;
        case 5: src = (SDL_Rect){3,  192, 16, 22}; break;
        default: return;
   }
   RenderCopyEx(renderer, tex_enemy, &src,
        &(SDL_Rect){enemy[i].xDraw, enemy[i].yDraw, enemy[i].widthDraw, enemy[i].heightDraw},
        0, NULL, SDL_FLIP_NONE);
}
void Editor_drawSpecials(int i) {
   RenderCopyEx(renderer,tex_specials,&(SDL_Rect){5+150*(specials[i].type - 1),0,125,125},&(SDL_Rect){specials[i].xDraw,specials[i].yDraw,specials[i].widthDraw,specials[i].heightDraw},0,NULL,SDL_FLIP_NONE);
}
void Editor_drawTextpopups(int i) {
   FtextureQuad(textpopups[i].xDraw,textpopups[i].yDraw,textpopups[i].widthDraw,textpopups[i].heightDraw,tex_textIcon,150,0);
}
void Editor_drawPlayer() {
   player[0].widthDraw = player[0].width;
   player[0].heightDraw = player[0].height;
   player[0].widthDraw  *= camera.scale;
   player[0].heightDraw *= camera.scale;
   player[0].xDraw = gameWidthBase/2 + (player[0].x + camera.x - gameWidthBase/2) * camera.scale;
   player[0].yDraw = gameHeightBase/2 + (player[0].y + camera.y  - gameHeightBase/2) * camera.scale;

   RenderCopyEx(renderer,tex_player,&(SDL_Rect){2,24,15,18},&(SDL_Rect){player[0].xDraw,player[0].yDraw,player[0].widthDraw,player[0].heightDraw},0,NULL,SDL_FLIP_NONE);
   if(editor.selected && editor.typeSelected == PLAYER){
      SDL_SetRenderDrawColor(renderer,0,255,0,255);
      RenderDrawRect(renderer,&(SDL_Rect){player[0].xDraw,player[0].yDraw,player[0].widthDraw,player[0].heightDraw});
   }
}
void Editor_drawDisplacements(int i) {
   FtextureQuad(displacement[i].xDraw,displacement[i].yDraw,displacement[i].widthDraw,displacement[i].heightDraw,tex_displacement,min(displacement[i].opacity+25,255),displacement[i].type);
}
void Editor_drawDeathboxes(int i) {
   FtextureQuad(deathbox[i].xDraw,
                deathbox[i].yDraw,
                deathbox[i].widthDraw,
                deathbox[i].heightDraw,
                tex_skull,
                min(deathbox[i].opacity+25,255),
                0);
}
/// ----------------------------------------------
/// ---------------------------------------------- 

void Editor_DrawObjects(){
   
   // Draw Player
   Editor_drawPlayer();
   // Draw Platforms
   DRAW_OBJECTS_EDITOR(platforms,PLATFORM,!platforms[i].collidable,FtexturePlatform(i))
   DRAW_OBJECTS_EDITOR(platforms,PLATFORM,platforms[i].collidable,FtexturePlatform(i))   
   // Draw triggers
   DRAW_OBJECTS_EDITOR(triggers,TRIGGER,1,Editor_drawTriggers(i);)
   // Draw lights
   DRAW_OBJECTS_EDITOR(light,LIGHT,1,Editor_drawLights(i);)
   // Draw displacements
   DRAW_OBJECTS_EDITOR(displacement,DISPLACEMENT,1,Editor_drawDisplacements(i);)
   // Draw movenodes
   Editor_drawMovenodes();
   // Draw deathboxes
   DRAW_OBJECTS_EDITOR(deathbox,DEATHBOX,1,Editor_drawDeathboxes(i);)
   // Draw scripts
   DRAW_OBJECTS_EDITOR(scripts,SCRIPT,1,Editor_drawScripts(i);)
   // Draw enemies
   DRAW_OBJECTS_EDITOR(enemy,ENEMY,1,Editor_drawEnemies(i);)
   // Draw specials
   DRAW_OBJECTS_EDITOR(specials,SPECIAL,1,Editor_drawSpecials(i);)
   // Draw textpopups
   DRAW_OBJECTS_EDITOR(textpopups,TEXTPOPUP,1,Editor_drawTextpopups(i);)

}