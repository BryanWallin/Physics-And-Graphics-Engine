//============================================================================//
//                                                                            //
//  Vector2.h                                                                 //
//                                                                            //
//  The Vector2 class is used to store attributes of a vector of length 2.    //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 01/19/2013 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#ifndef _VECTOR2_H_
#define _VECTOR2_H_

#include <cmath>
#include "Vector3.h"
#include "Vector4.h"

namespace GraphicsEngine
{

//Forward declarations.
class Vector3;
class Vector4;

class Vector2
{
    
public:
    
    //========================================================================//
    //==========================Public Instance Data==========================//
    //========================================================================//
    
    //The first component of the vector.
    float x;
    
    //The second component of the vector.
    float y;
    
    //========================================================================//
    //===========================Public Methods===============================//
    //========================================================================//
    
    //==============================Constructors==============================//
    
    //The complete constructor.
    Vector2(const float x = 0.0f, const float y = 0.0f);
    
    //The Vector2 copy constructor.
    Vector2(const Vector2& vector2);
    
    //The Vector3 copy constructor.
    explicit Vector2(const Vector3& vector3);
    
    //The Vector4 copy constructor.
    explicit Vector2(const Vector4& vector4);
    
    //===========================Indexing Operators===========================//
    
    //The "write" indexing operator.
    float& operator [] (int index);
    
    //The "read" indexing operator.
    const float& operator [] (int index) const;
    
    //===================Non-Modifying Arithmetic Operators===================//
    
    //The unary minus operator.
    Vector2 operator - () const;
    
    //The addition operator adds a given vector.
    Vector2 operator + (const Vector2& vector2) const;
    
    //The subtraction operator subtracts a given vector.
    Vector2 operator - (const Vector2& vector2) const;
    
    //The multiplication (by a constant) operator.
    Vector2 operator * (const float scalar) const;
    
    //The friend multiplication (by a constant) operator.
    friend Vector2 operator * (const float scalar, const Vector2 &vector2);
    
    //The multiplication (term-by-term product) operator.
    Vector2 operator * (const Vector2& vector2) const;
    
    //The division operator divides by a scalar.
    Vector2 operator / (const float scalar) const;
    
    //=====================Modifying Arithmetic Operators=====================//
    
    //The addition assignment operator adds the given vector and stores the
    //result.
    Vector2& operator += (const Vector2& vector2);
    
    //The subtraction assignment operator subtracts the given vector and stores
    //the result.
    Vector2& operator -= (const Vector2& vector2);
    
    //The multiplication assignment operator multiplies the vector by a
    //constant and stores the result.
    Vector2& operator *= (const float scalar);
    
    //The multiplication assignment operator multiplies the vector by the given
    //vector term-by-term and stores the result.
    Vector2& operator *= (const Vector2& vector2);
    
    //The division assignment operator divides the vector by a constant and
    //stores the result.
    Vector2& operator /= (const float scalar);
    
    //===========================Equality Operators===========================//
    
    //The equality operator checks if the given vector and this vector contain
    //the same components.
    bool operator == (const Vector2& vector2);
    
    //The inequality operator checks if the given vector and this vector
    //contain the same components.
    bool operator != (const Vector2& vector2);
    
    //=============================Cast Operators=============================//
    
    //The cast operator casts the vector to an array of floats.
    operator const float* () const;
    
    //The cast operator casts the vector to an array of floats.
    operator float* ();
    
    //============================Other Operators=============================//
    
    //This method computes the length.
    float length() const;
    
    //This method normalizes the vector.
    Vector2 normalize();
    
    //This method calculates the dot product with another vector.
    float dot(const Vector2& vector2) const;
    
    //=============================Other Methods==============================//
    
    //This method clears the entries all to 0.
    void clear();
};

}

#endif