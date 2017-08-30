//
//  StarfoxPalette.cpp
//  starfox_decoder
//
//  Created by Ahmed Al-Refaie on 27/08/2017.
//  Copyright © 2017 Primalfido. All rights reserved.
//

#include "StarfoxPalette.hpp"
#include "png++/png.hpp"

namespace StarfoxPalette {
    
    void ReadCurrentPalette(uint32_t address) {
        
        for(int i=0; i < 16; i++){
            cgRam_palette[i].c = smc.read(address++) &0xFF;
            cgRam_palette[i].c |= (smc.read(address++)&0xFF)<<8;
            std::cout<<int(cgRam_palette[i].c)<<"h ";
            
        }
        std::cout<<std::endl;
    }
    
    void GetRGB(int index, int & r, int & g, int & b,int & a){
        r= StarfoxPalette::cgRam_palette[index].c &0x1f;
        g=(StarfoxPalette::cgRam_palette[index].c >> 5) &0x1f;
        b=(StarfoxPalette::cgRam_palette[index].c >> 10) &0x1f;
        a=1;
        if(StarfoxPalette::cgRam_palette[index].c == 0) a = 0;
        
    }
    
    
    
    
    
}
