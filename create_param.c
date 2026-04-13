#include "mandelbrot.h"

int create_param(Params *params)
{
    SDL_Window *window = params->window;
    SDL_Renderer *render = params->render;
    SDL_Texture *texture = params->texture;
    TTF_Font *font = params->font;
    window = SDL_CreateWindow("Mandelbrot — SDL2",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,WIN_W, WIN_H, SDL_WINDOW_SHOWN);
    if (!window)
    { 
        fprintf(stderr, "Window: %s\n", SDL_GetError()); 
        return 1;
    }

    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!render) 
    { 
        fprintf(stderr, "Renderer: %s\n", SDL_GetError()); 
        return 1; 
    }

    texture = SDL_CreateTexture(render ,SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIN_W, WIN_H);
    if (!texture) 
    { 
        fprintf(stderr, "Texture: %s\n", SDL_GetError()); 
        return 1; 
    }

    const char *font_paths[] = 
    {
        "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf",
        "/usr/share/fonts/TTF/DejaVuSansMono.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationMono-Regular.ttf",
        "/System/Library/Fonts/Menlo.ttc",
        NULL
    };
    
    for (int i = 0; font_paths[i]; i++) 
    {
        font = TTF_OpenFont(font_paths[i], 16);
        if (font) break;
    }
    if (!font)
        fprintf(stderr, "Warning: no font found, FPS overlay disabled\n");

    params->window = window;
    params->render = render;
    params->texture = texture;
    params->font = font;

    return 0;

}