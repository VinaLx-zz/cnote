#ifndef CNOTE_NOTECHECKER_H_H
#define CNOTE_NOTECHECKER_H_H

#include "Infra/String.h"

/**
 * check the note specify by note_file belongs to the expective owner
 * @param note_file the note's file name
 * @param expect_owner the expective owner of the file
 * @return true if the note belongs to expective owner, false otherwise
 */
bool checkOwner(const String* note_file, const String* expect_owner);

/**
 * check whether the note title contains a certain substring
 * @param note_file the note's file name
 * @param title_substr the expective substring user expect the title to have
 * @return true if the title contains the substring, false otherwise
 */
bool checkTitle(const String* note_file, const String* title_substr);

#endif //CNOTE_NOTECHECKER_H_H
