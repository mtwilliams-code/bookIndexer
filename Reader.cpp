#include "Reader.hpp"

using namespace std;

void Reader::removeWord(string &S, string &toRemove)
{
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

    // debug stuff int count = 1;
    unique_ptr<Book> newBook = make_unique<Book>(synonyms, ignore);
    Chapter *newChap;
    int paraNumber = 0;
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
            string word;
            stringstream nextLineStream;
            nextLineStream << nextLine;
            while(nextLineStream >> word) {
                if (!ignore.count(word)) {
                    map<string, string>::iterator itr;
                    if ((itr = synonyms.find(word)) != synonyms.end())
                    {
                        word = itr->second;
                    }
                    nextPara << word << " ";
                }
            }
            getline(bookFile, nextLine);
            removePunc(nextLine);
            stringToLower(nextLine);
        }
        
        //checks if paragraph is chapter title
        string firstWord, secondWord, thirdWord, secondLine;
        int loc = nextPara.tellg();
        nextPara >> firstWord;
        nextPara >> secondWord;
        nextPara >> thirdWord;
        getline(nextPara, nextLine);
        if (firstWord == "chapter" && secondWord != "" && thirdWord == "" && isBlankLine(nextLine))
        {                  // if it is chapter, another word, and then a blank line, it is a chapter title
            cout << "found a chapter titled " << secondWord << endl; //debug output
            newBook->addChapter(secondWord);
            paraNumber = 0;
        }
        else 
        {
            nextPara.seekg(loc);
            unique_ptr<stringstream> newPara = make_unique<stringstream>();
            *newPara << nextPara.rdbuf();
            newBook->addParagraph(move(newPara));
        }

        
       /* THOWING SEGFAULTS HERE
        else
        { // else it is not a chapter titlea and is a normal paragraph
            int lineNumber = 0;
            paraNumber++;
            nextPara.seekg(loc);
            newPara = new Paragraph(newChap->getChapterTitle());
            while (getline(nextPara, nextLine))
            {
                lineNumber++;
                stringstream tempLine;
                tempLine << nextLine;
                while (tempLine >> firstWord)
                {
                    //if not in ignore
                    if (!ignore.count(firstWord))
                    {
                        map<string, string>::iterator itr;
                        // if in synonym, replace with word it means
                        if ((itr = synonyms.find(firstWord)) != synonyms.end())
                        {
                            firstWord = itr->second;
                        }
                        //add to paragraph
                        newPara->addWord(firstWord,paraNumber,lineNumber);
                    }
                }
                //add paragraph to last chapter (first check for null)
                if (newChap != NULL)
                {
                    newChap->addParagraph(newPara);
                }
            }
        }*/
    }
    return move(newBook);
}

