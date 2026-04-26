#include "mandelbrot.h"
# ifdef DEBUG_INTRINSIC

//return number of iterations


void mandelbrot_intrinsic(const Mandelbrot *view, int start_px, int py, int results[4])
{
    float dx = BASE_DX * view->scale;       
    float dy = BASE_DY * view->scale;

    results[0] = results[1] = results[2] = results[3] = 0;


    float y0_val = ((float)py - WIN_H/2.0f) * dy + view->roi_y;
    __m128 y0 = _mm_set1_ps(y0_val);
    

    __m128 vector = _mm_set_ps (3.0f, 2.0f, 1.0f, 0.0f);
    __m128 start = _mm_set1_ps((float)start_px);
    __m128 halfW = _mm_set1_ps(WIN_W / 2.0f);
    __m128 arr_dx = _mm_set1_ps(dx);
    __m128 roi_x = _mm_set1_ps(view->roi_x);

    __m128 x0 = _mm_add_ps(vector, start);
    x0 = _mm_sub_ps(x0, halfW);                 
    x0 = _mm_mul_ps(x0, arr_dx);                    
    x0 = _mm_add_ps(x0, roi_x);  

    __m128 x = x0;
    __m128 y = y0;
    __m128 r2 = _mm_setzero_ps();
    __m128 R2_MAX_v = _mm_set1_ps(R2_MAX);

    __m128i iter_vec = _mm_setzero_si128();

    for (int iter = 0; iter < N_MAX; ++iter)
    {
        __m128 old_x = x;
        __m128 old_y = y;

        __m128 xx = _mm_mul_ps(x, x);
        __m128 yy = _mm_mul_ps(y, y);
        r2 = _mm_add_ps(xx, yy);

        __m128 mask_ps = _mm_cmple_ps(r2, R2_MAX_v);
        int mask_bits = _mm_movemask_ps(mask_ps);
        if (mask_bits == 0)
            break;

        __m128i mask_i = _mm_castps_si128(mask_ps);
        iter_vec = _mm_sub_epi32(iter_vec, mask_i);

        __m128 xy = _mm_mul_ps(old_x, old_y);
        __m128 x2 = xx;
        __m128 y2 = yy;
        __m128 x_new = _mm_add_ps(_mm_sub_ps(x2, y2), x0);
        __m128 y_new = _mm_add_ps(_mm_add_ps(xy, xy), y0);

        __m128 alive_mask = mask_ps;
        __m128 dead_mask = _mm_andnot_ps(mask_ps, _mm_castsi128_ps(_mm_set1_epi32(-1)));

        __m128 x_alive = _mm_and_ps(x_new, alive_mask);
        __m128 x_dead  = _mm_and_ps(old_x, dead_mask);
        x = _mm_or_ps(x_alive, x_dead);

        __m128 y_alive = _mm_and_ps(y_new, alive_mask);
        __m128 y_dead  = _mm_and_ps(old_y, dead_mask);
        y = _mm_or_ps(y_alive, y_dead);
    }

    _mm_storeu_si128((__m128i*)results, iter_vec); // TODO: unaligned store

}

#endif