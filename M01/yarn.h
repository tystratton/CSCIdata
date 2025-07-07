/* Program name: yarn.h 
Author: Ty Stratton
Date last updated: 6/10/2025
Purpose: Yarn header file for class practice*/

#ifndef YARN_H
#define YARN_H

#include <string>
#include <map>
#include <iostream>
/*Write the include to get rid of std from my couts*/
using namespace std;

class YarnSkein {
public:
    enum fiberType { ACRYLIC, BAMBOO, COTTON, SILK, WOOL };
    enum weightType { BULKY, FINE, JUMBO, LACE, LIGHT, MEDIUM, SUPERBULKY, SUPERFINE };

    // Static conversion maps
    static const map<fiberType, string> fiberToStr;
    static const map<string, fiberType> strToFiber;
    static const map<string, weightType> strToWeight;
    static const map<weightType, string> weightToStr;

private:
    double hookSize;
    double length;
    double needleSize;
    double skeinWeight;
    fiberType fiber;
    int numFiberType;
    std::string color;
    weightType strandWeight;

public:
    // Constructors
    YarnSkein(string strandWeight, string color, double length, string fiber, double skeinWeight, double needleSize, double hookSize);
    YarnSkein(const YarnSkein& other);
    YarnSkein();

    // Assignment operator
    YarnSkein& operator=(const YarnSkein& other);

    // Getters
    double getHookSize() const;
    double getLength() const;
    double getNeedleSize() const;
    double getSkeinWeight() const;
    int getStrandWeight() const;
    std::string getColor() const;
    std::string getFiberList() const;
    std::string getStrandWeightName() const;

    // Setters
    void setColor(string color);
    void setFiber(string fiber);
    void setLength(double length);

    // Copy
    void copyYarn(const YarnSkein& other);
};

#endif // YARN_H

