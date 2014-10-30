#include "AssetLoader.h"

namespace GraphicsEngine
{

//This method gets the full file path of the file name and type requested.
std::string getFilePath(std::string fileName, std::string fileType)
{
	return "Resources\\" + fileName + "." + fileType;
}

//This method gets the full file contents of the file name and type requested.
const std::string getFileContents(std::string fileName, std::string fileType)
{
	std::ifstream t("");

	std::string str;

	t.seekg(0, std::ios::end);
	str.reserve((unsigned int)t.tellg());
	t.seekg(0, std::ios::beg);

	str.assign((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());

	return str;
}

//This method gets the full file contents of the file at the specified file 
//path.
const std::string getFileContents(std::string filePath)
{
	std::ifstream t(filePath);

	std::string str;

	t.seekg(0, std::ios::end);
	str.reserve((unsigned int)t.tellg());
	t.seekg(0, std::ios::beg);

	str.assign((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());

	return str;
}

}