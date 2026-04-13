#include "mandelbrot.h"

int destroy(Params *params)
{
    if (params->font) TTF_CloseFont(params->font);
    SDL_DestroyTexture(params->texture);
    SDL_DestroyRenderer(params->render);
    SDL_DestroyWindow(params->window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}