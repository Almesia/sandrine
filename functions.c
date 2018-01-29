#include "header.h"

SDL_Surface *init_image(char name[255],int r, int g, int b){
    SDL_Surface* surface = NULL;  //Temporary storage for the image that's loaded
    SDL_Surface* optimizedSurface = NULL; //The optimized image that will be used

    surface = SDL_LoadBMP(name);
    SDL_SetColorKey(surface, SDL_SRCCOLORKEY, SDL_MapRGB(surface->format, r, g, b));

     if( surface != NULL ){
        optimizedSurface = SDL_DisplayFormat(surface);  //Create an optimized image
        SDL_FreeSurface(surface); //Free the old image
    }
    return optimizedSurface;
}

void blit(SDL_Surface* destination, SDL_Surface* source, int x, int y){
    SDL_Rect position;
    position.x = x;
    position.y = y;
    SDL_BlitSurface( source, NULL, destination, &position );
}
