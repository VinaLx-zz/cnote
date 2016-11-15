#include "CnoteConfig.h"
#include "Executor.h"

extern Executor executor;

int main(int argc, char *argv[]) {
    // initialize configuration by default
    configInit();

    // execute command specified by argv
    ExecutorInitArg(&executor, argc, argv);

    if (not errorGet()) {
        ExecutorExecute(&executor);
    }
    // destroy
    ExecutorDestroy(&executor);

    exit(errorGet());
}
