//============================================================================//
//                                                                            //
//  Mesh.h                                                                    //
//                                                                            //
//  The Mesh class is used to store attributes of a mesh, such as the         //
//  vertices, normals, and texture coordinates.                               //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 02/08/2014 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#ifndef _MESH_H_
#define _MESH_H_

#include "MathLibrary.h"
#include "VertexData.h"
#include "Actor.h"

namespace GraphicsEngine
{

class StaticMesh : public Actor
{

public:

    //========================================================================//
    //=============================Public Methods=============================//
    //========================================================================//
    
    //==============================Constructors==============================//
    
    //The name constructor.
    StaticMesh(std::string name);
    
};

}

#endif