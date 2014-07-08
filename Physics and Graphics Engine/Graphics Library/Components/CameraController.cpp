#include "CameraController.h"

namespace GraphicsEngine
{

////============================================================================//
////===============================Public Methods===============================//
////============================================================================//
//    
////================================Constructors================================//
//
//CameraController::CameraController(Camera *camera, SceneNode *focusAtNode)
//{
//    //Storing the camera reference.
//    m_Camera = camera;
//
//    //Setting the default front and back distances.
//    m_MinCameraDistance = 1;
//    m_MaxCameraDistance = 10;
//
//    //Storing a reference to the focus at node.
//    m_FocusAtNode = focusAtNode;
//
//    //Creating the camera controller heirarchy.
//    m_RotationNode = focusAtNode->createChildSceneNode("CameraRotationNode");
//    m_CameraAtNode = m_RotationNode->createChildSceneNode("CameraLocation");
//
//    //Setting the default distance and placing the camera there.
//    m_CurrentCameraDistance = 5;
//    m_CameraAtNode->translate(0, 0, 5, SceneNode::LOCAL);
//    updateCamera();
//}
//
////==================================Setters===================================//
//
////This method sets the minimum distance the camera can be from the scene 
////node of interest.
//void CameraController::setMinimumDistance(float distance)
//{
//    if(distance >= 0)
//        m_MinCameraDistance = distance;
//}
//
////This method sets the maximum distance the camera can be from the scene 
////node of interest.
//void CameraController::setMaximumDistance(float distance)
//{
//    if(distance >= 0)
//        m_MaxCameraDistance = distance;
//}
//
////===========================Transformation Methods===========================//
//
////This method rotates the camera around the x axis.
//void CameraController::rotateCameraX(float xDegrees)
//{
//    m_RotationNode->rotateX(xDegrees);
//    updateCamera();
//}
//
////This method rotates the camera around the y axis.
//void CameraController::rotateCameraY(float yDegrees)
//{
//    m_RotationNode->rotateY(yDegrees);
//    updateCamera();
//}
//
////This method rotates the camera around the z axis.
//void CameraController::rotateCameraZ(float zDegrees)
//{
//    m_RotationNode->rotateZ(zDegrees);
//    updateCamera();
//}
//
////This method translates the camera in the direction it is pointing.
//void CameraController::translateCamera(float distance)
//{
//    //If we are in the proper distance range after the distance change, then 
//    //update the node and current distance.
//    if(m_CurrentCameraDistance + distance <= m_MaxCameraDistance && 
//        m_CurrentCameraDistance + distance >= m_MinCameraDistance)
//    {
//        m_CurrentCameraDistance += distance;
//        m_CameraAtNode->translate(0, 0, distance, SceneNode::LOCAL);
//        updateCamera();
//    }
//}
//
////This method updates the camera.
//void CameraController::updateCamera()
//{
//    m_Camera->setPosition(m_CameraAtNode->getPosition());
//    m_Camera->setPointOfFocus(m_FocusAtNode->getPosition());
//    m_Camera->setUpDirection(m_CameraAtNode->getUpDirection());
//}

}