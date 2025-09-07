#include "TestScene.h"
#include "GameObject.h"
#include "PrefabManager.h"
#include "TransformComponent.h"
#include "Renderer.h"
#include "Camera.h"
#include "SceneStateMachine.h"
using namespace BalisongEngine;
using namespace BalisongEngineOCM;
using namespace BalisongEngineComponents;
using namespace BalisongEngineRenderer;
using namespace BalisongEngineScenes;

#include <glad/glad.h>

#include <glm/glm.hpp>
using namespace glm;

#include <iostream>
using namespace std;

// ===============================================================================

void TestScene::OnInitialize()
{
	Renderer::SetClearColor(0, 0, .25, 1);

	time = 0;
}

void TestScene::OnUpdate(float deltaTime)
{
	time += deltaTime;

	//if (time > 2.0f)
}

void TestScene::OnRender()
{
	glPushMatrix();

	glTranslatef(0, 0, 0);

	glBegin(GL_TRIANGLES);
		glColor3f(1, 0, 0);
		glVertex3f(0, 0.5, 0);
		glColor3f(0, 1, 0);
		glVertex3f(-0.5, -0.5, 0);
		glColor3f(0, 0, 1);
		glVertex3f(0.5, -0.5, 0);
	glEnd();

	glPopMatrix();
}
