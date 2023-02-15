#include "clothing.h"

clothing::clothing(std::string size, std::string brand, std::string name_, double price_, int qty_) : Product("clothing", name_, price_, qty_) {
	this->size = size;
	this->brand = brand;
}

std::set<std::string> clothing::keywords() const{
	std::set<std::string> clothingKeySet;
	std::string clothingName = this->getName();

	clothingKeySet = parseStringToWords(clothingName);

	clothingKeySet.insert(brand);

	return clothingKeySet;
}

std::string clothing::displayString() const{
	std::string format;
	double dPrice = this->getPrice();
	std::string stringPrice = std::to_string(dPrice);
	stringPrice = stringPrice.substr(0, 5);

	format += name_;
	format += "\nSize: ";
	format +=  size;
	format += " Brand: ";
	format += brand;
	format += "\n";
	format += stringPrice;
	format += " ";
	format += std::to_string(this->getQty());
	format += " left.";

	return format;
}

void clothing::dump(std::ostream& os) const{
	//not sure
	os << category_ << std::endl << getName() << std::endl << getPrice() << std::endl << getQty() << std::endl << 
	size << std::endl << brand << std::endl;
}