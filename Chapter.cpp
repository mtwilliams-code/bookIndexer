#include "Chapter.hpp"

using namespace std;

Chapter::~Chapter() {
}

void Chapter::addParagraph(unique_ptr<stringstream> P) {
    paragraphs.emplace_back(move(P),++paragraphNumber,chapterTitle);
}

void Chapter::printChapter() const {
    cout << "Chapter " << chapterTitle << endl;
    cout << "--------------------------------------"<<endl<<endl;
    for (const auto& P : paragraphs)
    {
        P.printParagraph();
    }
}