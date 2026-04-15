#include "mandelbrot.h"

//draw text over frame

void draw_text(SDL_Renderer *rend, TTF_Font *font, double fps, const Mandelbrot *v)
{
    if (!font) return;                      //if font not found -> break

    char buf[128] = {0};
    snprintf(buf, sizeof(buf),"FPS: %.1f  |  Scale: %.4f  |  ROI: (%.4f, %.4f)", fps, v->scale, v->roi_x, v->roi_y);

    SDL_Color text = {255, 255, 255, 230};                              //color of text almost white
    SDL_Surface *surf = TTF_RenderUTF8_Blended(font, buf, text);        //render font
    if (!surf) return;

    SDL_Rect background = {6, 6, surf->w + 14, surf->h + 6};            //create background, draw surface form rect
    SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_BLEND);              //with alpha-blending
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);                         //black with alpa = 0 (прозрачность)
    SDL_RenderFillRect(rend, &background);                              //fill rect blending colour

    SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, surf);
    SDL_FreeSurface(surf);
    if (!texture) return;

    SDL_Rect dst = {background.x + 7, background.y + 3, background.w - 14, background.h - 6};       //text inside background
    SDL_RenderCopy(rend, texture, NULL, &dst);              //copy texture on screen
    SDL_DestroyTexture(texture);
}