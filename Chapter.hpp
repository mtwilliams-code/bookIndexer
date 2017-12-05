
#include <list>
#include <iterator>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include "Paragraph.hpp"
#ifndef CHAPTER
#define CHAPTER

class Chapter{
    private:
        std::list <Paragraph> paragraphs;
        const std::string chapterTitle;
        int paragraphNumber;
    public:
        Chapter(std::string S) : chapterTitle(S), paragraphNumber(0) {};
        ~Chapter();
        std::string getChapterTitle() const {return chapterTitle;};
        void addParagraph(std::unique_ptr<std::stringstream> P);
        Paragraph* getParagraph(int N) const;
        int getParagraphCount() const;
        void printChapter() const;
        
};

#endif