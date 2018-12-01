//
//  main.cpp
//  Dynamite
//
//  Created by Xander Van Raemdonck on 20/12/2017.
//  Copyright © 2017 TnTap. All rights reserved.
//

#include <iostream>
#include "Blockchain/Blockchain.hpp"
#include "MerkleTree/MerkleTree.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
//    Blockchain dynamite(4);
//    cout << "Adding 100.000 blocks to blockchain..." << endl;
//    for (int i = 0; i < 10; i++) {
//        printf("%d\r", i);
//        dynamite.addBlock("xander", "cis", 1.5);
//    }
//    cout << "Mining started..." << endl;
//    dynamite.startMiner();
//    dynamite.saveToFileSystem("chain");
//    Blockchain test("chain");
    
    MerkleTree tree;
    struct Transaction transactions[2];
    struct Transaction t = {"Xander", "Xander", 45};
    struct Transaction s = {"Jana", "Jana", 100};
    transactions[0] = t;
    transactions[1] = s;
    
    tree.calculateTree(transactions, 2);
    
    return 0;
}
