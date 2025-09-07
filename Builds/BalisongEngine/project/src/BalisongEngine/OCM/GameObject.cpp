#include "GameObject.h"
#include "TransformComponent.h"
using namespace BalisongEngine;
using namespace BalisongEngineOCM;
using namespace BalisongEngineComponents;

#include "GameObjectCollection.h"

#include "PoolAllocator.h"
using namespace BalisongEngineAllocator;

#include <iostream>
using namespace std;

// ===============================================================================

GameObject::GameObject(const string& custom_name) : name(custom_name)
{
	cout << endl << custom_name << ": Created" << endl;

	GameObjectCollection::Add(this);

	transform = AddComponent<TransformComponent>();
}

GameObject::GameObject() : GameObject(name) {} // just for default name

GameObject::~GameObject()
{
	cout << name << ": Destroyed\n\n";

	transform = nullptr;
}

// ===============================================================================

TransformComponent* GameObject::GetTransform()
{
	return transform;
}

// ===============================================================================

void GameObject::RunComponentAwake()
{
	for (auto* comp : componentsJustAdded)
	{
		if (!comp) continue;
		comp->Awake();
	}
}

void GameObject::RunComponentStart()
{
	for (auto* comp : componentsJustAdded)
	{
		if (!comp) continue;
		comp->Start();
	}
	// clear componentsJustAdded
	// so that Start and Awake do not happen again in the loop
	componentsJustAdded.clear();
}

void GameObject::RunComponentUpdate(float dt)
{
	if (destroyDelayStarted)
	{
		destroyDelayTimer -= dt;

		if (destroyDelayTimer <= 0)
		{
			Destroy();
		}
	}

	DeleteFlaggedComponents();

	for (auto* comp : components)
	{
		if (!comp) continue;
		comp->Update(dt);
	}
}

void GameObject::RunComponentRender()
{
	for (auto* comp : components)
	{
		if (!comp) continue;
		comp->Render();
	}
}

// ===============================================================================

void GameObject::OnCollisionFirstEnter(GameObject* other)
{
	for (auto* comp : components)
	{
		if (!comp) continue;
		comp->OnCollisionFirstEnter(other);
	}
}
void GameObject::OnCollisionEnter(GameObject* other)
{
	for (auto* comp : components)
	{
		if (!comp) continue;
		comp->OnCollisionEnter(other);
	}
}
void GameObject::OnCollisionStay(vector<GameObject*> others)
{
	for (auto* comp : components)
	{
		if (!comp) continue;
		comp->OnCollisionStay(others);
	}
}
void GameObject::OnCollisionExit(GameObject* other)
{
	for (auto* comp : components)
	{
		if (!comp) continue;
		comp->OnCollisionExit(other);
	}
}
void GameObject::OnCollisionLastExit(GameObject* other)
{
	for (auto* comp : components)
	{
		if (!comp) continue;
		comp->OnCollisionLastExit(other);
	}
}

// ===============================================================================

void GameObject::FlagComponentsForDestroy()
{
	for (auto* comp : components)
	{
		if (!comp) continue;
		comp->DestroyComponent();
	}
}

void GameObject::DeleteFlaggedComponents()
{
	// iterator-based for loop
	for (auto it = components.begin(); it != components.end();)
	{
		BaseComponent* comp = *it;

		if (comp->ShouldDestroy())
		{
			delete comp; // or delete *it
			// remove component from components
			// get next element automatically
			it = components.erase(it);
		}
		else it++;
	}
}

// ===============================================================================

void GameObject::Destroy(float delay)
{
	// first time called
	if (!destroyDelayStarted)
	{
		destroyDelayStarted = true;
		destroyDelayTimer = delay;
		return;
	}

	// option for shortening the timer
	if (delay < destroyDelayTimer)
	destroyDelayTimer = delay;

	// ignore if timer is not done yet
	if (destroyDelayTimer > 0) return;

	if (flaggedForDeletion) return;

	OnDestroy();

	DestroyEvent.Invoke(this);
	DestroyEvent.UnsubscribeAll();

	FlagComponentsForDestroy();

	flaggedForDeletion = true;
}

bool GameObject::ShouldDestroy() const
{
	return flaggedForDeletion;
}

void GameObject::OnDestroy()
{
	for (auto* comp : components)
	{
		if (!comp) continue;
		comp->OnDestroy();
	}
}

// ===============================================================================

static PoolAllocator alloc{ 1024 };

// override 'new' to use the allocator
void* GameObject::operator new(size_t size)
{
	return alloc.Allocate(size);
}

// override 'delete' to use the allocator
void GameObject::operator delete(void* ptr, size_t size)
{
	alloc.Deallocate(ptr, size);
}