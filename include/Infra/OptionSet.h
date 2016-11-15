#ifndef CNOTE_OPTION_SET_H
#define CNOTE_OPTION_SET_H

/**
 * simple struct wrap two options for getopt
 */
typedef struct OptionSet {
    /**
     * the complete option
     */
    const struct option *long_option;

    /**
     * the short option version
     */
    const char *short_option;

} OptionSet;

#endif // CNOTE_OPTION_H
