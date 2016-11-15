#include "CnoteConfig.h"
#include "CnoteCommand.h"
#include "Infra/FileHelper.h"

String CNOTE_HOME;
String CNOTE_USERS_FOLDER;
String CNOTE_PUBLIC_NOTE_PATH;

/**
 * initialize folders config and create them
 */
static void __configInitFolders();

String CNOTE_EDITOR;

/**
 * initialize the default editor choice
 */
static void __configInitEditor();

String CNOTE_LOGIN_FILE_PATH;

/**
 * initialize the path to the config files
 */
static void __configInitFiles();

String CNOTE_CURRENT_USER;

/**
 * initialize current user according to the state of login file
 */
static void __configInitUser();

String CNOTE_USER_HOME;
String CNOTE_USER_NOTE_PATH;

/**
 * initialize all path config of a user
 */
static void __configInitUserPath();

/**
 * clear the folder config strings
 */
static void __configClearFolders();

/**
 * clear the editor config string
 */
static void __configClearEditor();

/**
 * clear the user-related config string
 */
static void __configClearUser();

/**
 * clear the file config strings
 */
static void __configClearFiles();

void configInit() {
    __configInitFolders();
    __configInitEditor();
    __configInitFiles();
    __configInitUserPath();
    commandInit();

    atexit(configClear);
}

void configClear() {
    __configClearFolders();
    __configClearEditor();
    __configClearUser();
    __configClearFiles();
    commandClear();
}

void __configInitFolders() {
    StringInitCstring(&CNOTE_HOME, getenv("HOME"));
    StringAppendCstring(&CNOTE_HOME, "/.cnote/");
    dirCreate(&CNOTE_HOME, PUBLIC_MODE);

    StringInitString(&CNOTE_USERS_FOLDER, &CNOTE_HOME);
    StringAppendCstring(&CNOTE_USERS_FOLDER, "/users/");
    dirCreate(&CNOTE_USERS_FOLDER, PUBLIC_MODE);

    StringInitString(&CNOTE_PUBLIC_NOTE_PATH, &CNOTE_HOME);
    StringAppendCstring(&CNOTE_PUBLIC_NOTE_PATH, "/note/");
    dirCreate(&CNOTE_PUBLIC_NOTE_PATH, PUBLIC_MODE);
}

void __configInitEditor() {
    // TODO check if editor exist
    StringInitCstring(&CNOTE_EDITOR, "gedit");
}

void __configInitFiles() {
    StringInitString(&CNOTE_LOGIN_FILE_PATH, &CNOTE_HOME);
    StringAppendCstring(&CNOTE_LOGIN_FILE_PATH, "/.login");
}

void __configInitUser() {
    StringInitDefault(&CNOTE_CURRENT_USER);
    FILE *login_file = fileOpenRead(&CNOTE_LOGIN_FILE_PATH);
    if (login_file) {
        char username[MAX_USERNAME_LENGTH + 1];
        // username is guaranteed not containing spaces and no longer than
        // USER_MAX_SIZE
        fscanf(login_file, "%s", username);

        StringAssignCstring(&CNOTE_CURRENT_USER, username);
        fclose(login_file);
    }
}

void __configInitUserPath() {
    __configInitUser();
    if (StringSize(&CNOTE_CURRENT_USER)) {

        StringInitString(&CNOTE_USER_HOME, &CNOTE_USERS_FOLDER);
        StringAppendString(&CNOTE_USER_HOME, &CNOTE_CURRENT_USER);
        //        dirCreate(&CNOTE_USER_HOME); // created when register

        StringInitString(&CNOTE_USER_NOTE_PATH, &CNOTE_USER_HOME);
        StringAppendCstring(&CNOTE_USER_NOTE_PATH, "/note/");
        dirCreate(&CNOTE_USER_NOTE_PATH, PUBLIC_MODE);

    } else {
        StringInitDefault(&CNOTE_USER_HOME);
        StringInitDefault(&CNOTE_USER_NOTE_PATH);
    }
}

void __configClearFolders() {
    StringDestroy(&CNOTE_HOME);
    StringDestroy(&CNOTE_PUBLIC_NOTE_PATH);
    StringDestroy(&CNOTE_USERS_FOLDER);
}


void __configClearEditor() {
    StringDestroy(&CNOTE_EDITOR);
}

void __configClearUser() {
    StringDestroy(&CNOTE_CURRENT_USER);
    StringDestroy(&CNOTE_USER_HOME);
    StringDestroy(&CNOTE_USER_NOTE_PATH);
}

void __configClearFiles() {
    StringDestroy(&CNOTE_LOGIN_FILE_PATH);
}

