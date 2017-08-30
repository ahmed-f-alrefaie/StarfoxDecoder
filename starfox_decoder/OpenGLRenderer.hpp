//
//  OpenGLRenderer.hpp
//  starfox_decoder
//
//  Created by Ahmed Al-Refaie on 26/08/2017.
//  Copyright © 2017 Primalfido. All rights reserved.
//

#ifndef OpenGLRenderer_hpp
#define OpenGLRenderer_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>





class OpenGLRenderer{
private:
    int window_width,window_height;
    
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_GLContext context;
public:
    void Initialize(int width,int height);
    void BeginDraw();
    void EndDraw();
    void Cleanup();
    
    
    
    
    
    
};




#endif /* OpenGLRenderer_hpp */
