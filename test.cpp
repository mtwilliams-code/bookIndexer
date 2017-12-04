#include <string>
#include <iostream>
#include <cctype>
#include <sstream>
#include <iostream>
#include <memory>
#include "Reader.hpp"
using namespace std;

int main() {

    cout << "Enter number of test case you would like to run: ";
    string num;
    cin >> num;

    string bookname, synname, ignorename;
    bookname = "./testcases/" + num + "_book.txt";
    synname = "./testcases/" + num + "_synonyms.txt";
    ignorename = "./testcases/" + num + "_ignore.txt";

    Reader reader_(bookname,synname,ignorename);
    unique_ptr<Book> book_ = reader_.read();
    book_->printSynonyms();
    book_->printIgnored();

}