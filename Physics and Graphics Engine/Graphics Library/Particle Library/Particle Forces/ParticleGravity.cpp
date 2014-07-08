//============================================================================//
//                                                                            //
//  ParticleGravity.cpp                                                       //
//                                                                            //
//  The ParticleGravity class is an class that inherits from the              //
//  ParticleForce class and provides means of adding the force of gravity to  //
//  a particle.                                                               //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 02/17/2014 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#include "ParticleGravity.h"

namespace GraphicsEngine
{

//========================================================================//
//=============================Public Methods=============================//
//========================================================================//

//==============================Constructors==============================//

//The default contstructor.
ParticleGravity::ParticleGravity()
{
    m_Gravity = Vector3(0, 0, 0);
}

//The complete contstructor.
ParticleGravity::ParticleGravity(const Vector3 &gravity)
{
    m_Gravity = gravity;
}

//================================Setters=================================//

//This method sets the gravity.
void ParticleGravity::setGravity(const Vector3 &gravity)
{
    m_Gravity = gravity;
}

//===========================Overrided Methods============================//

//This method updates the force for a given particle and time since last
//update.
void ParticleGravity::updateForce(Particle *particle,
                                          float timeSinceLastUpdate)
{
    particle->addForce(m_Gravity * particle->getMass());
}

}