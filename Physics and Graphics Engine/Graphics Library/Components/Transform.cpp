//
//  Transform.cpp
//  Hello Arrow
//
//  Created by Bryan Wallin on 3/3/14.
//  Copyright (c) 2014 Bryan Wallin. All rights reserved.
//

#include "Transform.h"

namespace GraphicsEngine
{

//============================================================================//
//===============================Public Methods===============================//
//============================================================================//

//================================Constructors================================//

//The default constructor.
Transform::Transform() : Transform(Vector3(0, 0, 0), Vector3(1, 1, 1),
                                   Quaternion())
{
}

//The individual component constructor.
Transform::Transform(const Vector3 &position, const Vector3 &scale,
                     const Quaternion &rotation)
{
    //Setting the values passed in.
    m_Position = position;
    m_Scale = scale;
    m_Rotation = rotation;
    
    //Setting the default values.
    m_Up = Vector3(0, 1, 0);
    m_Forward = Vector3(0, 0, -1);
    m_Right = Vector3(1, 0, 0);
    m_TransformNeedsUpdate = true;
    m_InverseTransformNeedsUpdate = true;
}

//The matrix constructor.
Transform::Transform(const Matrix4 &transform)
{
    setTransform(transform);
}

//==================================Setters===================================//

//This method sets the position using a vector.  Note that the previous
//position is erased.
void Transform::setPosition(const Vector3 &position)
{
    m_Position = position;
    
    //Marking the transforms out of date.
    m_TransformNeedsUpdate = true;
    m_InverseTransformNeedsUpdate = true;
}

//This method sets the position using three floats.  Note that the previous
//position is erased.
void Transform::setPosition(float x, float y, float z)
{
    setPosition(Vector3(x, y, z));
}

//This method sets the scale using a vector.  Note that the previous
//scale is erased.
void Transform::setScale(const Vector3 &scale)
{
    m_Scale = scale;
    
    //Marking the transforms out of date.
    m_TransformNeedsUpdate = true;
    m_InverseTransformNeedsUpdate = true;
}

//This method sets the scale using three floats.  Note that the previous
//scale is erased.
void Transform::setScale(float x, float y, float z)
{
    setScale(Vector3(x, y, z));
}

//This method sets the rotation using a matrix.  Note that the previous
//rotation is erased.
void Transform::setRotation(const Quaternion &rotation)
{
    m_Rotation = rotation;
    
    //Marking the transforms out of date.
    m_TransformNeedsUpdate = true;
    m_InverseTransformNeedsUpdate = true;
}

//This method sets the entire transform using a matrix.  Note that the
//previous position, scale, and rotation is erased.
void Transform::setTransform(const Matrix4 &transform)
{
    //Making a copy of the rotation/scale part of the transform that can be
    //modified.
    Matrix3 copy = Matrix3(transform);
    
    //Computing the scale based on the column-basis.  Note that for a pure
    //rotation, the length should be 1, so the scale is equal to the length of
    //the column.
    float scaleX = copy[0].length();
    float scaleY = copy[1].length();
    float scaleZ = copy[2].length();
    
    m_Scale = Vector3(scaleX, scaleY, scaleZ);
    
    //Dividing each column by its length to obtain a true rotation-only matrix.
    copy[0] /= scaleX;
    copy[1] /= scaleY;
    copy[2] /= scaleZ;
    
    //Computing the rotation from the (now) rotation-only matrix.
    m_Rotation = Quaternion::Rotation(copy);
    
    //The position is simply the first three terms of the last column.
    m_Position = Vector3(transform[3]);
    
    //Marking the transforms out of date.
    m_TransformNeedsUpdate = true;
    m_InverseTransformNeedsUpdate = true;
}

//==================================Getters===================================//

//This method gets the position.
Vector3 Transform::getPosition()
{
    return m_Position;
}

//This method gets the scale.
Vector3 Transform::getScale()
{
    return m_Scale;
}

//This method gets the rotation.
Quaternion Transform::getRotation()
{
    return m_Rotation;
}

//This method gets the transform.
Matrix4 Transform::getTransform()
{
    //If the transform is out of date, update it.
    if(m_TransformNeedsUpdate)
        updateTransform();
    
    return m_Transform;
}

//This method gets the inverse transform.
Matrix4 Transform::getInverseTransform()
{
    //If the transform is out of date, update it.
    if(m_InverseTransformNeedsUpdate)
        updateInverseTransform();
    
    return m_InverseTransform;
}

//============================Transform Operations============================//

//This method translates the transform using a vector.
void Transform::translate(const Vector3 &translate, TransformSpace space)
{
    switch (space)
    {
        case Local:
            m_Position += Matrix3(m_Rotation) * translate;
            break;
        case Parent:
            m_Position += translate;
            break;
    }
    m_Position += translate;
    
    //Marking the transforms out of date.
    m_TransformNeedsUpdate = true;
    m_InverseTransformNeedsUpdate = true;
}

//This method translates the transform using three floats.
void Transform::translate(float x, float y, float z, TransformSpace space)
{
    translate(Vector3(x, y, z), space);
}

//This method scales the transform using a vector.
void Transform::scale(const Vector3 &scale)
{
    m_Scale *= scale;
    
    //Marking the transforms out of date.
    m_TransformNeedsUpdate = true;
    m_InverseTransformNeedsUpdate = true;
}

//This method scales the transform using three floats.
void Transform::scale(float x, float y, float z)
{
    scale(Vector3(x, y, z));
}

//This method rotates the transform around the x-axis.
void Transform::rotateX(float degrees, TransformSpace space)
{
    rotate(Quaternion::AngleAxis(degrees, Vector3(1, 0, 0)), space);
}

//This method rotates the transform around the y-axis.
void Transform::rotateY(float degrees, TransformSpace space)
{
    rotate(Quaternion::AngleAxis(degrees, Vector3(0, 1, 0)), space);
}

//This method rotates the transform around the z-axis.
void Transform::rotateZ(float degrees, TransformSpace space)
{
    rotate(Quaternion::AngleAxis(degrees, Vector3(0, 0, 1)), space);
}

//This method rotates the transform about the given axis.
void Transform::rotateAngleAxis(float degrees, const Vector3 &axis,
                                TransformSpace space)
{
    rotate(Quaternion::AngleAxis(degrees, axis), space);
}

//This method rotates the transform by the given quaternion.
void Transform::rotate(const Quaternion &rotation, TransformSpace space)
{
    switch (space)
    {
        case Local:
            m_Rotation = m_Rotation * rotation;
            break;
        case Parent:
            m_Rotation = rotation * m_Rotation;
            break;
    }
    
    //Marking the transforms out of date.
    m_TransformNeedsUpdate = true;
    m_InverseTransformNeedsUpdate = true;
}

//============================================================================//
//==============================Private Methods===============================//
//============================================================================//

//This method updates the transform.
void Transform::updateTransform()
{
    //Normalizing the quaternion before using it.
    m_Rotation.normalize();
    
    m_Transform = Matrix4::Translate(m_Position) * Matrix4(m_Rotation) *
        Matrix4::Scale(m_Scale);
    
    m_TransformNeedsUpdate = false;
}

//This method updates the inverse transform.
void Transform::updateInverseTransform()
{
    //Normalizing the quaternion before using it.
    m_Rotation.normalize();
    
    //Getting the inverse scale, rotation, and translation.
    Vector3 inverseScale = Vector3(1 / m_Scale.x,
                                   1 / m_Scale.y,
                                   1 / m_Scale.z);
    Vector3 inversePosition = Vector3(-m_Position.x,
                                      -m_Position.y,
                                      -m_Position.z);
    Quaternion inverseRotation = m_Rotation.inverse();
    
    m_InverseTransform = Matrix4::Translate(inversePosition) *
        Matrix4(inverseRotation) * Matrix4::Scale(inverseScale);
    
    m_InverseTransformNeedsUpdate = false;
}

}