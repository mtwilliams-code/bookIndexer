#include "Chapter.hpp"

using namespace std;

Chapter::~Chapter() {
}

void Chapter::addParagraph(unique_ptr<stringstream> P) {
    paragraphs.emplace_back(move(P),++paragraphNumber,chapterTitle);
}

void Chapter::printChapter() const {
    cout << "\nChapter " << chapterTitle << ", " << paragraphNumber << " paragraphs" << endl;
    cout << "--------------------------------------"<<endl;
    for (const auto& P : paragraphs)
    {
        P.printParagraph();
    }
}