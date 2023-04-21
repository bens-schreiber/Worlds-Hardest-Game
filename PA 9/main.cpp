
#include "raylib.h"

int main(void)
{
    
    const int screenWidth = 1600;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "World's Hardest Game");

    SetTargetFPS(60);            
    

    // Main game loop
    while (!WindowShouldClose())   
    {

        BeginDrawing();

        ClearBackground(RAYWHITE);

        EndDrawing();
    }

    CloseWindow();        

    return 0;
}