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
   LABEL,
   GOTO,
   PRINT,
   INPUT,
   LET,
   IF,
   THEN,
   ENDIF,
   WHILE,
   REPEAT,
   ENDWHILE,
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
};

inline std::string str(const TokenType tokenType) {
   switch (tokenType) {
      case END_OF_FILE: return "END_OF_FILE";
      case NEWLINE: return "NEWLINE";
      case NUMBER: return "NUMBER";
      case IDENT: return "IDENT";
      case STRING: return "STRING";
      case LABEL: return "LABEL";
      case GOTO: return "GOTO";
      case PRINT: return "PRINT";
      case INPUT: return "INPUT";
      case LET: return "LET";
      case IF: return "IF";
      case THEN: return "THEN";
      case ENDIF: return "ENDIF";
      case WHILE: return "WHILE";
      case REPEAT: return "REPEAT";
      case ENDWHILE: return "ENDWHILE";
      case EQ: return "EQ";
      case PLUS: return "PLUS";
      case MINUS: return "MINUS";
      case ASTERISK: return "ASTERISK";
      case SLASH: return "SLASH";
      case EQEQ: return "EQEQ";
      case NOTEQ: return "NOTEQ";
      case LT: return "LT";
      case LTEQ: return "LTEQ";
      case GT: return "GT";
      case GTEQ: return "GTEQ";

      default: std::unreachable();
   }
}

#endif //PYTHON_TRANSPILER_CPP_TOKENTYPE_H
