#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using namespace std;


enum tokenIdentifier {
    ITER_TK,
    VOID_TK,
    VAR_TK,
    RETURN_TK,
    SCAN_TK,
    PRINT_TK,
    PROGRAM_TK,
    COND_TK,
    THEN_TK,
    LET_TK,
    INTL_TK,
    EQUALS_TK,
    LESS_THAN_TK,
    GREATER_THAN_TK,
    COLON_TK,
    PLUS_TK,
    MINUS_TK,
    ASTERISK_TK,
    SLASH_TK,
    PERCENT_TK,
    PERIOD_TK,
    LEFT_PAREN_TK,
    RIGHT_PAREN_TK,
    LEFT_BRACKET_TK,
    RIGHT_BRACKET_TK,
    LEFT_BRACE_TK,
    RIGHT_BRACE_TK,
    SEMI_COLON_TK,
    COMMA_TK,
    ID_TK,
    INT_TK,
    OP_TK,
    DEL_TK,
    EOF_TK,
    ERROR_TK
};

struct Token {
    tokenIdentifier tokenID;
    string tokenInstance;
    int lineNumber;
};

#endif