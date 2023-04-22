
#include "raylib.h"
#include "const.h"
#include "Entity.hpp"
#include "Player.hpp"
#include "EnemyBall.hpp"
#include <vector>

int main(void)
{
    Player* p = new Player();
    std::vector<Entity*> entities = {
        p, 
        new EnemyBall(p, { screenWidth / 2, screenHeight / 2}, {5,5})
    };

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    while (!WindowShouldClose())   
    {

        for (const auto& e : entities) {
            e->update();
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