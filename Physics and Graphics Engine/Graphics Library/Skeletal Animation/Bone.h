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

#ifndef __BONE__
#define __BONE__

#include <iostream>
#include <vector>
#include "Transform.h"
#include "Armature.h"

namespace GraphicsEngine
{

//Forward Declarations.
class Armature;

class Bone
{

public:
    
    //========================================================================//
    //=============================Public Methods=============================//
    //========================================================================//
    
    //==============================Constructors==============================//
    
    //The parent constructor.
    Bone(std::string name, Bone *parent);
    
    //================================Setters=================================//
    
    //This method sets the parent of this bone.
    void setParent(Bone *parent);
    
    //This method sets the armature of this bone.
    void setArmature(Armature *armature);
    
    //This method sets the inverse bind pose of this bone.
    void setInverseBindPose(const Matrix4 inverseBindPose);
    
    void setIndex(int index);
    
    //================================Getters=================================//
    
    //This method gets the name of this bone.
    std::string getName();
    
    //This method gets the parent of this bone.
    Bone * getParent();
    
    //This method gets the head of this bone.
    Vector3 getHead();
    
    //This method gets the tail of this bone.
    Vector3 getTail();
    
    //This method gets the length of this bone.
    float getLength();
    
    //This method gets the local transform of this bone.
    Transform & getLocalTransform();
    
    //This method gets the global transform of this bone.
    Matrix4 getGlobalTransform();
    
    //This method gets the inverse bind pose of this bone.
    Matrix4 getInverseBindPose();
    
    int getIndex();
    
    //=============================Other Methods==============================//
    
    //This method adds a child to this bone.
    void addChild(Bone *child);
    
    //This method creates and adds a child to this bone.
    void createChild(std::string name);
    
    //This method sets the bind pose for this bone.
    void setBindPose();
    
    //This method updates the global transfom.
    void update(std::vector<Matrix4> &matrixList);
    
private:
    
    //========================================================================//
    //=========================Private Instance Data==========================//
    //========================================================================//
    
    //The name of this bone.
    std::string m_Name;
    
    //The armature this bone belongs to.
    Armature *m_Armature;
    
    //The parent of this bone.
    Bone *m_Parent;
    
    //The head of this bone.
    Vector3 m_Head;
    
    //The tail of this bone.
    Vector3 m_Tail;
    
    //The length of this bone.
    float length;
    
    //The children of this bone.
    std::vector<Bone *> m_Children;
    
    //The local transform of this bone relative to it's head.
    Transform m_LocalTransform;
    
    //The global transform (pose) of this bone.
    Matrix4 m_GlobalTransform;
    
    bool m_TransformNeedsUpdate;
    
    //The inverse transform matrix of the bind pose.
    Matrix4 m_InverseBindPose;
    
    //The index of this bone.
    int m_Index;
};

}

#endif