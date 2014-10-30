//============================================================================//
//                                                                            //
//  RigidBody.h                                                               //
//                                                                            //
//  The RigidBody class is used to store physical attributes of a rigid body, //
//  such as its world transform, its inertia tensor, its mass, linear         //
//  velocity, angular velocity, the forces applied to it, and more.           //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 04/18/2014 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#ifndef __RIGID_BODY__
#define __RIGID_BODY__

#include "..\Math Library\MathLibrary.h"
#include "..\Graphics Library\Components\Transform.h"

namespace GraphicsEngine
{
    
class RigidBody
{
public:
    
    //========================================================================//
    //===========================Public Methods===============================//
    //========================================================================//
    
    //==============================Constructors==============================//
    
    //The default constructor.
    RigidBody();
    
    //================================Setters=================================//
    
    //This method sets the mass.  The mass cannot be 0.
    void setMass(float mass);
    
    //This method sets the inverse mass.
    void setInverseMass(float inverseMass);
    
    //This method sets the linear damping.
    void setLinearDamping(float linearDamping);
    
    //This method sets the angular damping.
    void setAngularDamping(float anuglarDamping);
    
    //This method sets the inertia tensor.
    void setInertiaTensor(const Matrix3& inertiaTensor);
    
    //This method sets the inverse inertia tensor.
    void setInverseInertiaTensor(const Matrix3& inverseInertiaTensor);
    
    //================================Getters=================================//
    
    //=============================Force Methods==============================//
    
    
    
    //=============================Other Methods==============================//
    
    //This method integrates the current rigid body with the given duration.
    void integrate(float duration);
    
    void _transformInertiaTensor(Matrix3 &iitWorld,
                                 const Quaternion &q,
                                 const Matrix3 &iitBody,
                                 const Matrix4 &rotmat);
    
    void transformInertiaTensor(Matrix3 &iitWorld,
                                const Quaternion &q,
                                const Matrix3 &iitBody);
    
private:
    
    //========================================================================//
    //=========================Private Instance Data==========================//
    //========================================================================//
    
    //The inverse mass of this rigid body.
    float m_InverseMass;
    
    //The inverse inertia tensor matrix of this rigid body.
    Matrix3 m_InverseIntertiaTensor;
    
    //The linear velocity of this rigid body.
    Vector3 m_LinearVelocity;
    
    //The angular velocity of this rigid body.
    Vector3 m_AngularVelocity;
    
    //The linear damping of this rigid body.
    float m_LinearDamping;
    
    //The angular damping of this rigid body.
    float m_AngularDamping;
    
    //The force accumulated by this rigid body.
    Vector3 m_ForceAccumulated;
    
    //The torque accumulated by this rigid body.
    Vector3 m_TorqueAccumulated;
    
    //The transform of this rigid body.
    Transform m_Transform;
};

}

#endif