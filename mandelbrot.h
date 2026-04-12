#ifndef MANDELBROT_H_INCLUDED
#define MANDELBROT_H_INCLUDED

//======================================
/**
∀ P_0 (pixel)
P_{n+1} = P_n ^ 2 + P_0
if |P_n| > L_max -> break
n -> color
draw(P_0, color)

pixel (px, py) -> c = x_0 +i*y_0

**/
//======================================

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <stdio.h>

//======================================
//param of window
//======================================
#define WIN_W  800
#define WIN_H  600

//iterations for check point in set(множество??)
#define N_MAX    256
//|z|^2 > 100
#define R2_MAX   100.0f     
#define BASE_DX  (1.0f / 800.0f)
#define BASE_DY  (1.0f / 800.0f)

#define INIT_ROI_X  (-1.325f)
#define INIT_ROI_Y  ( 0.0f)
#define INIT_SCALE  ( 1.0f)


#define MOVE_STEP       0.05f
#define MOVE_STEP_FAST  0.5f
#define ZOOM_FACTOR     0.9f

typedef struct 
{
    float roi_x;            //Re part
    float roi_y;            //Im part
    float scale;            //start = 1, zoom = 0.5
    int   dirty;            //flag drawing frame
} Mandelbrot;

int mandelbrot_pixel(int px, int py, const Mandelbrot *v);
SDL_Color color_from_iter(int n);
void draw_frame(SDL_Texture *tex, const Mandelbrot *v);
void render_ui(SDL_Renderer *rend, TTF_Font *font, double fps, const Mandelbrot *v);
void start_view(Mandelbrot *v);

#endif