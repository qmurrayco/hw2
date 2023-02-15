#ifndef CLOTHING_H
#define CLOTHING_H
#include "product.h"

class clothing : public Product{
public:

	clothing(std::string size, std::string brand, std::string name_, double price_, int qty_);

	std::set<std::string> keywords() const;

	std::string displayString() const;

	void dump(std::ostream& os) const;

private:

	std::string size;
	std::string brand;

};



#endif