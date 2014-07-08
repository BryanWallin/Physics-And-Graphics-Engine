//============================================================================//
//                                                                            //
//  Matrix3.cpp                                                               //
//                                                                            //
//  The Matrix3 class is used to store attributes of a matrix of size 3x3.    //
//  Note that this class stores the matrix data in column-major format.       //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 03/18/2014 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#include "Matrix3.h"

namespace GraphicsEngine
{

//============================================================================//
//===========================Public Static  Methods===========================//
//============================================================================//

//==================================Identity==================================//

//This method makes the identity matrix.
Matrix3 Matrix3::Identity()
{
    return Matrix3(1, 0, 0,
                   0, 1, 0,
                   0, 0, 1);
}
    
//==================================Rotating==================================//

//This method makes a rotation matrix that rotates about the x axis.
Matrix3 Matrix3::RotationX(float degrees)
{
    float degreesInRadians = degreesToRadians(degrees);
    
    float sX = std::sinf(degreesInRadians);
    float cX = std::cosf(degreesInRadians);
    
    return Matrix3(1, 0,   0,
                   0, cX, -sX,
                   0, sX,  cX);
}

//This method makes a rotation matrix that rotates about the y axis.
Matrix3 Matrix3::RotationY(float degrees)
{
    float degreesInRadians = degreesToRadians(degrees);
    
    float sY = std::sinf(degreesInRadians);
    float cY = std::cosf(degreesInRadians);
    
    return Matrix3( cY, 0, sY,
                    0,  1, 0,
                   -sY, 0, cY);
}

//This method makes a rotation matrix that rotates about the z axis.
Matrix3 Matrix3::RotationZ(float degrees)
{
    float degreesInRadians = degreesToRadians(degrees);
    
    float sZ = std::sinf(degreesInRadians);
    float cZ = std::cosf(degreesInRadians);
    
    return Matrix3(cZ, -sZ, 0,
                   sZ,  cZ, 0,
                   0,   0,  1);
}

//This method makes a rotation matrix that rotates around the x axis,
//the y axis, and the z axis in that order.
Matrix3 Matrix3::EulerXYZ(float xDegrees, float yDegrees, float zDegrees)
{
    float xDegreesInRadians = degreesToRadians(xDegrees);
    float yDegreesInRadians = degreesToRadians(yDegrees);
    float zDegreesInRadians = degreesToRadians(zDegrees);
    
    float sX = std::sinf(xDegreesInRadians);
    float cX = std::cosf(xDegreesInRadians);
    float sY = std::sinf(yDegreesInRadians);
    float cY = std::cosf(yDegreesInRadians);
    float sZ = std::sinf(zDegreesInRadians);
    float cZ = std::cosf(zDegreesInRadians);
    
    return Matrix3( cY * cZ, cZ * sX * sY - cX * sZ, cX * cZ * sY + sX * sZ,
                    cY * sZ, cX * cZ + sX * sY * sZ, cX * sY * sZ - cZ * sX,
                   -sY,      cY * sX,                cX * cY);
}

//This method makes a rotation matrix that rotates around the x axis,
//the y axis, and the z axis in that order.
Matrix3 Matrix3::EulerXYZ(const Vector3 &vector3)
{
    return EulerXYZ(vector3.x, vector3.y, vector3.z);
}

//This method makes a rotation matrix that rotates around the x axis,
//the z axis, and the y axis in that order.
Matrix3 Matrix3::EulerXZY(float xDegrees, float yDegrees, float zDegrees)
{
    float xDegreesInRadians = degreesToRadians(xDegrees);
    float yDegreesInRadians = degreesToRadians(yDegrees);
    float zDegreesInRadians = degreesToRadians(zDegrees);
    
    float sX = std::sinf(xDegreesInRadians);
    float cX = std::cosf(xDegreesInRadians);
    float sY = std::sinf(yDegreesInRadians);
    float cY = std::cosf(yDegreesInRadians);
    float sZ = std::sinf(zDegreesInRadians);
    float cZ = std::cosf(zDegreesInRadians);
    
    return Matrix3( cY * cZ, sX * sY - cX * cY * sZ,  cX * sY + cY * sX * sZ,
                    sZ,      cX * cZ,                -cZ * sX,
                   -cZ * sY, cY * sX + cX * sY * sZ,  cX * cY - sX * sY * sZ);
}

//This method makes a rotation matrix that rotates around the x axis,
//the z axis, and the y axis in that order.
Matrix3 Matrix3::EulerXZY(const Vector3 &vector3)
{
    return EulerXZY(vector3.x, vector3.y, vector3.z);
}

//This method makes a rotation matrix that rotates around the y axis,
//the x axis, and the z axis in that order.
Matrix3 Matrix3::EulerYXZ(float xDegrees, float yDegrees, float zDegrees)
{
    float xDegreesInRadians = degreesToRadians(xDegrees);
    float yDegreesInRadians = degreesToRadians(yDegrees);
    float zDegreesInRadians = degreesToRadians(zDegrees);
    
    float sX = std::sinf(xDegreesInRadians);
    float cX = std::cosf(xDegreesInRadians);
    float sY = std::sinf(yDegreesInRadians);
    float cY = std::cosf(yDegreesInRadians);
    float sZ = std::sinf(zDegreesInRadians);
    float cZ = std::cosf(zDegreesInRadians);
    
    return Matrix3( cY * cZ - sX * sY * sZ, -cX * sZ, cZ * sY + cY * sX * sZ,
                    cZ * sX * sY + cY * sZ,  cX * cZ, sY * sZ - cY * cZ * sX,
                   -cX * sY,                 sX,      cX * cY);
}

//This method makes a rotation matrix that rotates around the y axis,
//the x axis, and the z axis in that order.
Matrix3 Matrix3::EulerYXZ(const Vector3 &vector3)
{
    return EulerYXZ(vector3.x, vector3.y, vector3.z);
}

//This method makes a rotation matrix that rotates around the y axis,
//the z axis, and the x axis in that order.
Matrix3 Matrix3::EulerYZX(float xDegrees, float yDegrees, float zDegrees)
{
    float xDegreesInRadians = degreesToRadians(xDegrees);
    float yDegreesInRadians = degreesToRadians(yDegrees);
    float zDegreesInRadians = degreesToRadians(zDegrees);
    
    float sX = std::sinf(xDegreesInRadians);
    float cX = std::cosf(xDegreesInRadians);
    float sY = std::sinf(yDegreesInRadians);
    float cY = std::cosf(yDegreesInRadians);
    float sZ = std::sinf(zDegreesInRadians);
    float cZ = std::cosf(zDegreesInRadians);
    
    return Matrix3(cY * cZ,                -sZ,      cZ * sY,
                   sX * sY + cX * cY * sZ,  cX * cZ, cX * sY * sZ - cY * sX,
                   cY * sX * sZ - cX * sY,  cZ * sX, cX * cY + sX * sY * sZ);
}

//This method makes a rotation matrix that rotates around the y axis,
//the z axis, and the x axis in that order.
Matrix3 Matrix3::EulerYZX(const Vector3 &vector3)
{
    return EulerYZX(vector3.x, vector3.y, vector3.z);
}

//This method makes a rotation matrix that rotates around the z axis,
//the x axis, and the y axis in that order.
Matrix3 Matrix3::EulerZXY(float xDegrees, float yDegrees, float zDegrees)
{
    float xDegreesInRadians = degreesToRadians(xDegrees);
    float yDegreesInRadians = degreesToRadians(yDegrees);
    float zDegreesInRadians = degreesToRadians(zDegrees);
    
    float sX = std::sinf(xDegreesInRadians);
    float cX = std::cosf(xDegreesInRadians);
    float sY = std::sinf(yDegreesInRadians);
    float cY = std::cosf(yDegreesInRadians);
    float sZ = std::sinf(zDegreesInRadians);
    float cZ = std::cosf(zDegreesInRadians);
    
    return Matrix3(cY * cZ + sX * sY * sZ, cZ * sX * sY - cY * sZ,  cX * sY,
                   cX * sZ,                cX * cZ,                -sX,
                   cY * sX * sZ - cZ * sY, cY * cZ * sX + sY * sZ,  cX * cY);
}

//This method makes a rotation matrix that rotates around the z axis,
//the x axis, and the y axis in that order.
Matrix3 Matrix3::EulerZXY(const Vector3 &vector3)
{
    return EulerZXY(vector3.x, vector3.y, vector3.z);
}

//This method makes a rotation matrix that rotates around the z axis,
//the y axis, and the x axis in that order.
Matrix3 Matrix3::EulerZYX(float xDegrees, float yDegrees, float zDegrees)
{
    float xDegreesInRadians = degreesToRadians(xDegrees);
    float yDegreesInRadians = degreesToRadians(yDegrees);
    float zDegreesInRadians = degreesToRadians(zDegrees);

    float sX = std::sinf(xDegreesInRadians);
    float cX = std::cosf(xDegreesInRadians);
    float sY = std::sinf(yDegreesInRadians);
    float cY = std::cosf(yDegreesInRadians);
    float sZ = std::sinf(zDegreesInRadians);
    float cZ = std::cosf(zDegreesInRadians);

    return Matrix3(cY * cZ,                -cY * sZ,                 sY,
                   cZ * sX * sY + cX * sZ,  cX * cZ - sX * sY * sZ, -cY * sX,
                   sX * sZ - cX * cZ * sY,  cZ * sX + cX * sY * sZ,  cX * cY);
}

//This method makes a rotation matrix that rotates around the z axis,
//the y axis, and the x axis in that order.
Matrix3 Matrix3::EulerZYX(const Vector3 &vector3)
{
    return EulerZYX(vector3.x, vector3.y, vector3.z);
}
    
//==================================Scaling===================================//

//This method makes a scale matrix that scales in x, y, and z.
Matrix3 Matrix3::Scale(float x, float y, float z)
{
    return Matrix3(x, 0, 0,
                   0, y, 0,
                   0, 0, z);
}

//This method makes a scale matrix that scales in x, y, and z.
Matrix3 Matrix3::Scale(const Vector3 &vector3)
{
    return Scale(vector3.x, vector3.y, vector3.z);
}

//============================================================================//
//=============================Public Methods=================================//
//============================================================================//

//================================Constructors================================//

//The default constructor.  It creates the identity matrix.
Matrix3::Matrix3()
{
    m_Matrix[0] = Vector3(1, 0, 0);
    m_Matrix[1] = Vector3(0, 1, 0);
    m_Matrix[2] = Vector3(0, 0, 1);
}

//The diagonal constructor.
Matrix3::Matrix3(float entry00, float entry11, float entry22)
{
    m_Matrix[0] = Vector3(entry00, 0,       0);
    m_Matrix[1] = Vector3(0,       entry11, 0);
    m_Matrix[2] = Vector3(0,       0,       entry22);
}

//The diagonal constructor.
Matrix3::Matrix3(const Vector3 &diagonal)
{
    m_Matrix[0] = Vector3(diagonal.x, 0,          0);
    m_Matrix[1] = Vector3(0,          diagonal.y, 0);
    m_Matrix[2] = Vector3(0,          0,          diagonal.z);
}

//The single-entry constructor.
Matrix3::Matrix3(float allEntries)
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
            m_Matrix[i][j] = allEntries;
    }
}

