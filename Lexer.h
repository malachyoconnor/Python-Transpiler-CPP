#ifndef PYTHON_TRANSPILER_CPP_LEXER_H
#define PYTHON_TRANSPILER_CPP_LEXER_H
#include <string>
#include "Token.h"
#include "Trie.h"

class Lexer {
public:
   Lexer(std::string source);

   // Process the next character.
   void NextChar();

   [[nodiscard]]
   std::string GetCurrentLine() const;

   [[nodiscard]]
   char Peek() const;

   Token GetToken();
   bool Finished();

private:
   int currentPos_;
   int currentIndentation_;
   const std::string source_;

   // Invalid token found, print error message and exit.
   void Abort(std::string msg);
   bool StartOfNewLine();
   void SkipWhiteSpace();
   int CountAndConsumeTabs();
   void SkipComment();

   [[nodiscard]]
   char GetCurrentChar() const;
};


#endif //PYTHON_TRANSPILER_CPP_LEXER_H
