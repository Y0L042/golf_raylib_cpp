#include <raylib.h>
#include "game.hpp"
#include "gameobject.hpp"

// Forward declarations
void Ready_GameObjects();
void ReadySpawnedGameObjects();
void Update_GameObjects(double delta);
void Draw_GameObjects(double delta);
void EndOfFrame_GameObjects();

void Ready();
void Update(double delta);
void Draw(double delta);



int main()
{
    int windowWidth = 750;
    int windowHeight = 700;
    int targetFPS = 144;

    Color grey = {29, 29, 27, 255};


    InitWindow(windowWidth, windowHeight, "Space Invaders");
    SetTargetFPS(targetFPS);

    Ready();
    Ready_GameObjects();

    while(!WindowShouldClose())
    {
        double delta = GetFrameTime();

        BeginDrawing();
        ClearBackground(grey);

        ReadySpawnedGameObjects();

        Update(delta);
        Update_GameObjects(delta);

        Draw(delta);
        Draw_GameObjects(delta);

        EndOfFrame_GameObjects();

        EndDrawing();
        //rlImGuiEnd();
    }

    CloseWindow();
}

void Ready_GameObjects()
{
    Game::Ready();
}

void ReadySpawnedGameObjects()
{
    Game::ProcessReadyQueue();
}

void Update_GameObjects(double delta)
{
    Game::Update(delta);
}

void Draw_GameObjects(double delta)
{
    Game::Draw(delta);
}

void EndOfFrame_GameObjects()
{
    Game::ProcessDestructionQueue();
    Game::ProcessAdditionsQueue();
}


void Ready()
{

}

void Update(double delta)
{

}


void Draw(double delta)
{
}
