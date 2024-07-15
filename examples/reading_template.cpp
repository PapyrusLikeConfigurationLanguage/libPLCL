#include <cstdint>
#include <iostream>
#include <variant>
#include <libPLCL.hpp>

#define EXAMPLE "\
TemplateName examplethingy \
\
TemplateElement ExampleElement \
    TemplateElementOptions \
        required = true \
    endTemplateElementOptions \
    string a required \
    int b default 321 \
    float c \
    bool d \
    TemplateList InnerElements \
        TemplateListOptions \
            required = true \
            minimumCount = 1 \
            maximumCount = 1 \
        endTemplateListOptions \
        TemplateListElement 0 \
            TemplateElement InnerElement \
                string hi default \":3\" \
            endTemplateElement \
        endTemplateListElement \
    endTemplateList \
endTemplateElement \
\
TemplateList TopLevelList \
    TemplateListElement 2 \
        TemplateElement ElementInList \
            string attribute required \
        endTemplateElement \
    endTemplateListElement \
endTemplateList \
"

using namespace PapyrusLikeConfigurationLanguage;

void printElement(Template::TemplateElement& element, size_t indent);

std::string valueTypeToString(Generic::ValueType& value) {
    if (std::holds_alternative<std::string>(value)) {
        return std::get<std::string>(value);
    }
    if (std::holds_alternative<int64_t>(value)) {
        return std::to_string(std::get<int64_t>(value));
    }
    if (std::holds_alternative<Generic::float64_t>(value)) {
        return std::to_string(std::get<Generic::float64_t>(value));
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

void printOptions(Template::TemplateOptions& options, size_t indent) {
    printIndent(indent);
    std::cout << "Options\n";
    indent += 4;
    for (auto& option : options.options) {
        printIndent(indent);
        std::cout << option->name << " = " << valueTypeToString(option->value) << '\n';
    } 
    indent -= 4;
}

void printList(Template::TemplateList& list, size_t indent) {
    printIndent(indent);
    std::cout << "List " << list.type << '\n';
    indent += 4;
    if (list.options != nullptr) {
        printOptions(*list.options, indent);
    }
    for (auto& element : list.elements) {
        printIndent(indent);
        std::cout << "ListElement " << element->id << '\n';
        indent += 4;
        printElement(*element->element, indent);
    }
}

void printElement(Template::TemplateElement& element, size_t indent) {
    printIndent(indent);
    std::cout << "Element " << element.type << '\n';
    indent += 4;
    if (element.options != nullptr) {
        printOptions(*element.options, indent);
    }
    for (auto& attribute : element.attributes) {
        printIndent(indent);
        std::cout << "Attribute " << attribute->name << ": " << Template::typeToString(attribute->type);
        if (attribute->required) {
            std::cout << " (required)";
        }
        if (attribute->defaultValue) {
            std::cout << " (default: " << *attribute->defaultValue << ")";
        }
        std::cout << '\n';
    }
    for (auto& list : element.lists) {
        printList(*list, indent);
    }
    indent -= 4;
}

int main() {
    Template::TemplateRoot templ = Template::TemplateRoot::fromString(EXAMPLE);
    std::cout << "Template Name: " << templ.name << '\n';
    for (auto& element : templ.elements) {
        printElement(*element, 0);
    }
    for (auto& list : templ.lists) {
        printList(*list, 0);
    }
    return 0;
}
