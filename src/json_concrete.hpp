#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <utility>
#include <string>
#include <initializer_list>
#include <iostream>

#include "core/json_abstract.hpp"

namespace json {

    struct JsonValue {
    private:
        template<typename T>
        using JsonStorage = json::core::JsonStorage<T>;
        using Entries = std::initializer_list<std::pair<std::string, JsonValue>>;
        using Object = std::map<std::string, JsonValue>;
        using Array = std::vector<JsonValue>;

        using value_ptr = json::core::value_ptr<json::core::JsonData>;
        value_ptr data;

        JsonValue(std::map<std::string, JsonValue>);

    public:
        JsonValue(std::initializer_list<JsonValue>);

        static JsonValue make_array(std::initializer_list<JsonValue>);

        static JsonValue make_object(Entries);

        JsonValue() = default;

        JsonValue(JsonValue const&) = default;

        JsonValue(JsonValue &&) = default;

        JsonValue& operator=(JsonValue const&) = default;

        JsonValue& operator=(JsonValue &&) = default;

        JsonValue& operator[](std::string const&);

        JsonValue const& operator[](std::string const&) const;

        JsonValue(int i);

        JsonValue(long l);

        JsonValue(double d);

        JsonValue(std::string s);

        JsonValue(char const *s);

        JsonValue(Entries);

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
    };

    std::string toJsonString(std::map<std::string, JsonValue> const&);
    std::string toJsonString(std::vector<JsonValue> const&);
} // json