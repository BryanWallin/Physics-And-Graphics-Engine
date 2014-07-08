#ifndef __ACTOR__
#define __ACTOR__

//Including the necessary files.
#include "Material.h"
#include "VertexData.h"
#include "Transform.h"

namespace GraphicsEngine
{

class Actor
{
    
public:
    
    //========================================================================//
    //=============================Public Methods=============================//
    //========================================================================//
    
    //==============================Constructors==============================//
    
    //The complete constructor.
    Actor(std::string name);
    
    //The copy constructor.
    Actor(const Actor &actor);
    
    //===============================Destructor===============================//
    
    //The destructor.
    virtual ~Actor();
    
    //================================Setters=================================//
    
    //This method sets the material.
    void setMaterial(Material *material);
    
    //This method sets the vertex data of the actor.
    void setVertexData(VertexData *vertexData);
    
    //================================Getters=================================//
    
    //This method gets the name of the actor.
    std::string getName() const;
    
    //This method gets the material of the actor.
    Material * getMaterial() const;
    
    //This method gets the vertex data of the actor.
    VertexData * getVertexData() const;
    
    //This method gets the transform of the actor.
    Transform * getTransform() const;
    
protected:
    
    //========================================================================//
    //========================Protected Instance Data=========================//
    //========================================================================//
    
    //The name of the actor.
    std::string m_Name;
    
    //The material of the actor.
    Material *m_Material;
    
    //The vertex data of the actor.
    VertexData *m_VertexData;
    
    //The transform of the actor.
    Transform *m_Transform;
};

}

#endif