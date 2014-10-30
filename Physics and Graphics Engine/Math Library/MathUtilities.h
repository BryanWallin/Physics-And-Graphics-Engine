//============================================================================//
//                                                                            //
//  MathUtilies.h                                                             //
//                                                                            //
//  The MathUtilies class provides basic math utilities and functions.        //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 01/27/2014 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#ifndef _MATHUTILITIES_H_
#define _MATHUTILITIES_H_

#include "Vectors\Vector2.h"
#include "Vectors\Vector3.h"
#include "Vectors\Vector4.h"

namespace GraphicsEngine
{

//=================================Constants==================================//

const float PI = 3.1415926f;

//==================================Methods===================================//

//This method converts radians to degrees.
float radiansToDegrees(float radians);

//This method converts degrees to radians.
float degreesToRadians(float degrees);

//This method linearly interpolates between two floats.
float lerp(float a, float b, float percent);

//This method linearly interpolates between two Vector2s.
Vector2 lerp(Vector2 a, Vector2 b, float percent);

//This method linearly interpolates between two Vector3s.
Vector3 lerp(Vector3 a, Vector3 b, float percent);

//This method linearly interpolates between two Vector4s.
Vector4 lerp(Vector4 a, Vector4 b, float percent);

}

#endif