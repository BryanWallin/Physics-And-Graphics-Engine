//============================================================================//
//                                                                            //
//  Particle.cpp                                                              //
//                                                                            //
//  The Particle class stores pieces of information relating to particles.    //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 02/11/2014 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#include "Particle.h"

namespace GraphicsEngine
{

//========================================================================//
//=============================Public Methods=============================//
//========================================================================//

//==============================Constructors==============================//

//The constructor.
Particle::Particle()
{
    //Setting the default values.
    setPosition(Vector3(0, 0, 0));
    setVelocity(Vector3(0, 0, 0));
    setStartColor(Vector4(1, 1, 1, 1));
    setEndColor(Vector4(1, 1, 1, 1));
    setStartSize(1);
    setEndSize(1);
    setLifetime(1);
}
    
//The complete constructor.
Particle::Particle(Vector3 position, Vector3 velocity, Vector4 startColor,
                   Vector4 endColor, float startSize,
                   float endSize, float lifetime)
{
    //Setting the values passed in.
    setPosition(position);
    setVelocity(velocity);
    setStartColor(startColor);
    setEndColor(endColor);
    setStartSize(startSize);
    setEndSize(endSize);
    setLifetime(lifetime);
}

//================================Setters=================================//

//This method sets the mass of the particle.
void Particle::setMass(float mass)
{
    m_Mass = mass;
    
    //If the mass is set to MAXFLOAT, then it means we want it to have
    //infinite mass.
	if (mass == FLT_MAX)
        m_InvertedMass = 0;
    else if(mass > 0)
        m_InvertedMass = 1 / mass;
}
    
//This method sets the inverted mass of the particle normally.
void Particle::setInvertedMass(float invertedMass)
{
    m_InvertedMass = invertedMass;
    
    //If the inverted mass is set to 0, then it means we want it to have
    //infinite mass.
    if(invertedMass == 0)
		m_Mass = FLT_MAX;
    else if(invertedMass > 0)
        m_Mass = 1 / invertedMass;
}
    
//This method sets the position of the particle.
void Particle::setPosition(const Vector3 position)
{
    m_Position = position;
}

//This method sets the velocity of the particle.
void Particle::setVelocity(Vector3 velocity)
{
    m_Velocity = velocity;
}

//This method sets the start color of the particle.
void Particle::setStartColor(Vector4 startColor)
{
    m_StartColor = startColor;
}

//This method sets the end color of the particle.
void Particle::setEndColor(Vector4 endColor)
{
    m_EndColor = endColor;
}

//This method sets the start size of the particle.
void Particle::setStartSize(float startSize)
{
    m_StartSize = startSize;
}

//This method sets the end size of the particle.
void Particle::setEndSize(float endSize)
{
    m_EndSize = endSize;
}

//This method sets the lifetime of the particle.
void Particle::setLifetime(float lifetime)
{
    m_Lifetime = lifetime;
    m_TimeToLive = lifetime;
}

//================================Getters=================================//

//This method gets the mass of the particle.
float Particle::getMass()
{
    return m_Mass;
}
    
//This method gets the inverted mass of the particle.
float Particle::getInvertedMass()
{
    return m_InvertedMass;
}
    
//This method gets the position of the particle.
Vector3 Particle::getPosition()
{
    return m_Position;
}

//This method gets the velocity of the particle.
Vector3 Particle::getVelocity()
{
    return m_Velocity;
}

//This method gets the start color of the particle.
Vector4 Particle::getStartColor()
{
    return m_StartColor;
}

//This method gets the end color of the particle.
Vector4 Particle::getEndColor()
{
    return m_EndColor;
}

//This method gets the start size of the particle.
float Particle::getStartSize()
{
    return m_StartSize;
}

//This method gets the end size of the particle.
float Particle::getEndSize()
{
    return m_EndSize;
}

//This method gets the lifetime of the particle.
float Particle::getLifetime()
{
    return m_Lifetime;
}
    
//This method gets the time the particle has left to live.
float Particle::getTimeToLive()
{
    return m_TimeToLive;
}
    
//=============================Other Methods==============================//

//This method adds a force acting on the particle between the last update
//and the next update.
void Particle::addForce(Vector3 force)
{
    m_AccumulatedForce += force;
}
    
//This method updates the particle.
void Particle::update(float timeSinceLastUpdate)
{
    //Decrementing the time to live by the time since the last update.
    m_TimeToLive -= timeSinceLastUpdate;
    
    //Updating position.
    m_Position += m_Velocity * timeSinceLastUpdate;
    
    //Updating velocity based on the forces accumulated between the last update
    //and this one.
    Vector3 acceleration = m_AccumulatedForce * m_InvertedMass;
    
    m_Velocity += acceleration * timeSinceLastUpdate;
    
    //Clearing the accumulated force.
    clearAccumulatedForce();
}
    
    //========================================================================//
    //============================Private Methods=============================//
    //========================================================================//
    
    //This method clears the accumulated force.  It is called automatically by
    //the update method after all updating has finished.
    void Particle::clearAccumulatedForce()
    {
        m_AccumulatedForce.clear();
    }

}