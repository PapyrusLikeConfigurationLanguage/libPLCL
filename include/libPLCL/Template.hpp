// SPDX-License-Identifier: Apache-2.0

/// @file
/// @brief Parsing into a template tree.
/// @attention This file is not meant to be included by the end user.
///
/// @namespace PapyrusLikeConfigurationLanguage::Template 
/// @brief The namespace for the template tree.
///
/// @enum PapyrusLikeConfigurationLanguage::Template::Type
/// @brief The type of a template attribute.
///
/// @fn std::string PapyrusLikeConfigurationLanguage::Template::typeToString(Type type)
/// @brief Converts a type to a string.
/// @param type The type to convert.
/// @return The string representation of the type.
///
/// @struct PapyrusLikeConfigurationLanguage::Template::TemplateRoot
/// @brief A struct that represents the root of a template tree.
///
/// @var std::string PapyrusLikeConfigurationLanguage::Template::TemplateRoot::name 
/// @brief The name of the template.
///
/// @var std::vector<PapyrusLikeConfigurationLanguage::Template::TemplateElement*> PapyrusLikeConfigurationLanguage::Template::TemplateRoot::elements
/// @brief The list of elements in the top level of the template.
///
/// @var std::vector<PapyrusLikeConfigurationLanguage::Template::TemplateList*> PapyrusLikeConfigurationLanguage::Template::TemplateRoot::lists
/// @brief The list of lists in the top level of the template.
///
/// @fn PapyrusLikeConfigurationLanguage::Template::TemplateRoot::TemplateRoot()
/// @brief Default constructor.
///
/// @fn PapyrusLikeConfigurationLanguage::Template::TemplateRoot::TemplateRoot(std::vector<Lexer::Token>& tokens)
/// @brief Constructor that parses tokens from the lexer.
/// @param tokens The list of tokens to parse.
///
/// @fn PapyrusLikeConfigurationLanguage::Template::TemplateRoot::TemplateRoot(std::string name, std::vector<TemplateElement*> elements, std::vector<TemplateList*> lists)
/// @brief Constructor that initializes all fields.
///
/// @fn PapyrusLikeConfigurationLanguage::Template::TemplateRoot PapyrusLikeConfigurationLanguage::Template::TemplateRoot::fromString(const std::string& input)
/// @brief Parses a template from a string. 
/// @param input The string to parse.
/// @return The parsed template.
///
/// @struct PapyrusLikeConfigurationLanguage::Template::TemplateList
/// @brief A struct that represents a list in the template tree.
/// @details It's used to store a list of elements in the template.
///
/// @var std::string PapyrusLikeConfigurationLanguage::Template::TemplateList::type
/// @brief The type (name) of the list.
///
/// @var PapyrusLikeConfigurationLanguage::Template::TemplateOptions* PapyrusLikeConfigurationLanguage::Template::TemplateList::options
/// @brief The options of the list.
///
/// @var std::vector<PapyrusLikeConfigurationLanguage::Template::TemplateListElement*> PapyrusLikeConfigurationLanguage::Template::TemplateList::elements
/// @brief The list of elements in the list.
///
/// @fn PapyrusLikeConfigurationLanguage::Template::TemplateList::TemplateList()
/// @brief Default constructor.
///
/// @fn PapyrusLikeConfigurationLanguage::Template::TemplateList::TemplateList(std::vector<Lexer::Token>& tokens, size_t& index)
/// @brief Constructor that parses tokens from the lexer.
/// @param tokens The list of tokens to parse.
/// @param index The index of the current token.
/// @attention This function is for internal use only.
///
/// @fn PapyrusLikeConfigurationLanguage::Template::TemplateList::TemplateList(std::string type, TemplateOptions* options, std::vector<TemplateListElement*> elements)
/// @brief Constructor that initializes all fields.
/// @param type The type (name) of the list.
/// @param options The options of the list.
/// @param elements The list of elements in the list.
///
/// @struct PapyrusLikeConfigurationLanguage::Template::TemplateListElement
/// @brief A struct that represents an element in a list in the template tree.
/// @details It's done this way to represent the structure of a template as closely as possible.
///
/// @var size_t PapyrusLikeConfigurationLanguage::Template::TemplateListElement::id 
/// @brief The id of the element.
///
/// @var PapyrusLikeConfigurationLanguage::Template::TemplateElement* PapyrusLikeConfigurationLanguage::Template::TemplateListElement::element
/// @brief The element in the list.
/// 
/// @fn PapyrusLikeConfigurationLanguage::Template::TemplateListElement::TemplateListElement()
/// @brief Default constructor.
///
/// @fn PapyrusLikeConfigurationLanguage::Template::TemplateListElement::TemplateListElement(std::vector<Lexer::Token>& tokens, size_t& index)
/// @brief Constructor that parses tokens from the lexer.
/// @param tokens The list of tokens to parse.
/// @param index The index of the current token.
/// @attention This function is for internal use only.
///
/// @fn PapyrusLikeConfigurationLanguage::Template::TemplateListElement::TemplateListElement(size_t id, TemplateElement* element)
/// @brief Constructor that initializes all fields.
/// @param id The id of the element.
/// @param element The element in the list.
///
/// @struct PapyrusLikeConfigurationLanguage::Template::TemplateElement
/// @brief A struct that represents an element in the template tree.
/// 
/// @var std::string PapyrusLikeConfigurationLanguage::Template::TemplateElement::type 
/// @brief The type (name) of the element.
///
/// @var PapyrusLikeConfigurationLanguage::Template::TemplateOptions* PapyrusLikeConfigurationLanguage::Template::TemplateElement::options 
/// @brief The options of the element.
///
/// @var std::vector<PapyrusLikeConfigurationLanguage::Template::TemplateAttribute*> PapyrusLikeConfigurationLanguage::Template::TemplateElement::attributes 
/// @brief The list of attributes of the element.
///
/// @var std::vector<PapyrusLikeConfigurationLanguage::Template::TemplateList*> PapyrusLikeConfigurationLanguage::Template::TemplateElement::lists
/// @brief The list of lists in the element.
///
/// @fn PapyrusLikeConfigurationLanguage::Template::TemplateElement::TemplateElement()
/// @brief Default constructor.
///
/// @fn PapyrusLikeConfigurationLanguage::Template::TemplateElement::TemplateElement(std::vector<Lexer::Token>& tokens, size_t& index)
/// @brief Constructor that parses tokens from the lexer.
/// @param tokens The list of tokens to parse.
/// @param index The index of the current token.
/// @attention This function is for internal use only.
///
/// @fn PapyrusLikeConfigurationLanguage::Template::TemplateElement::TemplateElement(std::string type, TemplateOptions* options, std::vector<TemplateAttribute*> attributes, std::vector<TemplateList*> lists)
/// @brief Constructor that initializes all fields.
/// @param type The type (name) of the element.
/// @param options The options of the element.
/// @param attributes The list of attributes of the element.
/// @param lists The list of lists in the element.
///
/// @struct PapyrusLikeConfigurationLanguage::Template::TemplateOptions
/// @brief A struct that represents the options of a template element or list.
/// 
/// @var std::vector<PapyrusLikeConfigurationLanguage::Template::TemplateOption*> PapyrusLikeConfigurationLanguage::Template::TemplateOptions::options
/// @brief The list of options.
///
/// @fn PapyrusLikeConfigurationLanguage::Template::TemplateOptions::TemplateOptions()
/// @brief Default constructor.
///
/// @fn PapyrusLikeConfigurationLanguage::Template::TemplateOptions::TemplateOptions(std::vector<Lexer::Token>& tokens, size_t& index)
/// @brief Constructor that parses tokens from the lexer.
/// @param tokens The list of tokens to parse.
/// @param index The index of the current token.
/// @attention This function is for internal use only.
///
/// @fn PapyrusLikeConfigurationLanguage::Template::TemplateOptions::TemplateOptions(std::vector<TemplateOption*> options)
/// @brief Constructor that initializes all fields.
/// @param options The list of options.
///
/// @struct PapyrusLikeConfigurationLanguage::Template::TemplateOption
/// @brief A struct that represents an option of a template element or list.
///
/// @var std::string PapyrusLikeConfigurationLanguage::Template::TemplateOption::name 
/// @brief The name of the option.
///
/// @var Generic::ValueType PapyrusLikeConfigurationLanguage::Template::TemplateOption::value 
/// @brief The value of the option.
///
/// @fn PapyrusLikeConfigurationLanguage::Template::TemplateOption::TemplateOption()
/// @brief Default constructor.
///
/// @fn PapyrusLikeConfigurationLanguage::Template::TemplateOption::TemplateOption(std::vector<Lexer::Token>& tokens, size_t& index)
/// @brief Constructor that parses tokens from the lexer.
/// @param tokens The list of tokens to parse.
/// @param index The index of the current token.
/// @attention This function is for internal use only.
///
/// @fn PapyrusLikeConfigurationLanguage::Template::TemplateOption::TemplateOption(std::string name, Generic::ValueType value)
/// @brief Constructor that initializes all fields.
/// @param name The name of the option.
/// @param value The value of the option.
///
/// @struct PapyrusLikeConfigurationLanguage::Template::TemplateAttribute
/// @brief A struct that represents an attribute of a template element.
///
/// @var PapyrusLikeConfigurationLanguage::Template::Type PapyrusLikeConfigurationLanguage::Template::TemplateAttribute::type 
/// @brief The type of the attribute.
///
/// @var std::string PapyrusLikeConfigurationLanguage::Template::TemplateAttribute::name
/// @brief The name of the attribute.
///
/// @var std::string* PapyrusLikeConfigurationLanguage::Template::TemplateAttribute::defaultValue 
/// @brief The default value of the attribute.
/// @details This is a pointer to allow for a null value.
///
/// @var bool PapyrusLikeConfigurationLanguage::Template::TemplateAttribute::required
/// @brief Whether the attribute is required.
/// @details If this is true, the attribute must be present in the configuration.
///
/// @fn PapyrusLikeConfigurationLanguage::Template::TemplateAttribute::TemplateAttribute()
/// @brief Default constructor.
///
/// @fn PapyrusLikeConfigurationLanguage::Template::TemplateAttribute::TemplateAttribute(std::vector<Lexer::Token>& tokens, size_t& index)
/// @brief Constructor that parses tokens from the lexer.
/// @param tokens The list of tokens to parse.
/// @param index The index of the current token.
/// @attention This function is for internal use only.
///
/// @fn PapyrusLikeConfigurationLanguage::Template::TemplateAttribute::TemplateAttribute(Type type, std::string name, std::string* defaultValue, bool required)
/// @brief Constructor that initializes all fields.
/// @param type The type of the attribute.
/// @param name The name of the attribute.
/// @param defaultValue The default value of the attribute.
/// @param required Whether the attribute is required.

