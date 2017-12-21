//
//  Block.cpp
//  Dynamite
//
//  Created by Xander Van Raemdonck on 20/12/2017.
//  Copyright © 2017 TnTap. All rights reserved.
//

#include "Block.hpp"

Block::Block(char* sender, char* receiver, double amount, int timestamp, char* previousHash, int index) {
    struct block_data *d = (struct block_data*)malloc(sizeof(struct block_data));
    d->receiver = receiver;
    d->sender = sender;
    d->amount = amount;
    d->reward = 50;
    this->nonce = MIN_NONCE;
    this->index = index;
    this->data = d;
    this->timestamp = timestamp;
    this->previousHash = previousHash;
    this->hash = calculateHash();
    this->verified = false;
}

Block::Block(int timestamp) {
    this->data = (struct block_data*)malloc(sizeof(struct block_data));
    this->data->sender = NULL;
    this->data->receiver = NULL;
    this->data->amount = 0;
    this->data->reward = 50;
    this->timestamp = timestamp;
    this->previousHash = NULL;
    this->nonce = MIN_NONCE;
    this->index = 0;
    this->verified = true;
    this->hash = calculateHash();
}

char * Block::calculateHash() {
    SHA sha;
    std::string s_timestamp = std::to_string(this->timestamp);
    char * plain = (char*)malloc(sizeof(struct block_data) + sizeof(char) * 65 + sizeof(char));
    strcpy(plain, this->previousHash == NULL ? "" : this->previousHash);
    strcat(plain, s_timestamp.c_str());
    strcat(plain, this->data == NULL ? "" : "test"); // TODO FIXME
    char * result = sha.sha256(plain);
    return result;
}

char* Block::getHash() {
    return this->hash;
}

char* Block::getPreviousHash() {
    return this->previousHash;
}

int Block::getTimestamp() {
    return this->timestamp;
}

int Block::getIndex() {
    return this->index;
}

long Block::getNonce() {
    return this->nonce;
}

void Block::setNonce(long nonce) {
    this->nonce = nonce;
}

bool Block::isVerified() {
    return this->verified;
}

void Block::setVerified(bool verified) {
    this->verified = verified;
}

struct block_data * Block::getData() {
    return this->data;
}
