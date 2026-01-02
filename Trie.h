#ifndef PYTHON_TRANSPILER_CPP_TRIE_H
#define PYTHON_TRANSPILER_CPP_TRIE_H
#include <memory>
#include <string>
#include <vector>

class Trie {
public:
   Trie() : children{}, endOfWord{false} {
   };
   Trie(const std::vector<std::string>& allWords);
   void Insert(std::string_view word);
   bool Contains(std::string_view word) const;
   bool StartsWith(std::string_view word) const;

private:
   std::unique_ptr<Trie> children[26];
   bool endOfWord;
};


#endif //PYTHON_TRANSPILER_CPP_TRIE_H
