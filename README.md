# mandelbrot
SDL - graphic library

Color
<img width="389" height="249" alt="image" src="https://github.com/user-attachments/assets/fb35f35a-5b42-4c3b-b999-84ff1de70aa3" />

LockTexture 
(give temporary buffer for write pixels)
NULL - Lock all texture
tex - address on texture
&pixels - address on start array of pixels
&pitch - len one str in bytes
<img width="630" height="119" alt="image" src="https://github.com/user-attachments/assets/a1fec013-d410-4dc9-b4b2-41e1a6098a86" />

AllocFormat
<img width="1219" height="63" alt="image" src="https://github.com/user-attachments/assets/23025bc0-e459-4af8-b364-7d31d0380f3a" />
creates and initializes a pixel format description structure
inside - 1) size of pixel in bytes
2)place bits R G B A
3)mask for each channel

MapRGB
<img width="1372" height="77" alt="image" src="https://github.com/user-attachments/assets/1e8a3bd3-99fe-4f3b-b0ad-957eb2c279f1" />
format - address on SDL_PixelFormat
r, g, b - value of channels (0, ... , 255)

FreeFormat
<img width="520" height="63" alt="image" src="https://github.com/user-attachments/assets/d1ea75be-e95d-44d3-b412-7e3e51544724" />
free memory 




main()
|
--> reset_view()          — заполнить структуру Mandelbrot
|
--> while(running)
    |--> SDL_PollEvent()   — клавиши/мышь -> меняют view, dirty=1
    |
    |--> dirty? → render_frame()
    |            --> для каждого пикселя:
    |            |   mandelbrot_pixel() -> n
    |            |   color_from_iter(n) -> цвет
    |            --> записать цвет в текстуру
    |
    --> FPS = 1 / dt
    │
    --> SDL_RenderCopy() + render_ui() --> SDL_RenderPresent()
