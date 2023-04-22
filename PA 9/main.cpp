
#include "raylib.h"
#include "consts.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "LinearBall.hpp"
#include "Map.hpp"
#include "Interface.hpp"
#include <vector>

int main(void)
{
    // Initial window size
    InitWindow(screenWidth, screenHeight, "Worlds Hardest Game - PA9 WSU");

    // Set our game to run at 60 frames-per-second
    SetTargetFPS(60);

    // Create a player entity to be the main controllable actor of the game.
    // The player is dependency injected into the PlayerCollideable interface
    Player p;
    PlayerCollidable::setPlayer(&p);

    // List of all drawable and updateable entities 
    std::vector<FrameListenable*> frameListenables = {
        new Map(),
        &p,
        new LinearBall({ screenWidth / 2, screenHeight / 2}, {0,-5}),
        new LinearBall({ screenWidth / 3, screenHeight / 2}, {0,5}),
        new LinearBall({ screenWidth / 4, screenHeight / 2}, {0,-5}),
        new Interface(),
    };

    while (!WindowShouldClose())   
    {

        // Update all entities each frame
        for (const auto& i : frameListenables) {
            i->update();
        }

        BeginDrawing();
        
        // Draw all entities each frame
        for (const auto& i : frameListenables) {
            i->draw();
        }

        ClearBackground(RAYWHITE);

        EndDrawing();
    }

    CloseWindow();        

    return 0;
}