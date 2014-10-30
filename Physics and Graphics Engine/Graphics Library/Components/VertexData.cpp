//============================================================================//
//                                                                            //
//  VertexData.cpp                                                            //
//                                                                            //
//  The VertexData class is used to store vertex data, such as position,      //
//  normals, colors, etc.                                                     //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 03/27/2014 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#include "VertexData.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

namespace GraphicsEngine
{

//============================================================================//
//===============================Public Methods===============================//
//============================================================================//

//================================Constructors================================//

//The default constructor.
VertexData::VertexData() : VertexData(Triangles, 0)
{
}

//The complete constructor.
VertexData::VertexData(VertexDataFormat dataFormat, int vertexCount)
{
    //Setting the data to be NULL.
    m_Data = NULL;
    
    //Setting the values passed in.
    m_DataFormat = dataFormat;
    m_VertexCount = vertexCount;
    
    //Setting the default values.
    m_DataCount = 0;
    m_Stride = 0;
    m_NeedsUploading = false;
    m_IsFinalized = false;
    
    //Setting the data arrays and data offsets to NULL.
    for(int dataType = 0; dataType < NumberOfDataTypes; dataType++)
    {
        m_VertexDataTypeData[dataType] = NULL;
        m_VertexDataTypeOffsets[dataType] = NULL;
    }
    
    //Setting the data type lengths.
    m_VertexDataTypeLengths[Position] = 3;
    m_VertexDataTypeLengths[Normal] = 3;
    m_VertexDataTypeLengths[TextureCoordinate] = 2;
    m_VertexDataTypeLengths[Color] = 4;
    m_VertexDataTypeLengths[Size] = 1;
    m_VertexDataTypeLengths[BoneIndices] = 2;
    m_VertexDataTypeLengths[BoneWeights] = 2;
    
    //Generating the vertex array and buffer.
    glGenVertexArrays(1, &m_VertexArrayPointer);
    glGenBuffers(1, &m_VertexBufferPointer);
}

//=================================Destructor=================================//

//The destructor.
VertexData::~VertexData()
{
    delete [] m_Data;
}

//==================================Setters===================================//

//This method sets the vertex data format.
void VertexData::setDataFormat(VertexDataFormat dataFormat)
{
    m_DataFormat = dataFormat;
}
    
//This method sets the number of vertices there are.
void VertexData::setVertexCount(int vertexCount)
{
    if(m_VertexCount == 0 && vertexCount > 0)
        m_VertexCount = vertexCount;
}

//==================================Getters===================================//

//This method gets the vertex data pointer.
GLuint VertexData::getVertexDataPointer()
{
    return m_VertexArrayPointer;
}

//This method gets the vertex data format.
VertexDataFormat VertexData::getDataFormat()
{
    return m_DataFormat;
}

//This method gets the vertex count.
int VertexData::getVertexCount()
{
    return m_VertexCount;
}

//This method gets the data count.
int VertexData::getDataCount()
{
    return m_DataCount;
}

//This method gets the data.
float * VertexData::getData()
{
    return m_Data;
}

//===============================Other Methods================================//

//This method adds data to the vertex data set.
bool VertexData::addData(VertexDataType type, float *data, float dataCount)
{
    //If the data count doesn't equal the number of vertices, return false.
    if(dataCount != m_VertexCount * m_VertexDataTypeLengths[type] ||
       m_IsFinalized)
        return false;
    
    //Making sure the data being added didn't already get added, and updating
    //the stride to reflect what was added.
    if(m_VertexDataTypeData[type] == NULL)
    {
        m_VertexDataTypeData[type] = data;
        m_Stride += m_VertexDataTypeLengths[type];
    }
    else
        return false;
    
    return true;
}

//This method updates data in the vertex data set.
bool VertexData::updateData(VertexDataType type, float *data, float dataCount)
{
    //Getting the length for the specified data type.
    int length = m_VertexDataTypeLengths[type];
    
    if(m_VertexDataTypeData[type] == NULL ||
       dataCount != m_VertexCount * length || !m_IsFinalized)
        return false;
    
    //Inserting the data into the data array.
    insertData(type, data, dataCount);
    
    return true;
}
    
bool VertexData::attachToProgram(OpenGLProgram *program)
{
    //Binding the vertex array and buffer.
    glBindVertexArray(m_VertexArrayPointer);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferPointer);
    glBufferData(GL_ARRAY_BUFFER, m_DataCount * sizeof(float),
                 m_Data, GL_DYNAMIC_DRAW);
    
