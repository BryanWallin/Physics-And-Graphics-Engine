//============================================================================//
//                                                                            //
//  ParticleGravity.h                                                         //
//                                                                            //
//  The ParticleGravity class is an class that inherits from the              //
//  ParticleForce class and provides means of adding the force of gravity to  //
//  a particle.                                                               //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 02/17/2014 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#ifndef __PARTICLE_GRAVITY__
#define __PARTICLE_GRAVITY__

#include "MathLibrary.h"
#include "ParticleForce.h"
#include <iostream>

namespace GraphicsEngine
{

class ParticleGravity : public ParticleForce
{
    
public:
    
    //========================================================================//
    //=============================Public Methods=============================//
    //========================================================================//
    
    //==============================Constructors==============================//
    
    //The default contstructor.
    ParticleGravity();
    
    //The complete contstructor.
    ParticleGravity(const Vector3 &gravity);
    
    //================================Setters=================================//
    
    //This method sets the gravity.
    void setGravity(const Vector3 &gravity);
    
    //===========================Overrided Methods============================//
    
    //This method updates the force for a given particle and time since last
    //update.
    virtual void updateForce(Particle *particle, float timeSinceLastUpdate);
    
private:
    
    //========================================================================//
    //=========================Private Instance Data==========================//
    //========================================================================//
    
    //The vector containing the acceleration of gravity.
    Vector3 m_Gravity;
};

}

#endif
