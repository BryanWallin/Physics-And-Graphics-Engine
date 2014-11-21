//============================================================================//
//                                                                            //
//  VertexData.h                                                              //
//                                                                            //
//  The VertexData class is used to store vertex data, such as position,      //
//  normals, colors, etc.                                                     //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 03/27/2014 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#ifndef __VERTEX_DATA__
#define __VERTEX_DATA__

#include <iostream>
#include <Windows.h>
#include "..\..\..\Visual Studio Projects\Physics and Graphics Engine Testbed\Common\Headers\glew.h"
#include <GL\gl.h>
#include "OpenGLProgram.h"

namespace GraphicsEngine
{
    
//============================================================================//
//===========================Namespace Enumerations===========================//
//============================================================================//

//Declaring an enumeration for the vertex data type.
enum VertexDataType {Position, Normal, Tangent, Bitangent, TextureCoordinate, 
	Color, Size, BoneIndices, BoneWeights, NumberOfDataTypes};

//Declaring an enumeration for the vertex data format.
enum VertexDataFormat {Points = GL_POINTS, Triangles = GL_TRIANGLES,
    TriangleStrip = GL_TRIANGLE_STRIP, TriangleFan = GL_TRIANGLE_FAN};

class VertexData
{
    
public:
    
    //========================================================================//
    //=============================Public Methods=============================//
    //========================================================================//
    
    //==============================Constructors==============================//
    
    //The default constructor.
    VertexData();
    
    //The complete constructor.
    VertexData(VertexDataFormat dataFormat, int vertexCount);
    
    //===============================Destructor===============================//
    
    //The destructor.
    ~VertexData();
    
    //================================Setters=================================//
    
    //This method sets the vertex data format.
    void setDataFormat(VertexDataFormat dataFormat);
    
    //This method sets the number of vertices there are.
    void setVertexCount(int vertexCount);
    
    //================================Getters=================================//
    
    //This method gets the vertex data pointer.
    GLuint getVertexDataPointer();
    
    //This method gets the vertex data format.
    VertexDataFormat getDataFormat();
    
    //This method gets the vertex count.
    int getVertexCount();
    
    //This method gets the data count.
    int getDataCount();
    
    //This method gets if the data needs uploading to the GPU or not.
    bool getNeedsUploading();
    
    //This method gets the data.
    float * getData();
    
    //=============================Other Methods==============================//
    
    //This method adds data to the vertex data set.
    bool addData(VertexDataType type, float *data, float dataCount);
    
    //This method updates data in the vertex data set.
    bool updateData(VertexDataType type, float *data, float dataCount);
    
    //This method finalizes the vertex data after all the data has been added.
    bool finalizeVertexData();
    
    //This method attaches the vertex data to a program.
    bool attachToProgram(OpenGLProgram *program);
    
    //This method uploads the data to the GPU.
    void uploadData();
    
private:
    
    //========================================================================//
    //=========================Private Instance Data==========================//
    //========================================================================//
    
    //The vertex data format.
    VertexDataFormat m_DataFormat;
    
    //The total number of vertices in the vertex data array.
    int m_VertexCount;
    
    //The total number of data entries in the vertex data array.
    int m_DataCount;
    
    //The data array.
    float *m_Data;
    
    //The array of arrays of vertex data type data that will be used to build
    //the final data array.
    float *m_VertexDataTypeData[NumberOfDataTypes];
    
    //The array of vertex data type offsets that will be used to build the
    //final data array.
    int m_VertexDataTypeOffsets[NumberOfDataTypes];
    
    //The array of vertex data type lengths that will be used to build the
    //final data array.
    int m_VertexDataTypeLengths[NumberOfDataTypes];
    
    //The stride of the data array.
    int m_Stride;
    
    //The pointer to the data array on the GPU.
    GLuint m_VertexArrayPointer;
    
    //The pointer to the data buffer on the GPU.
    GLuint m_VertexBufferPointer;
    
    //The boolean that monitors if the data needs to be uploaded to the
    //GPU.
    bool m_NeedsUploading;
    
    //The boolean that monitors if the vertex data is finalized.
    bool m_IsFinalized;
    
    //========================================================================//
    //============================Private Methods=============================//
    //========================================================================//
    
    //This method builds the data array using the data added so far.
    bool buildDataArray();
    
    //This method inserts data into the data array.
    void insertData(VertexDataType type, float *data, float dataCount);
    
};

}

#endif