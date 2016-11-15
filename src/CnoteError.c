#include "CnoteError.h"

CnoteError cnote_error = CNOTE_SUCCESS;

void errorSet(CnoteError cnote_err) {
    cnote_error = cnote_err;
}

CnoteError errorGet() {
    return cnote_error;
}

void errorClear() {
    cnote_error = CNOTE_SUCCESS;
}
