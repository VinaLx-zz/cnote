#include "Infra/Option.h"
#include <getopt.h>

/**
 * set option correspond to opt and opt arg
 * @param this this option
 * @param opt the option to set
 * @param opt_arg the argument of the option, NULL if no argument for the option
 */
static void __OptionSet(Option *this, char opt, const char *opt_arg);

void OptionInitDefault(Option *this) {
    memset(this->option_arg_, 0, sizeof(this->option_arg_));
    memset(this->option_map_, 0, sizeof(this->option_map_));
    VectorInitDefault(&this->params_);
}

bool OptionTest(const Option *this, char opt) {
    return this->option_map_[OPT_INDEX(opt)];
}

void OptionLoad(Option *this, int argc, char **argv, const OptionSet *opt_set) {
    for (int opt; (opt = getopt_long(
        argc, argv, opt_set->short_option, opt_set->long_option, NULL)) !=
                  -1;) {
        if (opt == '?') {
            errorSet(CNOTE_UNKNOWN_ARG);
            return;
        } else {
            __OptionSet(this, (char) opt, optarg);
        }
    }
    for (int i = optind; i < argc; ++i) {
        VectorPushCstring(&this->params_, argv[i]);
    }
}

const String *OptionGetArg(const Option *this, char opt) {
    return this->option_arg_[OPT_INDEX(opt)];
}

void OptionDestroy(Option *this) {
    for (size_t i = 0; i < OPTION_MAP_SIZE; ++i) {
        if (this->option_arg_[i]) {
            StringDestroy(this->option_arg_[i]);
            free(this->option_arg_[i]);
        }
    }
    VectorDestroy(&this->params_);
}

const StrVector *OptionGetParams(const Option *this) {
    return &this->params_;
}

void __OptionSet(Option *this, char opt, const char *opt_arg) {
    this->option_map_[OPT_INDEX(opt)] = true;
    if (opt_arg) {
        this->option_arg_[OPT_INDEX(opt)] = malloc(sizeof(String));
        StringInitCstring(this->option_arg_[OPT_INDEX(opt)], opt_arg);
    }
}
