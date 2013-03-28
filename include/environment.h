
#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_

#include "SDL.h"
#include "sprite.h"

typedef struct
{
    SDL_Surface *bg;
    SDL_Surface *optlines;
} Environment;

#define OPT_SPEC_LN 0
#define OPT_FOG_LN 1

void load_environment(char *name);
void blit_bg(SDL_Surface *dest);
void env_move_on();
Uint32 get_spec();
Uint8 get_fog();
SDL_PixelFormat *get_spec_fmt();

extern SuperBlitable *curr_envobj;

#endif


