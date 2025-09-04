#pragma once

namespace BalisongEngine{
namespace BalisongEngineOCM
{
	class GameObject; // forward declare

	// ===============================================================================

	/// <summary>
	/// This is the base class for custom prefabs
	/// </summary>
	class Prefab
	{
	public:

		/// <summary>
		/// Creates a GameObject that has been setup like a preset
		/// </summary>
		/// <returns></returns>
		virtual GameObject* CreateInstance() = 0;
		virtual ~Prefab() = default;

	};
}}