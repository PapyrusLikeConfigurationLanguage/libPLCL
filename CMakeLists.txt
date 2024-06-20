cmake_minimum_required(VERSION 3.28)
project(PapyrusLikeConfigurationLanguage)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(PapyrusLikeConfigurationLanguage STATIC
        src/Lexer.cpp
        src/Config.cpp
        src/Template.cpp)
