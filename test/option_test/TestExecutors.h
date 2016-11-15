#ifndef TEST_EXECUTORS_H
#define TEST_EXECUTORS_H

#include "Infra/Option.h"
#include "Infra/OptionSet.h"

// extern const OptionSet create_option;
// extern const OptionSet help_option;
// extern const OptionSet remove_option;
extern const OptionSet list_option;
// extern const OptionSet open_option;

// void executeCreate(Option *opt);
// void executeHelp(Option *opt);
// void executeRemove(Option *opt);
// void executeOpen(Option *opt);
void executeList(Option *opt);

#endif // TEST_EXECUTORS_H
