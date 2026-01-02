#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include "Lexer.h"

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

   while (!lexer.Finished()) {
      Token tok = lexer.GetToken();

      std::printf("%s(%s)\n", str(tok.GetType()).c_str(), tok.GetText().c_str());
   }

}