//The float constructor.
Matrix3::Matrix3(float entry00, float entry01, float entry02,
        float entry10, float entry11, float entry12,
        float entry20, float entry21, float entry22)
{
    m_Matrix[0] = Vector3(entry00, entry10, entry20);
    m_Matrix[1] = Vector3(entry01, entry11, entry21);
    m_Matrix[2] = Vector3(entry02, entry12, entry22);
}

//The vector constructor.
Matrix3::Matrix3(const Vector3& column1, const Vector3& column2,
                 const Vector3& column3)
{
    m_Matrix[0] = column1;
    m_Matrix[1] = column2;
    m_Matrix[2] = column3;
}

//The copy constructor.
Matrix3::Matrix3(const Matrix3& matrix3)
{
    m_Matrix[0] = matrix3[0];
    m_Matrix[1] = matrix3[1];
    m_Matrix[2] = matrix3[2];
}

//The Matrix2 copy constructor.
Matrix3::Matrix3(const Matrix2& matrix2)
{
    m_Matrix[0] = Vector3(matrix2[0]);
    m_Matrix[1] = Vector3(matrix2[1]);
    m_Matrix[2] = Vector3(0, 0, 0);
}

//The copy constructor.
Matrix3::Matrix3(const Matrix4& matrix4)
{
    m_Matrix[0] = Vector3(matrix4[0]);
    m_Matrix[1] = Vector3(matrix4[1]);
    m_Matrix[2] = Vector3(matrix4[2]);
}

