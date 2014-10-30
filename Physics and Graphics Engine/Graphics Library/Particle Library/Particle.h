//============================================================================//
//                                                                            //
//  Particle.h                                                                //
//                                                                            //
//  The Particle class stores pieces of information relating to particles.    //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 02/11/2014 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "..\..\Math Library\MathLibrary.h"
#include <iostream>

namespace GraphicsEngine

{

class Particle
{

public:
    
    //========================================================================//
    //=============================Public Methods=============================//
    //========================================================================//
    
    //==============================Constructors==============================//
    
    //The default constructor.
    Particle();
    
    //The complete constructor.
    Particle(Vector3 position, Vector3 velocity, Vector4 startColor,
             Vector4 endColor, float startSize, float endSize,
             float lifetime);
    
    //================================Setters=================================//
    
    //This method sets the inverted mass of the particle by using the actual
    //mass.
    void setMass(float mass);
    
    //This method sets the inverted mass of the particle normally.
    void setInvertedMass(float invertedMass);
    
    //This method sets the position of the particle.
    void setPosition(Vector3 position);
    
    //This method sets the velocity of the particle.
    void setVelocity(Vector3 velocity);
    
    //This method sets the start color of the particle.
    void setStartColor(Vector4 startColor);
    
    //This method sets the end color of the particle.
    void setEndColor(Vector4 endColor);
    
    //This method sets the start size of the particle.
    void setStartSize(float startSize);
    
    //This method sets the end size of the particle.
    void setEndSize(float endSize);
    
    //This method sets the lifetime of the particle.
    void setLifetime(float lifetime);
    
    //================================Getters=================================//
    
    //This method gets the mass of the particle.
    float getMass();
    
    //This method gets the inverted mass of the particle.
    float getInvertedMass();
    
    //This method gets the position of the particle.
    Vector3 getPosition();
    
    //This method gets the velocity of the particle.
    Vector3 getVelocity();
    
    //This method gets the start color of the particle.
    Vector4 getStartColor();
    
    //This method gets the end color of the particle.
    Vector4 getEndColor();
    
    //This method gets the start size of the particle.
    float getStartSize();
    
    //This method gets the end size of the particle.
    float getEndSize();
    
    //This method gets the lifetime of the particle.
    float getLifetime();
    
    //This method gets the time the particle has left to live.
    float getTimeToLive();
    
    //=============================Other Methods==============================//
    
    //This method adds a force acting on the particle between the last update
    //and the next update.
    void addForce(Vector3 force);
    
    //This method updates the particle.
    void update(float timeSinceLastUpdate);

private:
    
    //========================================================================//
    //=========================Private Instance Data==========================//
    //========================================================================//
    
    //The mass of the particle.
    float m_Mass;
    
    //The inverted mass of the particle.  It is stored this way in addition to
    //the normal mass for efficient force calculations.
    float m_InvertedMass;
    
    //The position of the particle.
    Vector3 m_Position;
    
    //The velocity of the particle.
    Vector3 m_Velocity;
    
    //The accumulated force between the last update and the next one.
    Vector3 m_AccumulatedForce;
    
    //The initial color of the particle.
    Vector4 m_StartColor;
    
    //The final color of the particle.
    Vector4 m_EndColor;
    
    //The initial size of the particle (in pixels).
    float m_StartSize;
    
    //The final size of the particle (in pixels).
    float m_EndSize;
    
    //The variable that stores the particle's lifetime (in seconds).
    float m_Lifetime;
    
    //The variable that tracks the time the particle has left to live (in
    //seconds).
    float m_TimeToLive;
    
    //========================================================================//
    //============================Private Methods=============================//
    //========================================================================//
    
    //This method clears the accumulated force.  It is called automatically by
    //the update method after all updating has finished.
    void clearAccumulatedForce();
};
    
}

#endif
