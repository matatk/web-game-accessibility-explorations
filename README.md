Web Game Accessibility Explorations
===================================

Exploring the possibilities for providing semantic information from games compiled for the web to players' assistive technologies.

Pre-requisites
--------------

### To install Emscripten

 * `git clone https://github.com/emscripten-core/emsdk`
 * `cd emsdk`
 * `./emsdk install 1.38.46-upstream`
 * `./emsdk activate 1.38.46-upstream`
 * Add `/directory/where/you/cloned/emsdk/emsdk_env.sh > /dev/null` to your shell start-up script and restart your shell.

You can also issue `./emsdk help` for more info. It's recommended to put the "emsdk" checked-out repo directory on your PATH.

### Set-up for this repo

 * `npm install`
 * `brew install cppcheck`

Tests/Support
-------------

Some simple tests for style consistency and linting are run via `npm test` and on pre-commit.

This has been run/tested on macOS (Mojave).

Background and acknowledgements
-------------------------------

The ideas explored here were presented and discussed at the [W3C Workshop on Web Games](https://www.w3.org/2018/12/games-workshop/). Thanks to everyone who helped with [our position paper, "Adaptive Accessibility"](https://www.w3.org/2018/12/games-workshop/papers/web-games-adaptive-accessibility.html), and to the workshop attendees for introducing us to approaches that can realise these aspirations.

Thanks to [The Paciello Group](https://www.paciellogroup.com/) for making this possible by supporting my involvement in and attendance of the workshop.

For more background on this and several other game accessibility matters, you might like to read my [technical summary of the workshop from an accessibility perspective](http://matatk.agrip.org.uk/articles/w3c-workshop-on-web-games/).
