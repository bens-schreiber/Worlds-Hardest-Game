
#include "raylib.h"
#include "const.h"
#include "Entity.hpp"
#include "Player.hpp"
#include "EnemyBall.hpp"
#include <vector>

int main(void)
{


    // Initial window size
    InitWindow(screenWidth, screenHeight, "Worlds Hardest Game - PA9 WSU");

    // Set our game to run at 60 frames-per-second
    SetTargetFPS(60);

    // Create a player entity to be the main controllable actor of the game
    Player* p = new Player();

    // List of all drawable and updateable entities 
    std::vector<Entity*> entities = {
        p, 
        new EnemyBall(p, { screenWidth / 2, screenHeight / 2}, {5,5})
    };

    while (!WindowShouldClose())   
    {

        // Update all entities each frame
        for (const auto& e : entities) {
            e->update();
        }

        BeginDrawing();
        
        // Draw all entities each frame
        for (const auto& e : entities) {
            e->draw();
        }

        ClearBackground(RAYWHITE);

        EndDrawing();
    }

    CloseWindow();        

    return 0;
}