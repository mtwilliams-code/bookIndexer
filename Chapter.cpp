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

string Chapter::getIndexEntries(string word) const 
{
    string entries = "";
    for (auto P : paragraphs) 
    {
        entries += P.getIndexEntry(word);
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