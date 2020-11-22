#include "json_concrete.hpp"

std::string json::toJsonString(json::array const &arr) {
        std::stringstream ss;

        auto curr = arr.begin();
        auto end = arr.end();
        ss << "[" << curr->toString();
        while(++curr != end) {
            ss << "," << curr->toString();
        }
        ss << "]";
        return ss.str();
    }

json::JsonValue::operator bool() {
    return static_cast<bool>(data);
}

std::string json::JsonValue::toString() const {
    if(!data) {
        return "null";
    } else {
        return data->toString();
    }
}

json::JsonValue::JsonValue(int i):
        data(json::core::make_value_ptr< JsonStorage<int> >(i))
{ }

json::JsonValue::JsonValue(long l):
        data(json::core::make_value_ptr< JsonStorage<long> >(l))
{ }

json::JsonValue::JsonValue(double d):
        data(json::core::make_value_ptr< JsonStorage<double> >(d))
{ }
json::JsonValue::JsonValue(std::string s):
        data(json::core::make_value_ptr< JsonStorage<std::string> >(s))
{ }
json::JsonValue::JsonValue(char const *s):
        data(json::core::make_value_ptr< JsonStorage<std::string> >(s))
{ }
json::JsonValue::JsonValue(std::initializer_list<JsonValue> il):
        data(json::core::make_value_ptr< JsonStorage<array> >(il))
{ }