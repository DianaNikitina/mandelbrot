#include "mandelbrot.h"

//return number of iterations 


void mandelbrot_4pixels(int start_px, int py, int results[4])
{
    Mandelbrot *view = {0};
    float dx = BASE_DX * view->scale;       
    float dy = BASE_DY * view->scale;
    float x0[4] = {0}, y0[4] = {0};
    
    
    float y0_val = ((float)py - WIN_H/2.0f) * dy + view->roi_y;
    y0[0] = y0_val;
    y0[1] = y0_val;
    y0[2] = y0_val;
    y0[3] = y0_val;
    
    for (int i = 0; i < 4; i++) {
        x0[i] = ((float)(start_px + i) - WIN_W/2.0f) * dx + view->roi_x;
    }
    
    float x[4] = {x0[0], x0[1], x0[2], x0[3]};
    float y[4] = {y0[0], y0[1], y0[2], y0[3]};
    
    results[0] = results[1] = results[2] = results[3] = 0;
    
    for (int iter = 0; iter < N_MAX; iter++) {
        int any_active = 0;
        
        for (int i = 0; i < 4; i++) {
            float r2 = x[i]*x[i] + y[i]*y[i];
            if (r2 < R2_MAX) {
                any_active = 1;
                float old_x = x[i];
                x[i] = x[i]*x[i] - y[i]*y[i] + x0[i];
                y[i] = 2 * old_x * y[i] + y0[i];
                results[i]++;
            }
        }
        
        if (!any_active) break;
    }
}