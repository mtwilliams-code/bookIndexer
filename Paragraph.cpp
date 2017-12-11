#include "Paragraph.hpp"

using namespace std;

void Paragraph::addWord(std::string word, int paraNum, int lineNum)
{
    occurrences[word]++;
    string loc = chapterTitle + ":P" + to_string(paraNum) + "L" + to_string(lineNum);
    location.insert(pair<string, string>(word, loc));
    //cout << "Adding word \"" << word << "\" to paragraph at location " << loc << " occurance " << occurrences[word] << endl; //debug
}

Paragraph::Paragraph(std::unique_ptr<std::stringstream> S, int paraNumber, string title) : chapterTitle(title), paragraphNumber(paraNumber)
{
    text = move(S);
    int loc = text->tellg();
    int lineNumber = 0;
    string word, line = "notempty";
    while (!line.empty() )
    {
        stringstream lineStream;
        std::getline(*text, line);
        lineNumber++;
        lineStream.str(line);
        while ( lineStream >> word ) {
            addWord(word, paragraphNumber, lineNumber);
        }
    }
    text->seekg(loc);
}

Paragraph::Paragraph(const Paragraph &P)
{
    this->occurrences = P.occurrences;
    this->location = P.location;
    this->text = make_unique<stringstream>();
    *(this->text) << P.text->str();
}

Paragraph::~Paragraph()
{
    occurrences.clear();
    location.clear();
}

void Paragraph::printParagraph() const
{
    cout << "P" << paragraphNumber << ": " << text->str() << endl;
}

string Paragraph::getIndexEntry(string word) const
{
    map<string, string>::const_iterator itr = location.find(word);
    if ( itr != location.end() ) {
        return (itr->second);
    }
    return "";
}

int Paragraph::getWordOccuranceCount(string S) const
{
    map<string, int>::const_iterator itr = occurrences.find(S);
    if ( itr != occurrences.end() ) {
        return itr->second;
    }
    return 0;   
}
