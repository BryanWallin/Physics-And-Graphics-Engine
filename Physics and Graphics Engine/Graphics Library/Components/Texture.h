//============================================================================//
//                                                                            //
//  Texture.h                                                                 //
//                                                                            //
//  The Texture class is used to store texture information, such as the       //
//  width, height, and image data for a given texture.                        //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 02/08/2014 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "..\..\Math Library\MathLibrary.h"
#include "AssetLoader.h"
#include <string>
#include <iostream>
#include <Windows.h>
#include <GL\glew.h>
#include <GL\gl.h>

namespace GraphicsEngine
{
//============================================================================//
//===========================Namespace Enumerations===========================//
//============================================================================//

//Declaring an enumeration for the texture type.
enum TextureType {DiffuseTexture = GL_TEXTURE0, NormalTexture = GL_TEXTURE1};

//Declaring an enumeration for the texture options.
enum TextureOptions {};

class Texture
{
    
public:
    
    //=============================Public Methods=============================//
    
    //The full file path constructor.
    Texture(std::string textureFilePath);
    
    //The iOS constructor.
    Texture(std::string textureFileName, std::string textureFileType);
    
    //================================Setters=================================//
    
    //This method sets the texture type.
    void setTextureType(TextureType textureType);
    
    //--------------------------------Getters---------------------------------//
    
    //This method gets the texture width.
    int getWidth();
    
    //This method gets the texture height.
    int getHeight();
    
    //This method gets the texture type.
    TextureType getTextureType();
    
    //This method returns the texture pointer.
    GLuint getTexture();
    
    //This method returns the texture pointer location.
    GLuint * getTextureLocation();
    
    //This method gets the file path of this texture.
    std::string getFilePath();
    
    //This method gets the texture data.
    GLubyte * getData();
    
private:
    
    //=========================Private Instance Data==========================//
    
    //This stores the width of the texture.
    int m_Width;
    
    //This stores the height of the texture.
    int m_Height;
    
    //Storing the texture type.
    TextureType m_TextureType;
    
    //Storing the texture location.
    GLuint m_TextureLocation;
    
    //The file path of the texture.
    std::string m_TextureFilePath;
    
    //The array of texture image data.
    GLubyte *m_TextureData;
    
    //============================Private Methods=============================//
    
    //This method imports a texture file (only .tga files).
    bool importTexture(std::string filePath);
};

}

#endif