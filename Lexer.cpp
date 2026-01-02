#include "Lexer.h"

#include <iostream>
#include <ostream>
#include <utility>

const Trie KEYWORD_TRIE = Trie({
   str(LABEL),
   str(GOTO),
   str(PRINT),
   str(INPUT),
   str(LET),
   str(IF),
   str(THEN),
   str(ENDIF),
   str(WHILE),
   str(REPEAT),
   str(ENDWHILE)
});

Lexer::Lexer(std::string source) : currentPos_(-1), source_(std::move(source)) {
   NextChar();
}

void Lexer::NextChar() {
   ++currentPos_;
}

std::string Lexer::GetCurrentLine() const {
   int i = currentPos_;
   while (i > 0 && source_[i] != '\n') {
      --i;
   }
   if (source_[i] == '\n') ++i;

   std::string resultString {};
   for (; i < source_.size() && source_[i] != '\n'; i++) {
      resultString += source_[i];
   }

   return resultString;
}

char Lexer::GetCurrentChar() const {
   if (currentPos_ >= source_.length()) {
      return '\0';
   }
   return source_[currentPos_];
}

char Lexer::Peek() const {
   if (currentPos_ + 1 >= source_.length()) {
      return '\0';
   }
   return source_[currentPos_ + 1];
}

void Lexer::Abort(std::string msg) {
   std::printf("ERROR: %s", msg.c_str());
}

void Lexer::SkipWhitespace() {
   while (GetCurrentChar() == ' ' || GetCurrentChar() == '\t' || GetCurrentChar() == '\r') {
      NextChar();
   }
}

void Lexer::SkipComment() {
   if (GetCurrentChar() == '#') {
      while (GetCurrentChar() != '\n') {
         NextChar();
      }
   }
}

bool IsDigit(char ch) {
   return ch >= '0' && ch <= '9';
}

bool IsAlpha(char ch) {
   return ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z';
}

Token Lexer::GetToken() {
   SkipWhitespace();
   SkipComment();

   std::optional<Token> result;
   switch (GetCurrentChar()) {
      case '\0': result = Token("\0", END_OF_FILE); break;
      case '\n': result = Token("\\n", NEWLINE);     break;
      case '+': result = Token("+", PLUS);          break;
      case '-': result = Token("-", MINUS);         break;
      case '*': result = Token("*", ASTERISK);      break;
      case '/': result = Token("/", SLASH);         break;
      case '!': {
         if (Peek() == '=') {
            result = Token("!=", NOTEQ);
         } else {
            Abort("Expected != but found only !");
         }
         break;
      }
      case '=': {
         if (Peek() == '=') {
            result = Token("==", EQEQ);
         } else {
            result = Token("=", EQ);
         }
         break;
      }
      case '>': {
         if (Peek() == '=') {
            result = Token(">=", GTEQ);
         } else {
            result = Token(">", GT);
         }
         break;
      }
      case '<': {
         if (Peek() == '=') {
            result = Token("<=", LTEQ);
         } else {
            result = Token("<", LT);
         }
         break;
      }
      case '"': {
         NextChar();
         int startIndex = currentPos_;
         while (GetCurrentChar() != '"' && GetCurrentChar() != '\0' ) NextChar();
         result = Token(source_.substr(startIndex, currentPos_ - startIndex), STRING);
      }
      default: {
         if (IsDigit(GetCurrentChar())) {
            int startIndex = currentPos_;
            bool fullStopPresent = false;
            for (char ch = GetCurrentChar(); IsDigit(GetCurrentChar()); NextChar()) {
               if (ch == '.' && fullStopPresent) Abort("Encountered more than one '.' in a number");
               else if (ch == '.') fullStopPresent = true;
            }

            return Token(source_.substr(startIndex, currentPos_ - startIndex), NUMBER);
         }
         if (IsAlpha(GetCurrentChar())) {
            int startIndex = currentPos_;
            NextChar();
            while (IsAlpha(GetCurrentChar()) && KEYWORD_TRIE.StartsWith(source_.substr(startIndex, currentPos_ - startIndex))) {
               NextChar();
            }

            if (KEYWORD_TRIE.Contains(source_.substr(startIndex, currentPos_ - startIndex))) {
               std::string keyword = source_.substr(startIndex, currentPos_ - startIndex);
               if (keyword == str(LABEL))    return Token("LABEL", LABEL);
               if (keyword == str(GOTO))     return Token("GOTO", GOTO);
               if (keyword == str(PRINT))    return Token("PRINT", PRINT);
               if (keyword == str(INPUT))    return Token("INPUT", INPUT);
               if (keyword == str(LET))      return Token("LET", LET);
               if (keyword == str(IF))       return Token("IF", IF);
               if (keyword == str(THEN))     return Token("THEN", THEN);
               if (keyword == str(ENDIF))    return Token("ENDIF", ENDIF);
               if (keyword == str(WHILE))    return Token("WHILE", WHILE);
               if (keyword == str(REPEAT))   return Token("REPEAT", REPEAT);
               if (keyword == str(ENDWHILE)) return Token("ENDWHILE", ENDWHILE);
               Abort(std::format("Unknown keyword: {}", keyword));
            }

            while (IsAlpha(GetCurrentChar())) {
               NextChar();
            }

            return Token(source_.substr(startIndex, currentPos_ - startIndex), IDENT);
         }
      }
   }

   NextChar();
   return result.value();
}

bool Lexer::Finished() {
   return currentPos_ >= source_.length();
}
