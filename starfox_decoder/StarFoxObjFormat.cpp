//
//  StarFoxObjFormat.cpp
//  starfox_decoder
//
//  Created by Ahmed Al-Refaie on 25/08/2017.
//  Copyright © 2017 Primalfido. All rights reserved.
//

#include "StarFoxObjFormat.hpp"
#include "StarfoxObjConverter.hpp"

glm::vec3 computeNormal(
                        glm::vec3 const & a,
                        glm::vec3 const & b,
                        glm::vec3 const & c)
{
    return glm::normalize(glm::cross(c - a, b - a));
}

void StarFoxObject::ConstructObject(){
   // object_id = 0x84DD;
 //  object_id = 0x20D3;
   // object_id=0x68DD;
   // object_id=0xD0BC;
  //  object_id = 0x60D1; //Andross
    //object_id = 0x49B4;
  //object_id = 0x69AC;
    //object_id = 0xB4E6;
  //  object_id = 0xA1AC;
   // object_id = 0xB4CA;
   // object_id = 0x83B9;
    object_id = 0x94C4;
   // object_id = 0x4BB9;
    auto header = StarfoxObjConverter::GetHeaderInfo(object_id);
    vertices = StarfoxObjConverter::ReadVertices(header);
    faces = StarfoxObjConverter::ReadFaces(header);
    transform[0] = 0.0;
    transform[1] = -2.0;
    transform[2] = -15.0;
    

    
    for(auto & f: faces){
        f.normal= glm::vec3(0.0f);

        if(f.num_sides>=3){
            f.normal = computeNormal(vertices[f.vertex_index[0]].frames[0],vertices[f.vertex_index[1]].frames[0],vertices[f.vertex_index[2]].frames[0]);
        }
    }
    
    
    
    
}

void StarFoxObject::UpdateObject(){
}
