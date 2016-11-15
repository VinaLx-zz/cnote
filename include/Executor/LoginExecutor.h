#ifndef CNOTE_LOGIN_EXECUTOR_H
#define CNOTE_LOGIN_EXECUTOR_H

#include "Infra/Option.h"

/**
 * the option set for the login command
 */
extern const OptionSet login_option;

/**
 * login or logout according to the option
 * @param option the input option for the login command
 */
void executeLogin(const Option *option);

/**
 * print help message of login, used by help executor
 */
void helpLogin();

#endif // CNOTE_LOGIN_EXECUTOR_H
