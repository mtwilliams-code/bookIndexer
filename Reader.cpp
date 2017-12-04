#include "Reader.hpp"

using namespace std;

string Reader::removePunc(string text)
{
    for (int i = 0, len = text.size(); i < len; i++)
    {
        if (ispunct(text[i]))
        {
            text.erase(i--, 1);
            len = text.size();
        }
    }
    return text;
}
bool Reader::isBlankLine(char const *line)
{
    for (char const *cp = line; *cp; ++cp)
    {
        if (!isspace(*cp))
            return false;
    }
    return true;
}

bool Reader::isBlankLine(string const &line)
{
    return isBlankLine(line.c_str());
}

Reader::Reader(std::string bookFileName, std::string synonym, std::string ignore) {
    /*bookFile.exceptions ( ifstream::failbit | ifstream::badbit );
    try{*/
    bookFile.open(bookFileName.c_str()); /*
    } 
    catch (const ifstream::failure& e) {
    std::cout << "Exception opening/reading file";
  }*/
    synonymFile.open(synonym.c_str());
    ignoreFile.open(ignore.c_str());
}

Reader::~Reader()
{
    bookFile.close();
    synonymFile.close();
    ignoreFile.close();
}

unique_ptr<Book> Reader::read()
{
    string currentLine, nextLine;
    stringstream nextPara;
    map<string, string> synonyms;
    while (!synonymFile.eof())
    {
        getline(synonymFile, nextLine);
        nextLine = removePunc(nextLine);
        string root, syn;
        stringstream line;
        line << nextLine;
        line >> root;
        while (line >> syn)
        {
            synonyms.emplace(syn, root);
        }
    }
    set<string> ignore;
    auto finishedBook = make_unique<Book>(synonyms, ignore);

    /*
    while (!bookFile.eof())
    {
        getline(bookFile, nextLine);
        nextLine = removePunc(nextLine);
        if (!isBlankLine(nextLine))
        {
        }
    }
*/
    return move(finishedBook);
}
