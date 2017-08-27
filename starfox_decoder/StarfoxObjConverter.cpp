//
//  StarfoxObjConverter.cpp
//  starfox_decoder
//
//  Created by Ahmed Al-Refaie on 24/08/2017.
//  Copyright © 2017 Primalfido. All rights reserved.
//

#include "StarfoxObjConverter.hpp"
#include "SMCReader.hpp"
#include <algorithm>
#include <set>
uint32_t StarfoxObjConverter::GetHeaderAddress(uint32_t object_id){
    uint32_t offset = ((object_id << 8) & 0xFF00) + ((object_id>>8) &0xFF);
    
    
    return (offset-obj_base_address)& 0xFFFFFF ;
    
    
}

uint32_t StarfoxObjConverter::ComputeObjectAddress(uint32_t address, uint8_t bank){
    
    return ((bank - 1) * 0x8000) + address;
    
}

StarfoxObjConverter::SFObjHeader StarfoxObjConverter::GetHeaderInfo(uint32_t obj_id){
    
    StarfoxObjConverter::SFObjHeader header_info;
    
    uint8_t raw_header[28];
    
    uint32_t header_address =GetHeaderAddress(obj_id);
    
    
    for(int i =0; i < 28; i++){
        raw_header[i]=smc.read(header_address + i);
        // std::cout<<std::hex<<int(raw_header[i])<<" ";
        
        
    }
    
    //std::cout<<std::endl;
    
    
    header_info.vertex_address = ((raw_header[1]<<8) & 0xFF00) + raw_header[0];
    std::cout<<std::hex<<header_info.vertex_address<<std::endl;
    header_info.bank_no = raw_header[2];
    header_info.face_address = ((raw_header[4]<<8) & 0xFF00) + raw_header[3];
    std::cout<<std::hex<<header_info.face_address<<std::endl;
    
    header_info.palette_address = ((raw_header[0x13]<<8) & 0xFF00) + raw_header[0x12];
    std::cout<<std::hex<<header_info.palette_address<<std::endl;
    
    return header_info;
    
    
    
}


void StarfoxObjConverter::DecodeAnimationData(uint32_t address,std::vector<Vertex> & vertex_list){
    
    int start_vertex = vertex_list.size();
    int num_frames = smc.read(address++);
    std::vector<int> foffsets;
    
    std::cout<<" Number of frames "<<num_frames<<std::endl;
    int offset = 0;
    for(int i = 0; i < num_frames; i++){
        int frame_offset =((smc.read(address++))&0xFF);
        offset++;
        frame_offset +=((smc.read(address++)<< 8) &0xFF00);
        offset++;
        frame_offset+= offset;
        foffsets.push_back(frame_offset);
        
        
        
        
        
    }
    std::set<int> unique_frames(foffsets.begin(),foffsets.end());
    std::cout<<" Unique frames = "<<unique_frames.size()<<std::endl;
    
    int vert_frames =unique_frames.size();
    
    std::cout<<int(smc.read(address))<<std::endl;
    
    int min_offset = *std::min_element(std::begin(foffsets),std::end(foffsets));
    
    std::cout<<min_offset<<std::endl;
    
    for(auto & i : foffsets){
        i-=min_offset;
        
    }
    
    int div=foffsets[1];
    
    for(auto & i : foffsets){
        i/=div;
        std::cout<<"Frame offsets: "<<i<<std::endl;
    }
    
    //int vertext
    
    
    
    for(int vl = 0; vl < vert_frames; vl++){
        DecodeAnimationVertices(address, vertex_list,start_vertex, vl, num_frames, foffsets);
        
        
        
        
        
    }
    
    
    //exit(0);
    
    
    
    
    
    
    
    
    
}

