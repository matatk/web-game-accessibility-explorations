Menu
====

Here are several different programs that exemplify a game menu. There are a few native programs (that don't interface with a screen-reader) and one web-based version (which does).

The native-only programs are:

 * `cli`: a simple text-based menu.
 * `cli-fancy`: as above, but produces more ornate output (it was created to test the separation of rendering from the menu structure).
 * `cli-sdl`: a graphical __FIXME__

The native and web scenario is a graphical menu, based on the native SDL one.
__FIXME__

Install
-------

### Mac

`brew install sdl sdl_ttf`

### Ubuntu

`sudo apt-get install libsdl1.2-dev libsdl-ttf2.0-dev`

Build
-----

Running `make` will build all scenarios

Run
---

 * **Native:** either `./cli`, `./cli-fancy` or `./sdl`
 * **Web:** `make serve`, open the given URL
