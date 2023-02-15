#include "book.h"

book::book(std::string ISBN, std::string author, std::string bookName, double bookPrice, int itemQty) : Product("book", bookName, bookPrice, itemQty) {
	this->ISBN = ISBN;
	this->author = author;
}

std::set<std::string> book::keywords() const{
	std::set<std::string> bookKeySet;
	std::string bookName = this->getName();

	bookKeySet = parseStringToWords(bookName);

	bookKeySet.insert(ISBN);
	bookKeySet.insert(author);


	return bookKeySet;
}

std::string book::displayString() const{
	std::string format;

	double priceB = this->getPrice();
	std::string priceString = std::to_string(priceB);
	priceString = priceString.substr(0, 5);

	format += name_;
	format += "\nAuthor: ";
	format +=  author;
	format += " ISBN: ";
	format += ISBN;
	format += "\n";
	format += priceString;
	format += " ";
	format += std::to_string(this->getQty());
	format += " left.";

	return format;
}

void book::dump(std::ostream& os) const{
	
	os << category_ << std::endl << getName() << std::endl << getPrice() << std::endl << getQty() << std::endl << ISBN <<
	std::endl << author << std::endl;
}