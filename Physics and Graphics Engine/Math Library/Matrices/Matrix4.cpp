//============================================================================//
//                                                                            //
//  Matrix4.cpp                                                               //
//                                                                            //
//  The Matrix4 class is used to store attributes of a matrix of size 4x4.    //
//  Note that this class stores the matrix data in column-major format.       //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 02/05/2013 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#include "Matrix4.h"
#include <iostream>

namespace GraphicsEngine
{

//============================================================================//
//===========================Public Static Methods============================//
//============================================================================//

//==================================Identity==================================//

//This method makes the identity matrix.
Matrix4 Matrix4::Identity()
{
    return Matrix4(1, 0, 0, 0,
                   0, 1, 0, 0,
                   0, 0, 1, 0,
                   0, 0, 0, 1);
}

//================================Translating=================================//

//This method generates a transformation matrix that translates in any of
//the 3 axes.
Matrix4 Matrix4::Translate(float x, float y, float z)
{
    return Matrix4(1, 0, 0, x,
                   0, 1, 0, y,
                   0, 0, 1, z,
                   0, 0, 0, 1);
}

//This method generates a transformation matrix that translates in any of
//the 3 axes.
Matrix4 Matrix4::Translate(const Vector3& xyz)
{
    return Translate(xyz.x, xyz.y, xyz.z);
}

//==================================Rotating==================================//

//This method makes a rotation matrix that rotates about the x axis.
Matrix4 Matrix4::RotationX(float degrees)
{
    float degreesInRadians = degreesToRadians(degrees);
    
    float sX = std::sinf(degreesInRadians);
    float cX = std::cosf(degreesInRadians);
    
    return Matrix4(1, 0,   0,  0,
                   0, cX, -sX, 0,
                   0, sX,  cX, 0,
                   0, 0,   0,  1);
}

//This method makes a rotation matrix that rotates about the y axis.
Matrix4 Matrix4::RotationY(float degrees)
{
    float degreesInRadians = degreesToRadians(degrees);
    
    float sY = std::sinf(degreesInRadians);
    float cY = std::cosf(degreesInRadians);
    
    return Matrix4( cY, 0, sY, 0,
                    0,  1, 0,  0,
                   -sY, 0, cY, 0,
                    0,  0, 0,  1);
}

//This method makes a rotation matrix that rotates about the z axis.
Matrix4 Matrix4::RotationZ(float degrees)
{
    float degreesInRadians = degreesToRadians(degrees);
    
    float sZ = std::sinf(degreesInRadians);
    float cZ = std::cosf(degreesInRadians);
    
    return Matrix4(cZ, -sZ, 0, 0,
                   sZ,  cZ, 0, 0,
                   0,   0,  1, 0,
                   0,   0,  0, 1);
}

//This method makes a rotation matrix that rotates around the x axis,
//the y axis, and the z axis in that order.
Matrix4 Matrix4::EulerXYZ(float xDegrees, float yDegrees, float zDegrees)
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
    
    return Matrix4( cY * cZ, cZ * sX * sY - cX * sZ, cX * cZ * sY + sX * sZ, 0,
                    cY * sZ, cX * cZ + sX * sY * sZ, cX * sY * sZ - cZ * sX, 0,
                   -sY,      cY * sX,                cX * cY,                0,
                    0,       0,                      0,                      1);
}

//This method makes a rotation matrix that rotates around the x axis,
//the y axis, and the z axis in that order.
Matrix4 Matrix4::EulerXYZ(const Vector3 &vector3)
{
    return EulerXYZ(vector3.x, vector3.y, vector3.z);
}

//This method makes a rotation matrix that rotates around the x axis,
//the z axis, and the y axis in that order.
Matrix4 Matrix4::EulerXZY(float xDegrees, float yDegrees, float zDegrees)
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
    
    return Matrix4( cY * cZ, sX * sY - cX * cY * sZ,  cX * sY + cY * sX * sZ, 0,
                    sZ,      cX * cZ,                -cZ * sX,                0,
                   -cZ * sY, cY * sX + cX * sY * sZ,  cX * cY - sX * sY * sZ, 0,
                    0,       0,                       0,                     1);
}

