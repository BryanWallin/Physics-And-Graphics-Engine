//============================================================================//
//                                                                            //
//  ParticleDrag.cpp                                                          //
//                                                                            //
//  The ParticleDrag class is an class that inherits from the ParticleForce   //
//  class and provides means of adding the force of drag to a particle.       //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 02/18/2014 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#include "ParticleDrag.h"

namespace GraphicsEngine
{

//========================================================================//
//=============================Public Methods=============================//
//========================================================================//

//==============================Constructors==============================//

//The default contstructor.
ParticleDrag::ParticleDrag()
{
    m_LinearCoefficient = 0;
    m_SquaredCoefficient = 0;
}

//The complete contstructor.
ParticleDrag::ParticleDrag(float linearCoefficient, float squaredCoefficient)
{
    m_LinearCoefficient = linearCoefficient;
    m_SquaredCoefficient = squaredCoefficient;
}

//================================Setters=================================//

//This method sets the drag coefficients.
void ParticleDrag::setCoefficients(float linearCoefficient,
                                   float squaredCoefficient)
{
    m_LinearCoefficient = linearCoefficient;
    m_SquaredCoefficient = squaredCoefficient;
}

//===========================Overrided Methods============================//

//This method updates the force for a given particle and time since last
//update.
void ParticleDrag::updateForce(Particle *particle, float timeSinceLastUpdate)
{
    Vector3 velocity = particle->getVelocity();
    float speed = velocity.length();
    
    float drag = m_LinearCoefficient * speed +
        m_SquaredCoefficient * speed * speed;
    
    particle->addForce(velocity.normalize() * -drag);
}

}