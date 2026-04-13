#include "mandelbrot.h"

void draw_frame(SDL_Texture *tex, const Mandelbrot *v)
{
    void *pixels = 0;
    int pitch = 0;
    SDL_LockTexture(tex, NULL, &pixels, &pitch);

    Uint32 *pix = (Uint32 *)pixels;   //1 pixel - 4 bytes
    int len_str = pitch / 4;   //len_str in pixels

    SDL_PixelFormat *fmt = SDL_AllocFormat(SDL_PIXELFORMAT_ARGB8888);

    for (int py = 0; py < WIN_H; py++) 
    {
        for (int px = 0; px < WIN_W; px++) 
        {
            int n = mandelbrot_pixel(px, py, v);
            SDL_Color c = color_from_iter(n);
            pix[py * len_str + px] = SDL_MapRGB(fmt, c.r, c.g, c.b);
        }
    }

    SDL_FreeFormat(fmt);
    SDL_UnlockTexture(tex);
}