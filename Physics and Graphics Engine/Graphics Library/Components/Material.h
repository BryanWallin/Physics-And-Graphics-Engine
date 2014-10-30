//============================================================================//
//                                                                            //
//  Material.h                                                                //
//                                                                            //
//  The Material class is used to store material information for a given      //
//  mesh.                                                                     //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 02/08/2014 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "..\..\Math Library\MathLibrary.h"
#include "OpenGLProgram.h"
#include "Texture.h"

namespace GraphicsEngine
{
    
class Material
{
    
public:
    
    //========================================================================//
    //=============================Public Methods=============================//
    //========================================================================//
    
    //==============================Constructors==============================//
    
    //The default constructor.
    Material();
    
    //================================Setters=================================//
    
    //This method sets the material's ambient color.
    void setAmbient(Vector4 ambient);
    
    //This method sets the material's diffuse color.
    void setDiffuse(Vector4 diffuse);
    
    //This method sets the material's specular color.
    void setSpecular(Vector4 specular);
    
    //This method sets the material's emssive color.
    void setEmissive(Vector4 emissive);
    
    //This method sets the material's shininess.
    void setShininess(float shininess);
    
    //This method sets the material's program.
    void setProgram(OpenGLProgram * program);
    
    //================================Getters=================================//
    
    //This method gets the material's ambient color.
    Vector4 getAmbient();
    
    //This method gets the material's diffuse color.
    Vector4 getDiffuse();
    
    //This method gets the material's specular color.
    Vector4 getSpecular();
    
    //This method gets the material's emssive color.
    Vector4 getEmissive();
    
    //This method gets the material's shininess.
    float getShininess();
    
    //This method gets the material's program.
    OpenGLProgram * getProgram();
    
    //=============================Other Methods==============================//
    
    //This method sets a texture in a texture slot.
    bool setTexture(std::string textureName, Texture *texture);
    
    //This method gets a texture from a texture slot.
    Texture * getTexture(std::string textureName);
    
private:
    
    //========================================================================//
    //=========================Private Instance Data==========================//
    //========================================================================//
    
    //Storing the lighting colors needed by the Phong Lighting model.
    Vector4 m_Ambient, m_Diffuse, m_Specular, m_Emissive;
    
    //Storing the shininess coefficient needed by the Phong Lighting model.
    float m_Shininess;
    
    //The program associated with the material.
    OpenGLProgram *m_Program;
    
    //The unordered map that stores the textures associated with the material.
    std::unordered_map<std::string, Texture *> m_Textures;
    
    //========================================================================//
    //============================Private Methods=============================//
    //========================================================================//
    
    //This method imports a material from a .mtl file made in Blender.
    void importMaterial(std::string filePath);
};
    
}

#endif