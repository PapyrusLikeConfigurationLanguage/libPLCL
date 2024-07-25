// SPDX-License-Identifier: Apache-2.0

#include <cstdint>
#include <stdexcept>
#include <format>
#include <Config.hpp>

namespace PLCL::Config {
    [[maybe_unused]] ConfigRoot ConfigRoot::fromString(const std::string &input) {
        Lexer lexer(input);
        auto tokens = lexer.lex();
        return ConfigRoot(tokens);
    }

    ConfigRoot::ConfigRoot(std::vector<Lexer::Token> &tokens) {
        size_t index = 0;
        if (tokens[index].type != Lexer::TokenType::ConfigName) {
            throw std::runtime_error(std::format(R"(Expected "ConfigName" at line {}, column {}, got {})", tokens[index].line, tokens[index].column, Lexer::tokenTypeToString(tokens[index].type)));
        }
        index++;
        if (tokens[index].type != Lexer::TokenType::Name) {
            throw std::runtime_error(std::format("Expected Name at line {}, column {}, got {}", tokens[index].line, tokens[index].column, Lexer::tokenTypeToString(tokens[index].type)));
        }
        this->name = tokens[index].value;
        index++;
        while (index < tokens.size()) {
            switch (tokens[index].type) {
                case Lexer::TokenType::Import:
                    index++;
                    if (tokens[index].type != Lexer::TokenType::StringLiteral) {
                        throw std::runtime_error(std::format("Expected string at line {}, column {}, got {}", tokens[index].line, tokens[index].column, Lexer::tokenTypeToString(tokens[index].type)));
                    }
                    this->imports.push_back(tokens[index].value);
                    index++;
                    break;
                case Lexer::TokenType::ConfigElement:
                    this->elements.push_back(new ConfigElement(tokens, index));
                    break;
                case Lexer::TokenType::ConfigList:
                    this->lists.push_back(new ConfigList(tokens, index));
                    break;
                case Lexer::TokenType::EndOfFile:
                    return;
                [[unlikely]] default:
                    throw std::runtime_error(std::format("Unexpected token at line {}, column {}, got {}", tokens[index].line, tokens[index].column, Lexer::tokenTypeToString(tokens[index].type)));
            }
        }
    }

    //void verifyHelper(ConfigElement &configElement, Template::TemplateElement &templateElement, bool strict) {
    //    if (configElement.type != templateElement.type) {
    //        throw std::runtime_error(std::format("Type mismatch: expected {}, got {}", templateElement.type, configElement.type));
    //    }
    //    for (auto &attribute : templateElement.attributes) {
    //        bool found = false;
    //        for (uint32_t i = 0; i < configElement.attributes.size(); ++i) {
    //            if (configElement.attributes[i]->name == attribute->name) {
    //                found = true;
    //                if ((std::holds_alternative<std::string>(configElement.attributes[i]->value) && attribute->type != Template::Type::String) ||
    //                    (std::holds_alternative<int64_t>(configElement.attributes[i]->value) && attribute->type != Template::Type::Integer) ||
    //                    (std::holds_alternative<bool>(configElement.attributes[i]->value) && attribute->type != Template::Type::Boolean)) {
    //                    std::string value;
    //                    if (std::holds_alternative<std::string>(configElement.attributes[i]->value)) {
    //                        value = std::get<std::string>(configElement.attributes[i]->value);
    //                    } else if (std::holds_alternative<int64_t>(configElement.attributes[i]->value)) {
    //                        value = std::to_string(std::get<int64_t>(configElement.attributes[i]->value));
    //                    } else if (std::holds_alternative<bool>(configElement.attributes[i]->value)) {
    //                        value = std::get<bool>(configElement.attributes[i]->value) ? "true" : "false";
    //                    }
    //                    throw std::runtime_error(std::format("Type mismatch: expected {}, got value {}", Template::typeToString(attribute->type), value));
    //                }
    //                configElement.attributes.erase(configElement.attributes.begin() + i);
    //            }
    //        }
    //        if (!found && attribute->required) {
    //            throw std::runtime_error(std::format("Missing required attribute: {}", attribute->name));
    //        }
    //    }
    //}

