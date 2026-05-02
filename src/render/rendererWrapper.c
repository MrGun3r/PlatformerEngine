
void RenderGeometry(SDL_Renderer* renderer,SDL_Texture* texture ,SDL_Vertex* vertices,int num_vertices, const int *indices, int num_indices) {
    SDL_Vertex scaledVertices[num_vertices];
    memcpy(scaledVertices,vertices,num_vertices*sizeof(SDL_Vertex));
    for(int i = 0;i<num_vertices;i++) {
        scaledVertices[i].position.x *= windowWidthScale;
        scaledVertices[i].position.y *= windowHeightScale;
    }
    SDL_RenderGeometry(renderer, texture, scaledVertices, num_vertices, indices, num_indices);
}

void RenderDrawRect(SDL_Renderer* renderer,SDL_Rect* rect) {
    SDL_Rect scaledRect = {rect->x*windowWidthScale,rect->y*windowHeightScale,rect->w*windowWidthScale,rect->h*windowHeightScale};
    SDL_RenderDrawRect(renderer,&scaledRect);
}
void RenderFillRect(SDL_Renderer* renderer,SDL_Rect* rect) {
    SDL_Rect scaledRect = {rect->x*windowWidthScale,rect->y*windowHeightScale,rect->w*windowWidthScale,rect->h*windowHeightScale};
    SDL_RenderFillRect(renderer,&scaledRect);
}
void RenderCopy(SDL_Renderer* renderer,SDL_Texture* texture, const SDL_Rect* srcRect,const SDL_Rect* dstRect) {
    SDL_Rect scaledDstRect = {dstRect->x*windowWidthScale,dstRect->y*windowHeightScale,dstRect->w*windowWidthScale,dstRect->h*windowHeightScale};
    SDL_RenderCopy(renderer, texture, srcRect, &scaledDstRect);
}
void RenderCopyEx(SDL_Renderer* renderer,SDL_Texture* texture, const SDL_Rect* srcRect,const SDL_Rect* dstRect,const double angle, const SDL_Point* center,const SDL_RendererFlip flip) {
    SDL_Rect scaledDstRect = {dstRect->x*windowWidthScale,dstRect->y*windowHeightScale,dstRect->w*windowWidthScale,dstRect->h*windowHeightScale};
    SDL_RenderCopyEx(renderer, texture, srcRect, &scaledDstRect,angle,center,flip);
}
void RenderDrawLine(SDL_Renderer * renderer,
                       int x1, int y1, int x2, int y2) {
    SDL_RenderDrawLine(renderer, x1*windowWidthScale, y1*windowHeightScale, x2*windowWidthScale,y2*windowHeightScale);
}