// SPDX-License-Identifier: Apache-2.0

/// @file
/// @brief Parsing into a template tree.
/// @attention This file is not meant to be included by the end user.
///
/// @namespace PLCL::Template 
/// @brief The namespace for the template tree.
///
/// @enum PLCL::Template::AttributeType
/// @brief The type of a template attribute.
///
/// @enum PLCL::Template::OptionsType
/// @brief The type of options in a template element or list.
///
/// @fn std::string PLCL::Template::attributeTypeToString(AttributeType type)
/// @brief Converts an attribute type to a string.
/// @param type The type to convert.
/// @return The string representation of the type.
///
/// @struct PLCL::Template::TemplateRoot
/// @brief A struct that represents the root of a template tree.
///
/// @var std::string PLCL::Template::TemplateRoot::name 
/// @brief The name of the template.
///
/// @var std::vector<PLCL::Template::TemplateElement*> PLCL::Template::TemplateRoot::elements
/// @brief The list of elements in the top level of the template.
///
/// @var std::vector<PLCL::Template::TemplateList*> PLCL::Template::TemplateRoot::lists
/// @brief The list of lists in the top level of the template.
///
/// @fn PLCL::Template::TemplateRoot::TemplateRoot()
/// @brief Default constructor.
///
/// @fn PLCL::Template::TemplateRoot::TemplateRoot(std::vector<Lexer::Token>& tokens)
/// @brief Constructor that parses tokens from the lexer.
/// @param tokens The list of tokens to parse.
///
/// @fn PLCL::Template::TemplateRoot::TemplateRoot(std::string name, std::vector<TemplateElement*> elements, std::vector<TemplateList*> lists)
/// @brief Constructor that initializes all fields.
///
/// @fn PLCL::Template::TemplateRoot PLCL::Template::TemplateRoot::fromString(const std::string& input)
/// @brief Parses a template from a string. 
/// @param input The string to parse.
/// @return The parsed template.
///
/// @fn std::string PLCL::Template::TemplateRoot::toString(size_t indent)
/// @brief Converts the template to a string.
/// @param indent The number of spaces to indent the template's contents.
/// @return The template as a string.
///
/// @struct PLCL::Template::TemplateList
/// @brief A struct that represents a list in the template tree.
/// @details It's used to store a list of elements in the template.
///
/// @var std::string PLCL::Template::TemplateList::type
/// @brief The type (name) of the list.
///
/// @var PLCL::Template::TemplateOptions* PLCL::Template::TemplateList::options
/// @brief The options of the list.
///
/// @var std::vector<PLCL::Template::TemplateListElement*> PLCL::Template::TemplateList::elements
/// @brief The list of elements in the list.
///
/// @fn PLCL::Template::TemplateList::TemplateList()
/// @brief Default constructor.
///
/// @fn PLCL::Template::TemplateList::TemplateList(std::vector<Lexer::Token>& tokens, size_t& index)
/// @brief Constructor that parses tokens from the lexer.
/// @param tokens The list of tokens to parse.
/// @param index The index of the current token.
/// @attention This function is for internal use only.
///
/// @fn PLCL::Template::TemplateList::TemplateList(std::string type, TemplateOptions* options, std::vector<TemplateListElement*> elements)
/// @brief Constructor that initializes all fields.
/// @param type The type (name) of the list.
/// @param options The options of the list.
/// @param elements The list of elements in the list.
///
/// @fn std::string PLCL::Template::TemplateList::toString(size_t indent, size_t indentStart)
/// @brief Converts the list to a string.
/// @param indent The number of spaces to indent the list's contents.
/// @param indentStart The number of spaces to indent the whole list.
/// @return The list as a string.
///
/// @struct PLCL::Template::TemplateListElement
/// @brief A struct that represents an element in a list in the template tree.
/// @details It's done this way to represent the structure of a template as closely as possible.
///
/// @var size_t PLCL::Template::TemplateListElement::id 
/// @brief The id of the element.
///
/// @var PLCL::Template::TemplateElement* PLCL::Template::TemplateListElement::element
/// @brief The element in the list.
/// 
/// @fn PLCL::Template::TemplateListElement::TemplateListElement()
/// @brief Default constructor.
///
/// @fn PLCL::Template::TemplateListElement::TemplateListElement(std::vector<Lexer::Token>& tokens, size_t& index)
/// @brief Constructor that parses tokens from the lexer.
/// @param tokens The list of tokens to parse.
/// @param index The index of the current token.
/// @attention This function is for internal use only.
///
/// @fn PLCL::Template::TemplateListElement::TemplateListElement(size_t id, TemplateElement* element)
/// @brief Constructor that initializes all fields.
/// @param id The id of the element.
/// @param element The element in the list.
///
/// @fn std::string PLCL::Template::TemplateListElement::toString(size_t indent, size_t indentStart)
/// @brief Converts the element to a string.
/// @param indent The number of spaces to indent the element's contents.
/// @param indentStart The number of spaces to indent the whole element.
/// @return The element as a string.
///
/// @struct PLCL::Template::TemplateElement
/// @brief A struct that represents an element in the template tree.
/// 
/// @var std::string PLCL::Template::TemplateElement::type 
/// @brief The type (name) of the element.
///
/// @var PLCL::Template::TemplateOptions* PLCL::Template::TemplateElement::options 
/// @brief The options of the element.
///
/// @var std::vector<PLCL::Template::TemplateAttribute*> PLCL::Template::TemplateElement::attributes 
/// @brief The list of attributes of the element.
///
/// @var std::vector<PLCL::Template::TemplateList*> PLCL::Template::TemplateElement::lists
/// @brief The list of lists in the element.
///
/// @fn PLCL::Template::TemplateElement::TemplateElement()
/// @brief Default constructor.
///
/// @fn PLCL::Template::TemplateElement::TemplateElement(std::vector<Lexer::Token>& tokens, size_t& index)
/// @brief Constructor that parses tokens from the lexer.
/// @param tokens The list of tokens to parse.
/// @param index The index of the current token.
/// @attention This function is for internal use only.
///
/// @fn PLCL::Template::TemplateElement::TemplateElement(std::string type, TemplateOptions* options, std::vector<TemplateAttribute*> attributes, std::vector<TemplateList*> lists)
/// @brief Constructor that initializes all fields.
/// @param type The type (name) of the element.
/// @param options The options of the element.
/// @param attributes The list of attributes of the element.
/// @param lists The list of lists in the element.
///
/// @fn std::string PLCL::Template::TemplateElement::toString(size_t indent, size_t indentStart)
/// @brief Converts the element to a string.
/// @param indent The number of spaces to indent the element's contents.
/// @param indentStart The number of spaces to indent the whole element.
/// @return The element as a string.
///
/// @struct PLCL::Template::TemplateOptions
/// @brief A struct that represents the options of a template element or list.
/// 
/// @var std::vector<PLCL::Template::TemplateOption*> PLCL::Template::TemplateOptions::options
/// @brief The list of options.
///
/// @fn PLCL::Template::TemplateOptions::TemplateOptions()
/// @brief Default constructor.
///
/// @fn PLCL::Template::TemplateOptions::TemplateOptions(std::vector<Lexer::Token>& tokens, size_t& index)
/// @brief Constructor that parses tokens from the lexer.
/// @param tokens The list of tokens to parse.
/// @param index The index of the current token.
/// @attention This function is for internal use only.
///
/// @fn PLCL::Template::TemplateOptions::TemplateOptions(std::vector<TemplateOption*> options)
/// @brief Constructor that initializes all fields.
/// @param options The list of options.
///
/// @fn std::string PLCL::Template::TemplateOptions::toString(size_t indent, size_t indentStart, OptionsType optionsType)
/// @brief Converts the options to a string.
/// @param indent The number of spaces to indent the options' contents.
/// @param indentStart The number of spaces to indent the whole options.
/// @param optionsType The type of the options.
/// @return The options as a string.
///
/// @struct PLCL::Template::TemplateOption
/// @brief A struct that represents an option of a template element or list.
///
/// @var std::string PLCL::Template::TemplateOption::name 
/// @brief The name of the option.
///
/// @var Generic::ValueType PLCL::Template::TemplateOption::value 
/// @brief The value of the option.
///
/// @fn PLCL::Template::TemplateOption::TemplateOption()
/// @brief Default constructor.
///
/// @fn PLCL::Template::TemplateOption::TemplateOption(std::vector<Lexer::Token>& tokens, size_t& index)
/// @brief Constructor that parses tokens from the lexer.
/// @param tokens The list of tokens to parse.
/// @param index The index of the current token.
/// @attention This function is for internal use only.
///
/// @fn PLCL::Template::TemplateOption::TemplateOption(std::string name, Generic::ValueType value)
/// @brief Constructor that initializes all fields.
/// @param name The name of the option.
/// @param value The value of the option.
///
/// @fn std::string PLCL::Template::TemplateOption::toString(size_t indent)
/// @brief Converts the option to a string.
/// @param indent The number of spaces to indent the option.
/// @return The option as a string.
///
/// @struct PLCL::Template::TemplateAttribute
/// @brief A struct that represents an attribute of a template element.
///
/// @var PLCL::Template::AttributeType PLCL::Template::TemplateAttribute::type
/// @brief The type of the attribute.
///
/// @var std::string PLCL::Template::TemplateAttribute::name
/// @brief The name of the attribute.
///
/// @var std::string* PLCL::Template::TemplateAttribute::defaultValue 
/// @brief The default value of the attribute.
/// @details This is a pointer to allow for a null value.
///
/// @var bool PLCL::Template::TemplateAttribute::required
/// @brief Whether the attribute is required.
/// @details If this is true, the attribute must be present in the configuration.
///
/// @fn PLCL::Template::TemplateAttribute::TemplateAttribute()
/// @brief Default constructor.
///
/// @fn PLCL::Template::TemplateAttribute::TemplateAttribute(std::vector<Lexer::Token>& tokens, size_t& index)
/// @brief Constructor that parses tokens from the lexer.
/// @param tokens The list of tokens to parse.
/// @param index The index of the current token.
/// @attention This function is for internal use only.
///
/// @fn PLCL::Template::TemplateAttribute::TemplateAttribute(AttributeType type, std::string name, std::string* defaultValue, bool required)
/// @brief Constructor that initializes all fields.
/// @param type The type of the attribute.
/// @param name The name of the attribute.
/// @param defaultValue The default value of the attribute.
/// @param required Whether the attribute is required.
///
/// @fn std::string PLCL::Template::TemplateAttribute::toString(size_t indent)
/// @brief Converts the attribute to a string.
/// @param indent The number of spaces to indent the attribute.
/// @return The attribute as a string.

