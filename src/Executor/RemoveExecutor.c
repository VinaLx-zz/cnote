#include "Executor/RemoveExecutor.h"
#include "Helpers/NoteHelper.h"
#include "Helpers/ErrorPrinter.h"
#include "Helpers/UserHelper.h"

const struct option remove_long_opt[] = {{NULL, 0, NULL, 0}};
const char remove_short_opt[] = "";

const OptionSet remove_option = {remove_long_opt, remove_short_opt};

/**
 * check whether the number of parameters for remove is reasonable
 * @param option the input option of remove command
 * @return true if pass the check, false if not
 */
static bool __removeCheckParam(const Option *option);

/**
 * remove notes whose titles are in note_names
 * @param note_names the titles of the notes to remove
 */
static void __removeNotes(const StrVector *note_names);

void executeRemove(const Option *option) {
    if (not isLoggedIn()) {
        printWrongLoginState("remove", "remove", "login");
    }

    if (not __removeCheckParam(option)) {
        return;
    }
    // if (we_want_to_remove_the_note_in_the_vector)
    __removeNotes(OptionGetParams(option));
}

void helpRemove() {
    printf(
        "\ncnote - remove : remove your notes from box\n\n"
            "Usage: cnote remove <note>...\n\n");
}

bool __removeCheckParam(const Option *option) {
    if (VectorSize(OptionGetParams(option)) == 0) {
        printNoInput("remove");
        errorSet(CNOTE_WRONG_ARG_NUM);
        return false;
    }
    return true;
}

void __removeNotes(const StrVector *note_names) {
    bool have_not_found = false;
    for (size_t i = 0; i < VectorSize(note_names); ++i) {
        const String *note_name = VectorGetConstString(note_names, i);
        noteRemove(note_name);
        if (errorGet() == CNOTE_NOTE_NOT_FOUND) {
            printNoteNotOwned(
                "remove", StringConstData(note_name),
                StringConstData(&CNOTE_CURRENT_USER));
            have_not_found = true;
            errorClear();
        }
    }
    if (have_not_found) {
        errorSet(CNOTE_NOTE_NOT_FOUND);
    }
}
