#include "mandelbrot.h"

void render_ui(SDL_Renderer *rend, TTF_Font *font, double fps, const Mandelbrot *v)
{
    if (!font) return;

    char buf[128];
    snprintf(buf, sizeof(buf),
        "FPS: %.1f  |  Scale: %.4f  |  ROI: (%.4f, %.4f)",
        fps, v->scale, v->roi_x, v->roi_y);

    SDL_Color fg = {255, 255, 255, 230};
    SDL_Surface *surf = TTF_RenderUTF8_Blended(font, buf, fg);
    if (!surf) return;

    SDL_Rect bg = {6, 6, surf->w + 14, surf->h + 6};
    SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 160);
    SDL_RenderFillRect(rend, &bg);

    SDL_Texture *t = SDL_CreateTextureFromSurface(rend, surf);
    SDL_FreeSurface(surf);
    if (!t) return;

    SDL_Rect dst = {bg.x + 7, bg.y + 3, bg.w - 14, bg.h - 6};
    SDL_RenderCopy(rend, t, NULL, &dst);
    SDL_DestroyTexture(t);
}