//The Quaternion conversion constructor.
Matrix3::Matrix3(const Quaternion& q)
{
    m_Matrix[0] = Vector3(1.0f - 2.0f * q.y * q.y - 2.0f * q.z * q.z,
                          2.0f * q.x * q.y + 2.0f * q.z * q.w,
                          2.0f * q.x * q.z - 2.0f * q.y * q.w);
    m_Matrix[1] = Vector3(2.0f * q.x * q.y - 2.0f * q.z * q.w,
                          1.0f - 2.0f * q.x * q.x - 2.0f * q.z * q.z,
                          2.0f * q.y * q.z + 2.0f * q.x * q.w);
    m_Matrix[2] = Vector3(2.0f * q.x * q.z + 2.0f * q.y * q.w,
                          2.0f * q.y * q.z - 2.0f * q.x * q.w,
                          1.0f - 2.0f * q.x * q.x - 2.0f * q.y * q.y);
}

//=============================Indexing Operators=============================//

//The "write" indexing operator.
Vector3& Matrix3::operator [] (int i)
{
    return m_Matrix[i];
}

//The "read" indexing operator.
const Vector3& Matrix3::operator [] (int i) const
{
    return m_Matrix[i];
}

//=====================Non-Modifying Arithmetic Operators=====================//

//The unary minus operator.
Matrix3 Matrix3::operator - () const
{
    return Matrix3(-m_Matrix[0], -m_Matrix[1], -m_Matrix[2]);
}

