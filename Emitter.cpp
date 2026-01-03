#include "Emitter.h"
#include <fstream>

void Emitter::NewLine() {
   code_ += '\n';
}

std::string Emitter::ReadAndClearBuffer() {
   std::string current = code_;
   code_ = "";
   return current;
}

void Emitter::Emit(const std::string &code) {
   if (!code_.empty() && code_.back() == '\n') {
      for (int i = 0; i < tabDepth_; ++i) code_ += "   ";
   }

   code_ += code;
}

void Emitter::IncrementTabDepth() {
   ++tabDepth_;
}

void Emitter::DecrementTabDepth() {
   --tabDepth_;
   if (tabDepth_ < 0) {
      printf("Tab depth less than 0!");
      exit(1);
   }
}

void Emitter::WriteFile() {
   std::ofstream outputStream {pathToOutputFile_};

   if (!outputStream.is_open()) {
      printf("Couldn't open output file: %s", pathToOutputFile_.c_str());
      exit(1);
   }

   outputStream << code_;
   outputStream.flush();
   outputStream.close();
}
