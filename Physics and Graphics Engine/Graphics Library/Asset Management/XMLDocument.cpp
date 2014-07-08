//============================================================================//
//                                                                            //
//  XMLDocument.cpp                                                           //
//                                                                            //
//  The XMLDocument class is used to store items that belong to an XML        //
//  document, using the XMLNode class as the underlying storage system.       //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 03/28/2014 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#include "XMLDocument.h"


namespace GraphicsEngine
{

//============================================================================//
//===============================Public Methods===============================//
//============================================================================//

//================================Constructors================================//

//The default constructor.
XMLDocument::XMLDocument() : XMLDocument("", "")
{
}

//The iOS constructor.
XMLDocument::XMLDocument(std::string fileName, std::string fileExtension)
{
    m_FileName = fileName;
    m_FileExtension = fileExtension;
    
    m_RootNode = NULL;
}

//=================================Destructor=================================//

//The destructor.
XMLDocument::~XMLDocument()
{
    delete m_RootNode;
}

//==================================Setters===================================//

//This method sets the file.
void XMLDocument::setFile(std::string fileName, std::string fileExtension)
{
    m_FileName = fileName;
    m_FileExtension = fileExtension;
}

//==================================Getters===================================//

//This method returns the root XML node.
XMLNode * XMLDocument::getRootNode()
{
    return m_RootNode;
}

//This method returns the XML node corresponding to the ID passed in.
XMLNode * XMLDocument::getNodeByID(std::string nodeID)
{
    std::unordered_map<std::string, XMLNode *>::iterator iterator =
        m_IDNodes.find(nodeID);
    
    if(iterator == m_IDNodes.end())
        return NULL;
    else
        return iterator->second;
}

//=============================Document Building==============================//

//This method builds the document from the file name given.
bool XMLDocument::buildDocument()
{
    //Creating an ifstream object from the file name passed in.
    std::ifstream file(getFilePath(m_FileName, m_FileExtension));
    
    //--------------------------Bookeeping Variables--------------------------//
    
    //This string holds the current file line.
    std::string fileLine;
    
    //The current char index of the current file line.
    int charIndex = 0;
    
    //A stack to keep track of the current XML node.
    std::stack<XMLNode *> stack;
    
    //------------------------------File Reading------------------------------//
    
    //Making sure the file is in the correct format.
    std::getline(file, fileLine);
    if(fileLine != "<?xml version=\"1.0\" encoding=\"utf-8\"?>")
    {
        std::cout << "Collada file is in the wrong format!\n";
        return false;
    }
    
    //Looping through the file line by line.
    while(std::getline(file, fileLine))
    {
        //Stripping off the leading and trailing whitespace.
        int first = int(fileLine.find_first_not_of(' '));
        int last = int(fileLine.find_last_not_of(' '));
        fileLine.erase(last + 1, fileLine.length());
        fileLine.erase(0, first);
        
        //Looping through the current line until all the characters are parsed.
        while(fileLine.length() > 0)
        {
            //Resetting the char index.
            charIndex = 0;
            
            //Case 1: It's an XML node.
            if(fileLine[0] == '<')
            {
                //Finding the end of the current XML node to parse.
                while(fileLine[charIndex] != '>')
                    charIndex++;
                
                parseXMLNode(fileLine.substr(0, charIndex + 1), stack);
                
                fileLine.erase(0, charIndex + 1);
            }
            //Case 2: It's content for an XML node.
            else
            {
                //Finding the beginning of next XML node to parse.
                while(fileLine[charIndex] != '<' &&
                      fileLine[charIndex] != '\n')
                    charIndex++;
                
                stack.top()->setContents(fileLine.substr(0, charIndex));
                
                fileLine.erase(0, charIndex);
            }
        }
    }
    
    return false;
}

//============================Document Displaying=============================//

//This method displays the document in the console.
void XMLDocument::displayDocument()
{
    m_RootNode->display(0);
}

//============================================================================//
//==============================Private Methods===============================//
//============================================================================//

//This is a helper method that parses a single XML node.
bool XMLDocument::parseXMLNode(std::string nodeString,
                               std::stack<XMLNode *> &nodeStack)
{
    //Erasing the outer and inner brackets.
    nodeString.erase(nodeString.end());
    nodeString.erase(nodeString.begin());
    
    //Case 1: The node is a closing node.
    if(nodeString.substr(0, 1) == "/")
    {
        //Making sure we are closing the proper node.
        if(nodeString.substr(1, nodeString.length() - 2) !=
           nodeStack.top()->getElementName())
        {
            std::cout << "Closing the wrong XML node!  Tried to close <"
                      << nodeString.substr(1, nodeString.length() - 2)
                      << "> but should have closed <"
                      << nodeStack.top()->getElementName() << ">!\n";
            return false;
        }
        
        //Otherwise, pop the node that was just closed.
        nodeStack.pop();
        
        return true;
    }
    //Case 2: The node is an opening node.
    else
    {
        int charIndex = 0;
        
        //Determining where the element name ends.
        while(nodeString[charIndex] != ' ' &&
              nodeString[charIndex] != '/' &&
              nodeString[charIndex] != '>')
            charIndex++;
        
        XMLNode *newNode = new XMLNode(nodeString.substr(0, charIndex));
        
        //Parenting this XML node.
        if(nodeStack.empty())
            m_RootNode = newNode;
        else
            nodeStack.top()->addChild(newNode);
        
        //Making this XML node the new current node.
        nodeStack.push(newNode);
        
        //Erasing the name from the string.
        nodeString.erase(0, charIndex);
        
        //Looping through to get the attributes.  If the length is more than 2,
        //there are attributes to get.
        while(nodeString.length() > 2)
        {
            //Resetting the char index to one past the space.
            charIndex = 1;
            
            bool isInsideValueString = false;
            
            //Determining where the attribute entry ends.
            while(isInsideValueString ||
                  (nodeString[charIndex] != ' ' &&
                   nodeString[charIndex] != '/' &&
                   nodeString[charIndex] != '>'))
            {
                if(nodeString[charIndex] == '\"')
                    isInsideValueString = !isInsideValueString;
                
                charIndex++;
            }
            
            addAttribute(nodeString.substr(1, charIndex - 1), nodeStack);
            
            nodeString.erase(0, charIndex);
        }
        //Seeing if the XML node is closed.
        if(nodeString[0] == '/')
            nodeStack.pop();
        
        return true;
    }
}

//This is a helper method that parses a string for attributes.
void XMLDocument::addAttribute(std::string nodeAttributeString,
                                std::stack<XMLNode *> &nodeStack)
{
    int nameEndIndex = 0;
    
    //Determining where the attribute name ends.
    while(nodeAttributeString[nameEndIndex] != '=')
        nameEndIndex++;
    
    std::string attributeName = nodeAttributeString.substr(0, nameEndIndex);
    
    int valueEndIndex = nameEndIndex + 2;
    int valueLength = 0;
    
    //Determining where the attribute value ends.
    while(nodeAttributeString[valueEndIndex] != '\"')
    {
        valueEndIndex++;
        valueLength++;
    }
    
    std::string attributeValue = nodeAttributeString.substr(nameEndIndex + 2,
                                                            valueLength);
    
    nodeStack.top()->addAttribute(attributeName, attributeValue);
    
    //If the attribute is an ID, then add it to the searchable list of XML
    //nodes with IDs.
    if(attributeName == "id")
        m_IDNodes.insert(std::make_pair(attributeValue, nodeStack.top()));
}

}