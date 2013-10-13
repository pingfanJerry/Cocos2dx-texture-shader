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
        
    texture = CCTextureCache::sharedTextureCache()->addImage("wolf.png");
        
    CCSize texSize = texture->getContentSizeInPixels();
    
    ccV3F_C4B_T2F_Quad quad_tmp = {
//                   Position                                      Color                        Texture coord.
        { { 0.0f,             texSize.height,   0.0f },           {255, 255, 255, 255},          {1.0f, 0.0f} },
        { { 0.0f,             0.0f,             0.0f },           {255, 255, 255, 255},          {1.0f, 1.0f} },
        { { texSize.width,    texSize.height,   0.0f },           {255, 255, 255, 255},          {0.0f, 0.0f} },
        { { texSize.width,    0.0f,             0.0f },           {255, 255, 255, 255},          {0.0f, 1.0f} }
    };    
    quad = quad_tmp;

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
}

void SimpleTextureShader::draw() {
    glEnable(GL_CULL_FACE);
    shaderProg->use();    
    shaderProg->setUniformsForBuiltins();
    
    
    ccGLEnableVertexAttribs( kCCVertexAttribFlag_PosColorTex );
    
    int vertSize = sizeof(quad.bl);
    long offset = (long)&quad;
    
    ccGLBindTexture2D( texture->getName() );
    
    int diff = offsetof( ccV3F_C4B_T2F, vertices);
    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, vertSize, (GLvoid*) (offset + diff));
    diff = offsetof( ccV3F_C4B_T2F, colors);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, vertSize, (GLvoid*) (offset + diff));
    diff = offsetof( ccV3F_C4B_T2F, texCoords);
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, vertSize, (GLvoid*) (offset + diff));
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    CHECK_GL_ERROR_DEBUG();
    
    glDisable(GL_CULL_FACE);
        
}