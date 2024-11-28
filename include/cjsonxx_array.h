#pragma once

#include "cjsonxx_base.h"

class cjsonxx_object;

class cjsonxx_array : public cjsonxx_base {
     public:
    cjsonxx_array(void);

     public:
    /**
     * @brief 转移json树，json对象控制权交由调用者，当前对象的root_会置空
     * @return cJSON*
     */
    cJSON *move(void) const;

     public:
    /**
     * @brief 解析json字符串，如果解析成功，而且是json数组，当前对象的root_会指向解析后的json树
     * @param data json字符串
     * @return true 成功
     * @return false 失败
     */
    bool parse(const char *json);

     public:
    /**
     * @brief 获取json数组的大小
     */
    int get_size(void) const;

     public:
    /**
     * @brief 获取json数组中指定索引的整数值
     */
    int get_int(int index) const;

     public:
    /**
     * @brief 获取json数组中指定索引的bool值
     */
    bool get_bool(int index) const;

     public:
    /**
     * @brief 获取json数组中指定索引的浮点值
     */
    double get_float(int index) const;

     public:
    /**
     * @brief 获取json数组中指定索引的字符串值
     */
    const char *get_string(int index) const;

     public:
    bool add_int(int value);
    bool add_bool(bool value);
    bool add_float(double value, uint8_t precision);
    bool add_string(const char *value);
    bool add_object(const cjsonxx_object &obj);
    bool add_array(const cjsonxx_array &arr);
    bool add_null(void);

     public:
    inline bool set_int(int value)
    {
        return add_int(value);
    }
    inline bool set_bool(bool value)
    {
        return add_bool(value);
    }
    inline bool set_float(double value, uint8_t precision = 4)
    {
        return add_float(value, precision);
    }
    inline bool set_string(const char *value)
    {
        return add_string(value);
    }
    inline bool set_object(const cjsonxx_object &obj)
    {
        return add_object(obj);
    }
    inline bool set_array(const cjsonxx_array &arr)
    {
        return add_array(arr);
    }
};