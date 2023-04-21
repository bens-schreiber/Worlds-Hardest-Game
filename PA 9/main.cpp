
#include "raylib.h"
#include "const.h"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------


    InitWindow(screenWidth, screenHeight, "raylib [core] example - keyboard input");

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