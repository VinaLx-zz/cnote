#ifndef CNOTE_CREATE_EXECUTOR_H
#define CNOTE_CREATE_EXECUTOR_H

#include "Infra/Option.h"
#include "Infra/OptionSet.h"
#include "Infra/String.h"
#include <stdbool.h>

/**
 * the option for create note
 */
extern const OptionSet create_option;

/**
 * create the note according to the option
 * @param option the input option for the create command
 */
void executeCreate(const Option *option);

/**
 * print help message of create, used by help executor
 */
void helpCreate();

#endif // CNOTE_CREATE_EXECUTOR_H
