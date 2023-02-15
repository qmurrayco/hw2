#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
	typename std::set<T> setI;
	typename std::set<T>::iterator setOneIter(s1.begin());
	typename std::set<T>::iterator setTwoIter(s2.begin());

	//as you walk, look to see if they are the same, if not compare which is larger and iterate the smaller
	//trying to take advantage of the ordered nature of sets 
	//insert -> O(log(n))
	//walking should be n as you are just concerned with the length of the shorter set
	while(setOneIter != s1.end() && setTwoIter != s2.end()){
		if(*setOneIter == *setTwoIter){
			//both are the same and can both be iterated
			setI.insert(*setOneIter);
			++setOneIter;
			++setTwoIter;
		}else{
			if(*setOneIter > *setTwoIter){
				++setTwoIter;
			}else{
				++setOneIter;
			}
		}
	}

	return setI;
}

template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{

	typename std::set<T> setU;
	if(s1.size() > s2.size()){
		setU = s1;

		typename std::set<T>::iterator setIter(s2.begin());
		for(; setIter != s2.end(); ++setIter){
			setU.insert(*setIter);
		}

		return setU;

	}else{
		setU = s2;

		typename std::set<T>::iterator setIter(s1.begin());
		for(; setIter != s1.end(); ++setIter){
			setU.insert(*setIter);
		}

		return setU;
	}

}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif