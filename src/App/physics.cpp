#include <pch.h>

#include "physics.h"

#include "Util.hpp"
#include "GML/Constants.h"

#include <dtl.h>

namespace golf {


	HitboxComponent::HitboxComponent(HitboxComponent::Typ tego_typu ,float radius = 0) 
		: m_Typ_obiektu(tego_typu), m_radius(radius) {}

	SurfaceComponent::SurfaceComponent(float a,float c)
		: kineticFrict(a), rollingResitance(c) {}
		
	

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
			m_Dynamic_Object->update_positions(deltaT,m_Surfaces);
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
			if(!std::isfinite(Wiemcoto.x) || !std::isfinite(Wiemcoto.y) || m_penetrationDepth > m_Obj1->m_radius) {
				DTL_ERR("kot wybuchł");
				return;
			}
			Owner1->getTransform()->x += Wiemcoto.x;
			Owner1->getTransform()->y += Wiemcoto.y;

			const float odbijability = 0.7f; //0 - 1 im wyzej tym odbijablej
			const float tarcielity = 0.1f;

			if(Owner2->hasComponent<KinematicPhysicsComponent>()){
				auto CircleComp = Owner1->getComponent<DynamicPhysicsComponent>();
				GML::Vec2f CirclePos = {Owner1->getTransform()->x, Owner1->getTransform()->y};
				GML::Vec2f PointOnCircleVelocity = CircleComp->m_velocity + static_cast<GML::Vec2f>( static_cast<GML::Vec3f>(CirclePos - m_collidePoint) % CircleComp->m_angular_velocity);

				auto BoxComp = Owner2->getComponent<KinematicPhysicsComponent>();
				GML::Vec2f BoxPos = {Owner2->getTransform()->x, Owner2->getTransform()->y};
				GML::Vec2f PointOnBoxVelocity = BoxComp->m_velocity + static_cast<GML::Vec2f>( static_cast<GML::Vec3f>(BoxPos - m_collidePoint) % BoxComp->m_angular_velocity);

				GML::Vec2f RelativeVelocity = PointOnCircleVelocity - PointOnBoxVelocity;
				float NormalRelVel = m_normalCollidePoint * RelativeVelocity;
				float TangentRelVel = GML::Vec2f(m_normalCollidePoint.y, -m_normalCollidePoint.x) * RelativeVelocity;
				if(TangentRelVel > 0) { TangentRelVel = 1; }
				else if(TangentRelVel < 0) { TangentRelVel = -1; }
				else { TangentRelVel = 0; }

				if(NormalRelVel < 0) { return; } //Jeśli obiekty już się oddalają to git elegancko super bomba

				float impulseStrenght = (-(1+odbijability) * NormalRelVel * CircleComp->m_mass);
				GML::Vec3f impulse = static_cast<GML::Vec3f>(m_normalCollidePoint) * impulseStrenght;
				CircleComp->apply_impulse(impulse, static_cast<GML::Vec3f>(CirclePos - m_collidePoint));

				GML::Vec3f tarcie = (GML::Vec3f(-m_normalCollidePoint.y, m_normalCollidePoint.x, 0)) * impulseStrenght * tarcielity * TangentRelVel;
				CircleComp->apply_impulse(tarcie, static_cast<GML::Vec3f>(CirclePos - m_collidePoint));

				DTL_ERR("Boing");
			}

