#include "ECS/Entity.h"
#include "Component.h"
#include "GML/LinearAlgebra/Vec2f.h"
#include "GML/LinearAlgebra/Vec3f.h"


namespace golf {

    class DynamicPhysicsComponent : public Component{
        void apply_force(GML::Vec3f force, GML::Vec3f apply_point);   //zmienia acceleration
        void apply_impulse(GML::Vec3f impulse, GML::Vec3f apply_point); //zmienia velocity
        void update_positions(float deltaT);                          //apply net_force and net_torque i zeruj
        DynamicPhysicsComponent(float mass,float inertia);
        void set_position(float x,float y);
        void set_rotation(float rot);

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

    class KinematicPhysicsComponent : public Component{
        void apply_force(GML::Vec3f force, GML::Vec3f apply_point);   //zmienia acceleration
        void update_positions(float deltaT);                          //apply net_force and net_torque i zeruj
        KinematicPhysicsComponent(float mass,float inertia);
        void set_position(float x,float y);
        void set_rotation(float rot);

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

    class StaticPhysicsComponent : public Component{
        StaticPhysicsComponent(float mass,float inertia);
        void set_position(float x,float y);
        void set_rotation(float rot);

    private:
        GML::Vec2f m_position; //nadpisuje

        GML::Vec3f m_rotation; //nadpisuje
        
        float m_mass;
        float m_inertia;
        
    }

}