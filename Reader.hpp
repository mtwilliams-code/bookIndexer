#include <iostream>
#include <fstream>
#include <map>
#include <iterator>
#include <string>
#include <sstream>
#include <set>
#include <memory>
#include <algorithm>
#include "Book.hpp"
#include "Chapter.hpp"
#include "Paragraph.hpp"
#ifndef READER
#define READER

class Reader {
  private:
    void stringToLower(std::string& sl);
    void removePunc( std::string& text );
    bool isBlankLine(char const *line);
    bool isBlankLine(std::string const &line);
    std::ifstream bookFile;
    std::ifstream synonymFile;
    std::ifstream ignoreFile;

  public:
    Reader(std::string bookFileName, std::string synonym, std::string ignore); // constructor will open file
    ~Reader();                                                         // deconstructor will close file.
    std::unique_ptr<Book> read();        // std::unique_ptr<Book> reader.read();                                               //will read file and build a Book consisting of Chapters which have Paragraphs. This is where the meat of the parsing will be.



};

#endif
