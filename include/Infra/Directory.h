#ifndef CNOTE_DIRECTORY_H
#define CNOTE_DIRECTORY_H

#include "Infra/String.h"
#include <dirent.h>
#include <stdbool.h>

typedef struct Directory {

    /**
     * underlying pointer point to the open directory
     */
    DIR *directory_;

    /**
     * the path to the open directory
     */
    String path_;

} Directory;

/**
 * default constructor for directory
 * @param this this directory
 */
void DirectoryInitDefault(Directory *this);

/**
 * use directory path to open a directory
 * @param this this directory
 * @param path the string specify the path of the directory
 */
bool DirectoryOpen(Directory *this, const String *path);

/**
 * close the directory if is opened
 * @param this this directory
 * @return true if successfully close the directory, false if it's already closed
 */
bool DirectoryClose(Directory *this);

/**
 * destructor for the directory, clear the path, close the directory_, unset
 * open_flag
 * @param this this directory
 */
void DirectoryDestroy(Directory *this);

/**
 * getter for the path of current opened directory
 * @param  this this directory
 * @return the path of the directory
 */
const String *DirectoryPath(const Directory *this);

/**
 * get next filename in the directory
 * @param this directory
 * @param entry_name where the next entry will be stored
 * @return true if an entry return successfully, false if reach the end
 */
bool DirectoryNextEntry(Directory *this, String *entry_name);

#endif // CNOTE_DIRECTORY_H
