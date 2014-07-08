//============================================================================//
//                                                                            //
//  Camera.cpp                                                                //
//                                                                            //
//  The Camera class is used to store camera attributes, such as the field of //
//  view, the focus, the aperture, and more.                                  //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 12/02/2013 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#include "Camera.h"

namespace GraphicsEngine
{

//============================================================================//
//===============================Public Methods===============================//
//============================================================================//

//================================Constructors================================//

//The complete constructor.
Camera::Camera(std::string name) : Actor(name)
{
    //Setting the camera to its default position, point of focus, and up 
    //direction.
    m_Transform->setPosition(Vector3(0, 0, 0));

    //Setting the field of view to 90 degrees.
    setFOV(90);
}

//==================================Setters===================================//

//This method allows the user to set the FOV.
void Camera::setFOV(float fov)
{
    if(fov >= MIN_FOV && fov <= MAX_FOV)
        m_FOV = fov;
}

//This method allows the user to set the focal length.
void Camera::setFocalLength(float length)
{
    if(length > 0)
        m_FocalLength = length;
}

//This method allows the user to set the plane in focus distance.
void Camera::setPlaneInFocusDistance(float distance)
{
    if(distance > 0)
        m_PlaneInFocusDistance = distance;
}

//This method allows the user to set the aperture size.
void Camera::setApertureSize(float size)
{
    if(size > 0)
        m_ApertureSize = size;
}

//==================================Getters===================================//

//This method returns the FOV.
float Camera::getFOV()
{
    return m_FOV;
}

//This method allows the user to get the focal length.
float Camera::getFocalLength()
{
    return m_FocalLength;
}

//This method allows the user to get the plane in focus distance.
float Camera::getPlaneInFocusDistance()
{
    return m_PlaneInFocusDistance;
}

//This method allows the user to set the aperture size.
float Camera::getApertureSize()
{
    return m_ApertureSize;
}

//=============================Camera Adjustments=============================//

//This method allows the user to increase the FOV by a specified amount.
void Camera::shiftFOV(float degrees)
{
    float possibleFOV = m_FOV + degrees;

    if(possibleFOV <= MIN_FOV && possibleFOV >= MAX_FOV)
        m_FOV = possibleFOV;
}

//This method allows the user to increase the FOV by a specified amount.
void Camera::shiftPlaneInFocus(float distance)
{
    if(m_PlaneInFocusDistance + distance > 0)
        m_PlaneInFocusDistance += distance;
}

//This method allows the user to increase the FOV by a specified amount.
void Camera::shiftApertureSize(float change)
{
    if(m_ApertureSize + change > 0)
        m_ApertureSize += change;
}

//===============================Camera Updates===============================//

//This method ends the current frame of the camera.
void Camera::endFrame()
{
    
}

}