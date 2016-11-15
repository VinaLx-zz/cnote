#ifndef CNOTE_EXECUTOR_H
#define CNOTE_EXECUTOR_H

#include "Executor/CreateExecutor.h"
#include "Executor/HelpExecutor.h"
#include "Executor/ListExecutor.h"
#include "Executor/LoginExecutor.h"
#include "Executor/OpenExecutor.h"
#include "Executor/RemoveExecutor.h"
#include "Executor/RegisterExecutor.h"
#include "Executor/ShowExecutor.h"
#include "CnoteCommand.h"
#include "Infra/Option.h"

typedef struct Executor {
    /**
     * argc from main
     */
    int argc_;

    /**
     * argv from main
     */
    char **argv_;

    /**
     * the command the argv represents
     */
    Command command_;

    /**
     * flag that indicating the executor has been destroyed
     */
    bool destroyed_;

    /**
     * option of the command
     */
    Option option_;

} Executor;

/**
 * constructor of executor using argc and argv from main
 * @param this this executor
 * @param argc argc from main
 * @param argv argv from main
 */
void ExecutorInitArg(Executor *this, int argc, char **argv);

/**
 * destructor for Executor
 * @param this this executor
 */
void ExecutorDestroy(Executor *this);

/**
 * execute the internal command of executor
 * @param this this executor
 */
void ExecutorExecute(Executor *this);

#endif //CNOTE_EXECUTOR_H
