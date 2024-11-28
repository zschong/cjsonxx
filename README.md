# cjson的c++封装
- `cjsonxx_base`   json基础操作（解析、序列化、克隆等）
- `cjsonxx_array`  json数组
- `cjsonxx_object` json对象

# 用法
```c++
#include <stdio.h>
#include "cjsonxx.h"

int main(void) {
    cjsonxx_array arr;
    cjsonxx_object obj;

    obj.set_string("name", "xiaoming");
    obj.set_int("age", 20);
    obj.set_string("job", "coder");

    for (int i = 0; i < 3; i++) {
        arr.add_object(obj);
    }

    printf("%s", arr.to_string());

    return 0;
}
```