//The addition operator adds a given matrix.
Matrix3 Matrix3::operator + (const Matrix3& matrix3) const
{
    return Matrix3(m_Matrix[0] + matrix3[0], m_Matrix[1] + matrix3[1],
                   m_Matrix[2] + matrix3[2]);
}

//The subtraction operator subtracts a given matrix.
Matrix3 Matrix3::operator - (const Matrix3& matrix3) const
{
    return Matrix3(m_Matrix[0] - matrix3[0], m_Matrix[1] - matrix3[1],
                   m_Matrix[2] - matrix3[2]);
}

//The multiplication (by a constant) operator.
Matrix3 Matrix3::operator * (const float scalar) const
{
    return Matrix3(m_Matrix[0] * scalar, m_Matrix[1] * scalar,
                   m_Matrix[2] * scalar);
}

//The multiplication operator.
Matrix3 Matrix3::operator * (const Matrix3& matrix3) const
{
    Matrix3 result = Matrix3(0.0f);
    
    for(int column = 0; column < 3; column++)
    {
        for(int row = 0; row < 3; row++)
        {
            for(int entry = 0; entry < 3; entry++)
                result[column][row] +=
                    m_Matrix[entry][row] * matrix3[column][entry];
        }
    }
    
    return result;
}
    
//The multiplication (by a Vector3) operator.
Vector3 Matrix3::operator * (const Vector3& vector3) const
{
    Vector3 result = Vector3(0, 0, 0);
    
    for(int row = 0; row < 3; row++)
    {
        for(int entry = 0; entry < 3; entry++)
            result[row] += m_Matrix[entry][row] * vector3[entry];
    }
    
    return result;
}

//The division operator divides by a scalar.
Matrix3 Matrix3::operator / (const float scalar) const
{
    return Matrix3(m_Matrix[0] / scalar, m_Matrix[1] / scalar,
                   m_Matrix[2] / scalar);
}

//=======================Modifying Arithmetic Operators=======================//

//The addition assignment operator adds the given matrix and stores the
//result.
Matrix3& Matrix3::operator += (const Matrix3& matrix3)
{
    m_Matrix[0] += matrix3[0];
    m_Matrix[1] += matrix3[1];
    m_Matrix[2] += matrix3[2];
    return *this;
}

//The subtraction assignment operator subtracts the given matrix and stores
//the result.
Matrix3& Matrix3::operator -= (const Matrix3& matrix3)
{
    m_Matrix[0] -= matrix3[0];
    m_Matrix[1] -= matrix3[1];
    m_Matrix[2] -= matrix3[2];
    
    return *this;
}

//The multiplication assignment operator multiplies the matrix by a
//constant and stores the result.
Matrix3& Matrix3::operator *= (const float scalar)
{
    m_Matrix[0] *= scalar;
    m_Matrix[1] *= scalar;
    m_Matrix[2] *= scalar;
    
    return *this;
}

//The multiplication assignment operator multiplies the matrix by the given
//matrix and stores the result.
Matrix3& Matrix3::operator *= (const Matrix3& matrix3)
{
    Matrix3 result = Matrix3(0.0f);
    
    for(int column = 0; column < 3; column++)
    {
        for(int row = 0; row < 3; row++)
        {
            for(int entry = 0; entry < 3; entry++)
                result[column][row] +=
                m_Matrix[entry][row] * matrix3[column][entry];
        }
    }
    
    *this = result;
    
    return *this;
}

