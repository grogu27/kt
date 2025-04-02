/*
 * Infix Notation calculator 
 * 1 + 2 * 3 = 7
 */

%{
#include <stdio.h>
#include <math.h>

int yylex();
void yyerror(char const *);
%}

/* Type for semantic values (default int) */
%define api.value.type {double}
%token NUM
%left '-' '+'
%left '*' '/'
%right '^' /* exponentiation */
%precedence NEG /* negation--unary minus */


%%

input:
  %empty
| input line
;

line:
  '\n'
| exp '\n'      { printf ("%.10g\n", $1); }
;

exp:
  NUM
| exp '+' exp  { $$ = $1 + $3; }
| exp '-' exp  { $$ = $1 - $3; }
| exp '*' exp  { $$ = $1 * $3; }
| exp '/' exp  { 
    if (fabs($3) < 2.2e-308){ //fabs($3) < DBL_MIN
        yyerror("Division by zero");
        YYABORT;
    }
    $$ = $1 / $3; }
| exp '^' exp  { $$ = pow($1, $3); } /* Exponentiation */
| '-' exp %prec NEG{ $$ = -$2; }  /* Unary minus */
| '(' exp ')'  { $$ = $2; }
;

%%

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

int yylex()
{
    int c = getchar();
    while (c == ' ' || c == '\t') {
        c = getchar();
    }

    /* Process floating point numbers */
    if (c == '.' || isdigit(c)) {
        ungetc(c, stdin);
        if (scanf("%lf", &yylval) != 1)
            abort();
        return NUM;
    } else if (c == EOF) {
        return YYEOF;
    }
    /* Single char token */
    return c;
}

void yyerror(char const *s)
{
    fprintf(stderr, "Error: %s\n", s);
}

int main()
{
    return yyparse();
}