    [[maybe_unused]] void ConfigRoot::verify(Template::TemplateRoot &configTemplate, bool strict) {
        (void)configTemplate;
        (void)strict;
        throw std::runtime_error("Unimplemented");
        //auto template_copy = configTemplate;
        //auto config_copy = *this;

        //uint32_t element_index = 0;

        //while (element_index < config_copy.elements.size()) {
        //
        //}
    }

    [[maybe_unused]] std::string ConfigRoot::toString(size_t indent) {
        std::string result;
        result += std::format("ConfigName {}\n", this->name);
        for (auto &import : this->imports) {
            result += std::format("Import \"{}\"\n", import);
        }
        for (auto &element : this->elements) {
            result += element->toString(indent, 0);
        }
        for (auto &list : this->lists) {
            result += list->toString(indent, 0);
        }
        return result;
    }

    ConfigList::ConfigList(std::vector<Lexer::Token> &tokens, size_t &index) {
        if (tokens[index].type != Lexer::TokenType::ConfigList) {
            throw std::runtime_error(std::format(R"(Expected "ConfigList" at line {}, column {}, got {})", tokens[index].line, tokens[index].column, Lexer::tokenTypeToString(tokens[index].type)));
        }
        index++;
        if (tokens[index].type != Lexer::TokenType::Name) {
            throw std::runtime_error(std::format("Expected Name at line {}, column {}, got {}", tokens[index].line, tokens[index].column, Lexer::tokenTypeToString(tokens[index].type)));
        }
        this->type = tokens[index].value;
        index++;
        while (index < tokens.size()) {
            if (tokens[index].type == Lexer::TokenType::ConfigListElement) {
                this->elements.push_back(new ConfigListElement(tokens, index));
            } else if (tokens[index].type == Lexer::TokenType::EndConfigList) {
                index++;
                break;
            } else {
                throw std::runtime_error(std::format("Unexpected token at line {}, column {}, got {}", tokens[index].line, tokens[index].column, Lexer::tokenTypeToString(tokens[index].type)));
            }
        }
    }

    std::string ConfigList::toString(size_t indent, size_t indentStart) {
        std::string result;
        result += std::format("{}ConfigList {}\n", std::string(indentStart, ' '), this->type);
        for (auto &element : this->elements) {
            result += element->toString(indent, indentStart + indent);
        }
        result += std::string(indentStart, ' ') + "endConfigList\n";
        return result;
    }

    ConfigListElement::ConfigListElement(std::vector<Lexer::Token> &tokens, size_t &index) {
        if (tokens[index].type != Lexer::TokenType::ConfigListElement) {
            throw std::runtime_error(std::format(R"(Expected "ConfigListElement" at line {}, column {}, got {})", tokens[index].line, tokens[index].column, Lexer::tokenTypeToString(tokens[index].type)));
        }
        index++;
        if (tokens[index].type != Lexer::TokenType::NumberLiteral) {
            throw std::runtime_error(std::format("Expected NumberLiteral at line {}, column {}, got {}", tokens[index].line, tokens[index].column, Lexer::tokenTypeToString(tokens[index].type)));
        }
        this->id = std::stoll(tokens[index].value);
        index++;
        while (index < tokens.size()) {
            if (tokens[index].type == Lexer::TokenType::ConfigElement) {
                if (this->element != nullptr) {
                    throw std::runtime_error(std::format("Element already set at line {}, column {}", tokens[index].line, tokens[index].column));
                }
                this->element = new ConfigElement(tokens, index);
            } else if (tokens[index].type == Lexer::TokenType::EndConfigListElement) {
                index++;
                break;
            } else {
                throw std::runtime_error(std::format("Unexpected token at line {}, column {}, got {}", tokens[index].line, tokens[index].column, Lexer::tokenTypeToString(tokens[index].type)));
            }
        }
    }

