#include "ECS/Entity.h"
#include "Component.h"
#include "GML/LinearAlgebra/Vec2f.h"
#include "GML/LinearAlgebra/Vec3f.h"


namespace golf {

    class PhysicsComponent : public Component{
        void apply_force(GML::Vec3f force, GML::Vec3f apply_point);   //zmienia acceleration
        void apply_impulse(GML::Vec3f impulse, GML::Vec3f apply_point); //zmienia velocity
        void update_positions(float deltaT);                          //apply net_force and net_torque i zeruj
        PhysicsComponent(float mass,float inertia);

    private:
        GML::Vec2f m_position; //nadpisuje
        GML::Vec2f m_velocity;
        GML::Vec2f m_acceleration;

        GML::Vec3f m_rotation; //nadpisuje
        GML::Vec3f m_angular_velocity;
        GML::Vec3f m_angular_acceleration;
        
        float m_mass;
        float m_inertia;

        GML::Vec2f m_net_force; //suma wszystkich sil
        GML::Vec3f m_net_torque; //suma wszystkich sil obrotowych
        

    }

}