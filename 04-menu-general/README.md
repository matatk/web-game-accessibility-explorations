?????????????
====

Here are several different programs that exemplify a game menu. There are a few native programs (that don't interface with a screen-reader) and one web-based version (which does).

The native programs are:

 * `menu-cli`: a simple text-based menu.
 * `menu-cli-fancy`: as above, but produces more ornate output (it was created to test the separation of rendering from the menu structure).
 * `menu-sdl`: a graphical version of the representative game menu.

The web scenario is based on the native SDL one, with an extra layer of code added (in both C and JavaScript) that creates DOM elements to act as proxies for the non-semantic entities in the game's code. A screen-reader will announce these controls as the user interacts with the game.

Design notes
------------

?????

Install
-------

You can use `make install-deps` or follow the instructions below.

### Mac

`brew install sdl sdl_ttf`

### Ubuntu

`sudo apt-get install libsdl1.2-dev libsdl-ttf2.0-dev`

Build
-----

Running `make` will build all scenarios

Run
---

 * **Native:** either `./menu-cli`, `./menu-cli-fancy` or `./menu-sdl`
 * **Web:** `make serve`, open the given URL
