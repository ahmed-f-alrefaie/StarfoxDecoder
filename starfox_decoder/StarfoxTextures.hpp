//
//  StarfoxTextures.hpp
//  starfox_decoder
//
//  Created by Ahmed Al-Refaie on 29/08/2017.
//  Copyright © 2017 Primalfido. All rights reserved.
//

#ifndef StarfoxTextures_hpp
#define StarfoxTextures_hpp

#include <stdio.h>
#include "StarfoxPalette.hpp"
#include "SMCReader.hpp"
namespace StarfoxTexture {
    
    const uint32_t ROM_TEXTURE_ADDRESS = 0x90000;
    const int MAX_TEXTURE_PAGE_SIZE = 0x10000;
    
    union TexturePixel{
        struct tex_pixel{
            unsigned int pageone : 4;
            unsigned int pagetwo : 4;
        } twopixel;
        uint8_t byte;
    } ;
    
    /*union TexturePixel{
        struct tex_pixel{
            uint8_t h : 4;
            uint8_t l : 4;
        } b;
        uint8_t pal_no;
    } ;*/
    
    
    
   static uint8_t SFTexPageOne[0x20000];
   static uint8_t SFTexPageTwo[0x20000];
   
   // static uint8_t RawPalettePixel[0x20000];
    
    
    void ReadTextureDataFromRom();
    
    
    void ExportToImage();
    
    
    
    
    
    
    
    
    
}





#endif /* StarfoxTextures_hpp */
