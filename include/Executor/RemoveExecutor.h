#ifndef CNOTE_REMOVE_EXECUTOR_H
#define CNOTE_REMOVE_EXECUTOR_H

#include "Infra/Option.h"
#include "Infra/OptionSet.h"
#include "Infra/String.h"
#include <stdbool.h>

/**
 * the option for remove note
 */
extern const OptionSet remove_option;

/**
 * do remove the note according to the option
 * @param option the input option for the remove command
 */
void executeRemove(const Option *option);

/**
 * print help message of remove, used by help executor
 */
void helpRemove();

#endif // CNOTE_REMOVE_EXECUTOR_H
