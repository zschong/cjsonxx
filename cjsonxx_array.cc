#include "cjsonxx_array.h"
#include "cjsonxx_object.h"

cjsonxx_array::cjsonxx_array(void) : cjsonxx_base()
{
    root_ = cJSON_CreateArray();
}

int cjsonxx_array::get_size(void) const
{
    if (nullptr == root_) {
        return 0;
    }

    return cJSON_GetArraySize(root_);
}

int cjsonxx_array::get_int(int index) const
{
    if (nullptr == root_) {
        return 0;
    }

    cJSON *item = cJSON_GetArrayItem(root_, index);
    if (nullptr == item) {
        return 0;
    }

    return item->valueint;
}

bool cjsonxx_array::get_bool(int index) const
{
    if (nullptr == root_) {
        return false;
    }

    cJSON *item = cJSON_GetArrayItem(root_, index);
    if (nullptr == item) {
        return false;
    }

    return item->valueint != 0;
}

double cjsonxx_array::get_float(int index) const
{
    if (nullptr == root_) {
        return 0.0;
    }

    cJSON *item = cJSON_GetArrayItem(root_, index);
    if (nullptr == item) {
        return 0.0;
    }

    return item->valuedouble;
}

const char *cjsonxx_array::get_string(int index) const
{
    if (nullptr == root_) {
        return nullptr;
    }

    cJSON *item = cJSON_GetArrayItem(root_, index);
    if (nullptr == item) {
        return nullptr;
    }

    return item->valuestring;
}

bool cjsonxx_array::add_string(const char *value)
{
    if (nullptr == value || nullptr == root_) {
        return false;
    }

    cJSON *item = cJSON_CreateString(value);
    if (nullptr == item) {
        return false;
    }

    return add_item(item);
}

bool cjsonxx_array::add_int(int value)
{
    if (nullptr == root_) {
        return false;
    }

    cJSON *item = cJSON_CreateNumberEx(value, 0);
    if (nullptr == item) {
        return false;
    }

    return add_item(item);
}

bool cjsonxx_array::add_float(double value, uint8_t precision = 4)
{
    if (nullptr == root_) {
        return false;
    }

    cJSON *item = cJSON_CreateNumberEx(value, precision);
    if (nullptr == item) {
        return false;
    }

    return add_item(item);
}

bool cjsonxx_array::add_bool(bool value)
{
    if (nullptr == root_) {
        return false;
    }

    cJSON *item = cJSON_CreateBool(value);
    if (nullptr == item) {
        return false;
    }

    return add_item(item);
}

bool cjsonxx_array::add_object(const cjsonxx_object &obj)
{
    if (nullptr == root_) {
        return false;
    }

    return add_item(obj.clone());
}

bool cjsonxx_array::add_array(const cjsonxx_array &arr)
{
    if (nullptr == root_) {
        return false;
    }

    return add_item(arr.clone());
}

cJSON *cjsonxx_array::move(void) const
{
    cjsonxx_array &r = *(cjsonxx_array *)this;

    cJSON          *ret = r.root_;
    r.root_             = cJSON_CreateObject();
    return ret;
}

bool cjsonxx_array::parse(const char *json)
{
    if (nullptr == json) {
        return false;
    }

    cJSON *root = cJSON_Parse(json);
    if (nullptr == root) {
        return false;
    }
    
    if (cJSON_Array != root->type) {
        cJSON_Delete(root);
        return false;
    }

    if (root_ != nullptr) {
        cJSON_Delete(root_);
    }

    root_ = root;
    return true;
}
