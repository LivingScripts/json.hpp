# json.hpp

A simple json utility for c++11 and above with a simple interface to create JSON objects without using any types.


```c++
// json value type is available in the following header
#include<src/json_concrete.hpp>
```
Creating Json objects is as simple as creating key value pair lists.
```c++
using namespace json;

// creating a json object
auto obj = JsonValue::make_object({
//  key,   value
    {"pi", 3.141591},
    {"str", "json.hpp"},
            // top level array
    {"arr", {1, "string",
            // nested array
            {"nested arr string", 234324}
        }
    };
});

// creating a json array
auto arr = JsonValue::make_array({1, "string", {"str", 3.14159}});
```

Stringify a any `JsonValue` object with `JsonValue::toString()`.

```c++
std::cout << obj.toString();
std::cout << std::endl;
std::cout << arr.toString();
```
Output:
```
{\"arr\":[1,\"string\",[\"nested arr string\",234324]],\"pi\":3.141591,\"str\":\"json.hpp\"}
[1,\"string\",[\"str\",3.14159]]
```
Javascript like reading and writing of key value in the object.
```c++
obj["pi"] = "my pi value";
```

## Work in progress
* json parser
* more utility functions