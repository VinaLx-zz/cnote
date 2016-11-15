#ifndef CNOTE_LIST_EXECUTOR_H
#define CNOTE_LIST_EXECUTOR_H

#include "Infra/Option.h"
#include "Infra/OptionSet.h"

/**
 * the option for list note
 */
extern const OptionSet list_option;

/**
 * list the notes according to the option
 * @param option the input option for the list command
 */
void executeList(const Option *option);

/**
 * print help message of list, used by help executor
 */
void helpList();

#endif // CNOTE_LIST_EXECUTOR_H