    if(!(m_VertexDataTypeData[Position] == NULL))
    {
        glEnableVertexAttribArray(program->getAttributeID("position"));
        glVertexAttribPointer(program->getAttributeID("position"),
                              m_VertexDataTypeLengths[Position], GL_FLOAT,
                              GL_FALSE, m_Stride * sizeof(float),
                              BUFFER_OFFSET(m_VertexDataTypeOffsets[Position]
                                            * 4));
    }
    if(!(m_VertexDataTypeData[Normal] == NULL))
    {
        glEnableVertexAttribArray(program->getAttributeID("normal"));
        glVertexAttribPointer(program->getAttributeID("normal"),
                              m_VertexDataTypeLengths[Normal], GL_FLOAT,
                              GL_FALSE, m_Stride * sizeof(float),
                              BUFFER_OFFSET(m_VertexDataTypeOffsets[Normal]
                                            * 4));
    }
    if(!(m_VertexDataTypeData[TextureCoordinate] == NULL))
    {
        glEnableVertexAttribArray(program->getAttributeID("textureCoordinate"));
        glVertexAttribPointer(program->getAttributeID("textureCoordinate"),
                              m_VertexDataTypeLengths[TextureCoordinate],
                              GL_FLOAT, GL_FALSE, m_Stride * sizeof(float),
                              BUFFER_OFFSET(
                                            m_VertexDataTypeOffsets[TextureCoordinate]
                                            * 4));
    }
    if(!(m_VertexDataTypeData[Color] == NULL))
    {
        glEnableVertexAttribArray(program->getAttributeID("color"));
        glVertexAttribPointer(program->getAttributeID("color"),
                              m_VertexDataTypeLengths[Color],
                              GL_FLOAT, GL_FALSE, m_Stride * sizeof(float),
                              BUFFER_OFFSET(m_VertexDataTypeOffsets[Color]
                                            * 4));
    }
    if(!(m_VertexDataTypeData[Size] == NULL))
    {
        glEnableVertexAttribArray(program->getAttributeID("size"));
        glVertexAttribPointer(program->getAttributeID("size"),
                              m_VertexDataTypeLengths[Size],
                              GL_FLOAT, GL_FALSE, m_Stride * sizeof(float),
                              BUFFER_OFFSET(m_VertexDataTypeOffsets[Size]
                                            * 4));
    }
    if(!(m_VertexDataTypeData[BoneIndices] == NULL))
    {
        glEnableVertexAttribArray(program->getAttributeID("boneIndices"));
        glVertexAttribPointer(program->getAttributeID("boneIndices"),
                              m_VertexDataTypeLengths[BoneIndices],
                              GL_FLOAT, GL_FALSE, m_Stride * sizeof(float),
                              BUFFER_OFFSET(m_VertexDataTypeOffsets[BoneIndices]
                                            * 4));
    }
    if(!(m_VertexDataTypeData[BoneWeights] == NULL))
    {
        glEnableVertexAttribArray(program->getAttributeID("boneWeights"));
        glVertexAttribPointer(program->getAttributeID("boneWeights"),
                              m_VertexDataTypeLengths[BoneWeights],
                              GL_FLOAT, GL_FALSE, m_Stride * sizeof(float),
                              BUFFER_OFFSET(m_VertexDataTypeOffsets[BoneWeights]
                                            * 4));
    }
    
    //Unbinding the current vertex array.
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    return true;
}

//This method compiles the vertex data after all the data has been added.
bool VertexData::finalizeVertexData()
{
    //If the vertex count is 0 or the vertex data has already been finalized,
    //return false.
    if(m_VertexCount == 0 || m_IsFinalized)
        return false;
    
    //Computing the data count from the vertex count and the stride.
    m_DataCount = m_VertexCount * m_Stride;
    
    //Building the data array.
    return buildDataArray();
}
    
//This method uploads the data to the GPU.
void VertexData::uploadData()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferPointer);
    glBufferData(GL_ARRAY_BUFFER, m_DataCount * sizeof(float),
                 m_Data, GL_DYNAMIC_DRAW);
}
    
//============================================================================//
//==============================Private Methods===============================//
//============================================================================//

