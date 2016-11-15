#include "Helpers/ErrorPrinter.h"
#include <stdio.h>

void printSuggestHelp() {
    fprintf(
        stderr, "note: Use \"note help [<command>]\" for more information\n");
}

void printUnknownCommand(const char *command) {
    fprintf(stderr, "note: Unknown command: %s\n", command);
}

void printNoInput(const char *command) {
    fprintf(stderr, "%s: no input file\n", command);
}

void printWrongArgNum(const char *command, size_t expect_num) {
    fprintf(
        stderr, "%s: incorrect parameters number, expect %lu\n", command,
        expect_num);
}

void printNoteAlreadyOwned(
    const char *command, const char *note_name, const char *owner) {
    fprintf(
        stderr, "%s: '%s' already has note '%s'\n", command, owner, note_name);
}

void printNoteNotOwned(
    const char *command, const char *note_name, const char *owner) {
    fprintf(
        stderr, "%s: '%s' doesn't have note '%s'\n", command, owner, note_name);
}

void printLackOption(const char *command, const char *opt_name) {
    fprintf(stderr, "%s: lack of option '%s'\n", command, opt_name);
}

void printUserExist(const char *command, const char *user) {
    fprintf(stderr, "%s: user '%s' already exists\n", command, user);
}

void printUserNotFound(const char *command, const char *username) {
    fprintf(stderr, "%s: user '%s' doesn't exist\n", command, username);
}

void printVerificationFail(const char *command) {
    fprintf(stderr, "%s: user verification fail\n", command);
}

void printWrongLoginState(
    const char *command, const char *operation, const char *state_required) {
    fprintf(
        stderr, "%s: '%s' needs to %s first\n", command, operation,
        state_required);
}

void printWrongEditor(const char *command, const char *editor) {
    fprintf(stderr, "%s: cnote doesn't support editor '%s'\n", command, editor);
}

void printOption(const Option *opt) {
    for (char i = 'a'; i <= 'z'; ++i) {
        if (OptionTest(opt, i)) {
            printf("-%c", i);
            const String *arg = OptionGetArg(opt, i);
            if (arg) {
                printf(": %s\n", StringConstData(arg));
            } else {
                puts("");
            }
        }
    }
    for (char i = 'A'; i <= 'Z'; ++i) {
        if (OptionTest(opt, i)) {
            printf("%c", i);
            const String *arg = OptionGetArg(opt, i);
            if (arg) {
                printf("%s\n", StringConstData(arg));
            } else {
                puts("");
            }
        }
    }
    const StrVector *params = OptionGetParams(opt);
    for (size_t i = 0; i < VectorSize(params); ++i) {
        printf("%s\n", VectorGetConstCstring(params, i));
    }
}
