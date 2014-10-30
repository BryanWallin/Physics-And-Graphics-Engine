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
#include <string>
#include <fstream>

namespace GraphicsEngine
{

//This method gets the full file path of the file name and type requested.
std::string getFilePath(std::string fileName, std::string fileType);

//This method gets the full file contents of the file name and type requested.
const std::string getFileContents(std::string fileName, std::string fileType);

//This method gets the full file contents of the file at the specified file 
//path.
const std::string getFileContents(std::string filePath);

}

#endif