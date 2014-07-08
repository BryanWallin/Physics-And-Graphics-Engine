//============================================================================//
//                                                                            //
//  AssetLoader.h                                                             //
//                                                                            //
//  The AssetLoader class allows for easier loading of assets.                //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 02/06/2014 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#ifndef _ASSETLOADER_H_
#define _ASSETLOADER_H_

#include <iostream>
#include <OpenGLES/ES2/gl.h>

namespace GraphicsEngine
{

//This method gets the full file path of the file name and type requested.
std::string getFilePath(std::string fileName, std::string fileType);

//This method gets the file contents of the file name and type requested.
GLchar * getFileContents(std::string fileName, std::string filePath);

}

#endif