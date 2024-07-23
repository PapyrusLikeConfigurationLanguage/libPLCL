// SPDX-License-Identifier: Apache-2.0

/// @file
/// @brief Generic utilities
/// @attention This file is not meant to be included by the end user.
///
/// @namespace PLCL::Generic
/// @brief Generic utilities
///
/// @var PLCL::Generic::float64_t
/// @brief The 64-bit floating point type.
/// @details It's either `std::float64_t` or `double` depending on the compiler's support for the former.
///
/// @var PLCL::Generic::ValueType
/// @brief A variant type that can hold a string, an integer, a floating point number, or a boolean.
/// @details It's used to store the value of a key-value pair in a configuration file.
///
/// @fn PLCL::Generic::iequals
/// @brief A function for comparing two strings in a case-insensitive manner.
/// @param lhs The first string to compare.
/// @param rhs The second string to compare.
/// @returns `true` if the strings are equal, `false` otherwise.
///
/// @fn PLCL::Generic::genericExpectedError
/// @brief A function for creating a `std::runtime_error` with a message about an expected value.
/// @param expected The expected value.
/// @param found The found value.
/// @param line The line number where the error occurred.
/// @param column The column number where the error occurred.
/// @returns A `std::runtime_error` with the message "Expected `expected` but found `found` at line `line` column `column`".
/// @note This function is used by the parser to create error messages when an expected value is not found.

#pragma once
#include <algorithm>
#include <cctype>
#include <cmath>
#include <stdexcept>
#include <stdfloat>
#include <string_view>
#include <variant>

namespace PLCL::Generic {
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
