//============================================================================//
//                                                                            //
//  Matrix3.h                                                                 //
//                                                                            //
//  The Matrix3 class is used to store attributes of a matrix of size 3x3.    //
//  Note that this class stores the matrix data in column-major format.       //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 03/18/2014 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#ifndef _MATRIX3_H_
#define _MATRIX3_H_

#include <cmath>
#include "..\Vectors\Vector3.h"
#include "Matrix2.h"
#include "Matrix4.h"
#include "..\MathUtilities.h"
#include "..\Quaternions\Quaternion.h"

namespace GraphicsEngine
{
    
//Forward Declarations.
class Matrix2;
class Matrix4;
class Quaternion;

class Matrix3
{
    
public:
    
    //========================================================================//
    //=========================Public Static Methods==========================//
    //========================================================================//
    
    //================================Identity================================//
    
    //This method makes the identity matrix.
    static Matrix3 Identity();
    
    //================================Rotating================================//
    
    //This method makes a rotation matrix that rotates about the x axis.
    static Matrix3 RotationX(float degrees);
    
    //This method makes a rotation matrix that rotates about the y axis.
    static Matrix3 RotationY(float degrees);
    
    //This method makes a rotation matrix that rotates about the z axis.
    static Matrix3 RotationZ(float degrees);
    
    //This method makes a rotation matrix that rotates around the x axis,
    //the y axis, and the z axis in that order.
    static Matrix3 EulerXYZ(float xDegrees, float yDegrees, float zDegrees);
    
    //This method makes a rotation matrix that rotates around the x axis,
    //the y axis, and the z axis in that order.
    static Matrix3 EulerXYZ(const Vector3 &vector3);
    
    //This method makes a rotation matrix that rotates around the x axis,
    //the z axis, and the y axis in that order.
    static Matrix3 EulerXZY(float xDegrees, float yDegrees, float zDegrees);
    
    //This method makes a rotation matrix that rotates around the x axis,
    //the z axis, and the y axis in that order.
    static Matrix3 EulerXZY(const Vector3 &vector3);
    
    //This method makes a rotation matrix that rotates around the y axis,
    //the x axis, and the z axis in that order.
    static Matrix3 EulerYXZ(float xDegrees, float yDegrees, float zDegrees);
    
    //This method makes a rotation matrix that rotates around the y axis,
    //the x axis, and the z axis in that order.
    static Matrix3 EulerYXZ(const Vector3 &vector3);
    
    //This method makes a rotation matrix that rotates around the y axis,
    //the z axis, and the x axis in that order.
    static Matrix3 EulerYZX(float xDegrees, float yDegrees, float zDegrees);
    
    //This method makes a rotation matrix that rotates around the y axis,
    //the z axis, and the x axis in that order.
    static Matrix3 EulerYZX(const Vector3 &vector3);
    
    //This method makes a rotation matrix that rotates around the z axis,
    //the x axis, and the y axis in that order.
    static Matrix3 EulerZXY(float xDegrees, float yDegrees, float zDegrees);
    
    //This method makes a rotation matrix that rotates around the z axis,
    //the x axis, and the y axis in that order.
    static Matrix3 EulerZXY(const Vector3 &vector3);
    
    //This method makes a rotation matrix that rotates around the z axis,
    //the y axis, and the x axis in that order.
    static Matrix3 EulerZYX(float xDegrees, float yDegrees, float zDegrees);
    
    //This method makes a rotation matrix that rotates around the z axis,
    //the y axis, and the x axis in that order.
    static Matrix3 EulerZYX(const Vector3 &vector3);
    
    //================================Scaling=================================//
    
    //This method makes a scale matrix that scales in x, y, and z.
    static Matrix3 Scale(float x, float y, float z);
    
    //This method makes a scale matrix that scales in x, y, and z.
    static Matrix3 Scale(const Vector3 &vector3);
    
    //========================================================================//
    //=============================Public Methods=============================//
    //========================================================================//
    
    //==============================Constructors==============================//
    
    //The default constructor.  It creates the identity matrix.
    Matrix3();
    
    //The diagonal constructor.
    Matrix3(float entry00, float entry11, float entry22);
    
    //The diagonal constructor.
    Matrix3(const Vector3 &diagonal);
    
    //The single-entry constructor.
    Matrix3(float allEntries);
    
    //The float constructor.
    Matrix3(float entry00, float entry01, float entry02,
            float entry10, float entry11, float entry12,
            float entry20, float entry21, float entry22);
    
    //The vector constructor.
    Matrix3(const Vector3& column1, const Vector3& column2,
            const Vector3& column3);
    
    //The Matrix3 copy constructor.
    Matrix3(const Matrix3& matrix3);
    