//This method makes a rotation matrix that rotates around the x axis,
//the z axis, and the y axis in that order.
Matrix4 Matrix4::EulerXZY(const Vector3 &vector3)
{
    return EulerXZY(vector3.x, vector3.y, vector3.z);
}

//This method makes a rotation matrix that rotates around the y axis,
//the x axis, and the z axis in that order.
Matrix4 Matrix4::EulerYXZ(float xDegrees, float yDegrees, float zDegrees)
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
    
    return Matrix4( cY * cZ - sX * sY * sZ, -cX * sZ, cZ * sY + cY * sX * sZ, 0,
                    cZ * sX * sY + cY * sZ,  cX * cZ, sY * sZ - cY * cZ * sX, 0,
                   -cX * sY,                 sX,      cX * cY,                0,
                    0,                       0,       0,                     1);
}

//This method makes a rotation matrix that rotates around the y axis,
//the x axis, and the z axis in that order.
Matrix4 Matrix4::EulerYXZ(const Vector3 &vector3)
{
    return EulerYXZ(vector3.x, vector3.y, vector3.z);
}

//This method makes a rotation matrix that rotates around the y axis,
//the z axis, and the x axis in that order.
Matrix4 Matrix4::EulerYZX(float xDegrees, float yDegrees, float zDegrees)
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
    
    return Matrix4(cY * cZ,                -sZ,      cZ * sY,                0,
                   sX * sY + cX * cY * sZ,  cX * cZ, cX * sY * sZ - cY * sX, 0,
                   cY * sX * sZ - cX * sY,  cZ * sX, cX * cY + sX * sY * sZ, 0,
                   0,                       0,       0,                      1);
}

//This method makes a rotation matrix that rotates around the y axis,
//the z axis, and the x axis in that order.
Matrix4 Matrix4::EulerYZX(const Vector3 &vector3)
{
    return EulerYZX(vector3.x, vector3.y, vector3.z);
}

//This method makes a rotation matrix that rotates around the z axis,
//the x axis, and the y axis in that order.
Matrix4 Matrix4::EulerZXY(float xDegrees, float yDegrees, float zDegrees)
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
    
    return Matrix4(cY * cZ + sX * sY * sZ, cZ * sX * sY - cY * sZ,  cX * sY, 0,
                   cX * sZ,                cX * cZ,                -sX,      0,
                   cY * sX * sZ - cZ * sY, cY * cZ * sX + sY * sZ,  cX * cY, 0,
                   0,                      0,                       0,       1);
}

//This method makes a rotation matrix that rotates around the z axis,
//the x axis, and the y axis in that order.
Matrix4 Matrix4::EulerZXY(const Vector3 &vector3)
{
    return EulerZXY(vector3.x, vector3.y, vector3.z);
}

//This method makes a rotation matrix that rotates around the z axis,
//the y axis, and the x axis in that order.
Matrix4 Matrix4::EulerZYX(float xDegrees, float yDegrees, float zDegrees)
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
    
    return Matrix4(cY * cZ,                -cY * sZ,                 sY,      0,
                   cZ * sX * sY + cX * sZ,  cX * cZ - sX * sY * sZ, -cY * sX, 0,
                   sX * sZ - cX * cZ * sY,  cZ * sX + cX * sY * sZ,  cX * cY, 0,
                   0,                       0,                       0,      1);
}

//This method makes a rotation matrix that rotates around the z axis,
//the y axis, and the x axis in that order.
Matrix4 Matrix4::EulerZYX(const Vector3 &vector3)
{
    return EulerZYX(vector3.x, vector3.y, vector3.z);
}

//==================================Scaling===================================//

//This method makes a scale matrix that scales in x and y.
Matrix4 Matrix4::Scale(float x, float y, float z)
{
    return Matrix4(x, 0, 0, 0,
                   0, y, 0, 0,
                   0, 0, z, 0,
                   0, 0, 0, 1);
}

//This method makes a scale matrix that scales in x and y.
Matrix4 Matrix4::Scale(const Vector3 &vector3)
{
    return Scale(vector3.x, vector3.y, vector3.z);
}

