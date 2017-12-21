//
//  Block.hpp
//  Dynamite
//
//  Created by Xander Van Raemdonck on 20/12/2017.
//  Copyright © 2017 TnTap. All rights reserved.
//

#ifndef Block_hpp
#define Block_hpp

#include <stdio.h>
#include "../Hashing/SHA256.hpp"

#define MIN_NONCE 2420000000//60 * 60 * 1000

struct block_data {
    char * receiver;
    char * sender;
    double amount;
    double reward;
};

class Block {
private:
    char * hash;
    struct block_data * data;
    char * previousHash;
    int index;
    long nonce;
    int timestamp;
    char * calculateHash();
    bool verified;
public:
    Block(char* sender, char* receiver, double amount, int timestamp, char* previousHash, int index);
    Block(int timestamp);
    char* getHash();
    char* getPreviousHash();
    int getTimestamp();
    int getIndex();
    long getNonce();
    void setNonce(long);
    bool isVerified();
    void setVerified(bool);
    struct block_data * getData();
};

#endif /* Block_hpp */
