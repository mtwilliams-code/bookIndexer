#include "Paragraph.hpp"

using namespace std;

void Paragraph::addWord(std::string word, int paraNum, int lineNum)
{
    occurances[word]++;
    string loc = chapterTitle + ":P" + to_string(paraNum) + "L" + to_string(lineNum);
    location.insert(pair<string, string>(word, loc));
}

Paragraph::Paragraph(std::unique_ptr<std::stringstream> S, int paraNumber, string title) : chapterTitle(title), paragraphNumber(paraNumber)
{
    text = move(S);
}

Paragraph::Paragraph(const Paragraph &P) 
{
        this->occurances = P.occurances;
        this->location = P.location;
        this->text = make_unique<stringstream>();
        *(this->text) << P.text->rdbuf();

}

Paragraph::~Paragraph()
{
    occurances.clear();
    location.clear();

}

void Paragraph::printParagraph() const {
    cout << endl << text->rdbuf() << endl;
}