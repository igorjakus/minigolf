#include <memory>
#include <pch.h>
#include <dtl.h>
#include "physics.h"

#include "Util.hpp"
#include "GML/Constants.h"

namespace golf {


	Hitbox::Hitbox(Hitbox::Typ tego_typu ,float radius = 0){
		m_Typ_obiektu = tego_typu;
		m_radius = radius;
	}

	Physics_Engine::Collision::Collision(std::shared_ptr<Hitbox> O1,std::shared_ptr<Hitbox> O2,
										GML::Vec2f collidePoint,GML::Vec2f normal,float penetracja){
		m_Obj1 = O1;
		m_Obj2 = O2;
		m_collidePoint = collidePoint;
		m_normalCollidePoint = normal;
		m_penetrationDepth = penetracja;
	}

	void Physics_Engine::Collision::reisolveCollison(){
		auto Owner1 = m_Obj1.getOwner();
		auto Owner2 = m_Obj2.getOwner();

		if(Owner2->hasComponent<DynamicPhysicsComponent>()){
			auto temp = Owner1;
			Owner1 = Owner2;
			Owner2 = temp;
		}
		
		if(m_Obj1.m_Typ_obiektu == Hitbox::Box || m_Obj2.m_Typ_obiektu == Hitbox::Kula) return;

		//ball to box colliison
		
		if(Owner1->hasComponent<DynamicPhysicsComponent>()){

			if(Owner2->hasComponent<KinematicPhysicsComponent>()){
				
			}

			if(Owner2->hasComponent<StaticPhysicsComponent>()){

				

			}

		}

		
	}


	//dynamic
	void DynamicPhysicsComponent::apply_force(GML::Vec3f force, GML::Vec3f apply_point){   //zmienia acceleration
		m_net_force += static_cast<GML::Vec2f>(force)  ;
		m_net_torque += GML::Vec3f::crossProduct(apply_point,force);
	}

	void DynamicPhysicsComponent::apply_impulse(GML::Vec3f impulse, GML::Vec3f apply_point){ //zmienia velocity
		m_velocity += static_cast<GML::Vec2f>(impulse) * (1/m_mass);
		m_angular_velocity += GML::Vec3f::crossProduct(impulse,apply_point)*(1/m_inertia);
	}
	void DynamicPhysicsComponent::update_positions(float deltaT){                          //apply net_force and net_torque i zeruj
		//float& x = getTransform()->x;
		//float& y = getTransform()->y;
		auto[x, y] = getTransform()->getPos();
		
		float& rotation = getTransform()->rot;

		m_position.set(x,y);

		//get rotation

		//aktualnie rotacja skosna nie jest przechowywana w transformie, trzeba to zmienic //rotacja skośna nie będzie przechowywana w transformie xD
		m_rotation.z = rotation; //to be changed

		m_acceleration = m_net_force / m_mass; //!Czm tu jest += a nie = ?
		m_velocity += m_acceleration * deltaT; //!Wzór na przyspieszenie chwilowe
		m_position += m_velocity * deltaT;

		m_angular_acceleration = m_net_torque *(1/ m_inertia);
		m_angular_velocity += m_angular_acceleration * deltaT;
		m_rotation += m_angular_velocity * deltaT;
		
		m_rotation.x = (m_rotation.x > GML::F_2_PI) ? m_rotation.x - GML::F_2_PI : m_rotation.x;
		m_rotation.y = (m_rotation.x > GML::F_2_PI) ? m_rotation.y - GML::F_2_PI : m_rotation.y;
		m_rotation.z = (m_rotation.x > GML::F_2_PI) ? m_rotation.z - GML::F_2_PI : m_rotation.z;

		m_rotation.x = (m_rotation.x < 0) ? m_rotation.x + GML::F_2_PI : m_rotation.x;
		m_rotation.y = (m_rotation.y < 0) ? m_rotation.y + GML::F_2_PI : m_rotation.y;
		m_rotation.z = (m_rotation.z < 0) ? m_rotation.z + GML::F_2_PI : m_rotation.z;

		x = m_position.x;
		y = m_position.y;
		//set rotation
		
		rotation = m_rotation.z; //to be changed!!!

		m_net_force.set(0,0); //suma wszystkich sil
		m_net_torque.set(0,0,0); //suma wszystkich sil obrotowych
		DTL_ENT("{0}", m_velocity);

	}

