/*
 * 
 * Copyright 2013 Stephen Coleman <omegacoleman@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include "global.h"



#include <stdio.h>
#include <time.h>
#include "SDL.h"
#include "sprite.h"
#include "player.h"
#include "environment.h"
#include "missle.h"
#include "explode.h"
#include "ui.h"

#define VIEWPORT_WIDTH 800
#define VIEWPORT_HEIGHT 600
#define FPS_MAX 40
#define FPS_MAX_DELAY (1000 / FPS_MAX)

int process_events(const SDL_Event *event);
int quited = 0;
GearObject gear;

int main(int argc, char **argv)
{
    SDL_Surface *screen;
    Player *player;
    Missle *missle;
    int tick_at_start, tick_gone;
    unsigned long frame = 0;
    int win = -1;
    
    srand((unsigned)time(NULL));
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    atexit(SDL_Quit);
    SDL_SetEventFilter(process_events);
    screen = SDL_SetVideoMode(VIEWPORT_WIDTH, VIEWPORT_HEIGHT, 
    32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    
    load_models();
    ui_init();
    explode_init();
    set_walls(0, VIEWPORT_HEIGHT, 0, VIEWPORT_WIDTH);
    load_environment("env_sea");
    missle_init();
    
    player = create_player(get_model("ca_r"), 200, 200, 3, 1000);
    missle = gen_missle(0, rand() % VIEWPORT_HEIGHT);
    
    while (! quited) {
        tick_at_start = SDL_GetTicks();
        SDL_PollEvent(NULL);
        blit_bg(screen);
        blit_missle(missle, screen);
        blit_player(player, screen);
        blit_explode(screen);
        draw_lifebar(screen, player->health, 0, 0);
        kb_control(player, SDL_GetKeyState(NULL));
        step_player(player);
        if (step_missle(missle) != 1)
        {
            if (rand() % 2)
            {
                missle = 
                gen_missle(VIEWPORT_WIDTH, rand() % VIEWPORT_HEIGHT);
            } else {
                missle = gen_missle(0, rand() % VIEWPORT_HEIGHT);
            }
            lock_gear(missle, &(player->gear));
        }
        env_move_on();
        SDL_Flip(screen);
        tick_gone = SDL_GetTicks() - tick_at_start;
        if (FPS_MAX_DELAY > tick_gone)
        {
            SDL_Delay(FPS_MAX_DELAY - tick_gone);
        }
        frame++;
    }
    if (win == 0) {
    }
    return 0;
}

int process_events(const SDL_Event *event)
{
    switch (event->type) {
        // case SDL_MOUSEBUTTONDOWN:
        case SDL_QUIT:
        quited = 1;
        break;
    }
    return 0;
}

