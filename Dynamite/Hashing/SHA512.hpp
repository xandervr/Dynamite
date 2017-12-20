//
//  SHA512.hpp
//  Dynamite
//
//  Created by Xander Van Raemdonck on 20/12/2017.
//  Copyright © 2017 TnTap. All rights reserved.
//

#ifndef SHA512_hpp
#define SHA512_hpp

#include <stdio.h>
#include <string>
#include "sha2.h"

class SHA {
private:
    size_t count(char text[]);
public:
    char* sha512(char plain[]);
};



#endif /* SHA512_hpp */
