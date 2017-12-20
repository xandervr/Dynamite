//
//  Blockchain.hpp
//  Dynamite
//
//  Created by Xander Van Raemdonck on 20/12/2017.
//  Copyright © 2017 TnTap. All rights reserved.
//

#ifndef Blockchain_hpp
#define Blockchain_hpp

#include <stdio.h>
#include "Block.hpp"

struct Chain {
    Block * block;
    struct Chain * next;
};

class Blockchain {
private:
    int difficulty;
    int index = 0;
    int verified = 0;
    struct Chain * chain_root;
    struct Chain * getLastChain();
    Block * getLastUnverifiedBlock();
    bool isValid(Block*, char*);
    char* calculateHash(Block*);
public:
    Blockchain(int);
    void addBlock(char*, char*, double);
    bool mineBlock();
    void startMiner();
};

#endif /* Blockchain_hpp */
