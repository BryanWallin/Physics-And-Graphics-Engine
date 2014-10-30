//============================================================================//
//                                                                            //
//  Camera.h                                                                  //
//                                                                            //
//  The Camera class is used to store camera attributes, such as the field of //
//  view, the focal length of the lens, the plane in focus, the aperture,     //
//  and more.                                                                 //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 12/05/2013 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "..\..\Math Library\MathLibrary.h"
#include "Actor.h"

namespace GraphicsEngine
{

class Camera : public Actor
{
public:

    //========================================================================//
    //============================Static Constants============================//
    //========================================================================//

    //Setting the maximum and minimum field of view.
    static const int MAX_FOV = 170;
    static const int MIN_FOV = 10;

    //==============================Constructors==============================//

    //The complete constructor.
    Camera(std::string name);

    //========================================================================//
    //=============================Public Methods=============================//
    //========================================================================//

    //================================Setters=================================//

    //This method allows the user to set the FOV.
    void setFOV(float fov);

    //This method allows the user to set the focal length.
    void setFocalLength(float length);

    //This method allows the user to set the plane in focus distance.
    void setPlaneInFocusDistance(float distance);

    //This method allows the user to set the aperture size.
    void setApertureSize(float size);

    //================================Getters=================================//

    //This method returns the FOV.
    float getFOV();

    //This method allows the user to get the focal length.
    float getFocalLength();

    //This method allows the user to get the plane in focus distance.
    float getPlaneInFocusDistance();

    //This method allows the user to get the aperture size.
    float getApertureSize();

    //===========================Camera Adjustments===========================//

    //This method allows the user to increase the FOV by a specified amount.
    void shiftFOV(float degrees);

    //This method allows the user to increase the FOV by a specified amount.
    void shiftPlaneInFocus(float distance);

    //This method allows the user to increase the FOV by a specified amount.
    void shiftApertureSize(float change);

    //=============================Camera Updates=============================//

    //This method ends the current frame of the camera.
    void endFrame();

private:

    //=========================Private Instance Data==========================//

    //This variable stores the field of view.
    float m_FOV;

    //This variable stores the focal length.
    float m_FocalLength;

    //This variable stores the plane in focus distance.
    float m_PlaneInFocusDistance;

    //This variable stores the aperture size.
    float m_ApertureSize;
};

}

#endif