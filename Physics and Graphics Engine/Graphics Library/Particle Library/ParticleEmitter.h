//============================================================================//
//                                                                            //
//  ParticleEmitter.h                                                         //
//                                                                            //
//  The ParticleEmitter class stores pieces of information relating to        //
//  particle systems and control how the individual particles are created,    //
//  their positions, velocities, changing colors, lifetimes, and sizes are    //
//  managed.                                                                  //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 02/11/2014 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#ifndef _PARTICLEEMITTER_H_
#define _PARTICLEEMITTER_H_

#include "..\..\Math Library\MathLibrary.h"
#include "Particle.h"
#include "Particle Forces\ParticleForce.h"
#include <vector>

namespace GraphicsEngine
{

class ParticleEmitter
{

public:
    
    //========================================================================//
    //=============================Public Methods=============================//
    //========================================================================//
    
    //==============================Constructors==============================//
    
    //The basic constructor.
    ParticleEmitter(int maxParticles);
    
    //The complete constructor.
    ParticleEmitter(float mass, float massVariance,
                    Vector3 position, Vector3 positionVariance,
                    Vector2 minAngle, Vector2 maxAngle,
                    float speed, float speedVariance,
                    Vector4 startColor, Vector4 startColorVariance,
                    Vector4 endColor, Vector4 endColorVariance,
                    float startSize, float startSizeVariance,
                    float endSize, float endSizeVariance,
                    float lifetime, float lifetimeVariance,
                    float maxParticles);
    
    //================================Setters=================================//
    
    //This method sets the mass and its variance.
    void setMassAndVariance(float mass, float massVariance);
    
    //This method sets the position and its variance.
    void setPositionAndVariance(Vector3 position, Vector3 positionVariance);
    
    //This method sets the minimum and maximum angles in sperical coordinates.
    void setMinAndMaxAngle(Vector2 minAngle, Vector2 maxAngle);
    
    //This method sets the speed and its variance.
    void setSpeedAndVariance(float speed, float speedVariance);
    
    //This method sets the start color and its variance.
    void setStartColorAndVariance(Vector4 startColor,
                                  Vector4 startColorVariance);
    
    //This method sets the end color and its variance.
    void setEndColorAndVariance(Vector4 endColor,
                                  Vector4 endColorVariance);
    
    //This method sets the start size and its variance.
    void setStartSizeAndVariance(float startSize, float startSizeVariance);

    //This method sets the end size and its variance.
    void setEndSizeAndVariance(float endSize, float endSizeVariance);
    
    //This method sets the lifetime and its variance.
    void setLifetimeAndVariance(float lifetime, float lifetimeVariance);
    
    //This method sets the emission rate of the particle system.
    void setEmissionRate(float emissionRate);
    
    //This method sets the emission time of the particle system.
    void setEmissionTime(float emissionTime);

    
    //================================Getters=================================//
    
    //This method gets the data count.
    int getDataCount();
    
    //This method gets the data.
    float * getData();
    
    //This method gets the number of active particles.
    int getNumberOfActiveParticles();
    
    //=======================Particle Emitter Controls========================//
    
    //This method pauses the particle emitter and retains its state.
    void pause();
    
    //This method stops the particle emitter and resets the state of the
    //particle emitter to its original state.
    void stop();
    
    //This method starts the particle emitter.
    void start();
    
    //This method updates the particle emitter.
    void update(float timeSinceLastUpdate, Matrix4 currentModelView);
    
    //This method resets the particle emitter.
    void reset();
    
    //=============================Other Methods==============================//
    
    //This method adds a particle force to the particle emitter.
    void addForce(ParticleForce *particleForce);
    
private:
    
    //========================================================================//
    //=========================Private Instance Data==========================//
    //========================================================================//
    
    //The mass of the particles.
    float m_Mass;
    
    //The variance of the mass of the particles.
    float m_MassVariance;
    
    //The position of the source of the particles.
    Vector3 m_Position;
    
    //The variance of the position of the source of the particles.
    Vector3 m_PositionVariance;
    
    //The minimum angle in spherical coordinates.  The x-component is the angle
    //about the xz-axis (OpenGL Space), and the y-component is the angle
    //relative to the y-axis (OpenGL Space).
    Vector2 m_MinAngle;
    
    //The maximum angle in spherical coordinates.  The x-component is the angle
    //about the xz-axis (OpenGL Space), and the y-component is the angle
    //relative to the y-axis (OpenGL Space).
    Vector2 m_MaxAngle;
    
    //The speed of the particles.
    float m_Speed;
    
    //The variance of the speed of the particless.
    float m_SpeedVariance;
    
    //The initial color of the particle.
    Vector4 m_StartColor;
    
    //The variance of the initial color of the particle.
    Vector4 m_StartColorVariance;
    
    //The final color of the particle.
    Vector4 m_EndColor;
    
    //The variance of the final color of the particle.
    Vector4 m_EndColorVariance;
    
    //The initial size in pixels of the particle.
    float m_StartSize;
    
    //The variance of the initial size in pixels of the particle.
    float m_StartSizeVariance;
    
    //The final size in pixels of the particle.
    float m_EndSize;
    
    //The variance of the final size in pixels of the particle.
    float m_EndSizeVariance;
    
    //The lifetime of the particles.
    float m_Lifetime;
    
    //The variance of the lifetime of the particles.
    float m_LifetimeVariance;
    
    //The elapsed time of the particle emitter.
    float m_ElapsedTime;
    
    //The max time the particle emitter should emit particles.
    float m_EmissionTime;
    
    //The emission rate of the particles.
    float m_EmissionRate;
    
    //The emission count of the particles.
    float m_EmissionCount;
    
    //The maximum number of particles the system is allowed to have active at
    //any given time.
    int m_MaxParticles;
    
    //The current number of particles the particle system contains.
    int m_ParticleCount;
    
    //The boolean that stores whether the particle emitter is running or not.
    bool m_IsActive;
    
    //The array of particles;
    Particle *m_Particles;
    
    //The array that contains particle data necessary for rendering.
    float *m_Data;
    
    //The forces that will act on the particles.
    std::vector<ParticleForce *> m_Forces;
    
    //The number of floats the data array is holding.
    int m_DataCount;
    
    //========================================================================//
    //============================Private Methods=============================//
    //========================================================================//
    
    //This method adds a particle to the particle system.
    bool emitParticle(Matrix4 currentModelView);
    
    //This method generates a float between minFloat and maxFloat.
    float randomFloat(float minFloat, float maxFloat);
};

}

#endif
