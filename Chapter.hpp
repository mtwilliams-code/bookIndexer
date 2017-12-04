
#include <list>
#include <iterator>
#include <string>
#include "Paragraph.hpp"
#ifndef CHAPTER
#define CHAPTER

class Chapter{
    private:
        std::list <Paragraph> paragraphs;
    public:
        Chapter();
        ~Chapter();
        void addParagraph(Paragraph& P);
        
};

#endif