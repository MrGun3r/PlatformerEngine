void editorMouseToObject_CalculateDistances(double* x,double* y){
   if(!editor.mouseToObjectDistanceBool){
      if(x != NULL){
         editor.mouseToObjectDistances[0] = editor.mouseProjected[0] - *x;
      }
      if(y != NULL){
         editor.mouseToObjectDistances[1] = editor.mouseProjected[1] - *y;
      }  
      editor.mouseToObjectDistanceBool = true;
   }
}