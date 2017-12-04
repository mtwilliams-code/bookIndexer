#include <list>
#include <iterator>
#include <map>
#include <set>
#include <string>
#include <iostream>
#include "Chapter.hpp"
#ifndef BOOK
#define BOOK

class Book {
    private:
        std::list<Chapter*> chapters;
        std::map<std::string, std::string> synonyms;
        std::set<std::string> ignore;
    public:
        Book( std::map<std::string,std::string>& S, std::set<std::string>& I );
        ~Book();
        void addChapter(Chapter* C);
        void printSynonyms();
        void printIgnored();
};


#endif