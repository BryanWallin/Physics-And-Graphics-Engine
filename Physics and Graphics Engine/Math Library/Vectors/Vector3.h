//============================================================================//
//                                                                            //
//  Vector3.h                                                                 //
//                                                                            //
//  The Vector3 class is used to store attributes of a vector of length 3.    //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 01/19/2013 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include <cmath>
#include "Vector2.h"
#include "Vector4.h"

namespace GraphicsEngine
{

//Forward declarations.
class Vector2;
class Vector4;

class Vector3
{
    
public:
    
    //========================================================================//
    //==========================Public Instance Data==========================//
    //========================================================================//
    
    //The first component of the vector.
    float x;
    
    //The second component of the vector.
    float y;
    
    //The third component of the vector.
    float z;
    
    //========================================================================//
    //===========================Public Methods===============================//
    //========================================================================//
    
    //==============================Constructors==============================//
    
    //The complete constructor.
    Vector3(const float x = 0.0f, const float y = 0.0f, const float z = 0.0f);
    
    //The Vector2 copy constructor.
    explicit Vector3(const Vector2& vector2, float z = 0.0f);
    
    //The Vector3 copy constructor.
    Vector3(const Vector3& vector3);
    
    //The Vector4 copy constructor.
    explicit Vector3(const Vector4& vector4);
    
    //===========================Indexing Operators===========================//
    
    //The "write" indexing operator.
    float& operator [] (int index);
    
    //The "read" indexing operator.
    const float& operator [] (int index) const;
    
    //===================Non-Modifying Arithmetic Operators===================//
    
    //The unary minus operator.
    Vector3 operator - () const;
    
    //The addition operator adds a given vector.
    Vector3 operator + (const Vector3& vector3) const;
    
    //The subtraction operator subtracts a given vector.
    Vector3 operator - (const Vector3& vector3) const;
    
    //The multiplication (by a constant) operator.
    Vector3 operator * (const float scalar) const;
    
    //The friend multiplication (by a constant) operator.
    friend Vector3 operator * (const float scalar, const Vector3 &vector3);
    
    //The multiplication (term-by-term product) operator.
    Vector3 operator * (const Vector3& vector3) const;
    
    //The division operator divides by a scalar.
    Vector3 operator / (const float scalar) const;
    
    //=====================Modifying Arithmetic Operators=====================//
    
    //The addition assignment operator adds the given vector and stores the
    //result.
    Vector3& operator += (const Vector3& vector3);
    
    //The subtraction assignment operator subtracts the given vector and stores
    //the result.
    Vector3& operator -= (const Vector3& vector3);
    
    //The multiplication assignment operator multiplies the vector by a
    //constant and stores the result.
    Vector3& operator *= (const float scalar);
    
    //The multiplication assignment operator multiplies the vector by the given
    //vector term-by-term and stores the result.
    Vector3& operator *= (const Vector3& vector3);
    
    //The division assignment operator divides the vector by a constant and
    //stores the result.
    Vector3& operator /= (const float scalar);
    
    //===========================Equality Operators===========================//
    
    //The equality operator checks if the given vector and this vector contain
    //the same components.
    bool operator == (const Vector3& vector3);
    
    //The inequality operator checks if the given vector and this vector
    //contain the same components.
    bool operator != (const Vector3& vector3);
    
    //=============================Cast Operators=============================//
    
    //The cast operator casts the vector to an array of floats.
    operator const float* () const;
    
    //The cast operator casts the vector to an array of floats.
    operator float* ();
    
    //============================Other Operators=============================//
    
    //This method computes the length.
    float length() const;
    
    //This method normalizes the vector.
    Vector3 normalize();
    
    //This method calculates the dot product with another vector.
    float dot(const Vector3& vector3) const;
    
    //This method calculates the cross product with another vector.
    Vector3 cross(const Vector3& vector3) const;
    
    //=============================Other Methods==============================//
    
    //This method clears the entries all to 0.
    void clear();
};

}

#endif