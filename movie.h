#ifndef MOVIE_H
#define MOVIE_H
#include "product.h"


class movie : public Product {
public:

	movie(std::string rating, std::string genre, std::string name_, double price_, int qty_);

	std::set<std::string> keywords() const;

	std::string displayString() const;

	void dump(std::ostream& os) const;

private:

	std::string rating;
	std::string genre;

};



#endif