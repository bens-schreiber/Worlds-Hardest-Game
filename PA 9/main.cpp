
#include "raylib.h"
#include "const.h"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------


    InitWindow(screenWidth, screenHeight, "raylib [core] example - keyboard input");

    std::vector<Entity*> entities = {};

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())   
    {

        for (const auto& e : entities) {
            e->update();
            e->handleCollision(nullptr);
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        for (const auto& e : entities) {
            e->draw();
        }

        ClearBackground(RAYWHITE);

        EndDrawing();
    }

    CloseWindow();        

    return 0;
}