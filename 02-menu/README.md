Menu
====

Here are several different programs that exemplify a game menu. There are a few native programs (that don't interface with a screen-reader) and one web-based version (which does).

The native programs are:

 * `menu-cli`: a simple text-based menu.
 * `menu-cli-fancy`: as above, but produces more ornate output (it was created to test the separation of rendering from the menu structure).
 * `menu-sdl`: a graphical version of the representative game menu.

The web scenario is based on the native SDL one, with an extra layer of code added (in both C and JavaScript) that creates DOM elements to act as proxies for the non-semantic entities in the game's code. A screen-reader will announce these controls as the user interacts with the game.

Design notes
------------

The game remains the primary focus of interaction: i.e. it receives all keyboard events. This is by design: whilst the proxy DOM elements are visible on the demo page, the expectation is that most games would run full-screen (or at least full-window). The proxy elements wouldn't normally be seen or interacted with in the standard manner using the screen-reader's virtual cursor (in fact, when the Accessibility Object Model is used, they wouldn't appear at all).

This does mean that screen-reader users can't use their virtual cursor to investigate the UI and interact with it, which is a limitation, but it seems acceptable on the basis that:

 * It's technically *very* difficult to do the communication back into the game from the web; I don't think this would fit the model of how games work currently, so it would add friction to the making-it-accessible process.
 * The game already needs to allow the user to explore all of the UI via effectively the keyboard (even if the "keyboard" is a game controller) and it makes sense for the game to manage the presentation/focus within that.
 * The game _could_ add some keyboard shortcuts to allow the user to skip between headings, or regions that are like landmarks, for example.

Of course it would be great if we can get the two-way communication and virtual cursor and game in future.

Note: `role="application"` is set on the `<body>` to ensure that the keyboard events go to the game.

This accessibility code layer is written fairly generically, though only supports menus at the moment. Future explorations will work towards generalising it.

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
