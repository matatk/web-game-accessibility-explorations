?????????????
====

Here are several different programs that exemplify a game page. There are a few native programs (that don't interface with a screen-reader) and one web-based version (which does).

The native programs are:

 * `page-cli`: a simple text-based page.
 * `page-cli-fancy`: as above, but produces more ornate output (it was created to test the separation of rendering from the page structure).
 * `page-sdl`: a graphical version of the representative game page.

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

 * **Native:** either `./page-cli`, `./page-cli-fancy` or `./page-sdl`
 * **Web:** `make serve`, open the given URL

Learnings
---------

 * https://www.cs.rit.edu/~ats/books/ooc.pdf
 * [Object-oriented techniques in C](https://dmitryfrank.com/articles/oop_in_c)
 * [Classes in C](https://www.pvv.ntnu.no/~hakonhal/main.cgi/c/classes/)
 * [C Object Oriented Programming](https://nullprogram.com/blog/2014/10/21/)
 * [Tip 63: Seamlessly extend C structures](https://modelingwithdata.org/arch/00000113.htm)
 * https://stackoverflow.com/questions/46784479/c11-struct-inheritance-with-anonymous-struct
 * https://stackoverflow.com/questions/8932707/when-are-anonymous-structs-and-unions-useful-in-c11
 * https://stackoverflow.com/questions/17621544/dynamic-method-dispatching-in-c/17622474#17622474
 * https://softwareengineering.stackexchange.com/questions/204500/when-and-for-what-purposes-should-the-const-keyword-be-used-in-c-for-variables
