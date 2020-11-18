#pragma once

#include "json_memory.hpp"

namespace json {
    namespace core {
        template<typename T>
        std::string to_json_string(T const&) = delete;

        class JsonData {
        public:
            virtual std::string to_string() const = 0;
            virtual std::unique_ptr<JsonData> clone() const = 0;
            virtual ~JsonData() = default;
        };

        template<typename T>
        class JsonStorage: public JsonData {
        public:
            T value;

            std::string to_string() const final {
                return to_json_string(value);
            }

            JsonStorage() = default;
            JsonStorage(JsonStorage const&) = default;
            JsonStorage(JsonStorage const&&) = default;
            JsonStorage& operator=(JsonStorage const&) = default;
            JsonStorage& operator=(JsonStorage const&&) = default;

        // take owner ship of the initializer object
            JsonStorage(T o):
                    value(std::move(o))
            { }

            std::unique_ptr<JsonData> clone() const final {
                return std::unique_ptr<JsonStorage>(new JsonStorage(*this));
            }
        };
    }
}
