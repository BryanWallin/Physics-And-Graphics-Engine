//============================================================================//
//                                                                            //
//  Matrix2.cpp                                                               //
//                                                                            //
//  The Matrix2 class is used to store attributes of a matrix of size 2x2.    //
//  Note that this class stores the matrix data in column-major format.       //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 02/05/2013 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#include "Matrix2.h"

namespace GraphicsEngine
{

//============================================================================//
//===========================Public Static Methods============================//
//============================================================================//

//==================================Identity==================================//

//This method makes the identity matrix.
Matrix2 Matrix2::Identity()
{
    return Matrix2(1, 0,
                   0, 1);
}

//==================================Rotating==================================//

//This method makes a rotation matrix.
Matrix2 Matrix2::Rotation(float degrees)
{
    float degreesInRadians = degreesToRadians(degrees);
    
    float sin = std::sinf(degreesInRadians);
    float cos = std::cosf(degreesInRadians);
    
    return Matrix2(cos, -sin,
                   sin, cos);
}
    
//==================================Scaling===================================//

//This method makes a scale matrix that scales in x and y.
Matrix2 Matrix2::Scale(float x, float y)
{
    return Matrix2(x, y);
}
    
//This method makes a scale matrix that scales in x and y.
Matrix2 Matrix2::Scale(const Vector2 &vector2)
{
    return Matrix2(vector2.x, vector2.y);
}

//============================================================================//
//=============================Public Methods=================================//
//============================================================================//

//================================Constructors================================//

//The default constructor.  It creates the identity matrix.
Matrix2::Matrix2()
{
    m_Matrix[0] = Vector2(1, 0);
    m_Matrix[1] = Vector2(0, 1);
}

//The diagonal constructor.
Matrix2::Matrix2(float entry00, float entry11)
{
    m_Matrix[0] = Vector2(entry00, 0);
    m_Matrix[1] = Vector2(0,       entry11);
}

//The diagonal constructor.
Matrix2::Matrix2(const Vector2 &diagonal)
{
    m_Matrix[0] = Vector2(diagonal.x, 0);
    m_Matrix[1] = Vector2(0,          diagonal.y);
}

//The single-entry constructor.
Matrix2::Matrix2(float allEntries)
{
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 2; j++)
            m_Matrix[i][j] = allEntries;
    }
}

//The float constructor.
Matrix2::Matrix2(float entry00, float entry01,
                 float entry10, float entry11)
{
    m_Matrix[0] = Vector2(entry00, entry10);
    m_Matrix[1] = Vector2(entry01, entry11);
}

//The column vector constructor.
Matrix2::Matrix2(const Vector2& column1, const Vector2& column2)
{
    m_Matrix[0] = column1;
    m_Matrix[1] = column2;
}

//The Matrix2 copy constructor.
Matrix2::Matrix2(const Matrix2& matrix2)
{
    m_Matrix[0] = matrix2[0];
    m_Matrix[1] = matrix2[1];
}

//The Matrix3 conversion constructor.
Matrix2::Matrix2(const Matrix3& matrix3)
{
    m_Matrix[0] = Vector2(matrix3[0]);
    m_Matrix[1] = Vector2(matrix3[1]);
}

//The Matrix4 conversion constructor.
Matrix2::Matrix2(const Matrix4& matrix4)
{
    m_Matrix[0] = Vector2(matrix4[0]);
    m_Matrix[1] = Vector2(matrix4[1]);
}

//===========================Indexing Operators===========================//

//The "write" indexing operator.
Vector2& Matrix2::operator [] ( int i )
{
    return m_Matrix[i];
}

//The "read" indexing operator.
const Vector2& Matrix2::operator [] ( int i ) const
{
    return m_Matrix[i];
}

//===================Non-Modifying Arithmetic Operators===================//

//The unary minus operator.
Matrix2 Matrix2::operator - () const
{
    return Matrix2(-m_Matrix[0], -m_Matrix[1]);
}

//The addition operator adds a given matrix.
Matrix2 Matrix2::operator + (const Matrix2& matrix2) const
{
    return Matrix2(m_Matrix[0] + matrix2[0], m_Matrix[1] + matrix2[1]);
}

//The subtraction operator subtracts a given matrix.
Matrix2 Matrix2::operator - (const Matrix2& matrix2) const
{
    return Matrix2(m_Matrix[0] - matrix2[0], m_Matrix[1] - matrix2[1]);
}

