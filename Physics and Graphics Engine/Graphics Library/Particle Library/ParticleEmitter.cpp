//============================================================================//
//                                                                            //
//  ParticleEmitter.cpp                                                       //
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

#include "ParticleEmitter.h"
#include <iostream>

namespace GraphicsEngine
{

//============================================================================//
//===============================Public Methods===============================//
//============================================================================//

//================================Constructors================================//

//The basic constructor.
ParticleEmitter::ParticleEmitter(int maxParticles)
{
    //Setting the default values.
    setMassAndVariance(1, 0);
    setPositionAndVariance(Vector3(0, 0, 0), Vector3(0, 0, 0));
    setMinAndMaxAngle(Vector2(0, 0), Vector2(0, 0));
    setSpeedAndVariance(1, 0);
    setStartColorAndVariance(Vector4(1, 1, 1, 1), Vector4(0, 0, 0, 0));
    setEndColorAndVariance(Vector4(1, 1, 1, 0), Vector4(0, 0, 0, 0));
    setStartSizeAndVariance(10, 0);
    setEndSizeAndVariance(5, 0);
    setLifetimeAndVariance(3, 0);
    setEmissionTime(10);
    
    m_ParticleCount = 0;
    m_MaxParticles = maxParticles;
    m_Particles = new Particle[m_MaxParticles];
    m_DataCount = m_MaxParticles * 8;
    m_Data = new float[m_DataCount];
    m_ElapsedTime = 0;
    m_EmissionCount = 0;
}

//The complete constructor.
ParticleEmitter::ParticleEmitter(float mass, float massVariance,
                                 Vector3 position, Vector3 positionVariance,
                                 Vector2 minAngle, Vector2 maxAngle,
                                 float speed, float speedVariance,
                                 Vector4 startColor, Vector4 startColorVariance,
                                 Vector4 endColor, Vector4 endColorVariance,
                                 float startSize, float startSizeVariance,
                                 float endSize, float endSizeVariance,
                                 float lifetime, float lifetimeVariance,
                                 float maxParticles)
{
    //Setting the values passed in.
    setPositionAndVariance(position, positionVariance);
    setMinAndMaxAngle(minAngle, maxAngle);
    setSpeedAndVariance(speed, speedVariance);
    setStartColorAndVariance(startColor, startColorVariance);
    setEndColorAndVariance(endColor, endColorVariance);
    setStartSizeAndVariance(startSize, startSizeVariance);
    setEndSizeAndVariance(endSize, endSizeVariance);
    setLifetimeAndVariance(lifetime, lifetimeVariance);
    
    m_ParticleCount = 0;
    m_MaxParticles = maxParticles;
    m_Particles = new Particle[m_MaxParticles];
    m_DataCount = m_MaxParticles * 8;
    m_Data = new float[m_DataCount];
    
    m_ElapsedTime = 0;
    m_EmissionCount = 0;
}

//==================================Setters===================================//

//This method sets the mass and its variance.
void ParticleEmitter::setMassAndVariance(float mass, float massVariance)
{
    m_Mass = mass;
    m_MassVariance = massVariance;
}
    
//This method sets the position and its variance.
void ParticleEmitter::setPositionAndVariance(Vector3 position,
                                             Vector3 positionVariance)
{
    m_Position = position;
    m_PositionVariance = positionVariance;
}

//This method sets the minimum and maximum angles in sperical coordinates.
void ParticleEmitter::setMinAndMaxAngle(Vector2 minAngle, Vector2 maxAngle)
{
    m_MinAngle = minAngle;
    m_MaxAngle = maxAngle;
}

//This method sets the speed and its variance.
void ParticleEmitter::setSpeedAndVariance(float speed, float speedVariance)
{
    m_Speed = speed;
    m_SpeedVariance = speedVariance;
}

//This method sets the start color and its variance.
void ParticleEmitter::setStartColorAndVariance(Vector4 startColor,
                                               Vector4 startColorVariance)
{
    m_StartColor = startColor;
    m_StartColorVariance = startColorVariance;
}

//This method sets the end color and its variance.
void ParticleEmitter::setEndColorAndVariance(Vector4 endColor,
                                             Vector4 endColorVariance)
{
    m_EndColor = endColor;
    m_EndColorVariance = endColorVariance;
}

//This method sets the start size and its variance.
void ParticleEmitter::setStartSizeAndVariance(float startSize,
                                              float startSizeVariance)
{
    m_StartSize = startSize;
    m_StartSizeVariance = startSizeVariance;
}

//This method sets the end size and its variance.
void ParticleEmitter::setEndSizeAndVariance(float endSize,
                                            float endSizeVariance)
{
    m_EndSize = endSize;
    m_EndSizeVariance = endSizeVariance;
}

//This method sets the lifetime and its variance.
void ParticleEmitter::setLifetimeAndVariance(float lifetime,
                                             float lifetimeVariance)
{
    m_Lifetime = lifetime;
    m_LifetimeVariance = lifetimeVariance;
}
    
//This method sets the emission rate of the particle system.
void ParticleEmitter::setEmissionRate(float emissionRate)
{
    m_EmissionRate = emissionRate;
}
    
//This method sets the emission time of the particle system.
void ParticleEmitter::setEmissionTime(float emissionTime)
{
    m_EmissionTime = emissionTime;
}
    
//==================================Getters===================================//

//This method gets the data count.
int ParticleEmitter::getDataCount()
{
    return m_DataCount;
}

//This method gets the data.
float * ParticleEmitter::getData()
{
    return m_Data;
}

//This method gets the number of active particles.
int ParticleEmitter::getNumberOfActiveParticles()
{
    return m_ParticleCount;
}

//=========================Particle Emitter Controls==========================//

//This method pauses the particle emitter and retains its state.
void ParticleEmitter::pause()
{
    m_IsActive = false;
}

//This method stops the particle emitter and resets the state of the
//particle emitter to its original state.
void ParticleEmitter::stop()
{
    reset();
    m_IsActive = false;
}

//This method starts the particle emitter.
void ParticleEmitter::start()
{
    m_IsActive = true;
}

//This method updates the particle emitter.
void ParticleEmitter::update(float timeSinceLastUpdate,
                             Matrix4 currentModelView)
{
    //Step 1: Emit particles according to the emission rate.
    m_EmissionCount += m_EmissionRate * timeSinceLastUpdate;
    
    //Updating the elapsed time.
    m_ElapsedTime += timeSinceLastUpdate;
    
    //Emit particles if the elapsed time is under the emit time, or if the emit
    //time equals 0 (emit infinitely).
    if(m_ElapsedTime < m_EmissionTime || m_EmissionTime == 0)
    {
        while(m_ParticleCount <= m_MaxParticles && m_EmissionCount >= 1)
        {
            emitParticle(currentModelView);
            m_EmissionCount--;
        }
    }
    
    //Step 2: Update all particles that are currently active, and replace the
    //particles that are dead with ones that are not.  This is to achieve tight
    //array packing for efficiency.
    int particleIndex = 0;
    
    while(particleIndex < m_ParticleCount)
    {
        //Getting the current particle.
        Particle *currentParticle = &m_Particles[particleIndex];
        
        //If the current particle is still alive, then update it.
        if(currentParticle->getTimeToLive() > 0)
        {
            //Adding forces to the current particle.
            for(int i = 0; i < m_Forces.size(); i++)
                m_Forces[i]->updateForce(currentParticle, timeSinceLastUpdate);
            
            //Updating the particle.
            currentParticle->update(timeSinceLastUpdate);
            
            //Using linear interpolation to solve for the color and size.
            float percentDead = 1 - currentParticle->getTimeToLive() /
                currentParticle->getLifetime();
            Vector4 color = lerp(currentParticle->getStartColor(),
                                 currentParticle->getEndColor(), percentDead);
            float size = lerp(currentParticle->getStartSize(),
                              currentParticle->getEndSize(), percentDead);
            Vector3 position = currentParticle->getPosition();
            
            m_Data[particleIndex * 8] = position.x;
            m_Data[particleIndex * 8 + 1] = position.y;
            m_Data[particleIndex * 8 + 2] = position.z;
            m_Data[particleIndex * 8 + 3] = color.x;
            m_Data[particleIndex * 8 + 4] = color.y;
            m_Data[particleIndex * 8 + 5] = color.z;
            m_Data[particleIndex * 8 + 6] = color.w;
            m_Data[particleIndex * 8 + 7] = size;
            
            particleIndex++;
        }
        //Otherwise, swap the dead particle with one from the end of the list.
        else
        {
            //If we aren't at the last alive particle in the list, then swap
            //the dead particle with an alive one from the end.
            if(particleIndex != m_ParticleCount - 1)
                m_Particles[particleIndex] = m_Particles[m_ParticleCount - 1];
            
            m_ParticleCount--;
        }
    }
}

//This method resets the particle emitter.
void ParticleEmitter::reset()
{
    
}

//===============================Other Methods================================//

//This method adds a particle force to the particle emitter.
void ParticleEmitter::addForce(ParticleForce *particleForce)
{
    m_Forces.push_back(particleForce);
}

//============================================================================//
//==============================Private Methods===============================//
//============================================================================//

//This method adds a particle to the particle system.
bool ParticleEmitter::emitParticle(Matrix4 currentModelView)
{
    //std::cout << "emit particle\n";
    if(m_ParticleCount >= m_MaxParticles)
        return false;
    
    Particle *currentParticle = &m_Particles[m_ParticleCount];
    
    //Creating random particle attributes within the specified ranges.
    //Mass.
    float mass = randomFloat(m_Mass - m_MassVariance, m_Mass - m_MassVariance);
    currentParticle->setMass(mass);
    
    //Position.
    float positionX = randomFloat(m_Position.x - m_PositionVariance.x,
                                  m_Position.x + m_PositionVariance.x);
    float positionY = randomFloat(m_Position.y - m_PositionVariance.y,
                                  m_Position.y + m_PositionVariance.y);
    float positionZ = randomFloat(m_Position.z - m_PositionVariance.z,
                                  m_Position.z + m_PositionVariance.z);
    Vector4 position = currentModelView * Vector4(positionX, positionY,
                                                  positionZ, 1);
    currentParticle->setPosition(Vector3(position));
    
    //Velocity.
    float speed = randomFloat(m_Speed - m_SpeedVariance,
                              m_Speed + m_SpeedVariance);
    float theta = degreesToRadians(randomFloat(m_MinAngle.x, m_MaxAngle.x));
    float phi = degreesToRadians(randomFloat(m_MinAngle.y, m_MaxAngle.y));
    float velocityX = speed * sinf(phi) * cosf(theta);
    float velocityY = speed * cosf(phi);
    float velocityZ = speed * sinf(phi) * sinf(theta);
    
    Vector4 velocity = currentModelView * Vector4(velocityX, velocityY,
                                                  velocityZ, 0);
    
    currentParticle->setVelocity(Vector3(velocity));
    
    //Color.
    float startColorX = randomFloat(m_StartColor.x - m_StartColorVariance.x,
                                    m_StartColor.x + m_StartColorVariance.x);
    float startColorY = randomFloat(m_StartColor.y - m_StartColorVariance.y,
                                    m_StartColor.y + m_StartColorVariance.y);
    float startColorZ = randomFloat(m_StartColor.z - m_StartColorVariance.z,
                                    m_StartColor.z + m_StartColorVariance.z);
    float startColorW = randomFloat(m_StartColor.w - m_StartColorVariance.w,
                                    m_StartColor.w + m_StartColorVariance.w);
    float endColorX = randomFloat(m_EndColor.x - m_EndColorVariance.x,
                                  m_EndColor.x + m_EndColorVariance.x);
    float endColorY = randomFloat(m_EndColor.y - m_EndColorVariance.y,
                                  m_EndColor.y + m_EndColorVariance.y);
    float endColorZ = randomFloat(m_EndColor.z - m_EndColorVariance.z,
                                  m_EndColor.z + m_EndColorVariance.z);
    float endColorW = randomFloat(m_EndColor.w - m_EndColorVariance.w,
                                  m_EndColor.w + m_EndColorVariance.w);
    currentParticle->setStartColor(Vector4(startColorX, startColorY,
                                           startColorZ, startColorW));
    currentParticle->setEndColor(Vector4(endColorX, endColorY, endColorZ,
                                         endColorW));
    
    //Size.
    float startSize = randomFloat(m_StartSize - m_StartSizeVariance,
                                  m_StartSize + m_StartSizeVariance);
    float endSize = randomFloat(m_EndSize - m_EndSizeVariance,
                                  m_EndSize + m_EndSizeVariance);
    
    currentParticle->setStartSize(startSize);
    currentParticle->setEndSize(endSize);
    
    //Lifetime.
    currentParticle->setLifetime(randomFloat(m_Lifetime - m_LifetimeVariance, m_Lifetime + m_LifetimeVariance));
    
    m_ParticleCount++;
    
    //std::cout << "particle added\n";
    
    return true;
}
    
//This method generates a float between minFloat and maxFloat.
float ParticleEmitter::randomFloat(float minFloat, float maxFloat)
{
    return ((float) rand() / (float) RAND_MAX) * (maxFloat - minFloat)
    + minFloat;
}

}