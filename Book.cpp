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
    for (const auto& word : allWords)
    {
        cout << word << " ";
        list<string> temp1, temp2, temp3;
        int max = 0;
        for(const auto& C: chapters)
        {
            if (C.getOccurrances(word) > max)
            {
                temp1 = C.getIndexEntries(word);
                temp3 = temp2;
                max = C.getOccurrances(word);
            }
            else if (C.getOccurrances(word) > 0)
            {
                temp3.splice(temp3.end(),C.getIndexEntries(word));
            }
            if (C.getOccurrances(word) > 0)
            {
                temp2.splice(temp2.end(),C.getIndexEntries(word));
            }
        }
        for (auto entry : temp1)
            cout << entry << ", ";
        for (auto entry : temp3)
        {
            if (entry != *(--temp3.end()))
                cout << entry << ", ";
            else cout << entry << " ";
        }
        if (word != *(--allWords.end()))
            cout << "\n";
    }

}    

void Book::printAllWords() const
{
    cout << "List of all words in book: ";
    for (const auto& word : allWords)
    {
        cout << word << ", ";
    }
}

void Book::printOccurrances() const
{
    for (const auto& word : allWords)
    {
        cout << word << " ";
        for (const auto& C : chapters)
        {
            cout << C.getOccurrances(word) << " ";
        }
        cout << endl;
    }
}