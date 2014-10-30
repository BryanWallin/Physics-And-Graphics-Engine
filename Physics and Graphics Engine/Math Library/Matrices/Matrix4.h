//============================================================================//
//                                                                            //
//  Matrix4.h                                                                 //
//                                                                            //
//  The Matrix4 class is used to store attributes of a matrix of size 4x4.    //
//  Note that this class stores the matrix data in column-major format.       //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 02/05/2013 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#include <cmath>
#include "..\Vectors\Vector4.h"
#include "Matrix3.h"
#include "..\Quaternions\Quaternion.h"

namespace GraphicsEngine
{

//Forward Declarations.
class Matrix2;
class Matrix3;
class Quaternion;

class Matrix4
{
    
public:
    
    //========================================================================//
    //=========================Public Static Methods==========================//
    //========================================================================//
    
    //================================Identity================================//
    
    //This method makes the identity matrix.
    static Matrix4 Identity();
    
    //==============================Translating===============================//
    
    //This method generates a transformation matrix that translates in any of
    //the 3 axes.
    static Matrix4 Translate(float x, float y, float z);
    
    //This method generates a transformation matrix that translates in any of
    //the 3 axes.
    static Matrix4 Translate(const Vector3& xyz);
    
    //================================Rotating================================//
    
    //This method makes a rotation matrix that rotates about the x axis.
    static Matrix4 RotationX(float degrees);
    
    //This method makes a rotation matrix that rotates about the y axis.
    static Matrix4 RotationY(float degrees);
    
    //This method makes a rotation matrix that rotates about the z axis.
    static Matrix4 RotationZ(float degrees);
    
    //This method makes a rotation matrix that rotates around the x axis,
    //the y axis, and the z axis in that order.
    static Matrix4 EulerXYZ(float xDegrees, float yDegrees, float zDegrees);
    
    //This method makes a rotation matrix that rotates around the x axis,
    //the y axis, and the z axis in that order.
    static Matrix4 EulerXYZ(const Vector3 &vector3);
    
    //This method makes a rotation matrix that rotates around the x axis,
    //the z axis, and the y axis in that order.
    static Matrix4 EulerXZY(float xDegrees, float yDegrees, float zDegrees);
    
    //This method makes a rotation matrix that rotates around the x axis,
    //the z axis, and the y axis in that order.
    static Matrix4 EulerXZY(const Vector3 &vector3);
    
    //This method makes a rotation matrix that rotates around the y axis,
    //the x axis, and the z axis in that order.
    static Matrix4 EulerYXZ(float xDegrees, float yDegrees, float zDegrees);
    
    //This method makes a rotation matrix that rotates around the y axis,
    //the x axis, and the z axis in that order.
    static Matrix4 EulerYXZ(const Vector3 &vector3);
    
    //This method makes a rotation matrix that rotates around the y axis,
    //the z axis, and the x axis in that order.
    static Matrix4 EulerYZX(float xDegrees, float yDegrees, float zDegrees);
    
    //This method makes a rotation matrix that rotates around the y axis,
    //the z axis, and the x axis in that order.
    static Matrix4 EulerYZX(const Vector3 &vector3);
    
    //This method makes a rotation matrix that rotates around the z axis,
    //the x axis, and the y axis in that order.
    static Matrix4 EulerZXY(float xDegrees, float yDegrees, float zDegrees);
    
    //This method makes a rotation matrix that rotates around the z axis,
    //the x axis, and the y axis in that order.
    static Matrix4 EulerZXY(const Vector3 &vector3);
    
    //This method makes a rotation matrix that rotates around the z axis,
    //the y axis, and the x axis in that order.
    static Matrix4 EulerZYX(float xDegrees, float yDegrees, float zDegrees);
    
    //This method makes a rotation matrix that rotates around the z axis,
    //the y axis, and the x axis in that order.
    static Matrix4 EulerZYX(const Vector3 &vector3);
    
    //================================Scaling=================================//
    
    //This method makes a scale matrix that scales in x and y.
    static Matrix4 Scale(float x, float y, float z);
    
    //This method makes a scale matrix that scales in x and y.
    static Matrix4 Scale(const Vector3 &vector3);
    
    //===========================Viewing Transforms===========================//
    
    //This method generates a perspective transformation matrix.
    static Matrix4 Perspective(float fieldOfView, float aspectRatio,
                               float near, float far);
    
    //This method generates an orthographic transformation matrix.
    static Matrix4 Ortho(float left, float right, float bottom, float top,
                         float near, float far);
    
