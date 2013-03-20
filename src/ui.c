
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#define S_FN_LIFECROSS "res/lifec.png"

SDL_Surface *s_lifecross;

void ui_init()
{
    IMG_Init(IMG_INIT_PNG);
    s_lifecross = IMG_Load(S_FN_LIFECROSS);
    IMG_Quit();
}

void draw_lifebar(SDL_Surface *dest, int life, int x, int y)
{
    int cross_nr = life / 150;
    if(life == 0)
    {
        return;
    }
    cross_nr += 1;
    int i;
    SDL_Rect thisrect;
    thisrect.x = x;
    thisrect.y = y;
    thisrect.w = s_lifecross->w;
    thisrect.h = s_lifecross->h;
    for (i = 0; i < cross_nr; i++)
    {
        SDL_BlitSurface(s_lifecross, NULL, dest, &thisrect);
        thisrect.x += s_lifecross->w;
    }
}


