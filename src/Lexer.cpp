// SPDX-License-Identifier: Apache-2.0

#include "libPapyrusLikeConfigurationLanguage/Lexer.hpp"
#include "libPapyrusLikeConfigurationLanguage/Helper.hpp"

namespace PapyrusLikeConfigurationLanguage {
    std::string Lexer::tokenTypeToString(Lexer::TokenType type) {
        switch (type) {
            case Lexer::TokenType::EndOfFile:
                return "EndOfFile";
            case Lexer::TokenType::Equals:
                return "Equals";
            case Lexer::TokenType::Name:
                return "Name";
            case Lexer::TokenType::StringLiteral:
                return "StringLiteral";
            case Lexer::TokenType::NumberLiteral:
                return "NumberLiteral";
            case Lexer::TokenType::BooleanLiteral:
                return "BooleanLiteral";
            case Lexer::TokenType::ConfigName:
                return "ConfigName";
            case Lexer::TokenType::Import:
                return "Import";
            case Lexer::TokenType::String:
                return "String";
            case Lexer::TokenType::Integer:
                return "Integer";
            case Lexer::TokenType::Boolean:
                return "Boolean";
            case Lexer::TokenType::ConfigElement:
                return "ConfigElement";
            case Lexer::TokenType::EndConfigElement:
                return "EndConfigElement";
            case Lexer::TokenType::ConfigListElement:
                return "ConfigListElement";
            case Lexer::TokenType::EndConfigListElement:
                return "EndConfigListElement";
            case Lexer::TokenType::ConfigList:
                return "ConfigList";
            case Lexer::TokenType::EndConfigList:
                return "EndConfigList";
            case Lexer::TokenType::TemplateName:
                return "TemplateName";
            case Lexer::TokenType::TemplateElement:
                return "TemplateElement";
            case Lexer::TokenType::EndTemplateElement:
                return "EndTemplateElement";
            case Lexer::TokenType::TemplateListElement:
                return "TemplateListElement";
            case Lexer::TokenType::EndTemplateListElement:
                return "EndTemplateListElement";
            case Lexer::TokenType::TemplateList:
                return "TemplateList";
            case Lexer::TokenType::EndTemplateList:
                return "EndTemplateList";
            case Lexer::TokenType::TemplateElementOptions:
                return "TemplateElementOptions";
            case Lexer::TokenType::EndTemplateElementOptions:
                return "EndTemplateElementOptions";
            case Lexer::TokenType::TemplateListOptions:
                return "TemplateListOptions";
            case Lexer::TokenType::EndTemplateListOptions:
                return "EndTemplateListOptions";
            case Lexer::TokenType::Unknown:
                return "Unknown";
        }
    }

    std::vector<Lexer::Token> Lexer::lex() {
        std::vector<Token> tokens;
        while (!this->eof()) {
            this->skipWhitespace();
            this->skipComment();
            this->skipWhitespace();
            if (this->eof()) {
                break;
            }
            tokens.push_back(this->nextToken());
        }
        tokens.push_back({TokenType::EndOfFile, "", line, column});
        return tokens;
    }

    unsigned char Lexer::peek() {
        if (this->index >= this->input.size()) {
            return '\0';
        }
        return this->input[this->index];
    }

    unsigned char Lexer::next() {
        char c = this->input[this->index];
        this->index++;
        if (c == '\n') {
            this->line++;
            this->column = 1;
        } else {
            this->column++;
        }
        return c;
    }

    bool Lexer::eof() {
        return this->index >= this->input.size();
    }

    void Lexer::skipWhitespace() {
        while (std::isspace(this->peek())) {
            this->next();
        }
    }

    void Lexer::skipComment() {
        if (this->peek() == ';') {
            while (this->peek() != '\n') {
                this->next();
            }
        }
    }

