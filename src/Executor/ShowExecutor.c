#include "Executor/ShowExecutor.h"
#include "Helpers/ErrorPrinter.h"
#include "Helpers/NoteHelper.h"
#include "Helpers/UserHelper.h"

const struct option show_long_opt[] = {
    // specify the owner to show other's note
    {"owner", required_argument, NULL, 'o'},
    // routine
    {NULL, 0, NULL, 0}};

const char show_short_opt[] = "o:";

const OptionSet show_option = {show_long_opt, show_short_opt};

/**
 * check parameter of show
 * @param option the input option of the show command
 * @return true if pass the check, false if not
 */
static bool __showCheckParam(const Option *option);

void executeShow(const Option *option) {

    if (not __showCheckParam(option)) {
        return;
    }

    if (not isLoggedIn() and not OptionTest(option, 'o')) {
        errorSet(CNOTE_WRONG_LOGIN_STATE);
        printWrongLoginState("show", "show without 'o' option", "login");
        return;
    }

    const String *owner = OptionTest(option, 'o') ? OptionGetArg(
        option, 'o') : (const String *) &CNOTE_CURRENT_USER;
    const String *title = VectorGetConstString(OptionGetParams(option), 0);


    if (not StringCompare(owner, &CNOTE_CURRENT_USER)) {
        noteShowOwned(title);
    } else {
        noteShowPublic(title, owner);
    }

    if (errorGet()) {
        printNoteNotOwned(
            "show", StringConstData(title), StringConstData(owner));
    }
}

void helpShow() {
    printf(
        "cnote-show: show the content of a note without opening it\n\n"
            "Usage: cnote show [-o <owner> | --owner=<owner>] <note>\n\n"
            "Options:\n\n"
            "-o <owner>, --owner <owner>\n"
            "specify the owner of the note when showing a public note\n\n");
}

bool __showCheckParam(const Option *option) {
    if (VectorSize(OptionGetParams(option)) != 1) {
        printWrongArgNum("show", 1);
        errorSet(CNOTE_WRONG_ARG_NUM);
        return false;
    }
    return true;
}