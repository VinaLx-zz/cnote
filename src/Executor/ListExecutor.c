#include "Executor/ListExecutor.h"
#include "Helpers/NoteHelper.h"
#include "Helpers/ErrorPrinter.h"
#include "Helpers/UserHelper.h"
#include "Helpers/ListFormater.h"
#include "Helpers/NoteChecker.h"

const struct option list_long_opt[] = {
    // title contains a substring of argument
    {"title", required_argument, NULL, 't'},
    // choose the owner of the note
    {"owner", required_argument, NULL, 'o'},
    // print access time instead of modification time
    {"access-time", no_argument, NULL, 'u'},
    // list private note only
    {"private", no_argument, NULL, 'i'},
    // list public note only
    {"public", no_argument, NULL, 'p'},
    // routine
    {NULL, 0, NULL, 0}};
const char list_short_opt[] = "pit:o:u";

const OptionSet list_option = {list_long_opt, list_short_opt};

/**
 * check parameter of list (normally list have no parameters, only options)
 * @param option the input option of the list command
 * @return true if pass the check, false if not
 */
static bool __listCheckParam(const Option *option);

/**
 * list public notes according to option
 * @param option the option of the list command
 * @param result where the result will be stored
 */
static void __listPublicNotes(const Option *option, StrVector *result);

/**
 * list private notes if is logged in according to option
 * @param option the option of the list
 * @param result where the result will be stored
 */
static void __listPrivateNotes(const Option *option, StrVector *result);

/**
 * implementation of listPublic and listPrivate Notes
 * @param option the option of the list command
 * @param result where the list result will be stored
 * @param is_public true to get public notes, false to get private notes
 */
static void
__listNotesImpl(const Option *option, StrVector *result, bool is_public);

/**
 * filter out all note_file that meet the requirement of the option
 * @param option the option and their args of the list
 * @param origin the original note_files list
 * @param filtered where the valid note_files will be stored
 */
static void __listFilter(
    const Option *option, const StrVector *origin, StrVector *filtered);

/**
 * determine whether the single note_file meets the requirement of option
 * @param option the option for the list
 * @param note_file the note file to check
 * @return true if pass the filter, false if not
 */
static bool __listFilterOne(const Option *option, const String *note_file);

/**
 * append the formated list result to the list_result
 * @param option the option of the list
 * @param note_files the file names of the notes
 * @param result where the list result is stored
 * @param is_public true indicating public notes, false indicating private ones
 */
static void __listFormat(
    const Option *option, const StrVector *note_files, StrVector *list_result);

/**
 * format one entry according to the option
 * @param option the option of the list command
 * @param note_file the file name to be format
 * @param result where the formated result stored
 * @param is_public true indicating a public note, false indicating a private one
 */
static void
__listFormatOne(const Option *option, const String *note_file, String *result);

/**
 * print the result of list
 * @param result the result of the list
 */
static void __listPrintResult(const Option *option, const StrVector *result) {
    for (size_t i = 0; i < VectorSize(result); ++i) {
        puts(VectorGetConstCstring(result, i));
    }
}

void executeList(const Option *option) {
    if (not __listCheckParam(option)) {
        return;
    }
    StrVector list_result;
    VectorInitDefault(&list_result);

    if (not OptionTest(option, 'i')) {
        __listPublicNotes(option, &list_result);
    }
    if (isLoggedIn() and not OptionTest(option, 'p')) {
        __listPrivateNotes(option, &list_result);
    }
    __listPrintResult(option, &list_result);
    VectorDestroy(&list_result);
}

void helpList() {
    printf(
        "\ncnote-list: list public notes and private notes if logged in\n\n"
            "Usage: cnote list [--public|-p] [--private|-i] [--title=<title> | -t <title>]\n"
            "                  [--owner=<owner> | -o <owner>] [--access-time|-u]\n\n"
            "Options:\n\n"
            "-p, --public:\n"
            "list public notes only\n\n"
            "-i, --private:\n"
            "list private notes only\n\n"
            "-o <owner>, --owner=<owner>\n"
            "only list notes belongs to the owner\n\n"
            "-t <title>, --title=<title>\n"
            "only list notes of whose title the <title> argument is a substring\n\n"
            "-u, --access-time\n"
            "use access time instead of modification time in the list\n\n");
}

bool __listCheckParam(const Option *option) {
    if (VectorSize(OptionGetParams(option))) {
        printWrongArgNum("list", 0);
        errorSet(CNOTE_WRONG_ARG_NUM);
        return false;
    }
    return true;
}

void __listPublicNotes(const Option *option, StrVector *result) {
    __listNotesImpl(option, result, true);
}

void __listPrivateNotes(const Option *option, StrVector *result) {
    __listNotesImpl(option, result, false);
}

void __listNotesImpl(const Option *option, StrVector *result, bool is_public) {
    StrVector note_files;
    VectorInitDefault(&note_files);
    noteGetFiles(&note_files, is_public);

    StrVector filtered_files;
    VectorInitDefault(&filtered_files);
    __listFilter(option, &note_files, &filtered_files);
    VectorDestroy(&note_files);

    __listFormat(option, &filtered_files, result);
    VectorDestroy(&filtered_files);
}

void __listFormat(
    const Option *option, const StrVector *note_files, StrVector *list_result) {
    String result_buffer;
    StringInitDefault(&result_buffer);
    for (size_t i = 0; i < VectorSize(note_files); ++i) {
        __listFormatOne(
            option, VectorGetConstString(note_files, i), &result_buffer);
        VectorPushString(list_result, &result_buffer);
    }
    StringDestroy(&result_buffer);
}

void
__listFormatOne(const Option *option, const String *note_file, String *result) {
    String note_title, owner;
    StringInitDefault(&note_title);
    StringInitDefault(&owner);
    StringAssignCstring(result, "");
    bool is_public = noteGetStatus(note_file, &note_title, &owner);

    setvbuf(stdout, 0, _IONBF, 0);

    formatAddPermission(is_public, result);

    FileTimeType time_type = MODIFY_TIME;
    if (OptionTest(option, 'u')) {
        time_type = ACCESS_TIME;
    }

    formatAddTime(note_file, time_type, result);

    formatAddBasic(&note_title, &owner, result);
    StringDestroy(&note_title);
    StringDestroy(&owner);
}

void __listFilter(
    const Option *option, const StrVector *origin, StrVector *filtered) {
    for (size_t i = 0; i < VectorSize(origin); ++i) {
        const String *current_note = VectorGetConstString(origin, i);
        if (__listFilterOne(option, current_note)) {
            VectorPushString(filtered, current_note);
        }
    }
}

bool __listFilterOne(const Option *option, const String *note_file) {
    if (OptionTest(option, 'o') and not checkOwner(
        note_file, OptionGetArg(option, 'o'))) {
        return false;
    }

    if (OptionTest(option, 't') and not checkTitle(
        note_file, OptionGetArg(option, 't'))) {
        return false;
    }

    return true;
}

