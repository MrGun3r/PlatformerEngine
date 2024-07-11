double min(double a, double b){
   return a < b ? a : b;
}
double max(double a, double b){
   return a > b ? a : b;
}
int len(char* a){
   for(int i = 0;i<256;i++){
      if (a[i] == '\0'){
         return i;
      }
   }
   return 256;
}

bool FCompareStrings(char* a,char* b){
  for(int i = 0;i<255;i++){
   if(a[i] == '\0' && b[i] == '\0'){
      return true;
   }
   if(a[i] != b[i]){
      return false;
   }
  }

}
char* FlowerCase(char* text,int textSize){
   char* returnText = malloc(textSize+1);
   for(int i = 0;i<textSize+1;i++){
      if(text[i] >= 65 && text[i] <= 90){
         returnText[i] = (char)((int)text[i] + 32);
      }
      else{returnText[i] = text[i];}
   }
   return returnText;
}

char* msToTimer(int ms){
   char *timer = malloc(9);
   // milliSeconds
   int mSeconds1 = (ms/10) % 10;
   timer[7] = (char)(mSeconds1+48);
   int mSeconds2 = (ms/100) % 10;
   timer[6] = (char)(mSeconds2+48);
   timer[5] = ':';
   // Seconds
   int Seconds1 = (ms/1000) % 10;
   timer[4] = (char)(Seconds1+48);
   int Seconds2 = (ms/10000) % 6;
   timer[3] = (char)(Seconds2+48);
   timer[2] = ':';
   // Minutes
   int Minutes1 = (ms/60000) % 10;
   timer[1] = (char)(Minutes1+48);
   int Minutes2 = (ms/600000) % 10;
   timer[0] = (char)(Minutes2+48);
   timer[8] = '\0';
   return timer;
}


void FdeltaTime(){
   app.deltaTime =      ((double)(SDL_GetTicks()-app.WINDOW_TICKS))/1000;
   app.deltaTimeGhost = ((double)(SDL_GetTicks()-app.WINDOW_TICKS))/1000;
   app.WINDOW_TICKS = SDL_GetTicks();

    
}
