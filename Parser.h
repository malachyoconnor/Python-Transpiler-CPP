#ifndef PYTHON_TRANSPILER_CPP_PARSER_H
#define PYTHON_TRANSPILER_CPP_PARSER_H
#include <optional>
#include <set>
#include <string>
#include <vector>

#include "Token.h"
#include "TokenType.h"

class Lexer;
class Emitter;

/*   GRAMMAR:
     program ::= {statement}
     statement ::= "print" OPEN_PAREN (expression | string) CLOSE_PAREN nl
         | "if" comparison COLON nl ADD_INDENT {statement | nl} REMOVE_INDENT
         | "while" comparison COLON nl ADD_INDENT {statement} {nl} REMOVE_INDENT
         | IDENT "=" (expression | input()) nl
         | "INPUT" OPEN_PAREN ident CLOSE_PARENT nl
     comparison ::= expression (("==" | "!=" | ">" | ">=" | "<" | "<=") expression)+
     expression ::= term {( "-" | "+" ) term}
     term ::= unary {( "/" | "*" ) unary}
     unary ::= ["+" | "-"] primary
     primary ::= number | ident
     nl ::= '\n'+
*/

class Parser {
public:

   Parser(Lexer& lexer, Emitter& emitter) : lexer_(lexer), emitter_(emitter) {
      // Called twice to initialise current and peek.
      NextToken();
      NextToken();
   };

   void ParseProgram();

   [[nodiscard]]
   const Token& GetCurrentToken() {
      if (!currentToken_.has_value()) Abort("Expected a value in current token!");
      return currentToken_.value();
   }

   [[nodiscard]]
   const Token& GetPeekToken() {
      if (!peekToken_.has_value()) Abort("Expected a value in current token!");
      return peekToken_.value();
   }

private:
   std::optional<Token> currentToken_;
   std::optional<Token> peekToken_;

   Lexer& lexer_;
   Emitter& emitter_;

   std::set<std::string> symbols_;
   std::set<std::string> labelsDeclared_;
   std::set<std::string> labelsGotoed_;

   bool CheckToken(TokenType kind);
   bool CheckTokenInList(std::vector<TokenType>&& kinds);
   bool CheckPeek(TokenType kind);
   void ConsumeOrAbort(TokenType kind);
   void NextToken();
   void Abort(const std::string &message);
   void Statement();
   void PrintStatement();
   void IfStatement();
   void WhileStatement();
   void ReassignmentStatement();
   void Comparison();
   void Expression();
   void Term();
   void Unary();
   void Primary();
   void NewLine();
};


#endif //PYTHON_TRANSPILER_CPP_PARSER_H