//=============================Viewing Transforms=============================//

//This method generates a perspective transformation matrix.
Matrix4 Matrix4::Perspective(float fieldOfViewY, float aspectRatio, float near,
                             float far)
{
    //Solving for the necessary points using trigonometry.
    float top = near * tan(degreesToRadians(fieldOfViewY / 2));
    float bottom = -top;
    float right = top * aspectRatio;
    float left = -right;
    
    return Frustum(left, right, bottom, top, near, far);
}

//This method generates an orthographic transformation matrix.
Matrix4 Matrix4::Ortho(float left, float right, float bottom, float top,
                       float near, float far)
{
    float r_m_l = right - left;
    float r_p_l = right + left;
    float t_m_b = top - bottom;
    float t_p_b = top + bottom;
    float f_m_n = far - near;
    float f_p_n = far + near;
    
    return Matrix4(2 / r_m_l, 0,          0,         -r_p_l / r_m_l,
                   0,         2 / t_m_b,  0,         -t_p_b / t_m_b,
                   0,         0,         -2 / f_m_n, -f_p_n / f_m_n,
                   0,         0,          0,          1);
}

//This method generates a user-chosen frustrum transformation matrix.
Matrix4 Matrix4::Frustum(float left, float right, float bottom, float top,
                         float near, float far)
{
    float n = near;
    float f = far;
    float r = right;
    float t = top;
    float f_m_n = far - near;
    float f_p_n = far + near;
    
    return Matrix4(n / r, 0,     0,              0,
                   0,     n / t, 0,              0,
                   0,     0,    -f_p_n / f_m_n, -2 * f * n / f_m_n,
                   0,     0,    -1,              0);
}

//This method is used to go from world-space to eye-space.
Matrix4 Matrix4::LookAt(float cameraAtX, float cameraAtY, float cameraAtZ,
                        float objectAtX, float objectAtY, float objectAtZ,
                        float upDirectionX, float upDirectionY,
                        float upDirectionZ)
{
    return LookAt(Vector3(cameraAtX, cameraAtY, cameraAtZ),
                  Vector3(objectAtX, objectAtY, objectAtZ),
                  Vector3(upDirectionX, upDirectionY, upDirectionZ));
}

//This method is used to go from world-space to eye-space.
Matrix4 Matrix4::LookAt(const Vector3& cameraAt, const Vector3& objectAt,
                        const Vector3& upDirection)
{
    Vector3 zAxis = (cameraAt - objectAt).normalize();
    Vector3 xAxis = (upDirection.cross(zAxis)).normalize();
    Vector4 yAxis = Vector4((zAxis.cross(xAxis)).normalize());
    
    //    std::cout << "Z Axis: (" << zAxis.x << ", " << zAxis.y << ", "
    //    << zAxis.z << ")\n";
    
    Matrix4 c = Matrix4(xAxis.x, xAxis.y, xAxis.z, 0,
                        yAxis.x, yAxis.y, yAxis.z, 0,
                        zAxis.x, zAxis.y, zAxis.z, 0,
                        0,       0,       0,       1);
    
    return c * Translate(-cameraAt);
}


//============================================================================//
//=============================Public Methods=================================//
//============================================================================//

//================================Constructors================================//

//The default constructor.  It creates the identity matrix.
Matrix4::Matrix4()
{
    m_Matrix[0] = Vector4(1, 0, 0, 0);
    m_Matrix[1] = Vector4(0, 1, 0, 0);
    m_Matrix[2] = Vector4(0, 0, 1, 0);
    m_Matrix[3] = Vector4(0, 0, 0, 1);
}

//The single-entry constructor.
Matrix4::Matrix4(float allEntries)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
            m_Matrix[i][j] = allEntries;
    }
}

//The float array constructor.
Matrix4::Matrix4(float *array)
{
    for(int row = 0; row < 4; row++)
    {
        for(int column = 0; column < 4; column++)
            m_Matrix[column][row] = array[row * 4 + column];
    }
}

