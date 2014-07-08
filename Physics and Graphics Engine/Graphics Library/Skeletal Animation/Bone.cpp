//============================================================================//
//                                                                            //
//  Bone.h                                                                    //
//                                                                            //
//  The Bone class is used to store attributes of a single bone.  Bones are   //
//  what compose an armature.
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 03/26/2014 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#include "Bone.h"

namespace GraphicsEngine
{

//========================================================================//
//=============================Public Methods=============================//
//========================================================================//

//==============================Constructors==============================//

//The parent constructor.
Bone::Bone(std::string name, Bone *parent)
{
    m_Name = name;
    
    //Default head and tail in bone space.
    m_Head = Vector3(0, 0, 0);
    m_Tail = Vector3(0, 1, 0);
    
    //Setting the parent to be NULL by default.
    m_Parent = NULL;
    
    //If parent is NULL, then we are the root node.
    if(parent != NULL)
    {
        setParent(parent);
        m_LocalTransform.translate(Vector3(0, 1, 0));
    }
}

//================================Setters=================================//

//This method sets the parent of this bone.
void Bone::setParent(Bone *parent)
{
    if(m_Parent != parent)
    {
        m_Parent = parent;
        parent->addChild(this);
    }
}

//This method sets the armature of this bone.
void Bone::setArmature(Armature *armature)
{
    m_Armature = armature;
    armature->addBone(this);
}

//This method sets the inverse bind pose of this bone.
void Bone::setInverseBindPose(const Matrix4 inverseBindPose)
{
    m_InverseBindPose = inverseBindPose;
}

void Bone::setIndex(int index)
{
    m_Index = index;
}

//================================Getters=================================//

//This method gets the name of this bone.
std::string Bone::getName()
{
    return m_Name;
}

//This method gets the parent of this bone.
Bone * Bone::getParent()
{
    return m_Parent;
}

//This method gets the head of this bone.
Vector3 Bone::getHead()
{
    return m_Head;
}

//This method gets the tail of this bone.
Vector3 Bone::getTail()
{
    return m_Tail;
}

//This method gets the length of this bone.
float Bone::getLength()
{
    return length;
}

//This method gets the transform of this bone.
Transform & Bone::getLocalTransform()
{
    return m_LocalTransform;
}

//This method gets the global transform of this bone.
Matrix4 Bone::getGlobalTransform()
{
    return m_GlobalTransform;
}

//This method gets the inverse bind pose of this bone.
Matrix4 Bone::getInverseBindPose()
{
    return m_InverseBindPose;
}

int Bone::getIndex()
{
    return m_Index;
}

//=============================Other Methods==============================//

//This method adds a child to this bone.
void Bone::addChild(Bone *child)
{
    m_Children.push_back(child);
}

//This method creates and adds a child to this bone.
void Bone::createChild(std::string name)
{
    Bone *child = new Bone(name, this);
    addChild(child);
}

//This method sets the bind pose for this bone.
void Bone::setBindPose()
{
    
}

//This method updates the global transfom.
void Bone::update(std::vector<Matrix4> &matrixList)
{
    //Updating this bone.
    if(m_Parent == NULL)
    {
        m_GlobalTransform = m_LocalTransform.getTransform();
    }
    else
    {
        m_GlobalTransform = m_Parent->getGlobalTransform() *
        m_LocalTransform.getTransform();
    }
    
    matrixList.insert(matrixList.begin() + m_Index,
                      m_GlobalTransform * m_InverseBindPose);
    
    //Updating this child's bone.
    for(Bone *bone : m_Children)
    {
//        std::cout << "Updating " << bone->getName() << " from " << m_Name
//                  << ".\n";
        bone->update(matrixList);
    }
}

}