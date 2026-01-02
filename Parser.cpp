#include "Parser.h"

#include "Emitter.h"
#include "Lexer.h"

void Parser::ParseProgram() {
   emitter_.Emit("#include <stdio.h>\n\n");
   emitter_.Emit("int main() {\n");
   emitter_.IncrementTabDepth();

   while (!CheckToken(END_OF_FILE)) {
      while (CheckToken(NEWLINE)) {
         NewLine();
      }

      Statement();
   }

   for (auto& label : labelsGotoed_) {
      if (!labelsDeclared_.contains(label)) {
         Abort("Attempting to GOTO to undeclared label: " + label);
      }
   }

   emitter_.DecrementTabDepth();
   emitter_.Emit("\n}");
}

bool Parser::CheckToken(TokenType kind) {
   return GetCurrentToken().GetType() == kind;
}

bool Parser::CheckTokenInList(std::vector<TokenType>&& kinds) {
   return std::any_of(kinds.begin(), kinds.end(),
      [this](TokenType kind) { return CheckToken(kind);});
}

bool Parser::CheckPeek(TokenType kind) {
   return GetPeekToken().GetType() == kind;
}

void Parser::ConsumeOrAbort(TokenType kind) {
   if (!CheckToken(kind)) {
      Abort(std::format("Expected '{}', but received '{}'.", str(kind), GetCurrentToken().GetText()));
   }
   NextToken();
}

void Parser::NextToken() {
   currentToken_ = peekToken_;
   peekToken_ = lexer_.GetToken();
}

void Parser::Abort(const std::string &message) {
   std::printf("PARSE ERROR: %s\n", message.c_str());
   std::printf("      LINE : %s\n", lexer_.GetCurrentLine().c_str());
   exit(1);
}

void Parser::Statement() {
   if (!CheckTokenInList({PRINT, IF, WHILE, LABEL, GOTO, LET,INPUT}))
      Abort(std::format("Expected a statement keyword, but found: {} ({})",
         GetCurrentToken().GetText(), str(GetCurrentToken().GetType())));

   switch (GetCurrentToken().GetType()) {
      case PRINT:  PrintStatement(); break;
      case IF:     IfStatement(); break;
      case WHILE:  WhileStatement(); break;
      case LABEL:  LabelStatement(); break;
      case GOTO:   GotoStatement(); break;
      case LET:    LetStatement(); break;
      case INPUT:  InputStatement(); break;
      default: std::unreachable();
   }
}

void Parser::PrintStatement() {
   ConsumeOrAbort(PRINT);
   emitter_.Emit("printf(");

   if (CheckToken(STRING)) {
      emitter_.Emit(std::format("\"{}\"", GetCurrentToken().GetText()));
      NextToken();
   } else {
      emitter_.Emit(R"("%.2f\n", )");
      Expression();
   }

   emitter_.Emit(");");
   NewLine();
}

void Parser::IfStatement() {
   ConsumeOrAbort(IF);
   emitter_.Emit("if (");
   Comparison();
   emitter_.Emit(")");
   ConsumeOrAbort(THEN);
   emitter_.Emit("{");
   emitter_.IncrementTabDepth();
   NewLine();
   //  Possible statement
   while (!CheckToken(ENDIF))
      Statement();

   ConsumeOrAbort(ENDIF);
   emitter_.DecrementTabDepth();
   emitter_.Emit("}");
   NewLine();
}

void Parser::WhileStatement() {
   ConsumeOrAbort(WHILE);
   emitter_.Emit("while (");
   Comparison();
   emitter_.Emit(") ");
   ConsumeOrAbort(REPEAT);
   emitter_.Emit("{");
   emitter_.IncrementTabDepth();
   NewLine();

   //  Possible statement
   while (!CheckToken(ENDWHILE))
      Statement();

   ConsumeOrAbort(ENDWHILE);
   emitter_.DecrementTabDepth();
   emitter_.Emit("}");
   NewLine();
}

