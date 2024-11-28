#pragma once
#include <stdbool.h>
#include <stdint.h>

#include <string>

#include "cJSON.h"

CJSON_PUBLIC(cJSON *) cJSON_CreateNumberEx(double num, int precision);

class cjsonxx_base {
     protected:
    cJSON      *root_ = nullptr;
    std::string string_;
    std::string pretty_;

     protected:
     /**
      * @brief 析构函数，自动释放root_指向的json树
      */
    ~cjsonxx_base(void);

     protected:
    /**
     * @brief 如果当前json是对象类型，则添加一个键值对
     * @param key 键
     * @param item 值
     * @return true 添加成功
     * @return false 添加失败
     */
    bool add_item(const char *key, cJSON *item);

     protected:
    /**
     * @brief 如果当前json是数组类型，则添加一个元素
     * @param item 值
     * @return true 添加成功
     * @return false 添加失败
     */
    bool add_item(cJSON *item);

     public:
    /**
     * @brief json序列化输出到的字符串
     * @return const char* 字符串指针
     * @return nullptr 失败
     */
    const char *to_string(void) const;

     public:
    /**
     * @brief 格式化输出json字符串, 按层次缩进行头
     * @return const char* 字符串指针
     * @return nullptr 失败
     */
    const char *to_formatted_string(void) const;

     public:
    /**
     * @brief 格式化输出json字符串, 按层次缩进行头
     * @return const char* 字符串指针
     * @return nullptr 失败
     */
    const char *to_string_pretty(void) const;

     public:
    /**
     * @brief 从现有的item节点复制一份json树，当前对象的root_会指向新克隆的节点
     * @param item cJSON节点
     * @return true 复制成功
     * @return false 复制失败
     */
    bool clone_item(cJSON *item);

     public:
    /**
     * @brief 克隆root_指向的json树，调用者需要cJSON_Delete释放克隆的json树
     * @return cJSON* 复制成功返回克隆的json树
     * @return nullptr 复制失败
     */
    cJSON *clone(void) const;

     public:
    /**
     * @brief 获取json序列化得到的字符串长度
     * @return size_t 长度数值
     */
    size_t length(void) const;

     public:
    /**
     * @brief 获取json序列化得到的字符串
     * @return const char* 字符串指针
     * @return nullptr 失败
     */
    const char *data(void) const;

     public:
    /**
     * @brief 把json序列化并编码成json字符串数值格式：{"key": "value"} => "{\"key\":\"value\"}"
     * @return const char* 字符串指针
     * @return nullptr 失败
     */
    const char *encode(void) const;

     public:
    /**
     * @brief 解析json字符串，如果解析成功，当前对象的root_会指向解析后的json树
     * @param data json字符串
     * @return true 成功
     * @return false 失败
     */
    virtual bool parse(const char *data) = 0;
};