//This method builds the data array using the data added so far.
bool VertexData::buildDataArray()
{
    //Keeping track of the current array offset.
    int currentOffset = 0;
    
    //Creating the data array.
    m_Data = new float[m_Stride * m_VertexCount];
    
    //Going through each possible vertex attribute and adding an entry if
    //necessary.
    if(!(m_VertexDataTypeData[Position] == NULL))
    {
        m_VertexDataTypeOffsets[Position] = currentOffset;
        currentOffset += m_VertexDataTypeLengths[Position];
        
        //Inserting the data into the data array.
        insertData(Position, m_VertexDataTypeData[Position],
                   (float) m_VertexCount * m_VertexDataTypeLengths[Position]);
    }
    if(!(m_VertexDataTypeData[Normal] == NULL))
    {
        m_VertexDataTypeOffsets[Normal] = currentOffset;
        currentOffset += m_VertexDataTypeLengths[Normal];
        
        //Inserting the data into the data array.
        insertData(Normal, m_VertexDataTypeData[Normal],
                   (float) m_VertexCount * m_VertexDataTypeLengths[Normal]);
    }
    if(!(m_VertexDataTypeData[TextureCoordinate] == NULL))
    {
        m_VertexDataTypeOffsets[TextureCoordinate] = currentOffset;
        currentOffset += m_VertexDataTypeLengths[TextureCoordinate];
        
        //Inserting the data into the data array.
        insertData(TextureCoordinate, m_VertexDataTypeData[TextureCoordinate],
                   (float) m_VertexCount * m_VertexDataTypeLengths[TextureCoordinate]);
    }
    if(!(m_VertexDataTypeData[Color] == NULL))
    {
        m_VertexDataTypeOffsets[Color] = currentOffset;
        currentOffset += m_VertexDataTypeLengths[Color];
        
        //Inserting the data into the data array.
        insertData(Color, m_VertexDataTypeData[Color],
                   (float) m_VertexCount * m_VertexDataTypeLengths[Color]);
    }
    if(!(m_VertexDataTypeData[Size] == NULL))
    {
        m_VertexDataTypeOffsets[Size] = currentOffset;
        currentOffset += m_VertexDataTypeLengths[Size];
        
        //Inserting the data into the data array.
        insertData(Size, m_VertexDataTypeData[Size],
                   (float) m_VertexCount * m_VertexDataTypeLengths[Size]);
    }
    if(!(m_VertexDataTypeData[BoneIndices] == NULL))
    {
        m_VertexDataTypeOffsets[BoneIndices] = currentOffset;
        currentOffset += m_VertexDataTypeLengths[BoneIndices];
        
        //Inserting the data into the data array.
        insertData(BoneIndices, m_VertexDataTypeData[BoneIndices],
                   (float) m_VertexCount * m_VertexDataTypeLengths[BoneIndices]);
    }
    if(!(m_VertexDataTypeData[BoneWeights] == NULL))
    {
        m_VertexDataTypeOffsets[BoneWeights] = currentOffset;
        currentOffset += m_VertexDataTypeLengths[BoneWeights];
        
        //Inserting the data into the data array.
        insertData(BoneWeights, m_VertexDataTypeData[BoneWeights],
                   (float) m_VertexCount * m_VertexDataTypeLengths[BoneWeights]);
    }
    
    //Making sure the current offset and the stride match up.
    if(currentOffset != m_Stride)
        return false;
    
    return true;
}

//This method inserts data into the data array.
void VertexData::insertData(VertexDataType type, float *data, float dataCount)
{
    //Getting the length and offset for the specified data type.
    int length = m_VertexDataTypeLengths[type];
    int offset = m_VertexDataTypeOffsets[type];
    
    if(type == Position)
        std::cout << "Position Length: ";
    else if(type == Normal)
        std::cout << "Normal Length: ";
    else if(type == TextureCoordinate)
        std::cout << "TextureCoordinate Length: ";
    else if(type == Color)
        std::cout << "Color Length: ";
    else if(type == Size)
        std::cout << "Size Length: ";
    else if(type == BoneIndices)
        std::cout << "BoneIndices Length: ";
    else if(type == BoneWeights)
        std::cout << "BoneWeights Length: ";
    
    std::cout << length << "\tOffset: " << offset << "\n";
    std::cout << "Stride: " << m_Stride << "\n";
    
    int dataIndex = 0;
    
    //Copying the data into the array.
    for(int i = 0; i < m_DataCount; i += m_Stride)
    {
        for(int j = offset; j < offset + length; j++)
        {
            m_Data[i + j] = data[dataIndex];
            dataIndex++;
        }
    }
}

}