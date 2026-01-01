#ifndef PYTHON_TRANSPILER_CPP_TRIE_H
#define PYTHON_TRANSPILER_CPP_TRIE_H
#include <string>
#include <vector>

class Trie {
public:
   Trie() : children{}, endOfWord{false} {
   };
   Trie(const std::vector<std::string>& allWords);
   ~Trie();
   void Insert(const std::string &word);
   bool Contains(const std::string &word) const;
   bool StartsWith(const std::string &word) const;

private:
   Trie *children[26];
   bool endOfWord;
};


#endif //PYTHON_TRANSPILER_CPP_TRIE_H
