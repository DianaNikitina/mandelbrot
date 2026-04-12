#include "mandelbrot.h"

//push button R -> start view

void start_view(Mandelbrot *v)
{
    v->roi_x = INIT_ROI_X;
    v->roi_y = INIT_ROI_Y;
    v->scale = INIT_SCALE;
    v->dirty = 1;
}