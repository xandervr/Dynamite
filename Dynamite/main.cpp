//
//  main.cpp
//  Dynamite
//
//  Created by Xander Van Raemdonck on 20/12/2017.
//  Copyright © 2017 TnTap. All rights reserved.
//

#include <iostream>
#include "Blockchain/Blockchain.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    Blockchain dynamite(5);
    cout << "Adding 100.000 blocks to blockchain..." << endl;
    for (int i = 0; i < 100000; i++) {
        printf("%d\r", i);
        dynamite.addBlock("xander", "cis", 1.5);
    }
    cout << "Mining started..." << endl;
    dynamite.startMiner();
    return 0;
}
