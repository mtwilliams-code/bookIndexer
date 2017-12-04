#include "Book.hpp"

using namespace std;

Book::Book( map<string,string>& S, set<string>& I ) : synonyms(S), ignore(I) {
    
}

Book::~Book() {

}

void Book::addChapter(Chapter* C) {

}

void Book::printSynonyms() {
    map<string,string>::iterator itr;
    for(itr=synonyms.begin(); itr !=synonyms.end(); ++itr){
        cout << itr->first << " " << itr->second << endl;
    }
}

void Book::printIgnored() {
    set<string>::iterator itr;
    for(auto ignored : ignore){
        cout << ignored << endl;
    }
}