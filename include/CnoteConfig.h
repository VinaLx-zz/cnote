#ifndef CNOTE_CONFIG_H
#define CNOTE_CONFIG_H

#include "Infra/String.h"
#include <getopt.h>

/**
 * the home directory where cnote located
 */
extern String CNOTE_HOME;

/**
 * editor when open a note
 */
extern String CNOTE_EDITOR;

/**
 * where the public note and user folder is located
 */
extern String CNOTE_PUBLIC_NOTE_PATH;

/**
 * where the login state file is located
 */
extern String CNOTE_LOGIN_FILE_PATH;

/**
 * the folder where contains all user's home
 */
extern String CNOTE_USERS_FOLDER;

/**
 * current user of the note
 */
extern String CNOTE_CURRENT_USER;

/**
 * the user's home directory
 */
extern String CNOTE_USER_HOME;

/**
 * the user's private note path;
 */
extern String CNOTE_USER_NOTE_PATH;

/**
 * max length of the username
 */
#define MAX_USERNAME_LENGTH (10)

/**
 * max length of the title of a note
 */
#define MAX_TITLE_LENGTH (30)

/**
 * initialiize the configuration to default option
 */
void configInit();

/**
 * clear all the config string
 */
void configClear();

#endif // CNOTE_CONFIG_H
