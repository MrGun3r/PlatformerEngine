void platformMovement(int i){
      if(level.Started && platforms[i].moveSpeed >= 1 && platforms[i].moveNodeInt >= 0 && platforms[i].moveNodeInt < 50 && movenodes[platforms[i].moveNodeInt].reserved){
         int from;
         int to;
         if(movenodes[platforms[i].moveNodeInt].wrap){
          platforms[i].moveNodeCount %= movenodes[platforms[i].moveNodeInt].nodesCount;
          from = platforms[i].moveNodeCount % movenodes[platforms[i].moveNodeInt].nodesCount;
          to = (platforms[i].moveNodeCount + 1) % movenodes[platforms[i].moveNodeInt].nodesCount;
         }
         else{
            if(!platforms[i].moveNodeReverse){
             from = platforms[i].moveNodeCount;
             to = platforms[i].moveNodeCount + 1;
            }
            else{
             from = platforms[i].moveNodeCount + 1;
             to = platforms[i].moveNodeCount;
            }
            
         }
          double nodesDistance = sqrt(pow(movenodes[platforms[i].moveNodeInt].positions[from][0]-movenodes[platforms[i].moveNodeInt].positions[to][0],2) + pow(movenodes[platforms[i].moveNodeInt].positions[from][1]-movenodes[platforms[i].moveNodeInt].positions[to][1],2));
         
         
         if(platforms[i].moveDistance >= nodesDistance){
            platforms[i].moveDistance = 0;
               platforms[i].x = movenodes[platforms[i].moveNodeInt].positions[to][0]-(platforms[i].  width-25)/2;
               platforms[i].y = movenodes[platforms[i].moveNodeInt].positions[to][1]-(platforms[i].height-25)/2;
            if(!platforms[i].moveNodeReverse){
               platforms[i].moveNodeCount++;
               

               if(!movenodes[platforms[i].moveNodeInt].wrap){
                  if(platforms[i].moveNodeCount >= movenodes[platforms[i].moveNodeInt].nodesCount - 1 && !platforms[i].moveNodeReverse){
                  platforms[i].moveNodeCount = movenodes[platforms[i].moveNodeInt].nodesCount - 2;
                  platforms[i].moveNodeReverse = true;
               }
              
               }
            }
            else{
               platforms[i].moveNodeCount--;
               if(!movenodes[platforms[i].moveNodeInt].wrap){
                  if(platforms[i].moveNodeCount < 0 && platforms[i].moveNodeReverse){
                  platforms[i].moveNodeCount = 0;
                  platforms[i].moveNodeReverse = false;
               }
               }
               
            }  
         }
          
         double moveAngle = atan((movenodes[platforms[i].moveNodeInt].positions[from][1] - movenodes[platforms[i].moveNodeInt].positions[to][1])/(movenodes[platforms[i].moveNodeInt].positions[from][0] - movenodes[platforms[i].moveNodeInt].positions[to][0]));

        if(movenodes[platforms[i].moveNodeInt].positions[to][0] <= movenodes[platforms[i].moveNodeInt].positions[from][0] && 
        movenodes[platforms[i].moveNodeInt].positions[to][1] <= movenodes[platforms[i].moveNodeInt].positions[from][1]){
         moveAngle = moveAngle - PI;
        }
        else if (movenodes[platforms[i].moveNodeInt].positions[to][0] <= movenodes[platforms[i].moveNodeInt].positions[from][0] && 
        movenodes[platforms[i].moveNodeInt].positions[to][1] >= movenodes[platforms[i].moveNodeInt].positions[from][1]){
         moveAngle = moveAngle + PI;   
        }
         platforms[i].x += platforms[i].moveSpeed*app.deltaTime*cos(moveAngle);
         platforms[i].y += platforms[i].moveSpeed*app.deltaTime*sin(moveAngle);
         platforms[i].moveDistance += platforms[i].moveSpeed*app.deltaTime;
        }
        return;
}


