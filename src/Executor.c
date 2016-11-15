#include <Executor/ShowExecutor.h>
#include "Executor.h"
#include "Helpers/ErrorPrinter.h"

Executor executor;

const OptionSet *command_options[] = {
    &help_option, &create_option, &remove_option, &open_option, &list_option,
    &register_option, &login_option, &show_option
};

typedef void (*CommandExecutor)(const Option *);

CommandExecutor command_executors[] = {
    &executeHelp, &executeCreate, &executeRemove, &executeOpen, &executeList,
    &executeRegister, &executeLogin, &executeShow
};

/**
 * shift argv by one to set the option for sub-command
 * @param this this Executor
 */
static void __ExecutorShiftArg(Executor *this);

/**
 * set the command according to argc and argv
 * @param this this executor
 * @return error code
 */
static void __ExecutorSetCommand(Executor *this);

/**
 * load param and option into option_
 * @param this this executor
 */
static void __ExecutorLoadArg(Executor *this);

void executorClear() {
    ExecutorDestroy(&executor);
}

void ExecutorInitArg(Executor *this, int argc, char **argv) {
    this->argc_ = argc;
    this->argv_ = argv;
    this->destroyed_ = false;
    OptionInitDefault(&this->option_);

    atexit(executorClear);

    __ExecutorLoadArg(this);
}

void ExecutorDestroy(Executor *this) {
    if (not this->destroyed_) {
        OptionDestroy(&this->option_);
        this->destroyed_ = true;
    }
}

void ExecutorExecute(Executor *this) {
    command_executors[this->command_](&this->option_);
}

void __ExecutorShiftArg(Executor *this) {
    --this->argc_;
    ++this->argv_;
}

void __ExecutorSetCommand(Executor *this) {
    // no command
    if (this->argc_ == 1) {
        printSuggestHelp();
        errorSet(CNOTE_WRONG_ARG_NUM);
        return;
    }

    const char *cmd_str = this->argv_[1];
    enum Command command = commandChoose(cmd_str);

    if (command == UNKNOWN) {
        printUnknownCommand(cmd_str);
        printSuggestHelp();
        errorSet(CNOTE_UNKNOWN_ARG);
        return;
    }

    this->command_ = command;
    return;
}

void __ExecutorLoadArg(Executor *this) {

    __ExecutorSetCommand(this);
    if (errorGet()) {
        return;
    }

    // shiftArg don't produce error
    __ExecutorShiftArg(this);

    // load the arg into the option
    OptionLoad(
        &this->option_, this->argc_, this->argv_,
        command_options[this->command_]);

    if (errorGet()) {
        if (errorGet() == CNOTE_UNKNOWN_ARG) {
            printSuggestHelp();
        }
        return;
    }
}
