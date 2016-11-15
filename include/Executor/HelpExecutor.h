#ifndef CNOTE_HELP_EXECUTOR_H
#define CNOTE_HELP_EXECUTOR_H

#include "Infra/Option.h"
#include "Infra/OptionSet.h"

/**
 * the option set for the help command
 */
extern const OptionSet help_option;

/**
 * print help message of some command
 * @param option the input option for the help command
 */
void executeHelp(const Option *option);

/**
 * print help message of help, used by help executor
 */
void helpHelp();

#endif // CNOTE_HELP_EXECUTOR_H
