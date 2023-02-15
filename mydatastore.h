#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "datastore.h"
#include "util.h"
#include <map>
#include <list>

class MyDataStore : public DataStore {
public:
	//Iterate over product keywords and add a pointer to the product to the set
	// matching the keyword in the map. Search returns the union or inter of all 
	// search set results.
	
	~MyDataStore();

	void addProduct(Product* p);

	void addUser(User* u);

	std::vector<Product*> search(std::vector<std::string>& terms, int type);

	void addToCart(std::string usrName, Product* item);

	void buyCart(std::string usrName);

	void displayCart(std::string user);

	void dump(std::ostream& ofile);

private:
	//some data structure that holds all available products
	std::map<std::string, std::set<Product*>> productsByTag;

	std::set<Product*> listOfProds;
	
	std::map<std::string, User*> nameObjMap;

	std::map<User*, std::list<Product*>> userCartMap;

	bool checkAvail(Product* prod);
};


#endif