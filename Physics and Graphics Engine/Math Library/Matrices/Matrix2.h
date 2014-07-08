//============================================================================//
//                                                                            //
//  Matrix2.h                                                                 //
//                                                                            //
//  The Matrix2 class is used to store attributes of a matrix of size 2x2.    //
//  Note that this class stores the matrix data in column-major format.       //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 02/05/2013 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#ifndef __MATRIX2__
#define __MATRIX2__

#include <cmath>
#include "Vector2.h"
#include "Matrix3.h"
#include "Matrix4.h"

namespace GraphicsEngine
{

//Forward Declarations.
class Matrix3;
class Matrix4;

class Matrix2
{
    
public:
    
    //========================================================================//
    //=========================Public Static Methods==========================//
    //========================================================================//
    
    //================================Identity================================//
    
    //This method makes the identity matrix.
    static Matrix2 Identity();
    
    //================================Rotating================================//
    
    //This method makes a rotation matrix.
    static Matrix2 Rotation(float degrees);
    
    //================================Scaling=================================//
    
    //This method makes a scale matrix that scales in x and y.
    Matrix2 Scale(float x, float y);
    
    //This method makes a scale matrix that scales in x and y.
    Matrix2 Scale(const Vector2 &vector2);
    
    //========================================================================//
    //===========================Public Methods===============================//
    //========================================================================//
    
    //==============================Constructors==============================//
    
    //The default constructor.  It creates the identity matrix.
    Matrix2();
    
    //The diagonal constructor.
    Matrix2(float entry00, float entry11);
    
    //The diagonal constructor.
    Matrix2(const Vector2 &diagonal);
    
    //The single-entry constructor.
    Matrix2(float allEntries);
    
    //The float constructor.
    Matrix2(float entry00, float entry01,
            float entry10, float entry11);
    
    //The column vector constructor.
    Matrix2(const Vector2& column1, const Vector2& column2);
    
    //The Matrix2 copy constructor.
    Matrix2(const Matrix2& matrix2);
    
    //The Matrix3 conversion constructor.
    explicit Matrix2(const Matrix3& matrix3);
    
    //The Matrix4 conversion constructor.
    explicit Matrix2(const Matrix4& matrix4);
    
    //===========================Indexing Operators===========================//
    
    //The "write" indexing operator.
    Vector2& operator [] ( int i );
    
    //The "read" indexing operator.
    const Vector2& operator [] ( int i ) const;
    
    //===================Non-Modifying Arithmetic Operators===================//
    
    //The unary minus operator.
    Matrix2 operator - () const;
    
    //The addition operator adds a given matrix.
    Matrix2 operator + (const Matrix2& matrix2) const;
    
    //The subtraction operator subtracts a given matrix.
    Matrix2 operator - (const Matrix2& matrix2) const;
    
    //The multiplication (by a constant) operator.
    Matrix2 operator * (const float scalar) const;
    
    //The multiplication operator.
    Matrix2 operator * (const Matrix2& matrix2) const;
    
    //The multiplication (by a Vector2) operator.
    Vector2 operator * (const Vector2& vector2) const;
    
    //The division operator divides by a scalar.
    Matrix2 operator / (const float scalar) const;
    
    //=====================Modifying Arithmetic Operators=====================//
    
    //The addition assignment operator adds the given matrix and stores the
    //result.
    Matrix2& operator += (const Matrix2& matrix2);
    
    //The subtraction assignment operator subtracts the given matrix and stores
    //the result.
    Matrix2& operator -= (const Matrix2& matrix2);
    
    //The multiplication assignment operator multiplies the matrix by a
    //constant and stores the result.
    Matrix2& operator *= (const float scalar);
    
    //The multiplication assignment operator multiplies the matrix by the given
    //matrix and stores the result.
    Matrix2& operator *= (const Matrix2& matrix2);
    
    //The division assignment operator divides the matrix by a constant and
    //stores the result.
    Matrix2& operator /= (const float scalar);
    
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
    Matrix2 transpose() const;
    
    //This method inverts the matrix.
    Matrix2 invert() const;
    
    //========================================================================//
    //=========================Private Instance Data==========================//
    //========================================================================//
    
private:
    
    //The columns of the matrix.
    Vector2 m_Matrix[2];
};

}

#endif