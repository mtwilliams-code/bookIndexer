#include <map>
#include <iterator>
#include <string>
#include <sstream>
#include <iostream>
#include <memory>
#ifndef PARAGRAPH
#define PARAGRAPH

class Paragraph{
    private:
        std::map <std::string, int> occurances;
        std::multimap <std::string, std::string> location;
        std::unique_ptr<std::stringstream> text;
        std::string chapterTitle;
        int paragraphNumber;
        void addWord(std::string word, int paraNum, int lineNum); //will check if word is already in multimap and then either add it and the location or just increment occurances

    public:
        Paragraph(std::unique_ptr<std::stringstream> S, int paraNumber, std::string title);
        Paragraph(const Paragraph &P);
        ~Paragraph();
        int getWordOccuranceCount(std::string S);
        void printParagraph() const;

};

#endif