#include <iostream>
#include "raylib.h"

int main()
{
    int windowWidth = 750;
    int windowHeight = 700;
    int targetFPS = 144;

    Color grey = {29, 29, 27, 255};

    InitWindow(windowWidth, windowHeight, "Raylib Game");
    SetTargetFPS(targetFPS);

    while(!WindowShouldClose())
    {
        double delta = GetFrameTime();

        BeginDrawing();
        ClearBackground(grey);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
