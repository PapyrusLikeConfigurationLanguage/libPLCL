// SPDX-License-Identifier: Apache-2.0

#include <stdexcept>
#include <format>
#include <utility>
#include <Template.hpp>

namespace PapyrusLikeConfigurationLanguage::Template {
    std::string typeToString(Type type) {
        switch (type) {
            case Type::String:
                return "String";
            case Type::Integer:
                return "Integer";
            case Type::Boolean:
                return "Boolean";
        }
    }

    [[maybe_unused]] TemplateRoot TemplateRoot::fromString(const std::string &input) {
        Lexer lexer(input);
        auto tokens = lexer.lex();
        return TemplateRoot(tokens);
    }

    TemplateRoot::TemplateRoot(std::vector<Lexer::Token> &tokens) {
        size_t index = 0;
        if (tokens[index].type != Lexer::TokenType::TemplateName) {
            throw Generic::genericExpectedError(R"("TemplateName")", Lexer::tokenTypeToString(tokens[index].type), tokens[index].line, tokens[index].column);
        }
        index++;
        if (tokens[index].type != Lexer::TokenType::Name) {
            throw Generic::genericExpectedError("Name", Lexer::tokenTypeToString(tokens[index].type), tokens[index].line, tokens[index].column);
        }
        this->name = tokens[index].value;
        index++;
        while (index < tokens.size()) {
            switch (tokens[index].type) {
                case Lexer::TokenType::TemplateElement:
                    this->elements.push_back(new TemplateElement(tokens, index));
                    break;
                case Lexer::TokenType::TemplateList:
                    this->lists.push_back(new TemplateList(tokens, index));
                    break;
                case Lexer::TokenType::EndOfFile:
                    return;
                [[unlikely]] default:
                    throw std::runtime_error(std::format("Unexpected token at line {}, column {}, got {}", tokens[index].line, tokens[index].column, Lexer::tokenTypeToString(tokens[index].type)));
            }
        }
    }

    TemplateList::TemplateList(std::vector<Lexer::Token> &tokens, size_t &index) {
        if (tokens[index].type != Lexer::TokenType::TemplateList) {
            throw Generic::genericExpectedError(R"("TemplateList")", Lexer::tokenTypeToString(tokens[index].type), tokens[index].line, tokens[index].column);
            //throw std::runtime_error(std::format("Expected \"TemplateList\" at line {}, column {}, got {}", tokens[index].line, tokens[index].column, Lexer::tokenTypeToString(tokens[index].type)));
        }
        index++;
        if (tokens[index].type != Lexer::TokenType::Name) {
            throw Generic::genericExpectedError("Name", Lexer::tokenTypeToString(tokens[index].type), tokens[index].line, tokens[index].column);
            //throw std::runtime_error(std::format("Expected Name at line {}, column {}, got {}", tokens[index].line, tokens[index].column, Lexer::tokenTypeToString(tokens[index].type)));
        }
        this->type = tokens[index].value;
        index++;
        while (index < tokens.size()) {
            switch (tokens[index].type) {
                case Lexer::TokenType::TemplateListElement:
                    this->elements.push_back(new TemplateListElement(tokens, index));
                    break;
                case Lexer::TokenType::TemplateListOptions:
                    if (this->options != nullptr) {
                        throw std::runtime_error(std::format("TemplateListOptions already set, Unexpected TemplateListOptions at line {}, column {}", tokens[index].line, tokens[index].column));
                    }
                    this->options = new TemplateOptions(tokens, index);
                    break;
                case Lexer::TokenType::EndTemplateList:
                    index++;
                    return;
                [[unlikely]] default:
                    throw std::runtime_error(std::format("Unexpected token at line {}, column {}, got {}", tokens[index].line, tokens[index].column, Lexer::tokenTypeToString(tokens[index].type)));
            }
        }
    }

