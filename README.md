Web Game Accessibility Explorations
===================================

Exploring the possibilities for providing semantic information from games compiled for the web to players' assistive technologies.

**You may want to check out the [live demo of a general menu and widget set](http://matatk.agrip.org.uk/web-game-accessibility-explorations/page-sdl.html).** (The code for that is in the `04-menu-general` directory.)

Pre-requisites
--------------

On top of the below, the individual examples have differing dependencies; info can be found in each of their READMEs.

### Mac & Ubuntu

It's possible to install emscripten via `brew` (Mac) or `apt-get` (Ubuntu) but I have found configuration problems when doing so, so recommend the officially-supported way...

 * `git clone https://github.com/emscripten-core/emsdk`
 * `cd emsdk`
 * `./emsdk install 1.38.46-upstream`
 * `./emsdk activate 1.38.46-upstream`
 * Add `/directory/where/you/cloned/emsdk/emsdk_env.sh > /dev/null` to your shell start-up script and restart your shell.

### Mac

 * `brew install cppcheck`

### Ubuntu

 * `sudo apt-get install cppcheck`

### Set-up for this repo

 * `npm install`

Tests/Support
-------------

Some simple tests for style consistency and linting are run via `npm test` and on pre-commit.

This has been run/tested on macOS (Mojave) and Ubuntu (19.04).

Background and acknowledgements
-------------------------------

The ideas explored here were presented and discussed at the [W3C Workshop on Web Games](https://www.w3.org/2018/12/games-workshop/). Thanks to everyone who helped with [our position paper, "Adaptive Accessibility"](https://www.w3.org/2018/12/games-workshop/papers/web-games-adaptive-accessibility.html), and to the workshop attendees for introducing us to approaches that can realise these aspirations.

Thanks to [The Paciello Group](https://www.paciellogroup.com/) for making this possible by supporting my involvement in and attendance of the workshop.

For more background on this and several other game accessibility matters, you might like to read my [technical summary of the workshop from an accessibility perspective](http://matatk.agrip.org.uk/articles/w3c-workshop-on-web-games/).
