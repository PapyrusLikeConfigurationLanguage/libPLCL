#include <cstdint>
#include <iostream>
#include <variant>
#include <libPLCL.hpp>

#define EXAMPLE R"(
ConfigName examplethingy

Import "thingy" 
Import "another thingy" 

ConfigElement ExampleElement 
    a = "string" 
    b = 123 
    c = 3.14 
    d = true 
    ConfigList InnerElements 
        ConfigListElement 0 
            ConfigElement InnerElement 
                hi = "uwu" 
            endConfigElement 
        endConfigListElement 
    endConfigList 
endConfigElement 

ConfigList TopLevelList 
    ConfigListElement 0 
        ConfigElement ElementInList 
            attribute = "value" 
        endConfigElement 
    endConfigListElement 
    ConfigListElement 1 
        ConfigElement ElementInList 
            attribute = "value2" 
        endConfigElement 
    endConfigListElement 
endConfigList 
)"

void printConfigElement(PLCL::Config::ConfigElement& element, size_t indent);

std::string valueTypeToString(PLCL::Generic::ValueType& value) {
    if (std::holds_alternative<std::string>(value)) {
        return std::get<std::string>(value);
    }
    if (std::holds_alternative<int64_t>(value)) {
        return std::to_string(std::get<int64_t>(value));
    }
    if (std::holds_alternative<PLCL::Generic::float64_t>(value)) {
        return std::to_string(std::get<PLCL::Generic::float64_t>(value));
    }
    if (std::holds_alternative<bool>(value)) {
        return std::get<bool>(value) ? "true" : "false";
    }
    return "Unreachable";
}

void printIndent(size_t indent) {
    for (size_t i = 0; i < indent; i++) {
        std::cout << ' ';
    }
}

void printList(PLCL::Config::ConfigList& list, size_t indent) {
    printIndent(indent);
    std::cout << "List " << list.type << '\n';
    indent += 4;
    for (auto& element : list.elements) {
        printIndent(indent);
        std::cout << "ListElement " << element->id << '\n';
        indent += 4;
        printConfigElement(*element->element, indent);
    }
}

void printConfigElement(PLCL::Config::ConfigElement& element, size_t indent) {
    printIndent(indent);
    std::cout << "Element " << element.type << '\n';
    indent += 4;
    for (auto& attribute : element.attributes) {
        printIndent(indent);
        std::cout << attribute->name << " = " << valueTypeToString(attribute->value) << '\n';
    }
    for (auto& list : element.lists) {
        printList(*list, indent);
    }
    indent -= 4;
}

int main() {
    PLCL::Config::ConfigRoot config = PLCL::Config::ConfigRoot::fromString(EXAMPLE);
    std::cout << "Config Name: " << config.name << '\n';
    for (auto& import : config.imports) {
        std::cout << "Import: " << import << '\n';
    }
    for (auto& element : config.elements) {
        printConfigElement(*element, 0);
    }
    for (auto& list : config.lists) {
        printList(*list, 0);
    }
    return 0;
}
