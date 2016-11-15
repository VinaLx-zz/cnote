#ifndef CNOTE_PRINTER_H
#define CNOTE_PRINTER_H

#include <stddef.h>
#include "Infra/Option.h"

/**
 * suggest the user to use help command
 */
void printSuggestHelp();

/**
 * print a message indicating the command is unknown
 * @param command the unknown command
 */
void printUnknownCommand(const char *command);

/**
 * print a message indictating the command need a parameter
 * @param command the command produces the error
 */
void printNoInput(const char *command);

/**
 * print a message indicating the input parameter number is incorrect
 * @param command the command produces the error
 * @param expect_num the expective number of parameter of the command
 */
void printWrongArgNum(const char *command, size_t expect_num);

/**
 * print a message indicating the file(note) is already exist
 * @param command the command produces the error
 * @param note_name the note title that already exist
 */
void printNoteAlreadyOwned(
    const char *command, const char *note_name, const char *owner);

/**
 * print a message indicating the note doesn't exist
 * @param command the command produces the error
 * @param note_name the note title that doesn't exist
 */
void printNoteNotOwned(
    const char *command, const char *note_name, const char *owner);

/**
 * print a message indicating the user already exists when register
 * @param command the command produces the error
 * @param user the username that already exist
 */
void printUserExist(const char *command, const char *user);

/**
 * print a message indicating the user doesn't exist
 * @param command the command produces the error
 * @param username the username that doens't exist
 */
void printUserNotFound(const char *command, const char *username);

/**
 * print a message indicating the password doesn't match the username
 * @param command the command produces the error
 */
void printVerificationFail(const char *command);

/**
 * print a message indicating the user is in a wrong login state when invoking a command
 * @param command the command produces the error
 * @param operation the operation done by the command
 * @param state_required the login state that required
 */
void printWrongLoginState(
    const char *command, const char *operation, const char *state_required);

/**
 * print a message indicating cnote doesn't support the editor
 * @param command the command produces the error
 * @param editor the invalid editor setting
 */
void printWrongEditor(const char *command, const char *editor);

/**
 * helper function for testing the option
 * @param opt the option
 */
//void printOption(const Option *opt);

#endif //CNOTE_PRINTER_H
