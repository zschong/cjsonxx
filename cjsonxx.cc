#include "cjsonxx.h"

#ifdef CJSONXX_TEST
#include <iostream>


void test_json_parse(void) {
    const char *jstr = "[{\"name\":\"cjsonxx\",\"age\":18,\"is_student\":true},{\"name\":\"cjsonxx\",\"age\":18,\"is_student\":true},{\"name\":\"cjsonxx\",\"age\":18,\"is_student\":true},{\"name\":\"cjsonxx\",\"age\":18,\"is_student\":true},{\"name\":\"cjsonxx\",\"age\":18,\"is_student\":true},{\"name\":\"cjsonxx\",\"age\":18,\"is_student\":true},{\"name\":\"cjsonxx\",\"age\":18,\"is_student\":true},{\"name\":\"cjsonxx\",\"age\":18,\"is_student\":true},{\"name\":\"cjsonxx\",\"age\":18,\"is_student\":true},{\"name\":\"cjsonxx\",\"age\":18,\"is_student\":true}]";
    cjsonxx_array arr;
    arr.parse(jstr);
    std::cout << arr.to_string_pretty() << std::endl;
}

int main(void) {
    cjsonxx_object obj;
    cjsonxx_array arr;

    obj.add_string("name", "cjsonxx");
    obj.add_int("age", 18);
    obj.add_bool("is_student", true);

    for (int i = 0; i < 3; i++) {
        arr.add_object(obj);
    }

    std::cout << obj.to_string() << std::endl;
    std::cout << obj.to_string_pretty() << std::endl;
    std::cout << arr.to_string_pretty() << std::endl;
    std::cout << arr.data() << std::endl;
    std::cout << arr.length() << std::endl;
    std::cout << arr.encode() << std::endl;

    test_json_parse();
    return 0;
}
#endif  // CJSONXX_TEST
