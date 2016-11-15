#ifndef CNOTE_FILE_HELPER_H
#define CNOTE_FILE_HELPER_H

#include "Infra/String.h"
#include <stdbool.h>
#include <stdio.h>
#include <sys/stat.h>

/**
 * the different time class for a file
 */
typedef enum FileTimeType {

    ACCESS_TIME, MODIFY_TIME, CHANGE_TIME

} FileTimeType;

/**
 * file permission for directory and regular file
 */
typedef enum FilePermission {

    PUBLIC_MODE, PRIVATE_MODE

} FilePemission;

/**
 * check if the file specified by the path exists
 * @param  path the path of the file
 * @return true if the path represents a file, false otherwise
 */
bool fileExist(const String *path);

/**
 * check if the file specified by the path is executable
 * @param  path the path of the file
 * @return  true if the file is executable, false otherwise
 */
bool fileExecutable(const String *path);

/**
 * create a public file, which open the read permission for other and group
 * @param path the path to the file
 * @param permission the permission mode of the file
 * @return true if success, fail if duplicate
 */
bool fileCreate(const String *path, FilePemission pemission);

/**
 * remove a file specified by the path
 * @param  path the path to the file to be removed
 * @return  true if success, false otherwise(possibly not exist)
 */
bool fileRemove(const String *path);

/**
 * unlock the file, so that it can be edit
 * @param path the path to the file
 * @return true if success, false otherwise
 */
bool fileEnableEdit(const String *path);

/**
 * restore the mode of the file that's been unlock
 * @param path the path to the file
 * @return true if success, false if no file is change before
 */
bool fileRestoreMode(const String *path);

/**
 * get the time string of the file in the form of "YYYY-MM-DD HH:MM"
 * @param path the path to the file
 * @param time_string where the time string of file would be stored in
 * @param time_type the type of the file time
 * @return true if success, false otherwise
 */
bool fileGetTimeString(
    const String *path, String *time_string, FileTimeType time_type);

/**
 * open a file in truncate mode and return the stream pointer
 * @param  path the path specifies the file
 * @return FILE stream pointer if success, NULL otherwise
 */
FILE *fileOpenTruncate(const String *path);

/**
 * open a file in read only mode and return the stream pointer
 * @param  path the path specifies the file
 * @return FILE stream pointer if success, NULL otherwise
 */
FILE *fileOpenRead(const String *path);

/**
 * read a whole line from the istream
 * @param istream the line from which is read
 * @param destination where to store the line read
 * @return true if a line is read, false if error or eof
 */
bool fileGetline(FILE *istream, String *destination);

/**
 * check if a directory specified by path exists
 * @param  path the path to the directory
 * @return true if a directory exist, false if not
 */
bool dirExist(const String *path);

/**
 * create a directory with rx of other and group
 * @param path the path to the directory
 * @param permission the abstract permission of the directory
 * @return true if success, false otherwise
 */
bool dirCreate(const String *path, FilePemission permission);

#endif // CNOTE_FILE_HELPER_H
