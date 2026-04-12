#include "mandelbrot.h"

int main(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
        return 1;
    }
    if (TTF_Init() < 0) 
    {
        fprintf(stderr, "TTF_Init: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow(
        "Mandelbrot — SDL2",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WIN_W, WIN_H, SDL_WINDOW_SHOWN);
    if (!win) { fprintf(stderr, "Window: %s\n", SDL_GetError()); return 1; }

    SDL_Renderer *rend = SDL_CreateRenderer(
        win, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!rend) { fprintf(stderr, "Renderer: %s\n", SDL_GetError()); return 1; }

    SDL_Texture *tex = SDL_CreateTexture(
        rend,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        WIN_W, WIN_H);
    if (!tex) { fprintf(stderr, "Texture: %s\n", SDL_GetError()); return 1; }

    /* ищем системный шрифт для FPS-оверлея */
    TTF_Font *font = NULL;
    const char *font_paths[] = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf",
        "/usr/share/fonts/TTF/DejaVuSansMono.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationMono-Regular.ttf",
        "/System/Library/Fonts/Menlo.ttc",
        NULL
    };
    for (int i = 0; font_paths[i]; i++) {
        font = TTF_OpenFont(font_paths[i], 16);
        if (font) break;
    }
    if (!font)
        fprintf(stderr, "Warning: no font found, FPS overlay disabled\n");

    Mandelbrot view;
    start_view(&view);

    /* drag-состояние */
    int   dragging = 0;
    int   drag_sx = 0, drag_sy = 0;
    float drag_rx = 0.0f, drag_ry = 0.0f;

    /* FPS */
    Uint64 freq = SDL_GetPerformanceFrequency();
    Uint64 prev = SDL_GetPerformanceCounter();
    double fps  = 0.0;

    int running = 1;
    SDL_Event ev;

    while (running) {
        
        while (SDL_PollEvent(&ev)) {
            switch (ev.type) {

            case SDL_QUIT:
                running = 0;
                break;

            case SDL_KEYDOWN: {
                int   shift = (ev.key.keysym.mod & KMOD_SHIFT) != 0;
                float step  = shift ? MOVE_STEP_FAST : MOVE_STEP;
                switch (ev.key.keysym.sym) {
                case SDLK_ESCAPE:
                case SDLK_q:
                    running = 0;
                    break;
                case SDLK_r:
                    start_view(&view);
                    break;
                case SDLK_RIGHT:
                    view.roi_x += step * view.scale; view.dirty = 1; break;
                case SDLK_LEFT:
                    view.roi_x -= step * view.scale; view.dirty = 1; break;
                case SDLK_DOWN:
                    view.roi_y += step * view.scale; view.dirty = 1; break;
                case SDLK_UP:
                    view.roi_y -= step * view.scale; view.dirty = 1; break;
                case SDLK_z:
                    view.scale *= shift ? ZOOM_FACTOR : (1.0f / ZOOM_FACTOR);
                    view.dirty = 1;
                    break;
                }
                break;
            }

            case SDL_MOUSEBUTTONDOWN:
                if (ev.button.button == SDL_BUTTON_LEFT) {
                    dragging = 1;
                    drag_sx  = ev.button.x;
                    drag_sy  = ev.button.y;
                    drag_rx  = view.roi_x;
                    drag_ry  = view.roi_y;
                }
                break;

            case SDL_MOUSEBUTTONUP:
                if (ev.button.button == SDL_BUTTON_LEFT)
                    dragging = 0;
                break;

            case SDL_MOUSEMOTION:
                if (dragging) {
                    float dx = BASE_DX * view.scale;
                    float dy = BASE_DY * view.scale;
                    view.roi_x = drag_rx - (ev.motion.x - drag_sx) * dy;
                    view.roi_y = drag_ry - (ev.motion.y - drag_sy) * dx;
                    view.dirty = 1;
                }
                break;

            case SDL_MOUSEWHEEL: {
                int mx, my;
                SDL_GetMouseState(&mx, &my);
                float factor = (ev.wheel.y > 0)
                    ? ZOOM_FACTOR : (1.0f / ZOOM_FACTOR);

                float dx = BASE_DX * view.scale;
                float dy = BASE_DY * view.scale;
                float wx = view.roi_x + (mx - WIN_W / 2.0f) * dy;
                float wy = view.roi_y + (my - WIN_H / 2.0f) * dx;

                view.scale *= factor;

                dx = BASE_DX * view.scale;
                dy = BASE_DY * view.scale;
                view.roi_x = wx - (mx - WIN_W / 2.0f) * dy;
                view.roi_y = wy - (my - WIN_H / 2.0f) * dx;
                view.dirty = 1;
                break;
            }
            }
        }

     
        if (view.dirty) {
            draw_frame(tex, &view);
            view.dirty = 0;
        }

       
        Uint64 now = SDL_GetPerformanceCounter();
        double dt  = (double)(now - prev) / (double)freq;
        prev = now;
        fps  = (dt > 0.0) ? 1.0 / dt : 0.0;

        SDL_RenderClear(rend);
        SDL_RenderCopy(rend, tex, NULL, NULL);
        render_ui(rend, font, fps, &view);
        SDL_RenderPresent(rend);
    }

    if (font) TTF_CloseFont(font);
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    TTF_Quit();
    SDL_Quit();
    return 0;
}