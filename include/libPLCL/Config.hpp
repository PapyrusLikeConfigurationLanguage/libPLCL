// SPDX-License-Identifier: Apache-2.0

#pragma once
#include <string>
#include <vector>
#include <variant>
#include "Lexer.hpp"
#include "Template.hpp"

namespace PapyrusLikeConfigurationLanguage::Config {
    struct Config;
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
    };

    struct ConfigList {
        std::string type;
        std::vector<ConfigListElement*> elements;

        ConfigList() = default;
        ConfigList(std::vector<Lexer::Token>& tokens, size_t& index);
        ConfigList(std::string type, std::vector<ConfigListElement*> elements)
            : type(std::move(type)), elements(std::move(elements)) {};
    };

    struct ConfigListElement {
        [[maybe_unused]] size_t id = {};

        ConfigElement* element = nullptr;
        ConfigListElement() = default;
        ConfigListElement(std::vector<Lexer::Token>& tokens, size_t& index);
        ConfigListElement(size_t id, ConfigElement* element)
            : id(id), element(element) {};
    };

    struct ConfigElement {
        std::string type;
        std::vector<ConfigElementAttribute*> attributes;
        std::vector<ConfigList*> lists;

        ConfigElement() = default;
        ConfigElement(std::vector<Lexer::Token>& tokens, size_t& index);
        ConfigElement(std::string type, std::vector<ConfigElementAttribute*> attributes, std::vector<ConfigList*> lists)
            : type(std::move(type)), attributes(std::move(attributes)), lists(std::move(lists)) {};
    };

    struct ConfigElementAttribute {
        std::string name;
        Generic::ValueType value;

        ConfigElementAttribute() = default;
        ConfigElementAttribute(std::vector<Lexer::Token>& tokens, size_t& index);
        ConfigElementAttribute(std::string name, Generic::ValueType value)
            : name(std::move(name)), value(std::move(value)) {};
    };
}