//The division assignment operator divides the matrix by a constant and
//stores the result.
Matrix3& Matrix3::operator /= (const float scalar)
{
    m_Matrix[0] /= scalar;
    m_Matrix[1] /= scalar;
    m_Matrix[2] /= scalar;
    
    return *this;
}

//===============================Cast Operators===============================//

//The cast operator casts the matrix to an array of floats.
Matrix3::operator const float* () const
{
    return static_cast<const float*>(&m_Matrix[0].x);
}

//The cast operator casts the matrix to an array of floats.
Matrix3::operator float* ()
{
    return static_cast<float*>(&m_Matrix[0].x);
}

//================================Euler Angles================================//

//This method extracts the XYZ Euler angles from the rotation matrix.
void Matrix3::extractEulerXYZ(float &xDegrees, float &yDegrees, float &zDegrees)
{
    //Diagram of the Euler XYZ Matrix:
    //
    // -------------------------------------------------------------
    //|  cY * cZ | cZ * sX * sY - cX * sZ | cX * cZ * sY + sX * sZ  |
    //|----------|------------------------|-------------------------|
    //|  cY * sZ | cX * cZ + sX * sY * sZ | cX * sY * sZ - cZ * sX  |
    //|----------|------------------------|-------------------------|
    //| -sY      | cY * sX                | cX * cY                 |
    // -------------------------------------------------------------
    
    //Case 1: -pi/2 < arcsin(sY) < pi/2 (or, -1 < sY < 1).  This solution is
    //unique.
    if(-1 + 0.000001f <= m_Matrix[0][2] && m_Matrix[0][2] <= 1 - 0.000001f)
    {
        xDegrees = radiansToDegrees(atan2f(m_Matrix[1][2], m_Matrix[2][2]));
        yDegrees = radiansToDegrees(asinf(-m_Matrix[0][2]));
        zDegrees = radiansToDegrees(atan2f(m_Matrix[0][1], m_Matrix[0][0]));
    }
    //Case 2: arcsin(sY) = pi/2 (or, sY = 1).  This solution is not unique, so
    //the z-angle is set to 0.
    else if(1 - 0.000001f < -m_Matrix[0][2] && -m_Matrix[0][2] < 1 + 0.000001f)
    {
        xDegrees = radiansToDegrees(atan2f(-m_Matrix[2][1], m_Matrix[1][1]));
        yDegrees = 90;
        zDegrees = 0;
    }
    //Case 3: arcsin(sY) = -pi/2 (or, sY = -1).  This solution is not unique,
    //so the z-angle is set to 0.
    else
    {
        xDegrees = radiansToDegrees(atan2f(-m_Matrix[2][1], m_Matrix[1][1]));
        yDegrees = -90;
        zDegrees = 0;
    }
}

//This method extracts the XYZ Euler angles from the rotation matrix.
void Matrix3::extractEulerXYZ(Vector3 &vector3)
{
    extractEulerXYZ(vector3.x, vector3.y, vector3.z);
}

//This method extracts the XZY Euler angles from the rotation matrix.
void Matrix3::extractEulerXZY(float &xDegrees, float &yDegrees, float &zDegrees)
{
    //Diagram of the Euler XZY Matrix:
    //
    // -------------------------------------------------------------
    //|  cY * cZ | sX * sY - cX * cY * sZ |  cX * sY + cY * sX * sZ |
    //|----------|------------------------|-------------------------|
    //|  sZ      | cX * cZ                | -cZ * sX                |
    //|----------|------------------------|-------------------------|
    //| -cZ * sY | cY * sX + cX * sY * sZ |  cX * cY - sX * sY * sZ |
    // -------------------------------------------------------------
    
    //Case 1: -pi/2 < arcsin(sZ) < pi/2 (or, -1 < sZ < 1).  This solution is
    //unique.
    if(-1 + 0.000001f <= m_Matrix[0][1] && m_Matrix[0][1] <= 1 - 0.000001f)
    {
        xDegrees = radiansToDegrees(atan2f(-m_Matrix[2][1], m_Matrix[1][1]));
        yDegrees = radiansToDegrees(atan2f(-m_Matrix[0][2], m_Matrix[0][0]));
        zDegrees = radiansToDegrees(asinf(m_Matrix[0][1]));
    }
    //Case 2: arcsin(sZ) = pi/2 (or, sZ = 1).  This solution is not unique, so
    //the y-angle is set to 0.
    else if(1 - 0.000001f < m_Matrix[0][1] && m_Matrix[0][1] < 1 + 0.000001f)
    {
        xDegrees = radiansToDegrees(atan2f(m_Matrix[1][2], m_Matrix[2][2]));
        yDegrees = 0;
        zDegrees = 90;
    }
    //Case 3: arcsin(sZ) = -pi/2 (or, sZ = -1).  This solution is not unique,
    //so the y-angle is set to 0.
    else
    {
        xDegrees = radiansToDegrees(atan2f(m_Matrix[1][2], m_Matrix[2][2]));
        yDegrees = 0;
        zDegrees = -90;
    }
}

