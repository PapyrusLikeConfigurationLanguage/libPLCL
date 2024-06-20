// SPDX-License-Identifier: Apache-2.0

#ifndef PAPYRUSLIKECONFIGURATIONLANGUAGE_CPP_CONFIG_HPP
#define PAPYRUSLIKECONFIGURATIONLANGUAGE_CPP_CONFIG_HPP

#include <string>
#include <vector>
#include <variant>

#include "Lexer.hpp"
/* #include "Template.hpp" */
#include "Helper.hpp"

namespace PapyrusLikeConfigurationLanguage::Config {
    struct Config;
    struct ConfigList;
    struct ConfigListElement;
    struct ConfigElement;
    struct ConfigElementAttribute;

    struct Config {
        std::string name;
        std::vector<std::string> imports;
        std::vector<ConfigElement*> elements;
        std::vector<ConfigList*> lists;

        Config() = default;
        explicit Config(std::vector<Lexer::Token>& tokens);
        [[maybe_unused]] Config(std::string name, std::vector<std::string> imports, std::vector<ConfigElement*> elements, std::vector<ConfigList*> lists)
            : name(std::move(name)), imports(std::move(imports)), elements(std::move(elements)), lists(std::move(lists)) {};

        [[maybe_unused]] static Config fromString(const std::string& input);
        /* [[maybe_unused]] void verify(Template::Template& configTemplate, bool strict); */
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
        Helper::ValueType value;

        ConfigElementAttribute() = default;
        ConfigElementAttribute(std::vector<Lexer::Token>& tokens, size_t& index);
        ConfigElementAttribute(std::string name, std::variant<std::string, int64_t, bool> value)
            : name(std::move(name)), value(std::move(value)) {};
    };
} // PapyrusLikeConfigurationLanguage

#endif //PAPYRUSLIKECONFIGURATIONLANGUAGE_CPP_CONFIG_HPP
