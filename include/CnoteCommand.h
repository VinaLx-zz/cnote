#ifndef CNOTE_CNOTECOMMAND_H
#define CNOTE_CNOTECOMMAND_H

#include "Infra/String.h"
#include "Infra/OptionSet.h"
#include "Infra/Option.h"

/**
 * Command represents each command in an integer form
 */
typedef enum Command {
    UNKNOWN = -1,
    HELP = 0,
    CREATE = 1,
    REMOVE = 2,
    OPEN = 3,
    LIST = 4,
    REGISTER = 5,
    LOGIN = 6,
    SHOW = 7
} Command;

/**
 * initialize all command strings
 */
void commandInit();

/**
 * destroy all command strings
 */
void commandClear();

/**
 * choose the command executor according to the command_string
 * @param command_string the string represents a command
 * @return the enum constant of the command
 */
Command commandChoose(const char *command_string);

#endif //CNOTE_CNOTECOMMAND_H
