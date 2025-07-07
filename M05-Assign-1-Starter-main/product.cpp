#include "product.h"

product::product(double price, std::string description, std::string prodNum, double rating)
{
    setPrice(price);
    setDescription(description);
    if (prodNum.size() > 0)
        this->prodNum = prodNum;
    else
        throw std::invalid_argument("Product number cannot be empty.");
    isPurchased = false;
    setRating(rating);
}

std::string product::getProdNum() const
{
    return prodNum;
}

std::string product::getDescription() const
{
    return description;
}

double product::getPrice() const
{
    return price;
}

void product::purchase()
{
    isPurchased = true;
}

double product::getRating() const
{
    return rating;
}

void product::setRating(double r)
{
    if (r >= 0)
        this->rating = r;
    else
        throw std::invalid_argument("The rating must be greater than 0.");
}

void product::setPrice(double price)
{
    if (price > 0)
        this->price = price;
    else
        throw std::invalid_argument("Price must be greater than 0.");
}

void product::setDescription(std::string description)
{
    this->description = description;
}

bool product::operator==(const product &op) const
{

    return this->prodNum == op.prodNum;
}

bool product::operator!=(const product &op) const
{
    return !(*this == op);
}

bool product::operator>(const product &op) const
{
    return this->prodNum > op.prodNum;
}

bool product::operator>=(const product &op) const
{
    return (*this > op) || (*this == op);
}

bool product::operator<(const product &op) const
{
    return this->prodNum < op.prodNum;
}

bool product::operator<=(const product &op) const
{
    return (*this < op) || (*this == op);
}

std::ostream &operator<<(std::ostream &out, const product &p)
{
    out << p.tostring();
    return out;
}

std::string product::tostring() const
{
    std::ostringstream out;
    out << std::setprecision(2) << std::fixed << std::showpoint;
    std::string purch = isPurchased ? "Not Available" : "Available";
    out << prodNum << " - " << description << " - $" << price << " - " << purch << " - " << rating << " stars out of 10.";
    return out.str();
}
