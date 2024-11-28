
#include "cjsonxx_array.h"
#include "cjsonxx_object.h"

cjsonxx_object::cjsonxx_object(void) : cjsonxx_base()
{
    root_ = cJSON_CreateObject();
}

bool cjsonxx_object::find(const char *key) const
{
    if (nullptr == key || nullptr == root_) {
        return false;
    }

    return (nullptr != cJSON_GetObjectItem(root_, key));
}

bool cjsonxx_object::remove(const char *key)
{
    if (nullptr == key || nullptr == root_) {
        return false;
    }

    cJSON *item = cJSON_GetObjectItem(root_, key);
    if (nullptr == item) {
        return false;
    }

    cJSON_DeleteItemFromObject(root_, key);
    return true;
}

int cjsonxx_object::get_int(const char *key) const
{
    if (nullptr == key || nullptr == root_) {
        return 0;
    }

    cJSON *item = cJSON_GetObjectItem(root_, key);
    if (nullptr == item) {
        return 0;
    }

    return item->valueint;
}

bool cjsonxx_object::get_bool(const char *key) const
{
    if (nullptr == key || nullptr == root_) {
        return false;
    }

    cJSON *item = cJSON_GetObjectItem(root_, key);
    if (nullptr == item) {
        return false;
    }

    return item->valueint;
}

double cjsonxx_object::get_float(const char *key) const
{
    if (nullptr == key || nullptr == root_) {
        return 0.0;
    }

    cJSON *item = cJSON_GetObjectItem(root_, key);
    if (nullptr == item) {
        return 0.0;
    }

    return item->valuedouble;
}

const char *cjsonxx_object::get_string(const char *key) const
{
    if (nullptr == key || nullptr == root_) {
        return nullptr;
    }

    cJSON *item = cJSON_GetObjectItem(root_, key);
    if (nullptr == item) {
        return nullptr;
    }

    return item->valuestring;
}

bool cjsonxx_object::get_object(const char *key, cjsonxx_object &obj) const
{
    if (nullptr == key || nullptr == root_) {
        return false;
    }

    cJSON *item = cJSON_GetObjectItem(root_, key);
    if (nullptr == item) {
        return false;
    }

    if (item->type != cJSON_Object) {
        return false;
    }

    return obj.clone_item(item);
}

bool cjsonxx_object::get_array(const char *key, cjsonxx_array &arr) const
{
    if (nullptr == key || nullptr == root_) {
        return false;
    }

    cJSON *item = cJSON_GetObjectItem(root_, key);
    if (nullptr == item) {
        return false;
    }

    if (item->type != cJSON_Array) {
        return false;
    }

    return arr.clone_item(item);
}

bool cjsonxx_object::add_int(const char *key, int value)
{
    if (nullptr == key || nullptr == root_) {
        return false;
    }

    cJSON *item = cJSON_CreateNumberEx(value, 0);
    if (nullptr == item) {
        return false;
    }

    return add_item(key, item);
}

bool cjsonxx_object::add_float(const char *key, double value, uint8_t precision = 4)
{
    if (nullptr == key || nullptr == root_) {
        return false;
    }

    cJSON *item = cJSON_CreateNumberEx(value, precision);
    if (nullptr == item) {
        return false;
    }

    return add_item(key, item);
}

bool cjsonxx_object::add_bool(const char *key, bool value)
{
    if (nullptr == key || nullptr == root_) {
        return false;
    }

    cJSON *item = cJSON_CreateBool(value);
    if (nullptr == item) {
        return false;
    }

    return add_item(key, item);
}

bool cjsonxx_object::add_string(const char *key, const char *value)
{
    if (nullptr == key || nullptr == value || nullptr == root_) {
        return false;
    }

    cJSON *item = cJSON_CreateString(value);
    if (nullptr == item) {
        return false;
    }

    return add_item(key, item);
}

bool cjsonxx_object::add_object(const char *key, const cjsonxx_object &obj)
{
    if (nullptr == key || nullptr == root_) {
        return false;
    }

    return add_item(key, obj.clone());
}

bool cjsonxx_object::add_array(const char *key, const cjsonxx_array &arr)
{
    if (nullptr == key || nullptr == root_) {
        return false;
    }

    return add_item(key, arr.clone());
}

cJSON *cjsonxx_object::move(void) const
{
    cjsonxx_object &r = *(cjsonxx_object *)this;

    cJSON           *ret = r.root_;
    r.root_              = cJSON_CreateObject();
    return ret;
}

bool cjsonxx_object::parse(const char *json)
{
    if (nullptr == json) {
        return false;
    }

    cJSON *root = cJSON_Parse(json);
    if (nullptr == root) {
        return false;
    }
    
    if (cJSON_Object != root->type) {
        cJSON_Delete(root);
        return false;
    }

    if (root_ != nullptr) {
        cJSON_Delete(root_);
    }

    root_ = root;
    return true;
}
