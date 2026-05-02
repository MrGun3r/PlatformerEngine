void clearPlatforms() {
    for (int i = 0; i < sizeof(platforms) / sizeof(platforms[0]); i++)
    {
        platforms[i].reserved = false;
    }
}
void clearTriggers() {
    for (int i = 0; i < sizeof(triggers) / sizeof(triggers[0]); i++)
        triggers[i].reserved = false;
}
void clearDisplacement() {
    for (int i = 0; i < sizeof(displacement) / sizeof(displacement[0]); i++)
        displacement[i].reserved = false;
}
void clearDeathboxes() {
    for (int i = 0; i < sizeof(deathbox) / sizeof(deathbox[0]); i++)
        deathbox[i].reserved = false;
}
void clearMovenodes() {
    for (int i = 0; i < sizeof(movenodes) / sizeof(movenodes[0]); i++)
        movenodes[i].reserved = false;
}
void clearScripts() {
    for (int i = 0; i < sizeof(scripts) / sizeof(scripts[0]); i++)
        scripts[i].reserved = false;
}
void clearEnemies() {
    for (int i = 0; i < sizeof(enemy) / sizeof(enemy[0]); i++)
        enemy[i].reserved = false;
}
void clearSpecials() {
    for (int i = 0; i < sizeof(specials) / sizeof(specials[0]); i++)
        specials[i].reserved = false;
}
void clearTextpopups() {
    for (int i = 0; i < sizeof(textpopups) / sizeof(textpopups[0]); i++) {
        textpopups[i].reserved = false;
        free(textpopups[i].textContent);
        textpopups[i].textContent = NULL;  // avoid dangling pointer
    }
}
void clearLight() {
    for (int i = 0; i < sizeof(light) / sizeof(light[0]); i++)
    {
        light[i].reserved = false;
    }
}
void clearAllElements() {
    clearLight();
    clearTriggers();
    clearDisplacement();
    clearDeathboxes();
    clearMovenodes();
    clearScripts();
    clearEnemies();
    clearSpecials();
    clearTextpopups();
    clearPlatforms();
}