Web Game Accessibility
======================

This repo contains some explorations around providing accessibility information from games compiled for the web (with WebAssembly) to players' assistive technologies (such as screen readers, screen magnifiers and so on).

Pre-requisites
--------------

### To install Emscripten

 * `git clone https://github.com/emscripten-core/emsdk`
 * `cd emsdk`
 * `./emsdk install latest-upstream`
 * `./emsdk activate latest-upstream`
 * Restart your shell

You can also issue `./emsdk help` for more info. It's recommended to put the "emsdk" checked-out repo directory on your PATH.

### Set-up for this repo

 * `npm install`
 * `brew install cppcheck`

Tests/Support
-------------

Some simple tests for style consistency and linting are run via `npm test` and on pre-commit.

This has been run/tested on macOS (Mojave).
