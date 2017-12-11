#include "Chapter.hpp"

using namespace std;

Chapter::~Chapter()
{
}

void Chapter::addParagraph(unique_ptr<stringstream> P)
{
    paragraphs.emplace_back(move(P), ++paragraphNumber, chapterTitle);
}

void Chapter::printChapter() const
{
    cout << "\nChapter " << chapterTitle << ", " << paragraphNumber << " paragraphs" << endl;
    cout << "--------------------------------------" << endl;
    for (const auto &P : paragraphs)
    {
        P.printParagraph();
    }
}

list<string> Chapter::getIndexEntries(string word) const 
{
    list<string> entries;
    for (auto P : paragraphs) 
    {
        if (P.getIndexEntry(word) != "")
            entries.push_back(P.getIndexEntry(word));
    }
    return entries;
}

int Chapter::getOccurrances(string word) const
{
    int totalOccurrences = 0;
    for (auto P : paragraphs) 
    {
        totalOccurrences += P.getWordOccuranceCount(word);
    }
    return totalOccurrences;
}