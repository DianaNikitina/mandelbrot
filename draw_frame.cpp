#include "mandelbrot.h"

void draw_frame(const Mandelbrot *view, SDL_Texture *tex)
{

    Uint64 start;
    Uint64 end;
    start = SDL_GetPerformanceCounter();
    
    #ifdef DEBUG_NOT_SAMPLE_TIME
    void *pixels = 0;
    int pitch = 0;
    SDL_LockTexture(tex, NULL, &pixels, &pitch);
    Uint32 *pix = (Uint32 *)pixels;   //1 pixel - 4 bytes
    int len_str = pitch / 4;   //len_str in pixels
    SDL_PixelFormat *fmt = SDL_AllocFormat(SDL_PIXELFORMAT_ARGB8888);
    #endif

    
    #ifdef DEBUG_PIXEL
    SDL_Color arr_c [480000]; 
    for (int py = 0; py < WIN_H; py++) 
    {
        for (int px = 0; px < WIN_W; px++) 
        {
            int n = mandelbrot_intrinsic(px, py, view);
            SDL_Color c = color_from_iter(n);
            arr_c [py * WIN_W + px] = c;
        }
    }

    #else
    SDL_Color arr_c [1920000]; 
    for (int py = 0; py < WIN_H; py++) 
        for (int px = 0; px < WIN_W; px += 4) 
        {
            int iterations[4] = {};
            mandelbrot_intrinsic(view, px, py, iterations);
            
            for (int i = 0; i < 4 && (px + i) < WIN_W; i++) 
            {
                SDL_Color c = color_from_iter(iterations[i]);
                arr_c [i + py * WIN_W + px] = c;
            }
        }
    #endif

    
    #ifdef DEBUG_NOT_SAMPLE_TIME
    #ifdef DEBUG_PIXEL
    for (int py = 0; py < WIN_H; py++)
    {
        for (int px = 0; px < WIN_W; px++)
        {
            pix[py * len_str + px] = SDL_MapRGB(fmt, arr_c[py * WIN_W + px].r, arr_c[py * WIN_W + px].g, arr_c[py * WIN_W + px].b);
        }
    }
    #else
    for (int py = 0; py < WIN_H; py++)
    {
        for (int px = 0; px < WIN_W; px++)
        {
            for (int i = 0; i < 4 && (px + i) < WIN_W; i++) 
            {
                pix[py * len_str + (px + i)] = SDL_MapRGB(fmt, arr_c[py * WIN_W + px + i].r, arr_c[py * WIN_W + px + i].g, arr_c[py * WIN_W + px + i].b);
            }
        }
    }

    SDL_FreeFormat(fmt);
    SDL_UnlockTexture(tex);
    #endif
    #endif

    end = SDL_GetPerformanceCounter();
    double delta = (double)(end - start) / (double)SDL_GetPerformanceFrequency();
    printf("intrinsic time: %.9f sec\n", delta);
}