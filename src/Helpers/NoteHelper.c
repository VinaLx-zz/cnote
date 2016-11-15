#include "CnoteError.h"
#include "Infra/Directory.h"
#include "Helpers/NoteHelper.h"
#include "Helpers/UserHelper.h"
#include <assert.h>
#include <ctype.h>
#include <sys/wait.h>

/**
 * convert the note title to its logical owned note path without existence check
 * @param note_title the title of the note
 * @param note_path where the logical path of the note would be stored
 * @param is_public true to convert to the public path, false to be private
 */
static void
__noteOwnedToPath(const String *note_title, String *note_path, bool is_public);

/**
 * convert the note title to the logical public note path without existence check
 * @param note_title the title of the note
 * @param owner the owner of the note
 * @param note_path where the logical path of the note would be stored
 */
static void __notePublicToPath(
    const String *note_title, const String *owner, String *note_path);

/**
 * search the note title that presume the user owned the note
 * @param note_title the title of the note
 * @param note_path where the path to the note would be stored, NULL to disable
 * @return true if found, false otherwise
 */
static bool __noteSearchOwned(const String *note_title, String *note_path);

/**
 * search the note title according to it's owner whose permission is public
 * @param note_title the title of the note
 * @param owner the owner of the note
 * @param note_path where the path to the note would be stored, NULL to disable
 * @return true if found, false otherwise
 */
static bool __noteSearchPublic(
    const String *note_title, const String *owner, String *note_path);

/**
 * open the note according to the path
 * @param path the path to the note
 */
static void __noteOpenPath(const String *path);

/**
 * get the content of the note and store every line in the reult
 * @param note_path the path to the note
 * @param result where the lines of the note store
 */
static void __noteGetContent(const String *note_path, StrVector *result);

bool noteTitleValid(const String *note_title) {
    if (StringSize(note_title) > MAX_TITLE_LENGTH) {
        printf("title: shouldn't be longer than %d\n", MAX_TITLE_LENGTH);
        errorSet(CNOTE_INVALID_PARAM);
        return false;
    }
    for (size_t i = 0; i < StringSize(note_title); ++i) {
        char current_char = StringGet(note_title, i);
        if (not isalnum(current_char) and current_char not_eq '_' and
            current_char not_eq '-') {
            printf(
                "title: invalid character '%c', "
                    "should only contain alpha, number, underscore and dash\n",
                current_char);
            errorSet(CNOTE_INVALID_PARAM);
            return false;
        }
    }
    return true;
}

void noteOpenOwned(const String *note_title) {
    String note_path;
    StringInitDefault(&note_path);
    if (not __noteSearchOwned(note_title, &note_path)) {
        errorSet(CNOTE_NOTE_NOT_FOUND);
    } else {
        fileEnableEdit(&note_path);
        __noteOpenPath(&note_path);
        fileRestoreMode(&note_path);
    }
    StringDestroy(&note_path);
}

void noteOpenPublic(const String *note_title, const String *owner) {
    String note_path;
    StringInitDefault(&note_path);
    if (not __noteSearchPublic(note_title, owner, &note_path)) {
        errorSet(CNOTE_NOTE_NOT_FOUND);
    } else {
        __noteOpenPath(&note_path);
    }
    StringDestroy(&note_path);
}

void noteCreate(const String *note_title, bool is_public) {
    String note_path;
    StringInitDefault(&note_path);

    // check the box with different permission
    __noteOwnedToPath(note_title, &note_path, not is_public);
    if (fileExist(&note_path)) {
        errorSet(CNOTE_NOTE_EXIST);
    } else {
        __noteOwnedToPath(note_title, &note_path, is_public);

        FilePemission permission = is_public ? PUBLIC_MODE : PRIVATE_MODE;
        if (not fileCreate(&note_path, permission)) {
            errorSet(CNOTE_NOTE_EXIST);
        }
    }
    StringDestroy(&note_path);
}

void noteRemove(const String *note_title) {
    String note_path;
    StringInitDefault(&note_path);
    bool search_result = __noteSearchOwned(note_title, &note_path);
    if (not search_result) {
        errorSet(CNOTE_NOTE_NOT_FOUND);
    } else {
        fileRemove(&note_path);
    }
    StringDestroy(&note_path);
}

void noteGetFiles(StrVector *note_files, bool is_public) {
    Directory note_dir;
    DirectoryInitDefault(&note_dir);
    if (is_public) {
        DirectoryOpen(&note_dir, &CNOTE_PUBLIC_NOTE_PATH);
    } else {
        DirectoryOpen(&note_dir, &CNOTE_USER_NOTE_PATH);
    }
    String file_path, dir_entry;
    StringInitDefault(&file_path);
    StringInitDefault(&dir_entry);
    for (; DirectoryNextEntry(&note_dir, &dir_entry);) {
        // ensure the entry of the directory is actually a file(a note)
        StringAssignString(&file_path, DirectoryPath(&note_dir));
        StringAppendString(&file_path, &dir_entry);
        if (fileExist(&file_path)) {
            VectorPushString(note_files, &dir_entry);
        }
    }
    DirectoryDestroy(&note_dir);
    StringDestroy(&file_path);
    StringDestroy(&dir_entry);
}

