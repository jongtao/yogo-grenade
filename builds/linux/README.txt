Yogo Grenade
============

This is a Ludum Dare 28 Entry!

Yogo Grenade is short for "You Only Get One Holy Hand Grenade"!
The goal of the game is to stay alive for as long as possible!



Making Your Own Maps
===========

You can make your own maps!
It's just a text file!
There's the map.txt as an example.
'M' are the wall tiles and, 'S' is the player spawn, and 'E' is Rabbit spawn.
Don't put more than 256 characters for each line or over 1024 lines.
I didn't get to rewriting my C arrays to grow dynamically.


Running the Game
================

This is the Linux build, which was compiled on an x86 Debian machine!
Run the executable "yogo-grenade" to play the game!
You MUST have "map.txt" and the "resources" folder in its directory.

The most common missing dependency is "libdumb1".
Make sure you have it installed before you run the game.

On any Linux distribution just use your favourite package manager!
For instance, on Ubuntu or any Debian-like distribution, the command is "apt-get install libdumb1"

If your machine is behind on shared libraries, use "ldd yogo-grenade" to see all of its dependencies.


Compiling the Game
==================

This game was made with the Allegro 5.1 game library.
You must have this library installed in order to compile.
Once Allegro is installed, change your directory to ludumdare28.
In the "Makefile", choose the "LIB" line to the static or dynamic one.
Make a "build" folder in the same directory and run "make".
This will create a "yogo-grenade" executable in your current directory.
