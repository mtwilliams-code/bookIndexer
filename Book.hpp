#include <list>
#include <iterator>
#include "Chapter.hpp"
#ifndef BOOK
#define BOOK

class Book {
    private:
        std::list<Chapter*> chapters;
    public:
        Book();
        ~Book();
        void addChapter(Chapter* C);
};


#endif