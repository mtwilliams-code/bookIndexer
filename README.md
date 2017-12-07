# bookIndexer

Specifications
--------------
## Overview

Create a program to index the words in a book.

## Chapters, Paragraphs, Lines, and Words

For this program, a book is a text input file consisting of chapters, paragraphs, lines and words.

A word is a set of letters and symbols which contains no whitespace. For the purposes of indexing, case does not matter. Punctuation marks at the end or beginning of a word must be removed. Punctuation marks to be removed are: <tt>. ? ! , ; : - " ' _ ( )</tt>.

A line of words consists of words separated by any whitespace except a newline.

A paragraph is a series of lines with no intervening blank lines. A blank line is one without a word on it.

A chapter consists of a series of paragraphs prefixed by a paragraph containing one line which contains exactly two words. The first word will be "chapter" and the second will the number of the chapter, which could be either in arabic or roman numerals, as shown below. This line is not part of the chapter and should not be indexed.

```
CHAPTER 3
Chapter IV
```

## Output

Your program should produce an alphabetical listing of words and occurrences of each within the book in the format illustrated below.

```
apple 3:P4L3, 3:P5L7, 2:P1L12, 9:P5L5

bakery 4:P5L13

manitoba 8:P11L9, IV:P4L1
```

Each output line consists of the word and comma separated list of occurrences. Each occurrence is formatted as: chapter-number, colon, P, paragraph-number, L, and line-number.

## Sorting

Words should be ordered alphabetically. Occurrences should be ordered first by chapter appearance order, than by paragraph, and finally by line number. However, the publishers believe that the chapter(s) in which a word appears the most number of times must be the most important occurrences of the words and therefore occurrences in those chapters must appear first in the list. Also, only the first occurrences of a word within the same paragraph should be listed.

## Special Cases

A second input file will contain a list of words, one per line, which should be completely ignored. For example, the follow might be used.

```
is
the
of
and
```

A third input file will contain words which should be considered synonyms. Each synonym group will appear together on one line of the file. Occurrences of any synonym should be considered an occurrence of the first word in each synonym group. For example, the following might be given, so wherever light occurs it should be treated as bright.

```
bright light sunny
main central
begin start first
```

## Execution

Once your program is built, run it using the example command shown below.

```
index book.txt ignore.txt synonyms.txt > result.txt
```


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