			if(Owner2->hasComponent<StaticPhysicsComponent>()){
				auto CircleComp = Owner1->getComponent<DynamicPhysicsComponent>();
				GML::Vec2f CirclePos = {Owner1->getTransform()->x, Owner1->getTransform()->y};
				GML::Vec2f RelativeVelocity = CircleComp->m_velocity + static_cast<GML::Vec2f>( static_cast<GML::Vec3f>(CirclePos - m_collidePoint) % CircleComp->m_angular_velocity);

				float NormalRelVel = m_normalCollidePoint * RelativeVelocity;
				float TangentRelVel = GML::Vec2f(m_normalCollidePoint.y, -m_normalCollidePoint.x) * RelativeVelocity;
				if(TangentRelVel > 0) { TangentRelVel = 1; }
				else if(TangentRelVel < 0) { TangentRelVel = -1; }
				else { TangentRelVel = 0; }

				if(NormalRelVel < 0) { return; } //Jeśli obiekty już się oddalają to git elegancko super bomba

				float impulseStrenght = (-(1+odbijability) * NormalRelVel * CircleComp->m_mass);
				GML::Vec3f impulse = static_cast<GML::Vec3f>(m_normalCollidePoint) * impulseStrenght;
				CircleComp->apply_impulse(impulse, static_cast<GML::Vec3f>(CirclePos - m_collidePoint));

				GML::Vec3f tarcie = (GML::Vec3f(m_normalCollidePoint.y, -m_normalCollidePoint.x, 0)) * impulseStrenght * tarcielity * TangentRelVel;
				CircleComp->apply_impulse(tarcie, static_cast<GML::Vec3f>(CirclePos - m_collidePoint));
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
		m_angular_velocity += GML::Vec3f::crossProduct(apply_point,impulse)/m_inertia;
	}
	void DynamicPhysicsComponent::apply_torque(GML::Vec3f torque) {
		m_net_torque += torque;
	}
	void DynamicPhysicsComponent::apply_torque_impulse(GML::Vec3f torque) {
		m_angular_velocity += torque / m_inertia;
	}

