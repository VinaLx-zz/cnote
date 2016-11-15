#include "Infra/String.h"

/**
 * expand the string to fit at least the goal_capacity
 * @param this this string
 * @param goal_capacity the minimum capacity after expansion
 * @param allow_copy whether allow the old string to copy to new place
 */
static void __StringExpand(String *this, size_t goal_capacity, bool allow_copy);

void StringInitDefault(String *this) {
    this->data_ = calloc(1, sizeof(char));
    this->length_ = 0;
    this->capacity_ = 1;
}

void StringInitCstring(String *this, const char *that) {
    this->length_ = strlen(that);
    this->capacity_ = this->length_ + 1;
    this->data_ = malloc(this->capacity_ * sizeof(char));
    strcpy(this->data_, that);
}

void StringInitString(String *this, const String *that) {
    this->length_ = that->length_;
    this->capacity_ = this->length_ + 1;
    this->data_ = malloc(this->capacity_ * sizeof(char));
    strcpy(this->data_, that->data_);
}

size_t StringSize(const String *this) {
    return this->length_;
}

char *StringData(String *this) {
    return this->data_;
}

const char *StringConstData(const String *this) {
    return this->data_;
}

char StringGet(const String *this, size_t index) {
    if (index >= this->length_) {
        return -1;
    }
    return this->data_[index];
}

bool StringSet(String *this, size_t index, char c) {
    if (index >= this->length_ or not c) {
        return false;
    }
    this->data_[index] = c;
    return true;
}

void StringDestroy(String *this) {
    if (this->data_) {
        free(this->data_);
        this->data_ = NULL;
    }
}

void StringAssignCstring(String *this, const char *that) {
    this->length_ = strlen(that);
    __StringExpand(this, this->length_ + 1, false);
    strcpy(this->data_, that);
}

void StringAssignString(String *this, const String *that) {
    this->length_ = that->length_;
    __StringExpand(this, this->length_ + 1, false);
    strcpy(this->data_, that->data_);
}

void StringAppendChar(String *this, char c) {
    __StringExpand(this, this->length_ + 1/* c */ + 1, true);
    this->data_[this->length_++] = c;
    this->data_[this->length_] = 0;
}

void StringAppendCstring(String *this, const char *cstr) {
    this->length_ = this->length_ + strlen(cstr);
    __StringExpand(this, this->length_ + 1, true);
    strcat(this->data_, cstr);
}

void StringAppendString(String *this, const String *str) {
    this->length_ = this->length_ + str->length_;
    __StringExpand(this, this->length_ + 1, true);
    strcat(this->data_, str->data_);
}

int StringCompare(const String *lhs, const String *rhs) {
    if (lhs == rhs) {
        return 0;
    }
    int result = strcmp(lhs->data_, rhs->data_);
    if (result > 0) {
        return 1;
    }
    if (result < 0) {
        return -1;
    }
    return 0;
}

void
StringSubstr(const String *this, size_t start, size_t length, String *sub_str) {
    if (start > this->length_) {
        StringAssignCstring(sub_str, "");
        return;
    }
    size_t real_length;
    if (start + length > this->length_) {
        real_length = this->length_ - start;
    } else {
        real_length = length;
    }
    __StringExpand(sub_str, real_length + 1, false);
    strncpy(sub_str->data_, this->data_ + start, real_length);
    sub_str->data_[real_length] = '\0';
    sub_str->length_ = real_length;
}

ssize_t StringFindChar(const String *this, char target, size_t start) {
    if (start >= this->length_) {
        return -1;
    }
    char *result = strchr(this->data_ + start, target);
    if (not result) {
        return -1;
    }
    return result - this->data_;
}

ssize_t
StringFindCstring(const String *this, const char *target, size_t start) {
    if (start >= this->length_) {
        return -1;
    }
    char *result = strstr(this->data_ + start, target);
    if (not result) {
        return -1;
    }
    return result - this->data_;
}

ssize_t
StringFindString(const String *this, const String *target, size_t start) {
    if (start >= this->length_) {
        return -1;
    }
    char *result = strstr(this->data_ + start, StringConstData(target));
    if (not result) {
        return -1;
    }
    return result - this->data_;
}

void __StringExpand(String *this, size_t goal_capacity, bool allow_copy) {
    if (this->capacity_ >= goal_capacity) {
        return;
    }
    for (; this->capacity_ < goal_capacity;) {
        this->capacity_ <<= 1;
    }
    char *new_data = malloc(this->capacity_);

    if (allow_copy) {
        strcpy(new_data, this->data_);
    }

    free(this->data_);
    this->data_ = new_data;
}
