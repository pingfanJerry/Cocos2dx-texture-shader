//
//  SimpleTextureShader.cpp
//  
//
//  Created by Tjaz Hrovat on 8/17/13.
//
//

#include "SimpleTextureShader.h"

using namespace cocos2d;

SimpleTextureShader::~SimpleTextureShader() {
    shaderProg->release();
}

bool SimpleTextureShader::init() {
    if ( !CCNode::init() )
        return false;
    
    //texture = (CCSprite::create("Icon.png"))->getTexture();
    texture = CCTextureCache::sharedTextureCache()->addImage("Icon.png");
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    ccV3F_C4B_T2F_Quad quad_tmp = {
//                   Position                                      Color                        Texture coord.
        { { 0.0f,             winSize.height,   0.0f },           {255, 255, 255, 255},          {0.0f, 1.0f} },
        { { 0.0f,             0.0f,             0.0f },           {255, 255, 255, 255},          {0.0f, 0.0f} },
        { { winSize.width,    winSize.height,   0.0f },           {255, 255, 255, 255},          {1.0f, 1.0f} },
        { { winSize.width,    0.0f,             0.0f },           {0, 0, 255, 255},          {1.0f, 0.0f} }
    };    
    quad = quad_tmp;
    
    //setContentSize(CCSizeMake(winSize.width * 0.5f, winSize.height * 0.5f));

    shaderProg = new CCGLProgram;
    shaderProg->initWithVertexShaderFilename("textureShader.vsh", "textureShader.fsh");
    setShaderProgram( shaderProg );
    
    CHECK_GL_ERROR_DEBUG();
    
    shaderProg->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
    shaderProg->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
    shaderProg->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
    
    shaderProg->link();    
    
    CHECK_GL_ERROR_DEBUG();
    
    shaderProg->updateUniforms();
    
    CHECK_GL_ERROR_DEBUG();
    
    shaderProg->setUniformsForBuiltins();
        
    return true;
    
    /*
    if ( !CCNode::init() )
        return false;
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    Quad quad_tmp = {
        //                   Position                                      Color
        { { 0.0f,             winSize.height },           {255, 255,   255,   255} },
        { { 0.0f,             0.0f           },           {255,   255, 255,   255} },
        { { winSize.width,    winSize.height },           {255,   255,   255, 255} },
        { { winSize.width,    0.0f           },           {255, 255, 255, 255} }
    };
    quad = quad_tmp;
    
    setContentSize(CCSizeMake(winSize.width, winSize.height));
    
    CCGLProgram *shaderProg = new CCGLProgram;
    shaderProg->initWithVertexShaderFilename("textureShader.vsh", "textureShader.fsh");
    setShaderProgram( shaderProg );
    
    CHECK_GL_ERROR_DEBUG();
    
    shaderProg->link();
    shaderProg->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
    shaderProg->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
    
    CHECK_GL_ERROR_DEBUG();
    
    shaderProg->updateUniforms();
    
    CHECK_GL_ERROR_DEBUG();
    
    shaderProg->setUniformsForBuiltins();
    
    return true;
*/
}

void SimpleTextureShader::draw() {
    glEnable(GL_CULL_FACE);
    shaderProg->use();
    shaderProg->updateUniforms();
    shaderProg->setUniformsForBuiltins();
    
    
    ccGLEnableVertexAttribs( kCCVertexAttribFlag_PosColorTex );
    
    int vertSize = sizeof(quad.bl);
    long offset = (long)&quad;
    
    //ccGLBindTexture2D( texture->getName() );
    
    //ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position | kCCVertexAttribFlag_Color );
    //glEnableVertexAttribArray(2);
    
    int diff = offsetof( ccV3F_C4B_T2F, vertices);
    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, vertSize, (GLvoid*) (offset + diff));
    diff = offsetof( ccV3F_C4B_T2F, colors);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, vertSize, (GLvoid*) (offset + diff));
    diff = offsetof( ccV3F_C4B_T2F, texCoords);
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, vertSize, (GLvoid*) (offset + diff));
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    CHECK_GL_ERROR_DEBUG();
    
    glDisable(GL_CULL_FACE);
        
    
    
    /*glEnable(GL_CULL_FACE);
    getShaderProgram()->use();
    getShaderProgram()->setUniformsForBuiltins();
    
    CCPoint p = getPosition();
    CCSize s = getContentSize();
    
    int vertSize = sizeof(quad.tl); // ccVertex2F & ccVertex4B
    long offset = (long)&quad;
    
    ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position | kCCVertexAttribFlag_Color);
    //  glEnableVertexAttribArray(kCCVertexAttribFlag_Position);
    //  glEnableVertexAttribArray(kCCVertexAttribFlag_Color);
    
    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, vertSize, (GLvoid*) (offset));
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, vertSize, (GLvoid*) (offset + sizeof(_ccVertex2F)));
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDisable(GL_CULL_FACE);
    */
    
}