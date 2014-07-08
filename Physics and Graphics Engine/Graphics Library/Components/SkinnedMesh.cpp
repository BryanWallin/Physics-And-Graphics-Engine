//
//  SkinnedMesh.cpp
//  Hello Arrow
//
//  Created by Bryan Wallin on 4/1/14.
//  Copyright (c) 2014 Bryan Wallin. All rights reserved.
//

#include "SkinnedMesh.h"

namespace GraphicsEngine
{

//========================================================================//
//=============================Public Methods=============================//
//========================================================================//

//==============================Constructors==============================//

//The name constructor.
SkinnedMesh::SkinnedMesh(std::string name) : StaticMesh(name)
{
}

//================================Setters=================================//

//This method sets the armature of the skinned mesh.
void SkinnedMesh::setArmature(Armature *armature)
{
    m_Armature = armature;
}

//================================Getters=================================//

//This method gets the armature of the skinned mesh.
Armature * SkinnedMesh::getArmature()
{
    return m_Armature;
}

}