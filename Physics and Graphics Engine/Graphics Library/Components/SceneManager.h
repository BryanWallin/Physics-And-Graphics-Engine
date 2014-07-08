#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

////Including the necessary files.
//#include <unordered_map>
//#include "RenderQueue.h"
//#include "Light.h"
//#include "Camera.h"
//
//namespace GraphicsEngine
//{
//
//class SceneManager
//{
//
//public:
//
//    //========================================================================//
//    //=============================Public Methods=============================//
//    //========================================================================//
//
//    //==============================Constructors==============================//
//
//    //The complete constructor.
//    SceneManager();
//
//    //================================Setters=================================//
//
//    //This method sets the ambient light.  The default value is gray.
//    void setAmbientLight(Vector4 ambientLight);
//
//    //This method sets the current camera.
//    void setCurrentCamera(Camera *currentCamera);
//
//    //================================Getters=================================//
//
//    //This method gets the ambient light.
//    Vector4 getAmbientLight();
//
//    //This method gets the root scene node.
//    SceneNode * getRootSceneNode();
//
//    //This method gets the specified scene node.
//    SceneNode * getSceneNode(std::string sceneNodeName);
//
//    //This method gets the current camera.
//    Camera * getCurrentCamera();
//
//    //=============================Other Methods==============================//
//
//    //This method creates an object with a name from a file.
//    //RenderableObject * createRenderableObject(std::string name,
//    //    std::string meshFilePath);
//
//    //This method creates a light with a name.
//    Light * createLight(std::string name);
//
//    //This method removes a light.
//    void destroyLight(std::string name);
//
//    //This method creates a camera with a name.
//    Camera * createCamera(std::string name);
//
//    //This method allows a scene node to "add" a renderable object to the 
//    //queue.
//    //void addRenderableObjectToQueue(SceneNode *sceneNode,
//    //    RenderableObject *renderableObject);
//
//    //This method allows a scene node to "add" another scene node to the list 
//    //of scene nodes.
//    void addSceneNodeToList(SceneNode *parentSceneNode, 
//        SceneNode *childSceneNode);
//
//    //This method renders the scene.
//    void renderScene(float motionBlur);
//
//    //This method sets the viewport size.
//    void setViewportSize(int viewportWidth, int viewportHeight);
//
//private:
//
//    //=========================Private Instance Data==========================//
//
//    //The root node of the scene.
//    SceneNode *m_RootSceneNode;
//
//    //The ambient light of the scene.
//    Vector4 m_AmbientLight;
//
//    //The render queue of the scene manager.
//    RenderQueue *m_RenderQueue;
//
//    //The unordered map of scene nodes that exist in the scene graph.
//    std::unordered_map<std::string, SceneNode *> *m_SceneNodes;
//
//    //The unordered map of renderable objects.
//    //std::unordered_map<std::string, RenderableObject *> *m_RenderableObjects;
//
//    //The unordered map of lights.
//    std::unordered_map<std::string, Light *> *m_Lights;
//
//    //The unordered map of cameras.
//    std::unordered_map<std::string, Camera *> *m_Cameras;
//
//    //The currently active camera.
//    Camera *m_CurrentCamera;
//
//    //The viewport width and height.
//    int m_ViewportWidth, m_ViewportHeight;
//
//    //============================Private Methods=============================//
//
//    //This method updates the render queue.
//    void updateRenderQueue();
//};
//
//}

#endif