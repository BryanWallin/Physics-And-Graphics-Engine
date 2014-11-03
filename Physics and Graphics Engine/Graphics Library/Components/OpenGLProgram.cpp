//============================================================================//
//                                                                            //
//  OpenGLProgram.cpp                                                         //
//                                                                            //
//  The OpenGLProgram class is used to store OpenGL program attributes and    //
//  their corresponding attribute and uniform name-ID pairs.                  //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 02/12/2014 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#include "OpenGLProgram.h"

namespace GraphicsEngine
{

//============================================================================//
//===============================Public Methods===============================//
//============================================================================//

//================================Constructors================================//

//The complete constructor.
OpenGLProgram::OpenGLProgram(std::string vertexShaderFileName,
                             std::string vertexShaderFileType,
                             std::string fragmentShaderFileName,
                             std::string fragmentShaderFileType)
{
    //Creating the program.
    if(!vertexShaderFileName.empty())
        this->createProgram(
			getFilePath(vertexShaderFileName, vertexShaderFileType),
			getFilePath(fragmentShaderFileName, fragmentShaderFileType));
}

//The standard constructor.
OpenGLProgram::OpenGLProgram(std::string vertexShaderFilePath,
	std::string fragmentShaderFilePath)
{
	//Creating the program.
	if (!vertexShaderFilePath.empty() && !fragmentShaderFilePath.empty())
		this->createProgram(vertexShaderFilePath, fragmentShaderFilePath);
}

//The vertex, geometry, and fragment shader constructor.
OpenGLProgram::OpenGLProgram(std::string vertexShaderFilePath,
	std::string geometryShaderFilePath, std::string fragmentShaderFilePath)
{
	//Creating the program.
	if (!vertexShaderFilePath.empty() && !geometryShaderFilePath.empty() &&
		!fragmentShaderFilePath.empty())
		this->createProgram(vertexShaderFilePath, geometryShaderFilePath,
			fragmentShaderFilePath);
}
    
//==================================Getters===================================//

//This method gets the attribute ID corresponding to the attribute name.
GLuint OpenGLProgram::getAttributeID(std::string attributeName)
{
    std::unordered_map<std::string, GLuint>::iterator it =
        m_Attributes.find(attributeName);
    
    if(it != m_Attributes.end())
        return it->second;
    else
        return NULL;
}

//This method gets the uniform ID corresponding to the uniform name.
GLuint OpenGLProgram::getUniformID(std::string uniformName)
{
    std::unordered_map<std::string, GLuint>::iterator it = 
        m_Uniforms.find(uniformName);

    if(it != m_Uniforms.end())
        return it->second;
    else
        return NULL;
}
    
//This method gets the texture ID corresponding to the texture name.
GLuint OpenGLProgram::getTextureID(std::string textureName)
{
    std::unordered_map<std::string, GLuint>::iterator it =
    m_Textures.find(textureName);
    
    if(it != m_Textures.end())
        return it->second;
    else
        return NULL;
}

//This method gets the program ID.
GLuint OpenGLProgram::getProgramID()
{
    return m_ProgramID;
}

//This method gets the attribute list.
std::vector<std::string> OpenGLProgram::getAttributeList()
{
    std::vector<std::string> attributeList = std::vector<std::string>();
    
    for(auto &i : m_Attributes)
        attributeList.push_back(i.first);
    
    return attributeList;
}

//This method gets the uniform list.
std::vector<std::string> OpenGLProgram::getUniformList()
{
    std::vector<std::string> uniformList = std::vector<std::string>();
    
    for(auto &i : m_Uniforms)
        uniformList.push_back(i.first);
    
    return uniformList;
}

//This method gets the texture list.
std::vector<std::string> OpenGLProgram::getTextureList()
{
    std::vector<std::string> textureList = std::vector<std::string>();
    
    for(auto &i : m_Textures)
        textureList.push_back(i.first);
    
    return textureList;
}

//===================Attribute, Uniform, and Texture Adding===================//

//This method adds an attribute name/ID pair to the attributes list.
void OpenGLProgram::addAttribute(std::string attributeName)
{
	m_Attributes.insert(std::make_pair(attributeName,
		glGetAttribLocation(m_ProgramID, attributeName.c_str())));
}

//This method adds a uniform name/ID pair to the uniforms list.
void OpenGLProgram::addUniform(std::string uniformName)
{
	m_Uniforms.insert(std::make_pair(uniformName,
		glGetUniformLocation(m_ProgramID, uniformName.c_str())));

	if (glGetUniformLocation(m_ProgramID, uniformName.c_str()) < 0)
		std::cout << "Uniform Location Error: " << uniformName << ", "
		<< glGetUniformLocation(m_ProgramID, uniformName.c_str())
		<< "\n";
}

//This method adds a uniform name/ID pair to the uniforms list.
void OpenGLProgram::addTexture(std::string textureName)
{
	m_Textures.insert(std::make_pair(textureName,
		glGetUniformLocation(m_ProgramID, textureName.c_str())));
}

//============================================================================//
//==============================Private Methods===============================//
//============================================================================//

//===============Program Compiling, Linking, and Error Checking===============//

//This method creates the program with the specified vertex and fragment
//shader file paths.
bool OpenGLProgram::createProgram(std::string vertexShaderFilePath,
	std::string fragmentShaderFilePath)
{
    //Clearing the attributes, uniforms, and textures maps.
    m_Uniforms.clear();
    m_Attributes.clear();
    m_Textures.clear();
    
    //Creating the program.
    m_ProgramID = glCreateProgram();
    
    //Creating vertex and fragment shader IDs.
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    //Getting the vertex and fragment shader contents.
    std::string vertexShaderContents =
		getFileContents(vertexShaderFilePath);
	std::string fragmentShaderContents =
		getFileContents(fragmentShaderFilePath);

	const GLchar * vertexShaderContentsPointer = 
		vertexShaderContents.c_str();
	const GLchar * fragmentShaderContentsPointer = 
		fragmentShaderContents.c_str();
    
    //Passing the shader contents to the shader IDs.
	glShaderSource(vertexShader, 1, &vertexShaderContentsPointer, NULL);
	glShaderSource(fragmentShader, 1, &fragmentShaderContentsPointer, NULL);

    //Compiling the program.
    if(!compileShader(vertexShader) || !compileShader(fragmentShader))
        return false;
    
    //Attaching the vertex and fragment shaders to the program.
    glAttachShader(m_ProgramID, vertexShader);
    glAttachShader(m_ProgramID, fragmentShader);
    
    //Linking the program.
    if(!linkProgram(m_ProgramID))
        return false;
    
    //----------File Reading for Attributes, Uniforms, and Textures-----------//
    
    //Creating an ifstream object from the file name passed in.
    std::ifstream vertexShaderFile(vertexShaderFilePath);
	std::ifstream fragmentShaderFile(fragmentShaderFilePath);
    
    //This string holds the current file line.
    std::string fileLine;
    std::string attribute, uniform, texture;
    
    //-----------------------Vertex Shader File Reading-----------------------//
    
    //Looping through the vertex shader file to find attribute and uniform
    //definitions.
    while(std::getline(vertexShaderFile, fileLine))
    {
        //Checking to see if an attribute definition was encountered.
        if(fileLine.substr(0, 10) == "attribute ")
        {
            attribute = fileLine.substr(fileLine.find_last_of(' ') + 1);
            attribute.pop_back();
            
            //Adding the attribute.
            addAttribute(attribute);
        }
        //Checking to see if a uniform definition was encountered.
        else if(fileLine.substr(0, 8) == "uniform ")
        {
            uniform = fileLine.substr(fileLine.find_last_of(' ') + 1);
            uniform.pop_back();
            
            if(uniform.find('[') == std::string::npos)
            {
                //Adding the uniform.
                addUniform(uniform);
            }
        }
    }
    
    //----------------------Fragment Shader File Reading----------------------//
    
    //Looping through the fragment shader file to find texture and uniform
    //definitions.
    while(std::getline(fragmentShaderFile, fileLine))
    {
        //Checking to see if a texture definition was encountered.
        if(fileLine.substr(0, 18) == "uniform sampler2D ")
        {
            texture = fileLine.substr(fileLine.find_last_of(' ') + 1);
            texture.pop_back();
            
            //Adding the texture.
            addTexture(texture);
        }
        //Checking to see if a uniform definition was encountered.
        else if(fileLine.substr(0, 8) == "uniform ")
        {
            uniform = fileLine.substr(fileLine.find_last_of(' ') + 1);
            uniform.pop_back();
            
            //Adding the uniform.
            addUniform(uniform);
        }
    }
    
    return true;
}

//This method creates the program with the specified vertex, geometry, and 
//fragment shader file paths.
bool OpenGLProgram::createProgram(std::string vertexShaderFilePath,
	std::string geometryShaderFilePath, std::string fragmentShaderFilePath)
{
	//Clearing the attributes, uniforms, and textures maps.
	m_Uniforms.clear();
	m_Attributes.clear();
	m_Textures.clear();

	//Creating the program.
	m_ProgramID = glCreateProgram();

	//Creating vertex and fragment shader IDs.
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//Getting the vertex and fragment shader contents.
	std::string vertexShaderContents =
		getFileContents(vertexShaderFilePath);
	std::string geometryShaderContents =
		getFileContents(geometryShaderFilePath);
	std::string fragmentShaderContents =
		getFileContents(fragmentShaderFilePath);

	const GLchar * vertexShaderContentsPointer =
		vertexShaderContents.c_str();
	const GLchar * geometryShaderContentsPointer =
		geometryShaderContents.c_str();
	const GLchar * fragmentShaderContentsPointer =
		fragmentShaderContents.c_str();

	//Passing the shader contents to the shader IDs.
	glShaderSource(vertexShader, 1, &vertexShaderContentsPointer, NULL);
	glShaderSource(geometryShader, 1, &geometryShaderContentsPointer, NULL);
	glShaderSource(fragmentShader, 1, &fragmentShaderContentsPointer, NULL);

	//Compiling the program.
	if (!compileShader(vertexShader) || !compileShader(geometryShader) ||
		!compileShader(fragmentShader))
		return false;

	//Attaching the vertex and fragment shaders to the program.
	glAttachShader(m_ProgramID, vertexShader);
	glAttachShader(m_ProgramID, geometryShader);
	glAttachShader(m_ProgramID, fragmentShader);

	//Linking the program.
	if (!linkProgram(m_ProgramID))
		return false;

	//----------File Reading for Attributes, Uniforms, and Textures-----------//

	//Creating an ifstream object from the file name passed in.
	std::ifstream vertexShaderFile(vertexShaderFilePath);
	std::ifstream fragmentShaderFile(fragmentShaderFilePath);

	//This string holds the current file line.
	std::string fileLine;
	std::string attribute, uniform, texture;

	//-----------------------Vertex Shader File Reading-----------------------//

	//Looping through the vertex shader file to find attribute and uniform
	//definitions.
	while (std::getline(vertexShaderFile, fileLine))
	{
		//Checking to see if an attribute definition was encountered.
		if (fileLine.substr(0, 10) == "attribute ")
		{
			attribute = fileLine.substr(fileLine.find_last_of(' ') + 1);
			attribute.pop_back();

			//Adding the attribute.
			addAttribute(attribute);
		}
		//Checking to see if a uniform definition was encountered.
		else if (fileLine.substr(0, 8) == "uniform ")
		{
			uniform = fileLine.substr(fileLine.find_last_of(' ') + 1);
			uniform.pop_back();

			if (uniform.find('[') == std::string::npos)
			{
				//Adding the uniform.
				addUniform(uniform);
			}
		}
	}

	//----------------------Fragment Shader File Reading----------------------//

	//Looping through the fragment shader file to find texture and uniform
	//definitions.
	while (std::getline(fragmentShaderFile, fileLine))
	{
		//Checking to see if a texture definition was encountered.
		if (fileLine.substr(0, 18) == "uniform sampler2D ")
		{
			texture = fileLine.substr(fileLine.find_last_of(' ') + 1);
			texture.pop_back();

			//Adding the texture.
			addTexture(texture);
		}
		//Checking to see if a uniform definition was encountered.
		else if (fileLine.substr(0, 8) == "uniform ")
		{
			uniform = fileLine.substr(fileLine.find_last_of(' ') + 1);
			uniform.pop_back();

			//Adding the uniform.
			addUniform(uniform);
		}
	}

	return true;
}
    
//This method compiles a shader and returns true if successful, false
//otherwise.
bool OpenGLProgram::compileShader(GLuint shaderPointer)
{
    //Compiling the shader.
	glCompileShader(shaderPointer);
    
    //Verifying the shaders compiled correctly.
    GLint shaderStatus;
    
	glGetShaderiv(shaderPointer, GL_COMPILE_STATUS, &shaderStatus);
	if (shaderStatus == 0)
    {
		std::cout << "Shader compiler error: " << shaderStatus
                  << "\n";
        int maxLength = 1000;
        char *info = new char[1000];
        int length;
		glGetShaderInfoLog(shaderPointer, maxLength, &length, info);
        std::cout << info << "\n";
        displayError(m_ProgramID);
        return false;
    }
    
    return true;
}

//This method links the program and returns true if successful, false
//otherwise.
bool OpenGLProgram::linkProgram(GLuint program)
{
    //Linking the program.
    glLinkProgram(program);
    
    //Verifying the program linked correctly.
    GLint linkStatus;
    
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
    if(linkStatus == 0)
    {
        std::cout << "Program failed to link: " << linkStatus << "\n";
        displayError(m_ProgramID);
        return false;
    }
    
    return true;
}

//This method displays an error if there exists one.
void OpenGLProgram::displayError(GLuint program)
{
    //Defining length and string variables.
    int length;
    int maxLength = 1000;
    char *info = new char[maxLength];
    
    //Getting the program log info, which contains the errors.
    glGetProgramInfoLog(program, maxLength, &length, info);
    
    //Displaying the log info.
    std::cout << "Error (length " << length << "): " << info << "\n";
    
    //Deleting the string we created before.
    delete info;
}

}