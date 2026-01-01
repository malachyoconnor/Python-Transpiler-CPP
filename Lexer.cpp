#include "Lexer.h"

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

Lexer::Lexer(std::string &source) {
}

void Lexer::NextChar() {
}

char Lexer::Peek() {
}

void Lexer::Abort(std::string msg) {
}

void Lexer::SkipWhitespace() {
}

void Lexer::SkipComment() {
}

Token Lexer::GetToken() {
}

char Lexer::GetCurrentChar() {
}
