/* Program name: url.cpp
Author: Ty Stratton
Date last updated: 6/23/2025
Purpose: Time Program Module 3 Assignment 1, learning stacks*/

#include "url.h"
#include "HTTPRequest.hpp"
#include <iostream>
#include <fstream>
#include <vector>

Url::Url(const std::string &url, const std::string &filename) : urlAddress(url), fileName(filename)
{
    // First, check if the file already exists and is not empty.
    std::ifstream inFile(this->fileName);
    if (inFile.good() && inFile.peek() != std::ifstream::traits_type::eof())
    {
        inFile.close();
        return; // File exists and is not empty, so we don't need to download it.
    }
    inFile.close();

    // If the file doesn't exist or is empty, try to download it.
    try
    {
        http::Request request{this->urlAddress};
        const auto response = request.send("GET");

        std::ofstream outFile(this->fileName);
        if (outFile.is_open())
        {
            outFile.write(reinterpret_cast<const char *>(response.body.data()), response.body.size());
            outFile.close();
        }
        else
        {
            std::cerr << "Error: Unable to open file for writing: " << this->fileName << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Request failed, error: " << e.what() << '\n';
    }
}

void Url::displayFileContents(int lineLimit) const
{
    std::ifstream inFile(this->fileName);
    if (!inFile.is_open())
    {
        std::cerr << "Error: Unable to open file for reading: " << this->fileName << std::endl;
        return;
    }

    std::string line;
    int lineCount = 0;
    while (std::getline(inFile, line) && (lineLimit == -1 || lineCount < lineLimit))
    {
        std::cout << line << std::endl;
        lineCount++;
    }
    inFile.close();
}

void Url::displayFile() const
{
    displayFileContents();
}

// Alias for lowercase url to match test expectations
typedef Url url;