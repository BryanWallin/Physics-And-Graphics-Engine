//
//  Actor.cpp
//  Hello Arrow
//
//  Created by Bryan Wallin on 2/20/14.
//  Copyright (c) 2014 Bryan Wallin. All rights reserved.
//

#include "Actor.h"

namespace GraphicsEngine
{

//============================================================================//
//===============================Public Methods===============================//
//============================================================================//

//================================Constructors================================//

//The complete constructor.
Actor::Actor(std::string name)
{
    m_Name = name;
    
    m_VertexData = new VertexData();
    m_Transform = new Transform();
}

//The copy constructor.
Actor::Actor(const Actor &actor)
{
    m_Name = actor.getName();
    m_Material = actor.getMaterial();
    m_VertexData = actor.getVertexData();
    m_Transform = actor.getTransform();
}

//=================================Destructor=================================//

//The destructor.
Actor::~Actor()
{
    delete m_VertexData;
    delete m_Transform;
}

//==================================Setters===================================//

//This method sets the material.
void Actor::setMaterial(Material *material)
{
    m_Material = material;
    
    m_VertexData->attachToProgram(m_Material->getProgram());
}

//This method sets the vertex data of the actor.
void Actor::setVertexData(VertexData *vertexData)
{
    std::cout << "\n\nVertex Data Pointer: " << m_VertexData << "\n\n\n";
    
    //Deleting the old vertex data.
    delete m_VertexData;
    
    m_VertexData = vertexData;
}
    
//==================================Getters===================================//

//This method gets the name of this renderable object.
std::string Actor::getName() const
{
    return m_Name;
}

//This method gets the material of this renderable object.
Material * Actor::getMaterial() const
{
    return m_Material;
}
    
//This method gets the vertex data.
VertexData * Actor::getVertexData() const
{
    return m_VertexData;
}

//This method gets the transform of the actor.
Transform * Actor::getTransform() const
{
    return m_Transform;
}

}