#include "mandelbrot.h"

void mm_set_ps (float mm[4], float val0, float val1, float val2, float val3)
{
    mm[0] = val0;
    mm[1] = val1;
    mm[2] = val2;
    mm[3] = val3;
}

void mm_set_psl (float mm[4], float val)
{
    for (int i = 0; i < 4; i++)
        mm[i] = val;
}

void mm_cpy_ps (float mm[4], const float mm2[4])
{
    for (int i = 0; i < 4; i++)
        mm[i] = mm2[i];
}

void mm_add_ps (float mm[4], const float mm1[4], const float mm2[4])
{
    for (int i = 0; i < 4; i++)
        mm[i] = mm1[i] + mm2[i];
}

void mm_sub_ps (float mm[4], const float mm1[4], const float mm2[4])
{
    for (int i = 0; i < 4; i++)
        mm[i] = mm1[i] - mm2[i];
}

void mm_mul_ps (float mm[4], const float mm1[4], const float mm2[4])
{
    for (int i = 0; i < 4; i++)
        mm[i] = mm1[i] * mm2[i];
}

void mm_add_epi32 (int mm[4], const int mm1[4], const float mm2[4])
{
    for (int i = 0; i < 4; i++)
        mm[i] = mm1[i] + (int)mm2[i];
}

void mm_cmp_le_ps (float cmp[4], const float mm1[4], const float mm2[4])
{
    for (int i = 0; i < 4; i++)
        cmp[i] = (mm1[i] <= mm2[i]) ? 1.0f : 0.0f;
}

int mm_movemask_ps (const float cmp[4])
{
    int mask = 0;
    for (int i = 0; i < 4; i++)
        mask |=(!!cmp[i] << i);
    return mask;
}

