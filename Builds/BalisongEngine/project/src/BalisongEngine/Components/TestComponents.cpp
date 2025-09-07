#include "TestComponents.h"
#include "GameObject.h"
#include "TransformComponent.h"
using namespace BalisongEngine;
using namespace BalisongEngineOCM;
using namespace BalisongEngineComponents;

#include <glm/glm.hpp>
using namespace glm;

#include <glad/glad.h>

#include <iostream>
using namespace std;

// ===============================================================================

FooComponent::FooComponent(GameObject* go, const string& comp_name) : BaseComponent(go, comp_name) {}
FooComponent::~FooComponent() {}

void FooComponent::Update(float dt)
{
	lifeTime += dt;

	if (!invoked && lifeTime >= 6.0f)
	{
		cout << bothNames << " I am still here by the way!" << endl;
		cout << bothNames << " adding component to self" << endl;

		auto qrc = gameObject->AddComponent<QuadRenderComponent>();
		qrc->SetColor(0.0f, 1.0f, 0.0f);

		invoked = true;
	}
}

// ===============================================================================

RotateComponent::RotateComponent(GameObject* go, const string& comp_name) : BaseComponent(go, comp_name) {}
RotateComponent::~RotateComponent() {}

void RotateComponent::Update(float dt)
{
	lifeTime += dt;

	transform->SetLocalRotation(lifeTime * 20.0f);

	if (lifeTime >= 2.0f)
	{
		cout << bothNames << " 2 seconds has passed since creation, change color and destroy self" << endl;

		auto qrc = gameObject->GetComponent <QuadRenderComponent>();
		qrc->SetColor(1.0f, 0.0f, 0.0f);

		DestroyComponent();
	}
}

// ===============================================================================

QuadRenderComponent::QuadRenderComponent(GameObject* go, const string& comp_name) : BaseComponent(go, comp_name) {}
QuadRenderComponent::~QuadRenderComponent() {}

void QuadRenderComponent::Awake()
{
	r = 0.0f; g = b = 1.0f;
}

void QuadRenderComponent::Render()
{
	auto pos = transform->GetLocalPosition();
	auto rot = transform->GetLocalRotation();

	glPushMatrix();
	glTranslatef(pos.x, pos.y, 0);
	glRotatef(rot, 0.0f, 0.0f, 1.0f);

	glColor3f(r, g, b);
	glBegin(GL_QUADS);
	glVertex3f(-0.5, 0.5, 0);
	glVertex3f(-0.5, -0.5, 0);
	glVertex3f(0.5, -0.5, 0);
	glVertex3f(0.5, 0.5, 0);
	glEnd();

	glPopMatrix();
}

void QuadRenderComponent::SetColor(float nr, float ng, float nb)
{
	r = nr; g = ng; b = nb;
	cout << bothNames << " change color to (" << r << ", "<< g << ", " << b << ")\n";
}

// ===============================================================================

DelayedDestroyComponent::DelayedDestroyComponent(GameObject* go, const string& comp_name) : BaseComponent(go, comp_name) {}
DelayedDestroyComponent::~DelayedDestroyComponent() {}

void DelayedDestroyComponent::Update(float dt)
{
	if (!started) return;

	secondsLeft -= dt;

	if (secondsLeft <= 0)
	{
		secondsLeft = 0;
		gameObject->Destroy();
	}
}

void DelayedDestroyComponent::StartDestroyDelay(float seconds)
{
	secondsLeft = seconds;
	started = true;
}
