//
//  StarfoxTextures.cpp
//  starfox_decoder
//
//  Created by Ahmed Al-Refaie on 29/08/2017.
//  Copyright © 2017 Primalfido. All rights reserved.
//

#include "StarfoxTextures.hpp"
#include "png++/png.hpp"

namespace StarfoxTexture {
    
    void ReadTextureDataFromRom(){
        uint32_t address = ROM_TEXTURE_ADDRESS;
        
        for(int i = 0; i < 0x20000; i++){
            TexturePixel data;
            data.byte = smc.read(address++);
            
            SFTexPageOne[i] = data.twopixel.pageone&0xF;
            //std::cout<<int(SFTexPageOne[i])<<std::endl;
            SFTexPageTwo[i] = data.twopixel.pagetwo&0xF;
            
        }
        
        
    }
    
    void ExportToImage(){

        png::image< png::rgba_pixel > image(256,256);
        for(int i=0;i<256;i++)
        {
            for(int j=0;j<256;j++)
            {
                int index =SFTexPageTwo[j + 256*i];
              //  auto color = ;
                
                int red=0,green=0,blue=0,alpha=0;
                StarfoxPalette::GetRGB(index, red, green, blue,alpha);
                
                //std::cout<<int(SFTexPageTwo[j + 255*i])<<std::endl;
                image[i][j]=png::rgba_pixel(red*8,green*8, blue*8,alpha*255);
            }
        }
        
        image.write("Page2.png");
        
        
        
    }
    
    
}

