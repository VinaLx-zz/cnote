#ifndef CNOTE_CNOTE_ERROR_H
#define CNOTE_CNOTE_ERROR_H

#include <stdbool.h>

typedef char CnoteError;

extern CnoteError cnote_error;

/**
 * set cnote error
 * @param cnote_err the error indication
 */
void errorSet(CnoteError cnote_err);

/**
 * get current error condition and clear the error_flag
 * @return the current error condition
 */
CnoteError errorGet();

/**
 * clear current error
 */
void errorClear();

/**
 * success
 */
#define CNOTE_SUCCESS (0)

/**
 * unknown options or arguments passed when invoking cnote
 */
#define CNOTE_UNKNOWN_ARG (1)

/**
 * number of argument(s) is different required
 */
#define CNOTE_WRONG_ARG_NUM (2)

/**
 * incorrection of the format of the parameter
 */
#define CNOTE_INVALID_PARAM (3)

/**
 * note not found when attempting to open a note
 */
#define CNOTE_NOTE_NOT_FOUND (4)

/**
 * note exist when creating a note or somewhere
 */
#define CNOTE_NOTE_EXIST (5)

/**
 * try to access a user that's not even exist
 */
#define CNOTE_USER_NOT_FOUND (6)

/**
 * duplication of user when register
 */
#define CNOTE_USER_EXIST (7)

/**
 * username not match password
 */
#define CNOTE_AUTHENTICATION_FAIL (8)

/**
 * try to do the thing under a wrong login state
 */
#define CNOTE_WRONG_LOGIN_STATE (9)

/**
 * use a wrong editor when open a note
 */
#define CNOTE_WRONG_EDITOR (10)

#endif // CNOTE_CNOTE_ERROR_H