    //The Matrix2 conversion constructor.
    explicit Matrix3(const Matrix2& matrix2);
    
    //The Matrix4 conversion constructor.
    explicit Matrix3(const Matrix4& matrix4);
    
    //The Quaternion conversion constructor.
    explicit Matrix3(const Quaternion& quaternion);
    
    //===========================Indexing Operators===========================//
    
    //The "write" indexing operator.
    Vector3& operator [] (int i);
    
    //The "read" indexing operator.
    const Vector3& operator [] (int i) const;
    
    //===================Non-Modifying Arithmetic Operators===================//
    
    //The unary minus operator.
    Matrix3 operator - () const;
    
    //The addition operator adds a given matrix.
    Matrix3 operator + (const Matrix3& matrix3) const;
    
    //The subtraction operator subtracts a given matrix.
    Matrix3 operator - (const Matrix3& matrix3) const;
    
    //The multiplication (by a constant) operator.
    Matrix3 operator * (const float scalar) const;
    
    //The multiplication operator.
    Matrix3 operator * (const Matrix3& matrix3) const;
    
    //The multiplication (by a Vector3) operator.
    Vector3 operator * (const Vector3& vector3) const;
    
    //The division operator divides by a scalar.
    Matrix3 operator / (const float scalar) const;
    
    //=====================Modifying Arithmetic Operators=====================//
    
    //The addition assignment operator adds the given matrix and stores the
    //result.
    Matrix3& operator += (const Matrix3& matrix3);
    
    //The subtraction assignment operator subtracts the given matrix and stores
    //the result.
    Matrix3& operator -= (const Matrix3& matrix3);
    
    //The multiplication assignment operator multiplies the matrix by a
    //constant and stores the result.
    Matrix3& operator *= (const float scalar);
    
    //The multiplication assignment operator multiplies the matrix by the given
    //matrix and stores the result.
    Matrix3& operator *= (const Matrix3& matrix3);
    
    //The division assignment operator divides the matrix by a constant and
    //stores the result.
    Matrix3& operator /= (const float scalar);
    
    //=============================Cast Operators=============================//
    
    //The cast operator casts the matrix to an array of floats.
    operator const float* () const;
    
    //The cast operator casts the matrix to an array of floats.
    operator float* ();
    
    //==============================Euler Angles==============================//
    
    //This method extracts the XYZ Euler angles from the rotation matrix.
    void extractEulerXYZ(float &xDegrees, float &yDegrees, float &zDegrees);
    
    //This method extracts the XYZ Euler angles from the rotation matrix.
    void extractEulerXYZ(Vector3 &vector3);
    
    //This method extracts the XZY Euler angles from the rotation matrix.
    void extractEulerXZY(float &xDegrees, float &yDegrees, float &zDegrees);
    
    //This method extracts the XZY Euler angles from the rotation matrix.
    void extractEulerXZY(Vector3 &vector3);
    
    //This method extracts the YXZ Euler angles from the rotation matrix.
    void extractEulerYXZ(float &xDegrees, float &yDegrees, float &zDegrees);
    
    //This method extracts the YXZ Euler angles from the rotation matrix.
    void extractEulerYXZ(Vector3 &vector3);
    
    //This method extracts the YZX Euler angles from the rotation matrix.
    void extractEulerYZX(float &xDegrees, float &yDegrees, float &zDegrees);
    
    //This method extracts the YZX Euler angles from the rotation matrix.
    void extractEulerYZX(Vector3 &vector3);
    
    //This method extracts the ZXY Euler angles from the rotation matrix.
    void extractEulerZXY(float &xDegrees, float &yDegrees, float &zDegrees);
    
    //This method extracts the ZXY Euler angles from the rotation matrix.
    void extractEulerZXY(Vector3 &vector3);
    
    //This method extracts the ZYX Euler angles from the rotation matrix.
    void extractEulerZYX(float &xDegrees, float &yDegrees, float &zDegrees);
    
    //This method extracts the ZYX Euler angles from the rotation matrix.
    void extractEulerZYX(Vector3 &vector3);
    
    //=============================Other Methods==============================//
    
    //This method transposes the matrix.
    Matrix3 transpose() const;
    
    //This method inverts the matrix.
    Matrix3 invert() const;
    
    //This method computes the determinant of the matrix.
    float determinant() const;
    
    //This method computes the trace of the matrix.
    float trace() const;
    
    //=====================Printing and Debugging Methods=====================//
    
    //This method prints the matrix.
    void print();
    
private:
    
    //========================================================================//
    //=========================Private Instance Data==========================//
    //========================================================================//
    
    //The columns of the matrix.
    Vector3 m_Matrix[3];
};

}

#endif