//This method extracts the XZY Euler angles from the rotation matrix.
void Matrix3::extractEulerXZY(Vector3 &vector3)
{
    extractEulerXZY(vector3.x, vector3.y, vector3.z);
}

//This method extracts the YXZ Euler angles from the rotation matrix.
void Matrix3::extractEulerYXZ(float &xDegrees, float &yDegrees, float &zDegrees)
{
    //Diagram of the Euler YXZ Matrix:
    //
    // -------------------------------------------------------------
    //|  cY * cZ - sX * sY * sZ | -cX * sZ | cZ * sY + cY * sX * sZ |
    //|-------------------------|----------|------------------------|
    //|  cZ * sX * sY + cY * sZ |  cX * cZ | sY * sZ - cY * cZ * sX |
    //|-------------------------|----------|------------------------|
    //| -cX * sY                |  sX      | cX * cY                |
    // -------------------------------------------------------------
    
    //Case 1: -pi/2 < arcsin(sX) < pi/2 (or, -1 < sX < 1).  This solution is
    //unique.
    if(-1 + 0.000001f <= m_Matrix[1][2] && m_Matrix[1][2] <= 1 - 0.000001f)
    {
        xDegrees = radiansToDegrees(asinf(m_Matrix[1][2]));
        yDegrees = radiansToDegrees(atan2f(-m_Matrix[0][2], m_Matrix[2][2]));
        zDegrees = radiansToDegrees(atan2f(-m_Matrix[1][0], m_Matrix[1][1]));
    }
    //Case 2: arcsin(sX) = pi/2 (or, sX = 1).  This solution is not unique, so
    //the z-angle is set to 0.
    else if(1 - 0.000001f < m_Matrix[1][2] && m_Matrix[1][2] < 1 + 0.000001f)
    {
        xDegrees = 90;
        yDegrees = radiansToDegrees(atan2f(m_Matrix[2][0], m_Matrix[0][0]));
        zDegrees = 0;
    }
    //Case 3: arcsin(sX) = -pi/2 (or, sX = -1).  This solution is not unique,
    //so the z-angle is set to 0.
    else
    {
        xDegrees = -90;
        yDegrees = radiansToDegrees(atan2f(m_Matrix[2][0], m_Matrix[0][0]));;
        zDegrees = 0;
    }
}

//This method extracts the YXZ Euler angles from the rotation matrix.
void Matrix3::extractEulerYXZ(Vector3 &vector3)
{
    extractEulerYXZ(vector3.x, vector3.y, vector3.z);
}

//This method extracts the YZX Euler angles from the rotation matrix.
void Matrix3::extractEulerYZX(float &xDegrees, float &yDegrees, float &zDegrees)
{
    //Diagram of the Euler YZX Matrix:
    //
    // -------------------------------------------------------------
    //| cY * cZ                | -sZ      | cZ * sY                |
    //|------------------------|----------|-------------------------|
    //| sX * sY + cX * cY * sZ |  cX * cZ | cX * sY * sZ - cY * sX |
    //|------------------------|----------|-------------------------|
    //| cY * sX * sZ - cX * sY |  cZ * sX | cX * cY + sX * sY * sZ |
    // -------------------------------------------------------------
    
    //Case 1: -pi/2 < arcsin(sZ) < pi/2 (or, -1 < sZ < 1).  This solution is
    //unique.
    if(-1 + 0.000001f <= m_Matrix[1][0] && m_Matrix[1][0] <= 1 - 0.000001f)
    {
        xDegrees = radiansToDegrees(atan2f(m_Matrix[1][2], m_Matrix[1][1]));
        yDegrees = radiansToDegrees(atan2f(m_Matrix[2][0], m_Matrix[0][0]));
        zDegrees = radiansToDegrees(asinf(-m_Matrix[1][0]));
    }
    //Case 2: arcsin(sZ) = pi/2 (or, sZ = 1).  This solution is not unique, so
    //the x-angle is set to 0.
    else if(1 - 0.000001f < -m_Matrix[1][0] && -m_Matrix[1][0] < 1 + 0.000001f)
    {
        xDegrees = 0;
        yDegrees = radiansToDegrees(atan2f(-m_Matrix[0][2], m_Matrix[2][2]));
        zDegrees = 90;
    }
    //Case 3: arcsin(sZ) = -pi/2 (or, sZ = -1).  This solution is not unique,
    //so the x-angle is set to 0.
    else
    {
        xDegrees = 0;
        yDegrees = radiansToDegrees(atan2f(-m_Matrix[0][2], m_Matrix[2][2]));
        zDegrees = -90;
    }
}

