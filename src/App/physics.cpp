#include <pch.h>
#include "physics.h"

#include "Util.hpp"
#include "GML/Constants.h"

namespace golf {

    //dynamic
    void DynamicPhysicsComponent::apply_force(GML::Vec3f force, GML::Vec3f apply_point){   //zmienia acceleration
        m_net_force = m_net_force + static_cast<GML::Vec2f>(force)  ;
        m_net_torque = m_net_torque + GML::Vec3f::crossProduct(apply_point,force);
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

        m_acceleration += m_net_force / m_mass;
        m_velocity += m_acceleration;
        m_position += m_velocity * deltaT;

        m_angular_acceleration += m_net_torque *(1/ m_inertia);
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

        m_net_force.set(0,0); //suma wszystkich sil
        m_net_torque.set(0,0,0); //suma wszystkich sil obrotowych
    }
    void DynamicPhysicsComponent::set_position(float x,float y){
		m_position.set(x, y);
    }
    void DynamicPhysicsComponent::set_rotation(float rot){
        m_rotation.z = rot;
    }
    DynamicPhysicsComponent::DynamicPhysicsComponent(float mass,float inertia){
        m_mass = mass;
        m_inertia = inertia;
    }
		


    //kinematic
    void KinematicPhysicsComponent::update_positions(float deltaT){                          //apply net_force and net_torque i zeruj
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
    
    void KinematicPhysicsComponent::set_position(float x,float y){
        m_position.x = x;
        m_position.y = y;
    }
    void KinematicPhysicsComponent::set_rotation(float rot){
        m_rotation.z = rot;
    }

    //static
    
    void StaticPhysicsComponent::set_position(float x,float y){
        m_position.x = x;
        m_position.y = y;
    }
    void StaticPhysicsComponent::set_rotation(float rot){
        m_rotation.z = rot;
    }
    

    }

