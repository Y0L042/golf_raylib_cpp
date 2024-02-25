#pragma once
#include <memory>
#include <vector>
#include "gameobject.hpp"

class Game 
{
public:
    static std::weak_ptr<Game> GetInstance();
    static void DestroyInstance();
    static std::shared_ptr<GameObject> Instantiate(std::shared_ptr<GameObject> gameObject);
    static void Ready();
    static void Draw(double delta);
    static void Update(double delta);
    static void HandleInput();
    static void Destroy(GameObject* gameObjectPtr);
    static void QueueDestroy(GameObject* gameObjectPtr);
    static void ProcessDestructionQueue();
    static void ProcessReadyQueue();
    static void ProcessAdditionsQueue();
    static void ProcessRemovalsQueue();
    Game();
    ~Game();
    static std::shared_ptr<Game> gameInstance;


private:

    std::vector<std::shared_ptr<GameObject>> gameObjects;
    std::vector<std::shared_ptr<GameObject>> destructionQueue;

    std::vector<std::shared_ptr<GameObject>> addQueue;
    std::vector<std::shared_ptr<GameObject>> readyQueue;
    std::vector<std::shared_ptr<GameObject>> removeQueue;


    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
};