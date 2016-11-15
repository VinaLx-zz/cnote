#ifndef CNOTE_SHOWEXECUTOR_H
#define CNOTE_SHOWEXECUTOR_H

#include "Infra/OptionSet.h"
#include "Infra/Option.h"

/**
 * option for show note content
 */
extern const OptionSet show_option;

/**
 * do the real show thing
 * @param option the input option for the show command
 */
void executeShow(const Option *option);

/**
 * print help message of show, used by help executor
 */
void helpShow();

#endif //CNOTE_SHOWEXECUTOR_H
