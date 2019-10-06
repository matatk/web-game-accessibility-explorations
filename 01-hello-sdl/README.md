Hello, SDL
==========

Super-simple "Hello, world!" sort-of program that uses SDL.

There are versions here for SDL 1.2 and SDL 2, supporting both native and Emscripten environments.

Unfortunately, the SDL 1.2 one doesn't work natively on the Mac (this appears to be somehow related to Mojave deprecating OpenGL, but I'm not sure why), but does work natively on Ubuntu and also works on the web.

Inversely, the SDL 2 version works fine natively on the Mac and Ubuntu, but not via Emscripten. I'm specifically interested in using SDL 1.2 though, because Emscripten has its own implementation of that API, which should keep things simple.

Install
-------

You can use `make install-deps` or follow the instructions below.

### Mac

`brew install sdl sdl2`

### Ubuntu

`sudo apt-get install libsdl1.2-dev libsdl2-dev`

Build
-----

`make` will build both native and web variants of the SDL 1.2 and SDL 2 versions.

Run
---

 * **Native:** `./hello-sdl1` and `./hello-sdl2`
 * **Web:** `make serve`, open the given URL and view "hello-sdl[12].html"
