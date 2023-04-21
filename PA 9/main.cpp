
#include "raylib.h"

int main(void)
{
    
    const int screenWidth = 1600;
    const int screenHeight = 900;

    Vector2 ballPosition = { (float)screenWidth / 5, (float)screenHeight / 5 };

    InitWindow(screenWidth, screenHeight, "World's Hardest Game");

    SetTargetFPS(60);            
    

    // Main game loop
    while (!WindowShouldClose())   
    {

        if (IsKeyDown(KEY_D)) ballPosition.x += 4.0f;
        if (IsKeyDown(KEY_A)) ballPosition.x -= 4.0f;
        if (IsKeyDown(KEY_W)) ballPosition.y -= 4.0f;
        if (IsKeyDown(KEY_S)) ballPosition.y += 4.0f;

    
        BeginDrawing();

        ClearBackground(RAYWHITE);

        EndDrawing();
    }

    CloseWindow();        

    return 0;
}