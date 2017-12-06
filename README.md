# bookIndexer

Specifications
--------------

You can find specifications in the [spec.html](https://htmlpreview.github.com?https://github.com/remasus/bookIndexer/spec.html) file included in this repo.


Design
------

The test.cpp file contains the main function, which accepts command line arguments of either a number or the names of the test case files.
It creates a Reader object with these names, which is in charge of all input. The Reader has a read() function which will read the text files and return a Book object consisting of Chapters which hold Paragraphs. 

Interface of Book:
------------------
```c++
Book(std::map<std::string, std::string> &S, std::set<std::string> &I);
~Book();
void addChapter(Chapter C);
void addChapter(std::string title);
void printSynonyms() const;
void printIgnored() const;
void printChapters() const;
void printBook() const;
void addParagraph(std::unique_ptr<std::stringstream> P);
void addWord(std::string word);
void removeWord(std::string word);
void printIndex() const;
void printAllWords() const;
Chapter *getChapter(int N) const;
int getChapterCount() const;
```

I believe these are all fairly self explanatory in what they do. 