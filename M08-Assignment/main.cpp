/* Program name: main.cpp
Author: Ty Stratton
Date last updated: 7/17/2025
Purpose: Time Program Module 8 Assignment 1, learning Blockchain*/

#include "block.h"
#include <fstream>
#include <vector>

void printHeader(const std::string& title) {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << title << std::endl;
    std::cout << std::string(50, '=') << std::endl;
}

int main() {
    std::cout << "Blockchain Message Digest System" << std::endl;
    
    // Create blockchain instance
    Blockchain blockchain;
    
    printHeader("STEP 1: CREATING BLOCKCHAIN WITH MESSAGES");
    
    // Read messages from input file
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cout << "Error: Could not open input.txt" << std::endl;
        return 1;
    }
    
    std::string message;
    std::vector<std::string> messages;
    
    std::cout << "Reading messages from input.txt..." << std::endl;
    while (std::getline(inputFile, message) && !message.empty()) {
        messages.push_back(message);
        blockchain.addBlock(message);
    }
    inputFile.close();
    
    if (messages.empty()) {
        std::cout << "No messages found in input1.txt" << std::endl;
        return 1;
    }
    
    std::cout << "Added " << messages.size() << " messages to the blockchain." << std::endl;
    
    printHeader("STEP 2: DISPLAYING MESSAGE DIGEST");
    blockchain.displayMessageDigest();
    
    printHeader("STEP 3: VALIDATING BLOCKCHAIN (BEFORE HACKING)");
    bool initialValidation = blockchain.validateChain();
    
    if (initialValidation) {
        std::cout << "Blockchain is valid and secure!" << std::endl;
    } else {
        std::cout << "Blockchain validation failed!" << std::endl;
    }
    
    printHeader("STEP 4: HACKING THE BLOCKCHAIN");
    
    // Demonstrate hacking by altering some blocks
    if (blockchain.getBlockCount() > 2) {
        // Hack block 1 (first user message block)
        blockchain.hackBlock(1, "HACKED MESSAGE: This data has been tampered with!");
        
        // If there are more blocks, hack another one
        if (blockchain.getBlockCount() > 3) {
            blockchain.hackBlock(2, "ANOTHER HACK: Blockchain security compromised!");
        }
    }
    
    printHeader("STEP 5: DISPLAYING MESSAGE DIGEST (AFTER HACKING)");
    blockchain.displayMessageDigest();
    
    printHeader("STEP 6: VALIDATING BLOCKCHAIN (AFTER HACKING)");
    bool postHackValidation = blockchain.validateChain();
    
    if (postHackValidation) {
        std::cout << "WARNING: Blockchain still appears valid (unexpected!)" << std::endl;
    } else {
        std::cout << "SECURITY BREACH DETECTED: Blockchain validation failed!" << std::endl;
        std::cout << "The system successfully detected the tampering attempts." << std::endl;
    }
    
    printHeader("SUMMARY");
    std::cout << "Total blocks in chain: " << blockchain.getBlockCount() << std::endl;
    std::cout << "Initial validation: " << (initialValidation ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Post-hack validation: " << (postHackValidation ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Security demonstration: " << (!postHackValidation ? "SUCCESSFUL" : "FAILED") << std::endl;
    std::cout << "\nBlockchain implementation demonstrates:" << std::endl;
    std::cout << "✓ Message storage in linked queue structure" << std::endl;
    std::cout << "✓ Hash-based block validation" << std::endl;
    std::cout << "✓ Chain integrity verification" << std::endl;
    std::cout << "✓ Tamper detection capabilities" << std::endl;
    
    return 0;
}