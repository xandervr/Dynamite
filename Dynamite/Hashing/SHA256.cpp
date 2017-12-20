//
//  SHA256.cpp
//  Dynamite
//
//  Created by Xander Van Raemdonck on 20/12/2017.
//  Copyright © 2017 TnTap. All rights reserved.
//

#include "SHA256.hpp"

size_t SHA::count(char text[]) {
    int i = 0;
    while (text[i] != '\0')
        i++;
    return i;
}

char* SHA::sha256(char plain[]) {
    SHA256_CTX ctx256;
    SHA256_Init(&ctx256);
    SHA256_Update(&ctx256, (unsigned char*)plain, count(plain));
    SHA256_End(&ctx256, (char*)plain);
    char* result = plain;
    return result;
}
