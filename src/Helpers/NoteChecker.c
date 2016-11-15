#include "Helpers/NoteChecker.h"
#include "Helpers/NoteHelper.h"

bool checkOwner(const String *note_file, const String *expect_owner) {
    String owner;
    StringInitDefault(&owner);
    noteGetStatus(note_file, NULL, &owner);
    bool result = StringCompare(&owner, expect_owner) == 0;
    StringDestroy(&owner);
    return result;
}

bool checkTitle(const String *note_file, const String *title_substr) {
    String note_title;
    StringInitDefault(&note_title);
    noteGetStatus(note_file, &note_title, NULL);
    bool result = StringFindString(&note_title, title_substr, 0) != -1;
    StringDestroy(&note_title);
    return result;
}

