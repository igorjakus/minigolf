#include "ECS/Entity.h"
#include "Component.h"
#include "GML/LinearAlgebra/Vec2f.h"
#include "GML/LinearAlgebra/Vec3f.h"
#include "GML/Constants.h"


namespace golf {

    //dynamic
    void DynamicPhysicsComponent::apply_force(GML::Vec3f force, GML::Vec3f apply_point){   //zmienia acceleration
        m_net_force += force;
        m_net_torque += GML::Vec3f::crossProduct(apply_point,force);
    }

    void DynamicPhysicsComponent::apply_impulse(GML::Vec3f impulse, GML::Vec3f apply_point){ //zmienia velocity
        m_velocity += impulse/m_mass;
        m_angular_velocity += GML::Vec3f::crossProduct(impulse,apply_point)/m_inertia;
    }
    void DynamicPhysicsComponent::update_positions(float deltaT){                          //apply net_force and net_torque i zeruj
        float& x = getTransform()->x;
		float& y = getTransform()->y;
        
        float& rotation = getTransform()->rot;

        m_position.set(x,y);

        //get rotation

        //aktualnie rotacja skosna nie jest przechowywana w transformie, trzeba to zmienic
        m_rotation.z = rotation; //to be changed

        m_acceleration += m_net_force / m_mas;
        m_velocity += m_acceleration;
        m_position += m_velocity * deltaT;

        m_angular_acceleration += m_net_torque / m_inertia;
        m_angular_velocity += m_angular_acceleration;
        m_rotation += m_angular_velocity * deltaT;

        m_rotation.x = util::clamp(m_rotation.x,0,2*GML::M_PI);
        m_rotation.y = util::clamp(m_rotation.y,0,2*GML::M_PI);
        m_rotation.z = util::clamp(m_rotation.z,0,2*GML::M_PI);

        x = m_position.x;
        y = m_position.y;
        //set rotation
        
        rotation = m_rotation.z; //to be changed!!!

        m_net_force.set(0,0); //suma wszystkich sil
        m_net_torque.set(0,0,0); //suma wszystkich sil obrotowych
    }
    DynamicPhysicsComponent::set_position(float x,float y){
        m_position.x = x;
        m_position.y = y;
    }
    DynamicPhysicsComponent::set_rotation(float rot){
        m_rotation.z = rot;
    }
    DynamicPhysicsComponent::DynamicPhysicsComponent(float mass,float inertia){
        m_mass = mass;
        m_inertia = inertia;
    }


    //kinematic
    void KinematicPhysicsComponent::apply_force(GML::Vec3f force, GML::Vec3f apply_point){   //zmienia acceleration
        m_net_force += force;
        m_net_torque += GML::Vec3f::crossProduct(apply_point,force);
    }

    void KinematicPhysicsComponent::update_positions(float deltaT){                          //apply net_force and net_torque i zeruj
        float& x = getTransform()->x;
		float& y = getTransform()->y;
        
        float& rotation = getTransform()->rot;

        m_position.set(x,y);

        //get rotation

        //aktualnie rotacja skosna nie jest przechowywana w transformie, trzeba to zmienic
        m_rotation.z = rotation; //to be changed

        m_acceleration += m_net_force / m_mas;
        m_velocity += m_acceleration;
        m_position += m_velocity * deltaT;

        m_angular_acceleration += m_net_torque / m_inertia;
        m_angular_velocity += m_angular_acceleration;
        m_rotation += m_angular_velocity * deltaT;

        m_rotation.x = util::clamp(m_rotation.x,0,2*GML::M_PI);
        m_rotation.y = util::clamp(m_rotation.y,0,2*GML::M_PI);
        m_rotation.z = util::clamp(m_rotation.z,0,2*GML::M_PI);

        x = m_position.x;
        y = m_position.y;
        //set rotation
        
        rotation = m_rotation.z; //to be changed!!!

        m_net_force.set(0,0); //suma wszystkich sil
        m_net_torque.set(0,0,0); //suma wszystkich sil obrotowych
    }
    
    KinematicPhysicsComponent::set_position(float x,float y){
        m_position.x = x;
        m_position.y = y;
    }
    KinematicPhysicsComponent::set_rotation(float rot){
        m_rotation.z = rot;
    }

    KinematicPhysicsComponent::KinematicPhysicsComponent(float mass,float inertia){
        m_mass = mass;
        m_inertia = inertia;
    }

    //static
    
    StaticPhysicsComponent::set_position(float x,float y){
        m_position.x = x;
        m_position.y = y;
    }
    StaticPhysicsComponent::set_rotation(float rot){
        m_rotation.z = rot;
    }
    StaticPhysicsComponent::StaticPhysicsComponent(float mass,float inertia){
        m_mass = mass;
        m_inertia = inertia;
    }
    

    }