    std::string ConfigListElement::toString(size_t indent, size_t indentStart) {
        std::string result;
        result += std::format("{}ConfigListElement {}\n", std::string(indentStart, ' '), this->id);
        result += this->element->toString(indent, indentStart + indent);
        result += std::string(indentStart, ' ') + "endConfigListElement\n";
        return result;
    }

    ConfigElement::ConfigElement(std::vector<Lexer::Token> &tokens, size_t &index) {
        if (tokens[index].type != Lexer::TokenType::ConfigElement) {
            throw std::runtime_error(std::format(R"(Expected "ConfigElement" at line {}, column {}, got {})", tokens[index].line, tokens[index].column, Lexer::tokenTypeToString(tokens[index].type)));
        }
        index++;
        if (tokens[index].type != Lexer::TokenType::Name) {
            throw std::runtime_error(std::format("Expected Name at line {}, column {}, got {}", tokens[index].line, tokens[index].column, Lexer::tokenTypeToString(tokens[index].type)));
        }
        this->type = tokens[index].value;
        index++;
        while (index < tokens.size()) {
            if (tokens[index].type == Lexer::TokenType::Name) {
                this->attributes.push_back(new ConfigElementAttribute(tokens, index));
            } else if (tokens[index].type == Lexer::TokenType::ConfigList) {
                this->lists.push_back(new ConfigList(tokens, index));
            } else if (tokens[index].type == Lexer::TokenType::EndConfigElement) {
                index++;
                break;
            } else {
                throw std::runtime_error(std::format("Unexpected token at line {}, column {}, got {}", tokens[index].line, tokens[index].column, Lexer::tokenTypeToString(tokens[index].type)));
            }
        }
    }

    std::string ConfigElement::toString(size_t indent, size_t indentStart) {
        std::string result;
        result += std::format("{}ConfigElement {}\n", std::string(indentStart, ' '), this->type);
        for (auto &attribute : this->attributes) {
            result += attribute->toString(indentStart + indent);
        }
        for (auto &list : this->lists) {
            result += list->toString(indent, indentStart + indent);
        }
        result += std::string(indentStart, ' ') + "endConfigElement\n";
        return result;
    }

    ConfigElementAttribute::ConfigElementAttribute(std::vector<Lexer::Token> &tokens, size_t &index) {
        if (tokens[index].type != Lexer::TokenType::Name) {
            throw std::runtime_error(std::format("Expected Name at line {}, column {}, got {}", tokens[index].line, tokens[index].column, Lexer::tokenTypeToString(tokens[index].type)));
        }
        this->name = tokens[index].value;
        index++;
        if (tokens[index].type != Lexer::TokenType::Equals) {
            throw std::runtime_error(std::format(R"(Expected "=" at line {}, column {}, got {})", tokens[index].line, tokens[index].column, Lexer::tokenTypeToString(tokens[index].type)));
        }
        index++;
        if (tokens[index].type == Lexer::TokenType::StringLiteral) {
            this->value = tokens[index].value;
        } else if (tokens[index].type == Lexer::TokenType::NumberLiteral) {
            if (tokens[index].value.find('.') != std::string::npos) {
                this->value = std::stod(tokens[index].value);
            } else {
                this->value = std::stoll(tokens[index].value);
            }
        } else if (tokens[index].type == Lexer::TokenType::BooleanLiteral) {
            this->value = tokens[index].value == "true";
        } else {
            throw std::runtime_error(std::format("Expected StringLiteral, NumberLiteral or BooleanLiteral at line {}, column {}, got {}", tokens[index].line, tokens[index].column, Lexer::tokenTypeToString(tokens[index].type)));
        }
        index++;
    }

    std::string ConfigElementAttribute::toString(size_t indent) {
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
