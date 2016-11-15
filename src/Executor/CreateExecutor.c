#include "Helpers/UserHelper.h"
#include "Executor/CreateExecutor.h"
#include "Helpers/NoteHelper.h"
#include "Helpers/ErrorPrinter.h"

const struct option create_long_opt[] = {
    // when logged in, create the note in public mode
    {"public", no_argument, NULL, 'p'},
    // open the first file created
    {"open", no_argument, NULL, 'o'},
    // routine
    {NULL, 0, NULL, 0}};

const char create_short_opt[] = "op";

const OptionSet create_option = {create_long_opt, create_short_opt};

/**
 * check whether there is a file to create
 * @param option the input option of the create command
 * @return true if pass the check, false if not
 */
static bool __createCheckParam(const Option *option);

/**
 * create notes in note_title
 * @param note_title the names of the notes to create
 */
static void __createNotes(const StrVector *note_title, bool is_public);

void executeCreate(const Option *option) {

    if (not isLoggedIn()) {
        printWrongLoginState("create", "create", "login");
        errorSet(CNOTE_WRONG_LOGIN_STATE);
        return;
    }

    if (not __createCheckParam(option)) {
        return;
    }

    // create notes in option
    __createNotes(OptionGetParams(option), OptionTest(option, 'p'));

    // if 'open' option is set and no error emit during create
    if (not errorGet() and OptionTest(option, 'o')) {
        const String *note = VectorGetConstString(OptionGetParams(option), 0);
        noteOpenOwned(note);
    }
}


void helpCreate() {
    printf(
        "\ncnote - create : Create notes to your own or public box\n\n"
            "Usage: cnote create [--public|-p] [--open|-o] <note>...\n\n"
            "Options:\n\n"
            "-p, --public"
            "create notes to public box when logged in, no effect when logged out\n\n"
            "-o, --open"
            "if all notes are created successfully, open the first one\n\n");
}

bool __createCheckParam(const Option *option) {
    // check whether there's a note to create
    if (VectorSize(OptionGetParams(option)) == 0) {
        printNoInput("create");
        errorSet(CNOTE_WRONG_ARG_NUM);
        return false;
    }
    return true;
}

void __createNotes(const StrVector *note_title, bool is_public) {

    bool have_duplicate = false;
    bool have_invalid_name = false;

    for (size_t i = 0; i < VectorSize(note_title); ++i) {
        const String *note_name = VectorGetConstString(note_title, i);
        if (not noteTitleValid(note_name)) {
            have_invalid_name = true;
            errorClear();
        } else {
            noteCreate(note_name, is_public);
            if (errorGet() == CNOTE_NOTE_EXIST) {
                have_duplicate = true;
                printNoteAlreadyOwned(
                    "create", StringConstData(note_name),
                    StringConstData(&CNOTE_CURRENT_USER));
                errorClear();
            }
        }
    }
    // reset error
    if (have_duplicate) {
        errorSet(CNOTE_NOTE_EXIST);
    } else if (have_invalid_name) {
        errorSet(CNOTE_INVALID_PARAM);
    }
}