    TemplateListElement::TemplateListElement(std::vector<Lexer::Token> &tokens, size_t &index) {
        if (tokens[index].type != Lexer::TokenType::TemplateListElement) {
            throw Generic::genericExpectedError(R"("TemplateListElement")", Lexer::tokenTypeToString(tokens[index].type), tokens[index].line, tokens[index].column);
            //throw std::runtime_error(std::format("Expected \"TemplateListElement\" at line {}, column {}, but got {}", tokens[index].line, tokens[index].column, Lexer::tokenTypeToString(tokens[index].type)));
        }
        index++;
        if (tokens[index].type != Lexer::TokenType::NumberLiteral) {
            throw Generic::genericExpectedError("NumberLiteral", Lexer::tokenTypeToString(tokens[index].type), tokens[index].line, tokens[index].column);
            //throw std::runtime_error(std::format("Expected NumberLiteral at line {}, column {}, but got {}", tokens[index].line, tokens[index].column, Lexer::tokenTypeToString(tokens[index].type)));
        }
        this->id = std::stoll(tokens[index].value);
        index++;
        while (index < tokens.size()) {
            switch (tokens[index].type) {
                case Lexer::TokenType::TemplateElement:
                    this->elements.push_back(new TemplateElement(tokens, index));
                    break;
                case Lexer::TokenType::EndTemplateListElement:
                    index++;
                    return;
                [[unlikely]] default:
                    throw std::runtime_error(std::format("Unexpected token at line {}, column {}, but got {}", tokens[index].line, tokens[index].column, Lexer::tokenTypeToString(tokens[index].type)));
            }
        }
    }

    TemplateElement::TemplateElement(std::vector<Lexer::Token> &tokens, size_t &index) {
        if (tokens[index].type != Lexer::TokenType::TemplateElement) {
            throw Generic::genericExpectedError(R"("TemplateElement")", Lexer::tokenTypeToString(tokens[index].type), tokens[index].line, tokens[index].column);
            //throw std::runtime_error(std::format("Expected \"TemplateElement\" at line {}, column {}, but got {}", tokens[index].line, tokens[index].column, Lexer::tokenTypeToString(tokens[index].type)));
        }
        index++;
        if (tokens[index].type != Lexer::TokenType::Name) {
            throw Generic::genericExpectedError("Name", Lexer::tokenTypeToString(tokens[index].type), tokens[index].line, tokens[index].column);
            //throw std::runtime_error(std::format("Expected Name at line {}, column {}, but got {}", tokens[index].line, tokens[index].column, Lexer::tokenTypeToString(tokens[index].type)));
        }
        this->type = tokens[index].value;
        index++;
        while (index < tokens.size()) {
            switch (tokens[index].type) {
                case Lexer::TokenType::String:
                case Lexer::TokenType::Integer:
                case Lexer::TokenType::Boolean:
                    this->attributes.push_back(new TemplateAttribute(tokens, index));
                    break;
                case Lexer::TokenType::TemplateElementOptions:
                    if (this->options != nullptr) {
                        throw std::runtime_error(std::format("TemplateElementOptions already set, Unexpected TemplateElementOptions at line {}, column {}", tokens[index].line, tokens[index].column));
                    }
                    this->options = new TemplateOptions(tokens, index);
                    break;
                case Lexer::TokenType::TemplateList:
                    this->lists.push_back(new TemplateList(tokens, index));
                    break;
                case Lexer::TokenType::EndTemplateElement:
                    index++;
                    return;
                [[unlikely]] default:
                    throw std::runtime_error(std::format("Unexpected token at line {}, column {}, but got {}", tokens[index].line, tokens[index].column, Lexer::tokenTypeToString(tokens[index].type)));
            }
        }
    }

