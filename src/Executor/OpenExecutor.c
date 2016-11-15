#include "Executor/OpenExecutor.h"
#include "Helpers/NoteHelper.h"
#include "Helpers/ErrorPrinter.h"
#include "Helpers/UserHelper.h"

const struct option open_long_opt[] = {
    // specify the editor to open the note
    {"editor", required_argument, NULL, 'e'},
    // specify the owner to open others note
    {"owner", required_argument, NULL, 'o'},
    // routine
    {NULL, 0, NULL, 0}};

const char open_short_opt[] = "o:e:";

const OptionSet open_option = {open_long_opt, open_short_opt};

/**
 * check whether parameters are valid for the open command
 * @param option the input option of the open command
 * @return true if pass the check, false if not
 */
static bool __openCheckParam(const Option *option);

/**
 * set the editor of the open command
 * @param editor the editor
 */
static void __openSetEditor(const String *editor);

void executeOpen(const Option *option) {
    if (not __openCheckParam(option)) {
        return;
    }
    if (not isLoggedIn() and not OptionTest(option, 'o')) {
        printWrongLoginState("open", "open without '-o' option", "login");
        errorSet(CNOTE_WRONG_LOGIN_STATE);
        return;
    }

    if (OptionTest(option, 'e')) {
        const String *editor = OptionGetArg(option, 'e');
        __openSetEditor(editor);
        if (errorGet()) {
            printWrongEditor("open", StringConstData(editor));
            return;
        }
    }

    const String *note_title = VectorGetConstString(OptionGetParams(option), 0);
    const String *note_owner = OptionTest(option, 'o') ? OptionGetArg(
        option, 'o') : (const String *) &CNOTE_CURRENT_USER;

    // no 'o' option specify or the parameter of 'o' is the user itself
    if (not StringCompare(
        note_owner, &CNOTE_CURRENT_USER)) {
        noteOpenOwned(note_title);
    } else {
        noteOpenPublic(note_title, note_owner);
    }
    if (errorGet() == CNOTE_NOTE_NOT_FOUND) {
        printNoteNotOwned(
            "open", StringConstData(note_title), StringConstData(note_owner));
    } else if (errorGet() == CNOTE_WRONG_EDITOR) {
        printWrongEditor("open", StringConstData(&CNOTE_EDITOR));
    }
}

void helpOpen() {
    printf(
        "\ncnote-open: open your note or read-only open other's note in public box\n\n"
            "Usage: cnote open <note> [-o <owner> | --owner=<owner>] [-e <editor> | --editor=<editor>]\n\n"
            "Options:\n\n"
            "-o <owner>, --owner=<owner>:\n"
            "specify the owner of the note to open a public note"
            "-e <editor>, --editor=<editor>:\n"
            "specify the editor to open the note, default to be gedit\n"
            "(only support vim, nano and gedit currently)\n\n");
}

bool __openCheckParam(const Option *option) {
    size_t note_num = VectorSize(OptionGetParams(option));

    if (not note_num) {
        printNoInput("open");
        errorSet(CNOTE_WRONG_ARG_NUM);
        return false;
    } else if (note_num > 1) {
        printWrongArgNum("open", 1);
        errorSet(CNOTE_WRONG_ARG_NUM);
        return false;
    }
    return true;
}

void __openSetEditor(const String *editor) {
    const char *editor_cstr = StringConstData(editor);
    if (STR_EQ(editor_cstr, "vim")) {
        StringAssignCstring(&CNOTE_EDITOR, "vim");
    } else if (STR_EQ(editor_cstr, "gedit")) {
        StringAssignCstring(&CNOTE_EDITOR, "gedit");
    } else if (STR_EQ(editor_cstr, "nano")) {
        StringAssignCstring(&CNOTE_EDITOR, "nano");
    } else {
        errorSet(CNOTE_WRONG_EDITOR);
    }
}
