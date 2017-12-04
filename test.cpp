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

    cout << endl;
    string test = "this is\n";
    string test2 = "this is a test\n";
    stringstream nextPara;
    nextPara << test;
    string firstWord, secondWord, thirdWord, secondLine, nextLine;
    stringstream para;
    para << nextPara.rdbuf();
    getline(nextPara, nextLine);
    para >> firstWord;
    para >> secondWord;
    para >> thirdWord;
    cout << "First word: " << firstWord << endl 
        << "Second word: " << secondWord << endl 
        << "Third word: " << thirdWord << endl;
    if (thirdWord == "\n") cout << "It's a newline!";
    if (thirdWord == "") cout << "It's empty!";

    nextPara.clear();
    para.clear();

    nextPara << test2;
    para << nextPara.rdbuf();
    getline(nextPara, nextLine);
    para >> firstWord;
    para >> secondWord;
    para >> thirdWord;
    cout << "First word: " << firstWord << endl 
        << "Second word: " << secondWord << endl 
        << "Third word: " << thirdWord << endl;

}