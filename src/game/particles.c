void addParticle(SDL_Texture* texture,double x,double y,double veloX,double veloY,double size,double red,double green,double blue,double angle){
     for(int i = 0;i<sizeof(particles)/sizeof(particles[0]);i++){
        if(!particles[i].reserved){
            particles[i].reserved = true;
            particles[i].x = x;
            particles[i].y = y;
            particles[i].veloX = veloX;
            particles[i].veloY = veloY;
            particles[i].size = size;
            particles[i].red = red;
            particles[i].green = green;
            particles[i].blue = blue;
            particles[i].rotation = angle;
            particles[i].texture = texture;
            break;
        }
     }
}


void addDamagePopUp(int value,double x,double y,double size,double veloX,double veloY){
    for(int i = 0;i<sizeof(damagepopups)/sizeof(damagepopups[0]);i++){
        if(!damagepopups[i].reserved){
           damagepopups[i].reserved = true;
           damagepopups[i].x = x;
           damagepopups[i].y = y;
           damagepopups[i].veloX = veloX;
           damagepopups[i].veloY = veloY;
           damagepopups[i].size = size;
           damagepopups[i].opacity = 255;
           damagepopups[i].number = value;
           
           break;
        }
     }
}