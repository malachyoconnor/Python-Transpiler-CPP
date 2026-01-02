#include <filesystem>
#include <fstream>
#include <iostream>

#include "Emitter.h"
#include "Lexer.h"
#include "Parser.h"

int main() {
   std::ifstream fileStream {"../exampleScripts/fib_program.txt"};

   if (!fileStream.is_open()) {
      std::printf("ERROR: Could not open file!");
      return 1;
   }
   std::string sourceString {};

   std::string line {};
   while (std::getline(fileStream, line)) {
      sourceString += line + "\n";
   }
   sourceString += '\0';

   Lexer lexer {sourceString};
   Emitter emitter {"../out.c"};
   Parser parser {lexer, emitter};

   parser.ParseProgram();
   emitter.WriteFile();

   printf("Parsing completed!\n");
}
