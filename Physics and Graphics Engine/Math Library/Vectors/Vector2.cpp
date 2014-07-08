//============================================================================//
//                                                                            //
//  Vector2.cpp                                                               //
//                                                                            //
//  The Vector2 class is used to store attributes of a vector of length 2.    //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 01/19/2013 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#include "Vector2.h"

namespace GraphicsEngine
{

//============================================================================//
//=============================Public Methods=================================//
//============================================================================//

//================================Constructors================================//

//The complete constructor.
Vector2::Vector2(float x, float y)
{
    this->x = x;
    this->y = y;
}

//The Vector2 copy constructor.
Vector2::Vector2(const Vector2& vector2)
{
    x = vector2.x;
    y = vector2.y;
}

//The Vector3 copy constructor.
Vector2::Vector2(const Vector3& vector3)
{
    x = vector3.x;
    y = vector3.y;
}

//The Vector4 copy constructor.
Vector2::Vector2(const Vector4& vector4)
{
    x = vector4.x;
    y = vector4.y;
}

//=============================Indexing Operators=============================//

//The "write" indexing operator.
float& Vector2::operator [] (int index)
{
    return *(&x + index);
}

//The "read" indexing operator.
const float& Vector2::operator [] (int index) const
{
    return *(&x + index);
}

//=====================Non-Modifying Arithmetic Operators=====================//

//The unary minus operator.
Vector2 Vector2::operator - () const
{
    return Vector2(-x, -y);
}

//The addition operator adds a given vector.
Vector2 Vector2::operator + (const Vector2& vector2) const
{
    return Vector2(x + vector2.x, y + vector2.y);
}

//The subtraction operator subtracts a given vector.
Vector2 Vector2::operator - (const Vector2& vector2) const
{
    return Vector2( x - vector2.x, y - vector2.y );
}

//The multiplication (by a constant) operator.
Vector2 Vector2::operator * (const float scalar) const
{
    return Vector2(scalar * x, scalar * y);
}

//The friend multiplication (by a constant) operator.
Vector2 operator * (const float scalar, const Vector2 &vector2)
{
    return vector2 * scalar;
}

//The multiplication (term-by-term product) operator.
Vector2 Vector2::operator * (const Vector2& vector2) const
{
    return Vector2(x * vector2.x, y * vector2.y);
}

//The division operator divides by a scalar.
Vector2 Vector2::operator / (const float scalar) const
{
    return Vector2(x / scalar, y / scalar);
}

//=======================Modifying Arithmetic Operators=======================//


//The addition assignment operator adds the given vector and stores the
//result.
Vector2& Vector2::operator += (const Vector2& vector2)
{
    x += vector2.x;
    y += vector2.y;
    return *this;
}

//The subtraction assignment operator subtracts the given vector and stores
//the result.
Vector2& Vector2::operator -= (const Vector2& vector2)
{
    x -= vector2.x;
    y -= vector2.y;
    return *this;
}

//The multiplication assignment operator multiplies the vector by a
//constant and stores the result.
Vector2& Vector2::operator *= (const float scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}

//The multiplication assignment operator multiplies the vector by the given
//vector term-by-term and stores the result.
Vector2& Vector2::operator *= (const Vector2& vector2)
{
    x *= vector2.x;
    y *= vector2.y;
    return *this;
}

//The division assignment operator divides the vector by a constant and
//stores the result.
Vector2& Vector2::operator /= (const float scalar)
{
    x /= scalar;
    y /= scalar;
    return *this;
}

//===========================Equality Operators===========================//

//The equality operator checks if the given vector and this vector contain
//the same components.
bool Vector2::operator == (const Vector2& vector2)
{
    return x == vector2.x && y == vector2.y;
}

//The inequality operator checks if the given vector and this vector
//contain the same components.
bool Vector2::operator != (const Vector2& vector2)
{
    return !(*this == vector2);
}

//===============================Cast Operators===============================//

//The cast operator casts the vector to an array of floats.
Vector2::operator const float* () const
{
    return static_cast<const float*>(&x);
}

//The cast operator casts the vector to an array of floats.
Vector2::operator float* ()
{
    return static_cast<float*>(&x);
}

//==============================Other Operators===============================//

//This method computes the length.
float Vector2::length() const
{
    return std::sqrtf(x * x + y * y);
}

//This method normalizes the vector.
Vector2 Vector2::normalize()
{
    float length = this->length();
    
    x /= length;
    y /= length;
    
    return Vector2(x, y);
}

//This method calculates the dot product with another vector.
float Vector2::dot(const Vector2& vector2) const
{
    return x * vector2.x + y * vector2.y;
}
    
//===============================Other Methods================================//

//This method clears the entries all to 0.
void Vector2::clear()
{
    x = y = 0;
}

}