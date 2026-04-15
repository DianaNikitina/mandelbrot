#include "mandelbrot.h"

SDL_Color color_from_iter(int n)
{
    if (n >= N_MAX)
        return (SDL_Color){0, 0, 0, 255};               //if not break earlier, set point

    float t = sqrtf(sqrtf((float)n / (float)N_MAX));    //how far point on current op
    float I = t * 255.0f;                               //bright pixel

    Uint8 r = (Uint8)(I * t * t);
    Uint8 g = (Uint8)(I);
    Uint8 b = (Uint8)(I * t * t);
    return (SDL_Color){r, g, b, 255};
}