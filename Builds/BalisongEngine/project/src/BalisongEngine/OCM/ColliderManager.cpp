#include "ColliderManager.h"
#include "GameObject.h"
#include "TransformComponent.h"
using namespace BalisongEngine;
using namespace BalisongEngineComponents;
using namespace BalisongEngineOCM;

#include "ColliderComponent.h"

using namespace std;

// ===============================================================================

set<ColliderComponent*> ColliderManager::colliders;

// ===============================================================================

void ColliderManager::Add(ColliderComponent* collider)
{
	colliders.insert(collider);

	collider->DestroyComponentEvent.Subscribe(&ColliderManager::OnComponentDestroyed);
}

void ColliderManager::Remove(ColliderComponent* collider)
{
	colliders.erase(collider);
}

void ColliderManager::OnComponentDestroyed(BaseComponent* comp)
{
	if (auto* collider = dynamic_cast<ColliderComponent*>(comp))
	{
		Remove(collider);
	}
}

// ===============================================================================

void ColliderManager::Update(float dt)
{
	// compare them
	for (auto it1 = colliders.begin(); it1 != colliders.end(); it1++)
	{
		auto it2 = it1;
		it2++;

		for (; it2 != colliders.end(); it2++)
		{
			ColliderComponent* a = *it1;
			ColliderComponent* b = *it2;
			if (!a || !b) continue;

			if (a->IsCollidingWith(b))
			{
				auto a_go = a->GetGameObject();
				auto b_go = b->GetGameObject();

				a->OnCollideWith(b_go);
				b->OnCollideWith(a_go);
			}
		}
	}

	// update them
	for (auto* collider : colliders)
	{
		if (!collider) continue;
		collider->UpdateCollisions();
	}
}

// ===============================================================================

set<ColliderComponent*>& ColliderManager::GetAllColliders()
{
	return colliders;
}

// ===============================================================================

void ColliderManager::Dispose()
{
	colliders.clear();
}

