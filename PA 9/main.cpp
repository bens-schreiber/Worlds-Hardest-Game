
#include "raylib.h"
#include "const.h"
#include "Entity.hpp"
#include <vector>

int main(void)
{
    std::vector<Entity*> entities = {};

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    while (!WindowShouldClose())   
    {

        for (const auto& e : entities) {
            e->update();
            e->handleCollision(nullptr);
        }

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