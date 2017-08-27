//
//  StarfoxObjConverter.hpp
//  starfox_decoder
//
//  Created by Ahmed Al-Refaie on 24/08/2017.
//  Copyright © 2017 Primalfido. All rights reserved.
//

#ifndef StarfoxObjConverter_hpp
#define StarfoxObjConverter_hpp

#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <vector>
#include "StarfoxObjFormat.hpp"

namespace StarfoxObjConverter{

    const uint32_t obj_base_address = 0x8000;
    const uint8_t NORMAL_VERTEX = 0x04;
    const uint8_t MIRRORX_VERTEX = 0x38;
    const uint8_t ANIMATED_VERTEX = 0x1C;
    const uint8_t END_VERTEX = 0x0C;
    
    struct SFObjHeader{
        
        uint32_t vertex_address;
        
        uint8_t bank_no;
        
        uint32_t face_address;
        
        uint32_t palette_address;
        
    };
    
    auto GetHeaderAddress(uint32_t object_id) -> uint32_t;
    auto ComputeObjectAddress(uint32_t address,uint8_t bank) -> uint32_t;
    
    void DecodeVertices(uint32_t & address,std::vector<Vertex> & vertex_list,int8_t type);
    void DecodeAnimationData(uint32_t address,std::vector<Vertex> & vertex_list);
    void DecodeAnimationVertices(uint32_t & address,std::vector<Vertex> & vertex_list,int start_vertex,int frame_num,int total_frames,const std::vector<int> & frame_idx);
    std::vector<Vertex> ReadVertices(const SFObjHeader & header);
    std::vector<Face> ReadFaces(const SFObjHeader & header);
    
    
    SFObjHeader GetHeaderInfo(uint32_t object_id);
    
    
    
}



#endif /* StarfoxObjConverter_hpp */