	DynamicPhysicsComponent::DynamicPhysicsComponent(float mass,float inertia){
		m_mass = mass;
		m_inertia = inertia;
	}
		


	//kinematic
	void KinematicPhysicsComponent::update_positions(float deltaT) {                          //apply net_force and net_torque i zeruj
		float& x = getTransform()->x;
		float& y = getTransform()->y;
		
		float& rotation = getTransform()->rot;

		m_position.set(x, y);

		//get rotation

		//aktualnie rotacja skosna nie jest przechowywana w transformie, trzeba to zmienic
		m_rotation.z = rotation; //to be changed

		m_velocity += m_acceleration;
		m_position += m_velocity * deltaT;

		m_angular_velocity += m_angular_acceleration;
		m_rotation += m_angular_velocity * deltaT;

		m_rotation.x = (m_rotation.x > GML::F_2_PI) ? m_rotation.x - GML::F_2_PI : m_rotation.x;
		m_rotation.y = (m_rotation.x > GML::F_2_PI) ? m_rotation.y - GML::F_2_PI : m_rotation.y;
		m_rotation.z = (m_rotation.x > GML::F_2_PI) ? m_rotation.z - GML::F_2_PI : m_rotation.z;

		m_rotation.x = (m_rotation.x < 0) ? m_rotation.x + GML::F_2_PI : m_rotation.x;
		m_rotation.y = (m_rotation.y < 0) ? m_rotation.y + GML::F_2_PI : m_rotation.y;
		m_rotation.z = (m_rotation.z < 0) ? m_rotation.z + GML::F_2_PI : m_rotation.z;

		x = m_position.x;
		y = m_position.y;
		//set rotation
		
		rotation = m_rotation.z; //to be changed!!!

		m_acceleration.set(0,0); //suma wszystkich sil
		m_angular_acceleration.set(0,0,0); //suma wszystkich sil obrotowych
	}


	//physics engine

	void Physics_Engine::update(float deltaT){
		//main Collision program

		for(long unsigned int dyn_id=0;dyn_id < m_Dynamic_Objects.size();dyn_id++){
			auto MyDynamicObject = m_Dynamic_Objects[dyn_id];

			for(long unsigned int kinem_id=0;kinem_id < m_Kinematic_Objects.size();kinem_id++){
				auto MyKinematicObject = m_Kinematic_Objects[kinem_id];
				//collise the
			}
			for(long unsigned int static_id=0;static_id < m_Static_Objects.size();static_id++){
				auto MyStaticObject = m_Static_Objects[static_id];
				//collise the
			}
			//prevent double collision
			for(long unsigned int dyn_second_id = dyn_id + 1;dyn_second_id < m_Dynamic_Objects.size();dyn_second_id++){
				auto MySecondDynamicObject = m_Dynamic_Objects[dyn_second_id];
				//collise the
			}
		}

		for(long unsigned int id=0;id < m_Dynamic_Objects.size();id++){
			m_Dynamic_Objects[id]->update_positions(deltaT);
		}

		for(long unsigned int id=0;id < m_Kinematic_Objects.size();id++){
			m_Kinematic_Objects[id]->update_positions(deltaT);
		}
	}

	std::shared_ptr<DynamicPhysicsComponent> Physics_Engine::addDynamicElement(){
		std::shared_ptr<DynamicPhysicsComponent> Obj = std::make_shared<DynamicPhysicsComponent>();
		m_Dynamic_Objects.push_back(Obj);
		return Obj;
	}
	std::shared_ptr<KinematicPhysicsComponent> Physics_Engine::addKinematicElement(){
		std::shared_ptr<KinematicPhysicsComponent> Obj = std::make_shared<KinematicPhysicsComponent>();
		m_Kinematic_Objects.push_back(Obj);
		return Obj;
	}
	std::shared_ptr<StaticPhysicsComponent> Physics_Engine::addStaticElement(){
		std::shared_ptr<StaticPhysicsComponent> Obj = std::make_shared<StaticPhysicsComponent>();
		m_Static_Objects.push_back(Obj);
		return Obj;
	}

	

	}

