#ifndef CNOTE_USER_HELPER_H
#define CNOTE_USER_HELPER_H

#include "Infra/String.h"
#include <crypt.h>
#include <stdio.h>

/**
 * max length of the password due to the encryption ability
 */
#define PASSWORD_MAX_SIZE (8)

/**
 * determine whether the username is valid
 * @param username the username to be checked
 * @return true if valid, false if not
 */
bool userNameValid(const String *username);

/**
 * check whether the home directory for the user exist
 * @param username username
 * @return true if the home directory exist, false if not
 */
bool userExist(const String *username);

/**
 * create home directory for the user if it doesn't have one
 * @param username the user to create the directory
 * @return true if directory created, false otherwise
 */
bool userCreateHome(const String *username);

/**
 * read password from file
 * @param password the place where password will be stored
 * @return true if success, false due to incorrection of password format
 */
bool readPassword(String *password);

/**
 * create a password file in the user's home directory
 * @param username the user want to create a password file
 * @param password the password
 */
void userCreatePassword(const String *username, const String *password);

/**
 * create a login file under CNOTE_HOME represents a login state
 * @param username the user whose logged in
 */
void userCreateLoginFile(const String *username);

/**
 * check whether it's a logged in state
 * @return true if it's logged in, false if not
 */
bool isLoggedIn();

/**
 * verify the is the user match the password
 * @param username username
 * @param password password
 */
void userVerification(const String *username, const String *password);

/**
 * destroy the file that represents the state of login
 */
void userDestroyLoginFile();

#endif // CNOTE_USER_HELPER_H
