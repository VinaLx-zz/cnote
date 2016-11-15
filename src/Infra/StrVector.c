#include "Infra/StrVector.h"
#include "Infra/String.h"

/**
 * expand the vector to fit at least the goal capacity
 * @param this this vector
 */
void __VectorExpand(StrVector *this, size_t goal_capacity);

void VectorInitDefault(StrVector *this) {
    this->capacity_ = 1;
    this->size_ = 0;
    this->data_ = malloc(sizeof(String *));
}

void VectorDestroy(StrVector *this) {
    if (this->data_) {
        for (size_t i = 0; i < this->size_; ++i) {
            StringDestroy(this->data_[i]);
            free(this->data_[i]);
        }
        free(this->data_);
        this->data_ = NULL;
    }
}

size_t VectorSize(const StrVector *this) {
    return this->size_;
}

void VectorPushCstring(StrVector *this, const char *cstr) {
    __VectorExpand(this, this->size_ + 1);
    String *new_string = malloc(sizeof(String));
    StringInitCstring(new_string, cstr);
    this->data_[this->size_++] = new_string;
}

void VectorPushString(StrVector *this, const String *str) {
    __VectorExpand(this, this->size_ + 1);
    String *new_string = malloc(sizeof(String));
    StringInitString(new_string, str);
    this->data_[this->size_++] = new_string;
}

bool VectorSetCstring(StrVector *this, size_t index, const char *cstr) {
    if (index >= this->size_) {
        return false;
    }
    StringAssignCstring(this->data_[index], cstr);
    return true;
}

bool VectorSetString(StrVector *this, size_t index, const String *str) {
    if (index >= this->size_) {
        return false;
    }
    StringAssignString(this->data_[index], str);
    return true;
}

const char *VectorGetConstCstring(const StrVector *this, size_t index) {
    if (index >= this->size_) {
        return NULL;
    }
    return StringConstData(this->data_[index]);
}

const String *VectorGetConstString(const StrVector *this, size_t index) {
    if (index >= this->size_) {
        return NULL;
    }
    return this->data_[index];
}

void VectorClear(StrVector *this) {
    for (size_t i = 0; i < this->size_; ++i) {
        StringDestroy(this->data_[i]);
        free(this->data_[i]);
    }
    this->size_ = 0;
}


void __VectorExpand(StrVector *this, size_t goal_capacity) {
    if (this->capacity_ >= goal_capacity) {
        return;
    }
    for (; this->capacity_ < goal_capacity;) {
        this->capacity_ <<= 1;
    }
    String **new_data = malloc(this->capacity_ * sizeof(String *));
    memcpy(new_data, this->data_, this->size_ * sizeof(String *));
    free(this->data_);
    this->data_ = new_data;
}
