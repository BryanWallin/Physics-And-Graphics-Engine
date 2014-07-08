//
//  RigidBody.cpp
//  Hello Arrow
//
//  Created by Bryan Wallin on 4/18/14.
//  Copyright (c) 2014 Bryan Wallin. All rights reserved.
//

#include "RigidBody.h"

namespace GraphicsEngine
{

//============================================================================//
//=============================Public Methods=================================//
//============================================================================//

//================================Constructors================================//

//The default constructor.
RigidBody::RigidBody()
{
    
}

//==================================Setters===================================//

//This method sets the inertia tensor.
void RigidBody::setInertiaTensor(const Matrix3& inertiaTensor)
{
    
}

//==================================Getters===================================//

//===============================Other Methods================================//

void RigidBody::_transformInertiaTensor(Matrix3 &iitWorld,
                             const Quaternion &q,
                             const Matrix3 &iitBody,
                             const Matrix4 &rotmat)
{
    float t4 = rotmat[0][0] * iitBody[0][0] + rotmat[1][0] * iitBody[0][1] +
        rotmat[2][0] * iitBody[0][2];
    float t9 = rotmat[0][0] * iitBody[1][0] + rotmat[1][0] * iitBody[1][1] +
        rotmat[2][0] * iitBody[1][2];
    float t14 = rotmat[0][0] * iitBody[2][0] + rotmat[1][0] * iitBody[2][1] +
        rotmat[2][0] * iitBody[2][2];
    float t28 = rotmat[0][1] * iitBody[0][0] + rotmat[1][1] * iitBody[0][1] +
        rotmat[2][1] * iitBody[0][2];
    float t33 = rotmat[0][1] * iitBody[1][0] + rotmat[1][1] * iitBody[1][1] +
        rotmat[2][1] * iitBody[1][2];
    float t38 = rotmat[0][1] * iitBody[2][0] + rotmat[1][1] * iitBody[2][1] +
        rotmat[2][1] * iitBody[2][2];
    float t52 = rotmat[0][2] * iitBody[0][0] + rotmat[1][2] * iitBody[0][1] +
        rotmat[2][2] * iitBody[0][2];
    float t57 = rotmat[0][2] * iitBody[1][0] + rotmat[1][2] * iitBody[1][1] +
        rotmat[2][2] * iitBody[1][2];
    float t62 = rotmat[0][2] * iitBody[2][0] + rotmat[1][2] * iitBody[2][1] +
        rotmat[2][2] * iitBody[2][2];
    
    iitWorld[0][0] = t4 * rotmat[0][0] + t9 * rotmat[1][0] +
        t14 * rotmat[2][0];
    iitWorld[1][0] = t4 * rotmat[0][1] + t9 * rotmat[1][1] +
        t14 * rotmat[2][1];
    iitWorld[2][0] = t4 * rotmat[0][2] + t9 * rotmat[1][2] +
        t14 * rotmat[2][2];
    iitWorld[0][1] = t28 * rotmat[0][0] + t33 * rotmat[1][0] +
        t38 * rotmat[2][0];
    iitWorld[1][1] = t28 * rotmat[0][1] + t33 * rotmat[1][1] +
        t38 * rotmat[2][1];
    iitWorld[2][1] = t28 * rotmat[0][2] + t33 * rotmat[1][2] +
        t38 * rotmat[2][2];
    iitWorld[0][2] = t52 * rotmat[0][0] + t57 * rotmat[1][0] +
        t62 * rotmat[2][0];
    iitWorld[1][2] = t52 * rotmat[0][1] + t57 * rotmat[1][1] +
        t62 * rotmat[2][1];
    iitWorld[2][2] = t52 * rotmat[0][2] + t57 * rotmat[1][2] +
        t62 * rotmat[2][2];
}

void RigidBody::transformInertiaTensor(Matrix3 &iitWorld,
                            const Quaternion &q,
                            const Matrix3 &iitBody)
{
    iitWorld = Matrix3(q) * iitBody * Matrix3(q.inverse());
}

}