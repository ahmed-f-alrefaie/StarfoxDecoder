//
//  main.cpp
//  starfox_decoder
//
//  Created by Ahmed Al-Refaie on 23/08/2017.
//  Copyright © 2017 Primalfido. All rights reserved.
//

#include <iostream>
#include "SMCReader.hpp"
#include "OpenGLSFObject.hpp"
#include "StarFoxObjFormat.hpp"
#include "OpenGLRenderer.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    //SMCReader smc;
    smc.Initialize();
    OpenGLRenderer opengl;
    
    opengl.Initialize(640, 480);
    
    OpenGLSFObject arwing;
    arwing.ConstructObject();
    
    
    //std::cout <<"Arwing header address: "<<std::hex << StarfoxObjConverter::GetHeaderAddress(0x20D3)<<std::endl;
    
    
    //auto header = StarfoxObjConverter::GetHeaderInfo(0x20D3);
    
    //auto vertex = StarfoxObjConverter::ReadVertices(header);
    
    //auto face = StarfoxObjConverter::ReadFaces(header);
    
    //for(auto v : vertex)
    //{
    //    std::cout << v.position.x<<" "<< v.position.y<<" "<< v.position.z << std::endl;
    //}

    //for(auto v : face)
    //{
    //    std::cout << v.vertex_index[0]<<" "<< v.vertex_index[1]<<" "<< v.vertex_index[2]<< std::endl;
    //}
    
    while(true){
        opengl.BeginDraw();
        arwing.Draw();
        opengl.EndDraw();
    }
    
    
    return 0;
}
