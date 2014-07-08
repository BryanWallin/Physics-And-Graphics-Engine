//============================================================================//
//                                                                            //
//  ParticleDrag.h                                                            //
//                                                                            //
//  The ParticleDrag class is an class that inherits from the ParticleForce   //
//  class and provides means of adding the force of drag to a particle.       //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 02/18/2014 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#ifndef __PARTICLE_DRAG__
#define __PARTICLE_DRAG__

#include <iostream>
#include "ParticleForce.h"

namespace GraphicsEngine
{

class ParticleDrag : public ParticleForce
{

public:
    
    //========================================================================//
    //=============================Public Methods=============================//
    //========================================================================//
    
    //==============================Constructors==============================//
    
    //The default contstructor.
    ParticleDrag();
    
    //The complete contstructor.
    ParticleDrag(float linearCoefficient, float squaredCoefficient);
    
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
