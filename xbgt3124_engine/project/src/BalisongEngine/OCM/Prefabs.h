#pragma once
#include "Prefab.h"
#include <string>

// ===============================================================================

namespace BalisongEngine{
namespace BalisongEngineOCM
{
	class TitlePrefab : public Prefab
	{
	public:
		GameObject* CreateInstance() override;
	};
	
	// ===============================================================================

	class PlayButtonPrefab : public Prefab
	{
	public:
		GameObject* CreateInstance() override;
	};
	
	// ===============================================================================

	class RetryButtonPrefab : public Prefab
	{
	public:
		GameObject* CreateInstance() override;
	};
	
	// ===============================================================================

	class MenuButtonPrefab : public Prefab
	{
	public:
		GameObject* CreateInstance() override;
	};
	
	// ===============================================================================

	class TutorialPrefab : public Prefab
	{
	public:
		GameObject* CreateInstance() override;
	};
	
	// ===============================================================================

	class MousePrefab : public Prefab
	{
	public:
		GameObject* CreateInstance() override;
	};
	
	// ===============================================================================

	class PlayerPrefab : public Prefab
	{
	public:
		GameObject* CreateInstance() override;
	};

	// ===============================================================================
	
	class PlayerExplodePrefab : public Prefab
	{
	public:
		GameObject* CreateInstance() override;
	};

	// ===============================================================================

	class EnemyPrefab : public Prefab
	{
	public:
		GameObject* CreateInstance() override;
	};

	// ===============================================================================

	class EnemyMuzzlePrefab : public Prefab
	{
	public:
		GameObject* CreateInstance() override;
	};

	// ===============================================================================

	class EnemyBulletPrefab : public Prefab
	{
	public:
		GameObject* CreateInstance() override;
	};

	// ===============================================================================

	class EnemyBulletImpactPrefab : public Prefab
	{
	public:
		GameObject* CreateInstance() override;
	};

	// ===============================================================================

	class EnemyExplodePrefab : public Prefab
	{
	public:
		GameObject* CreateInstance() override;
	};

	// ===============================================================================

	class EnemySpawnerPrefab : public Prefab
	{
	public:
		GameObject* CreateInstance() override;
	};

	// ===============================================================================

	class LoseUIPrefab : public Prefab
	{
	public:
		GameObject* CreateInstance() override;
	};

	// ===============================================================================

	class CreditsPrefab : public Prefab
	{
	public:
		GameObject* CreateInstance() override;
	};

	// ===============================================================================

	class CreditsButtonPrefab : public Prefab
	{
	public:
		GameObject* CreateInstance() override;
	};

	// ===============================================================================

	class CreditsBackButtonPrefab : public Prefab
	{
	public:
		GameObject* CreateInstance() override;
	};

	// ===============================================================================



}}