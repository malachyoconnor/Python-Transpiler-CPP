#include "Trie.h"

#include <stdexcept>

Trie::Trie(const std::vector<std::string> &allWords) : children{}, endOfWord(false) {
   for (const auto &word: allWords) {
      Insert(word);
   }
}

Trie::~Trie() {
   for (auto child: children) {
      delete child;
   }
}

void Trie::Insert(const std::string &word) {
   if (word.empty()) return;
   Trie *node = nullptr;

   for (const char &c: word) {
      auto lowerCase = static_cast<char>(tolower(c)) - 'a';
      if (!(lowerCase >= 0 && lowerCase < 26))
         throw std::invalid_argument("Invalid character - this trie requires a-z");

      if (children[lowerCase] == nullptr) {
         children[lowerCase] = new Trie();
      }
      node = children[lowerCase];
   }

   if (!node) return;
   node->endOfWord = true;
}

bool Trie::Contains(const std::string &word) const {
   Trie *node = nullptr;

   for (const char &c: word) {
      auto lowerCase = static_cast<char>(tolower(c)) - 'a';
      if (!(lowerCase >= 0 && lowerCase < 26))
         throw std::invalid_argument("Invalid character - this trie requires a-z");

      if (children[lowerCase] == nullptr) {
         return false;
      }

      node = children[lowerCase];
   }

   if (!node) return false;
   return node->endOfWord;
}

bool Trie::StartsWith(const std::string &word) const {
   Trie *node = nullptr;

   for (const char &c: word) {
      auto lowerCase = static_cast<char>(tolower(c)) - 'a';
      if (!(lowerCase >= 0 && lowerCase < 26))
         throw std::invalid_argument("Invalid character - this trie requires a-z");

      if (children[lowerCase] == nullptr) {
         return false;
      }

      node = children[lowerCase];
   }

   if (!node) return false;
   return true;
}
