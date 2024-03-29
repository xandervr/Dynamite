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
#include <ctime>
#include <fstream>
#include <stdlib.h>
#include "../Block/Block.hpp"
#include "../CPU/CPU.hpp"

#define DIFFICULTY_OFFSET 20

struct Chain {
    Block * block;
    struct Chain * next;
};

class Blockchain {
private:
    int difficulty;
    int index = 0;
    int verified = 0;
    struct Chain * chain_end;
    struct Chain * chain_root;
    struct Chain * getLastChain();
    Block * getLastUnverifiedBlock();
    void printMiningSpeed(Block*, time_t);
    bool isValid(Block*, char*);
    char* calculateHash(Block*);
public:
    Blockchain(int);
    Blockchain(char*);
    void saveToFileSystem(char*);
    void loadFromFileSystem(char*);
    void addBlock(char*, char*, double);
    bool mineBlock();
    void startMiner();
};

#endif /* Blockchain_hpp */
