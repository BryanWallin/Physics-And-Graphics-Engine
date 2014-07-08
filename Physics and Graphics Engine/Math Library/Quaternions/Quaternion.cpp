//============================================================================//
//                                                                            //
//  Quaternion.cpp                                                            //
//                                                                            //
//  The Quaternion class is used to store attributes of a quaternion.         //
//  Quaternions are extremely useful for storing rotations and interpolating  //
//  between them.                                                             //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 01/19/2013 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#include "Quaternion.h"

namespace GraphicsEngine
{

Quaternion Quaternion::Slerp(const Quaternion &q1, const Quaternion &q2,
                        float t)
{
    float theta = degreesToRadians(Angle(q1, q2));
    
    return (q1 * sinf((1 - t) * theta) + q2 * sinf(t * theta)) / sinf(theta);
}

Quaternion Quaternion::Nlerp(const Quaternion &q1, const Quaternion &q2,
                             float t)
{
    Quaternion result = q1 * (1 - t) + q2 * t;
    result.normalize();
    
    return result;
}

float Quaternion::Angle(const Quaternion &q1, const Quaternion &q2)
{
    float dotProduct = Dot(q1, q2);
    
    if(dotProduct > 1)
        dotProduct = 1;
    else if(dotProduct < -1)
        dotProduct = -1;
    
    return radiansToDegrees(acosf(dotProduct));
}

float Quaternion::Dot(const Quaternion &q1, const Quaternion &q2)
{
    return q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;
}

//============================================================================//
//===========================Public Static Methods============================//
//============================================================================//

//==================================Identity==================================//

//This method makes the identity quaternion.
Quaternion Quaternion::Identity()
{
    return Quaternion();
}

//==================================Rotating==================================//

//This method makes a quaternion from an axis-angle input.
Quaternion Quaternion::AngleAxis(float degrees, const Vector3 &axis)
{
    float radiansHalved = degreesToRadians(degrees) / 2;
    float cos = cosf(radiansHalved);
    float sin = sinf(radiansHalved);
    
    Vector3 axisNormalized = axis;
    axisNormalized.normalize();
    
    return Quaternion(cos, axisNormalized.x * sin, axisNormalized.y * sin,
                      axisNormalized.z * sin);
}

//This method makes a quaternion from a Matrix3 rotation.
Quaternion Quaternion::Rotation(const Matrix3 &matrix3)
{
    //Getting the trace of the rotation matrix.
    float trace = matrix3.trace();
    
    //Case 1: The trace is positive.
    if(trace > 0)
    {
        float root = sqrtf(trace + 1);
        float inverseDenominator = 0.5f / root;
        
        return Quaternion(0.5f * root,
                          (matrix3[1][2] - matrix3[2][1]) * inverseDenominator,
                          (matrix3[2][0] - matrix3[0][2]) * inverseDenominator,
                          (matrix3[0][1] - matrix3[1][0]) * inverseDenominator);
    }
    //Case 2a: The first component of the diagonal is the max.
    else if(matrix3[0][0] >= matrix3[1][1] && matrix3[1][1] >= matrix3[2][2])
    {
        float root = sqrtf(matrix3[0][0] - matrix3[1][1] - matrix3[2][2] + 1);
        float inverseDenominator = 0.5f / root;
        
        return Quaternion((matrix3[1][2] - matrix3[2][1]) * inverseDenominator,
                          0.5f * root,
                          (matrix3[0][1] + matrix3[1][0]) * inverseDenominator,
                          (matrix3[0][2] + matrix3[2][0]) * inverseDenominator);
    }
    //Case 2b: The second component is the max.
    else if(matrix3[1][1] >= matrix3[2][2] && matrix3[2][2] >= matrix3[0][0])
    {
        float root = sqrtf(matrix3[1][1] - matrix3[2][2] - matrix3[0][0] + 1);
        float inverseDenominator = 0.5f / root;
        
        return Quaternion((matrix3[2][0] - matrix3[0][2]) * inverseDenominator,
                          (matrix3[0][1] + matrix3[1][0]) * inverseDenominator,
                          0.5f * root,
                          (matrix3[1][2] + matrix3[2][1]) * inverseDenominator);
    }
    //Case 2c: The third component is the max.
    else
    {
        float root = sqrtf(matrix3[2][2] - matrix3[0][0] - matrix3[1][1] + 1);
        float inverseDenominator = 0.5f / root;
        
        return Quaternion((matrix3[0][1] - matrix3[1][0]) * inverseDenominator,
                          (matrix3[0][2] + matrix3[2][0]) * inverseDenominator,
                          (matrix3[1][2] + matrix3[2][1]) * inverseDenominator,
                          0.5f * root);
    }
}

//This method makes a quaternion from a Matrix4 rotation.
Quaternion Quaternion::Rotation(const Matrix4 &matrix4)
{
    //Converting the matrix4 into a matrix3.
    Matrix3 matrix3 = Matrix3(matrix4);
    
    return Rotation(matrix3);
}

//============================================================================//
//=============================Public Methods=================================//
//============================================================================//

//================================Constructors================================//

//The default constructor.
Quaternion::Quaternion()
{
    w = 1;
    x = y = z = 0;
}

//The complete constructor.
Quaternion::Quaternion(float w, float x, float y, float z)
{
    this->w = w;
    this->x = x;
    this->y = y;
    this->z = z;
}

//The axis/angle constructor.
Quaternion::Quaternion(float degrees, const Vector3 &axis)
{
    float radiansHalved = degreesToRadians(degrees) / 2;
    float cos = cosf(radiansHalved);
    float sin = sinf(radiansHalved);
    
    Vector3 axisNormalized = axis;
    axisNormalized.normalize();
    
    w = cos;
    x = axisNormalized.x * sin;
    y = axisNormalized.y * sin;
    z = axisNormalized.z * sin;
    
    //this->normalize();
}

//The copy constructor.
Quaternion::Quaternion(const Quaternion& quaternion)
{
    w = quaternion.w;
    x = quaternion.x;
    y = quaternion.y;
    z = quaternion.z;
}

//=====================Non-Modifying Arithmetic Operators=====================//

//The unary minus operator.
Quaternion Quaternion::operator - () const
{
    return Quaternion(-w, -x, -y, -z);
}

//The addition operator adds a given quaternion.
Quaternion Quaternion::operator + (const Quaternion& quaternion) const
{
    return Quaternion(w + quaternion.w, x + quaternion.x, y + quaternion.y,
                      z + quaternion.z);
}

//The subtraction operator subtracts a given quaternion.
Quaternion Quaternion::operator - (const Quaternion& quaternion) const
{
    return Quaternion(w - quaternion.w, x - quaternion.x, y - quaternion.y,
                      z - quaternion.z);
}

//The multiplication (by a constant) operator.
Quaternion Quaternion::operator * (const float scalar) const
{
    return Quaternion(w * scalar, x * scalar, y * scalar, z * scalar);
}

//The multiplication (by another quaternion) operator.
Quaternion Quaternion::operator * (const Quaternion& quaternion) const
{
    return Quaternion(w * quaternion.w - x * quaternion.x - y * quaternion.y -
                      z * quaternion.z,
                      w * quaternion.x + x * quaternion.w + y * quaternion.z -
                      z * quaternion.y,
                      w * quaternion.y - x * quaternion.z + y * quaternion.w +
                      z * quaternion.x,
                      w * quaternion.z + x * quaternion.y - y * quaternion.x +
                      z * quaternion.w);
}

//The division operator divides by a scalar.
Quaternion Quaternion::operator / (const float scalar) const
{
    return Quaternion(w / scalar, x / scalar, y / scalar, z / scalar);
}

//=======================Modifying Arithmetic Operators=======================//

//The addition assignment operator adds the given quaternion and stores the
//result.
Quaternion& Quaternion::operator += (const Quaternion& quaternion)
{
    w += quaternion.w;
    x += quaternion.x;
    y += quaternion.y;
    z += quaternion.z;
    
    return *this;
}

//The subtraction assignment operator subtracts the given quaternion and
//stores the result.
Quaternion& Quaternion::operator -= (const Quaternion& quaternion)
{
    w -= quaternion.w;
    x -= quaternion.x;
    y -= quaternion.y;
    z -= quaternion.z;
    
    return *this;
}

//The multiplication assignment operator multiplies the quaternion by a
//constant and stores the result.
Quaternion& Quaternion::operator *= (const float scalar)
{
    w *= scalar;
    x *= scalar;
    y *= scalar;
    z *= scalar;
    
    return *this;
}

//The multiplication assignment operator multiplies the quaternion by the
//given quaternion term-by-term and stores the result.
Quaternion& Quaternion::operator *= (const Quaternion& quaternion)
{
     float newW = w * quaternion.w - x * quaternion.x - y * quaternion.y -
        z * quaternion.z;
     float newX = w * quaternion.x + x * quaternion.w + y * quaternion.z -
        z * quaternion.y;
     float newY = w * quaternion.y - x * quaternion.z + y * quaternion.w -
        z * quaternion.x;
     float newZ = w * quaternion.z + x * quaternion.y - y * quaternion.x -
        z * quaternion.w;
    
    w = newW;
    x = newX;
    y = newY;
    z = newZ;
    
    return *this;
}

//The division assignment operator divides the quaternion by a constant and
//stores the result.
Quaternion& Quaternion::operator /= (const float scalar)
{
    w /= scalar;
    x /= scalar;
    y /= scalar;
    z /= scalar;
    
    return *this;
}

//=============================Equality Operators=============================//

//The equality operator checks if the given quaternion and this quaternion
//contain the same components.
bool Quaternion::operator == (const Quaternion& quaternion) const
{
    return (w == quaternion.w && x == quaternion.x && y == quaternion.y &&
            z == quaternion.z);
}

//The inequality operator checks if the given quaternion and this
//quaternion contain the same components.
bool Quaternion::operator != (const Quaternion& quaternion) const
{
    return !(*this == quaternion);
}

//==============================Other Operators===============================//

//This method returns the length of the quaternion.
float Quaternion::length() const
{
    return sqrtf(w * w + x * x + y * y + z * z);
}

//This method normalizes the quaternion.
void Quaternion::normalize()
{
    float length = this->length();
    
    w /= length;
    x /= length;
    y /= length;
    z /= length;
}

////This method returns the conjugate of this quaternion.
//Quaternion Quaternion::conjugate()
//{
//    return Quaternion();
//}
//
//This method returns the inverse of this quaternion.
Quaternion Quaternion::inverse() const
{
    return Quaternion(w, -x, -y, -z);
}

}