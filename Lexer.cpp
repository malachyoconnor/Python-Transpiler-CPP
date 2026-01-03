#include "Lexer.h"

#include <iostream>
#include <ostream>
#include <utility>

const Trie KEYWORD_TRIE = Trie({
   str(PRINT),
   str(INPUT),
   str(IF),
   str(WHILE),
   str(FOR),
   str(IN),
   str(RANGE),
});

Lexer::Lexer(std::string source) : currentPos_(-1), currentIndentation_(0), source_(std::move(source)) {
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
   std::printf("ERROR: %s\n", msg.c_str());
}

static bool IsWhitespace(char ch) {
   return ch == '\r' || ch  == ' ' || ch == '\t';
}

bool Lexer::StartOfNewLine() {
   if (currentPos_ == 0) return true;
   if (currentPos_ >= source_.length() || currentPos_ < 0) return false;
   if (GetCurrentChar() == '\n') return false; // This is counted as the 'end' of the previous line

   return source_[currentPos_ - 1] == '\n';
}

void Lexer::SkipWhiteSpace() {
   while (IsWhitespace(GetCurrentChar())) {
      NextChar();
   }
}

int Lexer::CountAndConsumeTabs() {
   int count = 0;
   while (GetCurrentChar() == ' ' || GetCurrentChar() == '\t' || GetCurrentChar() == '\r') {
      if (GetCurrentChar() == '\t') count += 3;
      else if (GetCurrentChar() == ' ') count += 1;
      NextChar();
   }

   if (count%3 != 0) {
      Abort("Whitespace error! Not divisible by 3.");
   }

   return count;
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
   // If this is an empty line, who cares about the indentation.
   if (StartOfNewLine() && Peek() != '\n') {
      int whitespaceCounted = CountAndConsumeTabs();

      if (whitespaceCounted != currentIndentation_) {
         if (whitespaceCounted == currentIndentation_ + 3) {
            currentIndentation_ += 3;
            return Token("   ", ADD_INDENT);
         }
         if (whitespaceCounted == currentIndentation_ - 3) {
            currentIndentation_ -= 3;
            return Token("   ", REMOVE_INDENT);
         }
         Abort("Whitespace increased or decreased by 2 tabs at once!");
      }
   } else {
      SkipWhiteSpace();
   }

   SkipComment();

   std::optional<Token> result;
   switch (GetCurrentChar()) {
      case '\n': result = Token("\\n", NEWLINE);    break;
      case '+':  result = Token("+", PLUS);         break;
      case '-':  result = Token("-", MINUS);        break;
      case '*':  result = Token("*", ASTERISK);     break;
      case '/':  result = Token("/", SLASH);        break;
      case '(':  result = Token("(", OPEN_PAREN);   break;
      case ')':  result = Token("(", CLOSE_PAREN);  break;
      case ':':  result = Token(":", COLON);        break;
      case ',':  result = Token(",", COMMA);        break;
      case '!': {
         if (Peek() == '=') {
            result = Token("!=", NOTEQ);
            NextChar();
         } else {
            Abort("Expected != but found only !");
         }
         break;
      }
      case '=': {
         if (Peek() == '=') {
            result = Token("==", EQEQ);
            NextChar();
         } else {
            result = Token("=", EQ);
         }
         break;
      }
      case '>': {
         if (Peek() == '=') {
            result = Token(">=", GTEQ);
            NextChar();
         } else {
            result = Token(">", GT);
         }
         break;
      }
      case '<': {
         if (Peek() == '=') {
            result = Token("<=", LTEQ);
            NextChar();
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
         break;
      }
      case '\0': {
         // Stay on the \0 character until we've emitted enough END_BLOCK tokens
         while (currentIndentation_ > 0) {
            currentIndentation_ -= 3;
            return Token("-   ", REMOVE_INDENT);
         }
         result = Token("\0", END_OF_FILE);
         break;
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
         else if (IsAlpha(GetCurrentChar())) {
            int startIndex = currentPos_;
            NextChar();
            while (IsAlpha(GetCurrentChar()) && KEYWORD_TRIE.StartsWith(source_.substr(startIndex, currentPos_ - startIndex))) {
               NextChar();
            }

            if (KEYWORD_TRIE.Contains(source_.substr(startIndex, currentPos_ - startIndex))) {
               std::string keyword = source_.substr(startIndex, currentPos_ - startIndex);
               return Token(keyword, fromStr(keyword));
            }

            while (IsAlpha(GetCurrentChar())) {
               NextChar();
            }

            return Token(source_.substr(startIndex, currentPos_ - startIndex), IDENT);
         } else {
            Abort(std::format("Expected alphanumeric character, but found: '{}'", GetCurrentChar()));
         }
      }
   }

   NextChar();
   return result.value();
}

bool Lexer::Finished() {
   return currentPos_ >= source_.length();
}