void Parser::LabelStatement() {
   ConsumeOrAbort(LABEL);

   labelsDeclared_.insert(GetCurrentToken().GetText());
   emitter_.Emit(GetCurrentToken().GetText());

   ConsumeOrAbort(IDENT);
   NewLine();
}

void Parser::GotoStatement() {
   ConsumeOrAbort(GOTO);
   emitter_.Emit("goto ");

   labelsGotoed_.insert(GetCurrentToken().GetText());
   emitter_.Emit(GetCurrentToken().GetText());

   ConsumeOrAbort(IDENT);
   NewLine();
}

void Parser::LetStatement() {
   ConsumeOrAbort(LET);
   if (!symbols_.contains(GetCurrentToken().GetText())) {
      emitter_.Emit("float ");
   }

   symbols_.insert(GetCurrentToken().GetText());
   emitter_.Emit(GetCurrentToken().GetText());
   ConsumeOrAbort(IDENT);

   ConsumeOrAbort(EQ);
   emitter_.Emit(" = ");
   Expression();
   emitter_.Emit(";");
   NewLine();
}

void Parser::InputStatement() {
   ConsumeOrAbort(INPUT);

   // If not declared, then declare it.
   if (!symbols_.contains(GetCurrentToken().GetText())) {
      emitter_.Emit(std::format("float {};\n", GetCurrentToken().GetText()));
   }
   emitter_.Emit("scanf(\"%f\", ");

   symbols_.insert(GetCurrentToken().GetText());
   emitter_.Emit(std::format("&{});", GetCurrentToken().GetText()));
   ConsumeOrAbort(IDENT);
   NewLine();
}

void Parser::Comparison() {
   Expression();

   while (CheckTokenInList({EQEQ, NOTEQ, GT, GTEQ, LT, LTEQ})) {
      switch (GetCurrentToken().GetType()) {
         case EQEQ:  emitter_.Emit(" == "); break;
         case NOTEQ: emitter_.Emit(" != "); break;
         case GT:    emitter_.Emit(" > "); break;
         case GTEQ:  emitter_.Emit(" >= "); break;
         case LT:    emitter_.Emit(" < "); break;
         case LTEQ:  emitter_.Emit(" <= "); break;
         default: std::unreachable();
      }

      NextToken();
      Expression();
   }
}

void Parser::Expression() {
   emitter_.Emit("(");
   Term();

   while (CheckToken(MINUS) || CheckToken(PLUS)) {
      switch (GetCurrentToken().GetType()) {
         case MINUS: emitter_.Emit(" - "); break;
         case PLUS:  emitter_.Emit(" + "); break;
         default: std::unreachable();
      }

      NextToken();
      Term();
   }
   emitter_.Emit(")");
}

void Parser::Term() {
   Unary();

   while (CheckToken(SLASH) || CheckToken(ASTERISK)) {
      switch (GetCurrentToken().GetType()) {
         case SLASH :    emitter_.Emit("/"); break;
         case ASTERISK : emitter_.Emit("*"); break;
         default: std::unreachable();
      }

      NextToken();
      Unary();
   }
}

void Parser::Unary() {
   if (CheckToken(PLUS) || CheckToken(MINUS)) {
      switch (GetCurrentToken().GetType()) {
         case MINUS: emitter_.Emit(" - "); break;
         case PLUS : emitter_.Emit(" + "); break;
         default: std::unreachable();
      }
      NextToken();
   }

   Primary();
}

void Parser::Primary() {
   if (!(CheckToken(NUMBER) || CheckToken(IDENT)))
      Abort(std::format("Expected a number or identifier, but found: {}", GetCurrentToken().GetText()));

   if (CheckToken(IDENT)) {
      if (!symbols_.contains(GetCurrentToken().GetText())) {
         Abort("Referencing variable before assignment: " + GetCurrentToken().GetText());
      }
   }

   emitter_.Emit(GetCurrentToken().GetText());
   NextToken();
}

void Parser::NewLine() {
   ConsumeOrAbort(NEWLINE);
   emitter_.Emit("\n");
}
