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

void Blockchain::printMiningSpeed(Block * curr_block, time_t start) {
    std::time_t inter = std::time(nullptr);
    std::time_t diff = inter - start;
    
    double hashes_per_second = diff == 0 ? ((double)curr_block->getNonce() - MIN_NONCE) / 1000 : (((double)curr_block->getNonce() - MIN_NONCE) / (double)diff / 1000);
    #ifdef __APPLE__
        //printf("%.2fkH/s Temp: %llu°C\r", hashes_per_second, get_cpu_temp());
        printf("%.2fkH/s - Nonce: %ld\r", hashes_per_second, curr_block->getNonce());
    #else
        printf("%.2fkH/s\r", hashes_per_second);
    #endif
    
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

Blockchain::Blockchain(char * path) {
    loadFromFileSystem(path);
}

void Blockchain::saveToFileSystem(char * path) {
    FILE * fh = fopen(path, "wb");
    fwrite(&this->difficulty, sizeof(int), 1, fh);
    fwrite(&this->verified, sizeof(int), 1, fh);
    struct Chain * curr_chain = this->chain_root;
    while(curr_chain->next != NULL) {
        fwrite(curr_chain, sizeof(struct Chain), 1, fh);
        curr_chain = curr_chain->next;
    }
    fclose(fh);
}

void Blockchain::loadFromFileSystem(char * path) {
    FILE * fh = fopen(path, "rb");
    if (fh != NULL) {
        fread(&this->difficulty, sizeof(int), 1, fh);
        fread(&this->verified, sizeof(int), 1, fh);
        this->chain_root = (struct Chain*)malloc(sizeof(struct Chain));
        size_t bytes_read = fread(chain_root, sizeof(struct Chain), 1, fh);
        this->chain_end = chain_root;
        this->index++;
        while (fh != NULL && bytes_read > 0) {
            struct Chain* chain = (struct Chain*)malloc(sizeof(struct Chain));
            bytes_read = fread(chain, sizeof(struct Chain), 1, fh);
            chain->next = NULL;
            this->chain_end->next = chain;
            this->chain_end = chain;
            this->index++;
        }
    }
    fclose(fh);
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
            printMiningSpeed(last_unverified_block, start);
        };
        std::time_t end = std::time(nullptr);
        std::time_t diff = end - start;
        double hashes_per_second = diff == 0 ? ((double)last_unverified_block->getNonce() - MIN_NONCE) / 1000 : (((double)last_unverified_block->getNonce() - MIN_NONCE) / (double)diff / 1000);
        printf("Block %d mined! - %s - %ld (Diff: %d, took %ld seconds, %.2fkH/s)\n", last_unverified_block->getIndex(), try_hash, last_unverified_block->getNonce(), this->difficulty, diff, hashes_per_second);
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


