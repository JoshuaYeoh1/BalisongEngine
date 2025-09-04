#pragma once
#include "BaseComponent.h"
#include "GameObjectRef.h"
#include <glm\glm.hpp>

// ===============================================================================

namespace BalisongEngine{
namespace BalisongEngineComponents
{
	class VelocityMeterComponent; // forward declare
	class MoveComponent; // forward declare
	
	// ===============================================================================

	/// <summary>
	/// The component for following or avoiding a target, it can also predict a moving target's future position
	/// </summary>
	class PursuitComponent : public BaseComponent
	{
	public:

		/// <summary>
		/// ctor
		/// </summary>
		/// <param name="go"></param>
		/// <param name="comp_name"></param>
		PursuitComponent(BalisongEngineOCM::GameObject* go, const std::string& comp_name = "[PursuitComponent]");
		~PursuitComponent();

		void Update(float dt) override;

		// ===============================================================================
        
        /// <summary>
        /// The MoveComponent reference to modify when trying to move
        /// </summary>
        MoveComponent* vehicle = nullptr;
        /// <summary>
        /// The maximum movement speed
        /// </summary>
        float maxSpeed = 1;

        /// <summary>
        /// If should slow down when reaching target
        /// </summary>
        bool arrival = true;
        /// <summary>
        /// The range from the target to stop at when following
        /// </summary>
        float arrivalRange = .05f;
        /// <summary>
        /// The offset range by the arrivalRange to start slowing down when following
        /// </summary>
        float arrivalSlowingRangeOffset = 1;

        /// <summary>
        /// If should move away from the target
        /// </summary>
        bool evade = false;
        /// <summary>
        /// If should slow down when reaching the departureRange from the target
        /// </summary>
        bool departure = true;
        /// <summary>
        /// The range from the target to stop at when avoiding
        /// </summary>
        float departureRange = 2;
        /// <summary>
        /// The offset range by the departureRange to start slowing down when avoiding
        /// </summary>
        float departureSlowingRangeOffset = 1;

        /// <summary>
        /// If should try and predict a moving target's future location on the next frame
        /// </summary>
        bool predict = true;

        /// <summary>
        /// If should avoid the target if too close
        /// </summary>
        bool maintainDistance = false;
        /// <summary>
        /// The distance from the target to start avoiding if maintainDistance is enabled
        /// </summary>
        float maintainRangeOffset = 0;

        // ===============================================================================

        /// <summary>
        /// Sets the target reference to detect
        /// </summary>
        /// <param name="to"></param>
        void SetTarget(BalisongEngineOCM::GameObject* to);
        /// <summary>
        /// Gets the current target reference
        /// </summary>
        /// <returns></returns>
        BalisongEngineOCM::GameObjectRef GetTargetRef() const;
        
        // ===============================================================================

        /// <summary>
        /// If should rotation and look at the target position
        /// </summary>
        bool faceTarget = false;
        /// <summary>
        /// The offset in angles when looking at the target position
        /// </summary>
        float angleOffset = 0;

        // ===============================================================================

        void OnDestroy() override;
        
        // ===============================================================================

    private:

        BalisongEngineOCM::GameObjectRef targetRef;

        VelocityMeterComponent* velocityMeter = nullptr;

        glm::vec3 GetPredictedPos() const;
        glm::vec3 GetPredictedDir() const;
        bool IsFacingEachOther() const;

        glm::vec3 GetVelocity(); // dont use const
        float GetArrivalSpeed(float distance); // dont use const
        float GetDepartureSpeed(float distance); // dont use const

        void TryMaintainDistance(float distance);
	};

}
}