void StarfoxObjConverter::DecodeAnimationVertices(uint32_t & address,std::vector<Vertex> & vertex_list,int start_vertex,int frame_num,int total_frames,const std::vector<int> & frame_idx){
    
    glm::vec3 position;
    int offset = 0;
    
    while (true){
        int8_t type= smc.read(address++);
        
        
        if(type == NORMAL_VERTEX){
            
            auto count = smc.read(address++);
            std::cout<<"NORMAL"<<std::endl;
            std::cout<<int(count)<<std::endl;
            for(int i = 0; i < count; i++){
                
                
                if(frame_num==0)vertex_list.push_back(Vertex());
                position.x = float(smc.read(address++));
                position.y = float(smc.read(address++));
                position.z = float(smc.read(address++));
                vertex_list[start_vertex+offset].frames.push_back(position);
                vertex_list[start_vertex+offset].vert_type = VertexType::Animated;
                vertex_list[start_vertex+offset].num_frames = total_frames;
                vertex_list[start_vertex+offset].frame_idx = frame_idx;
                //vertex_list.back().position.y = float(smc.read(address++));
                //vertex_list.back().position.z = float(smc.read(address++));
                offset++;
                
                
                
            }
            //if(frame_num!= total_frames){
            //Read 3 redundant bytes
            
            // for(int i=0; i < 20; i++)
            //   jmp=smc.read(address++);
            //}
            
            
        }else if(type == MIRRORX_VERTEX){
            //Fuck fuck fuck fuck fuck
            auto count = smc.read(address++);
            std::cout<<"MIRRORX"<<std::endl;
            std::cout<<int(count)<<std::endl;
            for(int i = 0; i < count; i++){
                //
               // int offset = i*2;
                
                
                position.x = float(smc.read(address++));
                position.y = float(smc.read(address++));
                position.z = float(smc.read(address++));
                
                if(frame_num==0)vertex_list.push_back(Vertex());
                
                vertex_list[start_vertex+offset].frames.push_back(position);
                vertex_list[start_vertex+offset].vert_type = VertexType::Animated;
                vertex_list[start_vertex+offset].num_frames = total_frames;
                vertex_list[start_vertex+offset].frame_idx = frame_idx;
                if(frame_num==0)vertex_list.push_back(Vertex());
                
                position.x*=-1;
                offset++;
                vertex_list[start_vertex+offset].frames.push_back(position);
                vertex_list[start_vertex+offset].vert_type = VertexType::Animated;
                vertex_list[start_vertex+offset].num_frames = total_frames;
                vertex_list[start_vertex+offset].frame_idx = frame_idx;
                offset++;
                
            }
            
            
        }else{
            // std::cout<<"Mate the fuck is this shit "<<uint(type)<<std::endl;
            //exit(0);
            std::cout<<"End val: "<<int(type)<<offset<<std::endl;
            if(type ==0x20){
                address++;
                address++;
                break;
                
            }else{

               // exit(0);
                
                
                break;
            }
            
        }
    }
}











void StarfoxObjConverter::DecodeVertices(uint32_t & address,std::vector<Vertex> & vertex_list,int8_t type){
    
    glm::vec3 position;
    
    if(type == NORMAL_VERTEX){
        
        auto count = smc.read(address++);
        for(int i = 0; i < count; i++){
            
            
            vertex_list.push_back(Vertex());
            position.x = float(smc.read(address++));
            position.y = float(smc.read(address++));
            position.z = float(smc.read(address++));
            vertex_list.back().frames.push_back(position);
            vertex_list.back().num_frames = 1;
            vertex_list.back().frame_idx.push_back(0);
            vertex_list.back().vert_type = VertexType::Static;
            //vertex_list.back().position.y = float(smc.read(address++));
            //vertex_list.back().position.z = float(smc.read(address++));
            
            
            
            
        }
        
        
    }else if(type == MIRRORX_VERTEX){
        //Fuck fuck fuck fuck fuck
        auto count = smc.read(address++);
        for(int i = 0; i < count; i++){
            //
            
            
            
            position.x = float(smc.read(address++));
            position.y = float(smc.read(address++));
            position.z = float(smc.read(address++));
            
            vertex_list.push_back(Vertex());
            
            vertex_list.back().frames.push_back(position);
            vertex_list.back().num_frames = 1;
            vertex_list.back().frame_idx.push_back(0);
            vertex_list.back().vert_type = VertexType::Static;
            
            vertex_list.push_back(Vertex());
            
            position.x*=-1;
            
            vertex_list.back().frames.push_back(position);
            vertex_list.back().num_frames = 1;
            vertex_list.back().frame_idx.push_back(0);
            vertex_list.back().vert_type = VertexType::Static;
            
            
        }
        
        
    }
    
    
    
}



