#ifndef CNOTE_LIST_HELPER_H
#define CNOTE_LIST_HELPER_H

#include "Infra/String.h"
#include "Infra/FileHelper.h"

/**
 * append the permission to the note information
 * @param result the note information string
 * @param is_public the permission for the note
 */
void formatAddPermission(bool is_public, String *result);

/**
 * append the basic information about a note to reult
 * @param note_name the title of a note
 * @param owner the owner of the note
 * @param result the note information string
 */
void
formatAddBasic(const String *note_name, const String *owner, String *result);

/**
 * append the time of the result to the note information string
 * @param note_file the file name of the note
 * @param time_type the type of the time (including ACCESS_TIME and MODIFY_TIME)
 * @param result the note information string
 */
void formatAddTime(const String *note_file, FileTimeType time_type, String *result);

#endif //CNOTE_LIST_HELPER_H
