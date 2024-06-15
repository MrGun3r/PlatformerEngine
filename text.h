void FapplyText(){
    if(editor.status == 0){
      editor.saving = true;
    }
    else if (editor.status == 1){
      char path[256];
      sprintf(path,"levels/%s.txt\0",editor.fileNameSave);
      for(int i = 0 ;i<sizeof(platforms)/sizeof(platforms[0]);i++){
        platforms[i].reserved = false;
      }
      FSetDataMap(path,len(path));
      editor.typing = false;
    }
}