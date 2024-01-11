#include <vector>

#include "ECS/Entity.h"
#include "ECS/Component.h"
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
        ~PhysicsComponent() override = default;
        virtual PC_ID getType() = 0;
    protected:
        GML::Vec2f m_position; //nadpisuje
        GML::Vec3f m_rotation; //nadpisuje
        
    };

    class DynamicPhysicsComponent : public PhysicsComponent{
    public:
        void apply_force(GML::Vec3f force, GML::Vec3f apply_point);   //zmienia acceleration
        void apply_impulse(GML::Vec3f impulse, GML::Vec3f apply_point); //zmienia velocity
        void update_positions(float deltaT);                          //apply net_force and net_torque i zeruj
        void set_position(float x,float y);
        void set_rotation(float rot);

        PC_ID getType() override;
        DynamicPhysicsComponent(float mass,float inertia);
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
        void set_position(float x,float y);
        void set_rotation(float rot);
        

        PC_ID getType() override;
        ~KinematicPhysicsComponent() override;

    private:
        GML::Vec2f m_velocity;
        GML::Vec2f m_acceleration;

        GML::Vec3f m_angular_velocity;
        GML::Vec3f m_angular_acceleration;

    };

    class StaticPhysicsComponent : public PhysicsComponent{
    public:
        void set_position(float x,float y);
        void set_rotation(float rot);

        PC_ID getType() override;
        ~StaticPhysicsComponent() override;
    };

    class Physics_Engine{
    public:
        void update_elements(float deltaT);

    private:
        //trzymam je
        std::vector<DynamicPhysicsComponent> Dynamic_Objects;
        std::vector<KinematicPhysicsComponent> Kinematic_Objects;
        std::vector<StaticPhysicsComponent> Static_Objects;

    };

}
