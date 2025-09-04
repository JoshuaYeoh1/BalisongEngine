#include "BaseComponent.h"
#include "GameObject.h"
using namespace BalisongEngine;
using namespace BalisongEngineOCM;
using namespace BalisongEngineComponents;

#include <iostream>
using namespace std;

// ===============================================================================

BaseComponent::BaseComponent(GameObject* go, const string& comp_name) : componentName(comp_name)
{
	gameObject = go;
	if (!gameObject) return;

	name = gameObject->name;
	bothNames = name + ": " + comp_name;

	transform = go->GetTransform();

	cout << bothNames << " Created\n";
}
// Required for subclasses to work properly.
BaseComponent::~BaseComponent()
{
	if (!gameObject) return;

	cout << bothNames << " Destroyed\n";
} 

// ===============================================================================

GameObject* BaseComponent::GetGameObject()
{
	return gameObject;
}
TransformComponent* BaseComponent::GetTransform()
{
	return transform;
}

// ===============================================================================

void BaseComponent::Awake() {}
void BaseComponent::Start() {}
void BaseComponent::Update(float dt) {}
void BaseComponent::Render() {}

// ===============================================================================

void BaseComponent::OnCollisionFirstEnter(GameObject* other) {}
void BaseComponent::OnCollisionEnter(GameObject* other) {}
void BaseComponent::OnCollisionStay(vector<GameObject*> others) {}
void BaseComponent::OnCollisionExit(GameObject* other) {}
void BaseComponent::OnCollisionLastExit(GameObject* other) {}

// ===============================================================================

void BaseComponent::DestroyComponent()
{
	flaggedForDeletion = true;

	DestroyComponentEvent.Invoke(this);
	DestroyComponentEvent.UnsubscribeAll();

	OnDestroyComponent();
}

bool BaseComponent::ShouldDestroy() const
{
	return flaggedForDeletion;
}

void BaseComponent::OnDestroyComponent() {}

void BaseComponent::OnDestroy() {}
