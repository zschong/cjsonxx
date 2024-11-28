#pragma once

#include "cjsonxx_base.h"

class cjsonxx_array;

class cjsonxx_object : public cjsonxx_base {
     public:
    cjsonxx_object(void);

     public:
    cJSON *move(void) const;

     public:
    /**
     * @brief 解析json字符串，如果解析成功，而且是json对象，当前对象的root_会指向解析后的json树
     * @param data json字符串
     * @return true 成功
     * @return false 失败
     */
    bool parse(const char *json);

     public:
    /**
     * @brief 判断key节点是否存在
     * @param key 节点名称
     * @return true 存在
     * @return false 不存在
     */
    bool find(const char *key) const;

     public:
    /**
     * @brief 删除key节点
     * @param key 节点名称
     * @return true 成功
     * @return false 失败
     */
    bool remove(const char *key);

     public:
    int         get_int(const char *key) const;
    bool        get_bool(const char *key) const;
    double      get_float(const char *key) const;
    const char *get_string(const char *key) const;
    bool        get_object(const char *key, cjsonxx_object &obj) const;
    bool        get_array(const char *key, cjsonxx_array &arr) const;

     public:
    bool add_int(const char *key, int value);
    bool add_bool(const char *key, bool value);
    bool add_float(const char *key, double value, uint8_t precision);
    bool add_string(const char *key, const char *value);
    bool add_object(const char *key, const cjsonxx_object &obj);
    bool add_array(const char *key, const cjsonxx_array &arr);

     public:
    inline bool set_int(const char *key, int value)
    {
        return add_int(key, value);
    }
    inline bool set_bool(const char *key, bool value)
    {
        return add_bool(key, value);
    }
    inline bool set_float(const char *key, double value, uint8_t precision = 4)
    {
        return add_float(key, value, precision);
    }
    inline bool set_string(const char *key, const char *value)
    {
        return add_string(key, value);
    }
    inline bool set_object(const char *key, const cjsonxx_object &obj)
    {
        return add_object(key, obj);
    }
    inline bool set_array(const char *key, const cjsonxx_array &arr)
    {
        return add_array(key, arr);
    }
};