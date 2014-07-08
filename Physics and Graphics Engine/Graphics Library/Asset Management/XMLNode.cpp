//============================================================================//
//                                                                            //
//  XMLNode.cpp                                                               //
//                                                                            //
//  The XMLNode class is used to store items that belong to an XML node, such //
//  as attributes and its contents.                                           //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 03/28/2014 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#include "XMLNode.h"

namespace GraphicsEngine
{

//============================================================================//
//===============================Public Methods===============================//
//============================================================================//

//================================Constructors================================//

//The name constructor.
XMLNode::XMLNode(std::string elementName)
{
    m_ElementName = elementName;
    
    //Setting the children and attributes to NULL.
    m_Children = NULL;
    m_Attributes = NULL;
}

//=================================Destructor=================================//

//The destructor.
XMLNode::~XMLNode()
{
    //If there are children, delete them as well.
    if(m_Children != NULL)
    {
        std::unordered_multimap<std::string, XMLNode *>::iterator iterator;

        for(iterator = m_Children->begin(); iterator != m_Children->end();
            iterator++)
            delete iterator->second;
    }
    
    delete m_Children;
    delete m_Attributes;
}

//==================================Setters===================================//

//This method sets the contents of the XML node.
void XMLNode::setContents(std::string contents)
{
    m_Contents = contents;
}
    
//==================================Getters===================================//

//This method gets the name of the XML node.
std::string XMLNode::getElementName()
{
    return m_ElementName;
}

//This method gets the contents of the XML node.
std::string XMLNode::getContents()
{
    return m_Contents;
}

//This method returns true if the child XML node corresponding to the
//element name passed in exists, false if not.
bool XMLNode::hasChild(std::string elementName)
{
    return getChild(elementName) != NULL;
}

//This method gets the child XML node corresponding to the element name passed
//in.
XMLNode * XMLNode::getChild(std::string elementName)
{
    //If there aren't any children, return NULL.
    if(m_Children == NULL)
        return NULL;
    
    std::unordered_multimap<std::string, XMLNode *>::iterator iterator =
        m_Children->find(elementName);
    
    if(iterator == m_Children->end())
        return NULL;
    else
        return iterator->second;
}

//This method gets the child XML node corresponding to the element name,
//attribute name, and attribute value passed in.
XMLNode * XMLNode::getChild(std::string elementName, std::string attributeName,
                   std::string attributeValue)
{
    //If there aren't any children, return NULL.
    if(m_Children == NULL)
        return NULL;
    
    //std::pair<std::unordered_multimap<std::string, XMLNode *>::iterator,
    //std::unordered_multimap<std::string, XMLNode *>::iterator> pairIterator
    auto pairIterator = m_Children->equal_range(elementName);
    for (auto iterator = pairIterator.first; iterator != pairIterator.second;
         iterator++)
    {
        //If the attribute name/value of this XML node matches the passed in
        //value, return it.
        if(iterator->second->getAttribute(attributeName) == attributeValue)
            return iterator->second;
    }
    
    //If we get here, we haven't found the matching XML node.
    return NULL;
}

//This method returns a vector with all the child XML nodes with the same
//element name passed in.
std::vector<XMLNode *> XMLNode::getChildren(std::string elementName)
{
    std::vector<XMLNode *> vector = std::vector<XMLNode *>();
    
    //If there aren't any children, return an empty vector.
    if(m_Children == NULL)
        return vector;
    
    //std::pair<std::unordered_multimap<std::string, XMLNode *>::iterator,
    //std::unordered_multimap<std::string, XMLNode *>::iterator> pairIterator
    auto pairIterator = m_Children->equal_range(elementName);
    for (auto iterator = pairIterator.first; iterator != pairIterator.second;
         iterator++)
        vector.push_back(iterator->second);
    
    return vector;
}

//This method returns a vector with all the child XML nodes.
std::vector<XMLNode *> XMLNode::getAllChildren()
{
    std::vector<XMLNode *> vector = std::vector<XMLNode *>();
    
    //If there aren't any children, return an empty vector.
    if(m_Children == NULL)
        return vector;
    
    for (auto iterator = m_Children->begin(); iterator != m_Children->end();
         iterator++)
        vector.push_back(iterator->second);
    
    return vector;
}

//This method gets the attribute data corresponding to the name passed in.
std::string XMLNode::getAttribute(std::string name)
{
    //If there aren't any attributes, return NULL.
    if(m_Attributes == NULL)
        return NULL;
    
    std::unordered_map<std::string, std::string>::iterator iterator =
        m_Attributes->find(name);
    
    if(iterator == m_Attributes->end())
        return NULL;
    else
        return iterator->second;
}

//===============================Adding Methods===============================//

//This method adds a child XML node.
void XMLNode::addChild(XMLNode *child)
{
    //If there aren't any children, instantiate the children unordered map.
    if(m_Children == NULL)
        m_Children = new std::unordered_multimap<std::string, XMLNode *>();
    
    m_Children->insert(std::make_pair(child->getElementName(), child));
}

//This method adds an attribute.
void XMLNode::addAttribute(std::string name, std::string value)
{
    //If there aren't any attributes, instantiate the children unordered map.
    if(m_Attributes == NULL)
        m_Attributes = new std::unordered_map<std::string, std::string>();
    
    m_Attributes->insert(std::make_pair(name, value));
}

//============================XML Node Displaying=============================//

//This method displays this XML node and all of its children.
void XMLNode::display(int indentation)
{
    //Indenting the proper amount.
    for(int i = 0; i < indentation; i++)
        std::cout << "\t";
    
    std::cout << "<" << m_ElementName;
    
    //If there are attributes, display them.
    if(m_Attributes != NULL)
    {
        std::unordered_map<std::string, std::string>::iterator iterator;
        
        for(iterator = m_Attributes->begin(); iterator != m_Attributes->end();
            iterator++)
            std::cout << " " << iterator->first << "=\"" << iterator->second
                      << "\"";
    }
    
    std::cout << ">";
    
    //If there are contents, display them.
    if(!m_Contents.empty())
        std::cout << " (" << m_Contents << ")";
    
    std::cout << "\n";
    
    //If there are children, display them as well.
    if(m_Children != NULL)
    {
        std::unordered_multimap<std::string, XMLNode *>::iterator iterator;
        
        for(iterator = m_Children->begin(); iterator != m_Children->end();
            iterator++)
            iterator->second->display(indentation + 1);
    }
}

}