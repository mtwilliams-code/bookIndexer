#include <string>
#include <iostream>
#include <cctype>
#include <sstream>
#include <iostream>
#include <memory>
#include "Reader.hpp"
using namespace std;

int main(int argc, char *argv[])
{

    string num;
    string bookname, synname, ignorename;
    if (argc == 4)
    {
        bookname = "./testcases/" + string(argv[1]);
        synname = "./testcases/" + string(argv[2]);
        ignorename = "./testcases/" + string(argv[3]);
    }
    else if (argc == 2)
    {
        num = string(argv[1]);
        bookname = "./testcases/" + num + "_book.txt";
        synname = "./testcases/" + num + "_synonyms.txt";
        ignorename = "./testcases/" + num + "_ignore.txt";
    }
    else
    {
        cout << "Invalid arguments" << endl;
        return 100;
    }
    Reader reader_(bookname, synname, ignorename);
    unique_ptr<Book> book_ = reader_.read();
    /* //debug output
    book_->printSynonyms();
    book_->printIgnored();
    book_->printChapters();
    book_->printAllWords();
    cout << endl;
    book_->printBook();

    cout << endl;
*/
    book_->printIndex();
    cout << endl;
    book_->printOccurrances();
}