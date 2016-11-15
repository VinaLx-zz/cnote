#include "Executor/HelpExecutor.h"
#include <getopt.h>
#include <stdio.h>
#include "CnoteCommand.h"
#include "Helpers/ErrorPrinter.h"
#include "Executor/ListExecutor.h"
#include "Executor/CreateExecutor.h"
#include "Executor/LoginExecutor.h"
#include "Executor/OpenExecutor.h"
#include "Executor/RegisterExecutor.h"
#include "Executor/RemoveExecutor.h"
#include "Executor/ShowExecutor.h"  

const struct option help_long_opt[] = {{NULL, 0, NULL, 0}};
const char help_short_opt[] = "";

const OptionSet help_option = {help_long_opt, help_short_opt};

typedef void (*HelpPrinter)();

HelpPrinter help_printers[] = {
    &helpHelp, &helpCreate, &helpRemove, &helpOpen, &helpList, &helpRegister,
    &helpLogin, &helpShow
};

/**
 * print help message of the whole program
 */
static void __help();

/**
 * check parameter in the option of help, cannot be more than one
 * @param option the input option of the help command
 * @return true if pass the check, false if not
 */
static bool __helpCheckParam(const Option *option);

void executeHelp(const Option *option) {
    if (not __helpCheckParam(option)) {
        return;
    }
    if (not VectorSize(OptionGetParams(option))) {
        __help();
        return;
    }
    const String *command_string = VectorGetConstString(
        OptionGetParams(option), 0);
    Command command = commandChoose(StringConstData(command_string));
    if (command == UNKNOWN) {
        printf(
            "help: no help message of %s\n", StringConstData(command_string));
        errorSet(CNOTE_INVALID_PARAM);
        return;
    }
    help_printers[command]();
}

void helpHelp() {
    printf(
        "cnote-help: print help message and exit\n\n"
            "Usage: cnote help [<command>]\n");
}

void __help() {
    printf(
        "\ncnote - the inconvenient note manager :)\n\n"
            "Usage: cnote [command] [<options>] [<args>]\n\n"
            "Command:\n\n"
            "create: create notes to the box\n\n"
            "remove: remove notes from the box\n\n"
            "open: open your or others note\n\n"
            "list: check notes in the box\n\n"
            "register: resgister a user\n\n"
            "login: login or logout a user\n\n");
}

bool __helpCheckParam(const Option *option) {
    if (VectorSize(OptionGetParams(option)) > 1) {
        printWrongArgNum("help", 1);
        errorSet(CNOTE_WRONG_ARG_NUM);
        return false;
    }
    return true;
}
