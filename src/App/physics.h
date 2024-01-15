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

	class Hitbox : public Component{
	public:
		enum Typ {Kula, Box};
		Typ m_Typ_obiektu;
		float m_radius;
		Hitbox(Typ,float);
	};

	class DynamicPhysicsComponent : public Component{
	public:
		bool m_in_physics_scope;
		void apply_force(GML::Vec3f force, GML::Vec3f apply_point);   //zmienia acceleration
		void apply_impulse(GML::Vec3f impulse, GML::Vec3f apply_point); //zmienia velocity
		void update_positions(float deltaT);  

		explicit DynamicPhysicsComponent(float mass=1,float inertia=1);

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
	private:
		GML::Vec2f m_position;
		GML::Vec3f m_rotation;  
	};

	class Physics_Engine{
	public:
		Physics_Engine() = default;

		void update(float deltaT);

		//return ID of element
		std::shared_ptr<DynamicPhysicsComponent> addDynamicElement();
		std::shared_ptr<KinematicPhysicsComponent> addKinematicElement();
		std::shared_ptr<StaticPhysicsComponent> addStaticElement();


	private:
		//trzymam je
		std::vector<std::shared_ptr<DynamicPhysicsComponent>> m_Dynamic_Objects;
		std::vector<std::shared_ptr<KinematicPhysicsComponent>> m_Kinematic_Objects;
		std::vector<std::shared_ptr<StaticPhysicsComponent>> m_Static_Objects;

		class Collision{
		public:
			Collision(std::shared_ptr<Hitbox>,std::shared_ptr<Hitbox>,GML::Vec2f,GML::Vec2f,float);

			std::shared_ptr<Hitbox> m_Obj1,m_Obj2;

			GML::Vec2f m_collidePoint;
			GML::Vec2f m_normalCollidePoint;

			float m_penetrationDepth;

			void reisolveCollison();//ide do wlasciciela Entity, ide do jego komponentu fizycznego i chuj
		};

	};

}

