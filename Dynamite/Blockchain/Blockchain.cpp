//
//  Blockchain.cpp
//  Dynamite
//
//  Created by Xander Van Raemdonck on 20/12/2017.
//  Copyright © 2017 TnTap. All rights reserved.
//

#include "Blockchain.hpp"

/**
 *
 * PRIVATE
 *
 */

struct Chain * Blockchain::getLastChain() {
    struct Chain * curr_chain = this->chain_root;
    while(curr_chain->next != NULL) {
        curr_chain = curr_chain->next;
    }
    return curr_chain;
}

Block * Blockchain::getLastUnverifiedBlock() {
    struct Chain * curr_chain = this->chain_root;
    while(curr_chain->next != NULL && curr_chain->block->isVerified()) {
        curr_chain = curr_chain->next;
    }
    return curr_chain->block;
}

bool Blockchain::isValid(Block* block, char* try_hash) {
    int count = 0;
    while(*(try_hash++) == '0')
        count++;
    if (count == this->difficulty) {
        block->setVerified(true);
        return true;
    } else {
        block->setNonce(block->getNonce() + 1);
        return false;
    }
}

char* Blockchain::calculateHash(Block* block) {
    SHA sha;
    std::string s_nonce = std::to_string(block->getNonce());
    char* plain = (char*)malloc(sizeof(char*) * 65 + sizeof(char*) * 65);
    strcpy(plain, block->getHash());
    strcat(plain, s_nonce.c_str());
    char * result = sha.sha256(plain);
    free(plain);
    return result;
}

/**
 *
 * PUBLIC
 *
 */

Blockchain::Blockchain(int difficulty) {
    this->difficulty = difficulty;
    this->chain_root = (struct Chain*)malloc(sizeof(struct Chain));
    Block genesisBlock(0);
    this->chain_root->block = (Block*)malloc(sizeof(Block));
    memcpy(this->chain_root->block, &genesisBlock, sizeof(genesisBlock));
    this->chain_root->next = NULL;
    this->chain_end = chain_root;
    this->index++;
}

void Blockchain::addBlock(char* sender, char* receiver, double amount) {
    struct Chain * last_chain = this->chain_end;
    Block * previousBlock = last_chain->block;
    Block block(sender, receiver, amount, 0, previousBlock->getHash(), this->index);
    struct Chain * new_chain = (struct Chain*)malloc(sizeof(struct Chain) * sizeof(Block));
    new_chain->block = (Block*)malloc(sizeof(block));
    memcpy(new_chain->block, &block, sizeof(block));
    new_chain->next = NULL;
    last_chain->next = new_chain;
    this->chain_end = new_chain;
    this->index++;
}

bool Blockchain::mineBlock() {
    Block* last_unverified_block = getLastUnverifiedBlock();
    if (last_unverified_block->getPreviousHash() != NULL && !last_unverified_block->isVerified()) {
        std::time_t start = std::time(nullptr);
        char* try_hash = calculateHash(last_unverified_block);
        while(!isValid(last_unverified_block, try_hash)) {
            try_hash = calculateHash(last_unverified_block);
        };
        std::time_t end = std::time(nullptr);
        std::time_t diff = end - start;
        double hashes_per_second = diff == 0 ? ((double)last_unverified_block->getNonce() - MIN_NONCE) / 1000 : (((double)last_unverified_block->getNonce() - MIN_NONCE) / (double)diff / 1000);
        printf("Block %d mined! - %s - %d (Diff: %d, took %ld seconds, %.2fkH/s)\n", last_unverified_block->getIndex(), try_hash, last_unverified_block->getNonce(), this->difficulty, diff, hashes_per_second);
        this->verified++;
        return true;
    } else {
        return false;
    }
}

void Blockchain::startMiner() {
    bool mined = mineBlock();
    while(mined) {
        if (verified % DIFFICULTY_OFFSET == 0)
            difficulty++;
        mined = mineBlock();
    }
    printf("All blocks are mined!\n");
}