bool noteGetStatus(const String *file_name, String *title, String *owner) {
    const char *file_name_cstr = StringConstData(file_name);
    char title_buffer[MAX_TITLE_LENGTH] = "";
    char owner_buffer[MAX_USERNAME_LENGTH] = "";
    sscanf(file_name_cstr, "%s%s", title_buffer, owner_buffer);
    if (title) {
        StringAssignCstring(title, title_buffer);
    }
    // if no owner's read, it's a private note
    bool is_public = owner_buffer[0];
    if (owner) {
        if (is_public) {
            StringAssignCstring(owner, owner_buffer);
        } else {
            StringAssignString(owner, &CNOTE_CURRENT_USER);
        }
    }
    return is_public;
}

void noteGetFileTime(
    const String *file_name, String *time_string, FileTimeType time_type) {
    String file_path;
    StringInitDefault(&file_path);
    // determine the note is public or not according to file name of the note
    bool is_public = noteGetStatus(file_name, NULL, NULL);
    if (is_public) {
        // CNOTE_PUBLIC_NOTE_PATH/file_name
        StringAssignString(&file_path, &CNOTE_PUBLIC_NOTE_PATH);
    } else {
        // CNOTE_USER_NOTE_PATH/file_name
        StringAssignString(&file_path, &CNOTE_USER_NOTE_PATH);
    }
    StringAppendString(&file_path, file_name);
    fileGetTimeString(&file_path, time_string, time_type);
    StringDestroy(&file_path);
}

void noteShowPublic(const String *note_title, const String *owner) {
    String note_path;
    StringInitDefault(&note_path);
    if (not __noteSearchPublic(note_title, owner, &note_path)) {
        errorSet(CNOTE_NOTE_NOT_FOUND);
    } else {
        StrVector note_contents;
        VectorInitDefault(&note_contents);
        __noteGetContent(&note_path, &note_contents);
        for (size_t i = 0; i < VectorSize(&note_contents); ++i) {
            printf("%s", VectorGetConstCstring(&note_contents, i));
        }
        VectorDestroy(&note_contents);
    }
    StringDestroy(&note_path);
}

void noteShowOwned(const String *note_title) {
    String note_path;
    StringInitDefault(&note_path);

    if (not __noteSearchOwned(note_title, &note_path)) {
        errorSet(CNOTE_NOTE_NOT_FOUND);
    } else {
        StrVector note_contents;
        VectorInitDefault(&note_contents);
        __noteGetContent(&note_path, &note_contents);
        for (size_t i = 0; i < VectorSize(&note_contents); ++i) {
            printf("%s", VectorGetConstCstring(&note_contents, i));
        }
        VectorDestroy(&note_contents);
    }
    StringDestroy(&note_path);
}

void
__noteOwnedToPath(const String *note_title, String *note_path, bool is_public) {

    assert(isLoggedIn()); // only when is logged in can this function be used

    if (is_public) {
        __notePublicToPath(note_title, &CNOTE_CURRENT_USER, note_path);
    } else {
        StringAssignString(note_path, &CNOTE_USER_NOTE_PATH);
        StringAppendString(note_path, note_title);
    }
}

void __notePublicToPath(
    const String *note_title, const String *owner, String *note_path) {
    StringAssignString(note_path, &CNOTE_PUBLIC_NOTE_PATH);
    StringAppendString(note_path, note_title);
    StringAppendChar(note_path, ' ');
    StringAppendString(note_path, owner);
}

bool __noteSearchOwned(const String *note_title, String *note_path) {

    assert(isLoggedIn()); // only when logged in can this function be used

    String search_path;
    StringInitDefault(&search_path);
    __noteOwnedToPath(note_title, &search_path, false);

    if (fileExist(&search_path)) {
        if (note_path) {
            StringAssignString(note_path, &search_path);
        }
        StringDestroy(&search_path);
        return true;
    }

    StringDestroy(&search_path);
    return __noteSearchPublic(note_title, &CNOTE_CURRENT_USER, note_path);
}

bool __noteSearchPublic(
    const String *note_title, const String *owner, String *note_path) {
    String search_path;
    StringInitDefault(&search_path);
    __notePublicToPath(note_title, owner, &search_path);

    bool search_result;
    if ((search_result = fileExist(&search_path)) and note_path) {
        StringAssignString(note_path, &search_path);
    }

    StringDestroy(&search_path);
    return search_result;
}

void __noteOpenPath(const String *path) {
    if (not fork()) {
        if (execlp(
            StringConstData(&CNOTE_EDITOR), StringConstData(&CNOTE_EDITOR),
            StringConstData(path), (char *) 0) < 0) {
            errorSet(CNOTE_WRONG_EDITOR);
        }
    } else {
//        int child_status;
        wait(NULL);
    }
}

void __noteGetContent(const String *note_path, StrVector *result) {
    FILE *note_stream = fileOpenRead(note_path);

    assert(note_stream); // note must exist

    VectorClear(result);
    String line;
    StringInitDefault(&line);
    for (; fileGetline(note_stream, &line);) {
        VectorPushString(result, &line);
    }
    fclose(note_stream);
    StringDestroy(&line);
}
