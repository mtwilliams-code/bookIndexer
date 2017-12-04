#include "Reader.hpp"

using namespace std;


void Reader::removeWord(string& S, string& toRemove) {
    string::size_type n = toRemove.length();
    for (string::size_type i = S.find(toRemove);
        i != string::npos;
        i = S.find(toRemove))
        S.erase(i, n);
}

void Reader::stringToLower(std::string &sl)
{
    transform(sl.begin(), sl.end(), sl.begin(), ::tolower);
}

void Reader::removePunc(string &text)
{
    for (int i = 0, len = text.size(); i < len; i++)
    {
        if (ispunct(text[i]))
        {
            text.erase(i--, 1);
            len = text.size();
        }
    }
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

Reader::Reader(std::string bookFileName, std::string synonym, std::string ignore)
{
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
    // reads and stores the ignore file as a set, to be passed to the Book.
    set<string> ignore;
    while (!ignoreFile.eof())
    {
        string nextLine;
        getline(ignoreFile, nextLine);
        removePunc(nextLine);
        stringToLower(nextLine);
        stringstream line;
        string ignoredWord;
        line << nextLine;
        line >> ignoredWord;
        if (ignoredWord != "chapter" && !ignoredWord.empty())
            ignore.emplace(ignoredWord);
    }

    //reads and stores the synonym file to be passed to the book. 
    map<string, string> synonyms;
    while (!synonymFile.eof())
    {
        string nextLine;
        getline(synonymFile, nextLine);
        removePunc(nextLine);
        stringToLower(nextLine);
        string root, syn;
        stringstream line;
        line << nextLine;
        line >> root;
        while (line >> syn)
        {
            synonyms.emplace(syn, root);
        }
    }
    //adds synonyms for ignored words to ignore list
    for (map<string, string>::iterator itr1 = synonyms.begin(); itr1 != synonyms.end(); ++itr1)
    {
        map<string, string>::iterator itr2 = itr1;
        if (ignore.find(itr2->second) != ignore.end())
        {
            ignore.emplace(itr1->first);
        }
        while ((itr2 = synonyms.find(itr2->second)) != synonyms.end())
        {
            if (ignore.find(itr2->second) != ignore.end())
            {
                ignore.emplace(itr1->first);
                break;
            }
        }
    }
    //changes synonyms to farthest synonym
    for (map<string, string>::iterator itr1 = synonyms.begin(); itr1 != synonyms.end(); ++itr1)
    {
        map<string, string>::iterator itr2 = itr1;
        while ((itr2 = synonyms.find(itr2->second)) != synonyms.end())
        {
            itr1->second = itr2->second;
        }
    }
    int count = 1;
    auto finishedBook = make_unique<Book>(synonyms, ignore);
    while (!bookFile.eof())
    {
        /*cout << "start loop << " << count << endl; //debug output */
        //reads first line of paragraph
        string nextLine;
        stringstream nextPara;
        getline(bookFile, nextLine);
        removePunc(nextLine);
        stringToLower(nextLine);
        //reads each next line of paragraph until arrives at blank line (consists of just whitespace)
        while (!isBlankLine(nextLine) && !bookFile.eof())
        {
            /*cout << "Read \"" << nextLine << endl; //debug output*/
            nextPara << nextLine;
            getline(bookFile, nextLine);
            removePunc(nextLine);
            stringToLower(nextLine);
        }
        //checks if paragraph is chapter title
        string firstWord, secondWord, thirdWord, secondLine;
        int loc = nextPara.tellg();
        nextPara >> firstWord; nextPara >> secondWord; nextPara >> thirdWord;
        getline(nextPara, nextLine);
        if (firstWord == "chapter" && secondWord != "" && thirdWord == "" && isBlankLine(nextLine)) {
            cout << "found a chapter titled " << secondWord << endl; //debug output
        }
        /*cout << "end loop " << count++ << endl; //debug output */
        nextPara.seekg(loc);

    }
    return move(finishedBook);
}
