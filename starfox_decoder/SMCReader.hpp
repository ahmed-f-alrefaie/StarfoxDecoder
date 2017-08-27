//
//  SMCReader.hpp
//  starfox_decoder
//
//  Created by Ahmed Al-Refaie on 25/08/2017.
//  Copyright © 2017 Primalfido. All rights reserved.
//

#ifndef SMCReader_hpp
#define SMCReader_hpp

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <iostream>
class SMCReader{
    int8_t* ROM;
    
    
    
    
public:
    void Initialize();
    int8_t read(uint32_t addr);
    
    
    
};

extern SMCReader smc;



#endif /* SMCReader_hpp */