#pragma once
#include <string>
#include <vector>

#include "Generic.hpp"
#include "Lexer.hpp"

namespace PapyrusLikeConfigurationLanguage::Template {
    enum class Type {
        String,
        Integer,
        Float,
        Boolean
    };

    std::string typeToString(Type type);

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
    };

    struct TemplateList {
        std::string type;
        TemplateOptions* options = nullptr;
        std::vector<TemplateListElement*> elements;

        TemplateList() = default;
        TemplateList(std::vector<Lexer::Token>& tokens, size_t& index);
        TemplateList(std::string type, TemplateOptions* options, std::vector<TemplateListElement*> elements)
            : type(std::move(type)), options(options), elements(std::move(elements)) {};
    };

    struct TemplateListElement {
        size_t id = {};
        TemplateElement* element = nullptr; 

        TemplateListElement() = default;
        TemplateListElement(std::vector<Lexer::Token>& tokens, size_t& index);
        TemplateListElement(size_t id, TemplateElement* element)
            : id(id), element(element) {};
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
    };

    struct TemplateOptions {
        std::vector<TemplateOption*> options;

        TemplateOptions() = default;
        TemplateOptions(std::vector<Lexer::Token>& tokens, size_t& index);
        explicit TemplateOptions(std::vector<TemplateOption*> options)
            : options(std::move(options)) {};
    };

    struct TemplateOption {
        std::string name;
        Generic::ValueType value;

        TemplateOption() = default;
        TemplateOption(std::vector<Lexer::Token>& tokens, size_t& index);
        TemplateOption(std::string name, Generic::ValueType value)
            : name(std::move(name)), value(std::move(value)) {};
    };

    struct TemplateAttribute {
        Type type;
        std::string name;
        std::string* defaultValue = nullptr;
        bool required = false;

        TemplateAttribute() = default;
        TemplateAttribute(std::vector<Lexer::Token>& tokens, size_t& index);
        TemplateAttribute(Type type, std::string name, std::string* defaultValue, bool required)
            : type(type), name(std::move(name)), defaultValue(defaultValue), required(required) {};
    };

}
