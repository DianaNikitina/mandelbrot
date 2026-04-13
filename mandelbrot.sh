gcc -O2 -o run mandelbrot.c mandelbrot_pixel.c draw_frame.c start_view.c init_param.c draw_text.c destroy.c create_param.c sdl_color.c $(sdl2-config --cflags --libs) -lSDL2_ttf -lm
