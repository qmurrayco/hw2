#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    set<string> wordSet;

		/*
			gotta make it recognize isbn ???

		*/

		//why would I need the other trim functions..? really lost on the use of them. 
    std::string cnvRaw = trim(rawWords);
    cnvRaw = convToLower(rawWords);
    
    //using string stream to break up sentence and begin breakdown of key words.
    stringstream sStream(cnvRaw);
    //for each word in sentence, will use in while loop
    string singleWord;
		int pos = -1;

		//could this be faster/require less code? does it handle odd edge cases? 
		while(sStream >> singleWord){
			int wSize = singleWord.size();
			
			if(singleWord == "&"){wordSet.insert("and");}

			//bigger than two then keyword
			if(wSize >= 2){
				//look for punc
				for(int i = 0; i < wSize; i++){
					if(singleWord[i] < 97 || singleWord[i] > 122){
						//punc found, break and anaylze substrings for potential keyword
						pos = i;
						break;
					}
				}
			}

				if(pos != -1){
					//punc location established, look at either end and insert if char count >= 2 (keyword)
					if(pos >= 2){wordSet.insert(singleWord.substr(0, pos));}
					if((wSize-1)-pos >= 2){wordSet.insert(singleWord.substr(pos+1, wSize));}

					//reset for next word
					pos = -1;

				}else{
					//just some other keyword with char count greater than 2 (no punc)
					wordSet.insert(singleWord);
				}
			}

    return wordSet;

}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
