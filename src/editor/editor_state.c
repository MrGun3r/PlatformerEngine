#define CLEAR_ARRAY(list) \
   for(int i = 0 ;i<sizeof(list)/sizeof(list[0]); i++){ \
      list[i].reserved = false; \
   } \



void reserve_buttons(int list[],int list_size) {
   for(int i = 0;i<list_size;i++) {
      buttons[list[i]].reserved = true;
   } 
}

void reserve_knobs(int list[],int list_size) {
   for(int i = 0;i<list_size;i++) {
      knobs[list[i]].reserved = true;
   } 
}

void reserve_sliders(int list[],int list_size) {
   for(int i = 0;i<list_size;i++) {
      sliders[list[i]].reserved = true;
   } 
}

void editorShowButtons(){
    
   CLEAR_ARRAY(buttons)
   CLEAR_ARRAY(sliders)
   CLEAR_ARRAY(knobs)
   CLEAR_ARRAY(textbox)
   
   reserve_buttons((int[]){0,3,4,6,10,11,12,13,14,15,16,19,20,23,25,30,33,34,36}, 19);

   if(editor.status >= 0) textbox[0].reserved = true;
   if(!editor.selected)   return;

   switch(editor.typeSelected) {
      case NONE:
         reserve_buttons((int[]){18}, 1);
         reserve_sliders((int[]){6,15}, 2);
         reserve_knobs((int[]){3,4,6,7,19}, 5);
         return;

      case PLAYER:
         reserve_buttons((int[]){1,2,5,9}, 4);
         break;

      case PLATFORM:
         reserve_buttons((int[]){1,2,5,9,17,24,40}, 7);
         reserve_sliders((int[]){1,2,14}, 3);
         reserve_knobs((int[]){0,5,8,9,16,17}, 6);
         ChangeSliderPosition(14, sliders[14].x, 340);

         if(platforms[editor.indexSelected].type == 0){
            reserve_buttons((int[]){7,8,38}, 3);
            reserve_sliders((int[]){0,10,11,12}, 4);
            ChangeSliderPosition(1, sliders[1].x, 260);
            ChangeSliderPosition(2, sliders[2].x, 280);
            ChangeSliderPosition(10, sliders[10].x, 380);
            ChangeSliderPosition(11, sliders[11].x, 400);
            ChangeSliderPosition(12, sliders[12].x, 420);
            ChangeKnobPosition(0, knobs[0].x, 240);
            ChangeKnobPosition(5, knobs[5].x, 360);
            ChangeKnobPosition(8, knobs[8].x, 440);
            ChangeKnobPosition(9, knobs[9].x, 460);
            ChangeButtonPosition(17, buttons[17].x, 320);
            ChangeButtonPosition(24, buttons[24].x, 300);
         }
         else if(platforms[editor.indexSelected].type == 1 ||
                 platforms[editor.indexSelected].type == 2){
            reserve_buttons((int[]){39}, 1);
            ChangeSliderPosition(1, sliders[1].x, 180);
            ChangeSliderPosition(2, sliders[2].x, 200);
            ChangeSliderPosition(14, sliders[14].x, 280);
            ChangeKnobPosition(0, knobs[0].x, 220);
            ChangeKnobPosition(5, knobs[5].x, 300);
            ChangeKnobPosition(8, knobs[8].x, 340);
            ChangeKnobPosition(9, knobs[9].x, 360);
            ChangeButtonPosition(17, buttons[17].x, 240);
            ChangeButtonPosition(24, buttons[24].x, 260);
         }
         break;

      case TRIGGER:
         reserve_buttons((int[]){1,2,5,9,29}, 5);
         reserve_sliders((int[]){14}, 1);
         reserve_knobs((int[]){8,9,10,11,12}, 5);
         ChangeSliderPosition(14, sliders[14].x, 220);
         ChangeKnobPosition(8, knobs[8].x, 260);
         ChangeKnobPosition(9, knobs[9].x, 280);
         ChangeKnobPosition(10, knobs[10].x, 300);
         break;

      case LIGHT:
         reserve_buttons((int[]){1,2,5,9,32}, 5);
         reserve_sliders((int[]){7,8,9,10,11,12}, 6);
         reserve_knobs((int[]){8,9}, 2);
         ChangeSliderPosition(10, sliders[10].x, 260);
         ChangeSliderPosition(11, sliders[11].x, 280);
         ChangeSliderPosition(12, sliders[12].x, 300);
         ChangeKnobPosition(8, knobs[8].x, 340);
         ChangeKnobPosition(9, knobs[9].x, 360);
         break;

      case DISPLACEMENT:
         reserve_buttons((int[]){1,2,5,9,21,22}, 6);
         reserve_sliders((int[]){13,14}, 2);
         reserve_knobs((int[]){8,9}, 2);
         ChangeSliderPosition(14, sliders[14].x, 240);
         ChangeKnobPosition(8, knobs[8].x, 300);
         ChangeKnobPosition(9, knobs[9].x, 320);
         break;

      case DEATHBOX:
         reserve_buttons((int[]){1,2,5,9}, 4);
         reserve_sliders((int[]){14}, 1);
         reserve_knobs((int[]){8,9}, 2);
         ChangeSliderPosition(14, sliders[14].x, 220);
         ChangeKnobPosition(8, knobs[8].x, 260);
         ChangeKnobPosition(9, knobs[9].x, 320);
         break;

      case MOVENODE:
         reserve_buttons((int[]){1,2,5,26,27,28}, 6);
         break;

      case SCRIPT:
         reserve_buttons((int[]){1,2,5,9,31}, 5);
         reserve_knobs((int[]){11,12}, 2);
         break;

      case ENEMY:
         reserve_buttons((int[]){1,2,5,9}, 4);
         reserve_sliders((int[]){16,17}, 2);
         reserve_knobs((int[]){18}, 1);
         break;

      case SPECIAL:
         reserve_buttons((int[]){1,2,5,9,35}, 5);
         break;

      case TEXTPOPUP:
         reserve_buttons((int[]){1,2,5,9,37}, 5);
         reserve_knobs((int[]){13,14,15}, 3);
         break;
   }
}