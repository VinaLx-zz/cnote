#ifndef CNOTE_CNOTE_HELPER_H
#define CNOTE_CNOTE_HELPER_H

#include "CnoteConfig.h"
#include "Infra/String.h"
#include <stdbool.h>
#include "Infra/StrVector.h"
#include "Infra/FileHelper.h"

/**
 * check if the title of the note is valid
 * @param note_title the title of the note to check
 * @return true if it's a valid title for a note, false if not
 */
bool noteTitleValid(const String *note_title);

/**
 * open the note that the user owned
 * @param note_title the title of the note
 */
void noteOpenOwned(const String *note_title);

/**
 * open the public note that owned by the owner
 * @param note_title the title of the note
 * @param owner the owner of the note
 */
void noteOpenPublic(const String *note_title, const String *owner);

/**
 * helper function to create a note titled note_title, if fail, CnoteError is set
 * @param note_title the title of the new note
 */
void noteCreate(const String *note_title, bool is_public);

/**
 * helper function to remove a note titled note_title, if fail, CnoteError is set
 * @param note_title the title of the new note
 */
void noteRemove(const String *note_title);

/**
 * get all notes' title according to whether is public
 * @param note_files where the file names of the note stored
 * @param is_public true to get the public notes, false to get private notes
 */
void noteGetFiles(StrVector *note_files, bool is_public);

/**
 * convert note file name to its status
 * @param file_name the file name of the note
 * @param title where the title of the note stored, NULL to omit
 * @param owner where the owner of the note stored, NULL to omit
 * @return true the note corresponding to the file name is public false otherwise
 */
bool noteGetStatus(const String *file_name, String *title, String *owner);

/**
 * show the public note belongs to the owner
 * @param note_title the title of the note
 * @param owner the owner of the note
 */
void noteShowPublic(const String *note_title, const String *owner);

/**
 * show the note the user owned
 * @param note_title the title of the note
 */
void noteShowOwned(const String *note_title);

/**
 * get the note's modification time or access time
 * @param file_name the file name of the note
 * @param time_string where the time string will be stored
 * @param time_type the type of the time to get
 */
void noteGetFileTime(
    const String *file_name, String *time_string, FileTimeType time_type);

#endif // CNOTE_CNOTE_HELPER_H
