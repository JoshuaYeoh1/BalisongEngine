#pragma once
#include "BaseComponent.h"

// ====================================================================

namespace BalisongEngine{
namespace BalisongEngineComponents
{
	/// <summary>
	/// A test component
	/// </summary>
	class FooComponent : public BaseComponent
	{
	public:

		/// <summary>
		/// ctor
		/// </summary>
		/// <param name="go"></param>
		/// <param name="comp_name"></param>
		FooComponent(BalisongEngineOCM::GameObject* go, const std::string& comp_name = "[FooComponent]");
		~FooComponent();

		void Update(float dt) override;

	private:

		float lifeTime = 0.0f;
		bool invoked = false;
	};

	// ===============================================================================

	/// <summary>
	/// A test component to rotate the GameObject transform
	/// </summary>
	class RotateComponent : public BaseComponent
	{
	public:

		/// <summary>
		/// ctor
		/// </summary>
		/// <param name="go"></param>
		/// <param name="comp_name"></param>
		RotateComponent(BalisongEngineOCM::GameObject* go, const std::string& comp_name = "[RotateComponent]");
		~RotateComponent();

		void Update(float dt) override;

	private:

		float lifeTime = 0.0f;
	};

	// ===============================================================================

	/// <summary>
	/// A test component to spawn a quad mesh with a color
	/// </summary>
	class QuadRenderComponent : public BaseComponent
	{
	public:

		/// <summary>
		/// ctor
		/// </summary>
		/// <param name="go"></param>
		/// <param name="comp_name"></param>
		QuadRenderComponent(BalisongEngineOCM::GameObject* go, const std::string& comp_name = "[QuadRenderComponent]");
		~QuadRenderComponent();

		void Awake() override;
		void Render() override;

		/// <summary>
		/// Set the color of the quad mesh
		/// </summary>
		/// <param name="r"></param>
		/// <param name="g"></param>
		/// <param name="b"></param>
		void SetColor(float r, float g, float b);

	private:

		float r=1, g=1, b=1;
	};

	// ===============================================================================

	/// <summary>
	/// A test component to destroy the GameObject after a time
	/// </summary>
	class DelayedDestroyComponent : public BaseComponent
	{
	public:

		/// <summary>
		/// ctor
		/// </summary>
		/// <param name="go"></param>
		/// <param name="comp_name"></param>
		DelayedDestroyComponent(BalisongEngineOCM::GameObject* go, const std::string& comp_name = "[DelayedDestroyComponent]");
		~DelayedDestroyComponent();

		void Update(float dt) override;

		/// <summary>
		/// Begin the countdown in seconds before destroying the GameObject
		/// </summary>
		/// <param name="seconds"></param>
		void StartDestroyDelay(float seconds);

	private:

		bool started = false;
		float secondsLeft = 0;
	};

}
}
