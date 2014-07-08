//============================================================================//
//                                                                            //
//  XMLDocument.h                                                             //
//                                                                            //
//  The XMLDocument class is used to store items that belong to an XML        //
//  document, using the XMLNode class as the underlying storage system.       //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 03/28/2014 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#ifndef __XML_DOCUMENT__
#define __XML_DOCUMENT__

#include <string>
#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <stack>
#include <unordered_map>
#include "AssetLoader.h"
#include "XMLNode.h"

namespace GraphicsEngine
{
    
class XMLDocument
{
    
public:
    
    //========================================================================//
    //=============================Public Methods=============================//
    //========================================================================//
    
    //==============================Constructors==============================//
    
    //The default constructor.
    XMLDocument();
    
    //The iOS constructor.
    XMLDocument(std::string fileName, std::string fileExtension);
    
    //===============================Destructor===============================//
    
    //The destructor.
    ~XMLDocument();
    
    //================================Setters=================================//
    
    //This method sets the file.
    void setFile(std::string fileName, std::string fileExtension);
    
    //================================Getters=================================//
    
    //This method returns the root XML node.
    XMLNode * getRootNode();
    
    //This method returns the XML node corresponding to the ID passed in.
    XMLNode * getNodeByID(std::string nodeID);
    
    //===========================Document Building============================//
    
    //This method builds the document from the file name given.
    bool buildDocument();
    
    //==========================Document Displaying===========================//
    
    //This method displays the document in the console.
    void displayDocument();
    
private:
    
    //========================================================================//
    //=========================Private Instance Data==========================//
    //========================================================================//
    
    //The file name of this document.
    std::string m_FileName;
    
    //The file extension of this document.
    std::string m_FileExtension;
    
    //The root XML node of this document.
    XMLNode *m_RootNode;
    
    //The IDs of the XML nodes in the document.
    std::unordered_map<std::string, XMLNode *> m_IDNodes;
    
    //========================================================================//
    //============================Private Methods=============================//
    //========================================================================//
    
    //This is a helper method that parses a single XML node.
    bool parseXMLNode(std::string nodeString, std::stack<XMLNode *> &nodeStack);
    
    //This is a helper method that parses a string for attributes.
    void addAttribute(std::string nodeAttributeString,
                       std::stack<XMLNode *> &nodeStack);
    
    
};

}

#endif