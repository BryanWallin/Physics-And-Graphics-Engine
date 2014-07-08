//============================================================================//
//                                                                            //
//  Texture.cpp                                                               //
//                                                                            //
//  The Texture class is used to store texture information, such as the       //
//  width, height, and image data for a given texture.                        //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 02/08/2014 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#include "Texture.h"
#include <fstream>

namespace GraphicsEngine
{

//===============================Public Methods===============================//

//--------------------------------Constructors--------------------------------//

//The full file path constructor.
Texture::Texture(std::string textureFilePath)
{
    //Initializing the variables to appropriate defaults.
    m_Width = 0;
    m_Height = 0;
    m_TextureLocation = 0;
    
    //If the texture filepath isn't empty, import the texture.
    if(!textureFilePath.empty())
    {
        m_TextureFilePath = textureFilePath;
        importTexture(textureFilePath);
    }
    else
        m_TextureFilePath = "";
}


//The full file path constructor.
Texture::Texture(std::string textureFileName, std::string textureFileType)
{
    //Initializing the variables to appropriate defaults.
    m_Width = 0;
    m_Height = 0;
    m_TextureLocation = 0;
    
    std::string textureFilePath = GraphicsEngine::getFilePath(textureFileName,
                                                              textureFileType);
    
    //If the texture filepath isn't empty, import the texture.
    if(!textureFilePath.empty())
    {
        m_TextureFilePath = textureFilePath;
        importTexture(textureFilePath);
    }
    else
        m_TextureFilePath = "";
}

//----------------------------------Setters-----------------------------------//

//This method sets the texture location.
void Texture::setTextureType(TextureType textureType)
{
    m_TextureType = textureType;
}

//----------------------------------Getters-----------------------------------//

//This method gets the texture width.
int Texture::getWidth()
{
    return this->m_Width;
}

//This method gets the texture height.
int Texture::getHeight()
{
    return this->m_Height;
}

//This method sets the texture type.
TextureType Texture::getTextureType()
{
    return m_TextureType;
}

//This method returns the texture pointer.
GLuint Texture::getTexture()
{
    return m_TextureLocation;
}

//This method returns the texture pointer location.
GLuint * Texture::getTextureLocation()
{
    return &m_TextureLocation;
}

//This method gets the file path of this texture.
std::string Texture::getFilePath()
{
    return m_TextureFilePath;
}

//This method gets the texture data.
GLubyte * Texture::getData()
{
    return this->m_TextureData;
}

//==============================Private Methods===============================//

//This method imports a texture file (only .tga files).
bool Texture::importTexture(std::string textureFilePath)
{
    //Creating an ifstream file holder.
    std::ifstream file(textureFilePath, std::ios::in | std::ios::binary);
    
    //18 bytes is the header length of an uncompressed .tga file.  Create the
    //char array, then read the header into it.
    char headerBuffer[18];
    file.read(headerBuffer, 18);
    
    //Offset 2: Colormap Type.  2 is what we want.
    if(headerBuffer[2] != 2)
        return false;
    
    //Offset 12, 2 Bytes: Image Width.  It goes from low to high, so we must
    //compute it.
    m_Width = 256 * (unsigned char) headerBuffer[13] +
    (unsigned char) headerBuffer[12];
    
    //Offset 14, 2 Bytes: Image Height.  It goes from low to high, so we must
    //compute it.
    m_Height = 256 * (unsigned char) headerBuffer[15] +
    (unsigned char) headerBuffer[14];
    
    //Initializing the texture and image buffer arrays.  TGA stores 4 channels:
    //RGBA.
    m_TextureData = new GLubyte[m_Width * m_Height * 4];
    char *imageBuffer = new char[m_Width * m_Height * 4];
    
    //Reading the image data.
    file.read(imageBuffer, m_Width * m_Height * 4);
    
    //Storing the image data into the texure array.
    for(int index = 0; index < m_Width * m_Height * 4; index++)
    {
        this->m_TextureData[index] = (unsigned char) imageBuffer[index];
    }
    
    return true;
}

}