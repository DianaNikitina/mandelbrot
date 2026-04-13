#include "mandelbrot.h"

int main(void)
{
    Params params = {.window = NULL, .render = NULL, .texture = NULL, .font = NULL};

    init_param();

    create_param(&params);

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
                int mx = 0, my = 0;
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
            draw_frame(params.texture, &view);
            view.dirty = 0;
        }

       
        Uint64 now = SDL_GetPerformanceCounter();
        double dt  = (double)(now - prev) / (double)freq;
        prev = now;
        fps  = (dt > 0.0) ? 1.0 / dt : 0.0;

        SDL_RenderClear(params.render);
        SDL_RenderCopy(params.render, params.texture, NULL, NULL);
        draw_text(params.render, params.font, fps, &view);
        SDL_RenderPresent(params.render);
    }

    destroy(&params);
    return 0;
}