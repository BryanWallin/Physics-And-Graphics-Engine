//
//  Armature.cpp
//  Hello Arrow
//
//  Created by Bryan Wallin on 3/25/14.
//  Copyright (c) 2014 Bryan Wallin. All rights reserved.
//

#include "Armature.h"

namespace GraphicsEngine
{

//============================================================================//
//===============================Public Methods===============================//
//============================================================================//

//================================Constructors================================//

//The default constructor.
Armature::Armature() : Armature("Nameless")
{
}

//The default constructor.
Armature::Armature(std::string name, std::string rootBoneName)
{
    m_Name = name;
    m_Root = new Bone(rootBoneName, NULL);
    addBone(m_Root);
}

//==================================Getters===================================//

//This method gets the root bone of this armature.
Bone * Armature::getRoot()
{
    return m_Root;
}

//This method gets the bone corresponding to the name passed in.
Bone * Armature::getBone(std::string boneName)
{
    std::unordered_map<std::string, Bone *>::iterator iterator =
    m_Bones.find(boneName);
    
    if(iterator == m_Bones.end())
        return NULL;
    else
        return iterator->second;
}

//This method gets all the bones of this armature.
std::vector<Bone *> Armature::getBones()
{
    std::vector<Bone *> bones;
    
    for(auto boneStringPair : m_Bones)
        bones.push_back(boneStringPair.second);
    
    return bones;
}

std::vector<Matrix4> & Armature::getMatrices()
{
    return  m_Matrices;
}

//===============================Other Methods================================//

//This method adds a bone to the armature.
void Armature::addBone(Bone *bone)
{
    m_Bones.insert(std::make_pair(bone->getName(), bone));
    m_Matrices.push_back(Matrix4());
}

//This method sets the bind pose for this bone.
void Armature::setBindPose()
{
    m_Root->setBindPose();
}

//This method updates the armature.
void Armature::update()
{
    m_Root->update(m_Matrices);
}

}