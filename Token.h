#ifndef PYTHON_TRANSPILER_CPP_TOKEN_H
#define PYTHON_TRANSPILER_CPP_TOKEN_H
#include <string>
#include "TokenType.h"

class Token {
public:
   Token(std::string text, TokenType type) : text_(text), type_(type) {
   }

   [[nodiscard]]
   const std::string &GetText() const {
      return text_;
   }


   [[nodiscard]]
   const TokenType &GetType() const {
      return type_;
   }

private:
   std::string text_;
   TokenType type_;
};

#endif //PYTHON_TRANSPILER_CPP_TOKEN_H
