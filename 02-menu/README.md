Here are several different programs that exemplify a game menu.

There are a few native programs (that don't interface with a screen-reader) and one web-based version (which does).

 * Native programs:
   - `cli` is a simple text-based menu.
   - `cli-fancy` is as above, but produces more ornate output (it was created to test the separation of rendering from the menu structure).
   - `cli-sdl` is a graphical __FIXME__
 * The web-based program is a graphical menu, based on the native SDL one.

**Install:**

...FIXME: not currently needed; not up to this stage yet...

 * `brew install sdl`
 * `brew install sdl_ttf`

**Build:**

 * `make`

**Run:**

 * **Native:** `make run-native` will run `./cli` and then `./cli-fancy`
 * **Web:** `make serve`, open the given URL
