//============================================================================//
//                                                                            //
//  Vector4.cpp                                                               //
//                                                                            //
//  The Vector4 class is used to store attributes of a vector of length 4.    //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 02/08/2014 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#include "Vector4.h"

namespace GraphicsEngine
{

//============================================================================//
//=============================Public Methods=================================//
//============================================================================//

//================================Constructors================================//

//The complete constructor.
Vector4::Vector4(float x, float y, float z, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

//The Vector2 copy constructor.
Vector4::Vector4(const Vector2& vector2, float z, float w)
{
    x = vector2.x;
    y = vector2.y;
    z = z;
    w = w;
}

//The Vector3 copy constructor.
Vector4::Vector4(const Vector3& vector3, float w)
{
    x = vector3.x;
    y = vector3.y;
    z = vector3.z;
    w = w;
}

//The Vector4 copy constructor.
Vector4::Vector4(const Vector4& vector4)
{
    x = vector4.x;
    y = vector4.y;
    z = vector4.z;
    w = vector4.w;
}

//=============================Indexing Operators=============================//

//The "write" indexing operator.
float& Vector4::operator [] (int index)
{
    return *(&x + index);
}

//The "read" indexing operator.
const float& Vector4::operator [] (int index) const
{
    return *(&x + index);
}

//=====================Non-Modifying Arithmetic Operators=====================//

//The unary minus operator.
Vector4 Vector4::operator - () const
{
    return Vector4(-x, -y, -z, -w);
}

//The addition operator adds a given vector.
Vector4 Vector4::operator + (const Vector4& vector4) const
{
    return Vector4(x + vector4.x, y + vector4.y, z + vector4.z, w + vector4.w);
}

//The subtraction operator subtracts a given vector.
Vector4 Vector4::operator - (const Vector4& vector4) const
{
    return Vector4(x - vector4.x, y - vector4.y, z - vector4.z, w - vector4.w);
}

//The multiplication (by a constant) operator.
Vector4 Vector4::operator * (const float scalar) const
{
    return Vector4(scalar * x, scalar * y, scalar * z, scalar * w);
}

//The friend multiplication (by a constant) operator.
Vector4 operator * (const float scalar, const Vector4 &vector4)
{
    return vector4 * scalar;
}

//The multiplication (term-by-term product) operator.
Vector4 Vector4::operator * (const Vector4& vector4) const
{
    return Vector4(x * vector4.x, y * vector4.y, z * vector4.z, w * vector4.w);
}

//The division operator divides by a scalar.
Vector4 Vector4::operator / (const float scalar) const
{
    return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
}

//=======================Modifying Arithmetic Operators=======================//


//The addition assignment operator adds the given vector and stores the
//result.
Vector4& Vector4::operator += (const Vector4& vector4)
{
    x += vector4.x;
    y += vector4.y;
    z += vector4.z;
    w += vector4.w;
    return *this;
}

//The subtraction assignment operator subtracts the given vector and stores
//the result.
Vector4& Vector4::operator -= (const Vector4& vector4)
{
    x -= vector4.x;
    y -= vector4.y;
    z -= vector4.z;
    w -= vector4.w;
    return *this;
}

//The multiplication assignment operator multiplies the vector by a
//constant and stores the result.
Vector4& Vector4::operator *= (const float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
    return *this;
}

//The multiplication assignment operator multiplies the vector by the given
//vector term-by-term and stores the result.
Vector4& Vector4::operator *= (const Vector4& vector4)
{
    x *= vector4.x;
    y *= vector4.y;
    z *= vector4.z;
    w *= vector4.w;
    return *this;
}

//The division assignment operator divides the vector by a constant and
//stores the result.
Vector4& Vector4::operator /= (const float scalar)
{
    x /= scalar;
    y /= scalar;
    z /= scalar;
    w /= scalar;
    return *this;
}

//===========================Equality Operators===========================//

//The equality operator checks if the given vector and this vector contain
//the same components.
bool Vector4::operator == (const Vector4& vector4)
{
    return x == vector4.x && y == vector4.y && z == vector4.z && w == vector4.w;
}

//The inequality operator checks if the given vector and this vector
//contain the same components.
bool Vector4::operator != (const Vector4& vector4)
{
    return !(*this == vector4);
}

//===============================Cast Operators===============================//

//The cast operator casts the vector to an array of floats.
Vector4::operator const float* () const
{
    return static_cast<const float*>(&x);
}

//The cast operator casts the vector to an array of floats.
Vector4::operator float* ()
{
    return static_cast<float*>(&x);
}

//==============================Other Operators===============================//

//This method computes the length.
float Vector4::length() const
{
    return std::sqrtf(x * x + y * y + z * z + w * w);
}

//This method normalizes the vector.
Vector4 Vector4::normalize()
{
    float length = this->length();
    
    x /= length;
    y /= length;
    z /= length;
    w /= length;
    
    return Vector4(x, y, z, w);
}

//This method calculates the dot product with another vector.
float Vector4::dot(const Vector4& vector4) const
{
    return x * vector4.x + y * vector4.y + z * vector4.z + w * vector4.w;
}
    
//===============================Other Methods================================//

//This method clears the entries all to 0.
void Vector4::clear()
{
    x = y = z = w = 0;
}

}