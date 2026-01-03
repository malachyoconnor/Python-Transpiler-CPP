#ifndef PYTHON_TRANSPILER_CPP_TOKENTYPE_H
#define PYTHON_TRANSPILER_CPP_TOKENTYPE_H
#include <format>
#include <map>
#include <stdexcept>
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
   FOR,
   IN,
   RANGE,
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
   COMMA
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
      case FOR:           return "for";
      case IN:            return "in";
      case RANGE:         return "range";
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
      case COMMA:         return "COMMA";
   }
   std::unreachable();
}

const std::map<const std::string, TokenType> tokenTypeMap = {
   {"END_OF_FILE", END_OF_FILE},
   {"NEWLINE", NEWLINE},
   {"NUMBER", NUMBER},
   {"IDENT", IDENT},
   {"STRING", STRING},
   {"print", PRINT},
   {"input", INPUT},
   {"if", IF},
   {"while", WHILE},
   {"for", FOR},
   {"in", IN},
   {"range", RANGE},
   {"EQ", EQ},
   {"PLUS", PLUS},
   {"MINUS", MINUS},
   {"ASTERISK", ASTERISK},
   {"SLASH", SLASH},
   {"EQEQ", EQEQ},
   {"NOTEQ", NOTEQ},
   {"LT", LT},
   {"LTEQ", LTEQ},
   {"GT", GT},
   {"GTEQ", GTEQ},
   {"ADD_INDENT", ADD_INDENT},
   {"REMOVE_INDENT", REMOVE_INDENT},
   {"OPEN_PAREN", OPEN_PAREN},
   {"CLOSE_PAREN", CLOSE_PAREN},
   {"COLON", COLON},
   {"COMMA", COMMA},
};

inline TokenType fromStr(const std::string& tokenString) {
   if (!tokenTypeMap.contains(tokenString)) {
      throw std::runtime_error(std::format("Token type does not exist: {}", tokenString));
   }
   return tokenTypeMap.at(tokenString);
}

#endif //PYTHON_TRANSPILER_CPP_TOKENTYPE_H
