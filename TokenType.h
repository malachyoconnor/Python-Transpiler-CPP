#ifndef PYTHON_TRANSPILER_CPP_TOKENTYPE_H
#define PYTHON_TRANSPILER_CPP_TOKENTYPE_H
#include <utility>

enum TokenType {
   END_OF_FILE,
   NEWLINE,
   NUMBER,
   IDENT,
   STRING,
   // Keywords
   PRINT,
   INPUT,
   IF,
   WHILE,
   ADD_INDENT,
   REMOVE_INDENT,
   // Operators.
   EQ,
   PLUS,
   MINUS,
   ASTERISK,
   SLASH,
   EQEQ,
   NOTEQ,
   LT,
   LTEQ,
   GT,
   GTEQ,
   OPEN_PAREN,
   CLOSE_PAREN,
   COLON,
};

inline std::string str(const TokenType tokenType) {
   switch (tokenType) {
      case END_OF_FILE:   return "END_OF_FILE";
      case NEWLINE:       return "NEWLINE";
      case NUMBER:        return "NUMBER";
      case IDENT:         return "IDENT";
      case STRING:        return "STRING";
      case PRINT:         return "print";
      case INPUT:         return "input";
      case IF:            return "if";
      case WHILE:         return "while";
      case EQ:            return "EQ";
      case PLUS:          return "PLUS";
      case MINUS:         return "MINUS";
      case ASTERISK:      return "ASTERISK";
      case SLASH:         return "SLASH";
      case EQEQ:          return "EQEQ";
      case NOTEQ:         return "NOTEQ";
      case LT:            return "LT";
      case LTEQ:          return "LTEQ";
      case GT:            return "GT";
      case GTEQ:          return "GTEQ";
      case ADD_INDENT:    return "ADD_INDENT";
      case REMOVE_INDENT: return "REMOVE_INDENT";
      case OPEN_PAREN:    return "OPEN_PAREN";
      case CLOSE_PAREN:   return "CLOSE_PAREN";
      case COLON:         return "COLON";
   }
   std::unreachable();
}

#endif //PYTHON_TRANSPILER_CPP_TOKENTYPE_H
