#pragma once

#include <vector>
#include <string>
#include <sstream>

#include "core/json_abstract.hpp"

namespace json {

    struct JsonValue {
        JsonValue() = default;

        JsonValue(JsonValue const&) = default;

        JsonValue(JsonValue &&) = default;

        JsonValue& operator=(JsonValue const&) = default;

        JsonValue& operator=(JsonValue &&) = default;

        explicit operator bool();

        std::string toString() const;

        template<typename T>
        T *get() {
            if(!data) return nullptr;
            JsonStorage <T> *pval = dynamic_cast<JsonStorage<T>*>(data.get());
            if(!pval) return nullptr;
            return &(pval->value);
        }

        template<typename T>
        T const *get() const {
            if(!data) return nullptr;
            JsonStorage <T> const *pval = dynamic_cast<JsonStorage<T>*>(data.get());
            if(!pval) return nullptr;
            return &(pval->value);
        }

        JsonValue(int i);

        JsonValue(long l);

        JsonValue(double d);

        JsonValue(std::string s);

        JsonValue(char const *s);

        JsonValue(std::initializer_list<JsonValue> il);

    private:
        template<typename T>
        using JsonStorage = json::core::JsonStorage<T>;

        using value_ptr = json::core::value_ptr<json::core::JsonData>;
        value_ptr data;

    };

    using array = std::vector<JsonValue>;
    std::string toJsonString(array const &arr);
} // json