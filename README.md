# Mandelbrot

Mandelbrot set visualization using **SDL2**.

## SDL graphics library

### Color

<img src="https://github.com/user-attachments/assets/fb35f35a-5b42-4c3b-b999-84ff1de70aa3" alt="Color example" width="420">

### `SDL_LockTexture`

Gives a temporary buffer for writing pixels into the texture.

- `NULL` — lock the whole texture
- `tex` — pointer to the texture
- `&pixels` — address of the beginning of the pixel buffer
- `&pitch` — length of one row in bytes

<img src="https://github.com/user-attachments/assets/a1fec013-d410-4dc9-b4b2-41e1a6098a86" alt="SDL_LockTexture" width="700">

### `SDL_AllocFormat`

Creates and initializes a pixel format description structure.

It contains:
- pixel size in bytes
- bit positions of `R`, `G`, `B`, `A`
- mask for each channel

<img src="https://github.com/user-attachments/assets/23025bc0-e459-4af8-b364-7d31d0380f3a" alt="SDL_AllocFormat" width="900">

### `SDL_MapRGB`

Maps RGB channel values into a pixel value according to `SDL_PixelFormat`.

- `format` — pointer to `SDL_PixelFormat`
- `r`, `g`, `b` — channel values in range `0..255`

<img src="https://github.com/user-attachments/assets/1e8a3bd3-99fe-4f3b-b0ad-957eb2c279f1" alt="SDL_MapRGB" width="900">

### `SDL_FreeFormat`

Frees the memory allocated for `SDL_PixelFormat`.

<img src="https://github.com/user-attachments/assets/d1ea75be-e95d-44d3-b412-7e3e51544724" alt="SDL_FreeFormat" width="520">

## Program flow

```text
main()
|
|--> reset_view()          — initialize Mandelbrot structure
|
|--> while (running)
     |--> SDL_PollEvent()  — keyboard/mouse input changes view, dirty = 1
     |
     |--> dirty ? render_frame()
     |            |--> for each pixel:
     |            |    mandelbrot_pixel() -> n
     |            |    color_from_iter(n) -> color
     |            |--> write color into texture
     |
     |--> FPS = 1 / dt
     |
     |--> SDL_RenderCopy() + render_ui()
     |--> SDL_RenderPresent()
```

## Notes

- `pitch` is the size of one row in **bytes**
- texture writing is done through `SDL_LockTexture`
- colors are created with `SDL_MapRGB`
- pixel format must be freed with `SDL_FreeFormat`
