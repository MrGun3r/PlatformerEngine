void addParticle(double x,double y,double size,double red,double green,double blue,double angle){
     for(int i = 0;i<sizeof(particles)/sizeof(particles[0]);i++){
        if(!particles[i].reserved){
            particles[i].reserved = true;
            particles[i].x = x;
            particles[i].y = y;
            particles[i].size = size;
            particles[i].red = red;
            particles[i].green = green;
            particles[i].blue = blue;
            particles[i].rotation = angle;
            break;
        }
     }
}