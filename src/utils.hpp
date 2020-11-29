#pragma once

#include <string>

namespace json {
    inline std::string addQuotes(std::string key) {
        return "\\\"" + key + "\\\"";
    }
}