//============================================================================//
//                                                                            //
//  AssetManager.h                                                            //
//                                                                            //
//  The AssetManager class is used to store assets such as meshes, materials, //
//  and much more.                                                            //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 03/27/2014 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#ifndef __ASSET_MANAGER__
#define __ASSET_MANAGER__

#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include "StaticMesh.h"
#include "SkinnedMesh.h"
#include "Material.h"
#include "OpenGLProgram.h"
#include "XMLDocument.h"
#include "Armature.h"

namespace GraphicsEngine
{

class AssetManager
{
    
public:
    
    //========================================================================//
    //=============================Public Methods=============================//
    //========================================================================//
    
    //==============================Constructors==============================//
    
    //The default constructor.
    AssetManager();
    
    //===============================Destructor===============================//
    
    //The destructor.
    virtual ~AssetManager();
    
    //=================================Getters================================//
    
    StaticMesh * getStaticMesh(std::string name);
    
    SkinnedMesh * getSkinnedMesh(std::string name);
    
    Armature * getArmature(std::string name);
    
    Material * getMaterial(std::string name);
    
    OpenGLProgram * getProgram(std::string name);
    
    //============================Loading Methods=============================//
    
    bool loadFile(std::string fileName, std::string fileExtension);
    
private:
    
    //========================================================================//
    //=========================Private Instance Data==========================//
    //========================================================================//
    
    std::unordered_map<std::string, StaticMesh *> m_StaticMeshes;
    
    std::unordered_map<std::string, SkinnedMesh *> m_SkinnedMeshes;
    
    std::unordered_map<std::string, Armature *> m_Armatures;
    
    std::unordered_map<std::string, Material *> m_Materials;
    
    std::unordered_map<std::string, OpenGLProgram *> m_Programs;
    
    //========================================================================//
    //============================Private Methods=============================//
    //========================================================================//
    
    std::vector<float> getFloatArray(std::string string);
    
    std::vector<int> getIntArray(std::string string);
    
    std::vector<std::string> getStringArray(std::string string);
    
    void addBone(XMLNode *boneNode, Bone *parent, Armature *armature);
    
    bool loadCollada(std::string fileName, std::string fileExtension);
    
    bool loadObj(std::string fileName, std::string fileExtension);
};

}

#include <iostream>

#endif /* defined(__Hello_Arrow__AssetManager__) */
