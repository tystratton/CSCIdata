/* Program name : yarn.cpp
 * Author       : Tarik Beyenal
 * Date updated : 6/13/2025
 * Purpose      : Yarn identification system
 */
#include "yarn.h"
#include <algorithm>
#include <cctype>
#include <sstream>

const std::map<YarnSkein::fiberType , std::string> YarnSkein::fiberToStr = {
    { YarnSkein::ACRYLIC, "Acrylic" },
    { YarnSkein::BAMBOO,  "Bamboo"  },
    { YarnSkein::COTTON,  "Cotton"  },
    { YarnSkein::SILK,    "Silk"    },
    { YarnSkein::WOOL,    "Wool"    }
};

const std::map<std::string, YarnSkein::fiberType> YarnSkein::strToFiber = {
    { "ACRYLIC", YarnSkein::ACRYLIC },
    { "BAMBOO",  YarnSkein::BAMBOO  },
    { "COTTON",  YarnSkein::COTTON  },
    { "SILK",    YarnSkein::SILK    },
    { "WOOL",    YarnSkein::WOOL    }
};

const std::map<std::string, YarnSkein::weightType> YarnSkein::strToWeight = {
    { "LACE",       YarnSkein::LACE       },
    { "SUPER FINE", YarnSkein::SUPERFINE },
    { "FINE",       YarnSkein::FINE       },
    { "LIGHT",      YarnSkein::LIGHT      },
    { "MEDIUM",     YarnSkein::MEDIUM     },
    { "BULKY",      YarnSkein::BULKY      },
    { "SUPER BULKY",YarnSkein::SUPERBULKY },
    { "JUMBO",      YarnSkein::JUMBO      }
};

const std::map<YarnSkein::weightType, std::string> YarnSkein::weightToStr = {
    { YarnSkein::LACE,       "Lace"       },
    { YarnSkein::SUPERFINE, "Super Fine" },
    { YarnSkein::FINE,       "Fine"       },
    { YarnSkein::LIGHT,      "Light"      },
    { YarnSkein::MEDIUM,     "Medium"     },
    { YarnSkein::BULKY,      "Bulky"      },
    { YarnSkein::SUPERBULKY, "Super Bulky"},
    { YarnSkein::JUMBO,      "Jumbo"      }
};

void YarnSkein::ensurePositive(double v, const char* field)
{
    if (v < 0.0)
        throw std::invalid_argument(std::string(field) + " cannot be negative");
}

// Constructor
YarnSkein::YarnSkein(std::string strandWeightStr,
                     std::string color,
                     double      length,
                     std::string fiberCSV,
                     double      skeinWeight,
                     double      needleSize,
                     double      hookSize)
    : hookSize(hookSize),
      length(length),
      needleSize(needleSize),
      skeinWeight(skeinWeight),
      fiber(nullptr),
      numFiberType(0),
      color()
{
    std::transform(strandWeightStr.begin(), strandWeightStr.end(),
                   strandWeightStr.begin(), [](unsigned char c){ return std::toupper(c); });

    auto wIt = strToWeight.find(strandWeightStr);
    if (wIt == strToWeight.end())
        throw std::invalid_argument("Invalid strand weight");
    strandWeight = wIt->second;

    // numeric
    ensurePositive(length,      "Length");
    ensurePositive(skeinWeight, "Skein weight");
    ensurePositive(needleSize,  "Needle size");
    ensurePositive(hookSize,    "Hook size");

    setColor(color);
    setFiber(fiberCSV);
}

YarnSkein::YarnSkein(const YarnSkein& other)
    : fiber(nullptr), numFiberType(0)
{
    copyYarn(other);
}

YarnSkein& YarnSkein::operator=(const YarnSkein& other)
{
    if (this != &other) {
        delete[] fiber;
        copyYarn(other);
    }
    return *this;
}

YarnSkein::~YarnSkein()
{
    delete[] fiber;
}

void YarnSkein::copyYarn(const YarnSkein& o)
{
    hookSize     = o.hookSize;
    length       = o.length;
    needleSize   = o.needleSize;
    skeinWeight  = o.skeinWeight;
    strandWeight = o.strandWeight;
    color        = o.color;

    numFiberType = o.numFiberType;
    fiber        = new fiberType[numFiberType];
    std::copy(o.fiber, o.fiber + numFiberType, fiber);
}

// Setters
void YarnSkein::setColor(std::string c)
{
    if (c.empty())
        throw std::invalid_argument("Color cannot be empty");
    color = c;
}

static inline std::string trim(const std::string& s)
{
    const char* ws = " \t\r\n\f\v";
    size_t b = s.find_first_not_of(ws);
    size_t e = s.find_last_not_of(ws);
    return (b == std::string::npos) ? "" : s.substr(b, e - b + 1);
}

void YarnSkein::setFiber(std::string csv)
{
    std::stringstream ss(csv);
    std::string token;
    std::vector<fiberType> parsed;
    while (std::getline(ss, token, ',')) {
        token = trim(token);
        std::transform(token.begin(), token.end(), token.begin(),
                       [](unsigned char c){ return std::toupper(c); });
        auto fIt = strToFiber.find(token);
        if (fIt == strToFiber.end())
            throw std::invalid_argument("Invalid fiber: " + token);
        parsed.push_back(fIt->second);
    }
    if (parsed.empty())
        throw std::invalid_argument("No fibers specified");

    numFiberType = static_cast<int>(parsed.size());
    fiber        = new fiberType[numFiberType];
    std::copy(parsed.begin(), parsed.end(), fiber);
}

std::string YarnSkein::getStrandWeightName() const
{
    return weightToStr.at(strandWeight);
}

std::string YarnSkein::getFiberList() const
{
    std::string out;
    for (int i = 0; i < numFiberType; ++i) {
        out += fiberToStr.at(fiber[i]);
        if (i + 1 < numFiberType)
            out += ", ";
    }
    return out;
}