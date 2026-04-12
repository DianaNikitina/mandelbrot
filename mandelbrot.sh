gcc -O2 -o run mandelbrot.c mandelbrot_pixel.c draw_frame.c start_view.c render_ui.c sdl_color.c $(sdl2-config --cflags --libs) -lSDL2_ttf -lm