//The float constructor.
Matrix4::Matrix4(float entry00, float entry01, float entry02, float entry03,
                 float entry10, float entry11, float entry12, float entry13,
                 float entry20, float entry21, float entry22, float entry23,
                 float entry30, float entry31, float entry32, float entry33)
{
    m_Matrix[0] = Vector4(entry00, entry10, entry20, entry30);
    m_Matrix[1] = Vector4(entry01, entry11, entry21, entry31);
    m_Matrix[2] = Vector4(entry02, entry12, entry22, entry32);
    m_Matrix[3] = Vector4(entry03, entry13, entry23, entry33);
}

//The vector constructor.
Matrix4::Matrix4(const Vector4& column1, const Vector4& column2,
                 const Vector4& column3, const Vector4& column4)
{
    m_Matrix[0] = column1;
    m_Matrix[1] = column2;
    m_Matrix[2] = column3;
    m_Matrix[3] = column4;
}

//The Matrix4 copy constructor.
Matrix4::Matrix4(const Matrix4& matrix4)
{
    m_Matrix[0] = matrix4[0];
    m_Matrix[1] = matrix4[1];
    m_Matrix[2] = matrix4[2];
    m_Matrix[3] = matrix4[3];
}

//The Matrix2 conversion constructor.
Matrix4::Matrix4(const Matrix2& matrix2)
{
    m_Matrix[0] = Vector4(matrix2[0]);
    m_Matrix[1] = Vector4(matrix2[1]);
    m_Matrix[2] = Vector4(0, 0, 0, 0);
    m_Matrix[3] = Vector4(0, 0, 0, 0);
}

//The Matrix3 conversion constructor.
Matrix4::Matrix4(const Matrix3& matrix3)
{
    m_Matrix[0] = Vector4(matrix3[0]);
    m_Matrix[1] = Vector4(matrix3[1]);
    m_Matrix[2] = Vector4(matrix3[2]);
    m_Matrix[3] = Vector4(0, 0, 0, 0);
}

//The Quaternion conversion constructor.
Matrix4::Matrix4(const Quaternion& q)
{
    m_Matrix[0] = Vector4(1.0f - 2.0f * q.y * q.y - 2.0f * q.z * q.z,
                          2.0f * q.x * q.y + 2.0f * q.z * q.w,
                          2.0f * q.x * q.z - 2.0f * q.y * q.w,
                          0.0f);
    m_Matrix[1] = Vector4(2.0f * q.x * q.y - 2.0f * q.z * q.w,
                          1.0f - 2.0f * q.x * q.x - 2.0f * q.z * q.z,
                          2.0f * q.y * q.z + 2.0f * q.x * q.w,
                          0.0f);
    m_Matrix[2] = Vector4(2.0f * q.x * q.z + 2.0f * q.y * q.w,
                          2.0f * q.y * q.z - 2.0f * q.x * q.w,
                          1.0f - 2.0f * q.x * q.x - 2.0f * q.y * q.y,
                          0.0f);
    m_Matrix[3] = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
}

//=============================Indexing Operators=============================//

//The "write" indexing operator.
Vector4& Matrix4::operator [] (int i)
{
    return m_Matrix[i];
}

//The "read" indexing operator.
const Vector4& Matrix4::operator [] (int i) const
{
    return m_Matrix[i];
}

//=====================Non-Modifying Arithmetic Operators=====================//

//The unary minus operator.
Matrix4 Matrix4::operator - () const
{
    return Matrix4(-m_Matrix[0], -m_Matrix[1], -m_Matrix[2], -m_Matrix[3]);
}

//The addition operator adds a given matrix.
Matrix4 Matrix4::operator + (const Matrix4& matrix4) const
{
    return Matrix4(m_Matrix[0] + matrix4[0],m_Matrix[1] + matrix4[1],
                   m_Matrix[2] + matrix4[2], m_Matrix[3] + matrix4[3]);
}

//The subtraction operator subtracts a given matrix.
Matrix4 Matrix4::operator - (const Matrix4& matrix4) const
{
    return Matrix4(m_Matrix[0] - matrix4[0], m_Matrix[1] - matrix4[1],
                   m_Matrix[2] - matrix4[2], m_Matrix[3] + matrix4[3]);
}

