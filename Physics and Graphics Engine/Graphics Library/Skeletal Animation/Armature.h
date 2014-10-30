//============================================================================//
//                                                                            //
//  Armature.h                                                                //
//                                                                            //
//  The Armature class is used to store attributes of a hierarchy of bones.   //
//  These bones can be used to pose a skinned mesh.                           //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 03/26/2014 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#ifndef __ARMATURE__
#define __ARMATURE__

#include <iostream>
#include <unordered_map>
#include "Bone.h"
#include "..\..\Math Library\MathLibrary.h"

namespace GraphicsEngine
{

//Forward Declarations.
class Bone;

class Armature
{
    
public:
    
    //========================================================================//
    //=============================Public Methods=============================//
    //========================================================================//
    
    //==============================Constructors==============================//
    
    //The default constructor.
    Armature();
    
    //The name constructor.
    Armature(std::string armatureName, std::string rootBoneName = "Root");
    
    //================================Getters=================================//
    
    //This method gets the root bone of this armature.
    Bone * getRoot();
    
    //This method gets the bone corresponding to the name passed in.
    Bone * getBone(std::string boneName);
    
    //This method gets all the bones of this armature.
    std::vector<Bone *> getBones();
    
    std::vector<Matrix4> & getMatrices();
    
    //=============================Other Methods==============================//
    
    //This method adds a bone to the armature.
    void addBone(Bone *bone);
    
    //This method sets the bind pose for this bone.
    void setBindPose();
    
    //This method updates the armature.
    void update();
    
    //========================================================================//
    //=========================Private Instance Data==========================//
    //========================================================================//
    
private:
    
    //The name of this armature.
    std::string m_Name;
    
    //The root bone of this armature.
    Bone *m_Root;
    
    //The unordered map of bones.
    std::unordered_map<std::string, Bone *> m_Bones;
    
    //The vector of matrices that define the armature.
    std::vector<Matrix4> m_Matrices;
};

}

#endif