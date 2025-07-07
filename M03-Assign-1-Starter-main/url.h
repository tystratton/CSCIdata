/* Program name: url.h
Author: Ty Stratton
Date last updated: 6/23/2025
Purpose: Time Program Module 3 Assignment 1, learning stacks*/

#ifndef URL_H
#define URL_H

#include <string>
#include <vector>

class Url
{
public:
    Url(const std::string &url, const std::string &filename);
    void displayFileContents(int lineLimit = -1) const;
    void displayFile() const;

private:
    std::string urlAddress;
    std::string fileName;
};

// Alias for lowercase url to match test expectations
typedef Url url;

#endif // URL_H