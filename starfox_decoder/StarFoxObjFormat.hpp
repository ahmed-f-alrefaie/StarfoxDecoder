//
//  StarFoxObjFormat.hpp
//  starfox_decoder
//
//  Created by Ahmed Al-Refaie on 25/08/2017.
//  Copyright © 2017 Primalfido. All rights reserved.
//

#ifndef StarFoxObjFormat_hpp
#define StarFoxObjFormat_hpp

#include <stdio.h>
#include <vector>
#include <stdint.h>
#include <math.h>
#include "glm/glm.hpp"
#include <iostream>

enum class VertexType {Static,Animated};


struct Vertex{
    VertexType vert_type;
    std::vector<glm::vec3> frames;
    int num_frames;
    std::vector<int> frame_idx;
    int current_offset;
    glm::vec3 GetFrame(int frame_num = 0){
        int idx =frame_num %num_frames;
        return frames[frame_idx[idx]];
    }
};

struct Face{
    int num_sides;
    int face_id;
    std::vector<int> vertex_index;
    glm::vec3 normal;
    int color;
    void Print(){ std::cout<<num_sides<<" "<<face_id<<std::endl;};
    
};


class StarFoxObject{
public:
    virtual void Update() = 0;
    virtual void Draw() = 0;
    void ConstructObject();
protected:
    std::vector<Vertex> vertices;
    std::vector<Face> faces;
    
    glm::vec3 transform;
    glm::vec3 rotation;
    glm::vec3 scale;

    
    void UpdateObject();
    

private:
    
    uint32_t object_id;
    float * object_address_hook;
    
    int frame_number;
    
};



#endif /* StarFoxObjFormat_hpp */
