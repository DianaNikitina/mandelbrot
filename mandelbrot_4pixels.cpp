#include "mandelbrot.h"

//return number of iterations


void mandelbrot_4pixels(const Mandelbrot *view, int start_px, int py, int results[4])
{
    float dx = BASE_DX * view->scale;       
    float dy = BASE_DY * view->scale;
    float x0[4] = {0, 0, 0, 0}, y0[4] = {0, 0, 0, 0};
    
    for (int i = 0; i < 4; i++) 
        results[i] = 0;
    float y0_val = ((float)py - WIN_H/2.0f) * dy + view->roi_y;
    mm_set_psl(y0, y0_val);

    float vector[4] = {0, 1, 2, 3};
    float arr_start_px[4] = {0, 0, 0, 0};
    float arr_WIN_W[4] = {0, 0, 0, 0};
    float arr_dx[4] = {0, 0, 0, 0};
    float arr_view[4] = {0, 0, 0, 0};
    mm_set_psl(arr_start_px, (float)start_px);
    mm_set_psl(arr_WIN_W, WIN_W/2.0f);
    mm_set_psl(arr_dx, dx);
    mm_set_psl(arr_view, view->roi_x);
    mm_add_ps(x0, vector, arr_start_px);
    mm_sub_ps(x0, x0, arr_WIN_W);
    mm_mul_ps(x0, x0, arr_dx);
    mm_add_ps(x0, x0, arr_view);

    
    float x[4] = {0, 0, 0, 0};
    float y[4] = {0, 0, 0, 0};
    float r2[4] = {0, 0, 0, 0};
    mm_cpy_ps(x, x0);
    mm_cpy_ps(y, y0);
    
    float cpy_x[4] = {0, 0, 0, 0};
    float cpy_y[4] = {0, 0, 0, 0};
    float arr_R2_MAX[4] = {R2_MAX, R2_MAX, R2_MAX, R2_MAX};
    float mask[4] = {0};
    
    for (int iter = 0; iter < N_MAX; iter++) 
    {
        
        mm_cpy_ps(cpy_y, y);
        mm_cpy_ps(cpy_x, x);
        mm_mul_ps(x, x, x);
        mm_mul_ps(y, y, y);
        mm_add_ps(r2, x, y);
        
        mm_cmp_le_ps (mask, r2, arr_R2_MAX);
        int bits = mm_movemask_ps(mask);
        if (bits == 0)
            break;
        for (int i = 0; i < 4; i++) 
        {
            if (mask[i]) {
                float x2 = x[i];       
                float y2 = y[i];   
                float old_x = cpy_x[i];
                float old_y = cpy_y[i];

                x[i] = x2 - y2 + x0[i];
                y[i] = 2.0f * old_x * old_y + y0[i];

                results[i]++;
            }
        }
      
    }
}