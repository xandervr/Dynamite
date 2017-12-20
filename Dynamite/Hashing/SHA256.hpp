//
//  SHA256.hpp
//  Dynamite
//
//  Created by Xander Van Raemdonck on 20/12/2017.
//  Copyright © 2017 TnTap. All rights reserved.
//

#ifndef SHA256_hpp
#define SHA256_hpp

#include <stdio.h>
#include <string>
#include "sha2.h"

class SHA {
private:
    size_t count(char text[]);
public:
    char* sha256(char plain[]);
};



#endif /* SHA256_hpp */
