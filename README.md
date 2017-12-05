# bookIndexer

Specifications
--------------

You can find specifications in the [spec.html](https://htmlpreview.github.com?https://github.com/remasus/bookIndexer/spec.html) file included in this repo.


Design
------

The test.cpp file contains the main function, which accepts command line arguments of either a number or the names of the test case files.
It creates a Reader object with these names, which is in charge of all input. The Reader has a read() function which will read the text files and return a Book object consisting of Chapters which hold Paragraphs. 
Then, an Indexer object is created, which accepts the Book and creates an index based off of it. 