//The multiplication (by a constant) operator.
Matrix4 Matrix4::operator * (const float scalar) const
{
    return Matrix4(m_Matrix[0] * scalar, m_Matrix[1] * scalar,
                   m_Matrix[2] * scalar, m_Matrix[3] * scalar);
}

//The multiplication operator.
Matrix4 Matrix4::operator * (const Matrix4& matrix4) const
{
    Matrix4 result = Matrix4(0.0f);
    
    for(int column = 0; column < 4; column++)
    {
        for(int row = 0; row < 4; row++)
        {
            for(int entry = 0; entry < 4; entry++)
                result[column][row] +=
                    m_Matrix[entry][row] * matrix4[column][entry];
        }
    }
    
    return result;
}
    
//The multiplication (by a Vector4) operator.
Vector4 Matrix4::operator * (const Vector4& vector4) const
{
    Vector4 result = Vector4(0, 0, 0, 0);
    
    for(int row = 0; row < 4; row++)
    {
        for(int entry = 0; entry < 4; entry++)
            result[row] += m_Matrix[entry][row] * vector4[entry];
    }
    
    return result;
}

//The division operator divides by a scalar.
Matrix4 Matrix4::operator / (const float scalar) const
{
    return Matrix4(m_Matrix[0] / scalar, m_Matrix[1] / scalar,
                   m_Matrix[2] / scalar, m_Matrix[3] / scalar);
}

//=====================Modifying Arithmetic Operators=====================//

//The addition assignment operator adds the given matrix and stores the
//result.
Matrix4& Matrix4::operator += (const Matrix4& matrix4)
{
    m_Matrix[0] += matrix4[0];
    m_Matrix[1] += matrix4[1];
    m_Matrix[2] += matrix4[2];
    m_Matrix[3] += matrix4[3];
    return *this;
}

//The subtraction assignment operator subtracts the given matrix and stores
//the result.
Matrix4& Matrix4::operator -= (const Matrix4& matrix4)
{
    m_Matrix[0] -= matrix4[0];
    m_Matrix[1] -= matrix4[1];
    m_Matrix[2] -= matrix4[2];
    m_Matrix[3] -= matrix4[3];
    
    return *this;
}

//The multiplication assignment operator multiplies the matrix by a
//constant and stores the result.
Matrix4& Matrix4::operator *= (const float scalar)
{
    m_Matrix[0] *= scalar;
    m_Matrix[1] *= scalar;
    m_Matrix[2] *= scalar;
    m_Matrix[3] *= scalar;
    
    return *this;
}

//The multiplication assignment operator multiplies the matrix by the given
//matrix and stores the result.
Matrix4& Matrix4::operator *= (const Matrix4& matrix4)
{
    Matrix4 result = Matrix4(0.0f);
    
    for(int column = 0; column < 4; column++)
    {
        for(int row = 0; row < 4; row++)
        {
            for(int entry = 0; entry < 4; entry++)
                result[column][row] +=
                    m_Matrix[entry][row] * matrix4[column][entry];
        }
    }
    
    *this = result;
    
    return *this;
}

//The division assignment operator divides the matrix by a constant and
//stores the result.
Matrix4& Matrix4::operator /= (const float scalar)
{
    m_Matrix[0] /= scalar;
    m_Matrix[1] /= scalar;
    m_Matrix[2] /= scalar;
    m_Matrix[3] /= scalar;
    return *this;
}

//=============================Cast Operators=============================//

//The cast operator casts the matrix to an array of floats.
Matrix4::operator const float* () const
{
    return static_cast<const float*>(&m_Matrix[0].x);
}

//The cast operator casts the matrix to an array of floats.
Matrix4::operator float* ()
{
    return static_cast<float*>(&m_Matrix[0].x);
}

//=============================Other Methods==============================//

