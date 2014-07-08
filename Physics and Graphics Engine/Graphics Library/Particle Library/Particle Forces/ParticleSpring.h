//============================================================================//
//                                                                            //
//  ParticleSpring.h                                                          //
//                                                                            //
//  The ParticleSpring class is an class that inherits from the ParticleForce //
//  class and provides means of adding the force of spring attached to a      //
//  particle and its emitter.                                                 //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 02/18/2014 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#ifndef __PARTICLE_SPRING__
#define __PARTICLE_SPRING__

#include <iostream>
#include "ParticleForce.h"
#include "MathLibrary.h"

namespace GraphicsEngine
{

class ParticleSpring
{

public:

//========================================================================//
//=============================Public Methods=============================//
//========================================================================//

//==============================Constructors==============================//

//The default contstructor.
ParticleSpring();

//The complete contstructor.
ParticleSpring(Vector3 anchor, float restLength, float springConstant);

//================================Setters=================================//

//This method sets the drag coefficients.
void setCoefficients(float linearCoefficient, float squaredCoefficient);

//===========================Overrided Methods============================//

//This method updates the force for a given particle and time since last
//update.
virtual void updateForce(Particle *particle, float timeSinceLastUpdate);

private:

//========================================================================//
//=========================Private Instance Data==========================//
//========================================================================//

//The float containing the linear drag coefficient.
float m_LinearCoefficient;

//The float containing the squared drag coefficient.
float m_SquaredCoefficient;
};

}

#endif
