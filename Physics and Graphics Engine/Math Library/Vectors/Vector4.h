//============================================================================//
//                                                                            //
//  Vector4.h                                                                 //
//                                                                            //
//  The Vector4 class is used to store attributes of a vector of length 4.    //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 02/08/2014 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#ifndef __VECTOR4__
#define __VECTOR4__

#include <cmath>
#include "Vector2.h"
#include "Vector3.h"

namespace GraphicsEngine
{

//Forward declarations.
class Vector2;
class Vector3;

class Vector4
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
    
    //The fourth component of the vector.
    float w;
    
    //========================================================================//
    //===========================Public Methods===============================//
    //========================================================================//
    
    //==============================Constructors==============================//
    
    //The complete constructor.
    Vector4(const float x = 0.0f, const float y = 0.0f, const float z = 0.0f,
            const float w = 0.0f);
    
    //The Vector2 copy constructor.
    explicit Vector4(const Vector2& vector2, float z = 0.0f, float w = 0.0f);
    
    //The Vector3 copy constructor.
    explicit Vector4(const Vector3& vector3, float w = 0.0f);
    
    //The Vector4 copy constructor.
    Vector4(const Vector4& vector4);
    
    //===========================Indexing Operators===========================//
    
    //The "write" indexing operator.
    float& operator [] (int index);
    
    //The "read" indexing operator.
    const float& operator [] (int index) const;
    
    //===================Non-Modifying Arithmetic Operators===================//
    
    //The unary minus operator.
    Vector4 operator - () const;
    
    //The addition operator adds a given vector.
    Vector4 operator + (const Vector4& vector4) const;
    
    //The subtraction operator subtracts a given vector.
    Vector4 operator - (const Vector4& vector4) const;
    
    //The multiplication (by a constant) operator.
    Vector4 operator * (const float scalar) const;
    
    //The friend multiplication (by a constant) operator.
    friend Vector4 operator * (const float scalar, const Vector4 &vector4);
    
    //The multiplication (term-by-term product) operator.
    Vector4 operator * (const Vector4& vector4) const;
    
    //The division operator divides by a scalar.
    Vector4 operator / (const float scalar) const;
    
    //=====================Modifying Arithmetic Operators=====================//
    
    //The addition assignment operator adds the given vector and stores the
    //result.
    Vector4& operator += (const Vector4& vector4);
    
    //The subtraction assignment operator subtracts the given vector and stores
    //the result.
    Vector4& operator -= (const Vector4& vector4);
    
    //The multiplication assignment operator multiplies the vector by a
    //constant and stores the result.
    Vector4& operator *= (const float scalar);
    
    //The multiplication assignment operator multiplies the vector by the given
    //vector term-by-term and stores the result.
    Vector4& operator *= (const Vector4& vector4);
    
    //The division assignment operator divides the vector by a constant and
    //stores the result.
    Vector4& operator /= (const float scalar);
    
    //===========================Equality Operators===========================//
    
    //The equality operator checks if the given vector and this vector contain
    //the same components.
    bool operator == (const Vector4& vector4);
    
    //The inequality operator checks if the given vector and this vector
    //contain the same components.
    bool operator != (const Vector4& vector4);
    
    //=============================Cast Operators=============================//
    
    //The cast operator casts the vector to an array of floats.
    operator const float* () const;
    
    //The cast operator casts the vector to an array of floats.
    operator float* ();
    
    //============================Other Operators=============================//
    
    //This method computes the length.
    float length() const;
    
    //This method normalizes the vector.
    Vector4 normalize();
    
    //This method calculates the dot product with another vector.
    float dot(const Vector4& vector4) const;
    
    //=============================Other Methods==============================//
    
    //This method clears the entries all to 0.
    void clear();
};

}

#endif