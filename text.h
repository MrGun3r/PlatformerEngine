void FapplyText(){
    if(app.status == 1){
        if(editor.status == 0){
            // saving
            FSaveMap();
            app.textboxSelected = -1;
            editor.status = -1;
            editorShowButtons();
        }
        else if (editor.status == 1){
            // loading
            char path[256];
            sprintf(path,"levels/%s.txt\0",textbox[0].textContent);
            FSetDataMap(path,textbox[0].textContentSize+12);
            app.textboxSelected = -1;
            editor.status = -1;
            editorShowButtons();
        }
    }
}