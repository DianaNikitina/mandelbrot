#include "mandelbrot.h"

int main()
{
    Params params = {.window = NULL, .render = NULL, .texture = NULL, .font = NULL};

    grafic_init();

    create_param(&params);

    click_processing(&params);

    destroy(&params);
    return 0;
}