    Lexer::Token Lexer::nextToken() {
        unsigned char c = this->peek();
        if (c == '=') {
            this->next();
            return {TokenType::Equals, "", line, column};
        }
        if (c == '"') {
            this->next();
            std::string value;
            while (this->peek() != '"') {
                if (this->peek() == '\\' && this->input[this->index + 1] == '"') {
                    this->next();
                }
                value += static_cast<char>(this->next());
            }
            this->next();
            return {TokenType::StringLiteral, value, line, column};
        }
        if (std::isdigit(c) || c == '-') {
            std::string value;
            while (std::isdigit(this->peek())) {
                value += static_cast<char>(this->next());
            }
            return {TokenType::NumberLiteral, value, line, column};
        }
        if (std::isalpha(c) || c == '_') {
            std::string value;
            while (std::isalnum(this->peek()) || this->peek() == '_') {
                value += static_cast<char>(this->next());
            }
            if (Helper::iequals(value, "true")) {
                return {TokenType::BooleanLiteral, "true", line, column};
            }
            if (Helper::iequals(value, "false")) {
                return {TokenType::BooleanLiteral, "false", line, column};
            }
            if (Helper::iequals(value, "import")) {
                return {TokenType::Import, "", line, column};
            }
            if (Helper::iequals(value, "string")) {
                return {TokenType::String, "", line, column};
            }
            if (Helper::iequals(value, "int")) {
                return {TokenType::Integer, "", line, column};
            }
            if (Helper::iequals(value, "bool")) {
                return {TokenType::Boolean, "", line, column};
            }
            if (Helper::iequals(value, "configname")) {
                return {TokenType::ConfigName, "", line, column};
            }
            if (Helper::iequals(value, "configelement")) {
                return {TokenType::ConfigElement, "", line, column};
            }
            if (Helper::iequals(value, "endconfigelement")) {
                return {TokenType::EndConfigElement, "", line, column};
            }
            if (Helper::iequals(value, "configlistelement")) {
                return {TokenType::ConfigListElement, "", line, column};
            }
            if (Helper::iequals(value, "endconfiglistelement")) {
                return {TokenType::EndConfigListElement, "", line, column};
            }
            if (Helper::iequals(value, "configlist")) {
                return {TokenType::ConfigList, "", line, column};
            }
            if (Helper::iequals(value, "endconfiglist")) {
                return {TokenType::EndConfigList, "", line, column};
            }
            if (Helper::iequals(value, "templatename")) {
                return {TokenType::TemplateName, "", line, column};
            }
            if (Helper::iequals(value, "templateelement")) {
                return {TokenType::TemplateElement, "", line, column};
            }
            if (Helper::iequals(value, "endtemplateelement")) {
                return {TokenType::EndTemplateElement, "", line, column};
            }
            if (Helper::iequals(value, "templatelistelement")) {
                return {TokenType::TemplateListElement, "", line, column};
            }
            if (Helper::iequals(value, "endtemplatelistelement")) {
                return {TokenType::EndTemplateListElement, "", line, column};
            }
            if (Helper::iequals(value, "templatelist")) {
                return {TokenType::TemplateList, "", line, column};
            }
            if (Helper::iequals(value, "endtemplatelist")) {
                return {TokenType::EndTemplateList, "", line, column};
            }
            if (Helper::iequals(value, "templateelementoptions")) {
                return {TokenType::TemplateElementOptions, "", line, column};
            }
            if (Helper::iequals(value, "endtemplateelementoptions")) {
                return {TokenType::EndTemplateElementOptions, "", line, column};
            }
            if (Helper::iequals(value, "templatelistoptions")) {
                return {TokenType::TemplateListOptions, "", line, column};
            }
            if (Helper::iequals(value, "endtemplatelistoptions")) {
                return {TokenType::EndTemplateListOptions, "", line, column};
            }
            return {TokenType::Name, value, line, column};
        }
        this->next();
        return {TokenType::Unknown, std::string(1, static_cast<char>(c)), line, column};
    }
} // PapyrusLikeConfigurationLanguage