std::vector<Vertex> StarfoxObjConverter::ReadVertices(const StarfoxObjConverter::SFObjHeader &header){
    
    uint32_t address = ComputeObjectAddress(header.vertex_address,header.bank_no);
    std::cout<<"Vertex address "<<std::hex<<address<<std::endl;
    std::vector<Vertex> vertex_list;
    //int8_t val = smc.read(address);
    glm::vec3 position;
    //std::cout<<std::hex<<int(val)<<std::endl;
    while(true){
        auto val = smc.read(address++);
        if(val == END_VERTEX) break;
        if(val == NORMAL_VERTEX){
            
            DecodeVertices(address, vertex_list, val);
            
            
        }else if(val == MIRRORX_VERTEX){
            DecodeVertices(address, vertex_list, val);
            
            
        }else if(val == ANIMATED_VERTEX){
            DecodeAnimationData(address, vertex_list);
            
            
        }else{
            std::cout<<"Don't know what "<<int(val)<<" does"<<std::endl;
            
        }
        
        
        
        
        
        
    }
    
    
    
    return vertex_list;
    
}

std::vector<Face> StarfoxObjConverter::ReadFaces(const StarfoxObjConverter::SFObjHeader &header){
    
    uint32_t address = ComputeObjectAddress(header.face_address,header.bank_no);
    std::cout<<"Face address "<<std::hex<<address<<std::endl;
    
    //Read and skip the triangle data
    auto val = smc.read(address++);
    std::cout<<std::hex<<int(val)<<std::endl;
    if(val != 0x30){
        std::cout<<"[Read face] Not sure what to do with this value"<<std::endl;
        
    }
    val = smc.read(address++);
    std::cout<<int(val)<<std::endl;
    // address += val*3;
    int skip = val;
    for(int i=0; i < skip; i++){
        val = smc.read(address++);
        std::cout<<int(val)<<" ";
        val = smc.read(address++);
        std::cout<<int(val)<<" ";
        val = smc.read(address++);
        std::cout<<int(val)<<std::endl;
        
    }
    //  exit(-1);
    //   */
    
    val = smc.read(address++);
    std::cout<<int(val)<<std::endl;
    //Read BSP data and skip it
    if(val == 0x3C){
        
        
        val = smc.read(address++);
        val = smc.read(address++);
        uint32_t byte_skip =(smc.read(address++)&0xFF);
        address += ((smc.read(address)<<8) &0xFF00);
        address += byte_skip;
        std::cout<<int(smc.read(address))<<std::endl;
    }
    // exit(0);
    
    std::vector<Face> face_list;
    while (true){
        val = smc.read(address);
        
        if(val == 0x14){
            address++;
            
            
        }else if(val == int8_t(0xFF) || val == int8_t(0xFE)){
            address++;
            continue;
        }else if (val == 0x00)
            break;
        
        face_list.push_back(Face());
        face_list.back().num_sides=smc.read(address++);
        face_list.back().face_id=smc.read(address++);
        face_list.back().color=smc.read(address++);
        
        face_list.back().normal[0]=float(smc.read(address++));
        face_list.back().normal[1]=float(smc.read(address++));
        face_list.back().normal[2]=float(smc.read(address++));
        for(int i=0; i < face_list.back().num_sides; i++)
            face_list.back().vertex_index.push_back(int(smc.read(address++)));
        
        
        
        
        
        
        face_list.back().normal = glm::normalize(face_list.back().normal);
        face_list.back().Print();
        
        
        
    }
    
    return face_list;
}


