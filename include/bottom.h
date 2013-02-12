
#ifndef _BOTTOM_H_
#define _BOTTOM_H_

#include <SDL/SDL.h>

void set_pixel_alpha(SDL_Surface *surface, int x, int y, Uint8 alpha);
Uint32 get_pixel(SDL_Surface *surface, int x, int y);
void set_pixel(SDL_Surface *surface, int x, int y, Uint32 dst);

#endif