#pragma once
#include <string>
#include <vector>

#include "Generic.hpp"
#include "Lexer.hpp"

namespace PLCL::Template {
    enum class AttributeType {
        String,
        Integer,
        Float,
        Boolean
    };

    enum class OptionsType {
        Element,
        List
    };

    std::string attributeTypeToString(AttributeType type);

    struct TemplateRoot;
    struct TemplateList;
    struct TemplateListElement;
    struct TemplateElement;
    struct TemplateOptions;
    struct TemplateOption;
    struct TemplateAttribute;

    struct TemplateRoot {
        std::string name;
        std::vector<TemplateElement*> elements;
        std::vector<TemplateList*> lists;

        TemplateRoot() = default;
        explicit TemplateRoot(std::vector<Lexer::Token>& tokens);
        TemplateRoot(std::string name, std::vector<TemplateElement*> elements, std::vector<TemplateList*> lists)
            : name(std::move(name)), elements(std::move(elements)), lists(std::move(lists)) {};

        [[maybe_unused]] static TemplateRoot fromString(const std::string& input);
        [[maybe_unused]] std::string toString(size_t indent);
    };

    struct TemplateList {
        std::string type;
        TemplateOptions* options = nullptr;
        std::vector<TemplateListElement*> elements;

        TemplateList() = default;
        TemplateList(std::vector<Lexer::Token>& tokens, size_t& index);
        TemplateList(std::string type, TemplateOptions* options, std::vector<TemplateListElement*> elements)
            : type(std::move(type)), options(options), elements(std::move(elements)) {};

