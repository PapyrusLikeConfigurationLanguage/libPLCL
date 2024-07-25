// SPDX-License-Identifier: Apache-2.0

#include <stdexcept>
#include <format>
#include <utility>
#include <Template.hpp>

namespace PLCL::Template {
    std::string attributeTypeToString(AttributeType type) {
        switch (type) {
            case AttributeType::String:
                return "string";
            case AttributeType::Integer:
                return "int";
            case AttributeType::Float:
                return "float";
            case AttributeType::Boolean:
                return "bool";
            [[unlikely]] default:
                std::unreachable();
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

    std::string TemplateRoot::toString(size_t indent) {
        std::string result;
        result += std::format("TemplateName {}\n", this->name);
        for (auto &element : this->elements) {
            result += element->toString(indent, 0);
        }
        for (auto &list : this->lists) {
            result += list->toString(indent, 0);
        }
        return result;
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

    std::string TemplateList::toString(size_t indent, size_t indentStart) {
        std::string result;
        result += std::format("{}TemplateList {}\n", std::string(indentStart, ' '), this->type);
        if (this->options != nullptr) {
            result += this->options->toString(indent, indentStart + indent, OptionsType::List);
        }
        for (auto &element : this->elements) {
            result += element->toString(indent, indentStart + indent);
        }
        result += std::format("{}endTemplateList\n", std::string(indentStart, ' '));
        return result;
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
                    this->element = new TemplateElement(tokens, index);
                    //this->elements.push_back(new TemplateElement(tokens, index));
                    break;
                case Lexer::TokenType::EndTemplateListElement:
                    index++;
                    return;
                [[unlikely]] default:
                    throw std::runtime_error(std::format("Unexpected token at line {}, column {}, but got {}", tokens[index].line, tokens[index].column, Lexer::tokenTypeToString(tokens[index].type)));
            }
        }
    }

    std::string TemplateListElement::toString(size_t indent, size_t indentStart) {
        std::string result;
        result += std::format("{}TemplateListElement {}\n", std::string(indentStart, ' '), this->id);
        result += this->element->toString(indent, indentStart + indent);
        result += std::format("{}endTemplateListElement\n", std::string(indentStart, ' '));
        return result;
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
                case Lexer::TokenType::Float:
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

    std::string TemplateElement::toString(size_t indent, size_t indentStart) {
        std::string result;
        result += std::format("{}TemplateElement {}\n", std::string(indentStart, ' '), this->type);
        if (this->options != nullptr) {
            result += this->options->toString(indent, indentStart + indent, OptionsType::Element);
        }
        for (auto &attribute : this->attributes) {
            result += attribute->toString(indentStart + indent);
        }
        for (auto &list : this->lists) {
            result += list->toString(indent, indentStart + indent);
        }
        result += std::format("{}endTemplateElement\n", std::string(indentStart, ' '));
        return result;
    }

    TemplateAttribute::TemplateAttribute(std::vector<Lexer::Token> &tokens, size_t &index) {
        switch (tokens[index].type) {
            case Lexer::TokenType::String:
                this->type = AttributeType::String;
                break;
            case Lexer::TokenType::Integer:
                this->type = AttributeType::Integer;
                break;
            case Lexer::TokenType::Float:
                this->type = AttributeType::Float;
                break;
            case Lexer::TokenType::Boolean:
                this->type = AttributeType::Boolean;
                break;
            [[unlikely]] default:
                throw Generic::genericExpectedError("String, Integer, Float, or Boolean", Lexer::tokenTypeToString(tokens[index].type), tokens[index].line, tokens[index].column);
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
                    case AttributeType::String:
                        if (tokens[index].type != Lexer::TokenType::StringLiteral) {
                            throw Generic::genericExpectedError("StringLiteral", Lexer::tokenTypeToString(tokens[index].type), tokens[index].line, tokens[index].column);
                        }
                        this->defaultValue = new std::string(tokens[index].value);
                        break;
                    case AttributeType::Integer:
                    case AttributeType::Float:
                        if (tokens[index].type != Lexer::TokenType::NumberLiteral) {
                            throw Generic::genericExpectedError("NumberLiteral", Lexer::tokenTypeToString(tokens[index].type), tokens[index].line, tokens[index].column);
                        }
                        this->defaultValue = new std::string(tokens[index].value);
                        break;
                    case AttributeType::Boolean:
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

    std::string TemplateAttribute::toString(size_t indent) {
        std::string result;
        result += std::format("{}{} {}{}", std::string(indent, ' '), attributeTypeToString(this->type), this->name, this->required ? " required" : "");
        if (this->defaultValue != nullptr) {
            if (this->type == AttributeType::String) {
                result += std::format(" default \"{}\"", *this->defaultValue);
            } else {
                result += std::format(" default {}", *this->defaultValue);
            }
        }
        result += '\n';
        return result;
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

    std::string TemplateOptions::toString(size_t indent, size_t indentStart, PLCL::Template::OptionsType optionsType) {
        std::string result;
        result += std::format("{}Template{}Options\n", std::string(indentStart, ' '), optionsType == OptionsType::Element ? "Element" : "List");
        for (auto &option : this->options) {
            result += option->toString(indentStart + indent);
        }
        result += std::format("{}endTemplate{}Options\n", std::string(indentStart, ' '), optionsType == OptionsType::Element ? "Element" : "List");
        return result;
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
            [[unlikely]] default:
                std::unreachable();
        }
        index++;
    }

    std::string TemplateOption::toString(size_t indent) {
        std::string result;
        result += std::format("{}{} = ", std::string(indent, ' '), this->name);
        if (std::holds_alternative<std::string>(this->value)) {
            result += "\"" + std::get<std::string>(this->value) + "\"\n";
        } else if (std::holds_alternative<int64_t>(this->value)) {
            result += std::to_string(std::get<int64_t>(this->value)) + "\n";
        } else if (std::holds_alternative<Generic::float64_t>(this->value)) {
            result += std::format("{}\n", std::get<Generic::float64_t>(this->value)); // std::format doesn't give trailing 0s
        } else if (std::holds_alternative<bool>(this->value)) {
            result += std::get<bool>(this->value) ? "true\n" : "false\n";
        }
        return result;
    }
}
