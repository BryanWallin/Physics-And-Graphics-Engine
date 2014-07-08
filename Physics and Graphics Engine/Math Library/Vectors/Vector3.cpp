//============================================================================//
//                                                                            //
//  Vector3.cpp                                                               //
//                                                                            //
//  The Vector3 class is used to store attributes of a vector of length 3.    //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 01/19/2013 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#include "Vector3.h"

namespace GraphicsEngine
{

//============================================================================//
//=============================Public Methods=================================//
//============================================================================//

//================================Constructors================================//

//The complete constructor.
Vector3::Vector3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

//The Vector2 copy constructor.
Vector3::Vector3(const Vector2& vector2, float z)
{
    x = vector2.x;
    y = vector2.y;
    z = z;
}

//The Vector3 copy constructor.
Vector3::Vector3(const Vector3& vector3)
{
    x = vector3.x;
    y = vector3.y;
    z = vector3.z;
}

//The Vector4 copy constructor.
Vector3::Vector3(const Vector4& vector4)
{
    x = vector4.x;
    y = vector4.y;
    z = vector4.z;
}

//=============================Indexing Operators=============================//

//The "write" indexing operator.
float& Vector3::operator [] (int index)
{
    return *(&x + index);
}

//The "read" indexing operator.
const float& Vector3::operator [] (int index) const
{
    return *(&x + index);
}

//=====================Non-Modifying Arithmetic Operators=====================//

//The unary minus operator.
Vector3 Vector3::operator - () const
{
    return Vector3(-x, -y, -z);
}

//The addition operator adds a given vector.
Vector3 Vector3::operator + (const Vector3& vector3) const
{
    return Vector3(x + vector3.x, y + vector3.y, z + vector3.z);
}

//The subtraction operator subtracts a given vector.
Vector3 Vector3::operator - (const Vector3& vector3) const
{
    return Vector3(x - vector3.x, y - vector3.y, z - vector3.z);
}

//The multiplication (by a constant) operator.
Vector3 Vector3::operator * (const float scalar) const
{
    return Vector3(scalar * x, scalar * y, scalar * z);
}

//The friend multiplication (by a constant) operator.
Vector3 operator * (const float scalar, const Vector3 &vector3)
{
    return vector3 * scalar;
}

//The multiplication (term-by-term product) operator.
Vector3 Vector3::operator * (const Vector3& vector3) const
{
    return Vector3(x * vector3.x, y * vector3.y, z * vector3.z);
}

//The division operator divides by a scalar.
Vector3 Vector3::operator / (const float scalar) const
{
    return Vector3(x / scalar, y / scalar, z / scalar);
}

//=======================Modifying Arithmetic Operators=======================//


//The addition assignment operator adds the given vector and stores the
//result.
Vector3& Vector3::operator += (const Vector3& vector3)
{
    x += vector3.x;
    y += vector3.y;
    z += vector3.z;
    return *this;
}

//The subtraction assignment operator subtracts the given vector and stores
//the result.
Vector3& Vector3::operator -= (const Vector3& vector3)
{
    x -= vector3.x;
    y -= vector3.y;
    z -= vector3.z;
    return *this;
}

//The multiplication assignment operator multiplies the vector by a
//constant and stores the result.
Vector3& Vector3::operator *= (const float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

//The multiplication assignment operator multiplies the vector by the given
//vector term-by-term and stores the result.
Vector3& Vector3::operator *= (const Vector3& vector3)
{
    x *= vector3.x;
    y *= vector3.y;
    z *= vector3.z;
    return *this;
}

//The division assignment operator divides the vector by a constant and
//stores the result.
Vector3& Vector3::operator /= (const float scalar)
{
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

//===========================Equality Operators===========================//

//The equality operator checks if the given vector and this vector contain
//the same components.
bool Vector3::operator == (const Vector3& vector3)
{
    return x == vector3.x && y == vector3.y && z == vector3.z;
}

//The inequality operator checks if the given vector and this vector
//contain the same components.
bool Vector3::operator != (const Vector3& vector3)
{
    return !(*this == vector3);
}

//===============================Cast Operators===============================//

//The cast operator casts the vector to an array of floats.
Vector3::operator const float* () const
{
    return static_cast<const float*>(&x);
}

//The cast operator casts the vector to an array of floats.
Vector3::operator float* ()
{
    return static_cast<float*>(&x);
}

//==============================Other Operators===============================//

//This method computes the length.
float Vector3::length() const
{
    return std::sqrtf(x * x + y * y + z * z);
}

//This method normalizes the vector.
Vector3 Vector3::normalize()
{
    float length = this->length();
    
    x /= length;
    y /= length;
    z /= length;
    
    return Vector3(x, y, z);
}

//This method calculates the dot product with another vector.
float Vector3::dot(const Vector3& vector3) const
{
    return x * vector3.x + y * vector3.y + z * vector3.z;
}

//This method calculates the cross product with another vector.
Vector3 Vector3::cross(const Vector3& vector3) const
{
    float crossX, crossY, crossZ;
    
    crossX = y * vector3.z - vector3.y * z;
    crossY = vector3.x * z - x * vector3.z;
    crossZ = x * vector3.y - vector3.x * y;
    
    return Vector3(crossX, crossY, crossZ);
}
    
//===============================Other Methods================================//

//This method clears the entries all to 0.
void Vector3::clear()
{
    x = y = z = 0;
}

}