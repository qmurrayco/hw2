#include "movie.h"

movie::movie(std::string rating, std::string genre, std::string name_, double price_, int qty_) : Product("movie", name_, price_, qty_) {
	this->rating = rating;
	this->genre = genre;

	std::cout << "in movie" << " " << genre << std::endl;
}

std::set<std::string> movie::keywords() const{
	std::set<std::string> movieKeySet;
	std::string movieName = this->getName();

	movieKeySet = parseStringToWords(movieName);

	movieKeySet.insert(genre);

	return movieKeySet;
}

std::string movie::displayString() const{
	std::string format;
	double cPrice = this->getPrice();
	std::string stringPrice = std::to_string(cPrice);
	stringPrice = stringPrice.substr(0, 5);

	format += name_;
	format += "\nGenre: ";
	format +=  genre;
	format += " Rating: ";
	format += rating;
	format += "\n";
	format += stringPrice;
	format += " ";
	format += std::to_string(this->getQty());
	format += " left.";

	return format;
}

void movie::dump(std::ostream& os) const{
	os << category_ << std::endl << getName() << std::endl << getPrice() << std::endl << getQty() << std::endl << 
	genre << std::endl << rating << std::endl;
}