//This method computes the determinant of the matrix.
float Matrix4::determinant() const
{
    return m_Matrix[0][0] * (m_Matrix[1][1] * m_Matrix[2][2] * m_Matrix[3][3] +
                             m_Matrix[2][1] * m_Matrix[3][2] * m_Matrix[1][3] +
                             m_Matrix[3][1] * m_Matrix[1][2] * m_Matrix[2][3] -
                             m_Matrix[3][1] * m_Matrix[2][2] * m_Matrix[1][3] -
                             m_Matrix[2][1] * m_Matrix[1][2] * m_Matrix[3][3] -
                             m_Matrix[1][1] * m_Matrix[3][2] * m_Matrix[2][3])
         - m_Matrix[1][0] * (m_Matrix[0][1] * m_Matrix[2][2] * m_Matrix[3][3] +
                             m_Matrix[2][1] * m_Matrix[3][2] * m_Matrix[0][3] +
                             m_Matrix[3][1] * m_Matrix[0][2] * m_Matrix[2][3] -
                             m_Matrix[3][1] * m_Matrix[2][2] * m_Matrix[0][3] -
                             m_Matrix[2][1] * m_Matrix[0][2] * m_Matrix[3][3] -
                             m_Matrix[0][1] * m_Matrix[3][2] * m_Matrix[2][3])
         + m_Matrix[2][0] * (m_Matrix[0][1] * m_Matrix[1][2] * m_Matrix[3][3] +
                             m_Matrix[1][1] * m_Matrix[3][2] * m_Matrix[0][3] +
                             m_Matrix[3][1] * m_Matrix[0][2] * m_Matrix[1][3] -
                             m_Matrix[3][1] * m_Matrix[1][2] * m_Matrix[0][3] -
                             m_Matrix[1][1] * m_Matrix[0][2] * m_Matrix[3][3] -
                             m_Matrix[0][1] * m_Matrix[3][2] * m_Matrix[1][3])
         - m_Matrix[3][0] * (m_Matrix[0][1] * m_Matrix[1][2] * m_Matrix[2][3] +
                             m_Matrix[1][1] * m_Matrix[2][2] * m_Matrix[0][3] +
                             m_Matrix[2][1] * m_Matrix[0][2] * m_Matrix[1][3] -
                             m_Matrix[2][1] * m_Matrix[1][2] * m_Matrix[0][3] -
                             m_Matrix[1][1] * m_Matrix[0][2] * m_Matrix[2][3] -
                             m_Matrix[0][1] * m_Matrix[2][2] * m_Matrix[1][3]);
}

//This method computes the trace of the matrix.
float Matrix4::trace() const
{
    return m_Matrix[0][0] + m_Matrix[1][1] + m_Matrix[2][2] + m_Matrix[3][3];
}
    
//This method transposes the matrix.
Matrix4 Matrix4::transpose() const
{
    return Matrix4(m_Matrix[0][0], m_Matrix[0][1], m_Matrix[0][2],
                   m_Matrix[0][3],
                   m_Matrix[1][0], m_Matrix[1][1], m_Matrix[1][2],
                   m_Matrix[1][3],
                   m_Matrix[2][0], m_Matrix[2][1], m_Matrix[2][2],
                   m_Matrix[2][3],
                   m_Matrix[3][0], m_Matrix[3][1], m_Matrix[3][2],
                   m_Matrix[3][3]);
}

