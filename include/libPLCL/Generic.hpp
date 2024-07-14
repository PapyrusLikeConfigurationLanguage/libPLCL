// SPDX-License-Identifier: Apache-2.0

#pragma once
#include <algorithm>
#include <cctype>
#include <cmath>
#include <stdexcept>
#include <stdfloat>
#include <string_view>
#include <variant>

namespace PapyrusLikeConfigurationLanguage::Generic {
    #if __STDCPP_FLOAT64_T__ == 1
        using float64_t = std::float64_t;
    #else
        #if __STDC_IEC_559__ == 1
            using float64_t = double;
        #else
            #error "No 64-bit floating point type available"
        #endif
    #endif
    
    using ValueType = std::variant<std::string, int64_t, float64_t, bool>;

    inline static bool iequals(std::string_view lhs, std::string_view rhs) {
        return std::ranges::equal(lhs, rhs, [](unsigned char a, unsigned char b) {
            return std::tolower(a) == std::tolower(b);
        });
    }

    inline static std::runtime_error genericExpectedError(std::string_view expected, std::string_view found, size_t line, size_t column) {
        return std::runtime_error("Expected " + std::string(expected) + " but found " + std::string(found) + " at line " + std::to_string(line) + " column " + std::to_string(column));
    }
}
