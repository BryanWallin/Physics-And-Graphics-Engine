//============================================================================//
//                                                                            //
//  ParticleForce.h                                                           //
//                                                                            //
//  The ParticleForce class is an abstract class that defines how particles   //
//  and forces interact.                                                      //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 02/17/2014 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#ifndef _PARTICLEFORCE_H_
#define _PARTICLEFORCE_H_

#include "..\Particle.h"

namespace GraphicsEngine
{

class ParticleForce
{
    
public:
    
    //========================================================================//
    //=============================Public Methods=============================//
    //========================================================================//
    
    //This method updates the force for a given particle and time since last
    //update.
    virtual void updateForce(Particle *particle, float timeSinceLastUpdate) = 0;
    
};

}

#endif