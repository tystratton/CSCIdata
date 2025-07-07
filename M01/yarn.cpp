/* Program name: yarn.cpp 
Author: Ty Stratton
Date last updated: 6/10/2025
Purpose: Yarn implementation file for class practice*/

#include "yarn.h"
#include <sstream>
#include <algorithm>
#include <stdexcept>

// Dynamic array to store fiber types for each YarnSkein instance
static map<const YarnSkein*, YarnSkein::fiberType*> fiberArrays;
static map<const YarnSkein*, int> fiberCounts;

// Static map definitions
const map<YarnSkein::fiberType, string> YarnSkein::fiberToStr = {
    {ACRYLIC, "ACRYLIC"},
    {BAMBOO, "BAMBOO"},
    {COTTON, "COTTON"},
    {SILK, "SILK"},
    {WOOL, "WOOL"}
};

const map<string, YarnSkein::fiberType> YarnSkein::strToFiber = {
    {"ACRYLIC", ACRYLIC},
    {"BAMBOO", BAMBOO},
    {"COTTON", COTTON},
    {"SILK", SILK},
    {"WOOL", WOOL}
};

const map<string, YarnSkein::weightType> YarnSkein::strToWeight = {
    {"BULKY", BULKY},
    {"FINE", FINE},
    {"JUMBO", JUMBO},
    {"LACE", LACE},
    {"LIGHT", LIGHT},
    {"MEDIUM", MEDIUM},
    {"SUPERBULKY", SUPERBULKY},
    {"SUPERFINE", SUPERFINE}
};

const map<YarnSkein::weightType, string> YarnSkein::weightToStr = {
    {BULKY, "BULKY"},
    {FINE, "FINE"},
    {JUMBO, "JUMBO"},
    {LACE, "LACE"},
    {LIGHT, "LIGHT"},
    {MEDIUM, "MEDIUM"},
    {SUPERBULKY, "SUPERBULKY"},
    {SUPERFINE, "SUPERFINE"}
};

string toUpperCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

// Default constructor
YarnSkein::YarnSkein() {
    hookSize = 0.0;
    length = 0.0;
    needleSize = 0.0;
    skeinWeight = 0.0;
    fiber = ACRYLIC;
    numFiberType = 0;
    color = "";
    strandWeight = LIGHT;
}

// Parameterized constructor
YarnSkein::YarnSkein(string strandWeight, string color, double length, string fiber, double skeinWeight, double needleSize, double hookSize) {
    // Variables can't be negative
    if (length < 0) {
        throw invalid_argument("Length cannot be negative");
    }
    if (skeinWeight < 0) {
        throw invalid_argument("Skein weight cannot be negative");
    }
    if (needleSize < 0) {
        throw invalid_argument("Needle size cannot be negative");
    }
    if (hookSize < 0) {
        throw invalid_argument("Hook size cannot be negative");
    }

    this->length = length;
    this->skeinWeight = skeinWeight;
    this->needleSize = needleSize;
    this->hookSize = hookSize;
    this->color = color;

    // Validate and set strand weight
    string upperStrandWeight = toUpperCase(strandWeight);
    if (strToWeight.find(upperStrandWeight) == strToWeight.end()) {
        throw invalid_argument("Invalid strand weight: " + strandWeight);
    }
    this->strandWeight = strToWeight.at(upperStrandWeight);

    setFiber(fiber);
}

// Destructor
YarnSkein::~YarnSkein() {
    // Clean up dynamic array
    if (fiberArrays.find(this) != fiberArrays.end()) {
        delete[] fiberArrays[this];
        fiberArrays.erase(this);
        fiberCounts.erase(this);
    }
}

// Copy constructor
YarnSkein::YarnSkein(const YarnSkein& other) {
    copyYarn(other);
}

// Assignment operator
YarnSkein& YarnSkein::operator=(const YarnSkein& other) {
    if (this != &other) {
        copyYarn(other);
    }
    return *this;
}

// Private setFiber function - parses comma-separated fiber string
void YarnSkein::setFiber(string fiberStr) {
    stringstream ss1(fiberStr);
    string fiberToken;
    int count = 0;
    
    while (getline(ss1, fiberToken, ',')) {
        fiberToken = trim(fiberToken);
        string upperFiber = toUpperCase(fiberToken);
        
        // Validate fiber type
        if (strToFiber.find(upperFiber) == strToFiber.end()) {
            throw invalid_argument("Invalid fiber type: " + fiberToken);
        }
        
        count++;
    }
    
    if (count == 0) {
        throw invalid_argument("No valid fiber types found");
    }

    // Create dynamic array to store all fiber types
    this->numFiberType = count;
    
    // Clean up any existing array for this instance
    if (fiberArrays.find(this) != fiberArrays.end()) {
        delete[] fiberArrays[this];
    }
    
    // Create new dynamic array
    fiberArrays[this] = new fiberType[this->numFiberType];
    fiberCounts[this] = this->numFiberType;
    
    // Second pass: populate the dynamic array
    stringstream ss2(fiberStr);
    int index = 0;
    while (getline(ss2, fiberToken, ',')) {
        fiberToken = trim(fiberToken);
        string upperFiber = toUpperCase(fiberToken);
        fiberArrays[this][index] = strToFiber.at(upperFiber);
        index++;
    }
}

// Getters
double YarnSkein::getHookSize() const {
    return hookSize;
}

double YarnSkein::getLength() const {
    return length;
}

double YarnSkein::getNeedleSize() const {
    return needleSize;
}

double YarnSkein::getSkeinWeight() const {
    return skeinWeight;
}

int YarnSkein::getStrandWeight() const {
    return static_cast<int>(strandWeight);
}

string YarnSkein::getColor() const {
    return color;
}

string YarnSkein::getFiberList() const {
    string result = "";
    if (fiberArrays.find(this) != fiberArrays.end()) {
        for (int i = 0; i < numFiberType; i++) {
            if (i > 0) result += ", ";
            result += fiberToStr.at(fiberArrays.at(this)[i]);
        }
    }
    return result;
}

string YarnSkein::getStrandWeightName() const {
    return weightToStr.at(strandWeight);
}

// Public setters
void YarnSkein::setColor(string color) {
    this->color = color;
}

void YarnSkein::setLength(double length) {
    if (length < 0) {
        throw invalid_argument("Length cannot be negative");
    }
    this->length = length;
}

// Copy function
void YarnSkein::copyYarn(const YarnSkein& other) {
    this->hookSize = other.hookSize;
    this->length = other.length;
    this->needleSize = other.needleSize;
    this->skeinWeight = other.skeinWeight;
    this->fiber = other.fiber;
    this->numFiberType = other.numFiberType;
    this->color = other.color;
    this->strandWeight = other.strandWeight;
    
    // Copy dynamic array
    if (fiberArrays.find(&other) != fiberArrays.end()) {
        // Clean up any existing array for this instance
        if (fiberArrays.find(this) != fiberArrays.end()) {
            delete[] fiberArrays[this];
        }
        
        // Create new dynamic array and copy data
        fiberArrays[this] = new fiberType[this->numFiberType];
        fiberCounts[this] = this->numFiberType;
        
        for (int i = 0; i < this->numFiberType; i++) {
            fiberArrays[this][i] = fiberArrays[&other][i];
        }
    }
}