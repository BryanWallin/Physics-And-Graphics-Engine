//============================================================================//
//                                                                            //
//  Mesh.cpp                                                                  //
//                                                                            //
//  The Mesh class is used to store attributes of a meshes, such as the       //
//  vertices, normals, and texture coordinates.                               //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 02/08/2014 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <vector>
#include "StaticMesh.h"

namespace GraphicsEngine
{

//===============================Public Methods===============================//

//--------------------------------Constructors--------------------------------//

//The name constructor.
StaticMesh::StaticMesh(std::string name) : Actor(name)
{
}

}