#ifndef CNOTE_OPEN_EXECUTOR_H
#define CNOTE_OPEN_EXECUTOR_H

#include "Infra/Option.h"
#include "Infra/OptionSet.h"
#include "Infra/String.h"
#include <stdbool.h>

/**
 * the option for open note
 */
extern const OptionSet open_option;

/**
 * open a note according to the option
 * @param option the input option for the open command
 */
void executeOpen(const Option *option);

/**
 * print help message of open, used by help executor
 */
void helpOpen();

#endif // CNOTE_OPEN_EXECUTOR_H
