#ifndef PYTHON_TRANSPILER_CPP_LEXER_H
#define PYTHON_TRANSPILER_CPP_LEXER_H
#include <string>
#include "Token.h"
#include "Trie.h"

class Lexer {
public:
   Lexer(std::string &source);

   // Process the next character.
   void NextChar();
   char Peek();

   // Invalid token found, print error message and exit.
   void Abort(std::string msg);

   // Skip whitespace except newlines, which we will use to indicate the end of a statement.
   void SkipWhitespace();
   void SkipComment();

   Token GetToken();

private:
   char GetCurrentChar();

   int currentPos_;
   std::string source_;
   Trie keyWordTrie_;
};


#endif //PYTHON_TRANSPILER_CPP_LEXER_H
