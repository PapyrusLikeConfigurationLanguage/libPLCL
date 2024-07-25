// SPDX-License-Identifier: Apache-2.0

/// @file
/// @brief Parsing into a configuration tree.
/// @attention This file is not meant to be included by the end user.
///
/// @namespace PLCL::Config
/// @brief The namespace for the configuration tree.
///
/// @struct PLCL::Config::ConfigRoot
/// @brief A struct that represents the root of a configuration tree.
/// @details It's used to store the parsed configuration.
///
/// @var PLCL::Config::ConfigRoot::name
/// @brief The name of the configuration.
///
/// @var PLCL::Config::ConfigRoot::imports
/// @brief The list of imported templates.
///
/// @var PLCL::Config::ConfigRoot::elements
/// @brief The list of elements in the top level of the configuration.
///
/// @var PLCL::Config::ConfigRoot::lists
/// @brief The list of lists in the top level of the configuration.
///
/// @fn PLCL::Config::ConfigRoot::ConfigRoot()
/// @brief Default constructor.
///
/// @fn PLCL::Config::ConfigRoot::ConfigRoot(std::vector<Lexer::Token>& tokens)
/// @brief Constructor that parses tokens from the lexer.
/// @param tokens The list of tokens to parse.
///
/// @fn PLCL::Config::ConfigRoot::ConfigRoot(std::string name, std::vector<std::string> imports, std::vector<ConfigElement*> elements, std::vector<ConfigList*> lists)
/// @brief Constructor that initializes all fields.
/// @param name The name of the configuration.
/// @param imports The list of imported templates.
/// @param elements The list of elements in the top level of the configuration.
/// @param lists The list of lists in the top level of the configuration.
///
/// @fn PLCL::Config::ConfigRoot PLCL::Config::ConfigRoot::fromString(const std::string& input)
/// @brief Parses a configuration from a string.
/// @param input The string to parse.
/// @return The parsed configuration.
///
/// @fn void PLCL::Config::ConfigRoot::verify(Template::TemplateRoot& configTemplate, bool strict)
/// @brief Verifies if the configuration is valid against a template.
/// @param configTemplate The template to verify against.
/// @param strict Whether to strictly verify the configuration.
/// @attention This function is not implemented yet.
///
/// @fn std::string PLCL::Config::ConfigRoot::toString(size_t indent)
/// @brief Converts the configuration to a string.
/// @param indent The number of spaces to indent the configuration's contents.
/// @return The configuration as a string.
///
/// @struct PLCL::Config::ConfigList
/// @brief A struct that represents a list in the configuration tree.
/// @details It's used to store a list of elements in the configuration.
///
/// @var PLCL::Config::ConfigList::type
/// @brief The type (name) of the list.
///
/// @var PLCL::Config::ConfigList::elements
/// @brief The list of elements in the list.
///
/// @fn PLCL::Config::ConfigList::ConfigList()
/// @brief Default constructor.
///
/// @fn PLCL::Config::ConfigList::ConfigList(std::vector<Lexer::Token>& tokens, size_t& index)
/// @brief Constructor that parses tokens from the lexer.
/// @param tokens The list of tokens to parse.
/// @param index The index of the token to start parsing from.
/// @attention This function is for internal use only.
///
/// @fn PLCL::Config::ConfigList::ConfigList(std::string type, std::vector<ConfigListElement*> elements)
/// @brief Constructor that initializes all fields.
/// @param type The type (name) of the list.
/// @param elements The list of elements in the list.
///
/// @fn std::string PLCL::Config::ConfigList::toString(size_t indent, size_t indentStart)
/// @brief Converts the list to a string.
/// @param indent The number of spaces to indent the list's contents.
/// @param indentStart The number of spaces to indent the whole list.
/// @return The list as a string.
///
/// @struct PLCL::Config::ConfigListElement
/// @brief A struct that represents an element in a list.
/// @details It's done this way to represent the structure of a configuration as closely as possible.
///
/// @var PLCL::Config::ConfigListElement::id
/// @brief The id of the element in the list.
///
/// @var PLCL::Config::ConfigListElement::element
/// @brief The element in the list.
/// 
/// @fn PLCL::Config::ConfigListElement::ConfigListElement()
/// @brief Default constructor.
///
/// @fn PLCL::Config::ConfigListElement::ConfigListElement(std::vector<Lexer::Token>& tokens, size_t& index)
/// @brief Constructor that parses tokens from the lexer.
/// @param tokens The list of tokens to parse.
/// @param index The index of the token to start parsing from.
/// @attention This function is for internal use only.
///
/// @fn PLCL::Config::ConfigListElement::ConfigListElement(size_t id, ConfigElement* element)
/// @brief Constructor that initializes all fields.
/// @param id The id of the element in the list.
/// @param element The element in the list.
///
/// @fn std::string PLCL::Config::ConfigListElement::toString(size_t indent, size_t indentStart)
/// @brief Converts the element to a string.
/// @param indent The number of spaces to indent the element's contents.
/// @param indentStart The number of spaces to indent the whole element.
/// @return The element as a string.
///
/// @struct PLCL::Config::ConfigElement
/// @brief A struct that represents an element in the configuration tree.
///
/// @var PLCL::Config::ConfigElement::type
/// @brief The type (name) of the element.
///
/// @var PLCL::Config::ConfigElement::attributes
/// @brief The list of attributes of the element.
///
/// @var PLCL::Config::ConfigElement::lists
/// @brief The list of lists in the element.
///
/// @fn PLCL::Config::ConfigElement::ConfigElement()
/// @brief Default constructor.
///
/// @fn PLCL::Config::ConfigElement::ConfigElement(std::vector<Lexer::Token>& tokens, size_t& index)
/// @brief Constructor that parses tokens from the lexer.
/// @param tokens The list of tokens to parse.
/// @param index The index of the token to start parsing from.
/// @attention This function is for internal use only.
///
/// @fn PLCL::Config::ConfigElement::ConfigElement(std::string type, std::vector<ConfigElementAttribute*> attributes, std::vector<ConfigList*> lists)
/// @brief Constructor that initializes all fields.
/// @param type The type (name) of the element.
/// @param attributes The list of attributes of the element.
/// @param lists The list of lists in the element.
///
/// @fn std::string PLCL::Config::ConfigElement::toString(size_t indent, size_t indentStart)
/// @brief Converts the element to a string.
/// @param indent The number of spaces to indent the element's contents.
/// @param indentStart The number of spaces to indent the whole element.
/// @return The element as a string.
///
/// @struct PLCL::Config::ConfigElementAttribute
/// @brief A struct that represents an attribute of an element.
///
/// @var PLCL::Config::ConfigElementAttribute::name
/// @brief The name of the attribute.
///
/// @var PLCL::Config::ConfigElementAttribute::value
/// @brief The value of the attribute.
///
/// @fn PLCL::Config::ConfigElementAttribute::ConfigElementAttribute()
/// @brief Default constructor.
///
/// @fn PLCL::Config::ConfigElementAttribute::ConfigElementAttribute(std::vector<Lexer::Token>& tokens, size_t& index)
/// @brief Constructor that parses tokens from the lexer.
/// @param tokens The list of tokens to parse.
/// @param index The index of the token to start parsing from.
/// @attention This function is for internal use only.
///
/// @fn PLCL::Config::ConfigElementAttribute::ConfigElementAttribute(std::string name, Generic::ValueType value)
/// @brief Constructor that initializes all fields.
/// @param name The name of the attribute.
/// @param value The value of the attribute.
///
/// @fn std::string PLCL::Config::ConfigElementAttribute::toString(size_t indent)
/// @brief Converts the attribute to a string.
/// @param indent The number of spaces to indent the attribute.
/// @return The attribute as a string.


