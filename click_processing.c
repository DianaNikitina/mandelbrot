#include "mandelbrot.h"

int click_processing(Params *params)
{
    Mandelbrot view;
    start_view(&view);

    Uint64 freq = SDL_GetPerformanceFrequency();
    Uint64 prev = SDL_GetPerformanceCounter();          //prev frame
    double fps  = 0.0;                                  //current value fps

    int running = 1;
    SDL_Event event;

    while (running) 
    {
        while (SDL_PollEvent(&event)) 
        {
            switch (event.type) 
            {

            case SDL_QUIT:
                running = 0;
                break;

            case SDL_KEYDOWN: 
            {
                SDL_Keycode key = event.key.keysym.sym;
                SDL_Keymod  mod = event.key.keysym.mod;

                int shift = (mod & KMOD_SHIFT) != 0;
                float step = shift ? MOVE_STEP_FAST : MOVE_STEP;

                switch (key) {
                case SDLK_ESCAPE:
                case SDLK_q:
                    running = 0;
                    break;

                case SDLK_r:
                    start_view(&view);
                    break;

                case SDLK_RIGHT:
                    view.roi_x += step * view.scale;
                    view.dirty = 1;
                    break;
                case SDLK_LEFT:
                    view.roi_x -= step * view.scale;
                    view.dirty = 1;
                    break;
                case SDLK_DOWN:
                    view.roi_y += step * view.scale;
                    view.dirty = 1;
                    break;
                case SDLK_UP:
                    view.roi_y -= step * view.scale;
                    view.dirty = 1;
                    break;

                case SDLK_z: 
                {
                    float factor;
                    if (shift)
                        factor = 1.0f / ZOOM_FACTOR;
                    else
                        factor = ZOOM_FACTOR;

                    view.scale *= factor;
                    view.dirty = 1;
                    break;
                }
                }
                break;
            }
            }
        }

     
        if (view.dirty) 
        {
            draw_frame(params->texture);
            view.dirty = 0;
        }

       
        Uint64 now = SDL_GetPerformanceCounter();
        double dt  = (double)(now - prev) / (double)freq;
        prev = now;
        fps  = (dt > 0.0) ? 1.0 / dt : 0.0;

        SDL_RenderClear(params->render);
        SDL_RenderCopy(params->render, params->texture, NULL, NULL);
        draw_text(params->render, params->font, fps, &view);
        SDL_RenderPresent(params->render);

    }

    return 0;
}