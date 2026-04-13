#include "mandelbrot.h"

int main(void)
{
    Params params = {.window = NULL, .render = NULL, .texture = NULL, .font = NULL};

    init_param();

    create_param(&params);

    click_processing(&params);

    destroy(&params);
    return 0;
}