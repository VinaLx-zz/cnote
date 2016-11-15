#include "Helpers/ListFormater.h"
#include "CnoteConfig.h"
#include "Helpers/NoteHelper.h"

void formatAddPermission(bool is_public, String *result) {
    StringAppendCstring(result, is_public ? "Public   " : "Private  ");
}

void
formatAddBasic(const String *note_title, const String *owner, String *result) {
    char buffer[MAX_TITLE_LENGTH + 1 + MAX_USERNAME_LENGTH + 1];
    sprintf(
        buffer, "%-*s %s", MAX_USERNAME_LENGTH, StringConstData(owner),
        StringConstData(note_title));
    StringAppendCstring(result, buffer);
}

void
formatAddTime(const String *note_file, FileTimeType time_type, String *result) {
    String time_string;
    StringInitDefault(&time_string);
    noteGetFileTime(note_file, &time_string, time_type);
    StringAppendString(result, &time_string);
    StringAppendCstring(result, "  ");
    StringDestroy(&time_string);
}
