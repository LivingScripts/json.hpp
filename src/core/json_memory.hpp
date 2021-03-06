#pragma once

#include <memory>

#include "json_type_traits.hpp"

namespace json {
    namespace core {
        namespace {
        // if type T does not have a clone method create a unique_ptr of it
            template<typename T,
                    typename std::enable_if<!json::core::cloneable<T>{}, bool>::type = true>
            std::unique_ptr<T> clone(T const &t) {
                return std::make_unique<T>(t);
            }

        // if type T has clone method return a cloned copy of the object
            template<typename T,
                    typename std::enable_if<json::core::cloneable<T>{}, bool>::type = true>
            std::unique_ptr<T> clone(T const &t) {
                return t.clone();
            }
        } // anon

    /*
    * value_ptr is an ownership (of the heap resource) taking container
    * copy assignment and copy initialization results in cloning of the resource (value semantics)
    * implemented through unique_ptr and clone method of the type T
    */
        template<typename T>
        struct value_ptr: std::unique_ptr<T> {
            using base = std::unique_ptr<T>;
            // what are these declarations
            using base::base;
            using base::operator=;

            value_ptr() = default;
            value_ptr(value_ptr &&) = default;
            value_ptr& operator=(value_ptr &&) = default;

        // handling initialization via subclasses of T
            template<typename X,
                    typename std::enable_if<std::is_base_of<T, X>::value, bool>::type = true>
            value_ptr(value_ptr<X> const &o):
                    base(o ? clone(*o) : nullptr)
            { }

        // template move constructor for subclasses of T
            template<typename X,
                    typename std::enable_if<std::is_base_of<T, X>::value, bool>::type = true>
            value_ptr(value_ptr<X> &&o):
                    base(std::move(o))
            { }

        // initializing with a unique_ptr
            value_ptr(base b):
                    base(std::move(b))
            { }

        // copy constructor
            value_ptr(value_ptr const &o):
                    base(o ? clone(*o) : nullptr)
            { }

        // copy assignment
            value_ptr& operator=(value_ptr const &o) {
                if(!o) {
                    this->reset();
                } else if(this != &o) {
                    auto tmp = clone(*o);
                    swap((base&)*this, tmp);
                }
                return *this;
            }
        };

        template<typename T, class ...Args>
        value_ptr<T> make_value_ptr(Args &&...args) {
            return std::move(
                std::make_unique<T>(std::forward<Args>(args)...)
            );
        }
    } // core
} // json