#pragma once
#include <string>
#include <vector>
#include "Lexer.hpp"
#include "Template.hpp"

namespace PLCL::Config {
    struct ConfigRoot;
    struct ConfigList;
    struct ConfigListElement;
    struct ConfigElement;
    struct ConfigElementAttribute;

    struct ConfigRoot {
        std::string name;
        std::vector<std::string> imports;
        std::vector<ConfigElement*> elements;
        std::vector<ConfigList*> lists;

        ConfigRoot() = default;
        explicit ConfigRoot(std::vector<Lexer::Token>& tokens);
        [[maybe_unused]] ConfigRoot(std::string name, std::vector<std::string> imports, std::vector<ConfigElement*> elements, std::vector<ConfigList*> lists)
            : name(std::move(name)), imports(std::move(imports)), elements(std::move(elements)), lists(std::move(lists)) {};

        [[maybe_unused]] static ConfigRoot fromString(const std::string& input);
        [[maybe_unused]] void verify(Template::TemplateRoot& configTemplate, bool strict);
        [[maybe_unused]] std::string toString(size_t indent);
    };

    struct ConfigList {
        std::string type;
        std::vector<ConfigListElement*> elements;

        ConfigList() = default;
        ConfigList(std::vector<Lexer::Token>& tokens, size_t& index);
        ConfigList(std::string type, std::vector<ConfigListElement*> elements)
            : type(std::move(type)), elements(std::move(elements)) {};

        [[maybe_unused]] std::string toString(size_t indent, size_t indentStart);
    };

    struct ConfigListElement {
        size_t id = {};
        ConfigElement* element = nullptr;

        ConfigListElement() = default;
        ConfigListElement(std::vector<Lexer::Token>& tokens, size_t& index);
        ConfigListElement(size_t id, ConfigElement* element)
            : id(id), element(element) {};

        [[maybe_unused]] std::string toString(size_t indent, size_t indentStart);
    };

    struct ConfigElement {
        std::string type;
        std::vector<ConfigElementAttribute*> attributes;
        std::vector<ConfigList*> lists;

        ConfigElement() = default;
        ConfigElement(std::vector<Lexer::Token>& tokens, size_t& index);
        ConfigElement(std::string type, std::vector<ConfigElementAttribute*> attributes, std::vector<ConfigList*> lists)
            : type(std::move(type)), attributes(std::move(attributes)), lists(std::move(lists)) {};

        [[maybe_unused]] std::string toString(size_t indent, size_t indentStart);
    };

    struct ConfigElementAttribute {
        std::string name;
        Generic::ValueType value;

        ConfigElementAttribute() = default;
        ConfigElementAttribute(std::vector<Lexer::Token>& tokens, size_t& index);
        ConfigElementAttribute(std::string name, Generic::ValueType value)
            : name(std::move(name)), value(std::move(value)) {};

        [[maybe_unused]] std::string toString(size_t indent);
    };
}