//This method inverts the matrix.
Matrix4 Matrix4::invert() const
{
    float determinant = this->determinant();
    
    //If the determinant is 0, then return the identity matrix.
    //if(-0.000001f <= determinant && determinant <= 0.000001f)
    //    return Matrix4::Identity();
    
    float m00 = m_Matrix[1][3] * (m_Matrix[2][1] * m_Matrix[3][2] -
                                  m_Matrix[2][2] * m_Matrix[3][1]) +
                m_Matrix[1][2] * (m_Matrix[2][3] * m_Matrix[3][1] -
                                  m_Matrix[2][1] * m_Matrix[3][3]) +
                m_Matrix[1][1] * (m_Matrix[2][2] * m_Matrix[3][3] -
                                  m_Matrix[2][3] * m_Matrix[3][2]);
    float m01 = m_Matrix[1][3] * (m_Matrix[2][2] * m_Matrix[3][0] -
                                  m_Matrix[2][0] * m_Matrix[3][2]) +
                m_Matrix[1][2] * (m_Matrix[2][0] * m_Matrix[3][3] -
                                  m_Matrix[2][3] * m_Matrix[3][0]) +
                m_Matrix[1][0] * (m_Matrix[2][3] * m_Matrix[3][2] -
                                  m_Matrix[2][2] * m_Matrix[3][3]);
    float m02 = m_Matrix[1][3] * (m_Matrix[2][0] * m_Matrix[3][1] -
                                  m_Matrix[2][1] * m_Matrix[3][0]) +
                m_Matrix[1][1] * (m_Matrix[2][3] * m_Matrix[3][0] -
                                  m_Matrix[2][0] * m_Matrix[3][3]) +
                m_Matrix[1][0] * (m_Matrix[2][1] * m_Matrix[3][3] -
                                  m_Matrix[2][3] * m_Matrix[3][1]);
    float m03 = m_Matrix[1][2] * (m_Matrix[2][1] * m_Matrix[3][0] -
                                  m_Matrix[2][0] * m_Matrix[3][1]) +
                m_Matrix[1][1] * (m_Matrix[2][0] * m_Matrix[3][2] -
                                  m_Matrix[2][2] * m_Matrix[3][0]) +
                m_Matrix[1][0] * (m_Matrix[2][2] * m_Matrix[3][1] -
                                  m_Matrix[2][1] * m_Matrix[3][2]);
    float m10 = m_Matrix[0][3] * (m_Matrix[2][2] * m_Matrix[3][1] -
                                  m_Matrix[2][1] * m_Matrix[3][2]) +
                m_Matrix[0][2] * (m_Matrix[2][1] * m_Matrix[3][3] -
                                  m_Matrix[2][3] * m_Matrix[3][1]) +
                m_Matrix[0][1] * (m_Matrix[2][3] * m_Matrix[3][2] -
                                  m_Matrix[2][2] * m_Matrix[3][3]);
    float m11 = m_Matrix[0][3] * (m_Matrix[2][0] * m_Matrix[3][2] -
                                  m_Matrix[2][2] * m_Matrix[3][0]) +
                m_Matrix[0][2] * (m_Matrix[2][3] * m_Matrix[3][0] -
                                  m_Matrix[2][0] * m_Matrix[3][3]) +
                m_Matrix[0][0] * (m_Matrix[2][2] * m_Matrix[3][3] -
                                  m_Matrix[2][3] * m_Matrix[3][2]);
    float m12 = m_Matrix[0][3] * (m_Matrix[2][1] * m_Matrix[3][0] -
                                  m_Matrix[2][0] * m_Matrix[3][1]) +
                m_Matrix[0][1] * (m_Matrix[2][0] * m_Matrix[3][3] -
                                  m_Matrix[2][3] * m_Matrix[3][0]) +
                m_Matrix[0][0] * (m_Matrix[2][3] * m_Matrix[3][1] -
                                  m_Matrix[2][1] * m_Matrix[3][3]);
    float m13 = m_Matrix[0][2] * (m_Matrix[2][0] * m_Matrix[3][1] -
                                  m_Matrix[2][1] * m_Matrix[3][0]) +
                m_Matrix[0][1] * (m_Matrix[2][2] * m_Matrix[3][0] -
                                  m_Matrix[2][0] * m_Matrix[3][2]) +
                m_Matrix[0][0] * (m_Matrix[2][1] * m_Matrix[3][2] -
                                  m_Matrix[2][2] * m_Matrix[3][1]);
    float m20 = m_Matrix[0][3] * (m_Matrix[1][1] * m_Matrix[3][2] -
                                  m_Matrix[1][2] * m_Matrix[3][1]) +
                m_Matrix[0][2] * (m_Matrix[1][3] * m_Matrix[3][1] -
                                  m_Matrix[1][1] * m_Matrix[3][3]) +
                m_Matrix[0][1] * (m_Matrix[1][2] * m_Matrix[3][3] -
                                  m_Matrix[1][3] * m_Matrix[3][2]);
    float m21 = m_Matrix[0][3] * (m_Matrix[1][2] * m_Matrix[3][0] -
                                  m_Matrix[1][0] * m_Matrix[3][2]) +
                m_Matrix[0][2] * (m_Matrix[1][0] * m_Matrix[3][3] -
                                  m_Matrix[1][3] * m_Matrix[3][0]) +
                m_Matrix[0][0] * (m_Matrix[1][3] * m_Matrix[3][2] -
                                  m_Matrix[1][2] * m_Matrix[3][3]);
    float m22 = m_Matrix[0][3] * (m_Matrix[1][0] * m_Matrix[3][1] -
                                  m_Matrix[1][1] * m_Matrix[3][0]) +
                m_Matrix[0][1] * (m_Matrix[1][3] * m_Matrix[3][0] -
                                  m_Matrix[1][0] * m_Matrix[3][3]) +
                m_Matrix[0][0] * (m_Matrix[1][1] * m_Matrix[3][3] -
                                  m_Matrix[1][3] * m_Matrix[3][1]);
    float m23 = m_Matrix[0][2] * (m_Matrix[1][1] * m_Matrix[3][0] -
                                  m_Matrix[1][0] * m_Matrix[3][1]) +
                m_Matrix[0][1] * (m_Matrix[1][0] * m_Matrix[3][2] -
                                  m_Matrix[1][2] * m_Matrix[3][0]) +
                m_Matrix[0][0] * (m_Matrix[1][2] * m_Matrix[3][1] -
                                  m_Matrix[1][1] * m_Matrix[3][2]);
    float m30 = m_Matrix[0][3] * (m_Matrix[1][2] * m_Matrix[2][1] -
                                  m_Matrix[1][1] * m_Matrix[2][2]) +
                m_Matrix[0][2] * (m_Matrix[1][1] * m_Matrix[2][3] -
                                  m_Matrix[1][3] * m_Matrix[2][1]) +
                m_Matrix[0][1] * (m_Matrix[1][3] * m_Matrix[2][2] -
                                  m_Matrix[1][2] * m_Matrix[2][3]);
    float m31 = m_Matrix[0][3] * (m_Matrix[1][0] * m_Matrix[2][2] -
                                  m_Matrix[1][2] * m_Matrix[2][0]) +
                m_Matrix[0][2] * (m_Matrix[1][3] * m_Matrix[2][0] -
                                  m_Matrix[1][0] * m_Matrix[2][3]) +
                m_Matrix[0][0] * (m_Matrix[1][2] * m_Matrix[2][3] -
                                  m_Matrix[1][3] * m_Matrix[2][2]);
    float m32 = m_Matrix[0][3] * (m_Matrix[1][1] * m_Matrix[2][0] -
                                  m_Matrix[1][0] * m_Matrix[2][1]) +
                m_Matrix[0][1] * (m_Matrix[1][0] * m_Matrix[2][3] -
                                  m_Matrix[1][3] * m_Matrix[2][0]) +
                m_Matrix[0][0] * (m_Matrix[1][3] * m_Matrix[2][1] -
                                  m_Matrix[1][1] * m_Matrix[2][3]);
    float m33 = m_Matrix[0][2] * (m_Matrix[1][0] * m_Matrix[2][1] -
                                  m_Matrix[1][1] * m_Matrix[2][0]) +
                m_Matrix[0][1] * (m_Matrix[1][2] * m_Matrix[2][0] -
                                  m_Matrix[1][0] * m_Matrix[2][2]) +
                m_Matrix[0][0] * (m_Matrix[1][1] * m_Matrix[2][2] -
                                  m_Matrix[1][2] * m_Matrix[2][1]);
    
	return Matrix4(m00, m01, m02, m03,
                   m10, m11, m12, m13,
                   m20, m21, m22, m23,
                   m30, m31, m32, m33) / determinant;
}

//=======================Printing and Debugging Methods=======================//

//This method prints the matrix.
void Matrix4::print()
{
    std::cout << "\n";
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
            std::cout << m_Matrix[j][i] << "\t";
        
        std::cout << "\n";
    }
    std::cout << "\n";
}

}