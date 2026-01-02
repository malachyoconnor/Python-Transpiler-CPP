#ifndef PYTHON_TRANSPILER_CPP_EMITTER_H
#define PYTHON_TRANSPILER_CPP_EMITTER_H
#include <filesystem>
#include <utility>


class Emitter {
public:
   Emitter(std::filesystem::path pathToOutputFile) : pathToOutputFile_(std::move(pathToOutputFile)), tabDepth_(0) {}

   void NewLine();
   void Emit(const std::string& code);
   void IncrementTabDepth();
   void DecrementTabDepth();
   void WriteFile();

private:
   std::filesystem::path pathToOutputFile_;
   std::string code_;
   int tabDepth_;

};

#endif //PYTHON_TRANSPILER_CPP_EMITTER_H