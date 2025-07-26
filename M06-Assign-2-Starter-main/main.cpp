/* Program name: main.cpp
Author: Ty Stratton
Date last updated: 7/16/2025
Purpose: Time Program Module 6 Assignment 2, learning Graphs*/

#include "graph.h"
#include <iostream>
#include <string>

int main()
{
    try
    {
        // Create a graph with sufficient size (max 20 nodes should be enough)
        graphType networkGraph(20);
        
        // Load the network topology from routes.txt (silently)
        networkGraph.createGraph("routes.txt");
        
        // Get user input
        std::string startIP, endIP;
        
        std::cout << "Enter the starting ip:" << std::endl;
        std::cin >> startIP;
        
        std::cout << std::endl << "Enter the goal ip:" << std::endl;
        std::cin >> endIP;
        
        std::cout << std::endl << "Finding path from " << startIP << " to " << endIP << std::endl;
        
        std::string path = networkGraph.findPath(startIP, endIP);
        
        // Replace " -> " with "-->" in the path output
        std::string modifiedPath = path;
        size_t pos = 0;
        while ((pos = modifiedPath.find(" -> ", pos)) != std::string::npos) {
            modifiedPath.replace(pos, 4, "-->");
            pos += 3;
        }
        
        std::cout << modifiedPath << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
