#include "RenderQueue.h"

namespace GraphicsEngine
{

//RenderQueue::RenderQueue(SceneManager *sceneManager)
//{
//    //Storing the reference to the scene manager.
//    m_SceneManager = sceneManager;
//
//    //Initializing the renderable objects list.
//    //m_RenderableObjects = new std::vector<RenderableObject *>();
//    m_Lights = new std::unordered_map<std::string, Light *>();
//}
//
////This method sets the target render size.
//void RenderQueue::setRenderSize(int windowWidth, int windowHeight)
//{
//    width = windowWidth;
//    height = windowHeight;
//
//    //Initializing the render queue.
//    initializeRenderQueue();
//}
//
////This method adds a renderable object.
////void RenderQueue::addRenderableObject(RenderableObject *renderableObject)
////{
////    GLuint program = renderableObject->getOpenGLProgram()->getProgram();
////
////    m_RenderableObjects->push_back(renderableObject);
////
////    //Create a vertex array object and buffer object.
////    glGenVertexArraysOES(1, renderableObject->getBinding()->getVertexArrayLocation());
////    glBindVertexArrayOES(renderableObject->getBinding()->getVertexArray());
////    glGenBuffers(1, renderableObject->getBinding()->getVertexBufferLocation());
////    glGenBuffers(1, renderableObject->getBinding()->getNormalBufferLocation());
////
////    //Sending the vertex data to the graphics card.
////    glBindBuffer(GL_ARRAY_BUFFER,  renderableObject->getBinding()->getVertexBuffer());
////    glBufferData(GL_ARRAY_BUFFER, renderableObject->getMesh()->getVertexCount() * sizeof(Vector4), 
////        renderableObject->getMesh()->getVertices(), GL_STATIC_DRAW);
////
////    //Telling the graphics card that the data passed corresponds to vertex 
////    //data.
////    GLuint vertexPosition_Shader = glGetAttribLocation(program, "vertexPosition");
////    glEnableVertexAttribArray(vertexPosition_Shader);
////    glVertexAttribPointer(vertexPosition_Shader, 4, GL_FLOAT, GL_FALSE, 0, 0);
////
////    //Sending the normal data to the graphics card.
////    glBindBuffer(GL_ARRAY_BUFFER, renderableObject->getBinding()->getNormalBuffer());
////    glBufferData(GL_ARRAY_BUFFER, renderableObject->getMesh()->getVertexCount() * sizeof(Vector4), 
////        renderableObject->getMesh()->getNormals(), GL_STATIC_DRAW);
////
////    //Telling the graphics card that the data passed corresponds to normal data.
////    GLuint vertexNormal_Shader = glGetAttribLocation(program, "vertexNormal");
////    glEnableVertexAttribArray(vertexNormal_Shader);
////    glVertexAttribPointer(vertexNormal_Shader, 4, GL_FLOAT, GL_FALSE, 0, 0);
////
////    //If we have textures, send the texture coordinates to the buffer.
////    if(renderableObject->getNumberOfTextures() > 0)
////    {
////        glGenBuffers(1, renderableObject->getBinding()->getTextureBufferLocation());
////        glBindBuffer(GL_ARRAY_BUFFER, renderableObject->getBinding()->getTextureBuffer());
////        glBufferData(GL_ARRAY_BUFFER, renderableObject->getMesh()->getVertexCount() * sizeof(vec2), 
////            renderableObject->getMesh()->getTextureCoordinates(), GL_STATIC_DRAW);
////
////        texCoords_Shader = glGetAttribLocation(program, "vertexTextureCoordinates");
////        glEnableVertexAttribArray(texCoords_Shader);
////        glVertexAttribPointer(texCoords_Shader, 2, GL_FLOAT, GL_FALSE, 0, 0);
////    }
////
////    //Iterating through each texture.
////    for(std::vector<Texture *>::iterator it = 
////        renderableObject->getTexturesVector()->begin(); it != 
////        renderableObject->getTexturesVector()->end(); it++)
////    {
////        ILuint imagePointer[1];
////        ilGenImages(1, imagePointer);
////        ilBindImage(imagePointer[0]);
////        loadTexFile((*it)->getFilePath().c_str());
////
////        glGenTextures(1, (*it)->getTextureLocation());
////        glBindTexture(GL_TEXTURE_2D, (*it)->getTexture());
////        glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), 
////            ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0,
////            ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_TYPE), ilGetData());
////        glGenerateMipmap(GL_TEXTURE_2D);
////
////        ilDeleteImages(1, imagePointer);
////
////        //Setting the texture parameters.
////        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
////        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
////        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
////        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
////    }
////}
//
////This method adds a light.
//void RenderQueue::addLight(Light *light, std::string name)
//{
//    m_Lights->insert(std::make_pair(name, light));
//
//    this->light = light;
//}
//
////This method renders the scene.
//void RenderQueue::renderScene(float motionBlurs)
//{
////    // bind the second (render-to-texture) framebuffer
////    glBindFramebuffer (GL_FRAMEBUFFER, bufferFBO);
////    // clear the framebuffer's colour and depth buffers
////    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
////
////    //Computing the projection matrix.
////    Matrix4 projection = perspective(m_SceneManager->getCurrentCamera()->getFOV(),
////            (float) width / (float) height, 0.05, 100);
////
////
////    //Looping through the renderable groups.
////    for(std::vector<RenderableObject *>::iterator it =
////        m_RenderableObjects->begin();
////        it != m_RenderableObjects->end(); it++)
////    {
////        RenderableObject *rO = *it;
////        
////        OpenGLProgram *program = rO->getOpenGLProgram();
////        glUseProgram(program->getProgram());
////
////        //Sending the GPU the current model-view matrix.
////        glUniformMatrix4fv(program->getPointer("currentModelView"), 1, GL_TRUE, 
////            m_SceneManager->getCurrentCamera()->getPreviousLookAtMatrix() * rO->getCurrentWorldTransform());
////        glUniformMatrix4fv(program->getPointer("previousModelView"), 1, GL_TRUE, 
////            m_SceneManager->getCurrentCamera()->getCurrentLookAtMatrix() * rO->getPreviousWorldTransform());
////        glUniformMatrix4fv(program->getPointer("projection"), 1, GL_TRUE, projection);
////        
////        glUniform4fv(program->getPointer("lightPosition"), 1, 
////            m_SceneManager->getCurrentCamera()->getCurrentLookAtMatrix() * light->getPosition());
////        glUniform4fv(program->getPointer("lightDiffuse"), 1, light->getDiffuse());
////        glUniform4fv(program->getPointer("lightSpecular"), 1, light->getSpecular());
////        
////        //Sending the GPU the mesh's material properties.
////        glUniform4fv(program->getPointer("materialAmbient"), 1, rO->getMaterial()->getAmbient());
////        glUniform4fv(program->getPointer("materialDiffuse"), 1, rO->getMaterial()->getDiffuse());
////        glUniform4fv(program->getPointer("materialSpecular"), 1, rO->getMaterial()->getSpecular());
////        glUniform4fv(program->getPointer("materialEmissive"), 1, rO->getMaterial()->getEmissive());
////        glUniform1f(program->getPointer("materialShininess"), rO->getMaterial()->getShininess());
////        
////        //Binding the GPU to the current mesh.
////        glBindVertexArray(rO->getBinding()->getVertexArray());
////        
////        for(std::vector<Texture *>::iterator it = rO->getTexturesVector()->begin();
////            it != rO->getTexturesVector()->end(); it++)
////        {
////            Texture *texture = *it;
////
////            glActiveTexture(GL_TEXTURE0 + texture->getTextureUnit());
////            glBindTexture(GL_TEXTURE_2D, texture->getTexture());
////        }
////        
////        //Telling the GPU to draw the mesh.
////        glDrawArrays(GL_TRIANGLES, 0, rO->getMesh()->getVertexCount());
////    }
////
////    //=================================Create Near and Far textures
////
////    glBindFramebuffer(GL_FRAMEBUFFER, postFBO);
////
////    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 
////        nearTexture, 0);
////    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, 
////        farTexture, 0);
////
////    // clear the framebuffer's colour and depth buffers
////    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
////    // our our post-processing shader for the screen-space quad
////    glUseProgram (this->createDepthAndSharpProgram);
////
////    glUniformMatrix4fv(projection_ShaderNew, 1, GL_TRUE, projection);
////    glUniform1f(focusPlane_Shader, m_SceneManager->getCurrentCamera()->getPlaneInFocusDistance());
////    glUniform1f(focalLength_Shader, m_SceneManager->getCurrentCamera()->getFocalLength());
////    glUniform1f(apertureSize_Shader, m_SceneManager->getCurrentCamera()->getApertureSize());
////
////    // bind the quad's VAO
////    glBindVertexArray (vao);
////    // activate the first texture slot and put texture from previous pass in it 
////    glActiveTexture(GL_TEXTURE0);
////    glBindTexture(GL_TEXTURE_2D, depthTexture);
////    glActiveTexture(GL_TEXTURE1);
////    glBindTexture(GL_TEXTURE_2D, sharpTexture);
////    glDrawArrays(GL_TRIANGLES, 0, 6);
////
////    //============================BLOOM CODE
////    glViewport(0, 0, width / 2, height / 2);
////
////    glBindFramebuffer(GL_FRAMEBUFFER, smallFBO);
////
////    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
////
////    glUseProgram(this->bloomProgram);
////    glActiveTexture (GL_TEXTURE0);
////    glBindTexture(GL_TEXTURE_2D, sharpTexture);
////    glDrawArrays(GL_TRIANGLES, 0, 6);
////
////
////    glViewport(0, 0, width / 4, height / 4);
////
////    glBindFramebuffer(GL_FRAMEBUFFER, quarterFBO);
////    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 
////        quarterTexture, 0);
////
////    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
////
////    glUseProgram(this->downsampleBlurProgram);
////    glActiveTexture (GL_TEXTURE0);
////    glBindTexture(GL_TEXTURE_2D, smallTexture);
////    glDrawArrays(GL_TRIANGLES, 0, 6);
////
////    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 
////        quarterTextureTemp, 0);
////    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
////    glUseProgram(this->horizontalForegroundBlurProgram);
////    glActiveTexture (GL_TEXTURE0);
////    glBindTexture(GL_TEXTURE_2D, quarterTexture);
////    glDrawArrays(GL_TRIANGLES, 0, 6);
////
////    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 
////        quarterTexture, 0);
////    glUseProgram(this->verticalForegroundBlurProgram);
////    glActiveTexture (GL_TEXTURE0);
////    glBindTexture(GL_TEXTURE_2D, quarterTextureTemp);
////    glDrawArrays(GL_TRIANGLES, 0, 6);
////
////    //===========================DOF Blurring
////
////    glViewport(0, 0, width, height);
////    glBindFramebuffer(GL_FRAMEBUFFER, postFBO);
////    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 
////        nearTextureTemp, 0);
////    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, 
////        farTextureTemp, 0);
////
////    glUseProgram(this->horizontalBlurProgram);
////    glBindVertexArray(vao);
////    glActiveTexture (GL_TEXTURE0);
////    glBindTexture(GL_TEXTURE_2D, nearTexture);
////    glActiveTexture (GL_TEXTURE1);
////    glBindTexture(GL_TEXTURE_2D, farTexture);
////    glDrawArrays(GL_TRIANGLES, 0, 6);
////
////    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 
////        sharpTextureTemp, 0);
////    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, 
////        0, 0);
////
////    glUseProgram (this->verticalBlurProgram);
////    glActiveTexture (GL_TEXTURE0);
////    glBindTexture(GL_TEXTURE_2D, nearTextureTemp);
////    glActiveTexture (GL_TEXTURE1);
////    glBindTexture(GL_TEXTURE_2D, farTextureTemp);
////    glActiveTexture (GL_TEXTURE2);
////    glBindTexture(GL_TEXTURE_2D, sharpTexture);
////    glDrawArrays(GL_TRIANGLES, 0, 6);
////
////
////    //================================Motion Blur Code
////    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 
////        sharpTexture, 0);
////    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, 
////        0, 0);
////    
////    glUseProgram(this->velocityProgram);
////    glBindVertexArray(vao);
////    glActiveTexture (GL_TEXTURE0);
////    glBindTexture(GL_TEXTURE_2D, sharpTextureTemp);
////    glActiveTexture (GL_TEXTURE1);
////    glBindTexture(GL_TEXTURE_2D, velocityTexture);
////    glUniform1f(motionBlur, motionBlurs);
////    glDrawArrays(GL_TRIANGLES, 0, 6);
////
////    //===========================Composite Textures
////
////    glViewport(0, 0, width, height);
////
////    // bind default framebuffer
////    glBindFramebuffer(GL_FRAMEBUFFER, 0);
////    // clear the framebuffer's colour and depth buffers
////    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
////    // our our post-processing shader for the screen-space quad
////    glUseProgram (this->combineProgram);
////
////    // bind the quad's VAO
////    glBindVertexArray (vao);
////    // activate the first texture slot and put texture from previous pass in it
////    glActiveTexture (GL_TEXTURE0);
////    glBindTexture(GL_TEXTURE_2D, sharpTexture);
////    glActiveTexture (GL_TEXTURE1);
////    glBindTexture(GL_TEXTURE_2D, quarterTexture);
////    glDrawArrays (GL_TRIANGLES, 0, 6);
////
////    //Swapping the buffers now that the drawing is complete.
////    glutSwapBuffers();
//    
//    
//    
//    
//    
//    
//    
//    
//    
//    
//    
//    
//    
//    
//    
//    
////    //Mesh VAO and VBO setup.
////    glGenVertexArraysOES(1, &_vertexArray);
////    glBindVertexArrayOES(_vertexArray);
////    
////    glGenBuffers(1, &_vertexBuffer);
////    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
////    glBufferData(GL_ARRAY_BUFFER, mesh->getDataCount() * sizeof(float),
////                 mesh->getData(), GL_DYNAMIC_DRAW);
////    
////    if(mesh->getDataFormat() == GraphicsEngine::Position)
////    {
////        glEnableVertexAttribArray(vPNew);
////        glVertexAttribPointer(vPNew, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), BUFFER_OFFSET(0));
////    }
////    else if(mesh->getDataFormat() == GraphicsEngine::PositionNormals)
////    {
////        glEnableVertexAttribArray(vPNew);
////        glVertexAttribPointer(vPNew, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), BUFFER_OFFSET(0));
////        glEnableVertexAttribArray(vNNew);
////        glVertexAttribPointer(vNNew, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), BUFFER_OFFSET(12));
////    }
////    else if(mesh->getDataFormat() == GraphicsEngine::PositionTexture)
////    {
////        glEnableVertexAttribArray(vPNew);
////        glVertexAttribPointer(vPNew, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), BUFFER_OFFSET(0));
////        glEnableVertexAttribArray(vNNew);
////        glVertexAttribPointer(vNNew, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), BUFFER_OFFSET(12));
////    }
////    else if(mesh->getDataFormat() == GraphicsEngine::PositionNormalsTexture)
////    {
////        glEnableVertexAttribArray(vPNew);
////        glVertexAttribPointer(vPNew, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), BUFFER_OFFSET(0));
////        glEnableVertexAttribArray(vNNew);
////        glVertexAttribPointer(vNNew, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), BUFFER_OFFSET(12));
////        glEnableVertexAttribArray(vTNew);
////        glVertexAttribPointer(vTNew, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), BUFFER_OFFSET(24));
////    }
//}
//
//
//
//
//
//
//
//
//
//
//
//
////This method initializes the render queue.
//void RenderQueue::initializeRenderQueue()
//{
////    ilInit(); /* Initialization of OpenIL */
////
////    //glEnable(GL_BLEND);
////    //glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
////
////    //============================Texture Creation============================//
////
////    //Sharp Texture.
////    glGenTextures(1, &sharpTexture);
////    glBindTexture(GL_TEXTURE_2D, sharpTexture);
////    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, 
////        GL_UNSIGNED_BYTE, 0);
////    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
////    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
////    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
////    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
////
////    //Sharp Texture Temp.
////    glGenTextures(1, &sharpTextureTemp);
////    glBindTexture(GL_TEXTURE_2D, sharpTextureTemp);
////    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, 
////        GL_UNSIGNED_BYTE, 0);
////    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
////    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
////    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
////    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
////
////    //Near Texture.
////    glGenTextures(1, &nearTexture);
////    glBindTexture(GL_TEXTURE_2D, nearTexture);
////    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, 
////        GL_UNSIGNED_BYTE, 0);
////    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
////    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
////    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
////    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
////
////    //Near Texture.
////    glGenTextures(1, &nearTextureTemp);
////    glBindTexture(GL_TEXTURE_2D, nearTextureTemp);
////    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, 
////        GL_UNSIGNED_BYTE, 0);
////    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
////    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
////    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
////    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
////
////    //Far Texture.
////    glGenTextures(1, &farTexture);
////    glBindTexture(GL_TEXTURE_2D, farTexture);
////    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, 
////        GL_UNSIGNED_BYTE, 0);
////    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
////    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
////    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
////    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
////
////    //Far Texture.
////    glGenTextures(1, &farTextureTemp);
////    glBindTexture(GL_TEXTURE_2D, farTextureTemp);
////    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, 
////        GL_UNSIGNED_BYTE, 0);
////    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
////    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
////    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
////    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
////
////    //Depth Texture.
////    glGenTextures(1, &depthTexture);
////    glBindTexture(GL_TEXTURE_2D, depthTexture);
////    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, 
////        GL_DEPTH_COMPONENT, GL_FLOAT, 0);
////    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
////    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
////    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
////    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
////
////    //Small Texture.
////    glGenTextures(1, &smallTexture);
////    glBindTexture(GL_TEXTURE_2D, smallTexture);
////    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width / 2, height / 2, 0, 
////        GL_RGBA, GL_UNSIGNED_BYTE, 0);
////    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
////    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
////    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
////    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
////
////    //Quarter Texture.
////    glGenTextures(1, &quarterTexture);
////    glBindTexture(GL_TEXTURE_2D, quarterTexture);
////    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width / 4, height / 4, 0, 
////        GL_RGBA, GL_UNSIGNED_BYTE, 0);
////    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
////    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
////    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
////    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
////
////    //Quarter Texture.
////    glGenTextures(1, &quarterTextureTemp);
////    glBindTexture(GL_TEXTURE_2D, quarterTextureTemp);
////    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width / 4, height / 4, 0, 
////        GL_RGBA, GL_UNSIGNED_BYTE, 0);
////    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
////    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
////    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
////    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
////
////    //Quarter Texture.
////    glGenTextures(1, &velocityTexture);
////    glBindTexture(GL_TEXTURE_2D, velocityTexture);
////    glTexImage2D(GL_TEXTURE_2D, 0, GL_RG16F, width, height, 0, 
////        GL_RG, GL_FLOAT, 0);
////    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
////    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
////    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
////    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
////
////    //==========================Framebuffer Creation==========================//
////
////    glGenFramebuffers (1, &bufferFBO);
////    glBindFramebuffer(GL_FRAMEBUFFER, bufferFBO);
////
////    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 
////        sharpTexture, 0);
////    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, 
////        velocityTexture, 0);
////    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, 
////        depthTexture, 0);
////
////    GLenum draw_bufsBuffer[2] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
////    glDrawBuffers (2, draw_bufsBuffer);
////
////
////    
////    glGenFramebuffers (1, &postFBO);
////    glBindFramebuffer(GL_FRAMEBUFFER, postFBO);
////
////    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 
////        nearTexture, 0);
////    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, 
////        farTexture, 0);
////
////    GLenum draw_bufs[2] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
////    glDrawBuffers (2, draw_bufs);
////
////    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
////        std::cout << "Framebuffer Error!\n";
////
////
////
////
////    glViewport(0, 0, width / 2, height / 2);
////    glGenFramebuffers (1, &smallFBO);
////    glBindFramebuffer(GL_FRAMEBUFFER, smallFBO);
////
////    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 
////        smallTexture, 0);
////
////    GLenum draw_bufs2[1] = {GL_COLOR_ATTACHMENT0};
////    glDrawBuffers (1, draw_bufs2);
////
////    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
////        std::cout << "Framebuffer Error!\n";
////
////
////
////
////
////    glViewport(0, 0, width / 4, height / 4);
////    glGenFramebuffers (1, &quarterFBO);
////    glBindFramebuffer(GL_FRAMEBUFFER, quarterFBO);
////
////    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 
////        quarterTexture, 0);
////
////    GLenum draw_bufs3[1] = {GL_COLOR_ATTACHMENT0};
////    glDrawBuffers (1, draw_bufs3);
////
////    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
////        std::cout << "Framebuffer Error!\n";
////
////    glViewport(0, 0, width, height);
////
////    //=====================2
////
////    /*glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, 
////        fb_texture22, 0);*/
////
////    // x,y vertex positions
////    float ss_quad_pos[] = {
////      -1.0, -1.0,
////       1.0, -1.0,
////       1.0,  1.0,
////       1.0,  1.0,
////      -1.0,  1.0,
////      -1.0, -1.0
////    };
////    // per-vertex texture coordinates
////    float ss_quad_st[] = {
////      0.0, 0.0,
////      1.0, 0.0,
////      1.0, 1.0,
////      1.0, 1.0,
////      0.0, 1.0,
////      0.0, 0.0
////    };
////    
////    //Create a vertex array object and buffer object.
////    glGenVertexArrays(1, &vao);
////    glBindVertexArray(vao);
////
////    glGenBuffers(1, &vboPosition);
////    glBindBuffer(GL_ARRAY_BUFFER,  vboPosition);
////    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vector4), 
////        ss_quad_pos, GL_STATIC_DRAW);
////
////    glGenBuffers(1, &vboTexture);
////    glBindBuffer(GL_ARRAY_BUFFER, vboTexture);
////    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(vec2), ss_quad_st, GL_STATIC_DRAW);
////
////
////
////    createDepthAndSharpProgram = InitShader("CreateCoC-Vertex.glsl", 
////        "CreateCoC-Fragment.glsl");
////
////    glBindBuffer(GL_ARRAY_BUFFER,  vboPosition);
////    GLuint a = glGetAttribLocation(createDepthAndSharpProgram, "vp");
////    glEnableVertexAttribArray(a);
////    glVertexAttribPointer(a, 2, GL_FLOAT, GL_FALSE, 0, 0);
////
////    glBindBuffer(GL_ARRAY_BUFFER, vboTexture);
////    a = glGetAttribLocation(createDepthAndSharpProgram, "vt");
////    glEnableVertexAttribArray(a);
////    glVertexAttribPointer(a, 2, GL_FLOAT, GL_FALSE, 0, 0);
////
////    glUniform1i(glGetUniformLocation(createDepthAndSharpProgram, "sharp"), 1);
////    glUniform1i(glGetUniformLocation(createDepthAndSharpProgram, "depth"), 0);
////
////    focalLength_Shader = glGetUniformLocation(createDepthAndSharpProgram, "focalLength");
////    focusPlane_Shader = glGetUniformLocation(createDepthAndSharpProgram, "focusPlane");
////    apertureSize_Shader = glGetUniformLocation(createDepthAndSharpProgram, "apertureSize");
////    projection_ShaderNew = glGetUniformLocation(createDepthAndSharpProgram, "projection");
////
////
////
////    horizontalBlurProgram = InitShader("HorizontalBlur-Vertex.glsl", "HorizontalBlur-Fragment.glsl");
////
////    //Telling the graphics card that the data passed corresponds to vertex 
////    //data.
////    glBindBuffer(GL_ARRAY_BUFFER,  vboPosition);
////    a = glGetAttribLocation(horizontalBlurProgram, "vp");
////    glEnableVertexAttribArray(a);
////    glVertexAttribPointer(a, 2, GL_FLOAT, GL_FALSE, 0, 0);
////
////    glBindBuffer(GL_ARRAY_BUFFER, vboTexture);
////    a = glGetAttribLocation(horizontalBlurProgram, "vt");
////    glEnableVertexAttribArray(a);
////    glVertexAttribPointer(a, 2, GL_FLOAT, GL_FALSE, 0, 0);
////
////    glUniform1i(glGetUniformLocation(horizontalBlurProgram, "near"), 0);
////    glUniform1i(glGetUniformLocation(horizontalBlurProgram, "far"), 1);
////
////
////
////    verticalBlurProgram = InitShader("VerticalBlur-Vertex.glsl", 
////        "VerticalBlur-Fragment.glsl");
////
////    //Telling the graphics card that the data passed corresponds to vertex 
////    //data.
////    glBindBuffer(GL_ARRAY_BUFFER, vboPosition);
////    a = glGetAttribLocation(verticalBlurProgram, "vp");
////    glEnableVertexAttribArray(a);
////    glVertexAttribPointer(a, 2, GL_FLOAT, GL_FALSE, 0, 0);
////
////    glBindBuffer(GL_ARRAY_BUFFER, vboTexture);
////    a = glGetAttribLocation(verticalBlurProgram, "vt");
////    glEnableVertexAttribArray(a);
////    glVertexAttribPointer(a, 2, GL_FLOAT, GL_FALSE, 0, 0);
////
////    glUniform1i(glGetUniformLocation(verticalBlurProgram, "near"), 0);
////    glUniform1i(glGetUniformLocation(verticalBlurProgram, "far"), 1);
////    glUniform1i(glGetUniformLocation(verticalBlurProgram, "sharp"), 2);
////
////    verticalForegroundBlurProgram = InitShader("VerticalForegroundBlur-Vertex.glsl", 
////        "VerticalForegroundBlur-Fragment.glsl");
////
////    //Telling the graphics card that the data passed corresponds to vertex 
////    //data.
////    glBindBuffer(GL_ARRAY_BUFFER, vboPosition);
////    a = glGetAttribLocation(verticalForegroundBlurProgram, "vp");
////    glEnableVertexAttribArray(a);
////    glVertexAttribPointer(a, 2, GL_FLOAT, GL_FALSE, 0, 0);
////
////    glBindBuffer(GL_ARRAY_BUFFER, vboTexture);
////    a = glGetAttribLocation(verticalForegroundBlurProgram, "vt");
////    glEnableVertexAttribArray(a);
////    glVertexAttribPointer(a, 2, GL_FLOAT, GL_FALSE, 0, 0);
////
////    glUniform1i(glGetUniformLocation(verticalForegroundBlurProgram, "near"), 0);
////
////
////
////    horizontalForegroundBlurProgram = InitShader("HorizontalForegroundBlur-Vertex.glsl", 
////        "HorizontalForegroundBlur-Fragment.glsl");
////
////    //Telling the graphics card that the data passed corresponds to vertex 
////    //data.
////    glBindBuffer(GL_ARRAY_BUFFER, vboPosition);
////    a = glGetAttribLocation(horizontalForegroundBlurProgram, "vp");
////    glEnableVertexAttribArray(a);
////    glVertexAttribPointer(a, 2, GL_FLOAT, GL_FALSE, 0, 0);
////
////    glBindBuffer(GL_ARRAY_BUFFER, vboTexture);
////    a = glGetAttribLocation(horizontalForegroundBlurProgram, "vt");
////    glEnableVertexAttribArray(a);
////    glVertexAttribPointer(a, 2, GL_FLOAT, GL_FALSE, 0, 0);
////
////    glUniform1i(glGetUniformLocation(horizontalForegroundBlurProgram, "near"), 0);
////
////
////
////
////    downsampleBlurProgram = InitShader("DownsampleBlur-Vertex.glsl", 
////        "DownsampleBlur-Fragment.glsl");
////
////    //Telling the graphics card that the data passed corresponds to vertex 
////    //data.
////    glBindBuffer(GL_ARRAY_BUFFER, vboPosition);
////    a = glGetAttribLocation(downsampleBlurProgram, "vp");
////    glEnableVertexAttribArray(a);
////    glVertexAttribPointer(a, 2, GL_FLOAT, GL_FALSE, 0, 0);
////
////    glBindBuffer(GL_ARRAY_BUFFER, vboTexture);
////    a = glGetAttribLocation(downsampleBlurProgram, "vt");
////    glEnableVertexAttribArray(a);
////    glVertexAttribPointer(a, 2, GL_FLOAT, GL_FALSE, 0, 0);
////
////    glUniform1i(glGetUniformLocation(downsampleBlurProgram, "fullSize"), 0);
////
////
////
////
////    bloomProgram = InitShader("BloomCreate-Vertex.glsl", 
////        "BloomCreate-Fragment.glsl");
////
////    //Telling the graphics card that the data passed corresponds to vertex 
////    //data.
////    glBindBuffer(GL_ARRAY_BUFFER, vboPosition);
////    a = glGetAttribLocation(bloomProgram, "vp");
////    glEnableVertexAttribArray(a);
////    glVertexAttribPointer(a, 2, GL_FLOAT, GL_FALSE, 0, 0);
////
////    glBindBuffer(GL_ARRAY_BUFFER, vboTexture);
////    a = glGetAttribLocation(bloomProgram, "vt");
////    glEnableVertexAttribArray(a);
////    glVertexAttribPointer(a, 2, GL_FLOAT, GL_FALSE, 0, 0);
////
////    glUniform1i(glGetUniformLocation(bloomProgram, "inputColor"), 0);
////
////
////
////
////    velocityProgram = InitShader("MotionBlur-Vertex.glsl", 
////        "MotionBlur-Fragment.glsl");
////
////    //Telling the graphics card that the data passed corresponds to vertex 
////    //data.
////    glBindBuffer(GL_ARRAY_BUFFER, vboPosition);
////    a = glGetAttribLocation(velocityProgram, "vp");
////    glEnableVertexAttribArray(a);
////    glVertexAttribPointer(a, 2, GL_FLOAT, GL_FALSE, 0, 0);
////
////    glBindBuffer(GL_ARRAY_BUFFER, vboTexture);
////    a = glGetAttribLocation(velocityProgram, "vt");
////    glEnableVertexAttribArray(a);
////    glVertexAttribPointer(a, 2, GL_FLOAT, GL_FALSE, 0, 0);
////
////    glUniform1i(glGetUniformLocation(velocityProgram, "sharp"), 0);
////    glUniform1i(glGetUniformLocation(velocityProgram, "velocity"), 1);
////    motionBlur = glGetUniformLocation(velocityProgram, "motionBlur");
////
////
////    combineProgram = InitShader("Combine-Vertex.glsl", 
////        "Combine-Fragment.glsl");
////
////    //Telling the graphics card that the data passed corresponds to vertex 
////    //data.
////    glBindBuffer(GL_ARRAY_BUFFER, vboPosition);
////    a = glGetAttribLocation(combineProgram, "vp");
////    glEnableVertexAttribArray(a);
////    glVertexAttribPointer(a, 2, GL_FLOAT, GL_FALSE, 0, 0);
////
////    glBindBuffer(GL_ARRAY_BUFFER, vboTexture);
////    a = glGetAttribLocation(combineProgram, "vt");
////    glEnableVertexAttribArray(a);
////    glVertexAttribPointer(a, 2, GL_FLOAT, GL_FALSE, 0, 0);
////
////    glUniform1i(glGetUniformLocation(combineProgram, "sharp"), 0);
////    glUniform1i(glGetUniformLocation(combineProgram, "bloom"), 1);
//}

}