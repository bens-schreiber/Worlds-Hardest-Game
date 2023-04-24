
#include "raylib.h"
#include "consts.hpp"
#include "Game.hpp"

int main(void)
{

    // Initial window size
    InitWindow(screenWidth, screenHeight, "Worlds Hardest Game - PA9 WSU");

    // Set our game to run at 60 frames-per-second
    SetTargetFPS(60);

    // List of all drawable and updateable entities 
    Game g;
    g.initialize();

    while (!WindowShouldClose())   
    {

        // Update all entities each frame
        g.update();
        
        BeginDrawing();
        
        // Draw all entities each frame
        g.draw();

        ClearBackground(mapBackground);

        EndDrawing();
    }

    CloseWindow();        

    return 0;
}