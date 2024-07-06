// SPDX-License-Identifier: Apache-2.0

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
        std::vector<TemplateElement*> elements;

        TemplateListElement() = default;
        TemplateListElement(std::vector<Lexer::Token>& tokens, size_t& index);
        TemplateListElement(size_t id, std::vector<TemplateElement*> elements)
            : id(id), elements(std::move(elements)) {};
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
