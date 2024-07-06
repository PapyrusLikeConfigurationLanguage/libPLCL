// SPDX-License-Identifier: Apache-2.0

#pragma once
#include <cctype>
#include <string_view>
#include <algorithm>
#include <variant>
#include <stdexcept>
#include <sstream>

namespace PapyrusLikeConfigurationLanguage::Generic {
    using ValueType = std::variant<std::string, int64_t, double, bool>;

    inline static bool iequals(std::string_view lhs, std::string_view rhs) {
        return std::ranges::equal(lhs, rhs, [](unsigned char a, unsigned char b) {
            return std::tolower(a) == std::tolower(b);
        });
    }

    inline static std::runtime_error genericExpectedError(std::string_view expected, std::string_view found, size_t line, size_t column) {
        return std::runtime_error("Expected " + std::string(expected) + " but found " + std::string(found) + " at line " + std::to_string(line) + " column " + std::to_string(column));
    }
}
