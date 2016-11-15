#ifndef CNOTE_STRING_H
#define CNOTE_STRING_H

#include <iso646.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct String {
    /**
     * data contains
     */
    char *data_;

    /**
     * length of the string
     */
    size_t length_;

    /**
     * the capacity of data
     */
    size_t capacity_;

} String;

/**
 * determine whether two c-strings are equal
 */
#define STR_EQ(s1, s2) (strcmp(s1, s2) == 0)

/**
 * default constructor
 * @param this this string
 */
void StringInitDefault(String *this);

/**
 * initialize this string from a c-style string
 * @param this this string
 * @param that the c-style string to copy
 */
void StringInitCstring(String *this, const char *that);

/**
 * initialize this string from another string
 * @param this this string
 * @param that the string to copy
 */
void StringInitString(String *this, const String *that);

/**
 * getter for the length of the string
 * @param this this string
 * @return the length of this string
 */
size_t StringSize(const String *this);

/**
 * getter for the underlying c-string of the String
 * @param this this string
 * @return the c-string of the String
 */
char *StringData(String *this);

/**
 * getter for the underlying c-string of a const string
 * @param this this string
 * @return the c-string of the string
 */
const char *StringConstData(const String *this);

/**
 * getter for the character of the specific index
 * @param  this  this string
 * @param  index the character index
 * @return the character in that index, -1 if out of range
 */
char StringGet(const String *this, size_t index);

/**
 * setter for the character of the specific index
 * @param  this  this string
 * @param  index the character index
 * @param  c     the character to set
 * @return       true if success, false if out of range
 */
bool StringSet(String *this, size_t index, char c);

/**
 * destructor of the string, free data
 * @param this this string
 */
void StringDestroy(String *this);

/**
 * assign this string from a c-style string
 * @param this this string
 * @param that the c style string to copy
 */
void StringAssignCstring(String *this, const char *that);

/**
 * assign another string to this
 * @param this this string
 * @param that the pointer to the string for this to copy
 */
void StringAssignString(String *this, const String *that);

/**
 * append the character to this string
 * @param this this string
 * @param c the character to append
 */
void StringAppendChar(String *this, char c);

/**
 * append the c-style string to this string
 * @param this this string
 * @param cstr the c-style string to append
 */
void StringAppendCstring(String *this, const char *cstr);

/**
 * append another string to this string
 * @param this this string
 * @param str the string to append
 */
void StringAppendString(String *this, const String *str);

/**
 * compare two strings with lexigraphical order
 * @param lhs string on the left
 * @param rhs string on the right
 * @return -1 if lhs < rhs, 1 if lhs > rhs, 0 if lhs == rhs
 */
int StringCompare(const String *lhs, const String *rhs);

/**
 * get an substring of the this string
 * @param this   this string
 * @param start  the index to start
 * @param length the maximum length of the substring
 * @param sub_str where the substring would be stored
 */
void
StringSubstr(const String *this, size_t start, size_t length, String *sub_str);

/**
 * find first appear of target in this string
 * @param  this   this string
 * @param  target the target character
 * @param  start  the index start to find
 * @return the index of the location of the character, -1 if not found
 */
ssize_t StringFindChar(const String *this, char target, size_t start);

/**
 * find first appear of target string in this string
 * @param  this   this string
 * @param  target the target string
 * @param  start  the index start to find
 * @return the index of the location of the string, -1 if not found
 */
ssize_t StringFindCstring(const String *this, const char *target, size_t start);

/**
 * find first appear of target string in this string
 * @param  this   this string
 * @param  target the target string
 * @param  start  the index start to find
 * @return the index of the location of the string, -1 if not found
 */
ssize_t
StringFindString(const String *this, const String *target, size_t start);

#endif // CNOTE_Infra/String.h
