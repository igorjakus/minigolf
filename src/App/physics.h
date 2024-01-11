#include <vector>

#include "ECS/Entity.h"
#include "Component.h"
#include "GML/LinearAlgebra/Vec2f.h"
#include "GML/LinearAlgebra/Vec3f.h"


namespace golf {

    class PhysicsComponent : public Component{
    public:
        enum struct PC_ID {
            Dynamic,
            Static,
            Kinematic
        };
        void set_position(float x,float y);
        void set_rotation(float rot);
        PhysicsComponent(float mass,float inertia);
        virtual ~PhysicsComponent() = default;
        virtual PC_ID getType();
    protected:
        GML::Vec2f m_position; //nadpisuje
        GML::Vec3f m_rotation; //nadpisuje
        
    };

    

    class DynamicPhysicsComponent : public PhysicsComponent{
    public:
        void apply_force(GML::Vec3f force, GML::Vec3f apply_point);   //zmienia acceleration
        void apply_impulse(GML::Vec3f impulse, GML::Vec3f apply_point); //zmienia velocity
        void update_positions(float deltaT);                          //apply net_force and net_torque i zeruj
        
        PC_ID getType() override;
        ~DynamicPhysicsComponent() override;

    private:
        GML::Vec2f m_velocity;
        GML::Vec2f m_acceleration;

        GML::Vec3f m_angular_velocity;
        GML::Vec3f m_angular_acceleration;

        GML::Vec2f m_net_force; //suma wszystkich sil
        GML::Vec3f m_net_torque; //suma wszystkich sil obrotowych
        
        float m_mass;
        float m_inertia;

    };

    class KinematicPhysicsComponent : public PhysicsComponent{
    public:
        void update_positions(float deltaT);                          //apply net_force and net_torque i zeruj
        KinematicPhysicsComponent(float mass,float inertia);
        void set_position(float x,float y);
        void set_rotation(float rot);

        PC_ID getType() override;
        ~KinematicPhysicsComponent() override;

    private:
        GML::Vec2f m_velocity;
        GML::Vec2f m_acceleration;

        GML::Vec3f m_angular_velocity;
        GML::Vec3f m_angular_acceleration;

        GML::Vec2f m_net_force; //suma wszystkich sil
        GML::Vec3f m_net_torque; //suma wszystkich sil obrotowych
        

    };

    class StaticPhysicsComponent : public PhysicsComponent{
    public:
        PC_ID getType() override;
        ~DynamicPhysicsComponent() override;
    };

    class Physics_Engine{
    public:
        void update_elements(float deltaT);
        void add_Collision_Object

    private:
        //trzymam je
        std::vector<DynamicPhysicsComponent> Dynamic_Objects;
        std::vector<KinematicPhysicsComponent> Kinematic_Objects;
        std::vector<StaticPhysicsComponent> Static_Objects;

    }

}