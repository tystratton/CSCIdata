#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <iomanip>

class product
{
public:
    product(double, std::string description, std::string prodNum, double rating = 0);
    std::string getProdNum() const;
    std::string getDescription() const;
    double getPrice() const;
    void purchase();
    double getRating() const;
    void setRating(double);
    void setPrice(double);
    void setDescription(std::string);
    bool operator==(const product &) const;
    bool operator!=(const product &) const;
    bool operator>(const product &) const;
    bool operator>=(const product &) const;
    bool operator<(const product &) const;
    bool operator<=(const product &) const;
    friend std::ostream &operator<<(std::ostream &, const product &);

protected:
    double price;
    double rating;
    std::string description;
    std::string prodNum;
    bool isPurchased;
    std::string tostring() const;
};

#endif