    TemplateAttribute::TemplateAttribute(std::vector<Lexer::Token> &tokens, size_t &index) {
        switch (tokens[index].type) {
            case Lexer::TokenType::String:
                this->type = Type::String;
                break;
            case Lexer::TokenType::Integer:
                this->type = Type::Integer;
                break;
            case Lexer::TokenType::Boolean:
                this->type = Type::Boolean;
                break;
            [[unlikely]] default:
                throw Generic::genericExpectedError("String, Integer, or Boolean", Lexer::tokenTypeToString(tokens[index].type), tokens[index].line, tokens[index].column);
        }
        index++;
        if (tokens[index].type != Lexer::TokenType::Name) {
            throw Generic::genericExpectedError("Name", Lexer::tokenTypeToString(tokens[index].type), tokens[index].line, tokens[index].column);
        }
        this->name = tokens[index].value;
        index++;
        while (index < tokens.size()) {
            if (tokens[index].type != Lexer::TokenType::Name) {
                return;
            }
            if (tokens[index].value == "required") {
                this->required = true;
                index++;
            } else if (tokens[index].value == "default") {
                index++;
                switch (this->type) {
                    case Type::String:
                        if (tokens[index].type != Lexer::TokenType::StringLiteral) {
                            throw Generic::genericExpectedError("StringLiteral", Lexer::tokenTypeToString(tokens[index].type), tokens[index].line, tokens[index].column);
                        }
                        this->defaultValue = new std::string(tokens[index].value);
                        break;
                    case Type::Integer:
                        if (tokens[index].type != Lexer::TokenType::NumberLiteral) {
                            throw Generic::genericExpectedError("NumberLiteral", Lexer::tokenTypeToString(tokens[index].type), tokens[index].line, tokens[index].column);
                        }
                        this->defaultValue = new std::string(tokens[index].value);
                        break;
                    case Type::Boolean:
                        if (tokens[index].type != Lexer::TokenType::BooleanLiteral) {
                            throw Generic::genericExpectedError("BooleanLiteral", Lexer::tokenTypeToString(tokens[index].type), tokens[index].line, tokens[index].column);
                        }
                        this->defaultValue = new std::string(tokens[index].value);
                        break;
                }
                index++;
            } else {
                return;
            }
        }
    }

    TemplateOptions::TemplateOptions(std::vector<Lexer::Token> &tokens, size_t &index) {
        if (tokens[index].type != Lexer::TokenType::TemplateElementOptions && tokens[index].type != Lexer::TokenType::TemplateListOptions) {
            throw Generic::genericExpectedError(R"("TemplateElementOptions" or "TemplateListOptions")", Lexer::tokenTypeToString(tokens[index].type), tokens[index].line, tokens[index].column);
        }
        index++;
        while (index < tokens.size()) {
            if (tokens[index].type == Lexer::TokenType::Name) {
                this->options.push_back(new TemplateOption(tokens, index));
            } else if (tokens[index].type == Lexer::TokenType::EndTemplateElementOptions || tokens[index].type == Lexer::TokenType::EndTemplateListOptions) {
                index++;
                return;
            } else {
                throw Generic::genericExpectedError("Name", Lexer::tokenTypeToString(tokens[index].type), tokens[index].line, tokens[index].column);
            }
        }
    }

    TemplateOption::TemplateOption(std::vector<Lexer::Token> &tokens, size_t &index) {
        if (tokens[index].type != Lexer::TokenType::Name) {
            throw Generic::genericExpectedError("Name", Lexer::tokenTypeToString(tokens[index].type), tokens[index].line, tokens[index].column);
        }
        this->name = tokens[index].value;
        index++;
        if (tokens[index].type != Lexer::TokenType::Equals) {
            throw Generic::genericExpectedError("=", Lexer::tokenTypeToString(tokens[index].type), tokens[index].line, tokens[index].column);
        }
        index++;
        if (tokens[index].type != Lexer::TokenType::StringLiteral && tokens[index].type != Lexer::TokenType::NumberLiteral && tokens[index].type != Lexer::TokenType::BooleanLiteral) {
            throw Generic::genericExpectedError("StringLiteral, NumberLiteral, or BooleanLiteral", Lexer::tokenTypeToString(tokens[index].type), tokens[index].line, tokens[index].column);
        }
        switch (tokens[index].type) {
            case Lexer::TokenType::StringLiteral:
                this->value = tokens[index].value;
                break;
            case Lexer::TokenType::NumberLiteral:
                this->value = std::stoll(tokens[index].value);
                break;
            case Lexer::TokenType::BooleanLiteral:
                this->value = tokens[index].value == "true";
                break;
            [[unlikely]]
            default:
                std::unreachable();
        }
        index++;
    }
}
