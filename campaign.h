void FDraw_Campaign(){
    for(int i = 0 ;i<6;i++){
        for(int j = 0;j<6;j++){
            SDL_RenderCopy(renderer,tex_water,NULL,&(SDL_Rect){200*i,200*j,200,200});
        }
    }
}



void FUpdate_Campaign(){
    
}