// SPDX-License-Identifier: Apache-2.0

#pragma once
#include <vector>
#include <string>

namespace PapyrusLikeConfigurationLanguage {
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