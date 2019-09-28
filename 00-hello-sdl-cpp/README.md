Hello, SDL
==========

Super-simple "Hello, world!" sort-of program that uses SDL.

There are versions here for SDL 1.2 and SDL 2, supporting both native and Emscripten environments.

Unfortunately, the SDL 1.2 one doesn't work natively on the Mac (Mojave deprecated OpenGL, and the blank-window issue looks similar, but I'm not requesting OpenGL, so it's likely me doing something wrong), but does work on the web.

Inversely, the SDL 2 version works fine natively on the Mac, but not in Emscripten. I'm specifically interested in using SDL 1.2 though, because Emscripten has its own implementation of that API, which should keep things simple.

Install
-------

`brew install sdl sdl2`

Build
-----

`make` will build both native and web variants of the SDL 1.2 and SDL 2 versions.

Run
---

 * **Native:** `./emtestsdl1` and `./emtestsdl2`
 * **Web:** `make serve`, open the given URL and view "emtestsdl[12].html"
