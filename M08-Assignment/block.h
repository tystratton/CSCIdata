/* Program name: block.h
Author: Ty Stratton
Date last updated: 7/17/2025
Purpose: Time Program Module 8 Assignment 1, learning Blockchain*/

#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>

class Block {
private:
    int blockNumber;
    time_t nonce;           // Using system time as nonce
    std::string data;       // Text message
    std::string previousHash;
    std::string hashValue;
    Block* next;           // For linked queue implementation

    // Helper method to calculate hash
    std::string calculateHash() const;
    
public:
    // Constructors
    Block();
    Block(int number, const std::string& message, const std::string& prevHash);
    
    // Destructor
    ~Block();
    
    // Getters
    int getBlockNumber() const { return blockNumber; }
    time_t getNonce() const { return nonce; }
    std::string getData() const { return data; }
    std::string getPreviousHash() const { return previousHash; }
    std::string getHashValue() const { return hashValue; }
    Block* getNext() const { return next; }
    
    // Setters
    void setNext(Block* nextBlock) { next = nextBlock; }
    void setData(const std::string& newData);  // For hacking purpose
    
    // Validation
    bool validateBlock() const;
    
    // Display
    void display() const;
};

class Blockchain {
private:
    Block* front;          // Front of the queue (genesis block)
    Block* rear;           // Rear of the queue (most recent block)
    int blockCount;
    
public:
    // Constructor and Destructor
    Blockchain();
    ~Blockchain();
    
    // Core functionality
    void addBlock(const std::string& data);
    bool validateChain() const;
    void displayMessageDigest() const;
    
    // Hacking functionality
    void hackBlock(int blockNumber, const std::string& newData);
    
    // Utility
    bool isEmpty() const { return front == nullptr; }
    int getBlockCount() const { return blockCount; }
};

// Utility function for simple hash calculation
std::string simpleHash(const std::string& input);

#endif