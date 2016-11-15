#include "CnoteCommand.h"

/**
 * string that invoke the help command
 */
String CNOTE_COMMAND_HELP;

/**
 * string that invoke the create command
 */
String CNOTE_COMMAND_CREATE;

/**
 * string that invoke the remove command
 */
String CNOTE_COMMAND_REMOVE;

/**
 * string that invoke the open command
 */
String CNOTE_COMMAND_OPEN;

/**
 * string that invoke the list command
 */
String CNOTE_COMMAND_LIST;

/**
 * string that invoke the register command
 */
String CNOTE_COMMAND_REGISTER;

/**
 * string that invoke the login command
 */
String CNOTE_COMMAND_LOGIN;

/**
 * string the invoke the show command
 */
String CNOTE_COMMAND_SHOW;

void commandInit() {
    StringInitCstring(&CNOTE_COMMAND_HELP, "help");
    StringInitCstring(&CNOTE_COMMAND_CREATE, "create");
    StringInitCstring(&CNOTE_COMMAND_REMOVE, "remove");
    StringInitCstring(&CNOTE_COMMAND_OPEN, "open");
    StringInitCstring(&CNOTE_COMMAND_LIST, "list");
    StringInitCstring(&CNOTE_COMMAND_REGISTER, "register");
    StringInitCstring(&CNOTE_COMMAND_LOGIN, "login");
    StringInitCstring(&CNOTE_COMMAND_SHOW, "show");
}

void commandClear() {
    StringDestroy(&CNOTE_COMMAND_HELP);
    StringDestroy(&CNOTE_COMMAND_CREATE);
    StringDestroy(&CNOTE_COMMAND_REMOVE);
    StringDestroy(&CNOTE_COMMAND_OPEN);
    StringDestroy(&CNOTE_COMMAND_LIST);
    StringDestroy(&CNOTE_COMMAND_REGISTER);
    StringDestroy(&CNOTE_COMMAND_LOGIN);
    StringDestroy(&CNOTE_COMMAND_SHOW);
}

Command commandChoose(const char *command_string) {
    if (STR_EQ(command_string, StringConstData(&CNOTE_COMMAND_HELP))) {
        return HELP;
    } else if (STR_EQ(command_string, StringConstData(&CNOTE_COMMAND_CREATE))) {
        return CREATE;
    } else if (STR_EQ(command_string, StringConstData(&CNOTE_COMMAND_REMOVE))) {
        return REMOVE;
    } else if (STR_EQ(command_string, StringConstData(&CNOTE_COMMAND_OPEN))) {
        return OPEN;
    } else if (STR_EQ(command_string, StringConstData(&CNOTE_COMMAND_LIST))) {
        return LIST;
    } else if (STR_EQ(command_string,
                      StringConstData(&CNOTE_COMMAND_REGISTER))) {
        return REGISTER;
    } else if (STR_EQ(command_string, StringConstData(&CNOTE_COMMAND_LOGIN))) {
        return LOGIN;
    } else if (STR_EQ(command_string, StringConstData(&CNOTE_COMMAND_SHOW))) {
        return SHOW;
    }
    return UNKNOWN;
}