//This method extracts the YZX Euler angles from the rotation matrix.
void Matrix3::extractEulerYZX(Vector3 &vector3)
{
    extractEulerYZX(vector3.x, vector3.y, vector3.z);
}

//This method extracts the ZXY Euler angles from the rotation matrix.
void Matrix3::extractEulerZXY(float &xDegrees, float &yDegrees, float &zDegrees)
{
    //Diagram of the Euler ZXY Matrix:
    //
    // ------------------------------------------------------------
    //| cY * cZ + sX * sY * sZ | cZ * sX * sY - cY * sZ |  cX * sY |
    //|------------------------|------------------------|----------|
    //| cX * sZ                | cX * cZ                | -sX      |
    //|------------------------|------------------------|----------|
    //| cY * sX * sZ - cZ * sY | cY * cZ * sX + sY * sZ |  cX * cY |
    // ------------------------------------------------------------
    
    //Case 1: -pi/2 < arcsin(sX) < pi/2 (or, -1 < sX < 1).  This solution is
    //unique.
    if(-1 + 0.000001f <= m_Matrix[2][1] && m_Matrix[2][1] <= 1 - 0.000001f)
    {
        xDegrees = radiansToDegrees(asinf(-m_Matrix[2][1]));
        yDegrees = radiansToDegrees(atan2f(m_Matrix[2][0], m_Matrix[2][2]));
        zDegrees = radiansToDegrees(atan2f(m_Matrix[0][1], m_Matrix[1][1]));
    }
    //Case 2: arcsin(sX) = pi/2 (or, sX = 1).  This solution is not unique, so
    //the y-angle is set to 0.
    else if(1 - 0.000001f < -m_Matrix[2][1] && -m_Matrix[2][1] < 1 + 0.000001f)
    {
        xDegrees = 90;
        yDegrees = 0;
        zDegrees = radiansToDegrees(atan2f(-m_Matrix[1][0], m_Matrix[0][0]));
    }
    //Case 3: arcsin(sX) = -pi/2 (or, sX = -1).  This solution is not unique,
    //so the y-angle is set to 0.
    else
    {
        xDegrees = -90;
        yDegrees = 0;
        zDegrees = radiansToDegrees(atan2f(-m_Matrix[1][0], m_Matrix[0][0]));
    }
}

//This method extracts the ZXY Euler angles from the rotation matrix.
void Matrix3::extractEulerZXY(Vector3 &vector3)
{
    extractEulerZXY(vector3.x, vector3.y, vector3.z);
}

