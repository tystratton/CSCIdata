/* Program name: block.cpp
Author: Ty Stratton
Date last updated: 7/17/2025
Purpose: Time Program Module 8 Assignment 1, learning Blockchain*/


#include "block.h"
#include <functional>

// Utility function for simple hash calculation
std::string simpleHash(const std::string& input) {
    std::hash<std::string> hasher;
    size_t hashValue = hasher(input);
    
    // Convert to hex string
    std::stringstream ss;
    ss << std::hex << hashValue;
    return ss.str();
}

// Block Implementation
Block::Block() : blockNumber(0), nonce(0), data(""), previousHash("0"), next(nullptr) {
    hashValue = calculateHash();
}

Block::Block(int number, const std::string& message, const std::string& prevHash) 
    : blockNumber(number), data(message), previousHash(prevHash), next(nullptr) {
    nonce = time(nullptr);  // Use current time as nonce
    hashValue = calculateHash();
}

Block::~Block() {
    // Destructor - no dynamic memory to clean up for this block
}

std::string Block::calculateHash() const {
    // Combine all block data for hashing
    std::stringstream ss;
    ss << blockNumber << nonce << data << previousHash;
    return simpleHash(ss.str());
}

void Block::setData(const std::string& newData) {
    data = newData;
    // Note: We don't recalculate hash here for hacking demonstration
}

bool Block::validateBlock() const {
    // Check if the stored hash matches the calculated hash
    return hashValue == calculateHash();
}

void Block::display() const {
    std::cout << "=== Block " << blockNumber << " ===" << std::endl;
    std::cout << "Block Number: " << blockNumber << std::endl;
    std::cout << "Nonce (Timestamp): " << nonce << std::endl;
    std::cout << "Data: " << data << std::endl;
    std::cout << "Previous Hash: " << previousHash << std::endl;
    std::cout << "Hash Value: " << hashValue << std::endl;
    std::cout << "Valid: " << (validateBlock() ? "Yes" : "No") << std::endl;
    std::cout << std::endl;
}

// Blockchain Implementation
Blockchain::Blockchain() : front(nullptr), rear(nullptr), blockCount(0) {
    // Create genesis block
    Block* genesisBlock = new Block(0, "Genesis Block", "0");
    front = rear = genesisBlock;
    blockCount = 1;
}

Blockchain::~Blockchain() {
    // Clean up all blocks
    while (front != nullptr) {
        Block* temp = front;
        front = front->getNext();
        delete temp;
    }
}

void Blockchain::addBlock(const std::string& data) {
    // Get the hash of the last block
    std::string prevHash = rear->getHashValue();
    
    // Create new block
    Block* newBlock = new Block(blockCount, data, prevHash);
    
    // Add to rear of queue
    rear->setNext(newBlock);
    rear = newBlock;
    blockCount++;
    
    std::cout << "Block " << blockCount - 1 << " added successfully!" << std::endl;
}

bool Blockchain::validateChain() const {
    if (isEmpty()) {
        return true;
    }
    
    Block* current = front;
    bool isValid = true;
    
    std::cout << "\n=== BLOCKCHAIN VALIDATION ===" << std::endl;
    
    while (current != nullptr) {
        // Validate individual block
        bool blockValid = current->validateBlock();
        std::cout << "Block " << current->getBlockNumber() << ": " 
                  << (blockValid ? "VALID" : "INVALID") << std::endl;
        
        if (!blockValid) {
            isValid = false;
        }
        
        // Check if previous hash matches (except for genesis block)
        if (current->getNext() != nullptr) {
            Block* nextBlock = current->getNext();
            if (nextBlock->getPreviousHash() != current->getHashValue()) {
                std::cout << "Chain integrity broken between Block " 
                          << current->getBlockNumber() << " and Block " 
                          << nextBlock->getBlockNumber() << std::endl;
                isValid = false;
            }
        }
        
        current = current->getNext();
    }
    
    std::cout << "Overall Chain Status: " << (isValid ? "VALID" : "INVALID") << std::endl;
    std::cout << std::endl;
    
    return isValid;
}

void Blockchain::displayMessageDigest() const {
    std::cout << "\n=== BLOCKCHAIN MESSAGE DIGEST ===" << std::endl;
    std::cout << "Total Blocks: " << blockCount << std::endl;
    std::cout << std::endl;
    
    Block* current = front;
    while (current != nullptr) {
        current->display();
        current = current->getNext();
    }
}

void Blockchain::hackBlock(int blockNumber, const std::string& newData) {
    Block* current = front;
    
    // Find the block to hack
    while (current != nullptr && current->getBlockNumber() != blockNumber) {
        current = current->getNext();
    }
    
    if (current != nullptr) {
        std::cout << "\n=== HACKING BLOCK " << blockNumber << " ===" << std::endl;
        std::cout << "Original Data: " << current->getData() << std::endl;
        current->setData(newData);
        std::cout << "New Data: " << current->getData() << std::endl;
        std::cout << "Block hacked successfully!" << std::endl;
        std::cout << "Note: Hash was not recalculated, so validation will fail." << std::endl;
        std::cout << std::endl;
    } else {
        std::cout << "Block " << blockNumber << " not found!" << std::endl;
    }
}