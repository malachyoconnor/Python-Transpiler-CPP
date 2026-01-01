cmake_minimum_required(VERSION 4.1)
project(Python_Transpiler_CPP)

set(CMAKE_CXX_STANDARD 26)

add_executable(Python_Transpiler_CPP
        main.cpp
        Lexer.h
        Lexer.cpp
        Trie.h
        Trie.cpp
        Token.h
        TokenType.h)
