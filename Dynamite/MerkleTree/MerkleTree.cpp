//
//  MerkleTree.cpp
//  Dynamite
//
//  Created by Xander Van Raemdonck on 01/12/2018.
//  Copyright © 2018 TnTap. All rights reserved.
//

#include "MerkleTree.hpp"

MerkleTree::MerkleTree() {
    
}

char* MerkleTree::calculateParent(char** leafHashes) {
    printf("%s", leafHashes);
    leafHashes++;
    printf("%s", leafHashes);
}

char* MerkleTree::calculateTree(struct Transaction transactions[], int numberOfTransactions) {
    for (int i = 1; i < numberOfTransactions; i++) {
        char* sAmount = (char*)malloc(sizeof(transactions[i-1].amount));
        sprintf(sAmount, "%f", transactions[i-1].amount);
        char* t1 = (char*)malloc(sizeof(transactions[i-1].receiver) + sizeof(transactions[i-1].sender) + sizeof(sAmount) + 10);
        strcpy(t1, transactions[i-1].receiver);
        strcat(t1, transactions[i-1].sender);
        strcat(t1, sAmount);
        char * tAmount = (char*)malloc(sizeof(transactions[i].amount));
        sprintf(tAmount, "%f", transactions[i].amount);
        char* t2 = (char*)malloc(sizeof(transactions[i].receiver) + sizeof(transactions[i].sender) + sizeof(tAmount) + 10);
        strcpy(t2, transactions[i].receiver);
        strcat(t2, transactions[i].sender);
        strcat(t2, tAmount);
        free(sAmount);
        free(tAmount);
        this->sha.sha256(t1);
        this->sha.sha256(t2);
        printf("h1: %s \n h2: %s\n", t1, t2);
        free(t1);
        free(t2);
    }
    return "dqf";
}
