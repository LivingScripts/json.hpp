#include <type_traits>

#ifndef JSON_TYPE_TRAITS_HPP
#define JSON_TYPE_TRAITS_HPP

namespace json {
/*
* defaults to false type for any type T without a member named clone
*/
    template<typename T, class=void>
    struct cloneable : std::false_type { };

/*
* if type T has a method named clone, it is a true type
*/
    template<typename T>
    struct cloneable<T, decltype(void(&T::clone))> : std::true_type { };
}

#endif //JSON_TYPE_TRAITS_HPP