        [[maybe_unused]] std::string toString(size_t indent, size_t indentStart);
    };

    struct TemplateListElement {
        size_t id = {};
        TemplateElement* element = nullptr; 

        TemplateListElement() = default;
        TemplateListElement(std::vector<Lexer::Token>& tokens, size_t& index);
        TemplateListElement(size_t id, TemplateElement* element)
            : id(id), element(element) {};

        [[maybe_unused]] std::string toString(size_t indent, size_t indentStart);
    };

    struct TemplateElement {
        std::string type;
        TemplateOptions* options = nullptr;
        std::vector<TemplateAttribute*> attributes;
        std::vector<TemplateList*> lists;

        TemplateElement() = default;
        TemplateElement(std::vector<Lexer::Token>& tokens, size_t& index);
        TemplateElement(std::string type, TemplateOptions* options, std::vector<TemplateAttribute*> attributes, std::vector<TemplateList*> lists)
            : type(std::move(type)), options(options), attributes(std::move(attributes)), lists(std::move(lists)) {};

        [[maybe_unused]] std::string toString(size_t indent, size_t indentStart);
    };

    struct TemplateOptions {
        std::vector<TemplateOption*> options;

        TemplateOptions() = default;
        TemplateOptions(std::vector<Lexer::Token>& tokens, size_t& index);
        explicit TemplateOptions(std::vector<TemplateOption*> options)
            : options(std::move(options)) {};

        [[maybe_unused]] std::string toString(size_t indent, size_t indentStart, OptionsType optionsType);
    };

    struct TemplateOption {
        std::string name;
        Generic::ValueType value;

        TemplateOption() = default;
        TemplateOption(std::vector<Lexer::Token>& tokens, size_t& index);
        TemplateOption(std::string name, Generic::ValueType value)
            : name(std::move(name)), value(std::move(value)) {};

        [[maybe_unused]] std::string toString(size_t indent);
    };

    struct TemplateAttribute {
        AttributeType type;
        std::string name;
        std::string* defaultValue = nullptr;
        bool required = false;

        TemplateAttribute() = default;
        TemplateAttribute(std::vector<Lexer::Token>& tokens, size_t& index);
        TemplateAttribute(AttributeType type, std::string name, std::string* defaultValue, bool required)
            : type(type), name(std::move(name)), defaultValue(defaultValue), required(required) {};

        [[maybe_unused]] std::string toString(size_t indent);
    };

}
