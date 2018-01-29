#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sqlite3.h>
#include <SDL.h>
#include <time.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "database.h"
#include "fight.h"

#define DEBUG 1
#define DATABASE_FILE "esgi_clicker.db"

SDL_Surface *init_image(char name[255],int r, int g, int b);
void blit(SDL_Surface* destination, SDL_Surface* source, int x, int y);
