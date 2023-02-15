#include "mydatastore.h"

MyDataStore::~MyDataStore(){
	std::set<Product*>::iterator prodIter(listOfProds.begin());

	for(; prodIter != listOfProds.end(); ++prodIter){
		delete *prodIter;
	}

	std::map<std::string, User*>::iterator nameIter(nameObjMap.begin());

	for(; nameIter != nameObjMap.end(); ++nameIter){
		delete (*nameIter).second;
	}


}

void MyDataStore::addProduct(Product* p){

	listOfProds.insert(p);

	std::set<std::string> keys = p->keywords();
	std::set<std::string>::iterator keyIter(keys.begin());
	std::map<std::string, std::set<Product*>>::iterator loopIter;

	for(; keyIter != keys.end(); ++keyIter){
		if(productsByTag.find(*keyIter) != productsByTag.end()){
			loopIter = productsByTag.find(*keyIter);
			loopIter->second.insert(p);
		}else{
			std::set<Product*> newProdSet;
			newProdSet.insert(p);
			std::pair<std::string, std::set<Product*>> pr(*keyIter, newProdSet);
			std::pair<std::string, std::set<Product*>> prL(convToLower(*keyIter), newProdSet);
			productsByTag.insert(pr);
			productsByTag.insert(prL);
		}
	}
}

void MyDataStore::addUser(User* u){

	std::map<std::string, User*> nameToUsrObj;
	std::pair<std::string, User*> nameObjPair(u->getName(), u);

	nameObjMap.insert(nameObjPair);

	std::list<Product*> emptyCart;

	std::pair<User*, std::list<Product*>> usrCartPair(u, emptyCart);
	userCartMap.insert(usrCartPair);

}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){

	std::vector<Product*> searchResult;
	int termSize = terms.size();

	if(type == 0){
		//and

		std::set<std::set<Product*>> prodHits;

		for(int i = 0; i < termSize; i++){
			if(productsByTag.find(terms[i]) != productsByTag.end()){
				prodHits.insert(productsByTag.at(terms[i]));
			}
		}

		//std::cout << "In and I found:" << prodHits.size() << " product hits for search..." << std::endl;
		
		std::set<Product*> intersectResult;
		std::set<std::set<Product*>>::iterator hitIter(prodHits.begin());
		
		if(hitIter != prodHits.end()){
			intersectResult = *hitIter;
		}else{
			return searchResult;
		} //no hits

		++hitIter;

		for(; hitIter != prodHits.end(); ++hitIter){
			std::set<Product*> someSet = *hitIter;
			if(someSet.size() > 0){
				intersectResult = setIntersection(intersectResult, someSet);
			}
		}

		//std::cout << "The size of the intersection set is:" << intersectResult.size() << " ..." << std::endl;

		std::set<Product*>::iterator interIter = intersectResult.begin();

		for(; interIter != intersectResult.end(); ++interIter){
			searchResult.push_back(*interIter);
		}

		return searchResult;

	}
	
	else if(type == 1){
		//or
		std::set<std::set<Product*>> prodHits;
		for(int i = 0; i < termSize; i++){
			if(productsByTag.find(terms[i]) != productsByTag.end()){
				prodHits.insert(productsByTag.find(terms[i])->second);
			}
		}

		//std::cout << "PROD HITS IN OR: " << prodHits.size() << std::endl;

		std::set<Product*> unionResult;

		std::set<std::set<Product*>>::iterator uIter(prodHits.begin());

		for(; uIter != prodHits.end(); ++uIter){
			std::set<Product*> someSet = *uIter;
			unionResult = setUnion(unionResult, someSet);
		}

		//std::cout << "UNION RESULTS SIZE: " << unionResult.size() << std::endl;

		std::set<Product*>::iterator vecIter(unionResult.begin());
		for(; vecIter != unionResult.end(); ++vecIter){
			searchResult.push_back(*vecIter);
		}

		return searchResult;
	}

	// ????
	return searchResult;
}

void MyDataStore::addToCart(std::string usrName, Product* item){
	if(nameObjMap.find(usrName) == nameObjMap.end()){
		std::cout << "Invalid request" << std::endl;
		return;
	}

	User* usr = nameObjMap.find(usrName)->second;
	

	userCartMap.at(usr).push_front(item);
	//(*listOfProds.find(item))->subtractQty(1);

}

