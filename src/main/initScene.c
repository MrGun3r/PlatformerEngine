
void initEditor() {
    editor.mapNameSet = false;
    app.backgroundInt = FindBackgroundInt("background");
    editor.GameScale = 2;
    app.backgroundOpacity = 255;
    editor.gridMove = 1;
    editor.StarTime = 60;
    editor.StarTimeMs = 0;
    player[0].x = 0;
    player[0].y = 0;
    player[0].spawnX = 0;
    player[0].spawnY = 0;
    player[0].width = 18;
    player[0].height = 20;
    camera.x = gameWidth / 2;
    camera.y = gameHeight / 2;
    camera.scaleReal = 1;
    camera.scale = 1;
    mapData.xMin = -5000;
    mapData.yMin = -5000;
    mapData.xMax = 5000;
    mapData.yMax = 5000;
    editor.status = -1;

    editor.mouseToObjectDistances[0] = 0;
    editor.mouseToObjectDistances[1] = 0;
    editor.mouseToObjectDistanceBool = false;
    editor.gridMove = 1;
    editor.transform = 1;
    editor.selected = false;
    editor.typeSelected = 0;
    editor.indexSelected = 0;
}