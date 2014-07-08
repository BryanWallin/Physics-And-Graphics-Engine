//============================================================================//
//                                                                            //
//  CameraController.h                                                        //
//                                                                            //
//  The CameraController class is used to control a camera by means of an     //
//  easy-to-use interface.                                                    //
//                                                                            //
//  Original Author: Bryan Wallin                                             //
//  Last modified on 12/02/2013 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#ifndef _CAMERACONTROLLER_H_
#define _CAMERACONTROLLER_H_

////Including the necessary files.
//#include "MathLibrary.h"
//#include "SceneNode.h"
//#include "Camera.h"
//
//namespace GraphicsEngine
//{
//
//class CameraController
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
//    //The default constructor.
//    CameraController(Camera *camera, SceneNode *focusAtNode);
//
//    //================================Setters=================================//
//
//    //This method sets the minimum distance the camera can be from the scene 
//    //node of interest.
//    void setMinimumDistance(float distance);
//
//    //This method sets the maximum distance the camera can be from the scene 
//    //node of interest.
//    void setMaximumDistance(float distance);
//
//    //=========================Transformation Methods=========================//
//
//    //This method rotates the camera around the x axis.
//    void rotateCameraX(float xDegrees);
//
//    //This method rotates the camera around the y axis.
//    void rotateCameraY(float yDegrees);
//
//    //This method rotates the camera around the z axis.
//    void rotateCameraZ(float zDegrees);
//
//    //This method translates the camera in the direction it is pointing.
//    void translateCamera(float distance);
//
//private:
//
//    //========================================================================//
//    //=========================Private Instance Data==========================//
//    //========================================================================//
//
//    //The camera we are controlling.
//    Camera *m_Camera;
//
//    //Storing the focus at and camera at nodes.
//    SceneNode *m_FocusAtNode, *m_CameraAtNode;
//
//    //Storing the rotation nodes.
//    SceneNode *m_RotationNode;
//
//    //Storing the max back and front distances.
//    float m_MaxCameraDistance, m_MinCameraDistance;
//
//    //Storing the current distance.
//    float m_CurrentCameraDistance;
//
//    //========================================================================//
//    //============================Private Methods=============================//
//    //========================================================================//
//
//    //This method updates the camera.
//    void updateCamera();
//};
//
//}

#endif