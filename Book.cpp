#include "Book.hpp"

using namespace std;

Book::Book(map<string, string> &S, set<string> &I) : synonyms(S), ignore(I)
{
}

Book::~Book()
{
    chapters.clear();
}

void Book::addChapter(Chapter C)
{
    chapters.push_back(C);
}

void Book::addChapter(string title)
{
    chapters.emplace_back(title);
}

void Book::addParagraph(unique_ptr<stringstream> P)
{
    if (!chapters.empty())
        chapters.back().addParagraph(move(P));
}

void Book::addWord(string word)
{
    allWords.insert(word);
}

void Book::removeWord(string word)
{
    allWords.erase(word);
}

void Book::printSynonyms() const
{
    cout << "\nSynonyms:\n";
    for (const auto &synonym : synonyms)
    {
        cout << synonym.first << " " << synonym.second << endl;
    }
}

void Book::printIgnored() const
{
    cout << "\nIgnored words:\n";
    for (const auto &ignored : ignore)
    {
        cout << ignored << endl;
    }
}

void Book::printChapters() const
{
    cout << "\nThis Book is comprised of " << chapters.size() << " chapters:" << endl;
    for (const auto &chap : chapters)
    {
        cout << "Chapter " << chap.getChapterTitle() << endl;
    }
}

void Book::printBook() const
{
    for (const auto &C : chapters)
    {
        C.printChapter();
    }
}

void Book::printIndex() const
{
    
}

void Book::printAllWords() const
{
    cout << "List of all words in book: ";
    for (const auto& word : allWords)
    {
        cout << word << ", ";
    }
}