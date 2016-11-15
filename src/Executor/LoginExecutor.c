#include "Executor/LoginExecutor.h"
#include "CnoteConfig.h"
#include "Helpers/ErrorPrinter.h"
#include "Helpers/UserHelper.h"

const struct option login_long_opt[] = {
    // print current state of login
    {"print", no_argument, NULL, 'p'},
    // silent and don't output SUCCESS message
    {"silent", no_argument, NULL, 's'},
    // log out
    {"quit", no_argument, NULL, 'q'},
    // routine
    {NULL, 0, NULL, 0}};

const char login_short_opt[] = "sqp";

const OptionSet login_option = {login_long_opt, login_short_opt};

/**
 * check parameter for login
 * @param option the input option of the login command
 * @return true if pass the check, false if not
 */
static bool __loginCheckParam(const Option *option);

/**
 * user login, add a login state file to CNOTE_HOME, if fail, cnote_error would
 * be set
 * @param username username
 * @param password password
 */
static void __login(const String *username, const String *password);

/**
 * print current login state
 */
static void __loginPrintState();

/**
 * check current state whether a login is permitted
 * @return true if a login is permitted, false otherwise
 */
static bool __loginCheckState();

/**
 * user logout
 */
static void __logout();

/**
 * print a message indicating the login or logout operation sucess
 * @param in_or_out specify log in or out
 * @param username  the user related to the operation
 */
static void __logSuccess(const char *in_or_out, const String *username);

void executeLogin(const Option *option) {
    if (not __loginCheckParam(option)) {
        return;
    }
    if (OptionTest(option, 'q')) {
        __logout();
        if (not errorGet() and not OptionTest(option, 's')) {
            __logSuccess("out", &CNOTE_CURRENT_USER);
        }
        return;
    }

    if (OptionTest(option, 'p')) {
        __loginPrintState();
        return;
    }

    if (not __loginCheckState()) {
        return;
    }

    const String *username = VectorGetConstString(OptionGetParams(option), 0);
    String password;
    StringInitDefault(&password);
    if (not readPassword(&password)) {
        return;
    }
    __login(username, &password);

    if (not errorGet() and not OptionTest(option, 's')) {
        __logSuccess("in", username);
    }

    StringDestroy(&password);
}

void helpLogin() {
    printf(
        "\ncnote-login: login and enter a login state before logout\n\n"
            "Usage: cnote login [--silent|-s] [[--quit|-q] | [--print|-p] | <username>]\n\n"
            "Options:\n\n"
            "-s, --silent:\n"
            "suppress output message when successfully login or logout"
            "(doesn't suppress error message)\n\n"
            "-q, --quit\n"
            "log out from a user\n\n"
            "-p, --print\n"
            "print current login state and exit\n\n");
}

bool __loginCheckParam(const Option *option) {
    if (OptionTest(option, 'q')) {
        if (VectorSize(OptionGetParams(option))) {
            printWrongArgNum("logout", 0);
            errorSet(CNOTE_WRONG_ARG_NUM);
            return false;
        }
        return true;
    }
    if (OptionTest(option, 'p')) {
        if (VectorSize(OptionGetParams(option))) {
            printWrongArgNum("login -p", 0);
            errorSet(CNOTE_WRONG_ARG_NUM);
            return false;
        }
        return true;
    }
    if (1 != VectorSize(OptionGetParams(option))) {
        printWrongArgNum("login", 1);
        errorSet(CNOTE_WRONG_ARG_NUM);
        return false;
    }
    return true;
}

void __login(const String *username, const String *password) {
    userVerification(username, password);
    if (errorGet()) {
        printVerificationFail("login");
        return;
    }
    userCreateLoginFile(username);
}

void __loginPrintState() {
    if (isLoggedIn()) {
        printf(
            "cnote: %s is logged in\n", StringConstData(&CNOTE_CURRENT_USER));
    } else {
        printf("cnote: no one's logged in\n");
    }
}

bool __loginCheckState() {
    if (isLoggedIn()) {
        // login: login require logout
        printWrongLoginState("login", "login", "logout");
        errorSet(CNOTE_WRONG_LOGIN_STATE);
        return false;
    }
    return true;
}

void __logout() {
    if (not isLoggedIn()) {
        printWrongLoginState("logout", "logout", "login");
        errorSet(CNOTE_WRONG_LOGIN_STATE);
        return;
    }
    userDestroyLoginFile();
}

void __logSuccess(const char *in_or_out, const String *username) {
    printf(
        "log%s: user '%s' logged %s\n", in_or_out, StringConstData(username),
        in_or_out);
}
