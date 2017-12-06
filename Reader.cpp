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
    for (char const *cp = line; *cp != '\0'; ++cp)
    {
        if (!isspace(*cp) && !(*cp == '\n'))
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
    exception e;
    try
    {
        bookFile.open(bookFileName.c_str());
        if (bookFile.fail()) // throw only when needed
        {
            cout << string("Exception opening/reading file \"" + bookFileName + "\"\n"); // more accurate exception
            throw e;
        }
        synonymFile.open(synonym.c_str());
        if (synonymFile.fail()) // throw only when needed
        {
            cout << string("Exception opening/reading file \"" + bookFileName + "\"\n"); // more accurate exception
            throw e;
        }
        ignoreFile.open(ignore.c_str());
        if (ignoreFile.fail()) // throw only when needed
        {
            cout << string("Exception opening/reading file \"" + bookFileName + "\"\n"); // more accurate exception
            throw e;
        }
    }
    catch (exception &error)
    {
        cout << "Some error occured in Reader instantiation. Exiting.. \n";
        bookFile.close();
        synonymFile.close();
        ignoreFile.close();
        throw("broken");
    }
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
        std::getline(ignoreFile, nextLine);
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
        std::getline(synonymFile, nextLine);
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
    while (!bookFile.eof())
    {
        /*cout << "start loop << " << count << endl; //debug output */
        //reads first line of paragraph
        string nextLine;
        stringstream nextPara;
        nextLine = "some none-empty string";
        //reads each next line of paragraph until arrives at blank line (consists of just whitespace)
        while (!isBlankLine(nextLine) && !bookFile.eof())
        {
            std::getline(bookFile, nextLine);
            removePunc(nextLine);
            stringToLower(nextLine);
            //cout << "Read \"" << nextLine << endl; //debug output*/
            string word;
            stringstream nextLineStream;
            stringstream finishedLineStream;
            if (!isBlankLine(nextLine))
                nextLineStream << nextLine;
            while (nextLineStream >> word)
            {
                if (!ignore.count(word))
                {
                    map<string, string>::iterator itr;
                    if ((itr = synonyms.find(word)) != synonyms.end())
                    {
                        word = itr->second;
                    }
                    if (!isBlankLine(word)) {
                        newBook->addWord(word);
                        finishedLineStream << word << " ";
                    }
                }
            }
            string finishedNextLine = finishedLineStream.str();
            std::size_t pos;
            if ((pos = finishedNextLine.find('\n')) != string::npos)
                finishedNextLine.erase(pos, 1);

            finishedLineStream.str("");
            finishedLineStream << finishedNextLine;

            if (!isBlankLine(finishedNextLine)){
                finishedLineStream << "\n";
            }

            nextPara << finishedLineStream.str();
        }

        if (isBlankLine(nextPara.str()))
        {
            nextPara << "\n";
        }

        stringstream temp;
        //checks if paragraph is chapter title
        string firstWord, secondWord, thirdWord, firstLine, secondLine;
        int loc = nextPara.tellg();
        nextPara.seekg(loc);
        std::getline(nextPara, firstLine);
        std::getline(nextPara, secondLine);
        temp << firstLine;
        temp >> firstWord;
        temp >> secondWord;
        temp >> thirdWord;
        if (firstWord == "chapter" && secondWord != "" && thirdWord == "" && isBlankLine(secondLine))
        {                                                            // if it is chapter, another word, and then a blank line, it is a chapter title
            newBook->addChapter(secondWord);
        } //otherwise adds paragraph
        else
        {
            nextPara.seekg(loc);
            unique_ptr<stringstream> newPara = make_unique<stringstream>();
            *newPara << nextPara.str();
            newBook->addParagraph(move(newPara));
        }

    }
    return move(newBook);
}
