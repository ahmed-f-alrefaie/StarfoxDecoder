//
//  OpenGLSFObject.cpp
//  starfox_decoder
//
//  Created by Ahmed Al-Refaie on 26/08/2017.
//  Copyright © 2017 Primalfido. All rights reserved.
//

#include "OpenGLSFObject.hpp"

void OpenGLSFObject::Draw(){
    
    /* We don't want to modify the projection matrix. */
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
    angle += 0.5f;
    //glrotate(transform.x, transform.y, transform.z);
    //
    frame+=0.2;
    
    glTranslatef(transform.x, transform.y, transform.z);
  //      glRotatef(180.0, 0.0, 0.0, 1.0);
    glRotatef(180.0, 0.0, 0.0, 1.0);
    glRotatef(angle,0.0,1.0,0.0);
    glScalef(0.1 ,0.1, 0.1);
    for(auto f : faces){
        
        if(f.num_sides == 2){
            glBegin(GL_LINES);
            glNormal3f(0.0, 0.0, 1.0);
            
        }else if(f.num_sides == 1)
            glBegin(GL_POINT);
        else{
            //continue;
            glBegin(GL_POLYGON);
            glNormal3f(f.normal.x, f.normal.y, f.normal.z);
        }
        
        for(int i=0; i < f.num_sides; i++){
            
            glm::vec3 position =vertices[f.vertex_index[i]].GetFrame(int(frame));
           glVertex3f(position.x,position.y,position.z);
        }
        glEnd();
    }
    
    
    
}

void OpenGLSFObject::Update(){};
