//
//  OpenGLRenderer.cpp
//  starfox_decoder
//
//  Created by Ahmed Al-Refaie on 26/08/2017.
//  Copyright © 2017 Primalfido. All rights reserved.
//

#include "OpenGLRenderer.hpp"
#include <iostream>

void OpenGLRenderer::Initialize(int width, int height){

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to init SDL\n";
        exit(-1);
    }
    
    // Create our window centered at 512x512 resolution
    window = SDL_CreateWindow(
                                  "Starfox",
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  width,
                                  height,
                                  SDL_WINDOW_OPENGL
                                  );
    
    
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    
    
    context = SDL_GL_CreateContext
    (
     window
     );

    
    float ratio = (float) width / (float) height;
    
    /* Our shading model--Gouraud (smooth). */
    glShadeModel( GL_SMOOTH);
    
    /* Culling. */
    glCullFace( GL_BACK );
    glFrontFace( GL_CCW );
    glEnable( GL_CULL_FACE );
    glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    GLfloat lightpos[] = {.5, 0.0, -0.0f, 0.};
    GLfloat color[] = {.2, 0.2, 0.2f, 0.};
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, color);
    //glLightfv(GL_LIGHT0, GL_DIFFUSE, color);
    //glLightModelfv(GL_AMBIENT, color);
    
    
    /* Set the clear color. */
    glClearColor( 0, 0, 0, 0 );
    
    /* Setup our viewport. */
    glViewport( 0, 0, width, height );
    
    /*
     * Change to the projection matrix and set
     * our viewing volume.
     */
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    /*
     * EXERCISE:
     * Replace this with a call to glFrustum.
     */
    gluPerspective( 60.0, ratio, 1.0, 1024.0 );
    
    
}

void OpenGLRenderer::EndDraw(){
    
    SDL_GL_SwapWindow(window);
    
}

void OpenGLRenderer::BeginDraw(){
    
    /* Clear the color and depth buffers. */
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
}
