%{
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>

#include "Parser.h"
#include "CoolLexer.h"

#undef YY_DECL
#define YY_DECL int CoolLexer::yylex()

%}

white_space       [ \t\n\f\r\v]*
digit             [0-9]
alpha             [A-Za-z_]
alpha_num         ({alpha}|{digit})
hex_digit         [0-9a-fA-F]
identifier_obj    [a-z]{alpha_num}*
identifier_type   [A-Z]{alpha_num}*
unsigned_integer  {digit}+
hex_integer       ${hex_digit}{hex_digit}*
exponent          e[+-]?{digit}+
i                 {unsigned_integer}
real              ({i}\.{i}?|{i}?\.{i}){exponent}?
string            \"(\\|\\t|\\n|\\f|\\b|[^\n\"\\])*\"


%x COMMENT

%option warn nodefault batch noyywrap c++
%option yylineno
%option yyclass="CoolLexer"

%%


"(*)"                 BEGIN(COMMENT);
<COMMENT>"*)"        BEGIN(INITIAL);
<COMMENT>.            { /* skip*/ }
<COMMENT>\n           { lineno++; }
<COMMENT><<EOF>>      Error("EOF in comment");



class                return TOKEN_KW_CLASS;
and                  return TOKEN_LOGICAL_OPERATOR_AND;
case                 return TOKEN_KW_CASE;
let                  return TOKEN_KW_LET;
else                 return TOKEN_KW_ELSE;
if                   return TOKEN_KW_IF;
fi                   return TOKEN_KW_FI;
not                  return TOKEN_KW_NOT;
or                   return TOKEN_LOGICAL_OPERATOR_OR;
of                   return TOKEN_KW_OF;
then                 return TOKEN_KW_THEN;
while                return TOKEN_KW_WHILE;
pool                 return TOKEN_KW_POOL;
loop                 return TOKEN_KW_LOOP;
inherits             return TOKEN_KW_INHERITS;
true                 return TOKEN_KW_TRUE;
false                return TOKEN_KW_FALSE;
new                  return TOKEN_KW_NEW;
esac                 return TOKEN_KW_ESAC;
isvoid               return TOKEN_KW_ISVOID;
self                 return TOKEN_IDENTIFIER_SELF;
SELF_TYPE            return TOKEN_IDENTIFIER_SELFTYPE;

"<="|"=<"            return TOKEN_COMPARISON_OPERATOR_LEQ;
"=>"|">="            return TOKEN_COMPARISON_OPERATOR_GEQ;
"<"                  return TOKEN_COMPARISON_OPERATOR_LESS_THEN;
">"                  return TOKEN_COMPARISON_OPERATOR_MORE_THEN;
"<>"                 return TOKEN_COMPARISON_OPERATOR_NEQ;
"="                  return TOKEN_COMPARISON_OPERATOR_ASSIGN;
"+"                  return TOKEN_ARITHMETIC_OPERATOR_PLUS;
"-"                  return TOKEN_ARITHMETIC_OPERATOR_MINUS;
"*"                  return TOKEN_ARITHMETIC_OPERATOR_MULT;
"/"                  return TOKEN_ARITHMETIC_OPERATOR_DIV;

"<-"                 return TOKEN_ASSIGMENT_OPERATOR_ASSIGN;

"{"                  return TOKEN_UNION_OPERATOR_LBRACE;
"}"                  return TOKEN_UNION_OPERATOR_RBRACE;
"("                  return TOKEN_UNION_OPERATOR_LPAREN;
")"                  return TOKEN_UNION_OPERATOR_RPAREN;
";"                  return TOKEN_EOC_SEMICOLON;
","                  return TOKEN_COMMA;




{unsigned_integer}   return TOKEN_UNSIGNED_INTEGER;

{string}             return TOKEN_STRING;

{identifier_type}    return TOKEN_IDENTIFIER_TYPE;
{identifier_obj}     return TOKEN_IDENTIFIER_OBJ;

[*/+\-,^.;:()\[\]]   return yytext[0];

{white_space}        { /* skip spaces */ }
\n                   lineno++;
.                    Error("unrecognized character");

%%

void CoolLexer::Error(const char* msg) const
{
    std::cerr << "Lexer error (line " << lineno << "): " << msg << ": lexeme '" << YYText() << "'\n";
    std::exit(YY_EXIT_FAILURE);
}
