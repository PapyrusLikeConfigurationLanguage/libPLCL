// SPDX-License-Identifier: Apache-2.0

/// @file
/// @brief Turning input into tokens
/// @attention This file is not meant to be included by the end user.
///
/// @class PLCL::Lexer
/// @brief A class that turns input into tokens
/// @details The lexer is responsible for turning the input into tokens that the parser can understand.
/// It does this by reading the input character by character and determining what kind of token it is.
///
/// @enum PLCL::Lexer::TokenType
/// @brief The different types of tokens that the lexer can produce
///
/// @struct PLCL::Lexer::Token
/// @brief A struct that represents a token produced by the lexer
///
/// @var PLCL::Lexer::Token::type 
/// @brief The type of the token
///
/// @var PLCL::Lexer::Token::value
/// @brief The value of the token
/// @details The value of the token is the actual string that was read from the input
/// 
/// @var PLCL::Lexer::Token::line 
/// @brief The line number where the token was found
///
/// @var PLCL::Lexer::Token::column
/// @brief The column number where the token was found
///
/// @fn PLCL::Lexer::Lexer(std::string input)
/// @brief Constructs a lexer with the given input
///
/// @fn std::vector<Token> PLCL::Lexer::lex()
/// @brief Turns the input into tokens
/// @return A vector of tokens 
///
/// @fn std::string PLCL::Lexer::tokenTypeToString(TokenType type)
/// @brief Converts a token type to a string 
/// @param type The token type to convert 
/// @return The string representation of the token type

#pragma once
#include <vector>
#include <string>

namespace PLCL {
    class Lexer {
    public:
        enum class TokenType {
            EndOfFile,
            Equals,
            Name,
            StringLiteral,
            NumberLiteral,
            BooleanLiteral,
            Import,
            String,
            Integer,
            Float,
            Boolean,

            ConfigName,
            ConfigElement,
            EndConfigElement,
            ConfigListElement,
            EndConfigListElement,
            ConfigList,
            EndConfigList,

            TemplateName,
            TemplateElement,
            EndTemplateElement,
            TemplateListElement,
            EndTemplateListElement,
            TemplateList,
            EndTemplateList,
            TemplateElementOptions,
            EndTemplateElementOptions,
            TemplateListOptions,
            EndTemplateListOptions,

            Unknown,
        };

        struct Token {
            TokenType type;
            std::string value;
            size_t line;
            size_t column;
        };

        explicit Lexer(std::string input) : input(std::move(input)) {};

        std::vector<Token> lex();
        static std::string tokenTypeToString(TokenType type);

    private:
        std::string input;
        size_t index = {};
        size_t line = {1};
        size_t column = {1};

        unsigned char peek();
        unsigned char next();
        bool eof();
        void skipWhitespace();
        void skipComment();
        Token nextToken();
    };
}
