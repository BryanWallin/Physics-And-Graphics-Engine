//============================================================================//
//                                                                            //
//  Light.cpp                                                                 //
//                                                                            //
//  The Light class is used to store light information, such as direction,    //
//  color, position, and more.                                                //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 10/29/2013 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#include "Light.h"

namespace GraphicsEngine
{

////===============================Public Methods===============================//
//
////--------------------------------Constructors--------------------------------//
//    
////The complete constructor.
//Light::Light(Vector4 position, Vector4 diffuse, Vector4 specular, 
//    float constantAttenuation, float linearAttenuation, 
//    float squaredAttenuation, float lightAmount)
//{
//    this->setLightAmount(lightAmount);
//    this->setPosition(position);
//    this->setDiffuse(diffuse);
//    this->setSpecular(specular);
//    this->setConstantAttenuation(constantAttenuation);
//    this->setLinearAttenuation(linearAttenuation);
//    this->setSquaredAttenuation(squaredAttenuation);
//}
//
////----------------------------------Setters-----------------------------------//
//
////This method sets the light's diffuse color.
//void Light::setDiffuse(Vector4 diffuse)
//{
//    this->diffuse = diffuse;
//}
//
////This method sets the light's specular color.
//void Light::setSpecular(Vector4 specular)
//{
//    this->specular = specular;
//}
//
////This method sets the light's constant attenuation.
//void Light::setConstantAttenuation(float constantAttenuation)
//{
//    this->constantAttenuation = constantAttenuation;
//}
//
////This method sets the light's linear attenuation.
//void Light::setLinearAttenuation(float linearAttenuation)
//{
//    this->linearAttenuation = linearAttenuation;
//}
//
////This method sets the light's squared attenuation.
//void Light::setSquaredAttenuation(float squaredAttenuation)
//{
//    this->squaredAttenuation = squaredAttenuation;
//}
//
////This method sets the light's position.
//void Light::setPosition(Vector4 position)
//{
//    this->position = position;
//}
//
////This method returns the light's spotlight direction, if it has one.
//void Light::setSpotlightDirection(Vector4 spotlightDirection)
//{
//    this->spotlightDirection = spotlightDirection;
//}
//
////This method sets the light's spotlight cutoff.
//void Light::setSpotlightCutoff(float spotlightCutoff)
//{
//    this->spotlightCutoff = spotlightCutoff;
//}
//
////This method sets the light's spotlight exponent.
//void Light::setSpotlightExponent(float spotlightExponent)
//{
//    this->spotlightExponent = spotlightExponent;
//}
//
////This method sets the light's light amount.
//void Light::setLightAmount(float lightAmount)
//{
//    this->lightAmount = lightAmount;
//}
//
////----------------------------------Getters-----------------------------------//
//
////This method gets the light's diffuse color.
//Vector4 Light::getDiffuse()
//{
//    return this->diffuse;
//}
//
////This method gets the light's specular color.
//Vector4 Light::getSpecular()
//{
//    return this->specular;
//}
//
////This method gets the light's constant attenuation.
//float Light::getConstantAttenuation()
//{
//    return this->constantAttenuation;
//}
//
////This method gets the light's linear attenuation.
//float Light::getLinearAttenuation()
//{
//    return this->linearAttenuation;
//}
//
////This method gets the light's squared attenuation.
//float Light::getSquaredAttenuation()
//{
//    return this->squaredAttenuation;
//}
//
////This method gets the light's position.
//Vector4 Light::getPosition()
//{
//    return this->position;
//}
//
////This method returns the light's spotlight direction, if it has one.
//Vector4 Light::getSpotlightDirection()
//{
//    return this->spotlightDirection;
//}
//
////This method return the light's spotlight cutoff, if it has one.
//float Light::getSpotlightCutoff()
//{
//    return this->spotlightCutoff;
//}
//
////This method return the light's spotlight exponent, if it has one.
//float Light::getSpotlightExponent()
//{
//    return this->spotlightExponent;
//}
//
////This method gets the light's light amount.
//float Light::getLightAmount()
//{
//    return this->lightAmount;
//}
//
////-------------------------------Other Methods--------------------------------//
//
////This method converts the current light into a spotlight.
//void Light::makeSpotlight(Vector4 spotlightDirection, float spotlightCutoff, 
//    float spotlightExponent)
//{
//    this->setSpotlightDirection(spotlightDirection);
//    this->setSpotlightCutoff(spotlightCutoff);
//    this->setSpotlightExponent(spotlightExponent);
//}
//
////This method sets the light on if it is off, and vice versa.
//void Light::toggleLight()
//{
//    if(this->getLightAmount() == 1)
//        this->setLightAmount(0);
//    else
//        this->setLightAmount(1);
//}

}