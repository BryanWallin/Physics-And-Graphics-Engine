//============================================================================//
//                                                                            //
//  XMLNode.h                                                                 //
//                                                                            //
//  The XMLNode class is used to store items that belong to an XML node, such //
//  as attributes and its contents.                                           //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 03/28/2014 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#ifndef __XML_NODE__
#define __XML_NODE__

#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>

namespace GraphicsEngine
{
    
class XMLNode
{
    
public:
    
    //========================================================================//
    //=============================Public Methods=============================//
    //========================================================================//
    
    //==============================Constructors==============================//
    
    //The name constructor.
    XMLNode(std::string elementName);
    
    //===============================Destructor===============================//
    
    //The destructor.
    virtual ~XMLNode();
    
    //================================Setters=================================//
    
    //This method sets the contents of the XML node.
    void setContents(std::string contents);
    
    //================================Getters=================================//
    
    //This method gets the element name of the XML node.
    std::string getElementName();
    
    //This method gets the contents of the XML node.
    std::string getContents();
    
    //This method returns true if the child XML node corresponding to the
    //element name passed in exists, false if not.
    bool hasChild(std::string elementName);
    
    //This method gets the child XML node corresponding to the element name
    //passed in.
    XMLNode * getChild(std::string elementName);
    
    //This method gets the child XML node corresponding to the element name,
    //attribute name, and attribute value passed in.
    XMLNode * getChild(std::string elementName, std::string attributeName,
                       std::string attributeValue);
    
    //This method returns a vector with all the child XML nodes with the same
    //element name passed in.
    std::vector<XMLNode *> getChildren(std::string elementName);
    
    //This method returns a vector with all the child XML nodes.
    std::vector<XMLNode *> getAllChildren();
    
    //This method gets the attribute data corresponding to the name passed in.
    std::string getAttribute(std::string name);
    
    //=============================Adding Methods=============================//
    
    //This method adds a child XML node.
    void addChild(XMLNode *child);
    
    //This method adds an attribute.
    void addAttribute(std::string name, std::string value);
    
    //==========================XML Node Displaying===========================//
    
    //This method displays this XML node and all of its children.
    void display(int indentation);
    
private:
    
    //========================================================================//
    //=========================Private Instance Data==========================//
    //========================================================================//
    
    //The element name of this node.
    std::string m_ElementName;
    
    //The contents of this tag.
    std::string m_Contents;
    
    //The children of this XML node.
    std::unordered_multimap<std::string, XMLNode *> *m_Children;
    
    //The attributes of this XML node.
    std::unordered_map<std::string, std::string> *m_Attributes;
};

}

#endif