#include <pch.h>
#include <dtl.h>

#include <utility>
#include "physics.h"

#include "Util.hpp"
#include "GML/Constants.h"

namespace golf {


	HitboxComponent::HitboxComponent(HitboxComponent::Typ tego_typu ,float radius = 0) 
		: m_Typ_obiektu(tego_typu), m_radius(radius) {}

	//physics engine

	void Physics_Engine::update(float deltaT){
		//main Collision program

		for(auto MyDynamicObject : m_Dynamic_Objects){
			auto HitboxDyna = MyDynamicObject->getOwner()->getComponent<HitboxComponent>();
			if(!HitboxDyna) { continue; }

			for(auto MyKinematicObject : m_Kinematic_Objects){
				auto HitboxKina = MyKinematicObject->getOwner()->getComponent<HitboxComponent>();
				if(!HitboxKina) { continue; }
				//check collision
				//make hitboxes
				check_collision(HitboxDyna,HitboxKina);
			}
			for(auto MyStaticObject : m_Static_Objects){
				auto HitboxStalina = MyStaticObject->getOwner()->getComponent<HitboxComponent>();
				if(!HitboxStalina) { continue; }
				//collise the
				check_collision(HitboxDyna,HitboxStalina);
			}
			// //prevent double collision
			// for(long unsigned int dyn_second_id = dyn_id + 1;dyn_second_id < m_Dynamic_Objects.size();dyn_second_id++){
			// 	auto MySecondDynamicObject = m_Dynamic_Objects[dyn_second_id];
			// 	//collise the
			// }
		}

		while(!ColideQue.empty()){
			ColideQue.front().reisolveCollison();
			ColideQue.pop();
		}

		for(auto & m_Dynamic_Object : m_Dynamic_Objects){
			m_Dynamic_Object->update_positions(deltaT);
		}

		for(auto & m_Kinematic_Object : m_Kinematic_Objects){
			m_Kinematic_Object->update_positions(deltaT);
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


	//Kula z kwadratem
	void Physics_Engine::check_collision(std::shared_ptr<HitboxComponent> A,std::shared_ptr<HitboxComponent> B){
		//stworz siatke boxa
		float Ballx = A->getOwner()->getTransform()->x;
		float Bally = A->getOwner()->getTransform()->y;
		float Ballradius = A->m_radius;
		float Boxx = B->getOwner()->getTransform()->x;
		float Boxy = B->getOwner()->getTransform()->y;
		float BoxRot = B->getOwner()->getTransform()->rot*GML::F_DEG_TO_RAD;
		float Boxxscale = B->getOwner()->getTransform()->xScale;
		float Boxyscale = B->getOwner()->getTransform()->yScale;

		if( (Ballx - Boxx)*(Ballx - Boxx) + (Bally - Boxy)*(Bally - Boxy) >
		 (Boxxscale + Boxyscale)*(Boxxscale + Boxyscale)/4 + 
		 2*(Boxxscale + Boxyscale)*Ballradius + 
		 Ballradius*Ballradius){
			return;
		}

		const GML::Mat2f AntyRotBox = {std::cos(BoxRot),std::sin(BoxRot),-std::sin(BoxRot),std::cos(BoxRot)};
		const GML::Mat2f RotBox = {std::cos(BoxRot),-std::sin(BoxRot),std::sin(BoxRot),std::cos(BoxRot)};
		
		GML::Vec2f BoxPos = {Boxx,Boxy};

		GML::Vec2f newBallPos = AntyRotBox*(GML::Vec2f(Ballx,Bally) - BoxPos) + BoxPos;
		float closestX = util::clamp(newBallPos.x,Boxx - Boxxscale/2, Boxx + Boxxscale/2);
		float closestY = util::clamp(newBallPos.y,Boxy - Boxyscale/2, Boxy + Boxyscale/2);
		GML::Vec2f closest = {closestX,closestY};

		float ruchanie = (closest - newBallPos).getLength() - Ballradius;

		if( ruchanie > 0 ) { return; }

		GML::Vec2f normalny = (closest - newBallPos).normalized();

		closest = RotBox*(closest - BoxPos) + BoxPos;
		normalny = RotBox*normalny;

		ColideQue.emplace(A,B,closest,normalny,ruchanie);

	}

	Physics_Engine::Collision::Collision(std::shared_ptr<HitboxComponent> O1,std::shared_ptr<HitboxComponent> O2,
										GML::Vec2f collidePoint,GML::Vec2f normal,float penetracja)
		: m_Obj1(std::move(O1)), m_Obj2(std::move(O2)), m_collidePoint(collidePoint), m_normalCollidePoint(normal), m_penetrationDepth(penetracja) {}

	void Physics_Engine::Collision::reisolveCollison(){
		auto* Owner1 = m_Obj1->getOwner();
		auto* Owner2 = m_Obj2->getOwner();

		if(Owner2->hasComponent<DynamicPhysicsComponent>()){
			auto* temp = Owner1;
			Owner1 = Owner2;
			Owner2 = temp;
		}
		
		if(m_Obj1->m_Typ_obiektu == HitboxComponent::Box || m_Obj2->m_Typ_obiektu == HitboxComponent::Kula) { return; }

		//ball with box colliison
		
		if(Owner1->hasComponent<DynamicPhysicsComponent>()){

			GML::Vec2f Wiemcoto = m_normalCollidePoint*m_penetrationDepth;
			Owner1->getTransform()->x += Wiemcoto.x;
			Owner1->getTransform()->y += Wiemcoto.y;

			if(Owner2->hasComponent<KinematicPhysicsComponent>()){
				auto maciej = Owner2->getComponent<KinematicPhysicsComponent>();
				GML::Vec2f Pos = {Owner2->getTransform()->x,Owner2->getTransform()->y};
				float RelativeVelocity = (Owner1->getComponent<DynamicPhysicsComponent>()->m_velocity - (maciej->m_velocity + GML::Vec2f( GML::Vec3f( Pos - m_collidePoint )% maciej->m_angular_velocity ) ))*m_normalCollidePoint;
				float odbijability = 0.5f; //0 - 1 im wyzej tym odbijablej
				if(RelativeVelocity < 0) return; //to jest problem, za czesto sie uruchamia
				DTL_ENT("Status siura: kolidowany");
				Owner1->getComponent<DynamicPhysicsComponent>()->apply_impulse( GML::Vec3f(m_normalCollidePoint) * (-(1+odbijability) * RelativeVelocity * Owner1->getComponent<DynamicPhysicsComponent>()->m_mass)
																				, GML::Vec3f(m_collidePoint) );

			}

			if(Owner2->hasComponent<StaticPhysicsComponent>()){

				float RelativeVelocity = Owner1->getComponent<DynamicPhysicsComponent>()->m_velocity*m_normalCollidePoint;
				float odbijability = 0.5f; //0 - 1 im wyzej tym odbijablej
				DTL_ENT("Status siura: kolidowany");
				if(RelativeVelocity < 0) return; //to jest problem, za czesto sie uruchamia
				Owner1->getComponent<DynamicPhysicsComponent>()->apply_impulse( GML::Vec3f(m_normalCollidePoint) * (-(1+odbijability) * RelativeVelocity * Owner1->getComponent<DynamicPhysicsComponent>()->m_mass)
																				, GML::Vec3f(m_collidePoint) );

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

	}

	DynamicPhysicsComponent::DynamicPhysicsComponent(float mass,float inertia)
		: m_in_physics_scope(true), m_mass(mass), m_inertia(inertia) {}
		


	//kinematic
	void KinematicPhysicsComponent::update_positions(float deltaT) {                          //apply net_force and net_torque i zeruj
		float& x = getTransform()->x;
		float& y = getTransform()->y;
		
		float rotation = getTransform()->rot * GML::F_DEG_TO_RAD;

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

		getTransform()->rot = rotation*GML::F_RAD_TO_DEG;

		m_acceleration.set(0,0); //suma wszystkich sil
		m_angular_acceleration.set(0,0,0); //suma wszystkich sil obrotowych
	}


	
	

	}

