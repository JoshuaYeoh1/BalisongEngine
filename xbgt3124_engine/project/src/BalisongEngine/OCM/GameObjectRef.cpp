#include "GameObjectRef.h"
#include "GameObject.h"
using namespace BalisongEngine;
using namespace BalisongEngineOCM;

#include <iostream>
using namespace std;

// ===============================================================================

GameObjectRef::GameObjectRef(GameObject* who)
{
	Set(who);
}

GameObjectRef::~GameObjectRef()
{
	Set(nullptr);
}

// ===============================================================================

void GameObjectRef::Set(GameObject* to)
{
	TryUnsubDestroyEvent();

	ref = to;

	TrySubDestroyEvent();
}

GameObject* GameObjectRef::Get() const
{
	return ref;
}

// ===============================================================================

void GameObjectRef::TrySubDestroyEvent()
{
	if (!ref) return;

	destroyEventId = ref->DestroyEvent.Subscribe(this, &GameObjectRef::OnRefDestroyed);
}

void GameObjectRef::TryUnsubDestroyEvent()
{
	if (!ref) return;
	if (destroyEventId == -1) return;

	ref->DestroyEvent.Unsubscribe(destroyEventId);

	destroyEventId = -1;
}

// ===============================================================================

void GameObjectRef::OnRefDestroyed(GameObject* who)
{
	ref = nullptr;
	destroyEventId = -1;
	// dont unsub, because target doesnt exist anymore, read access violation
}