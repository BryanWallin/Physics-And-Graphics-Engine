//============================================================================//
//                                                                            //
//  Quaternion.h                                                              //
//                                                                            //
//  The Quaternion class is used to store attributes of a quaternion.         //
//  Quaternions are extremely useful for storing rotations and interpolating  //
//  between them.                                                             //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 01/19/2013 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#ifndef __QUATERNION__
#define __QUATERNION__

#include <iostream>
#include "Vector3.h"
#include "Matrix4.h"
#include "MathLibrary.h"

namespace GraphicsEngine
{

class Vector3;
    class Matrix3;
    class Matrix4;

class Quaternion
{
public:
    
    static Quaternion Slerp(const Quaternion &q1, const Quaternion &q2,
                            float t);
    
    static Quaternion Nlerp(const Quaternion &q1, const Quaternion &q2,
                            float t);
    
    static float Angle(const Quaternion &q1, const Quaternion &q2);
    
    static float Dot(const Quaternion &q1, const Quaternion &q2);
    
    //========================================================================//
    //=========================Public Static Methods==========================//
    //========================================================================//
    
    //================================Identity================================//
    
    //This method makes the identity quaternion.
    static Quaternion Identity();
    
    //================================Rotating================================//
    
    //This method makes a quaternion from an axis-angle input.
    static Quaternion AngleAxis(float degrees, const Vector3 &axis);
    
    //This method makes a quaternion from a Matrix3 rotation.
    static Quaternion Rotation(const Matrix3 &matrix3);
    
    //This method makes a quaternion from a Matrix4 rotation.
    static Quaternion Rotation(const Matrix4 &matrix4);

    //========================================================================//
    //==========================Public Instance Data==========================//
    //========================================================================//
    
    //The first component of the quaternion.
    float x;
    
    //The second component of the quaternion.
    float y;
    
    //The third component of the quaternion.
    float z;
    
    //The fourth component of the quaternion.
    float w;
    
    //========================================================================//
    //===========================Public Methods===============================//
    //========================================================================//
    
    //==============================Constructors==============================//
    
    //The default constructor.
    Quaternion();
    
    //The complete constructor.
    Quaternion(float w, float x, float y, float z);
    
    //The axis/angle constructor.
    Quaternion(float angle, const Vector3 &axis);
    
    //The copy constructor.
    Quaternion(const Quaternion& quaternion);
    
    //===================Non-Modifying Arithmetic Operators===================//
    
    //The unary minus operator.
    Quaternion operator - () const;
    
    //The addition operator adds a given quaternion.
    Quaternion operator + (const Quaternion& quaternion) const;
    
    //The subtraction operator subtracts a given quaternion.
    Quaternion operator - (const Quaternion& quaternion) const;
    
    //The multiplication (by a constant) operator.
    Quaternion operator * (const float scalar) const;
    
    //The multiplication (by another quaternion) operator.
    Quaternion operator * (const Quaternion& quaternion) const;
    
    //The division operator divides by a scalar.
    Quaternion operator / (const float scalar) const;
    
    //=====================Modifying Arithmetic Operators=====================//
    
    //The addition assignment operator adds the given quaternion and stores the
    //result.
    Quaternion& operator += (const Quaternion& quaternion);
    
    //The subtraction assignment operator subtracts the given quaternion and
    //stores the result.
    Quaternion& operator -= (const Quaternion& quaternion);
    
    //The multiplication assignment operator multiplies the quaternion by a
    //constant and stores the result.
    Quaternion& operator *= (const float scalar);
    
    //The multiplication assignment operator multiplies the quaternion by the
    //given quaternion term-by-term and stores the result.
    Quaternion& operator *= (const Quaternion& quaternion);
    
    //The division assignment operator divides the quaternion by a constant and
    //stores the result.
    Quaternion& operator /= (const float scalar);
    
    //===========================Equality Operators===========================//
    
    //The equality operator checks if the given quaternion and this quaternion
    //contain the same components.
    bool operator == (const Quaternion& quaternion) const;
    
    //The inequality operator checks if the given quaternion and this
    //quaternion contain the same components.
    bool operator != (const Quaternion& quaternion) const;
    
    //============================Other Operators=============================//
    
    //This method returns the length of the quaternion.
    float length() const;
    
    //This method normalizes the quaternion.
    void normalize();
    
//    //This method returns the conjugate of this quaternion.
//    Quaternion conjugate();
//    
    //This method returns the inverse of this quaternion.
    Quaternion inverse() const;
    
private:
    
    //========================================================================//
    //==========================Private Methods===============================//
    //========================================================================//
    
    
};

}

#endif
