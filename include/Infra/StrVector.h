#ifndef CNOTE_STR_VECTOR_H
#define CNOTE_STR_VECTOR_H

#include "Infra/String.h"

typedef struct StrVector {
    /**
     * the array that contains the pointer to the string
     */
    String **data_;

    /**
     * the size of the vector
     */
    size_t size_;

    /**
     * the maximum size current memory space can contain
     */
    size_t capacity_;

} StrVector;

/**
 * default constructor for vector
 * @param this this vector
 */
void VectorInitDefault(StrVector *this);

/**
 * destructor for the vector
 * @param this this vector
 */
void VectorDestroy(StrVector *this);

/**
 * getter for the number of elements this vector contains
 * @param this this vector
 */
size_t VectorSize(const StrVector *this);

/**
 * add a string whose content is equal to cstr into the vector
 * @param this this vector
 * @param cstr the c-style string to copy
 */
void VectorPushCstring(StrVector *this, const char *cstr);

/**
 * add a string whose content is equal to str into the vector
 * @param this this vector
 * @param str  the string to copy
 */
void VectorPushString(StrVector *this, const String *str);

/**
 * set the content of the string at the target index of the vector equal to cstr
 * @param this  this vector
 * @param index the index of the string to set
 * @param cstr  the cstring to copy to the index
 * @return      true if success, false if out of range
 */
bool VectorSetCstring(StrVector *this, size_t index, const char *cstr);

/**
 * set the content of the string at the target index of the vector equal to str
 * @param this  this vector
 * @param index the index of the string to set
 * @param str   the string to copy to the index
 * @return      true if success, false if out of range
 */
bool VectorSetString(StrVector *this, size_t index, const String *str);

/**
 * get the pointer to the content of the string at the index
 * @param this  this vector
 * @param index the index of the string to obtain
 * @return      the pointer to the content of the string, NULL if out of range
 */
const char *VectorGetConstCstring(const StrVector *this, size_t index);

/**
 * get the pointer to the string at the index
 * @param this  this vector
 * @param index the index of the string to obtain
 * @return      the pointer to the string, NULL if out of range
 */
const String *VectorGetConstString(const StrVector *this, size_t index);

/**
 * clear the vector's content
 * @param this this vector
 */
void VectorClear(StrVector *this);

#endif // CNOTE_STR_VECTOR_H
