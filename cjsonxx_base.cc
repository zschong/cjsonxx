#include "cjsonxx_base.h"

CJSON_PUBLIC(cJSON *) cJSON_CreateNumberEx(double num, int precision)
{
#ifdef CJSON_ORIGIN
    return cJSON_CreateNumber(num);
#else
    return cJSON_CreateNumber(num, precision);
#endif
}

cjsonxx_base::~cjsonxx_base(void)
{
    if (nullptr != root_) {
        cJSON_Delete(root_);
    }
}

bool cjsonxx_base::add_item(const char *key, cJSON *item)
{
    if (nullptr == item || nullptr == root_) {
        return false;
    }

    if (cJSON_Object != root_->type) {
        root_ = item;
        return true;
    }
    
    cJSON_DeleteItemFromObject(root_, key);
    if (nullptr == item) {
        return false;
    }

    bool ret = cJSON_AddItemToObject(root_, key, item);
    if (false == ret) {
        cJSON_Delete(item);
    }

    return ret;
}

bool cjsonxx_base::add_item(cJSON *item)
{
    if (nullptr == item || nullptr == root_) {
        return false;
    }

    if (cJSON_Array != root_->type) {
        root_ = item;
        return true;
    }

    bool ret = cJSON_AddItemToArray(root_, item);
    if (false == ret) {
        cJSON_Delete(item);
    }

    return ret;
}

bool cjsonxx_base::clone_item(cJSON *item)
{
    if (nullptr == item) {
        return false;
    }

    cJSON *clone = cJSON_Duplicate(item, true);
    if (nullptr == clone) {
        return false;
    }

    if (root_) {
        cJSON_Delete(root_);
    }

    root_ = clone;
    return true;
}

const char *cjsonxx_base::data(void) const
{
    return to_string();
}

size_t cjsonxx_base::length(void) const
{
    return string_.length();
}

const char *cjsonxx_base::encode(void) const
{
    if (nullptr == root_) {
        return nullptr;
    }

    char *str = cJSON_PrintUnformatted(root_);
    if (nullptr == str) {
        return nullptr;
    }

    cJSON *item = cJSON_CreateString(str);
    if (nullptr == item) {
        cJSON_free(str);
        return nullptr;
    }

    char *jstr = cJSON_PrintUnformatted(item);
    cJSON_Delete(item);
    cJSON_free(str);

    if (nullptr == jstr) {
        return nullptr;
    }

    *(std::string *)&string_ = jstr;
    cJSON_free(jstr);
    return string_.c_str();
}

const char *cjsonxx_base::to_string(void) const
{
    if (nullptr == root_) {
        return nullptr;
    }

    char *str = cJSON_PrintUnformatted(root_);
    if (nullptr == str) {
        return nullptr;
    }

    *(std::string *)&string_ = str;
    cJSON_free(str);
    return string_.c_str();
}

const char *cjsonxx_base::to_formatted_string(void) const
{
    if (nullptr == root_) {
        return nullptr;
    }

    char *str = cJSON_Print(root_);
    if (nullptr == str) {
        return nullptr;
    }

    *(std::string *)&pretty_ = str;
    cJSON_free(str);
    return pretty_.c_str();
}

const char *cjsonxx_base::to_string_pretty(void) const
{
    return to_formatted_string();
}

cJSON *cjsonxx_base::clone(void) const
{
    if (nullptr == root_) {
        return nullptr;
    }
    cJSON *item = cJSON_Duplicate(root_, true);
    if (nullptr == item) {
        return nullptr;
    }

    return item;
}
