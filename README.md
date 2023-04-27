# WORLDS HARDEST GAME (WSU CPTS 122 PA 9)
DEVELOPERS: Benjamin Schreiber, Kendall Lyons, Andrew Mcgann, Andrew Varkey

Created as a class project. Takes inspiration from a browser game by the same name, but uses its own levels and adds in networking.
Utilizes the C raylib rendering library.
In essence, it is a game engine that takes in WHG files and turns them into playable levels.
The client game is composed of two threads, one for running the game and another responsible for starting and maintaning a TCP socket connection using Winsock2.
The Server is responsible for recieving a socket connection from the client, accepting the current player level and coordinates, 
and returning the postion of all other players in the same level as the player that is not the player.


# WORLD GENERATION CHARACTERS

@ - player spawnpoint (safezone)

T - automated test player

$ - safezone

% - endzone ( go to next level )

\# - normal block

R - linear ball on X axis going right

L - linear ball on X axis going left

U - linear ball on the Y axis going up

D - linear ball on the Y axis going down

C - Circular movement ball centered around title

K - Coin

## WHG FILE FORMAT
INTEGER MAP HEIGHT ( generally the amount of rows in the map )
TITLE
MAP INFO

## EXAMPLE
3
IMPOSSIBLE MAP
@\#\#\L
\#\#\#\L
\#\#\#\L

## WHGT FILE FORMAT
INTEGER MAP HEIGHT ( generally the amount of rows in the map )
COMMANDS (WASD)
TITLE
MAP INFO

## EXAMPLE
3
WASDWASDWASDWWWWWAAAASSSSDDDDDDDDD
IMPOSSIBLE MAP
@\#\#\L
\#\#\#\L
\#\#\#\L