g++ -D _DEBUG -ggdb3 -std=c++17 -O3 -Wall -g -Wextra \
    -mavx2 -mavx \
    mandelbrot.cpp mandelbrot_intrinsic.cpp mandelbrot_4pixels_func.cpp \
    mandelbrot_4pixels.cpp mandelbrot_pixel.cpp draw_frame.cpp \
    start_view.cpp grafic_init.cpp draw_text.cpp click_processing.cpp destroy.cpp \
    create_param.cpp sdl_color.cpp intrinsic.cpp \
    $(sdl2-config --cflags --libs) -lSDL2_ttf \
    -o run