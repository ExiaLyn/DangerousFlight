
#include "missle.h"


#define EXPLODE_TICK_MAX 50
#define EXPLODE_TICK_MIN 40
#define EXPLODE_TICK_GAP (EXPLODE_TICK_MAX - EXPLODE_TICK_MIN)

#define MISSLE_PUSH_X_MAX -30
#define MISSLE_PUSH_X_MIN -70
#define MISSLE_PUSH_Y_MAX 7
#define MISSLE_PUSH_Y_MIN -7

#define MISSLE_PUSH_X_GAP (MISSLE_PUSH_X_MAX - MISSLE_PUSH_X_MIN)
#define MISSLE_PUSH_Y_GAP (MISSLE_PUSH_Y_MAX - MISSLE_PUSH_Y_MIN)

SuperBlitable *missle_model;

void missle_init()
{
    missle_model = get_model("missle");
}

Missle *gen_missle(int x, int y)
{
    Missle *curr = malloc(sizeof(Missle));
    curr->explode_tick_left = \
    EXPLODE_TICK_MIN + (rand() % EXPLODE_TICK_GAP);
    curr->gear.x = x;
    curr->gear.y = y;
    curr->gear.x_vector = 0;
    curr->gear.y_vector = 0;
    curr->gear.angle = 0;
    curr->gear.weight = 3;
    int x_push = MISSLE_PUSH_X_MIN + (rand() % MISSLE_PUSH_X_GAP);
    int y_push = MISSLE_PUSH_Y_MIN + (rand() % MISSLE_PUSH_Y_GAP);
    give_push(&(curr->gear), x_push, y_push);
}

int step_missle(Missle *missle)
{
    missle->explode_tick_left -= 1;
    if (missle->explode_tick_left <= 0)
    {
        free(missle);
        return 0;
    }
    step_gear(&(missle->gear));
    return 1;
}

void blit_missle(Missle *missle, SDL_Surface *dest)
{
    super_blit(missle_model, dest, missle->gear.x, missle->gear.y, missle->gear.angle);
}

