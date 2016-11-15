#ifndef CNOTE_REGISTER_EXECUTOR_H
#define CNOTE_REGISTER_EXECUTOR_H

#include "Infra/Option.h"
#include "Infra/OptionSet.h"

/**
 * the option for register a user
 */
extern const OptionSet register_option;

/**
 * register a user according to the option
 * @param option the input option for the register command
 */
void executeRegister(const Option *option);

/**
 * print help message of register, used by help executor
 */
void helpRegister();

#endif // CNOTE_REGISTER_EXECUTOR_H
