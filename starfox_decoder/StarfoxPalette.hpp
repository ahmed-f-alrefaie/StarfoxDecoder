//
//  StarfoxPalette.hpp
//  starfox_decoder
//
//  Created by Ahmed Al-Refaie on 27/08/2017.
//  Copyright © 2017 Primalfido. All rights reserved.
//

#ifndef StarfoxPalette_hpp
#define StarfoxPalette_hpp

#include <stdio.h>
#include <stdint.h>
#include "SMCReader.hpp"

namespace StarfoxPalette {
    
    
    const int MAX_PALETTE = 16;
    const uint32_t SPACE_PALETTE_ADDRESS = 0x18aca;
    
    
    union Palette{
        struct RGB{
            unsigned int r : 5;
            unsigned int g : 5;
            unsigned int b : 5;
        }rgb;
        uint16_t c;
        uint8_t l;
        uint8_t h;
        
    };
    
 static    Palette cgRam_palette[MAX_PALETTE];
    
    void GetRGB(int index, int & r, int & g, int & b,int & a);
    void ReadCurrentPalette(uint32_t address);
    
    
    
}



#endif /* StarfoxPalette_hpp */
