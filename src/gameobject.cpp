#include "game.hpp"
#include "gameobject.hpp"

std::weak_ptr<GameObject> _instance;

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}


void GameObject::Ready()
{
}

void GameObject::Draw(double delta)
{
}

void GameObject::Update(double delta)
{
}

void GameObject::HandleInput()
{
}

void GameObject::Destroy()
{
	Game::Destroy(this);
}

void GameObject::QueueDestroy()
{
	Game::QueueDestroy(this);
}
