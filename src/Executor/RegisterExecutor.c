#include "Executor/RegisterExecutor.h"
#include "Helpers/ErrorPrinter.h"
#include "Helpers/UserHelper.h"
#include <getopt.h>

const struct option register_long_opt[] = {
    // routine
    {NULL, 0, NULL, 0}};

const char register_short_opt[] = "";

const OptionSet register_option = {register_long_opt, register_short_opt};

/**
 * check parameter and option
 * @param option the input option of the register command
 * @bool true if pass the check, false if not
 */
static bool __registerCheckParam(const Option *option);

/**
 * try to add the user to the passwd file, if duplicate, nothing change bug
 * error will be set
 * @param username the username
 */
static void __registerTryAddUser(const String *username);

void executeRegister(const Option *option) {
    if (not __registerCheckParam(option)) {
        return;
    }
    const String *username = VectorGetConstString(OptionGetParams(option), 0);
    if (not userNameValid(username)) {
        return;
    }
    __registerTryAddUser(username);
}

void helpRegister() {
    printf(
        "\ncnote - register: register a user to have a private note box\n\n"
            "Usage: cnote register <username>\n\n");
}

bool __registerCheckParam(const Option *option) {
    if (VectorSize(OptionGetParams(option)) != 1) {
        printWrongArgNum("register", 1);
        errorSet(CNOTE_WRONG_ARG_NUM);
        return false;
    }
    return true;
}

void __registerTryAddUser(const String *username) {
    if (userExist(username)) {
        printUserExist("register", StringConstData(username));
        errorSet(CNOTE_USER_EXIST);
        return;
    }
    String password;
    StringInitDefault(&password);
    if (not readPassword(&password)) {
        return;
    }
    userCreateHome(username);
    // create password file
    userCreatePassword(username, &password);
    StringDestroy(&password);
}
