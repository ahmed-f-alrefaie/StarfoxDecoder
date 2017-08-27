//
//  OpenGLSFObject.hpp
//  starfox_decoder
//
//  Created by Ahmed Al-Refaie on 26/08/2017.
//  Copyright © 2017 Primalfido. All rights reserved.
//

#ifndef OpenGLSFObject_hpp
#define OpenGLSFObject_hpp

#include <stdio.h>
#include "StarFoxObjFormat.hpp"
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include "glm/glm.hpp"
class OpenGLSFObject : public StarFoxObject{
public:
    virtual void Update() override final;
    virtual void Draw() override final;
    float angle = 0.0;
    float frame = 0;
};

#endif /* OpenGLSFObject_hpp */
