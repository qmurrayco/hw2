#ifndef BOOK_H
#define BOOK_H
#include "product.h"

class book : public Product {
public:
	
	book(std::string ISBN, std::string author, std::string name_, double price_, int qty_);

	std::set<std::string> keywords() const;

	std::string displayString() const;

	void dump(std::ostream& os) const;

private:

	std::string ISBN;
	std::string author;

};



#endif