void MyDataStore::buyCart(std::string usrName){
	if(nameObjMap.find(usrName) == nameObjMap.end()){
		std::cout << "Invalid username" << std::endl;
		return;
	}

	User* usr = nameObjMap.at(usrName);

	std::list<Product*>::iterator cartIter(userCartMap.at(usr).begin());

	//not so sure about this
	// for(; cartIter != userCartMap.at(usr).end(); ++cartIter){
	// 	if((usr->getBalance() - (*cartIter)->getPrice()) >= 0 && checkAvail(*cartIter)){
	// 		usr->deductAmount((*cartIter)->getPrice());
	// 		(*cartIter)->subtractQty(1);

	// 		userCartMap.at(usr).erase(cartIter);
	// 		cartIter = userCartMap.at(usr).begin();
	// 	}
	// }

	// for(; cartIter != userCartMap.at(usr).end(); ++cartIter){
	// 	if((usr->getBalance() - (*cartIter)->getPrice()) >= 0 && checkAvail(*cartIter)){
	// 		usr->deductAmount((*cartIter)->getPrice());
	// 		(*cartIter)->subtractQty(1);

	// 		std::cout << "buy" << std::endl;
			
	// 		userCartMap.at(usr).erase(cartIter);
	// 		// cartIter = userCartMap.at(usr).begin();
	// 	}
	// }

	// while(cartIter != userCartMap.at(usr).end()){
	// 	if((usr->getBalance() - (*cartIter)->getPrice()) >= 0 && checkAvail(*cartIter)){
	// 		usr->deductAmount((*cartIter)->getPrice());
	// 		(*cartIter)->subtractQty(1);

	// 		std::cout << "buy" << std::endl;
			
	// 		userCartMap.at(usr).erase(cartIter);
	// 		cartIter = userCartMap.at(usr).begin();
	// 	}
	// }

	std::list<Product*> afterBuy;

	for(; cartIter != userCartMap.at(usr).end(); ++cartIter){
		if((usr->getBalance() - (*cartIter)->getPrice()) >= 0 && checkAvail(*cartIter)){

			usr->deductAmount((*cartIter)->getPrice());
			(*cartIter)->subtractQty(1);

		}else{
			afterBuy.push_back(*cartIter);
		}
	}

	userCartMap.at(usr) = afterBuy;

}

void MyDataStore::displayCart(std::string user){
	if(nameObjMap.find(user) == nameObjMap.end()){
		std::cout << "Invalid username" << std::endl;
		return;
	}

	// std::list<Product*>::iterator cartIter;
	// User* usr = nameObjMap.at(user);
	// cartIter = userCartMap.at(usr).begin();

	// for(int i = 1; cartIter != userCartMap.at(usr).end(); ++cartIter, i++){
	// 	std::cout << "Item " << i << std::endl << (*cartIter)->displayString() << std::endl << std::endl;
	// }

	std::list<Product*>::iterator cartIter;
	User* usr = nameObjMap.at(user);
	cartIter = userCartMap.at(usr).end();
	int i = 1;
	if(cartIter == userCartMap.at(usr).begin()){std::cout << "Item " << i << std::endl << (*cartIter)->displayString() << std::endl << std::endl; return;}
	--cartIter;

	for(; cartIter != userCartMap.at(usr).begin(); --cartIter, i++){
		std::cout << "Item " << i << std::endl << (*cartIter)->displayString() << std::endl << std::endl;
	}

	std::cout << "Item " << i << std::endl << (*cartIter)->displayString() << std::endl << std::endl;

}

bool MyDataStore::checkAvail(Product* prod){
	 return (prod->getQty() > 0);
}

void MyDataStore::dump(std::ostream& ofile){
	ofile << "<products>" << std::endl;

	std::set<Product*>::iterator prodsIter(listOfProds.begin());

	for(; prodsIter != listOfProds.end(); ++prodsIter){
		(*prodsIter)->dump(ofile);
	}

	ofile << "</products>" << std::endl;
	ofile << "<users>" << std::endl;

	std::map<std::string, User*>::iterator usrIter(nameObjMap.begin());

	for(; usrIter != nameObjMap.end(); ++usrIter){
		(*usrIter).second->dump(ofile);
	}

	ofile << "</users>" << std::endl;
}
