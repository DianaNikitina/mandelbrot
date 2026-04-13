#include "mandelbrot.h"

void draw_frame(SDL_Texture *tex)
{
    void *pixels = 0;
    int pitch = 0;
    SDL_LockTexture(tex, NULL, &pixels, &pitch);

    Uint32 *pix = (Uint32 *)pixels;   //1 pixel - 4 bytes
    int len_str = pitch / 4;   //len_str in pixels

    SDL_PixelFormat *fmt = SDL_AllocFormat(SDL_PIXELFORMAT_ARGB8888);

    for (int py = 0; py < WIN_H; py++) 
    {
        for (int px = 0; px < WIN_W; px += 4) 
        {
            int iterations[4];
            mandelbrot_4pixels(px, py, iterations);
            
            for (int i = 0; i < 4 && (px + i) < WIN_W; i++) 
            {
                SDL_Color c = color_from_iter(iterations[i]);
                pix[py * len_str + (px + i)] = SDL_MapRGB(fmt, c.r, c.g, c.b);
            }
        }
    }

    SDL_FreeFormat(fmt);
    SDL_UnlockTexture(tex);
}