	void DynamicPhysicsComponent::update_positions(float deltaT, std::vector<std::shared_ptr<SurfaceComponent>>& Surfaces) {                          //apply net_force and net_torque i zeruj
		//float& x = getTransform()->x;
		//float& y = getTransform()->y;
		auto [x, y] = getTransform()->getPos();
		m_position.set(x, y);

		//get rotation
		float rotation = getTransform()->rot * GML::F_DEG_TO_RAD;
		//aktualnie rotacja skosna nie jest przechowywana w transformie, trzeba to zmienic //rotacja skośna nie będzie przechowywana w transformie xD
		m_rotation.z = rotation; //to be changed

		auto Hitbox = getOwner()->getComponent<HitboxComponent>();
		float radius = 0;
		if (Hitbox) {
			radius = Hitbox->m_radius;
		}

		[[maybe_unused]] float kineticFrict = 0.1f;
		[[maybe_unused]] float rollingResitance = 0.01f;

		for (auto& ref : Surfaces) {
			float xScale = ref->getOwner()->getTransform()->xScale / 2, yScale = ref->getOwner()->getTransform()->yScale / 2;
			float xSurf = ref->getOwner()->getTransform()->x, ySurf = ref->getOwner()->getTransform()->y;
			float rotSurf = ref->getOwner()->getTransform()->rot;

			GML::Mat2f AntyRotSurf = { std::cos(rotSurf),std::sin(rotSurf),-std::sin(rotSurf),std::cos(rotSurf) };

			GML::Vec2f newPoint = AntyRotSurf * (m_position - GML::Vec2f(xSurf, ySurf)) + GML::Vec2f(xSurf, ySurf);

			if (xSurf - xScale < newPoint.x && newPoint.x < xSurf + xScale && ySurf - yScale < newPoint.y && newPoint.y < ySurf + yScale) {
				//koliduje z powierzchnia
				kineticFrict = ref->kineticFrict;
				rollingResitance = ref->rollingResitance;
				break;
			}
		}

		//GML::Vec3f rollingResForce = {0,0,0};

		//if(m_velocity.getLength() > 0){
		//	rollingResForce  = -1*(static_cast<GML::Vec3f>(m_velocity.normalized())) * m_mass * Gravity * rollingResitance * radius;
		//}

		//GML::Vec2f contactPointVel = (m_velocity + static_cast<GML::Vec2f>( GML::Vec3f(0,0,-radius) % m_angular_velocity)) * -1;
		//GML::Vec3f friction;
		//if(contactPointVel.getLength() < 0.001f){ //mało
		//	friction = (static_cast<GML::Vec3f>(m_net_force) + rollingResForce);
		//	if(friction.getLength() > m_mass*Gravity*staticFrict ){
		//		friction = {0,0,0};
		//	}
		//}
		//else{
		//	friction = (static_cast<GML::Vec3f>(contactPointVel.normalized())) * m_mass * Gravity * kineticFrict * -1;
		//}
		//DTL_WAR("{0} {0} {0}", friction.x, friction.y, friction.z);
		//
		//DTL_WAR("{0}", static_cast<GML::Vec2f>(GML::Vec3f(0, 0, -radius) % m_angular_velocity));
		//
		//apply_force(rollingResForce, {0,0,0});
		//apply_force(friction, {0,0,-radius});



		m_acceleration = m_net_force / m_mass;
		m_velocity += m_acceleration * deltaT;
		m_position += m_velocity * deltaT;

		m_angular_acceleration = m_net_torque / m_inertia;
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
		getTransform()->rot = rotation * GML::F_RAD_TO_DEG;

		////////////////////
		// Frictions here:
		////////////////////

		const float gravity = 9.81f;

		// Spinning in Z-axis
		if (m_angular_velocity.z != 0) {
			float direction = m_angular_velocity.z / abs(m_angular_velocity.z);
			float spinningDamping = 2.5f * rollingResitance * gravity / radius * deltaT * direction;
			if (abs(spinningDamping) >= abs(m_angular_velocity.z)) {
				m_angular_velocity.z = 0;
			} else {
				m_angular_velocity.z -= spinningDamping;
			}
		}

		GML::Vec2f contactPointVel = (m_velocity + static_cast<GML::Vec2f>(GML::Vec3f(0, 0, -radius) % m_angular_velocity));

		if(contactPointVel.getLengthSquared() > 0) {
			float linearDamping = kineticFrict * gravity * deltaT;
			m_velocity -= linearDamping * contactPointVel / contactPointVel.getLength();
			float rollDamping = 2.5f * linearDamping / radius;
			GML::Vec2f delta = contactPointVel.normalized() * rollDamping;
			float tanDelta = -1 * delta * static_cast<GML::Vec2f>(m_angular_velocity).normalized();
			GML::Vec2f perp = delta + tanDelta * static_cast<GML::Vec2f>(m_angular_velocity).normalized();
			
			if (tanDelta > static_cast<GML::Vec2f>(m_angular_velocity).getLength()) {
				tanDelta = static_cast<GML::Vec2f>(m_angular_velocity).getLength();
			}
			GML::Vec2f tan = static_cast<GML::Vec2f>(m_angular_velocity).normalized() * tanDelta * -1;

			m_angular_velocity += static_cast<GML::Vec3f>(tan + perp);

		} else if (m_velocity.getLengthSquared() > 0) {
			float linearDamping = rollingResitance * gravity * deltaT;
			if (linearDamping >= m_velocity.getLength()) {
				m_velocity = { 0, 0 };
				m_angular_velocity.x = 0;
				m_angular_velocity.y = 0;
			} else {
				m_velocity -= linearDamping * m_velocity / m_velocity.getLength();
				m_angular_velocity.x = (GML::Vec3f(0,0,-1) % static_cast<GML::Vec3f>(m_velocity)).x;
				m_angular_velocity.y = (GML::Vec3f(0,0,-1) % static_cast<GML::Vec3f>(m_velocity)).y;
			}
		}

		DTL_WAR("{0}", contactPointVel);


		DTL_ENT("{0} {0} {0}",m_angular_velocity.x,m_angular_velocity.y,m_angular_velocity.z);

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