//The multiplication (by a constant) operator.
Matrix2 Matrix2::operator * (const float scalar) const
{
    return Matrix2(m_Matrix[0] * scalar, m_Matrix[1] * scalar);
}

//The multiplication operator.
Matrix2 Matrix2::operator * (const Matrix2& matrix2) const
{
    Matrix2 result = Matrix2(0.0f);
    
    for(int column = 0; column < 2; column++)
    {
        for(int row = 0; row < 2; row++)
        {
            for(int entry = 0; entry < 2; entry++)
                result[column][row] +=
                    m_Matrix[entry][row] * matrix2[column][entry];
        }
    }
    
    return result;
}

//The multiplication (by a Vector2) operator.
Vector2 Matrix2::operator * (const Vector2& vector2) const
{
    Vector2 result = Vector2(0, 0);
    
    for(int row = 0; row < 2; row++)
    {
        for(int entry = 0; entry < 2; entry++)
            result[row] += m_Matrix[entry][row] * vector2[entry];
    }
    
    return result;
}

//The division operator divides by a scalar.
Matrix2 Matrix2::operator / (const float scalar) const
{
    return Matrix2(m_Matrix[0] / scalar, m_Matrix[1] / scalar);
}

//=====================Modifying Arithmetic Operators=====================//

//The addition assignment operator adds the given matrix and stores the
//result.
Matrix2& Matrix2::operator += (const Matrix2& matrix2)
{
    m_Matrix[0] += matrix2[0];
    m_Matrix[1] += matrix2[1];
    
    return *this;
}

//The subtraction assignment operator subtracts the given matrix and stores
//the result.
Matrix2& Matrix2::operator -= (const Matrix2& matrix2)
{
    m_Matrix[0] -= matrix2[0];
    m_Matrix[1] -= matrix2[1];
    
    return *this;
}

//The multiplication assignment operator multiplies the matrix by a
//constant and stores the result.
Matrix2& Matrix2::operator *= (const float scalar)
{
    m_Matrix[0] *= scalar;
    m_Matrix[1] *= scalar;
    
    return *this;
}

//The multiplication assignment operator multiplies the matrix by the given
//matrix term-by-term and stores the result.
Matrix2& Matrix2::operator *= (const Matrix2& matrix2)
{
    Matrix2 result = Matrix2(0.0f);
    
    for(int column = 0; column < 2; column++)
    {
        for(int row = 0; row < 2; row++)
        {
            for(int entry = 0; entry < 2; entry++)
                result[column][row] +=
                    m_Matrix[entry][row] * matrix2[column][entry];
        }
    }
    
    *this = result;
    
    return *this;
}

//The division assignment operator divides the matrix by a constant and
//stores the result.
Matrix2& Matrix2::operator /= (const float scalar)
{
    m_Matrix[0] /= scalar;
    m_Matrix[1] /= scalar;
    
    return *this;
}

//=============================Cast Operators=============================//

//The cast operator casts the matrix to an array of floats.
Matrix2::operator const float* () const
{
    return static_cast<const float*>(&m_Matrix[0].x);
}

//The cast operator casts the matrix to an array of floats.
Matrix2::operator float* ()
{
    return static_cast<float*>(&m_Matrix[0].x);
}

//=============================Other Methods==============================//

//This method computes the determinant of the matrix.
float Matrix2::determinant() const
{
    return m_Matrix[0][0] * m_Matrix[1][1] - m_Matrix[0][1] * m_Matrix[1][0];
}

//This method computes the trace of the matrix.
float Matrix2::trace() const
{
    return m_Matrix[0][0] + m_Matrix[1][1];
}
    
//This method transposes the matrix.
Matrix2 Matrix2::transpose() const
{
return Matrix2(m_Matrix[0][0], m_Matrix[0][1],
               m_Matrix[1][0], m_Matrix[1][1]);
}
    
//This method inverts the matrix.
Matrix2 Matrix2::invert() const
{
    float determinant = this->determinant();
    
    //If the determinant is 0, then return the identity matrix.
    if(-0.000001f <= determinant && determinant <= 0.000001f)
        return Matrix2::Identity();
    
    return Matrix2(m_Matrix[1][1], -m_Matrix[1][0],
                   -m_Matrix[0][1], m_Matrix[0][0]) / std::abs(determinant);
}

}