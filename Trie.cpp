#include "Trie.h"

#include <stdexcept>

Trie::Trie(const std::vector<std::string> &allWords) : children{}, endOfWord(false) {
   for (const auto &word: allWords) {
      Insert(word);
   }
}

void Trie::Insert(const std::string_view word) {
   if (word.empty()) {
      endOfWord = true;
      return;
   }
   const char lowerCase = static_cast<char>(tolower(word[0])) - 'a';

   if (!(lowerCase >= 0 && lowerCase < 26))
      throw std::invalid_argument("Invalid character - this trie requires a-z");

   if (children[lowerCase] == nullptr) {
      children[lowerCase] = std::make_unique<Trie>();
   }
   children[lowerCase]->Insert(word.substr(1, word.length() - 1));
}

bool Trie::Contains(std::string_view word) const {
   if (word.empty()) {
      return endOfWord;
   }
   const char lowerCase = static_cast<char>(tolower(word[0])) - 'a';

   if (!(lowerCase >= 0 && lowerCase < 26))
      throw std::invalid_argument("Invalid character - this trie requires a-z");

   if (children[lowerCase] == nullptr) {
      return false;
   }
   return children[lowerCase]->Contains(word.substr(1, word.length() - 1));
}

bool Trie::StartsWith(std::string_view word) const {
   if (word.empty()) {
      return true;
   }
   const char lowerCase = static_cast<char>(tolower(word[0])) - 'a';

   if (!(lowerCase >= 0 && lowerCase < 26))
      throw std::invalid_argument("Invalid character - this trie requires a-z");

   if (children[lowerCase] == nullptr) {
      return false;
   }
   return children[lowerCase]->StartsWith(word.substr(1, word.length() - 1));

}
