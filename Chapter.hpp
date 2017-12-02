
#include <list>
#include <iterator>
#include <string>
#include <fstream>
#include "Paragraph.hpp"
#ifndef CHAPTER
#define CHAPTER

class Chapter{
    private:
        std::list <Paragraph> paragraphs;
    public:
        Chapter();
        ~Chapter();

};

#endif