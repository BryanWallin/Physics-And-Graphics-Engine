//============================================================================//
//                                                                            //
//  MathUtilies.cpp                                                           //
//                                                                            //
//  The MathUtilies class provides basic math utilities and functions.        //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 01/27/2014 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#include "MathUtilities.h"

namespace GraphicsEngine
{
    
//==================================Methods===================================//

//This method converts radians to degrees.
float radiansToDegrees(float radians)
{
    return radians * (180 / PI);
}

//This method converts degrees to radians.
float degreesToRadians(float degrees)
{
    return degrees * (PI / 180);
}

//This method linearly interpolates between two floats.
float lerp(float a, float b, float percent)
{
    return a + (b - a) * percent;
}

//This method linearly interpolates between two Vector2s.
Vector2 lerp(Vector2 a, Vector2 b, float percent)
{
    return a + (b - a) * percent;
}

//This method linearly interpolates between two Vector3s.
Vector3 lerp(Vector3 a, Vector3 b, float percent)
{
    return a + (b - a) * percent;
}

//This method linearly interpolates between two Vector4s.
Vector4 lerp(Vector4 a, Vector4 b, float percent)
{
    return a + (b - a) * percent;
}

}