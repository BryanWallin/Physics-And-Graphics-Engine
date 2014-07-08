//============================================================================//
//                                                                            //
//  SkinnedMesh.h                                                             //
//                                                                            //
//  The SkinnedMesh class is used to store attributes of a skinned mesh, such //
//  as the skin of the mesh and the underlying armature (skeleton).           //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 04/01/2014 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#ifndef __SKINNED_MESH__
#define __SKINNED_MESH__

#include "StaticMesh.h"
#include "Armature.h"

namespace GraphicsEngine
{

class SkinnedMesh : public StaticMesh
{
    
public:
    
    //========================================================================//
    //=============================Public Methods=============================//
    //========================================================================//
    
    //==============================Constructors==============================//
    
    //The name constructor.
    SkinnedMesh(std::string name);
    
    //================================Setters=================================//
    
    //This method sets the armature of the skinned mesh.
    void setArmature(Armature *armature);
    
    //================================Getters=================================//
    
    //This method gets the armature of the skinned mesh.
    Armature * getArmature();
    
private:
    
    //========================================================================//
    //=========================Private Instance Data==========================//
    //========================================================================//
    
    //The armature of the skinned mesh.
    Armature *m_Armature;
    
};

}

#endif