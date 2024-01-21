#pragma once

#include "ECS/Component.h"
#include "GML/LinearAlgebra/Vec2f.h"
#include "GML/LinearAlgebra/Mat2f.h"
#include "GML/LinearAlgebra/Vec3f.h"

//!Zosta� tydzie�
//!nieca�y
//!nie dzia�a tu nic

namespace golf {

	class HitboxComponent : public Component{
	public:
		enum Typ {Kula, Box};
		Typ m_Typ_obiektu;
		float m_radius;
		HitboxComponent(Typ,float);
	};

	class SurfaceComponent : public Component{
	public:
		float rollingResistance;
		float spinningResistance;

		SurfaceComponent(float,float);

	};


	class DynamicPhysicsComponent : public Component{
	public:
		bool m_in_physics_scope;
		void apply_force(GML::Vec3f force, GML::Vec3f apply_point);   //zmienia acceleration
		void apply_impulse(GML::Vec3f impulse, GML::Vec3f apply_point); //zmienia velocity
		void apply_torque(GML::Vec3f torque);
		void apply_torque_impulse(GML::Vec3f torque);
		void update_positions(float deltaT,std::vector<std::shared_ptr<SurfaceComponent>> &Surfaces);  

		[[nodiscard]] bool isMoving() const;
		[[nodiscard]] bool exploded() const;
		void explode();

		explicit DynamicPhysicsComponent(float mass=1,float inertia=1);

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

		bool m_exploded;

	};

	class KinematicPhysicsComponent : public Component{
	public:
		bool m_in_physics_scope;
		void update_positions(float deltaT);   

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
	private:
		GML::Vec2f m_position;
		GML::Vec3f m_rotation;  
	};

	class PhysicsEngine{
	public:
		PhysicsEngine() = default;

		void update(float deltaT);
		void check_collision(std::shared_ptr<HitboxComponent>, std::shared_ptr<HitboxComponent>);

		//return ID of element
		std::shared_ptr<DynamicPhysicsComponent> addDynamicElement(float mass = 1.f, float inertia = 0.5f);
		std::shared_ptr<KinematicPhysicsComponent> addKinematicElement();
		std::shared_ptr<StaticPhysicsComponent> addStaticElement();

		std::shared_ptr<SurfaceComponent> addSurfaceElement(float rollingResistance = 0.1f, float spinningResistance = 0.05f);

	private:
		//trzymam je
		std::vector<std::shared_ptr<DynamicPhysicsComponent>> m_Dynamic_Objects;
		std::vector<std::shared_ptr<KinematicPhysicsComponent>> m_Kinematic_Objects;
		std::vector<std::shared_ptr<StaticPhysicsComponent>> m_Static_Objects;

		std::vector<std::shared_ptr<SurfaceComponent>> m_Surfaces;

		class Collision{
		public:
			Collision(std::shared_ptr<HitboxComponent>,std::shared_ptr<HitboxComponent>,GML::Vec2f,GML::Vec2f,float);

			std::shared_ptr<HitboxComponent> m_Obj1,m_Obj2;

			GML::Vec2f m_collidePoint;
			GML::Vec2f m_normalCollidePoint;

			float m_penetrationDepth;

			void reisolveCollison();//ide do wlasciciela Entity, ide do jego komponentu fizycznego i chuj
		};

		std::queue<Collision> ColideQue;

	};

}

