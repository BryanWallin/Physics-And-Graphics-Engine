#include "SceneManager.h"
#include <string>

namespace GraphicsEngine
{

////============================================================================//
////===============================Public Methods===============================//
////============================================================================//
//
////================================Constructors================================//
//
////The complete constructor.
//SceneManager::SceneManager()
//{
//    //Creating the root node.
//    m_RootSceneNode = new SceneNode(this, "Root");
//
//    //Setting the default amount of ambient light.
//    m_AmbientLight = Vector4(0.5, 0.5, 0.5, 1);
//
//    //Initializing the render queue.
//    m_RenderQueue = new RenderQueue(this);
//
//    //Initializing the lists of scene nodes, renderable objects, lights, and 
//    //cameras.
//    m_SceneNodes = new std::unordered_map<std::string, SceneNode *>();
//    //m_RenderableObjects = new std::unordered_map<std::string,
//    //    RenderableObject *>();
//    m_Lights = new std::unordered_map<std::string, 
//        Light *>();
//    m_Cameras = new std::unordered_map<std::string, 
//        Camera *>();
//
//    //Setting the current camera to be nothing.
//    m_CurrentCamera = NULL;
//}
//
////==================================Setters===================================//
//
////This method sets the ambient light.  The default value is black.
//void SceneManager::setAmbientLight(Vector4 ambientLight)
//{
//    m_AmbientLight = ambientLight;
//}
//
////This method sets the current camera.
//void SceneManager::setCurrentCamera(Camera *currentCamera)
//{
//    m_CurrentCamera = currentCamera;
//}
//
////==================================Getters===================================//
//
////This method gets the ambient light.
//Vector4 SceneManager::getAmbientLight()
//{
//    return m_AmbientLight;
//}
//
////This method gets the root scene node.
//SceneNode * SceneManager::getRootSceneNode()
//{
//    return m_RootSceneNode;
//}
//
////This method gets the specified scene node.
//SceneNode * SceneManager::getSceneNode(std::string sceneNodeName)
//{
//    std::unordered_map<std::string, SceneNode *>::iterator iterator = 
//        m_SceneNodes->find(sceneNodeName);
//
//    if(iterator == m_SceneNodes->end())
//        return NULL;
//    else
//        return iterator->second;
//}
//
////This method gets the current camera.
//Camera * SceneManager::getCurrentCamera()
//{
//    return m_CurrentCamera;
//}
//
////===============================Other Methods================================//
//
////This method renders the current scene.
//void SceneManager::renderScene(float motionBlur)
//{
//    //Updating the scene graph before rendering.
//    m_RootSceneNode->updateSelfAndChildren();
//
//    //Rendering the scene using the render queue.
//    m_RenderQueue->renderScene(motionBlur);
//
//    //Notifying the camera that the frame has ended.
//    m_CurrentCamera->endFrame();
//}
//
////This method creates an object with a name from a file.
////RenderableObject * SceneManager::createRenderableObject(std::string name, 
////        std::string meshFilePath)
////{
////    //Creating a new renderable object.
////    RenderableObject *renderableObject = 
////        new RenderableObject(this, name, meshFilePath);
////
////    //Inserting the renderable object into the list of renderable objects.
////    m_RenderableObjects->insert(std::make_pair(name, renderableObject));
////
////    return renderableObject;
////}
//
////This method creates a light with a name.
//Light * SceneManager::createLight(std::string name)
//{
//    Light * light = new Light();
//
//    m_Lights->insert(std::make_pair(name, light));
//    m_RenderQueue->addLight(light, name);
//
//    return light;
//}
//
////This method creates a camera with a name.
//Camera * SceneManager::createCamera(std::string name)
//{
//    Camera * camera = new Camera();
//
//    m_Cameras->insert(std::make_pair(name, camera));
//
//    return camera;
//}
//
////This method allows a scene node to "add" a renderable object to the 
////queue.
////void SceneManager::addRenderableObjectToQueue(SceneNode *sceneNode, 
////    RenderableObject *renderableObject)
////{
////    m_RenderQueue->addRenderableObject(renderableObject);
////}
//
////This method allows a scene node to "add" another scene node to the list 
////of scene nodes.
//void SceneManager::addSceneNodeToList(SceneNode *parentSceneNode, 
//    SceneNode *childSceneNode)
//{
//    m_SceneNodes->insert(std::make_pair(childSceneNode->getName(),
//                                        childSceneNode));
//}
//
////This method sets the viewport size.
//void SceneManager::setViewportSize(int viewportWidth, int viewportHeight)
//{
//    m_ViewportWidth = viewportWidth;
//    m_ViewportHeight = viewportHeight;
//
//    m_RenderQueue->setRenderSize(viewportWidth, viewportHeight);
//}
//
////==============================Private Methods===============================//

}