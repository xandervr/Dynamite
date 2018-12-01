//
//  MerkleTree.hpp
//  Dynamite
//
//  Created by Xander Van Raemdonck on 01/12/2018.
//  Copyright © 2018 TnTap. All rights reserved.
//

#ifndef MerkleTree_hpp
#define MerkleTree_hpp

#include <stdio.h>
#include <string.h>
#include "../Hashing/SHA256.hpp"
#include "../Transaction/Transaction.hpp"

class MerkleTree {
private:
    SHA sha;
    struct Transaction remaining[];
    char* calculateParent(char**);
public:
    MerkleTree();
    char* calculateTree(struct Transaction[], int);
};

#endif /* MerkleTree_hpp */
