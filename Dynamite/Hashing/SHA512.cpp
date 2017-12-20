//
//  SHA512.cpp
//  Dynamite
//
//  Created by Xander Van Raemdonck on 20/12/2017.
//  Copyright © 2017 TnTap. All rights reserved.
//

#include "SHA512.hpp"

size_t SHA::count(char text[]) {
    int i = 0;
    while (text[i] != '\0')
        i++;
    return i;
}

char* SHA::sha512(char plain[]) {
    //char *buf = (char*)malloc(129 + sizeof(char) * 129);
    //printf("addr: %x\n", buf);
    //memcpy(buf, plain, count(plain));
    SHA512_CTX ctx512;
    SHA512_Init(&ctx512);
    SHA512_Update(&ctx512, (unsigned char*)plain, count(plain));
    SHA512_End(&ctx512, (char*)plain);
    char* result = plain;
    return result;
}
