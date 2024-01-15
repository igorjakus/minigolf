#include <vector>
#include <queue>

#include "ECS/Entity.h"
#include "ECS/Component.h"
#include "GML/LinearAlgebra/Vec2f.h"
#include "GML/LinearAlgebra/Vec3f.h"

//!Zosta� tydzie�
//!nieca�y
//!nie dzia�a tu nic

namespace golf {

	

	class DynamicPhysicsComponent : public Component{
	public:
		bool m_in_physics_scope;
		void apply_force(GML::Vec3f force, GML::Vec3f apply_point);   //zmienia acceleration
		void apply_impulse(GML::Vec3f impulse, GML::Vec3f apply_point); //zmienia velocity
		void update_positions(float deltaT);  

		explicit DynamicPhysicsComponent(float mass=1,float inertia=1);
		~DynamicPhysicsComponent() override = default;

	private:
		GML::Vec2f m_velocity;
		GML::Vec2f m_acceleration;

		GML::Vec3f m_angular_velocity;
		GML::Vec3f m_angular_acceleration;

		GML::Vec2f m_net_force; //suma wszystkich sil
		GML::Vec3f m_net_torque; //suma wszystkich sil obrotowych
		
		float m_mass;
		float m_inertia;

		GML::Vec2f m_position;
		GML::Vec3f m_rotation;  

	};

	class KinematicPhysicsComponent : public Component{
	public:
		bool m_in_physics_scope;
		void update_positions(float deltaT);   
		
		~KinematicPhysicsComponent() override = default;

	private:
		GML::Vec2f m_velocity;
		GML::Vec2f m_acceleration;

		GML::Vec3f m_angular_velocity;
		GML::Vec3f m_angular_acceleration;

		GML::Vec2f m_position;
		GML::Vec3f m_rotation;  

	};

	class StaticPhysicsComponent : public Component{
	public:
		bool m_in_physics_scope;
		~StaticPhysicsComponent() override = default;
	private:
		GML::Vec2f m_position;
		GML::Vec3f m_rotation;  
	};

	class Physics_Engine{
	public:
		Physics_Engine() = default;
		~Physics_Engine() = default;

		void updateElements(float deltaT);

		//return ID of element
		std::shared_ptr<DynamicPhysicsComponent> addDynamicElement();
		std::shared_ptr<KinematicPhysicsComponent> addKinematicElement();
		std::shared_ptr<StaticPhysicsComponent> addStaticElement();


	private:
		//trzymam je

		std::vector<std::shared_ptr<DynamicPhysicsComponent>> m_Dynamic_Objects;
		std::vector<std::shared_ptr<KinematicPhysicsComponent>> m_Kinematic_Objects;
		std::vector<std::shared_ptr<StaticPhysicsComponent>> m_Static_Objects;

	};

}

