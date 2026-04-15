#include "mandelbrot.h"

int main()
{
    Params params = {.window = NULL, .render = NULL, .texture = NULL, .font = NULL};

    grafic_init();

    grafic_create(&params);

    click_processing(&params);

    destroy(&params);
    return 0;
}