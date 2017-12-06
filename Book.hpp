#include <list>
#include <iterator>
#include <map>
#include <set>
#include <string>
#include <memory>
#include <iostream>
#include <sstream>
#include "Chapter.hpp"
#ifndef BOOK
#define BOOK

class Book {
    private:
        std::list<Chapter> chapters;
        std::map<std::string, std::string> synonyms;
        std::set<std::string> ignore;
        std::set<std::string> allWords;
    public:
        Book( std::map<std::string,std::string>& S, std::set<std::string>& I );
        ~Book();
        void addChapter(Chapter C);
        void addChapter(std::string title);
        void printSynonyms() const;
        void printIgnored() const;
        void printChapters() const;
        void printBook() const;
        void addParagraph(std::unique_ptr<std::stringstream> P);
        void addWord(std::string word);
        Chapter* getChapter(int N) const;
        int getChapterCount() const;
};


#endif