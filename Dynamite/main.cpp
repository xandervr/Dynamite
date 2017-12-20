//
//  main.cpp
//  Dynamite
//
//  Created by Xander Van Raemdonck on 20/12/2017.
//  Copyright © 2017 TnTap. All rights reserved.
//

#include <iostream>
#include "Blockchain.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    Blockchain dynamite(1);
    for (int i = 0; i < 1000; i++)
        dynamite.addBlock("xander", "cis", 1.5);
    dynamite.startMiner();
    return 0;
}
