#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include "game.hpp"
#include "gameobject.hpp"

std::shared_ptr<Game> Game::gameInstance = nullptr;

Game::Game()
{
}

Game::~Game()
{
    DestroyInstance();
}


void Game::Ready()
{
    ProcessReadyQueue();
}

void Game::Draw(double delta)
{
    auto gamePtr = GetInstance().lock();
    for (auto& obj : gamePtr->gameObjects)
    {
        if (obj) obj->Draw(delta);
    }
}

void Game::Update(double delta)
{
    auto gamePtr = GetInstance().lock();
    for (auto& obj : gamePtr->gameObjects)
    {
        if (obj) obj->Update(delta);
    }
}

void Game::HandleInput()
{
    auto gamePtr = GetInstance().lock();
    for (auto& obj : gamePtr->gameObjects)
    {
        if (obj) obj->HandleInput();
    }
}

std::shared_ptr<GameObject> Game::Instantiate(std::shared_ptr<GameObject> gameObjectPtr)
{
    auto gamePtr = GetInstance().lock();
    gamePtr->addQueue.push_back(gameObjectPtr);
    return gameObjectPtr;
}

void Game::Destroy(GameObject* gameObjectPtr)
{
    auto& vec = GetInstance().lock()->gameObjects;
    vec.erase(
        std::remove_if(vec.begin(), vec.end(),
            [gameObjectPtr](const std::shared_ptr<GameObject>& ptr) {
                return ptr.get() == gameObjectPtr;
            }),
        vec.end());
}

void Game::QueueDestroy(GameObject* gameObjectPtr)
{
    auto gamePtr = GetInstance().lock();
    // Find the shared_ptr in gameObjects that matches gameObjectPtr and add it to destructionQueue
    for (auto& obj : gamePtr->gameObjects) {
        if (obj.get() == gameObjectPtr) {
            gamePtr->destructionQueue.push_back(obj); // obj is the shared_ptr that needs to be queued for destruction
            break; // Assuming unique objects, break once found
        }
    }
}

void Game::ProcessDestructionQueue()
{
    auto gamePtr = GetInstance().lock();
    // Process all objects in the destruction queue
    for (auto& toDestroy : gamePtr->destructionQueue) {
        // Find and remove the object in the gameObjects vector
        auto& objects = gamePtr->gameObjects; // Reference for easier access
        objects.erase(std::remove_if(objects.begin(), objects.end(),
            [&toDestroy](const std::shared_ptr<GameObject>& obj) {
                return obj == toDestroy; // Compare shared_ptrs directly
            }), objects.end());
    }
    gamePtr->destructionQueue.clear();
}

/// <summary>
/// Ummm, the AdditionsQueue does not actually do anything. Why don't I just call ready on it?
/// </summary>
void Game::ProcessAdditionsQueue()
{
    auto gamePtr = GetInstance().lock();
    for (auto& obj : gamePtr->addQueue) {
        gamePtr->readyQueue.push_back(obj);
    }
    gamePtr->addQueue.clear();
}

void Game::ProcessReadyQueue()
{
    auto gamePtr = GetInstance().lock();
    for (auto& obj : gamePtr->readyQueue) {
        obj->Ready();
        gamePtr->gameObjects.push_back(obj);
    }
    gamePtr->readyQueue.clear();
}

void Game::ProcessRemovalsQueue()
{
    auto gamePtr = GetInstance().lock();
    for (auto& objToRemove : gamePtr->removeQueue) {
        gamePtr->gameObjects.erase(
            std::remove_if(gamePtr->gameObjects.begin(), gamePtr->gameObjects.end(),
                [&objToRemove](const std::shared_ptr<GameObject>& obj) {
                    return obj == objToRemove;
                }),
            gamePtr->gameObjects.end());
    }
    gamePtr->removeQueue.clear();
}


std::weak_ptr<Game> Game::GetInstance()
{
    if (!gameInstance)
    {
        gameInstance = std::make_shared<Game>();
    }
    return gameInstance;
}

void Game::DestroyInstance()
{
    if (gameInstance)
    {
        gameInstance.reset();
    }
}
