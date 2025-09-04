# Manual

This is the user manual for custom components, game objects/prefabs, and scenes.

### How to create custom components

First, create a new header file for your component and name it. e.g., MyCustomComponent.h

It must inherit from BaseComponent.

Include necessary files like BaseComponent.h, and any other dependencies like string, Random.h, or glm/glm.hpp

Here is where you can add member variables and functions that your component, or other components, will use.

Forward declare other components that your custom component might need. These will be fully included in the .cpp file, not the header file, if you want to keep your header files lightweight.

GameObject and TransformComponent are already forward declared in BaseComponent, so no need to do it again.

Make sure they are in the proper namespaces

```cpp
#pragma once
#include "BaseComponent.h"
//optional includes
#include "GameObjectRef.h"
#include <glm/glm.hpp>

// Must be in the correct nested namespaces
namespace BalisongEngine {
namespace BalisongEngineComponents {

    // this is from another custom component
    class MoveComponent; // forward declare

    // your custom component
    class MyCustomComponent : public BaseComponent
    {
    public:

        MyCustomComponent(BalisongEngineOCM::GameObject* go, const std::string& comp_name = "[MyCustomComponent]");
        ~MyCustomComponent();

        // Override from base component
        void Awake() override;
        void Start() override;
        void Update(float deltaTime) override;
        void Render() override;
        void OnDestroy() override;

        void OnCollisionFirstEnter(BalisongEngineOCM::GameObject* other) override;
		void OnCollisionEnter(BalisongEngineOCM::GameObject* other) override;
		void OnCollisionStay(std::set<BalisongEngineOCM::GameObject*> others) override;
		void OnCollisionExit(BalisongEngineOCM::GameObject* other) override;
		void OnCollisionLastExit(BalisongEngineOCM::GameObject* other) override;

    private:
        
        GameObjectRef targetRef;
        MoveComponent* vehicle = nullptr; // this is from another custom component

    };

}
}
```

After that, now you can implement the functionality of your component in the corresponding .cpp file.

Include the header file you just created.

The other most common headers to use are GameObject and TransformComponent, with the namespaces BalisongEngineOCM and BalisongEngineComponents.

Implement the constructor and destructor. The constructor is used to initialize the component, and the destructor is used to clean up.

Override the BaseComponent methods, like Awake, Start, or Update to define the behavior that happens every frame.


```cpp
#include "MyCustomComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "MoveComponent.h"
using namespace BalisongEngine;
using namespace BalisongEngineOCM;
using namespace BalisongEngineComponents;

#include <glm/glm.hpp>
using namespace glm;

#include <iostream>
using namespace std;

MyCustomComponent::MyCustomComponent(GameObject* go, const std::string& comp_name) : BaseComponent(go, comp_name) {}
MyCustomComponent::~MyCustomComponent() {}

void MyCustomComponent::Update(float dt)
{
    cout << "Hello world!\n";

    auto target = targetRef.Get();
    if (!target) return;
    if (!vehicle) return;

    vec3 target_position = target->GetWorldPosition();
    vec3 direction = glm::normalize(target_position - vehicle->GetPosition());
    
    vehicle->SetDirection(direction); // this is from another custom component

    // other stuff here...
}
```

So after creating your custom component, you will now need a game object or prefab to put it in.

### How to create custom GameObjects or Prefabs

First, create and declare a new class that inherits from Prefab class. It should override its CreateInstance method.

```cpp
class MyCustomPrefab : public Prefab
{
public:
	GameObject* CreateInstance() override;
};
```

After that, create the definition of your prefab's CreateInstance method.

Here is where you can create a new GameObject and attach your custom components that you created previously.

At the end of the method, make sure to return the created game object

