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

   [[nodiscard]]
   char Peek() const;

   Token GetToken();
   bool Finished();

private:
   // Invalid token found, print error message and exit.
   void Abort(std::string msg);
   void SkipWhitespace();
   void SkipComment();

   [[nodiscard]]
   char GetCurrentChar() const;

   int currentPos_;
   std::string source_;
};


#endif //PYTHON_TRANSPILER_CPP_LEXER_H
