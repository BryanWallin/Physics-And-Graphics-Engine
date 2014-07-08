//============================================================================//
//                                                                            //
//  OpenGLProgram.h                                                           //
//                                                                            //
//  The OpenGLProgram class is used to store OpenGL program attributes and    //
//  their corresponding attribute and uniform name-ID pairs.                  //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 02/12/2014 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#ifndef _OPENGLPROGRAM_H_
#define _OPENGLPROGRAM_H_

#include <unordered_map>
#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <string>
#include <vector>
#include <OpenGLES/ES2/gl.h>
#include "AssetLoader.h"
#include "Texture.h"

namespace GraphicsEngine
{

class OpenGLProgram
{
public:

    //========================================================================//
    //=============================Public Methods=============================//
    //========================================================================//

    //==============================Constructors==============================//

    //The complete constructor.
    OpenGLProgram(std::string vertexShaderFileName = "",
                  std::string vertexShaderFileType = "",
                  std::string fragmentShaderFileName = "",
                  std::string fragmentShaderFileType = "");
    
    //================================Getters=================================//
    
    //This method gets the attribute ID corresponding to the attribute name.
    GLuint getAttributeID(std::string attributeName);
    
    //This method gets the uniform ID corresponding to the uniform name.
    GLuint getUniformID(std::string uniformName);
    
    //This method gets the texture ID corresponding to the texture name.
    GLuint getTextureID(std::string textureName);

    //This method gets the program ID.
    GLuint getProgramID();
    
    //This method gets the attribute list.
    std::vector<std::string> getAttributeList();
    
    //This method gets the uniform list.
    std::vector<std::string> getUniformList();
    
    //This method gets the texture list.
    std::vector<std::string> getTextureList();

private:

    //========================================================================//
    //=========================Private Instance Data==========================//
    //========================================================================//

    //The program ID.
    GLuint m_ProgramID;

    //The vertex shader file name without the extension.
    std::string m_VertexShaderFileName;
    
    //The vertex shader file extension type.
    std::string m_VertexShaderFileType;

    //The fragment shader file name without the extension.
    std::string m_FragmentShaderFileName;
    
    //The fragment shader file extension type.
    std::string m_FragmentShaderFileType;

    //The unordered map that stores string-attribute ID pairs.
    std::unordered_map<std::string, GLuint> m_Attributes;
    
    //The unordered map that stores string-uniform ID pairs.
    std::unordered_map<std::string, GLuint> m_Uniforms;
    
    //The unordered map that stores string-texture ID pairs.
    std::unordered_map<std::string, GLuint> m_Textures;
    
    //========================================================================//
    //============================Private Methods=============================//
    //========================================================================//
    
    //=============Program Compiling, Linking, and Error Checking=============//
    
    //This method creates the program with the specified vertex and fragment
    //shader file names and extension types.
    bool createProgram(std::string vertexShaderFileName,
                       std::string vertexShaderFileType,
                       std::string fragmentShaderFileName,
                       std::string fragmentShaderFileType);
    
    //This method compiles the shaders and returns true if successful, false
    //otherwise.
    bool compileShaders(GLuint vertexShader, GLuint fragmentShader);
    
    //This method links the program and returns true if successful, false
    //otherwise.
    bool linkProgram(GLuint program);
    
    //This method displays an error if there exists one.
    void displayError(GLuint program);
    
public:
    
    //=================Attribute, Uniform, and Texture Adding=================//
    
    //This method adds an attribute name/ID pair to the attributes list.
    void addAttribute(std::string attributeName);
    
    //This method adds a uniform name/ID pair to the uniforms list.
    void addUniform(std::string uniformName);
    
    //This method adds a uniform name/ID pair to the uniforms list.
    void addTexture(std::string textureName);
};

}

#endif