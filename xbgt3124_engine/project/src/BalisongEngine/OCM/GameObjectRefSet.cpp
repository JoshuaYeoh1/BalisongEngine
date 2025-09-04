#include "GameObjectRefSet.h"
#include "GameObject.h"
using namespace BalisongEngine;
using namespace BalisongEngineOCM;

#include <vector>
#include <iostream>
using namespace std;

// ===============================================================================

GameObjectRefSet::GameObjectRefSet() {}

GameObjectRefSet::~GameObjectRefSet()
{
	RemoveAll();
}

// ===============================================================================

void GameObjectRefSet::Add(GameObject* who)
{
	if (!who) return;
	if (Contains(who)) return;

	refs.push_back(who);

	TrySubDestroyEvent(who);
}

// ===============================================================================

void GameObjectRefSet::Remove(GameObject* who, bool unsub)
{
	if (!Contains(who)) return;

	refs.erase(remove(refs.begin(), refs.end(), who), refs.end());

	TryUnsubDestroyEvent(who, unsub);
}

void GameObjectRefSet::RemoveAll()
{
	for (auto* ref : refs)
	{
		Remove(ref);
	}
	refs.clear();
}

void GameObjectRefSet::RemoveNulls()
{
	refs.erase(remove(refs.begin(), refs.end(), nullptr), refs.end());
}

// ===============================================================================

void GameObjectRefSet::TrySubDestroyEvent(GameObject* who)
{
	if (!who) return;

	bool id_found = destroyEventIdsDict.find(who) != destroyEventIdsDict.end();
	if (id_found) return;

	int id = who->DestroyEvent.Subscribe(this, &GameObjectRefSet::OnRefDestroyed);
	destroyEventIdsDict[who] = id;
}

void GameObjectRefSet::TryUnsubDestroyEvent(GameObject* who, bool unsub)
{
	if (!who) return;

	auto it = destroyEventIdsDict.find(who);

	bool id_found = it != destroyEventIdsDict.end();
	if (!id_found) return;

	int id = it->second;

	if(unsub)
	who->DestroyEvent.Unsubscribe(id);

	destroyEventIdsDict.erase(it);
}

// ===============================================================================

void GameObjectRefSet::OnRefDestroyed(GameObject* who)
{
	Remove(who, false); // dont unsub, because target doesnt exist anymore, read access violation
}

// ===============================================================================

bool GameObjectRefSet::Contains(GameObject* who)
{
	RemoveNulls();
	return find(refs.begin(), refs.end(), who) != refs.end();
}

int GameObjectRefSet::Count()
{
	RemoveNulls();
	return (int) refs.size();
}

bool GameObjectRefSet::IsEmpty()
{
	return Count() <= 0;
}

// ===============================================================================

GameObject* GameObjectRefSet::Get(int i)
{
	if (IsEmpty()) return nullptr;
	if (i >= Count()) return nullptr;

	return refs[i];
}

vector<GameObject*> GameObjectRefSet::GetAll()
{
	return refs;
}
