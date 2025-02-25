#ifndef PARSER_H
#define PARSER_H

/* Token types */
enum TokenType {
    TOKEN_AND = 1,
    TOKEN_ARRAY = 2,
    TOKEN_BEGIN = 3,
    TOKEN_CASE = 4,
    TOKEN_CONST = 5,
    TOKEN_DIV,
    TOKEN_DO,
    TOKEN_DOWNTO,
    TOKEN_ELSE,
    TOKEN_END,
    TOKEN_FILE,
    TOKEN_FOR,
    TOKEN_FUNCTION,
    TOKEN_GOTO,
    TOKEN_IF,
    TOKEN_IN,
    TOKEN_LABEL,
    TOKEN_MOD,
    TOKEN_NIL,
    TOKEN_NOT,
    TOKEN_OF,
    TOKEN_PACKED,
    TOKEN_PROCEDURE,
    TOKEN_PROGRAM,
    TOKEN_RECORD,
    TOKEN_REPEAT,
    TOKEN_SET,
    TOKEN_THEN,
    TOKEN_TO,
    TOKEN_TYPE,
    TOKEN_UNTIL,
    TOKEN_VAR,
    TOKEN_WHILE,
    TOKEN_WITH,
    TOKEN_LEQ,
    TOKEN_GEQ,
    TOKEN_NEQ,
    TOKEN_EQ,
    TOKEN_DOUBLEDOT,
    TOKEN_UNSIGNED_INTEGER,
    TOKEN_REAL,
    TOKEN_HEX_INTEGER,
    TOKEN_STRING,
    TOKEN_IDENTIFIER
};

#endif
