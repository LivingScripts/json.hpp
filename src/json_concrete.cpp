#include "json_concrete.hpp"

json::JsonValue json::JsonValue::make_array(std::initializer_list<json::JsonValue> e) {
    return json::JsonValue(e);
}

json::JsonValue json::JsonValue::make_object(Entries e) {
    std::map<std::string, json::JsonValue> tmp;
    for(auto entry: e) {
        tmp.insert(static_cast<std::pair<std::string, json::JsonValue>>(entry));
    }
    return json::JsonValue(tmp);
}

json::JsonValue::JsonValue(std::initializer_list<json::JsonValue> il):
        data(json::core::make_value_ptr< JsonStorage<Array> >(il))
{ }

json::JsonValue::JsonValue(std::map<std::string, JsonValue> obj) {
    data = std::move(std::make_unique< JsonStorage<Object> >(obj));
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

json::JsonValue& json::JsonValue::operator[](std::string const &key) {
    if(!data) throw std::runtime_error("null object is not subsciptable");
    JsonStorage<Object> *pval = dynamic_cast<JsonStorage<Object>*> (data.get());
    if(!pval) {
        throw std::runtime_error("value type not subscriptable");
    } else {
        return (pval->value).at(key);
    }
}

json::JsonValue const& json::JsonValue::operator[](std::string const &key) const {
    if(!data) throw std::runtime_error("null object is not subsciptable");
    JsonStorage<Object> const *pval = dynamic_cast<JsonStorage<Object>*> (data.get());
    if(!pval) {
        throw std::runtime_error("value type not subscriptable");
    } else {
        return (pval->value).at(key);
    }
}

json::JsonValue& json::JsonValue::operator[](size_t const &idx) {
    if(!data) throw std::runtime_error("null object is not subscriptable");
    JsonStorage<Array> *pval = dynamic_cast<JsonStorage<Array>*> (data.get());
    if(!pval) {
        throw std::runtime_error("value type not subscriptable");
    } else {
        return (pval->value).at(idx);
    }
}

json::JsonValue const& json::JsonValue::operator[](size_t const &idx) const {
    if(!data) throw std::runtime_error("null object is not subscriptable");
    JsonStorage<Array> const *pval = dynamic_cast<JsonStorage<Array>*> (data.get());
    if(!pval) {
        throw std::runtime_error("value type not subscriptable");
    } else {
        return (pval->value).at(idx);
    }
}

std::string json::toJsonString(std::map<std::string, json::JsonValue> const &map) {
    std::string str = "{";
    auto start = map.cbegin();
    auto end = map.cend();
    str += (json::addQuotes(start->first) + ":" + start->second.toString()); // sparing an if inside the loop
    while(++start != end) {
        str += ("," + json::addQuotes(start->first) + ":" + start->second.toString());
    }
    return str + "}";
}

std::string json::toJsonString(std::vector<JsonValue> const &arr) {
    std::stringstream ss;
    auto curr = arr.cbegin();
    auto end = arr.cend();
    ss << "[" << curr->toString(); // sparing an if inside the loop
    while(++curr != end) {
        ss << "," << curr->toString();
    }
    ss << "]";
    return ss.str();
}