    //This method generates a user-chosen frustrum transformation matrix.
    static Matrix4 Frustum(float left, float right, float bottom, float top,
                           float near, float far);
    
    //This method is used to go from world-space to eye-space.
    static Matrix4 LookAt(float cameraAtX, float cameraAtY, float cameraAtZ,
                          float objectAtX, float objectAtY, float objectAtZ,
                          float upDirectionX, float upDirectionY,
                          float upDirectionZ);
    
    //This method is used to go from world-space to eye-space.
    static Matrix4 LookAt(const Vector3& cameraAt, const Vector3& objectAt,
                          const Vector3& upDirection);
    
    //========================================================================//
    //===========================Public Methods===============================//
    //========================================================================//
    
    //==============================Constructors==============================//
    
    //The default constructor.  It creates the identity matrix.
    Matrix4();
    
    //The single-entry constructor.
    Matrix4(float allEntries);
    
    //The float array constructor.
    Matrix4(float *array);
    
    //The float constructor.
    Matrix4(float entry00, float entry01, float entry02, float entry03,
            float entry10, float entry11, float entry12, float entry13,
            float entry20, float entry21, float entry22, float entry23,
            float entry30, float entry31, float entry32, float entry33);
    
    //The vector constructor.
    Matrix4(const Vector4& row1, const Vector4& row2, const Vector4& row3,
            const Vector4& row4);
    
    //The Matrix4 copy constructor.
    Matrix4(const Matrix4& matrix4);
    
    //The Matrix2 conversion constructor.
    explicit Matrix4(const Matrix2& matrix2);
    
    //The Matrix3 conversion constructor.
    explicit Matrix4(const Matrix3& matrix3);
    
    //The Quaternion conversion constructor.
    explicit Matrix4(const Quaternion& quaternion);
    
    //===========================Indexing Operators===========================//
    
    //The "write" indexing operator.
    Vector4& operator [] (int i);
    
    //The "read" indexing operator.
    const Vector4& operator [] (int i) const;
    
    //===================Non-Modifying Arithmetic Operators===================//
    
    //The unary minus operator.
    Matrix4 operator - () const;
    
    //The addition operator adds a given matrix.
    Matrix4 operator + (const Matrix4& matrix4) const;
    
    //The subtraction operator subtracts a given matrix.
    Matrix4 operator - (const Matrix4& matrix4) const;
    
    //The multiplication (by a constant) operator.
    Matrix4 operator * (const float scalar) const;
    
    //The multiplication (term-by-term product) operator.
    Matrix4 operator * (const Matrix4& matrix4) const;
    
    //The multiplication (by a Vector4) operator.
    Vector4 operator * (const Vector4& vector4) const;
    
    //The division operator divides by a scalar.
    Matrix4 operator / (const float scalar) const;
    
    //=====================Modifying Arithmetic Operators=====================//
    
    //The addition assignment operator adds the given matrix and stores the
    //result.
    Matrix4& operator += (const Matrix4& matrix4);
    
    //The subtraction assignment operator subtracts the given matrix and stores
    //the result.
    Matrix4& operator -= (const Matrix4& matrix4);
    
    //The multiplication assignment operator multiplies the matrix by a
    //constant and stores the result.
    Matrix4& operator *= (const float scalar);
    
    //The multiplication assignment operator multiplies the matrix by the given
    //matrix term-by-term and stores the result.
    Matrix4& operator *= (const Matrix4& matrix4);
    
    //The division assignment operator divides the matrix by a constant and
    //stores the result.
    Matrix4& operator /= (const float scalar);
    
    //=============================Cast Operators=============================//
    
    //The cast operator casts the matrix to an array of floats.
    operator const float* () const;
    
    //The cast operator casts the matrix to an array of floats.
    operator float* ();
    
    //=============================Other Methods==============================//
    
    //This method computes the determinant of the matrix.
    float determinant() const;
    
    //This method computes the trace of the matrix.
    float trace() const;
    
    //This method transposes the matrix.
    Matrix4 transpose() const;
    
    //This method inverts the matrix.
    Matrix4 invert() const;
    
    //=====================Printing and Debugging Methods=====================//
    
    //This method prints the matrix.
    void print();
    
    //========================================================================//
    //=========================Private Instance Data==========================//
    //========================================================================//
    
private:
    
    //The columns of the matrix.
    Vector4 m_Matrix[4];
};

}

#endif