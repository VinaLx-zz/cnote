#include "Helpers/UserHelper.h"
#include "CnoteConfig.h"
#include "CnoteError.h"
#include "Infra/FileHelper.h"
#include <ctype.h>

/**
 * convert the username string to his home directory and store in home_dir
 * @param username the username
 * @param home_dir the destination
 */
static void __userToUserHome(const String *username, String *home_dir);

/**
 * determine whether the password is valid
 * @param  password the password to be checked
 * @return true if valid, false if not
 */
static bool __userPasswordValid(const String *password);

static char *salt = "CN";

/**
 * encrypt password to the code
 * @param key  the user input password
 * @param code the password after encryption
 */
static void __passwordEncrypt(const String *key, String *code) {
    StringAssignCstring(code, crypt(StringConstData(key), salt));
}

/**
 * get the path of the user's password file
 * @param username the user's username
 * @param passwd_path where the path of the password stored
 */
static void __userPasswordPath(const String *username, String *passwd_path) {
    __userToUserHome(username, passwd_path);
    StringAppendCstring(passwd_path, "/password");
}

/**
 * get the encrypted password of user
 * @param user     the owner of the password
 * @param password where encrypted password will be stored
 */
static void __userGetPassword(const String *username, String *password);


bool userNameValid(const String *username) {
    if (StringSize(username) > MAX_USERNAME_LENGTH) {
        errorSet(CNOTE_INVALID_PARAM);
        fprintf(
            stderr, "username: shouldn't be longer than %d\n",
            MAX_USERNAME_LENGTH);
        return false;
    }
    for (size_t i = 0; i < StringSize(username); ++i) {
        if (not isalnum(StringGet(username, i)) and
            StringGet(username, i) not_eq '_') {
            errorSet(CNOTE_INVALID_PARAM);
            fprintf(
                stderr, "username: should only contain alpha or digit or "
                    "underscore '_'\n");
            return false;
        }
    }
    return true;
}

bool userExist(const String *username) {
    String home_dir;
    StringInitDefault(&home_dir);
    __userToUserHome(username, &home_dir);

    bool result = dirExist(&home_dir);
    StringDestroy(&home_dir);
    return result;
}

bool userCreateHome(const String *username) {
    String home_dir;
    StringInitDefault(&home_dir);
    __userToUserHome(username, &home_dir);

    bool result = dirCreate(&home_dir, PUBLIC_MODE);
    StringDestroy(&home_dir);
    return result;
}

bool readPassword(String *password) {
    char buffer[PASSWORD_MAX_SIZE + 1 /* new line from fgets*/ +
                1 /*detect over-length*/ + 1 /*\0*/];
    printf("password: ");
    fgets(buffer, PASSWORD_MAX_SIZE + 3, stdin);

    // change tail to '\0', delete the trailing '\n'
    buffer[strlen(buffer) - 1] = '\0';
    StringAssignCstring(password, buffer);
    return __userPasswordValid(password);
}


void userCreatePassword(const String *username, const String *password) {
    String passwd_path;
    StringInitDefault(&passwd_path);
    __userPasswordPath(username, &passwd_path);

    String encrypted_passwd;
    StringInitDefault(&encrypted_passwd);
    __passwordEncrypt(password, &encrypted_passwd);

    fileCreate(&passwd_path, PRIVATE_MODE);
    FILE *passwd_file = fileOpenTruncate(&passwd_path);

    fprintf(passwd_file, "%s\n", StringConstData(&encrypted_passwd));

    StringDestroy(&passwd_path);
    StringDestroy(&encrypted_passwd);
    fclose(passwd_file);
}

void userCreateLoginFile(const String *username) {
    FILE *login_file = fileOpenTruncate(&CNOTE_LOGIN_FILE_PATH);
    // puts the username into the file
    fprintf(login_file, "%s\n", StringConstData(username));
    fclose(login_file);
}

bool isLoggedIn() {
    return fileExist(&CNOTE_LOGIN_FILE_PATH);
}

void userVerification(const String *username, const String *password) {
    if (not userExist(username)) {
        errorSet(CNOTE_AUTHENTICATION_FAIL);
        return;
    }
    // get the input password
    String encrypted_passwd;
    StringInitDefault(&encrypted_passwd);
    __passwordEncrypt(password, &encrypted_passwd);

    // get real password
    String real_passwd;
    StringInitDefault(&real_passwd);
    __userGetPassword(username, &real_passwd);

    if (StringCompare(&encrypted_passwd, &real_passwd)) {
        errorSet(CNOTE_AUTHENTICATION_FAIL);
    }

    StringDestroy(&encrypted_passwd);
    StringDestroy(&real_passwd);
}

void userDestroyLoginFile() {
    fileRemove(&CNOTE_LOGIN_FILE_PATH);
}

void __userToUserHome(const String *username, String *home_dir) {
    StringAssignString(home_dir, &CNOTE_USERS_FOLDER);
    StringAppendString(home_dir, username);
}

bool __userPasswordValid(const String *password) {
    if (StringSize(password) > PASSWORD_MAX_SIZE) {
        errorSet(CNOTE_INVALID_PARAM);
        fprintf(
            stderr, "password: shouldn't be longer than %d\n",
            PASSWORD_MAX_SIZE);
        return false;
    }
    return true;
}

void __userGetPassword(const String *username, String *password) {
    String passwd_path;
    StringInitDefault(&passwd_path);
    __userPasswordPath(username, &passwd_path);

    FILE *passwd_file = fileOpenRead(&passwd_path);
    char real_passwd[100] /*something way longer than encryted password*/;
    fgets(real_passwd, 100, passwd_file);

    // clear the final '\n'
    real_passwd[strlen(real_passwd) - 1] = '\0';
    StringAssignCstring(password, real_passwd);

    StringDestroy(&passwd_path);
    fclose(passwd_file);
}
