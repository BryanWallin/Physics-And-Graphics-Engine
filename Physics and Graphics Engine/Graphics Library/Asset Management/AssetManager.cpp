//============================================================================//
//                                                                            //
//  AssetManager.cpp                                                          //
//                                                                            //
//  The AssetManager class is used to store assets such as meshes, materials, //
//  and much more.                                                            //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 03/27/2014 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#include "AssetManager.h"

namespace GraphicsEngine
{
//============================================================================//
//===============================Public Methods===============================//
//============================================================================//

//================================Constructors================================//

//The default constructor.
AssetManager::AssetManager()
{
    
}

//=================================Destructor=================================//

//The destructor.
AssetManager::~AssetManager()
{
    
}

//===================================Getters==================================//

StaticMesh * AssetManager::getStaticMesh(std::string name)
{
    std::unordered_map<std::string, StaticMesh *>::iterator iterator =
        m_StaticMeshes.find(name);
    
    if(iterator == m_StaticMeshes.end())
        return NULL;
    else
        return iterator->second;
}

SkinnedMesh * AssetManager::getSkinnedMesh(std::string name)
{
    std::unordered_map<std::string, SkinnedMesh *>::iterator iterator =
    m_SkinnedMeshes.find(name);
    
    if(iterator == m_SkinnedMeshes.end())
        return NULL;
    else
        return iterator->second;
}

Armature * AssetManager::getArmature(std::string name)
{
    std::unordered_map<std::string, Armature *>::iterator iterator =
    m_Armatures.find(name);
    
    if(iterator == m_Armatures.end())
        return NULL;
    else
        return iterator->second;
}

Material * AssetManager::getMaterial(std::string name)
{
    std::unordered_map<std::string, Material *>::iterator iterator =
        m_Materials.find(name);
    
    if(iterator == m_Materials.end())
        return NULL;
    else
        return iterator->second;
}

OpenGLProgram * AssetManager::getProgram(std::string name)
{
    std::unordered_map<std::string, OpenGLProgram *>::iterator iterator =
        m_Programs.find(name);
    
    if(iterator == m_Programs.end())
        return NULL;
    else
        return iterator->second;
}

//==============================Loading Methods===============================//

bool AssetManager::loadFile(std::string fileName, std::string fileExtension)
{
    if(fileExtension == ".obj")
        return loadObj(fileName, fileExtension);
    else if(fileExtension == ".dae")
        return loadCollada(fileName, fileExtension);
    
    //Otherwise, the file extension supplied is not supported.
    return false;
}

//============================================================================//
//==============================Private Methods===============================//
//============================================================================//

std::vector<float> AssetManager::getFloatArray(std::string string)
{
    std::stringstream stream = std::stringstream(string);
    
    float currentFloat;
    
    std::vector<float> floatArray;
    
    while(stream >> currentFloat)
        floatArray.push_back(currentFloat);
    
    return floatArray;
}

std::vector<int> AssetManager::getIntArray(std::string string)
{
    std::stringstream stream = std::stringstream(string);
    
    int currentInt;
    
    std::vector<int> intArray;
    
    while(stream >> currentInt)
        intArray.push_back(currentInt);
    
    return intArray;
}

std::vector<std::string> AssetManager::getStringArray(std::string string)
{
    std::stringstream stream = std::stringstream(string);
    std::vector<std::string> stringArray;
    std::string temp;
    
    while(stream >> temp)
        stringArray.push_back(temp);
    
    return stringArray;
}

void AssetManager::addBone(XMLNode *boneNode, Bone *parent, Armature *armature)
{
    std::string name = boneNode->getAttribute("name");
    std::vector<float> transform =
        getFloatArray(boneNode->getChild("matrix")->getContents());
    Bone *child = new Bone(name, parent);
    child->getLocalTransform().setTransform(transform.data());
    parent->addChild(child);
    child->setArmature(armature);
    
    std::cout << "\"" << parent->getName() << "\" is the parent of \""
              << child->getName() << "\".\n";
    
    //Making the child the new parent.
    parent = child;
    
    //Pushing the children bones onto the queue.
    std::vector<XMLNode *> children = boneNode->getChildren("node");
    for(XMLNode *child : children)
        addBone(child, parent, armature);
}
    
bool AssetManager::loadCollada(std::string fileName, std::string fileExtension)
{
    //Building an XML document from the collada file.
    XMLDocument document = XMLDocument(fileName, fileExtension);
    document.buildDocument();
    
    //Making sure the document was built properly.
    if(document.getRootNode()->getElementName() != "COLLADA")
    {
        std::cout << "Collada XML Document was built wrong!";
        return false;
    }
    
    //Using the XML document to import asset data.
    XMLNode *library_geometries =
        document.getRootNode()->getChild("library_geometries");
    
    std::vector<XMLNode *> geometries =
        library_geometries->getChildren("geometry");
    
    //Iterating through each geometry in the geometries list.
    for(XMLNode *currentGeometry : geometries)
    {
        std::string name = currentGeometry->getAttribute("name");
        
        //If the geometry node is a mesh type, import a mesh.
        if(currentGeometry->hasChild("mesh"))
        {
            XMLNode *mesh = currentGeometry->getChild("mesh");
            
            //Creating variables to hold mesh data.
            bool hasNormals = false;
            bool hasTextureCoordinates = false;
            std::string indices;
            std::string positions;
            std::string normals;
            std::string textureCoordinates;
            int vertexCount;
            int positionsOffset;
            int normalsOffset;
            int textureCoordinatesOffset;
            int positionCount;
            int normalCount;
            int textureCoordinateCount;
            
            //Creating vectors to hold the mesh data.
            std::vector<float> positionsArray;
            std::vector<float> normalsArray;
            std::vector<float> textureCoordinatesArray;
            std::vector<int> indicesArray;
            
            //Seeing if the mesh data is specified through a <polylist> node.
            if(mesh->hasChild("polylist"))
            {
                XMLNode *polylist = mesh->getChild("polylist");
                
                //Getting all the inputs.
                std::vector<XMLNode *> inputs = polylist->getChildren("input");
                
                for(XMLNode *input : inputs)
                {
                    //Case 1: The input is vertex positions.
                    if(input->getAttribute("semantic") == "VERTEX")
                    {
                        positionsOffset =
                            std::stoi(input->getAttribute("offset"));
                        
                        //Getting the positions.
                        std::string vertexSource =
                            (input->getAttribute("source")).erase(0, 1);
                        XMLNode *vertices = document.getNodeByID(vertexSource);
                        
                        std::string positionSource =
                            vertices->getChild("input")->
                            getAttribute("source").erase(0, 1);
                        
                        XMLNode *position =
                            document.getNodeByID(positionSource);
                        
                        positions =
                            position->getChild("float_array")->getContents();
                        positionCount =
                            std::stoi(position->getChild("float_array")->
                                      getAttribute("count"));
                    }
                    //Case 2: The input is normals.
                    if(input->getAttribute("semantic") == "NORMAL")
                    {
                        hasNormals = true;
                        normalsOffset =
                            std::stoi(input->getAttribute("offset"));
                        
                        //Getting the normals.
                        std::string normalSource =
                        (input->getAttribute("source")).erase(0, 1);
                        XMLNode *normal = document.getNodeByID(normalSource);
                        
                        normals =
                            normal->getChild("float_array")->getContents();
                        normalCount =
                        std::stoi(normal->getChild("float_array")->
                                  getAttribute("count"));
                    }
                    //Case 3: The input is texture coordinates.
                    if(input->getAttribute("semantic") == "TEXCOORD")
                    {
                        hasTextureCoordinates = true;
                        textureCoordinatesOffset =
                            std::stoi(input->getAttribute("offset"));
                        
                        //Getting the texture coordinates.
                        std::string textureSource =
                        (input->getAttribute("source")).erase(0, 1);
                        XMLNode *texture = document.getNodeByID(textureSource);
                        
                        textureCoordinates =
                        texture->getChild("float_array")->getContents();
                        textureCoordinateCount =
                        std::stoi(texture->getChild("float_array")->
                                  getAttribute("count"));
                    }
                }
                
                indices = polylist->getChild("p")->getContents();
                vertexCount = std::stoi(polylist->getAttribute("count")) * 3;
                
                //Creating a mesh based off of the data.
//                std::cout << "Position Count:\t" << positionCount << "\n";
//                std::cout << "Positions Offset:\t" << positionsOffset << "\n";
                
                int indexStride = 1;
                
                
                positionsArray = getFloatArray(positions);
                
                if(hasNormals)
                {
                    indexStride++;
                    normalsArray = getFloatArray(normals);
                }
                if(hasTextureCoordinates)
                {
                    indexStride++;
                    textureCoordinatesArray = getFloatArray(textureCoordinates);
                }
                
                indicesArray = getIntArray(indices);
                
                //Computing the mesh.
                float *positionsList = new float[vertexCount * 3];
                float *normalsList = new float[vertexCount * 3];
                float *textureCoordinatesList = new float[vertexCount * 2];
                
                VertexData *data = new VertexData();
                data->setVertexCount(vertexCount);
                
                std::cout << "Index Stride:\t" << indexStride << "\n";
                
                int counter = 0;
                
                for(int index = 0; index < (vertexCount * indexStride);
                    index += indexStride, counter++)
                {
                    int positionIndex = indicesArray[index + positionsOffset];
                    
                    positionsList[counter * 3 + 0] =
                        positionsArray[3 * positionIndex + 0];
                    positionsList[counter * 3 + 1] =
                        positionsArray[3 * positionIndex + 1];
                    positionsList[counter * 3 + 2] =
                        positionsArray[3 * positionIndex + 2];
                    
//                    std::cout << "(" << positionsList[counter * 3 + 0] << ", "
//                              << positionsList[counter * 3 + 1] << ", "
//                              << positionsList[counter * 3 + 2] << ")\n";
                    
                    if(hasNormals)
                    {
                        int normalIndex = indicesArray[index + normalsOffset];
                        
                        normalsList[counter * 3 + 0] =
                            normalsArray[3 * normalIndex + 0];
                        normalsList[counter * 3 + 1] =
                            normalsArray[3 * normalIndex + 1];
                        normalsList[counter * 3 + 2] =
                            normalsArray[3 * normalIndex + 2];
                    }
                    if(hasTextureCoordinates)
                    {
                        int textureCoordinateIndex =
                            indicesArray[index + textureCoordinatesOffset];
                        
                        std::cout << "Tex Coord Index: " <<
                        textureCoordinateIndex << "\n";
                        
                        textureCoordinatesList[counter * 2 + 0] =
                        textureCoordinatesArray[2 * textureCoordinateIndex + 0];
                        textureCoordinatesList[counter * 2 + 1] =
                        textureCoordinatesArray[2 * textureCoordinateIndex + 1];
                        
                        std::cout << "(" << textureCoordinatesList[counter * 2 + 0] << ", "
                              << textureCoordinatesList[counter * 2 + 1] << ")\n";
                    }
                }
                
                data->addData(Position, positionsList, vertexCount * 3);
                if(hasNormals)
                    data->addData(Normal, normalsList, vertexCount * 3);
                if(hasTextureCoordinates)
                    data->addData(TextureCoordinate, textureCoordinatesList,
                                  vertexCount * 2);
                
                bool isSkinnedMesh = false;
                
                //Determining if the mesh is a skinned mesh or not.
                XMLNode *controller;
                XMLNode *skin;
                XMLNode *library_controllers =
                    document.getRootNode()->getChild("library_controllers");
                if(library_controllers->hasChild("controller"))
                {
                    controller =
                        library_controllers->getChild("controller");
                    if(controller->hasChild("skin"))
                    {
                        skin = controller->getChild("skin");
                        if (skin->getAttribute("source").erase(0, 1) == currentGeometry->getAttribute("id"))
                        {
                            isSkinnedMesh = true;
                            std::cout << "Skinned Mesh Encountered!\n\n";
                        }
                    }
                }
                
                //Static Mesh!
                if(!isSkinnedMesh)
                {
                    //Finalizing the vertex data.
                    data->finalizeVertexData();
                    
                    StaticMesh *staticMesh = new StaticMesh(name);
                    staticMesh->setVertexData(data);

                    //Adding the mesh to the asset manager.
                    m_StaticMeshes.insert(std::make_pair(name, staticMesh));
                    std::cout << "Mesh Name: " << name << "\n";
                }
                //Skinned mesh!
                else
                {
                    XMLNode *vertex_weights = skin->getChild("vertex_weights");
                    XMLNode *inputWeight =
                        vertex_weights->getChild("input", "semantic", "WEIGHT");
                    XMLNode *inputJoint =
                        vertex_weights->getChild("input", "semantic", "JOINT");
                    
                    //Finding the vertex weight data.
                    int jointOffset =
                        std::stoi(inputJoint->getAttribute("offset"));
                    int weightOffset =
                        std::stoi(inputWeight->getAttribute("offset"));
                    int numberOfVertexWeights =
                        std::stoi(vertex_weights->getAttribute("count"));
                    
                    XMLNode *vcount = vertex_weights->getChild("vcount");
                    XMLNode *v = vertex_weights->getChild("v");
                    
                    std::string skinWeightID =
                        inputWeight->getAttribute("source").erase(0, 1);
                    std::string skinJointID =
                        inputJoint->getAttribute("source").erase(0, 1);
                    XMLNode *skinWeightSource =
                        document.getNodeByID(skinWeightID);
                    XMLNode *skinJointSource =
                        document.getNodeByID(skinJointID);
                    
                    std::vector<int> vertexCounts =
                        getIntArray(vcount->getContents());
                    std::vector<int> indices =
                        getIntArray(v->getContents());
                    std::vector<float> weights =
                        getFloatArray(skinWeightSource->
                                    getChild("float_array")->getContents());
                    
                    float *weightsList = new float[numberOfVertexWeights * 2];
                    float *jointsList = new float[numberOfVertexWeights * 2];
                    
                    int readIndex = 0;
                    int writeIndex = 0;
                    
//                    std::cout << "Number of Indices: "  << indices.size() << "\n";
                    
                    for(int currentVertex = 0; currentVertex < numberOfVertexWeights; currentVertex++)
                    {
                        int numberOfJoints = vertexCounts[currentVertex];
                        
//                        std::cout << "Vertex " << currentVertex
//                        << " has " << numberOfJoints
//                        << " bones.\n";
                        
                        //Reading the joint indices and weights.
                        for(int i = 0; i < 2; i++)
                        {
                            //Fill in the array with real data.
                            if(i < numberOfJoints)
                            {
//                                std::cout << "weightsList[" << writeIndex
//                                          << "] = "
//                                << weights[indices[readIndex + weightOffset]];
//                                std::cout << "jointsList[" << writeIndex
//                                << "] = "
//                                << jointsList[indices[readIndex + weightOffset]];
                                
                                weightsList[writeIndex] =
                                    weights[indices[readIndex + weightOffset]];
                                jointsList[writeIndex] =
                                    indices[readIndex + jointOffset];
                                
                                readIndex += 2;
                                writeIndex++;
                            }
                            //If we have less than the max number of joints,
                            //fill in default data.
                            else
                            {
                                weightsList[writeIndex] = 0;
                                jointsList[writeIndex] = 0;
                                
                                writeIndex++;
                            }
                        }
                    }
                    
                    float *vertexWeights = new float[vertexCount * 2];
                    float *vertexJoints = new float[vertexCount * 2];
                    
                    int counter = 0;
                    
                    for(int index = 0; index < (vertexCount * indexStride);
                        index += indexStride, counter++)
                    {
                        int positionIndex = indicesArray[index + positionsOffset];
                        
                        vertexWeights[counter * 2 + 0] =
                            weightsList[2 * positionIndex + 0];
                        vertexWeights[counter * 2 + 1] =
                            weightsList[2 * positionIndex + 1];
                        
                        vertexJoints[counter * 2 + 0] =
                            jointsList[2 * positionIndex + 0];
                        vertexJoints[counter * 2 + 1] =
                            jointsList[2 * positionIndex + 1];
                    }
                    
//                    std::cout << "\nVertex Weights: ";
//                    for(int index = 0; index < vertexCount * 2; index++)
//                        std::cout << vertexWeights[index] << " ";
//                    
//                    std::cout << "\nVertex Joints: ";
//                    for(int index = 0; index < vertexCount * 2; index++)
//                        std::cout << vertexJoints[index] << " ";
                    
                    data->addData(BoneWeights, vertexWeights, vertexCount * 2);
                    data->addData(BoneIndices, vertexJoints, vertexCount * 2);
                    
                    //Finalizing the vertex data.
                    data->finalizeVertexData();
                    
                    StaticMesh *staticMesh = new StaticMesh(name);
                    staticMesh->setVertexData(data);
                    
                    //Adding the mesh to the asset manager.
                    m_StaticMeshes.insert(std::make_pair(name, staticMesh));
                    std::cout << "Mesh Name: " << name << "\n";
                }
            }
            else
            {
                std::cout << "This engine currently only supports the "
                          << "<polylist> XML node for specifying mesh data!\n";
                return false;
            }
        }
        else
        {
            std::cout << "No meshes to import!";
            return false;
        }
    }
    
    //Now, importing skinned meshes.
    //Using the XML document to import asset data.
    XMLNode *library_visual_scenes =
        document.getRootNode()->getChild("library_visual_scenes");
    
    if(library_visual_scenes->hasChild("visual_scene"))
   {
        std::vector<XMLNode *> visual_scenes =
            library_visual_scenes->getChildren("visual_scene");
        
        //Looping through each visual scene.
        for (XMLNode *visual_scene : visual_scenes)
        {
            //Looping through the nodes of each visual scene.
            std::vector<XMLNode *> nodes = visual_scene->getChildren("node");
            
            for(XMLNode *node : nodes)
            {
                //Found the instance controller for the skeleton!
                if(node->hasChild("instance_controller"))
                {
                    XMLNode *instance_controller =
                        node->getChild("instance_controller");
                    XMLNode *skeleton =
                        instance_controller->getChild("skeleton");
                    
                    std::string rootBoneID =
                        skeleton->getContents().erase(0, 1);
                    
                    //Building the armature based on the hierarchy of bones.
                    XMLNode *boneNode = document.getNodeByID(rootBoneID);
                    
                    std::cout << "Root Bone ID: "
                              << boneNode->getAttribute("name") << "\n";
                    
                    std::vector<float> transform =
                    getFloatArray(boneNode->getChild("matrix")->getContents());
                    
                    //Constructing an armature.
                    Armature *armature = new Armature("Armature",
                                            boneNode->getAttribute("name"));
                    armature->getRoot()->getLocalTransform().setTransform(
                        Matrix4(transform.data()));
                    
                    //Pushing the children bones onto the queue.
                    std::vector<XMLNode *> children =
                        boneNode->getChildren("node");
                    for(XMLNode *child : children)
                        addBone(child, armature->getRoot(), armature);
                    
                    //Now, find the inverse bind pose matrices.
                    std::string skinController = instance_controller->getAttribute("url").erase(0, 1);
                    
                    XMLNode *controller = document.getNodeByID(skinController);
                    XMLNode *skin = controller->getChild("skin");
                    XMLNode *joints = skin->getChild("joints");
                    XMLNode *inputJoints = joints->getChild("input",
                                                            "semantic",
                                                            "JOINT");
                    XMLNode *inputInverse = joints->getChild("input",
                                                             "semantic",
                                                             "INV_BIND_MATRIX");
                    std::string jointSource =
                        inputJoints->getAttribute("source").erase(0, 1);
                    std::string inverseSource =
                        inputInverse->getAttribute("source").erase(0, 1);
                    
                    XMLNode *Name_array = document.getNodeByID(jointSource)->getChild("Name_array");
                    std::vector<std::string> nameArray =
                        getStringArray(Name_array->getContents());
                    
                    int index = 0;
                    //Setting the bone index values based on the name ordering.
                    for(std::string boneName : nameArray)
                    {
                        armature->getBone(boneName)->setIndex(index);
                        index++;
                    }
                    
                    XMLNode *invBindPoses = document.getNodeByID(inverseSource);
                    XMLNode *float_array =
                        invBindPoses->getChild("float_array");
                    std::vector<float> invArray =
                        getFloatArray(float_array->getContents());
                    
                    float *matrixArray = invArray.data();
                    index = 0;
                    
                    for(std::string boneName : nameArray)
                    {
                        Matrix4 mat = Matrix4(matrixArray + index * 16);
                        armature->getBone(boneName)->setInverseBindPose(mat);
                        
                        std::cout << boneName << " inverse bind matrix:\n";
                        mat.print();
                        
                        index++;
                    }
                    
                    m_Armatures.insert(std::make_pair("Armature", armature));
                        
                }
            }
        }
   }
    
    return false;
}

bool AssetManager::loadObj(std::string fileName, std::string fileExtension)
{
    //----------------------Temporary Storage Variables-----------------------//
    
    //Creating an ifstream object from the file name passed in.
    std::ifstream file(getFilePath(fileName, fileExtension));
    
    //This string holds the current file line.
    std::string fileLine;
    
    //These vectors hold lists of vectors, normals, texture coordinates, and
    //faces.
    std::vector<Vector3> vertexList;
    std::vector<Vector3> normalList;
    std::vector<Vector2> textureList;
    std::vector<Vector3> faceVertexList;
    std::vector<Vector3> faceNormalList;
    std::vector<Vector3> faceTextureList;
    
    Vector3 currentVertex;
    
    //This bool keeps track of if this mesh has normals and texture
    //coordinates or not.
    bool hasTextureCoordinates = false;
    bool hasNormals = false;
    
    //These floats are used for temporarily storing vectors and normals.
    float x, y, z;
    
    //These floats are used for temporarily storing texture coordinates.
    float u, v;
    
    //These ints store vector, normal, and texture coordinate information for a
    //given face.
    int v1, v2, v3, n1, n2, n3, t1, t2, t3;
    
    //This char is used to hold "junk" characters that don't need to be stored.
    char junk;
    
    //This holds the number of faces the mesh has.
    int faceCount = 0;
    
    //------------------------------File Reading------------------------------//
    
    //Looping through the file to fill the vector list with vector data, as
    //well as to count the number of faces.
    while(std::getline(file, fileLine))
    {
        //Creating a stringstream object from the current file line.
        std::stringstream stream(fileLine);
        
        //Checking to see if a vertex definition was encountered.
        if(fileLine.substr(0, 2) == "v ")
        {
            stream >> junk >> x >> y >> z;
            vertexList.push_back(Vector3(x, y, z));
        }
        //Checking to see if a normal definition was encountered.
        else if(fileLine.substr(0, 3) == "vn ")
        {
            //Declaring that this mesh has vertex normals.
            hasNormals = true;
            
            stream >> junk >> junk >> x >> y >> z;
            normalList.push_back(Vector3(x, y, z));
        }
        //Checking to see if a texture coordinate definition was encountered.
        else if(fileLine.substr(0, 3) == "vt ")
        {
            //Declaring that this mesh has texture coordinates.
            hasTextureCoordinates = true;
            
            stream >> junk >> junk >> u >> v;
            textureList.push_back(Vector2(u, v));
        }
        //Checking to see if a face definition was encountered.
        else if(fileLine.substr(0, 2) == "f ")
        {
            //Incrementing the face count.
            faceCount++;
            
            //If the mesh has texture coordinates and normals, adjust the
            //reading scheme accordingly.
            if(hasTextureCoordinates && hasNormals)
            {
                stream >> junk >> v1 >> junk >> t1 >> junk >> n1 >> v2 >>
                junk >> t2 >> junk >> n2 >> v3 >> junk >> t3 >> junk >> n3;
                
                faceNormalList.push_back(Vector3(n1, n2, n3));
                faceTextureList.push_back(Vector3(t1, t2, t3));
            }
            //Otherwise, if the mesh has texture coordinates but no normals,
            //adjust the reading scheme accordingly.
            else if(hasTextureCoordinates)
            {
                stream >> junk >> v1 >> junk >> t1 >> v2 >> junk >> t2 >> v3 >>
                junk >> t3;
                
                faceTextureList.push_back(Vector3(t1, t2, t3));
            }
            //Otherwise, if the mesh has normals but no texture coordinates,
            //adjust the reading scheme accordingly.
            else if(hasNormals)
            {
                stream >> junk >> v1 >> junk >> junk >> n1 >> v2 >> junk >>
                junk >> n2 >> v3 >> junk >> junk >> n3;
                
                faceNormalList.push_back(Vector3(n1, n2, n3));
            }
            //Finally, if we arrive here, the mesh only has vertex data.
            else
                stream >> junk >> v1 >> v2 >> v3;
            
            faceVertexList.push_back(Vector3(v1, v2, v3));
        }
    }
    
    //-----------------------------Mesh Computing-----------------------------//
    
    //Computing the total number of vertices.
    int vertexCount = faceCount * 3;
    
    //Creating temporary arrays to hold vertex data.
    float positions[vertexCount * 3];
    float normals[vertexCount * 3];
    float textureCoordinates[vertexCount * 2];
    
    int dataIndex = 0;
    
    for(int face = 0; face < faceCount; face++)
    {
        for(int vertex = 0; vertex < 3; vertex++)
        {
            currentVertex = vertexList[faceVertexList[face][vertex] - 1];
            
            positions[dataIndex++] = currentVertex[0];
            positions[dataIndex++] = currentVertex[1];
            positions[dataIndex++] = currentVertex[2];
        }
    }
    
    VertexData *vertexData = new VertexData();
    vertexData->setVertexCount(vertexCount);
    
    //Adding the positions to vertex data.
    vertexData->addData(Position, positions, vertexCount * 3);
    
    if(hasNormals)
    {
        int dataIndex = 0;
        
        for(int face = 0; face < faceCount; face++)
        {
            for(int vertex = 0; vertex < 3; vertex++)
            {
                currentVertex = normalList[faceNormalList[face][vertex] - 1];
                
                normals[dataIndex++] = currentVertex[0];
                normals[dataIndex++] = currentVertex[1];
                normals[dataIndex++] = currentVertex[2];
            }
        }
        
        //Adding the positions to vertex data.
        vertexData->addData(Normal, normals, vertexCount * 3);
    }
    
    if(hasTextureCoordinates)
    {
        int dataIndex = 0;
        
        for(int face = 0; face < faceCount; face++)
        {
            for(int vertex = 0; vertex < 3; vertex++)
            {
                currentVertex =
                    Vector3(textureList[faceTextureList[face][vertex] - 1]);
                
                textureCoordinates[dataIndex++] = currentVertex[0];
                textureCoordinates[dataIndex++] = currentVertex[1];
            }
        }
        
        //Adding the positions to vertex data.
        vertexData->addData(TextureCoordinate, textureCoordinates,
                              vertexCount * 2);
    }
    
    //Finalizing the vertex data.
    vertexData->finalizeVertexData();
    
    StaticMesh *staticMesh = new StaticMesh(fileName);
    staticMesh->setVertexData(vertexData);
    
    //Adding the mesh to the asset manager.
    m_StaticMeshes.insert(std::make_pair(fileName, staticMesh));
    std::cout << "Mesh Name: " << fileName << "\n";
    
    return true;
}

}