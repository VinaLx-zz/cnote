#ifndef CNOTE_OPTION_H
#define CNOTE_OPTION_H

#include "CnoteError.h"
#include "Infra/OptionSet.h"
#include "Infra/StrVector.h"
#include "Infra/String.h"
#include <limits.h>
#include <stdbool.h>

// since only options ranged in 'A' - 'Z' and 'a' - 'z' are valid
#define OPTION_MAP_SIZE (CHAR_MAX - 'A')

#define OPT_INDEX(opt) (opt - 'A')

/**
 * the option pass to executor indicating which option is set
 */
typedef struct Option {
    /**
     * the option map indicating which option is set
     */
    bool option_map_[OPTION_MAP_SIZE];

    /**
     * contains the parameter of an option if it has one
     */
    String *option_arg_[OPTION_MAP_SIZE];

    /**
     * parameter
     */
    StrVector params_;

} Option;

/**
 * default initialize the option
 * @param this this option
 */
void OptionInitDefault(Option *this);

/**
 * set corresponding option and args according to argc, argv and option set
 * @param this    this option
 * @param argc    argc
 * @param argv    argv
 * @param opt_set the set of available option
 */
void OptionLoad(Option *this, int argc, char **argv, const OptionSet *opt_set);

/**
 * test whether the option is set
 * @param this this option
 * @param opt  the option to test
 * @return true if the option is set, false otherwise
 */
bool OptionTest(const Option *this, char opt);

/**
 * get option arg of an option
 * @param  this this option
 * @param  opt  the option whose arg is to get
 * @return a pointer to the arg, NULL if not exist
 */
const String *OptionGetArg(const Option *this, char opt);

/**
 * destructor of Option, free all the memory used by param
 * @param this this option
 */
void OptionDestroy(Option *this);

/**
 * get the params
 * @param this this Option
 * @return the const pointer pointing to the vector of params
 */
const StrVector *OptionGetParams(const Option *this);

#endif // CNOTE_OPTION_H
