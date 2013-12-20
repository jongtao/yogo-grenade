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

This is the Windows build, which was compiled on an x86 Windows 7 machine!
Run the executable "yogo-grenade.exe" to play the game!
You MUST have "map.txt" and the "resources" folder in its directory.


Compiling the Game
==================

This game was made with the Allegro 5.1 game library.
You must have this library installed in order to compile.
Simply compile the game and link Allegro with your IDE or compiler.

Visual Studio Note:
I used sprintf(), which VS thinks is "unsafe".

