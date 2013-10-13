//
//  SimpleTextureShader.h
//  
//
//  Created by Tjaz Hrovat on 8/17/13.
//
//

#ifndef __Simple_Texture_Shader__
#define __Simple_Texture_Shader__

#include "cocos2d.h"

class SimpleTextureShader : public cocos2d::CCNode {
public:
    SimpleTextureShader() {}
    ~SimpleTextureShader();
    
    bool init();

private:   
    cocos2d::ccV3F_C4B_T2F_Quad quad;
    cocos2d::CCGLProgram *shaderProg;
    cocos2d::CCTexture2D *texture;
    void draw();
};

#endif