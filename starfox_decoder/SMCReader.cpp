//
//  SMCReader.cpp
//  starfox_decoder
//
//  Created by Ahmed Al-Refaie on 25/08/2017.
//  Copyright © 2017 Primalfido. All rights reserved.
//

#include "SMCReader.hpp"

SMCReader smc;

void SMCReader::Initialize(){
    
    FILE* fp = nullptr;
    fp= fopen("/Users/Food-Processor/Downloads/Star Fox (J) [!].smc","r");
    
    if(fp==nullptr){
        std::cout<<"Error could not open StarFox file\n";
        exit(-1);
    }
    
    fseek(fp, 0L, SEEK_END);
    auto sz = ftell(fp);
    //Rewind to the beginning
    rewind(fp);
    auto rem = sz % 1024;
    
    //We are dealing with headerless, proceed as normal
    if(rem == 0){
        std::cout<<"Rom is headerless\n";
        ROM = new int8_t[sz];
        
        
        
    }else if(rem == 512){
    
        std::cout<<"Rom has header\n";
    //SMC header rinformation
        uint8_t header[512];
    
    
        auto count = fread(header,1,512,fp);
        
        if(count != 512){
            std::cout<<"Malformed header, should be 512 bytes but its only "<<count*8<< "bytes\n";
            exit(-1);
        }
        sz-=512;
        
        ROM = new int8_t[sz];
        
        
    }
    //Reading rom
    fread(ROM,1,sz,fp);
    //And we should be done;
    
    
    
    
    
}

int8_t SMCReader::read(uint32_t addr){
    return ROM[addr];
    
}