void deathboxMovement(int i){
      if(level.Started && deathbox[i].moveSpeed >= 1 && deathbox[i].moveNodeInt >= 0 && deathbox[i].moveNodeInt < 50 && movenodes[deathbox[i].moveNodeInt].reserved){
         int from;
         int to;
         if(movenodes[deathbox[i].moveNodeInt].wrap){
          deathbox[i].moveNodeCount %= movenodes[deathbox[i].moveNodeInt].nodesCount;
          from = deathbox[i].moveNodeCount % movenodes[deathbox[i].moveNodeInt].nodesCount;
          to = (deathbox[i].moveNodeCount + 1) % movenodes[deathbox[i].moveNodeInt].nodesCount;
         }
         else{
            if(!deathbox[i].moveNodeReverse){
             from = deathbox[i].moveNodeCount;
             to = deathbox[i].moveNodeCount + 1;
            }
            else{
             from = deathbox[i].moveNodeCount + 1;
             to = deathbox[i].moveNodeCount;
            }
            
         }
          double nodesDistance = sqrt(pow(movenodes[deathbox[i].moveNodeInt].positions[from][0]-movenodes[deathbox[i].moveNodeInt].positions[to][0],2) + pow(movenodes[deathbox[i].moveNodeInt].positions[from][1]-movenodes[deathbox[i].moveNodeInt].positions[to][1],2));
         
         
         if(deathbox[i].moveDistance >= nodesDistance){
            deathbox[i].moveDistance = 0;
               deathbox[i].x = movenodes[deathbox[i].moveNodeInt].positions[to][0]-(deathbox[i].  width-25)/2;
               deathbox[i].y = movenodes[deathbox[i].moveNodeInt].positions[to][1]-(deathbox[i].height-25)/2;
            if(!deathbox[i].moveNodeReverse){
               deathbox[i].moveNodeCount++;
               

               if(!movenodes[deathbox[i].moveNodeInt].wrap){
                  if(deathbox[i].moveNodeCount >= movenodes[deathbox[i].moveNodeInt].nodesCount - 1 && !deathbox[i].moveNodeReverse){
                  deathbox[i].moveNodeCount = movenodes[deathbox[i].moveNodeInt].nodesCount - 2;
                  deathbox[i].moveNodeReverse = true;
               }
              
               }
            }
            else{
               deathbox[i].moveNodeCount--;
               if(!movenodes[deathbox[i].moveNodeInt].wrap){
                  if(deathbox[i].moveNodeCount < 0 && deathbox[i].moveNodeReverse){
                  deathbox[i].moveNodeCount = 0;
                  deathbox[i].moveNodeReverse = false;
               }
               }
               
            }  
         }
          
         double moveAngle = atan((movenodes[deathbox[i].moveNodeInt].positions[from][1] - movenodes[deathbox[i].moveNodeInt].positions[to][1])/(movenodes[deathbox[i].moveNodeInt].positions[from][0] - movenodes[deathbox[i].moveNodeInt].positions[to][0]));

        if(movenodes[deathbox[i].moveNodeInt].positions[to][0] <= movenodes[deathbox[i].moveNodeInt].positions[from][0] && 
        movenodes[deathbox[i].moveNodeInt].positions[to][1] <= movenodes[deathbox[i].moveNodeInt].positions[from][1]){
         moveAngle = moveAngle - PI;
        }
        else if (movenodes[deathbox[i].moveNodeInt].positions[to][0] <= movenodes[deathbox[i].moveNodeInt].positions[from][0] && 
        movenodes[deathbox[i].moveNodeInt].positions[to][1] >= movenodes[deathbox[i].moveNodeInt].positions[from][1]){
         moveAngle = moveAngle + PI;   
        }
         deathbox[i].x += deathbox[i].moveSpeed*app.deltaTime*cos(moveAngle);
         deathbox[i].y += deathbox[i].moveSpeed*app.deltaTime*sin(moveAngle);
         deathbox[i].moveDistance += deathbox[i].moveSpeed*app.deltaTime;
        }
        return;
}
void lightMovement(int i){
      
      if(level.Started && light[i].moveSpeed >= 1 && light[i].moveNodeInt >= 0 && light[i].moveNodeInt < 50 && movenodes[light[i].moveNodeInt].reserved){
         int from;
         int to;
         
         if(movenodes[light[i].moveNodeInt].wrap){
          light[i].moveNodeCount %= movenodes[light[i].moveNodeInt].nodesCount;
          from = light[i].moveNodeCount % movenodes[light[i].moveNodeInt].nodesCount;
          to = (light[i].moveNodeCount + 1) % movenodes[light[i].moveNodeInt].nodesCount;
         }
         else{
            if(!light[i].moveNodeReverse){
             from = light[i].moveNodeCount;
             to = light[i].moveNodeCount + 1;
            }
            else{
             from = light[i].moveNodeCount + 1;
             to = light[i].moveNodeCount;
            }
            
         }
          double nodesDistance = sqrt(pow(movenodes[light[i].moveNodeInt].positions[from][0]-movenodes[light[i].moveNodeInt].positions[to][0],2) + pow(movenodes[light[i].moveNodeInt].positions[from][1]-movenodes[light[i].moveNodeInt].positions[to][1],2));
         
         
         if(light[i].moveDistance >= nodesDistance){
            light[i].moveDistance = 0;
               light[i].x = movenodes[light[i].moveNodeInt].positions[to][0]-(light[i].size-25)/2;
               light[i].y = movenodes[light[i].moveNodeInt].positions[to][1]-(light[i].size-25)/2;
            if(!light[i].moveNodeReverse){
               light[i].moveNodeCount++;
               

               if(!movenodes[light[i].moveNodeInt].wrap){
                  if(light[i].moveNodeCount >= movenodes[light[i].moveNodeInt].nodesCount - 1 && !light[i].moveNodeReverse){
                  light[i].moveNodeCount = movenodes[light[i].moveNodeInt].nodesCount - 2;
                  light[i].moveNodeReverse = true;
               }
              
               }
            }
            else{
               light[i].moveNodeCount--;
               if(!movenodes[light[i].moveNodeInt].wrap){
                  if(light[i].moveNodeCount < 0 && light[i].moveNodeReverse){
                  light[i].moveNodeCount = 0;
                  light[i].moveNodeReverse = false;
               }
               }
               
            }  
         }
          
         double moveAngle = atan((movenodes[light[i].moveNodeInt].positions[from][1] - movenodes[light[i].moveNodeInt].positions[to][1])/(movenodes[light[i].moveNodeInt].positions[from][0] - movenodes[light[i].moveNodeInt].positions[to][0]));

        if(movenodes[light[i].moveNodeInt].positions[to][0] <= movenodes[light[i].moveNodeInt].positions[from][0] && 
        movenodes[light[i].moveNodeInt].positions[to][1] <= movenodes[light[i].moveNodeInt].positions[from][1]){
         moveAngle = moveAngle - PI;
        }
        else if (movenodes[light[i].moveNodeInt].positions[to][0] <= movenodes[light[i].moveNodeInt].positions[from][0] && 
        movenodes[light[i].moveNodeInt].positions[to][1] >= movenodes[light[i].moveNodeInt].positions[from][1]){
         moveAngle = moveAngle + PI;   
        }
         light[i].x += light[i].moveSpeed*app.deltaTime*cos(moveAngle);
         light[i].y += light[i].moveSpeed*app.deltaTime*sin(moveAngle);
         light[i].moveDistance += light[i].moveSpeed*app.deltaTime;
        }
        return;
}
void displacementMovement(int i){
      if(level.Started && displacement[i].moveSpeed >= 1 && displacement[i].moveNodeInt >= 0 &&  displacement[i].moveNodeInt < 50 && movenodes[displacement[i].moveNodeInt].reserved){
         int from;
         int to;
         if(movenodes[displacement[i].moveNodeInt].wrap){
          displacement[i].moveNodeCount %= movenodes[displacement[i].moveNodeInt].nodesCount;
          from = displacement[i].moveNodeCount % movenodes[displacement[i].moveNodeInt].nodesCount;
          to = (displacement[i].moveNodeCount + 1) % movenodes[displacement[i].moveNodeInt].nodesCount;
         }
         else{
            if(!displacement[i].moveNodeReverse){
             from = displacement[i].moveNodeCount;
             to = displacement[i].moveNodeCount + 1;
            }
            else{
             from = displacement[i].moveNodeCount + 1;
             to = displacement[i].moveNodeCount;
            }
            
         }
          double nodesDistance = sqrt(pow(movenodes[displacement[i].moveNodeInt].positions[from][0]-movenodes[displacement[i].moveNodeInt].positions[to][0],2) + pow(movenodes[displacement[i].moveNodeInt].positions[from][1]-movenodes[displacement[i].moveNodeInt].positions[to][1],2));
         
         
         if(displacement[i].moveDistance >= nodesDistance){
            displacement[i].moveDistance = 0;
               displacement[i].x = movenodes[displacement[i].moveNodeInt].positions[to][0]-(displacement[i].  width-25)/2;
               displacement[i].y = movenodes[displacement[i].moveNodeInt].positions[to][1]-(displacement[i].height-25)/2;
            if(!displacement[i].moveNodeReverse){
               displacement[i].moveNodeCount++;
               

               if(!movenodes[displacement[i].moveNodeInt].wrap){
                  if(displacement[i].moveNodeCount >= movenodes[displacement[i].moveNodeInt].nodesCount - 1 && !displacement[i].moveNodeReverse){
                  displacement[i].moveNodeCount = movenodes[displacement[i].moveNodeInt].nodesCount - 2;
                  displacement[i].moveNodeReverse = true;
               }
              
               }
            }
            else{
               displacement[i].moveNodeCount--;
               if(!movenodes[displacement[i].moveNodeInt].wrap){
                  if(displacement[i].moveNodeCount < 0 && displacement[i].moveNodeReverse){
                  displacement[i].moveNodeCount = 0;
                  displacement[i].moveNodeReverse = false;
               }
               }
               
            }  
         }
          
         double moveAngle = atan((movenodes[displacement[i].moveNodeInt].positions[from][1] - movenodes[displacement[i].moveNodeInt].positions[to][1])/(movenodes[displacement[i].moveNodeInt].positions[from][0] - movenodes[displacement[i].moveNodeInt].positions[to][0]));

        if(movenodes[displacement[i].moveNodeInt].positions[to][0] <= movenodes[displacement[i].moveNodeInt].positions[from][0] && 
        movenodes[displacement[i].moveNodeInt].positions[to][1] <= movenodes[displacement[i].moveNodeInt].positions[from][1]){
         moveAngle = moveAngle - PI;
        }
        else if (movenodes[displacement[i].moveNodeInt].positions[to][0] <= movenodes[displacement[i].moveNodeInt].positions[from][0] && 
        movenodes[displacement[i].moveNodeInt].positions[to][1] >= movenodes[displacement[i].moveNodeInt].positions[from][1]){
         moveAngle = moveAngle + PI;   
        }
         displacement[i].x += displacement[i].moveSpeed*app.deltaTime*cos(moveAngle);
         displacement[i].y += displacement[i].moveSpeed*app.deltaTime*sin(moveAngle);
         displacement[i].moveDistance += displacement[i].moveSpeed*app.deltaTime;
        }
        return;

}