//This method extracts the ZYX Euler angles from the rotation matrix.
void Matrix3::extractEulerZYX(float &xDegrees, float &yDegrees, float &zDegrees)
{
    //Diagram of the Euler ZYX Matrix:
    //
    // -------------------------------------------------------------
    //| cY * cZ,               | -cY * sZ,               |  sY      |
    //|------------------------|-------------------------|----------|
    //| cZ * sX * sY + cX * sZ |  cX * cZ - sX * sY * sZ | -cY * sX |
    //|------------------------|-------------------------|----------|
    //| sX * sZ - cX * cZ * sY |  cZ * sX + cX * sY * sZ |  cX * cY |
    // -------------------------------------------------------------
    
    //Case 1: -pi/2 < arcsin(sY) < pi/2 (or, -1 < sY < 1).  This solution is
    //unique.
    if(-1 + 0.000001f <= m_Matrix[2][0] && m_Matrix[2][0] <= 1 - 0.000001f)
    {
        xDegrees = radiansToDegrees(atan2f(-m_Matrix[2][1], m_Matrix[2][2]));
        yDegrees = radiansToDegrees(asinf(m_Matrix[2][0]));
        zDegrees = radiansToDegrees(atan2f(-m_Matrix[1][0], m_Matrix[0][0]));
    }
    //Case 2: arcsin(sY) = pi/2 (or, sY = 1).  This solution is not unique, so
    //the x-angle is set to 0.
    else if(1 - 0.000001f < m_Matrix[2][0] && m_Matrix[2][0] < 1 + 0.000001f)
    {
        yDegrees = 90;
        xDegrees = 0;
        zDegrees = radiansToDegrees(atan2f(m_Matrix[0][1], m_Matrix[1][1]));
    }
    //Case 3: arcsin(sY) = -pi/2 (or, sY = -1).  This solution is not unique,
    //so the x-angle is set to 0.
    else
    {
        yDegrees = -90;
        xDegrees = 0;
        zDegrees = radiansToDegrees(atan2f(m_Matrix[0][1], m_Matrix[1][1]));
    }
}

//This method extracts the ZYX Euler angles from the rotation matrix.
void Matrix3::extractEulerZYX(Vector3 &vector3)
{
    extractEulerZYX(vector3.x, vector3.y, vector3.z);
}

//===============================Other Methods================================//

//This method transposes the matrix.
Matrix3 Matrix3::transpose() const
{
    return Matrix3(m_Matrix[0][0], m_Matrix[0][1], m_Matrix[0][2],
                   m_Matrix[1][0], m_Matrix[1][1], m_Matrix[1][2],
                   m_Matrix[2][0], m_Matrix[2][1], m_Matrix[2][2]);
}

//This method inverts the matrix.
Matrix3 Matrix3::invert() const
{
    float determinant = this->determinant();
    
    //If the determinant is 0, then return the identity matrix.
    if(-0.000001f <= determinant && determinant <= 0.000001f)
        return Matrix3::Identity();
    
    float entry00 = m_Matrix[1][1] * m_Matrix[2][2] -
        m_Matrix[1][2] * m_Matrix[2][1];
    float entry01 = m_Matrix[1][2] * m_Matrix[2][0] -
        m_Matrix[1][0] * m_Matrix[2][2];
    float entry02 = m_Matrix[1][0] * m_Matrix[2][1] -
        m_Matrix[1][1] * m_Matrix[2][0];
    float entry10 = m_Matrix[0][2] * m_Matrix[2][1] -
        m_Matrix[0][1] * m_Matrix[2][2];
    float entry11 = m_Matrix[0][0] * m_Matrix[2][2] -
        m_Matrix[0][2] * m_Matrix[2][0];
    float entry12 = m_Matrix[0][1] * m_Matrix[2][0] -
        m_Matrix[0][0] * m_Matrix[2][1];
    float entry20 = m_Matrix[0][1] * m_Matrix[1][2] -
        m_Matrix[0][2] * m_Matrix[1][1];
    float entry21 = m_Matrix[0][2] * m_Matrix[1][0] -
        m_Matrix[0][0] * m_Matrix[1][2];
    float entry22 = m_Matrix[0][0] * m_Matrix[1][1] -
        m_Matrix[0][1] * m_Matrix[1][0];
    
    return Matrix3(entry00, entry01, entry02,
                   entry10, entry11, entry12,
                   entry20, entry21, entry22) / std::abs(determinant);
}

//This method computes the determinant of the matrix.
float Matrix3::determinant() const
{
    return m_Matrix[0][0] * (m_Matrix[1][1] * m_Matrix[2][2] -
                             m_Matrix[1][2] * m_Matrix[2][1])
    - m_Matrix[1][0] * (m_Matrix[0][1] * m_Matrix[2][2] -
                        m_Matrix[0][2] * m_Matrix[2][1])
    + m_Matrix[2][0] * (m_Matrix[0][1] * m_Matrix[1][2] -
                        m_Matrix[0][2] * m_Matrix[1][1]);
}

//This method computes the trace of the matrix.
float Matrix3::trace() const
{
    return m_Matrix[0][0] + m_Matrix[1][1] + m_Matrix[2][2];
}

//=======================Printing and Debugging Methods=======================//

//This method prints the matrix.
void Matrix3::print()
{
    std::cout << "\n";
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
            std::cout << m_Matrix[j][i] << "\t";
        
        std::cout << "\n";
    }
    std::cout << "\n";
}

}