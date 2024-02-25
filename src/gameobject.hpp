#pragma once
#include <raylib.h>
#include <memory>
#include "game.hpp"

class GameObject
{
public:
    GameObject();
    virtual ~GameObject();
    virtual void Ready();
    virtual void Draw(double delta);
    virtual void Update(double delta);
    virtual void HandleInput();
    virtual void Destroy();
    virtual void QueueDestroy();

    template<typename T, typename... Args>
    static std::weak_ptr<T> Instantiate(Args&&... args) {
        static_assert(std::is_base_of<GameObject, T>::value, "T must be a GameObject derived class");
        auto instance = std::make_shared<T>(std::forward<Args>(args)...);
        // Assuming Game::Instantiate takes a shared_ptr<GameObject>
        Game::Instantiate(std::static_pointer_cast<GameObject>(instance));
        //instance->Ready();
        return instance;
    }

private:

};
