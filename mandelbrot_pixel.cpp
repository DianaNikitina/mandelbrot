#include "mandelbrot.h"
#ifdef DEBUG_PIXEL

//return number of iterations 

int mandelbrot_intrinsic(int px, int py, const Mandelbrot *v)
{
    float dx = BASE_DX * v->scale;          //size pixel with zoom
    float dy = BASE_DY * v->scale;


    //pixel -> c-plane
    float x0 = ((float)px - WIN_H / 2.0f) * dx + v->roi_x;
    float y0 = ((float)py - WIN_W / 2.0f) * dy + v->roi_y;

    float x = x0, y = y0;
    int n = 0;

    for (n = 0; n < N_MAX; n++) 
    {
        float x2 = x * x;
        float y2 = y * y;
        float xy = x * y;
        float r2 = x2 + y2;
        if (r2 >= R2_MAX) break;        //if not in plane -> break
        x = x2 - y2 + x0;               // Re(z^2 + c)
        y = xy + xy  + y0;              //IM(z^2 + c)
    }
    return n;
}

#endif