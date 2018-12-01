//
//  Transaction.hpp
//  Dynamite
//
//  Created by Xander Van Raemdonck on 01/12/2018.
//  Copyright © 2018 TnTap. All rights reserved.
//

#ifndef Transaction_hpp
#define Transaction_hpp

#include <stdio.h>

struct Transaction {
    char * receiver;
    char * sender;
    double amount;
};

#endif /* Transaction_hpp */
