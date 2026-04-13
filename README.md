# Mandelbrot

Mandelbrot set visualization using **SDL2**.

## SDL graphics library

<img width="809" height="638" alt="image" src="https://github.com/user-attachments/assets/ba8dd3e3-b421-414d-bb12-139589cb44e9" />

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

### `TTF_RenderUTF8_Blended`

Allocate a new 32-bit, ARGB surface, using alpha blending to dither the font with the given color.

<img width="600" height="78" alt="image" src="https://github.com/user-attachments/assets/41b03e79-7c36-4e73-9166-de27b2f39ce7" />


## `SDL_Rect`

Draw rectangle as a background for text (FPS, Scale, ROI).

<img width="302" height="158" alt="image" src="https://github.com/user-attachments/assets/7ed1b417-cf00-457b-81ed-917107f69c15" />

## `SDL_SetRenderDrawBlendMode`

<img width="905" height="52" alt="image" src="https://github.com/user-attachments/assets/ccf709bd-759d-4739-842f-07607a40864f" />

## `

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
