#ifndef _RENDERQUEUE_H_
#define _RENDERQUEUE_H_

//#include <unordered_map>
//#include <string>
//#include <vector>
//#include "MathLibrary.h"
//#include "Light.h"
//#include <OpenGLES/ES2/gl.h>
//
//namespace GraphicsEngine
//{
//    
//    class SceneManager;
//
//class RenderQueue
//{
//public:
//
//    RenderQueue(SceneManager *sceneManager);
//
//    //This method adds a renderable object.
//    //void addRenderableObject(RenderableObject *renderableObject);
//
//    //This method adds a light.
//    void addLight(Light *light, std::string name);
//
//    //This method sets the target render size.
//    void setRenderSize(int windowWidth, int windowHeight);
//
//    //This method renders the scene.
//    void renderScene(float motionBlur);
//
//private:
//
//    //The scene manager this render queue belongs to.
//    SceneManager *m_SceneManager;
//
//    //This is the list of objects that are to be rendered.
//    //std::vector<RenderableObject *> *m_RenderableObjects;
//
//    //The unordered map of lights.
//    std::unordered_map<std::string, Light *> *m_Lights;
//
//    Light *light;
//
//    int width, height;
//
//    //An array of OpenGL programs.
//    GLuint ambientSceneColor_Shader;
//    GLuint lightPosition_Shader, lightDiffuse_Shader, lightSpecular_Shader;
//    GLuint materialAmbient_Shader, materialDiffuse_Shader, 
//        materialSpecular_Shader, materialEmissive_Shader, 
//        materialShininess_Shader;
//    GLuint modelView_Shader, projection_Shader;
//    GLuint texCoords_Shader, textureImage;
//
//    GLuint bufferFBO, postFBO, depthTexture, sharpTexture, sharpTextureTemp, nearTexture, motionBlur,
//        nearTextureTemp, bloomProgram, velocityTexture, velocityProgram, combineProgram,   
//        farTexture, farTextureTemp, smallTexture, quarterTexture, quarterTextureTemp, 
//        vao, vboPosition, vboTexture, createDepthAndSharpProgram, verticalBlurProgram, 
//        horizontalBlurProgram, verticalForegroundBlurProgram, horizontalForegroundBlurProgram, 
//        focalLength_Shader, focusPlane_Shader, apertureSize_Shader, smallFBO, quarterFBO, downsampleBlurProgram, 
//        projection_ShaderNew;
//
//
//
//    GLuint program2, program3, 
//        focalLength2, focusPlane2, apertureSize2, projection_Shader22, programBlur,programBlurV;
//
//    //This method initializes the render queue.
//    void initializeRenderQueue();
//};
//
//}

#endif