```cpp
GameObject* MyCustomPrefab::CreateInstance()
{
	auto go = new GameObject("[GO] My Game Object");
	go->GetTransform()->TranslateLocal(0, .25f);

    auto my_comp = go->AddComponent<MyCustomComponent>();
	my_comp->anyPublicVariable = 123;
	my_comp->AnyPublicMethod();

	auto sprite = go->AddComponent<SpriteRendererComponent>();
	sprite->SetTexture("../assets/your/custom/image.png");
	sprite->SetPixelsPerUnit(300);

	return go;
}
```

Lastly, you must add your prefab into the PrefabManager when Application starts.

You will need to give it a string name that you can remember.

You can do it before the Scenes and after Camera sections.


```cpp
void Application::Run()
{
	// Input ===============================================================================

	// Renderer ===============================================================================
	
	// Camera ===============================================================================

	// Prefabs ===============================================================================
	
	PrefabManager::AddPrefab("MyCustomPrefab", new MyCustomPrefab());

    // Scenes ===============================================================================
}
```

Now your prefab is ready, but first you will need to create your custom scene to spawn it in

### How to create custom scenes

First, create and declare a new class that inherits from BaseScene class. You will need to give it a string name that you can remember, and override its OnInitialize method. Then, you can optionally override its Awake, Start, Update, or Render methods.

```cpp
#pragma once
#include "BaseScene.h"

namespace BalisongEngine{
namespace BalisongEngineScenes
{
	class MyCustomScene : public BaseScene
	{
	public:

		std::string GetName() const override { return "MyCustomScene"; }

	protected:

		void OnInitialize() override;
		void OnUpdate(float deltaTime) override;

		float time = 0;
	};

}
}
```

Next, create the definition for your custom scene.

Here is where you can set the background color, camera, and instantiate your custom GameObject prefabs. You must use the exact string name that you set for your prefab, case sensitive.

You don't have to create prefabs for all GameObjects, sometimes you can just create them here on scene initialization, if you are sure that you will just spawn them once and won't spawn them again later.

```cpp
void MyCustomScene::OnInitialize()
{
	time = 0;
	Renderer::SetClearColor(.1f, .1f, .1f, 1); // bg color
	Camera::SetPosition(0, 0, 0);

    // ===============================================================================

	auto my_object = PrefabManager::Instantiate("MyCustomPrefab");
	auto my_object_tr = my_object->GetTransform();
	my_object_tr->SetLocalPosition(0, -.5f);

	auto another = new GameObject("[GO] Another One");
	another->GetTransform()->SetParent(my_object_tr);

	auto sprite = another->AddComponent<SpriteRendererComponent>();
	sprite->SetTexture("../assets/another/one.png");
	sprite->SetPixelsPerUnit(375);

	// ===============================================================================

	auto logo = new GameObject("[GO] Balisong Logo");
	logo->GetTransform()->SetLocalPosition(0, .15f);

	auto logo_sprite = logo->AddComponent<SpriteRendererComponent>();
	logo_sprite->SetTexture("../assets/splash/balisong_logo.png");
	logo_sprite->SetPixelsPerUnit(300);
}

void MyCustomScene::OnUpdate(float dt)
{
	time += dt;

	if (time >= 3 || Input::GetKeyDown(KeyCode::SPACE))
	{
		SceneStateMachine::LoadScene("AnotherScene");
	}
}
```

Lastly, you must add your scene into the SceneStateMachine when Application starts.

You can then load it with the string name you gave for your custom scene. You must use the exact string name, case sensitive.

You can also load it using the index depending on the order you added the scenes in.

You can do it after the Prefabs section.


```cpp
void Application::Run()
{
	// Other stuff ===============================================================================
	
	// Camera ===============================================================================

	// Prefabs ===============================================================================
	
	PrefabManager::AddPrefab("MyCustomPrefab", new MyCustomPrefab());

    // Scenes ===============================================================================

    SceneStateMachine::AddScene<MyCustomScene>();
    SceneStateMachine::LoadScene("MyCustomScene");

    // Other stuff  ===============================================================================
}
```

Now your scene is ready, and will load after you compile and start the game.