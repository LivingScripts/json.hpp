#pragma once

#include <iomanip>

#include "json_memory.hpp"
#include "../utils.hpp"

namespace json {
    namespace core {
        template<typename T>
        inline std::string toJsonString(T const&) = delete;
        inline std::string toJsonString(int const &i) {
            std::stringstream ss;
            ss << i;
            return ss.str();
        }

        inline std::string toJsonString(long const &l) {
            std::stringstream ss;
            ss << l;
            return ss.str();
        }

        inline std::string toJsonString(double const &d) {
            std::stringstream ss;
            ss << std::setprecision(16) << d;
            return ss.str();
        }

        inline std::string toJsonString(std::string const &s) {
            return json::addQuotes(s);
        }

        class JsonData {
        public:
            virtual std::string toString() const = 0;
            virtual std::unique_ptr<JsonData> clone() const = 0;
            virtual ~JsonData() = default;
        };

        template<typename T>
        class JsonStorage: public JsonData {
        public:
            T value;

            std::string toString() const final {
                return toJsonString(value);
            }

            JsonStorage() = default;
            JsonStorage(JsonStorage const&) = default;
            JsonStorage(JsonStorage &&) = default;
            JsonStorage& operator=(JsonStorage const&) = default;
            JsonStorage& operator=(JsonStorage &&) = default;

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
