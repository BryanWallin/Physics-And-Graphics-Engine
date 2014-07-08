//============================================================================//
//                                                                            //
//  Light.h                                                                   //
//                                                                            //
//  The Light class is used to store light information, such as direction,    //
//  color, position, and more.                                                //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 10/29/2013 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#ifndef _LIGHT_H_
#define _LIGHT_H_

//#include "MathLibrary.h"
//
//namespace GraphicsEngine
//{
//
//class Light
//{
//
//public:
//
//    //=============================Public Methods=============================//
//
//    //------------------------------Constructors------------------------------//
//    
//    //The complete constructor.
//    Light(Vector4 position = Vector4(0, 0, 0, 0),
//          Vector4 diffuse = Vector4(1, 1, 1, 1),
//          Vector4 specular = Vector4(1, 1, 1, 1),
//          float constantAttenuation = 1, float linearAttenuation = 0,
//          float squaredAttenuation = 0, float lightAmount = 1);
//
//    //--------------------------------Setters---------------------------------//
//    
//    //This method sets the light's position.
//    void setPosition(Vector4 position);
//
//    //This method sets the light's diffuse color.
//    void setDiffuse(Vector4 diffuse);
//
//    //This method sets the light's specular color.
//    void setSpecular(Vector4 specular);
//
//    //This method sets the light's constant attenuation.
//    void setConstantAttenuation(float constantAttenuation);
//
//    //This method sets the light's linear attenuation.
//    void setLinearAttenuation(float linearAttenuation);
//
//    //This method sets the light's squared attenuation.
//    void setSquaredAttenuation(float squaredAttenuation);
//
//    //This method sets the light's spotlight direction.
//    void setSpotlightDirection(Vector4 spotlightDirection);
//
//    //This method sets the light's spotlight cutoff.
//    void setSpotlightCutoff(float spotlightCutoff);
//
//    //This method sets the light's spotlight exponent.
//    void setSpotlightExponent(float spotlightExponent);
//
//    //This method sets the light's light amount.
//    void setLightAmount(float lightAmount);
//
//    //--------------------------------Getters---------------------------------//
//
//    //This method gets the light's position.
//    Vector4 getPosition();
//
//    //This method gets the light's diffuse color.
//    Vector4 getDiffuse();
//
//    //This method gets the light's specular color.
//    Vector4 getSpecular();
//
//    //This method gets the light's constant attenuation.
//    float getConstantAttenuation();
//
//    //This method gets the light's linear attenuation.
//    float getLinearAttenuation();
//
//    //This method gets the light's squared attenuation.
//    float getSquaredAttenuation();
//
//    //This method returns the light's spotlight direction, if it has one.
//    Vector4 getSpotlightDirection();
//
//    //This method return the light's spotlight cutoff, if it has one.
//    float getSpotlightCutoff();
//
//    //This method return the light's spotlight exponent, if it has one.
//    float getSpotlightExponent();
//
//    //This method gets the light's light amount.
//    float getLightAmount();
//
//    //-----------------------------Other Methods------------------------------//
//
//    //This method converts the current light into a spotlight.
//    void makeSpotlight(Vector4 spotlightDirection, float spotlightCutoff, 
//        float spotlightExponent);
//
//    //This method sets the light on if it is off, and vice versa.
//    void toggleLight();
//
//private:
//
//    //=========================Private Instance Data==========================//
//
//    //Storing the position of the light source.
//    Vector4 position;
//
//    //Storing the lighting colors needed by the Phong Lighting model.
//    Vector4 diffuse, specular;
//
//    //Storing if the light is enabled or not.
//    float lightAmount;
//
//    //Storing the attenuation terms for the light source.
//    float constantAttenuation, linearAttenuation, squaredAttenuation;
//
//    //Storing spotlight information.  The spotlight cutoff is in degrees.
//    Vector4 spotlightDirection;
//    float spotlightCutoff, spotlightExponent;
//};
//
//}

#endif