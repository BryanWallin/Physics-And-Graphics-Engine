//
//  Transform.h
//  Hello Arrow
//
//  Created by Bryan Wallin on 3/3/14.
//  Copyright (c) 2014 Bryan Wallin. All rights reserved.
//

#ifndef __TRANSFORM__
#define __TRANSFORM__

#include "..\..\Math Library\MathLibrary.h"

namespace GraphicsEngine
{

class Transform
{

public:
    
    //========================================================================//
    //==========================Public Enumerations===========================//
    //========================================================================//
    
    enum TransformSpace {Local, Parent};
    
    //========================================================================//
    //=============================Public Methods=============================//
    //========================================================================//
    
    //==============================Constructors==============================//
    
    //The default constructor.
    Transform();
    
    //The individual component constructor.
    Transform(const Vector3 &position, const Vector3 &scale,
              const Quaternion &rotation);
    
    //The matrix constructor.
    Transform(const Matrix4 &transform);
    
    //================================Setters=================================//
    
    //This method sets the position using a vector.  Note that the previous
    //position is erased.
    void setPosition(const Vector3 &position);
    
    //This method sets the position using three floats.  Note that the previous
    //position is erased.
    void setPosition(float x, float y, float z);
    
    //This method sets the scale using a vector.  Note that the previous
    //scale is erased.
    void setScale(const Vector3 &scale);
    
    //This method sets the scale using three floats.  Note that the previous
    //scale is erased.
    void setScale(float x, float y, float z);
    
    //This method sets the rotation using a matrix.  Note that the previous
    //rotation is erased.
    void setRotation(const Quaternion &rotation);
    
    //This method sets the entire transform using a matrix.  Note that the
    //previous position, scale, and rotation is erased.
    void setTransform(const Matrix4 &transform);
    
    //================================Getters=================================//
    
    //This method gets the position.
    Vector3 getPosition();
    
    //This method gets the scale.
    Vector3 getScale();
    
    //This method gets the rotation.
    Quaternion getRotation();
    
    //This method gets the transform.
    Matrix4 getTransform();
    
    //This method gets the inverse transform.
    Matrix4 getInverseTransform();
    
    //==========================Transform Operations==========================//
    
    //This method translates the transform using a vector.
    void translate(const Vector3 &translate, TransformSpace space = Local);
    
    //This method translates the transform using three floats.
    void translate(float x, float y, float z, TransformSpace space = Local);
    
    //This method scales the transform using a vector.
    void scale(const Vector3 &scale);
    
    //This method scales the transform using three floats.
    void scale(float x, float y, float z);
    
    //This method rotates the transform around the x-axis.
    void rotateX(float degrees, TransformSpace space = Local);
    
    //This method rotates the transform around the y-axis.
    void rotateY(float degrees, TransformSpace space = Local);
    
    //This method rotates the transform around the z-axis.
    void rotateZ(float degrees, TransformSpace space = Local);
    
    //This method rotates the transform about the given axis.
    void rotateAngleAxis(float degrees, const Vector3 &axis,
                         TransformSpace space = Local);
    
    //This method rotates the transform by the given quaternion.
    void rotate(const Quaternion &rotation, TransformSpace space = Local);
    
private:
    
    //========================================================================//
    //=========================Private Instance Data==========================//
    //========================================================================//
    
    //Storing the position vector.
    Vector3 m_Position;

    //Storing the scale vector.
    Vector3 m_Scale;
    
    //Storing the rotation matrix.
    Quaternion m_Rotation;
    
    //Storing the up direction.
    Vector3 m_Up;
    
    //Storing the forward direction.
    Vector3 m_Forward;
    
    //Storing the right direction.
    Vector3 m_Right;

    //Storing the transform matrix.
    Matrix4 m_Transform;
    
    //Storing the inverse transform matrix.
    Matrix4 m_InverseTransform;
    
    //Storing the normal transformation matrix.
    Matrix3 m_NormalTransform;

    //Storing a flag to mark if the currently stored transform is out of date.
    bool m_TransformNeedsUpdate;
    
    //Storing a flag to mark if the currently stored inverse transform is out
    //of date.
    bool m_InverseTransformNeedsUpdate;
    
    //========================================================================//
    //============================Private Methods=============================//
    //========================================================================//
    
    //This method updates the transform.
    void updateTransform();
    
    //This method updates the inverse transform.
    void updateInverseTransform();
};

}

#endif