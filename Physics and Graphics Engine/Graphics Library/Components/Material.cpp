//============================================================================//
//                                                                            //
//  Material.cpp                                                              //
//                                                                            //
//  The Material class is used to store material information for a given      //
//  mesh.                                                                     //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 02/08/2014 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#include <iostream>
#include <fstream>
#include <sstream>
#include "Material.h"

namespace GraphicsEngine
{

//============================================================================//
//===============================Public Methods===============================//
//============================================================================//

//--------------------------------Constructors--------------------------------//

//The default constructor.
Material::Material() : m_Ambient(0, 0, 0), m_Diffuse(1, 1, 1),
    m_Specular(0, 0, 0), m_Emissive(0, 0, 0)
{
}

//----------------------------------Setters-----------------------------------//

//This method sets the material's ambient color.
void Material::setAmbient(Vector4 ambient)
{
    m_Ambient = ambient;
}

//This method sets the material's diffuse color.
void Material::setDiffuse(Vector4 diffuse)
{
    m_Diffuse = diffuse;
}

//This method sets the material's specular color.
void Material::setSpecular(Vector4 specular)
{
    m_Specular = specular;
}

//This method sets the material's emissive color.
void Material::setEmissive(Vector4 emissive)
{
    m_Emissive = emissive;
}

//This method sets the material's shininess.
void Material::setShininess(float shininess)
{
    m_Shininess = shininess;
}

//This method sets the material's program.
void Material::setProgram(OpenGLProgram *program)
{
    m_Program = program;
    
    std::vector<std::string> textures = m_Program->getTextureList();
    
    //Clearing the unordered map of textures.
    m_Textures.clear();
    
    //Adding the new textures with a default value of null.
    for(int i = 0; i < textures.size(); i++)
        m_Textures.insert(std::pair<std::string, Texture *>(textures[i], NULL));
}

//----------------------------------Getters-----------------------------------//

//This method gets the material's ambient color.
Vector4 Material::getAmbient()
{
    return m_Ambient;
}

//This method gets the material's diffuse color.
Vector4 Material::getDiffuse()
{
    return m_Diffuse;
}

//This method gets the material's specular color.
Vector4 Material::getSpecular()
{
    return m_Specular;
}

//This method sets the material's emissive color.
Vector4 Material::getEmissive()
{
    return m_Emissive;
}

//This method gets the material's shininess.
float Material::getShininess()
{
    return m_Shininess;
}

//This method gets the material's program.
OpenGLProgram * Material::getProgram()
{
    return m_Program;
}

//===============================Other Methods================================//

//This method sets a texture in a texture slot.
bool Material::setTexture(std::string textureName, Texture *texture)
{
    //Finding if the texture name exists.
    std::unordered_map<std::string, Texture *>::iterator iterator =
        m_Textures.find(textureName);

    //If we can't find the texture name, return false.
    if(iterator == m_Textures.end())
        return false;
    
    m_Textures.erase(textureName);
    m_Textures.insert(std::pair<std::string, Texture *>(textureName, texture));
    
    return true;
}

//This method gets a texture from a texture slot.
Texture * Material::getTexture(std::string textureName)
{
    //Finding if the texture name exists.
    std::unordered_map<std::string, Texture *>::iterator iterator =
    m_Textures.find(textureName);
    
    //If we can't find the texture name, return false.
    if(iterator == m_Textures.end())
        return NULL;
    else
        return iterator->second;
}

//============================================================================//
//==============================Private Methods===============================//
//============================================================================//

//This method imports a material from a .mtl file made in Blender.
void Material::importMaterial(std::string filePath)
{
    //----------------------Temporary Storage Variables-----------------------//
    
    //Creating an ifstream object from the file name passed in.
    std::ifstream file(filePath);
    
    //This string holds the current file line.
    std::string fileLine;
    
    //These floats are used for temporarily storing material properties.als.
    float r, g, b, a, shininess;
    
    //This char is used to hold "junk" characters that don't need to be stored.
    char junk;
    
    //------------------------------File Reading------------------------------//
    
    //Looping through the file to fill the vector list with vector data, as
    //well as to count the number of faces.
    while(std::getline(file, fileLine))
    {
        //Creating a stringstream object from the current file line.
        std::stringstream stream(fileLine);
        
        //Checking to see if the ambient definition was encountered.
        if(fileLine.substr(0, 3) == "Ka ")
        {
            stream >> junk >> junk >> r >> g >> b;
            m_Ambient = Vector4(r, g, b, 1.0f);
        }
        //Checking to see if the diffuse definition was encountered.
        else if(fileLine.substr(0, 3) == "Kd ")
        {
            stream >> junk >> junk >> r >> g >> b;
            m_Diffuse = Vector4(r, g, b, 1.0f);
        }
        //Checking to see if the specular definition was encountered.
        else if(fileLine.substr(0, 3) == "Ks ")
        {
            stream >> junk >> junk >> r >> g >> b;
            m_Specular = Vector4(r, g, b, 1.0f);
        }
        //Checking to see if the shininess definition was encountered.
        else if(fileLine.substr(0, 3) == "Ns ")
        {
            stream >> junk >> junk >> shininess;
            m_Shininess = shininess;
        }
        //Checking to see if the alpha definition was encountered.
        else if(fileLine.substr(0, 2) == "d ")
        stream >> junk >> a;
        
        //Setting the alpha for each material component.
        m_Ambient[3] = a;
        m_Diffuse[3] = a;
        m_Specular[3] = a;
    }
}

}