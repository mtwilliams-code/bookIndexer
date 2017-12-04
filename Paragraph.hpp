#include <map>
#include <iterator>
#include <string>
#ifndef PARAGRAPH
#define PARAGRAPH

class Paragraph{
    private:
        std::multimap <std::string, int> occurances;
        std::multimap <std::string, std::string> location;
    public:
        Paragraph();
        ~Paragraph();
        std::string addOccurance(std::string word, std::string location); //will check if word is already in multimap and then either add it and the location or just increment occurances

};

#endif